#include "searchserver.h"

static std::string NormalizeWord(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput) {
    auto& freqDictionary = InvertedIndex::getFreqDictionary();
    std::vector<std::vector<RelativeIndex>> docsRelevance;

    int maxResponses = ConverterJSON::getResponsesLimit();
    if (maxResponses <= 0)
        maxResponses = 5;

    for (const auto& request : queriesInput) {
        std::set<std::string> uniqueWords;
        std::stringstream ss(request);
        std::string word;
        while (ss >> word)
            uniqueWords.insert(NormalizeWord(word));

        std::map<size_t, int> docToAbsRelevance;
        for (auto& w : uniqueWords) {
            auto it = freqDictionary.find(w);
            if (it != freqDictionary.end()) {
                for (const auto& entry : it->second)
                    docToAbsRelevance[entry.docId] += static_cast<int>(entry.count);
            }
        }

        std::vector<RelativeIndex> ranking;
        if (docToAbsRelevance.empty()) {
            docsRelevance.emplace_back(std::move(ranking));
            continue;
        }

        int maxRel = 0;
        for (auto& [docId, rel] : docToAbsRelevance)
            if (rel > maxRel)
                maxRel = rel;

        for (auto& [docId, rel] : docToAbsRelevance) {
            ranking.push_back({ docId, static_cast<float>(rel) / maxRel });
        }

        std::sort(ranking.begin(), ranking.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return a.rank > b.rank;
            });

        if ((int)ranking.size() > maxResponses)
            ranking.resize(maxResponses);

        docsRelevance.push_back(std::move(ranking));
    }

    return docsRelevance;
}
