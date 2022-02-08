// Author : Maks Mishin
// Date 2/8/2022

#ifndef C_PLUS_PLUS_YELLOW_SYNONYMS_H
#define C_PLUS_PLUS_YELLOW_SYNONYMS_H

#include <string>
#include <map>
#include <set>

using Synonyms = std::map<std::string, std::set<std::string>>;

void AddSynonyms(Synonyms& synonyms, const std::string& first_word,
                 const std::string& second_word) {
    synonyms[first_word].insert(second_word);
    synonyms[second_word].insert(first_word);
}

size_t GetSynonymsCount(Synonyms& synonyms,
                        const std::string& word) {
    return synonyms[word].size();
}

bool AreSynonyms(Synonyms& synonyms, const std::string& first_word,
                 const std::string& second_word) {
    return synonyms[first_word].count(second_word) == 1;
}

#endif //C_PLUS_PLUS_YELLOW_SYNONYMS_H
