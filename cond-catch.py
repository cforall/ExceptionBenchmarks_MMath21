#!/usr/bin/env python3

# Conditional Match (or Re-Raise)

from time import thread_time_ns


class EmptyException(Exception):
    pass


should_catch = False


def main(argv):
    times = 1
    if 1 < len(argv):
        times = int(argv[1])
    if 2 < len(argv):
        should_catch = 0 < int(argv[2])

    start_time = thread_time_ns()
    for count in range(times):
        try:
            try:
                raise EmptyException()
            except EmptyException as exc:
                if not should_catch:
                    raise
        except EmptyException:
            pass

    end_time = thread_time_ns()
    print('Run-Time (s): {:.1f}'.format((end_time - start_time) / 1_000_000_000.))


if '__main__' == __name__:
    import sys
    main(sys.argv)
