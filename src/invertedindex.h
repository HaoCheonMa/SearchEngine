#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <mutex>
#include <cctype>

/**
* Структура, содержащая данные о количестве входждений слова в документ
*/
struct Entry {
	size_t docId = 0, count = 0;
	bool operator==(const Entry& other) const {
		return docId == other.docId && count == other.count;
	}
};

class InvertedIndex {
public:
	InvertedIndex() = default;
	/**
	* Обновить или заполнить базу документов, по которой будем совершать
	* поиск
	* @param texts_input содержащее документы
	*/
	static void updateDocumentBase(std::vector<std::string> inputDocs);
	/**
	* Метод возвращающий частотный словарь
	* @return возвращает частотный словарь
	*/
	static const std::map<std::string, std::vector<Entry>>& getFreqDictionary() { return freqDictionary; }
	/**
	* Метод определяет количество входждений слова word в загруженной базе
	* документов
	* @param word слово, частоту входждений которого необходимо определить
	* @return возвращает подготовленный список с частотой слов
	*/
	static std::vector<Entry> getWordCount(const std::string& word);

private:
	static std::vector<std::string> docs; // список содержащего документов
	static std::map<std::string, std::vector<Entry>> freqDictionary; // частотный словарь
};
