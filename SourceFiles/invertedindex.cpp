#include "invertedindex.h"
std::mutex mtx;
std::vector<std::string> InvertedIndex::docs;
std::map<std::string, std::vector<Entry>> InvertedIndex::freqDictionary;

static std::string NormalizeWord(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs) {
    docs = std::move(inputDocs);
    freqDictionary.clear();

    std::vector<std::thread> threads;
    std::vector<std::map<std::string, size_t>> wordCountPerDoc(docs.size());

    for (size_t docId = 0; docId < docs.size(); ++docId) {
        threads.emplace_back([docId, &wordCountPerDoc]() {
            std::stringstream ss(docs[docId]);
            std::string word;
            std::map<std::string, size_t> localCount;
            while (ss >> word) {
                std::string lowered = NormalizeWord(word);
                ++localCount[lowered];
            }
            wordCountPerDoc[docId] = std::move(localCount);
            });
    }

    for (auto& t : threads) {
        t.join();
    }

    std::lock_guard<std::mutex> lock(mtx);
    for (size_t docId = 0; docId < wordCountPerDoc.size(); ++docId) {
        for (const auto& [word, count] : wordCountPerDoc[docId]) {
            freqDictionary[word].push_back({ docId, count });
        }
    }
}


std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::string wordLower = NormalizeWord(word);
    if (freqDictionary.count(wordLower))
        return freqDictionary[wordLower];
    else
        return {};
}

