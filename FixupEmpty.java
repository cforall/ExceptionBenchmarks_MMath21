public class FixupEmpty {
	public interface Fixup {
		public int op(int fixup);
	}

	static void nounwind_fixup(int frames, Fixup raised_rtn) {
		if (0 < frames) {
			nounwind_fixup(frames - 1, raised_rtn);
		} else {
			int fixup = frames;
			fixup = raised_rtn.op(fixup);
		}
	}

	private static long loop(int times, int total_frames) {
		Fixup raised = (int fixup) -> total_frames + 42; // use local scope => lexical link

		long startTime = System.nanoTime();
		for (int count = 0 ; count < times ; ++count) {
			nounwind_fixup(total_frames, raised);
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
