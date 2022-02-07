// Author : Maks Mishin
// Date : 2/7/2022.

#include "UnitTestFramework.h"
#include <string>

bool IsPalindrom(const std::string& s);

void TestPalindrom() {
    Assert(IsPalindrom(""), "test empty string");
    Assert(IsPalindrom("a"), "test one char");
    Assert(IsPalindrom("madam"), "test madam");
    Assert(IsPalindrom("level"), "test level");
    Assert(IsPalindrom("wasitacaroracatisaw"), "test wasitacaroracatisaw");

    Assert(!IsPalindrom("asjdk;k"), "test no asjdk;k");
    Assert(!IsPalindrom("981723971"), "test no 981723971");
    Assert(!IsPalindrom("aaaAAA"), "test no aaaAAA");
    Assert(!IsPalindrom("wasitacaroracatisa"), "test pass last symbol");
    Assert(!IsPalindrom("asitacaroracatisaw"), "test pass first symbol");
    Assert(!IsPalindrom("wasitacaroracatis"), "test pass 2 last symbols");
    Assert(!IsPalindrom("sitacaroracatisaw"), "test pass 2 first symbols");
    Assert(!IsPalindrom("mad\tam"), "test tab symbol");
    Assert(!IsPalindrom("m adam"), "test space symbol");
    Assert(IsPalindrom("\n\t  \t\n"), "test space symbols");
    Assert(!IsPalindrom("madAm"), "test mid string 1");
    Assert(!IsPalindrom("madaM"), "test mid string 2");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestPalindrom, "TestPalindrom");
    return 0;
}

