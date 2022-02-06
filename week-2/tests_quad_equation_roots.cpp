// Author : Maks Mishin
// Date : 2/6/2022.

#include "UnitTestFramework.h"
#include <random>

// test implementation of tested function
int GetDistinctRealRootCount(double a, double b, double c) {
    if (a == 0) {
        if (b != 0) {
            return 1;
        }
        return 0;
    }
    int D = b * b - 4 * a * c;
    if (D > 0) {
        return 2;
    }
    if (D == 0) {
        return 1;
    }
    return 0;
}

void TestRoots() {
    mt19937 gen;
    uniform_real_distribution<> distribution(-10, 10);

    for (int i = 0; i < 100; ++i) {
        const auto a = distribution(gen);
        const auto b = distribution(gen);
        const auto c = distribution(gen);

        const auto count = GetDistinctRealRootCount(a, b, c);

        Assert(count >= 0 && count <= 2, "Quadratic equation has only 0, 1 or 2 real roots");
    }
}

void TestNoRoots() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "x^2 + 1 has one root");
    AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0, "x^2+3x+4 = 0 has 0 real roots.");
    AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0, "x^2-2x+10 = 0 has 0 real roots.");
}

void TestOneRoot() {
    mt19937 gen;
    uniform_real_distribution<> distribution(-10, 10);

    for (auto i = 0; i < 100; ++i) {
        const auto x_1 = distribution(gen);

        const auto p = x_1 + x_1;
        const auto q = x_1 * x_1;

        const auto count = GetDistinctRealRootCount(1, p, q);
        stringstream description;
        description << showpos << "x^2" << p << "x" << q
                    << " = 0 has 1 real root.";

        AssertEqual(count, 1, description.str());
    }
}

void TestLinearEquation() {
    AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1, "2x+1=0 has one root");
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "x = 0 has one root");
    AssertEqual(GetDistinctRealRootCount(0, 123, -5434), 1, "123x - 5434 = 0 has one root");
}

void TestConstants() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "1 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, -123), 0, "-123 = 0 has 0 real roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1723517235), 0, "1723517235 = 0 has 0 real roots");

}

int main() {
    TestRunner runner;
    runner.RunTest(TestRoots, "TestRoots");
    runner.RunTest(TestOneRoot, "TestOneRoot");
    runner.RunTest(TestNoRoots, "TestNoRoots");
    runner.RunTest(TestLinearEquation, "TestLinearEquation");
    runner.RunTest(TestConstants, "TestConstants");
    return 0;
}