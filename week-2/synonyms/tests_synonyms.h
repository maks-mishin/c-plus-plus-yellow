// Author : Maks Mishin
// Date : 2/8/2022

#ifndef C_PLUS_PLUS_YELLOW_TESTS_SYNONYMS_H
#define C_PLUS_PLUS_YELLOW_TESTS_SYNONYMS_H

#include "synonyms.h"
#include "../unit_test_framework/unit_test_framework.h"

void TestAddSynonyms() {
    {
        Synonyms empty;
        AddSynonyms(empty, "a", "b");
        const Synonyms expected = {
                {"a", {"b"}},
                {"b", {"a"}}
        };
        AssertEqual(empty, expected, "Add to empty");
    }
    {
        Synonyms synonyms = {
                {"a", {"b"}},
                {"b", {"a", "c"}},
                {"c", {"b"}}
        };
        AddSynonyms(synonyms, "a", "c");
        Synonyms expected = {
                {"a", {"b", "c"}},
                {"b", {"a", "c"}},
                {"c", {"b", "a"}}
        };
        AssertEqual(synonyms, expected, "Add to synonyms");
    }
}

void TestCount() {
    {
        Synonyms empty;
        AssertEqual(GetSynonymsCount(empty, "a"), 0u, "count for empty");
    }
    {
        Synonyms synonyms = {
                {"a", {"b", "c"}},
                {"b", {"a"}},
                {"c", {"a"}}
        };
        AssertEqual(GetSynonymsCount(synonyms, "a"), 2u, "count for a");
        AssertEqual(GetSynonymsCount(synonyms, "b"), 1u, "count for b");
        AssertEqual(GetSynonymsCount(synonyms, "z"), 0u, "count for z");
    }
}

void TestAreSynonyms() {
    {
        Synonyms empty;
        Assert(!AreSynonyms(empty, "a", "b"), "empty a b");
        Assert(!AreSynonyms(empty, "a", "b"), "empty b a");
    }
    {
        Synonyms synonyms = {
                {"a", {"b", "c"}},
                {"b", {"a"}},
                {"c", {"a"}},
        };
        Assert(AreSynonyms(synonyms, "a", "b"), "");
        Assert(AreSynonyms(synonyms, "b", "a"), "");
        Assert(AreSynonyms(synonyms, "a", "c"), "");
        Assert(AreSynonyms(synonyms, "a", "b"), "");
        Assert(!AreSynonyms(synonyms, "b", "c"), "");
        Assert(!AreSynonyms(synonyms, "c", "b"), "");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestAreSynonyms, "TestAreSynonyms");
    tr.RunTest(TestCount, "TestCount");
    tr.RunTest(TestAddSynonyms, "TestAddSynonyms");
}

#endif //C_PLUS_PLUS_YELLOW_TESTS_SYNONYMS_H
