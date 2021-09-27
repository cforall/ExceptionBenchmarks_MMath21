#!/usr/bin/env python3

from time import thread_time_ns

def nounwind_fixup(frames, raised_rtn):
    if 0 < frames:
        nounwind_fixup(frames - 1, raised_rtn)
    else:
        fixup = 17;
        raised_rtn(fixup);


def main(argv):
    times = 1
    total_frames = 1
    if 1 < len(argv):
        times = int(argv[1])
    if 2 < len(argv):
        total_frames = int(argv[2])

    raised = lambda lfixup : total_frames + 42		# use local scope => lexical link
    start_time = thread_time_ns()
    for count in range(times):
        nounwind_fixup(total_frames, raised)

    end_time = thread_time_ns()
    print('Run-Time (s): {:.1f}'.format((end_time - start_time) / 1_000_000_000.))


if '__main__' == __name__:
    import sys
    main(sys.argv)
