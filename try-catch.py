#!/usr/bin/env python3

# Cross a Try Statement with a Termination Handler

from time import thread_time_ns


class NotRaisedException(Exception):
    pass


def main(argv):
    times = 1;
    if 1 < len(argv):
        times = int(argv[1])

    start_time = thread_time_ns()
    for count in range(times):
        try:
            pass
        except NotRaisedException:
            pass

    end_time = thread_time_ns()
    print('Run-Time (s): {:.1f}'.format((end_time - start_time) / 1_000_000_000.))


if '__main__' == __name__:
    import sys
    main(sys.argv)
