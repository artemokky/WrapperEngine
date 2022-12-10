#include <iostream>
#include "wrapper.h"
#include "engine.h"

class TestPow {
public:
	int Pow(int x, int n) {
		if (n == 0) return 1;
		if (n == 1) return x;

		int ans = Pow(x, n / 2);

		if (n & 1) {
			return x * ans * ans;
		}

		return ans * ans;
	}
};

class TestMax {
public:
	int Max(int a, int b, int c) {
		auto max = a > b ? (a > c ? a : c) : (b > c ? b : c);
		return max;
	}
};

class TestCountOnes {
public:
	int OnesOf(int a) {
		int ones = 0;
		for (int n = a; n; n >>= 1)
			ones += n & 1;
		return ones;
	}
};

int main(void) {
	TestPow test1;
	TestMax test2;
	TestCountOnes test3;

	Engine engine;

	try {
		Wrapper wrapper1(&test1, &TestPow::Pow, { {"arg1", 0}, {"arg2", 0} });
		engine.registerCommand(&wrapper1, "command1");
		auto res1 = engine.execute("command1", {{"arg1", 17}, {"arg2", 2}});
		std::cout << "17^2 = " << res1 << std::endl;
	}
	catch (std::exception e) {

		std::cout << "test1 " << e.what() << std::endl;
	}

	try {
		Wrapper wrapper2(&test2, &TestMax::Max, { {"arg1", 0}, {"arg2", 0}, {"arg3", 0} });
		engine.registerCommand(&wrapper2, "command2");
		auto res2 = engine.execute("command2", { {"arg1", 17}, {"arg2", 17}, {"arg3", 34} });
		std::cout << "max(17, 17, 34) = " << res2 << std::endl;
	}
	catch (std::exception e) {
		std::cout << "test2 " << e.what() << std::endl;
	}

	try {
		Wrapper wrapper3(&test3, &TestCountOnes::OnesOf, { {"arg1", 0} });
		engine.registerCommand(&wrapper3, "command3");
		auto res3 = engine.execute("command3", { {"arg1", 29} });
		std::cout << "29_10 = 11101_2, count of ones = " << res3 << std::endl;
	}
	catch (std::exception e) {
		std::cout << "test3 " << e.what() << std::endl;
	}
	
	return 0;
}