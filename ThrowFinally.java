// Throw Across Finally

class EmptyException extends Exception {}

public class ThrowFinally {
	private static void unwind_finally(int frames)
			throws EmptyException {
		if (0 < frames) {
			try {
				unwind_finally(frames - 1);
			} finally {
				// ...
			}
		} else {
			throw new EmptyException();
		}
	}

	private static long loop(int times, int total_frames) {
		long startTime = System.nanoTime();
		for (int count = 0 ; count < times ; ++count) {
			try {
				unwind_finally(total_frames);
			} catch (EmptyException e) {
				// ...
			}
		}
		long endTime = System.nanoTime();
		return endTime - startTime;
	}

	public static void main(String[] args) {
		int times = 1;
		int total_frames = 1;
		if (0 < args.length) {
			times = Integer.parseInt(args[0]);
		}
		if (1 < args.length) {
			total_frames = Integer.parseInt(args[1]);
		}

		// Warm-Up:
		loop(1000, total_frames);

		long time = loop(times, total_frames);
		System.out.format("Run-Time (s): %.1f%n", time / 1_000_000_000.);
	}
}
