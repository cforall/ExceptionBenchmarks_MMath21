// Resume Across Fixup
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iomanip>
#include <functional>

using namespace std;
using namespace chrono;

void nounwind_fixup(unsigned int frames, function<void (int &)> raised_rtn ) {
	if (frames) {
		nounwind_fixup(frames - 1, raised_rtn);
	} else {
		int fixup = 17;
		raised_rtn(fixup);
	}
}

int main(int argc, char * argv[]) {
	unsigned int times = 1;
	unsigned int total_frames = 1;
	if (1 < argc) {
		times = strtol(argv[1], nullptr, 10);
	}
	if (2 < argc) {
		total_frames = strtol(argv[2], nullptr, 10);
	}

	auto raised = [=] (int & fixup) -> void {
					  fixup = total_frames + 42;		// use local scope => lexical link
				  };
	time_point<steady_clock> start_time = steady_clock::now();
	for (unsigned int count = 0 ; count < times ; ++count) {
		nounwind_fixup(total_frames, raised);
	}
	time_point<steady_clock> end_time = steady_clock::now();
	nanoseconds duration = duration_cast<nanoseconds>(end_time - start_time);
	cout << "Run-Time (s): " << fixed << setprecision(1) << duration.count() / 1'000'000'000. << endl;
}
