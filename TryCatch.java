// Enter and Leave a Try Statement with a Termination Handler

class NotRaisedException extends Exception {}

public class TryCatch {
	private static boolean shouldThrow = false;

	private static long loop(int times) {
		long startTime = System.nanoTime();
		for (int count = 0 ; count < times ; ++count) {
			try {
				if (shouldThrow) {
					throw new NotRaisedException();
				}
			} catch (NotRaisedException e) {
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
