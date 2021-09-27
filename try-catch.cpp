// Cross a Try Statement with a Termination Handler
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct NotRaisedException : public std::exception {};

int main(int argc, char * argv[]) {
	unsigned int times = 1;
	volatile bool should_throw = false;
	if (1 < argc) {
		times = strtol(argv[1], nullptr, 10);
	}

	time_point<steady_clock> start_time = steady_clock::now();
	for (unsigned int count = 0 ; count < times ; ++count) {
		try {
			asm volatile ("# try block");
			if (should_throw) {
				throw NotRaisedException();
			}
		} catch (NotRaisedException &) {
			asm volatile ("# catch block");
		}
	}
	time_point<steady_clock> end_time = steady_clock::now();
	nanoseconds duration = duration_cast<nanoseconds>(end_time - start_time);
	cout << "Run-Time (s): " << fixed << setprecision(1) << duration.count() / 1'000'000'000. << endl;
}
