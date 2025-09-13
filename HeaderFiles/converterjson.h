#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class ConverterJSON {
public:
	ConverterJSON() = default;
	/**
	* ����� ��������� ����������� ������
	* @return ���������� ������ � ���������� ������ �������������
	* � config.json
	*/
	static std::vector<std::string> GetTextDocuments(); 
	/**
	* ����� ��������� ���� max_responses ��� ����������� �����������
	* ���������� ������� �� ���� ������
	* @return
	*/
	static int GetResponsesLimit();
	/**
	* ����� ��������� �������� �� ����� requests.json
	* @return ���������� ������ �������� �� ����� requests.json
	*/
	static std::vector<std::string> GetRequests();
	/**
	* �������� � ���� answers.json ���������� ��������� ��������
	*/
	static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

	static nlohmann::json GetJSONText(const std::string& path);
	static const std::string configPath;

private:
	static const std::string requestsPath;
	static const std::string answersPath;
};