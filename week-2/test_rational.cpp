// Author : Maks Mishin
// Date : 2/7/2022.

#include "UnitTestFramework.h"

class Rational {
public:
    Rational();
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;
};

void AssertRational(const Rational& submitted, const pair<int, int>& correct, const string& message) {
    AssertEqual(pair<int, int>(submitted.Numerator(), submitted.Denominator()), correct, message);
}

const auto p = [](int numerator, int denominator){
    return pair<int, int>(numerator, denominator);
};

void TestPredefined() {
    AssertRational(Rational(1, 1), p(1, 1), "Canonical form of 1/1 is 1/1");
    AssertRational(Rational(3, 5), p(3, 5), "Canonical form of 3/5 is 3/5");
    AssertRational(Rational(2147483647, 2147483647), p(1, 1), "Canonical form of 2147483647/2147483647 is 1/1");
    AssertRational(Rational(-5, 4), p(-5, 4), "Canonical form of -5/4 is -5/4");
    AssertRational(Rational(5, -4), p(-5, 4), "Canonical form of 5/-4 is -5/4");
    AssertRational(Rational(-6, -2), p(3, 1), "Canonical form of -6/-2 is 3/1");
    AssertRational(Rational(21, 56), p(3, 8), "Canonical form of 21/56 is 3/8");
    AssertRational(Rational(0, 100), p(0, 1), "Canonical form of 0/100 is 0/1");
    AssertRational(Rational(), p(0, 1), "Canonical form of default constructed is 0/1");
}

void TestConstructor() {
    Rational rational;
    AssertEqual(rational.Numerator(), 0, "test default numerator");
    AssertEqual(rational.Denominator(), 1, "test default denominator");

    Rational rational1(1, 5);
    AssertEqual(rational1.Numerator(), 1, "test numerator");
    AssertEqual(rational1.Denominator(), 5, "test denominator");
}

void TestReduction() {
    {
        Rational rational(2, 2);
        AssertEqual(rational.Numerator(), 1, "test numerator 2 2");
        AssertEqual(rational.Denominator(), 1, "test denominator 2 2");
    }
    {
        Rational rational(7, 14);
        AssertEqual(rational.Numerator(), 1, "test numerator 7 14");
        AssertEqual(rational.Denominator(), 2, "test denominator 7 14");
    }
    {
        Rational rational(11, 44);
        AssertEqual(rational.Numerator(), 1, "test numerator 11 44");
        AssertEqual(rational.Denominator(), 4, "test denominator 11 44");
    }
}

void TestNegative() {
    {
        Rational rational(2, -7);
        Assert(rational.Numerator() < 0, "TestNegative p>0");
        Assert(rational.Denominator() > 0, "TestNegative q<0");
    }
    {
        Rational rational(-1276, 1231);
        Assert(rational.Numerator() < 0, "TestNegative p<0");
        Assert(rational.Denominator() > 0, "TestNegative q>0");
    }
}

void TestPositive() {
    {
        Rational rational(16523, 12371);
        Assert(rational.Numerator() > 0, "TestPositive p>0");
        Assert(rational.Denominator() > 0, "TestPositive q>0");
    }
    {
        Rational rational(-123123, -123654);
        Assert(rational.Numerator() > 0, "TestPositive p<0");
        Assert(rational.Denominator() > 0, "TestPositive q<0");
    }
}

void TestDenominator() {
    {
        Rational rational(0, 12371);
        AssertEqual(rational.Denominator(), 1, "test denominator 1");
    }
}

int main() {
    TestRunner runner;
    runner.RunTest(TestPredefined, "TestPredefined");
    runner.RunTest(TestConstructor, "TestConstructor");
    runner.RunTest(TestReduction, "TestReduction");
    runner.RunTest(TestNegative, "TestNegative");
    runner.RunTest(TestPositive, "TestPositive");
    runner.RunTest(TestDenominator, "TestDenominator");
    return 0;
}

