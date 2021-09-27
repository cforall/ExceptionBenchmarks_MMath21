// Enter and Leave a Try Statement with a Finally Handler

public class TryFinally {
	private static boolean shouldThrow = false;

	private static long loop(int times) {
		long startTime = System.nanoTime();
		for (int count = 0 ; count < times ; ++count) {
			try {
				// ...
			} finally {
				// ...
			}
		}
		long endTime = System.nanoTime();
		return endTime - startTime;
	}

	public static void main(String[] args) {
		int times = 1;
		if (0 < args.length) {
			times = Integer.parseInt(args[0]);
		}

		// Warm-Up:
		loop(1000);

		long time = loop(times);
		System.out.format("Run-Time (s): %.1f%n", time / 1_000_000_000.);
	}
}
