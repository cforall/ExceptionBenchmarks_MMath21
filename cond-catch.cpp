// Conditional Match (or Re-Raise)
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct EmptyException : public std::exception {};

bool should_catch = false;

int main(int argc, char * argv[]) {
	unsigned int times = 1;
	if (1 < argc) {
		times = strtol(argv[1], nullptr, 10);
	}
	if (2 < argc) {
		should_catch = strtol(argv[2], nullptr, 10);
	}

	time_point<steady_clock> start_time = steady_clock::now();
    for (unsigned int count = 0 ; count < times ; ++count) {
        try {
			try {
				throw EmptyException();
			} catch (EmptyException & exc) {
				if (!should_catch) {
					throw;
				}
				asm volatile ("# catch block (conditional)");
			}
		} catch (EmptyException &) {
			asm volatile ("# catch block (unconditional)");
		}
    }
	time_point<steady_clock> end_time = steady_clock::now();
	nanoseconds duration = duration_cast<nanoseconds>(end_time - start_time);
	cout << "Run-Time (s): " << fixed << setprecision(1) << duration.count() / 1'000'000'000. << endl;
}
