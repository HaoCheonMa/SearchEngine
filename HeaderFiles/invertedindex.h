#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <mutex>
#include <cctype>

/**
* ���������, ���������� ������ � ���������� ��������� ����� � ��������
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
	* �������� ��� ��������� ���� ����������, �� ������� ����� ���������
	�����
	* @param texts_input ���������� ����������
	*/
	static void updateDocumentBase(std::vector<std::string> inputDocs);
	/**
	* ����� ������������ ��������� �������
	* @return ���������� ��������� �������
	*/
	static const std::map<std::string, std::vector<Entry>>& getFreqDictionary() { return freqDictionary; }
	/**
	* ����� ���������� ���������� ��������� ����� word � ����������� ����
	����������
	* @param word �����, ������� ��������� �������� ���������� ����������
	* @return ���������� �������������� ������ � �������� ����
	*/
	static std::vector<Entry> getWordCount(const std::string& word);

private:
	static std::vector<std::string> docs; // ������ ����������� ����������
	static std::map<std::string, std::vector<Entry>> freqDictionary; // ��������� �������
};
