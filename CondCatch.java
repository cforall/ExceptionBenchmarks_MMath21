// Conditional Match (or Re-Raise)

class EmptyException extends Exception {}

public class CondCatch {
	static boolean should_catch = false;

	private static long loop(int times) {
		long startTime = System.nanoTime();
		for (int count = 0 ; count < times ; ++count) {
			try {
				try {
					throw new EmptyException();
				} catch (EmptyException exc) {
					if (!should_catch) {
						throw exc;
					}
				}
			} catch (EmptyException exc) {
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
		if (1 < args.length) {
			should_catch = 0 != Integer.parseInt(args[1]);
		}

		// Warm-Up:
		loop(1000);

		long time = loop(times);
		System.out.format("Run-Time (s): %.1f%n", time / 1_000_000_000.);
	}
}
