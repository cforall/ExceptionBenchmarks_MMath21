// Throw Across Destructor
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct EmptyException : public std::exception {};

struct WithDestructor {
	~WithDestructor() {
		asm volatile ("# destructor body");
	}
};

void unwind_destructor(unsigned int frames) {
	if (frames) {
		WithDestructor object;
		unwind_destructor(frames - 1);
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
	for (int count = 0 ; count < times ; ++count) {
		try {
			unwind_destructor(total_frames);
		} catch (EmptyException &) {
			asm volatile ("# catch block");
		}
	}
	time_point<steady_clock> end_time = steady_clock::now();
	nanoseconds duration = duration_cast<nanoseconds>(end_time - start_time);
	cout << "Run-Time (s): " << fixed << setprecision(1) << duration.count() / 1'000'000'000. << endl;
}
