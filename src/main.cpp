#include <iostream>
#include "config.h"

int main() {
	try {
		auto config = get_config::Config();
		config.load_config("../examples/config.ini");

		long double a = config.get<double>("A");
		long double b = config.get<double>("B");
		long double h = config.get<double>("H");

		std::cout << "[]\n";
		std::cout << "TASK_NAME = " << config["TASK_NAME"] << '\n';
		std::cout << "TASK_DESCRIPTION = " << config["TASK_DESCRIPTION"] << '\n';
		std::cout << "A = " << a << '\n';
		std::cout << "B = " << b << '\n';
		std::cout << "H = " << h << '\n';


		bool use_omp = config.get<bool>("SEIDEL", "USE_OMP");
		long double tolerance = config.get<double>("SEIDEL", "TOLERANCE");
		size_t max_iter = config.get<size_t>("SEIDEL", "MAX_ITERATIONS");

		std::cout << "[SEIDEL]\n";
		std::cout << "USE_OMP = " << use_omp << '\n';
		std::cout << "TOLERANCE = " << tolerance << '\n';
		std::cout << "MAX_ITERATIONS = " << max_iter << '\n';

		use_omp = config.get<bool>("POWER", "USE_OMP");
		tolerance = config.get<double>("POWER", "TOLERANCE");
		max_iter = config.get<size_t>("POWER", "MAX_ITERATIONS");

		std::cout << "[POWER]\n";
		std::cout << "USE_OMP = " << use_omp << '\n';
		std::cout << "TOLERANCE = " << tolerance << '\n';
		std::cout << "MAX_ITERATIONS = " << max_iter << '\n';
	}
	catch (std::exception e) {
		std::cerr << e.what();
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unexpected error";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}