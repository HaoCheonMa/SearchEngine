#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

class ConverterJSON {
public:
	ConverterJSON() = default;

	/**
	* ����� ��������� ����������� ������
	* @return ���������� ������ � ���������� ������ �������������
	* � config.json
	*/
	static std::vector<std::string> getTextDocuments(); 
	/**
	* ����� ��������� ���� max_responses ��� ����������� �����������
	* ���������� ������� �� ���� ������
	* @return
	*/
	static int getResponsesLimit();
	/**
	* ����� ��������� �������� �� ����� requests.json
	* @return ���������� ������ �������� �� ����� requests.json
	*/
	static std::vector<std::string> getRequests();
	/**
	* �������� � ���� answers.json ���������� ��������� ��������
	*/
	static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
	/**
	* ����� ��������� ������ �� JSON ������
	* @param path ��������� ���� � �����
	* @return ���������� ���������� ������������ � JSON �����
	*/
	static nlohmann::json getJSONText(const std::string& path);
	static const std::string configPath; // ���� � ������ �����

private:
	static const std::string requestsPath; // ���� � ����� ��������
};
