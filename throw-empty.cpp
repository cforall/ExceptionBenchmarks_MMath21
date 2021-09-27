// Throw Across Empty Function
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct EmptyException : public std::exception {};

void unwind_empty(unsigned int frames) {
	if (frames) {
		unwind_empty(frames - 1);
		if (-1 == frames) printf("~");
	} else {
		throw (EmptyException){};
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

	time_point<steady_clock> start_time = steady_clock::now();
	for (unsigned int count = 0 ; count < times ; ++count) {
		try {
			unwind_empty(total_frames);
		} catch (EmptyException &) {
			asm volatile ("# catch block");
		}
	}
	time_point<steady_clock> end_time = steady_clock::now();
	nanoseconds duration = duration_cast<nanoseconds>(end_time - start_time);
	cout << "Run-Time (s): " << fixed << setprecision(1) << duration.count() / 1'000'000'000. << endl;
}
