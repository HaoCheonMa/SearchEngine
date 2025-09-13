#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <mutex>
#include <cctype>

struct Entry {
	size_t docId = 0, count = 0;
	bool operator==(const Entry& other) const {
		return docId == other.docId && count == other.count;
	}
};

class InvertedIndex {
public:
	InvertedIndex() = default;

	//Îáíîâëåíèå ñëîâàðÿ è ñïèñêà äîêóìåíòîâ
	static void UpdateDocumentBase(std::vector<std::string> inputDocs);
	static const std::map<std::string, std::vector<Entry>>& GetFreqDictionary() { return freqDictionary; }
	static std::vector<Entry> GetWordCount(const std::string& word);

private:
	static std::vector<std::string> docs; //ñïèñîê äîêóìåíòîâ
	static std::map<std::string, std::vector<Entry>> freqDictionary; //÷àñòîòíûé ñëîâàðü
};
