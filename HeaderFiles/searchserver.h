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
* ���������, ���������� ������ ������������� ������
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
	* @param idx � ����������� ������ ��������� ������ �� �����
	InvertedIndex,
	* ����� SearchServer ��� ������ ������� ���� ����������� �
	�������
	*/
	SearchServer(InvertedIndex& idx) : index(idx) {};
	/**
	* ����� ��������� ��������� ��������
	* @param queries_input ��������� ������� ������ �� �����
	requests.json
	* @return ���������� ��������������� ������ ����������� ������� ���
	�������� ��������
	*/
	std::vector<std::vector<RelativeIndex>> search(const
		std::vector<std::string>& queriesInput);
private:
	InvertedIndex index;
};