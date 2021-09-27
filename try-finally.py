#!/usr/bin/env python3

# Cross a Try Statement With Finally Clause

from time import thread_time_ns


def main(argv):
    times = 1;
    total_frames = 1;
    if 1 < len(argv):
        times = int(argv[1])
    if 2 < len(argv):
        total_frames = int(argv[2])

    start_time = thread_time_ns()
    for count in range(times):
        try:
            pass
        finally:
            pass

    end_time = thread_time_ns()
    print('Run-Time (s): {:.1f}'.format((end_time - start_time) / 1_000_000_000.))


if '__main__' == __name__:
    import sys
    main(sys.argv)
