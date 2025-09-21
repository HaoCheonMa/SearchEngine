#pragma once

#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include <cctype>
#include "invertedindex.h"
#include "converterjson.h"

/**
* Структура, содержащая данные релевантности ответа
*/
struct RelativeIndex {
	size_t docId;
	float rank;
	bool operator ==(const RelativeIndex& other) const {
		return (docId == other.docId && rank == other.rank);
	}
};
class SearchServer {
public:
	/**
	* @param idx в конструктор класса передаётся ссылка на класс
	InvertedIndex,
	* чтобы SearchServer мог узнать частоту слов встречаемых в
	запросе
	*/
	SearchServer(InvertedIndex& idx) : index(idx) {};
	/**
	* Метод обработки поисковых запросов
	* @param queries_input поисковые запросы взятые из файла
	requests.json
	* @return возвращает отсортированный список релевантных ответов для
	заданных запросов
	*/
	std::vector<std::vector<RelativeIndex>> search(const
		std::vector<std::string>& queriesInput);
private:
	InvertedIndex index;
};