#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>
#include <memory>
#include "converterjson.h"
#include "invertedindex.h"
#include "searchserver.h"

class SearchEngine {
public:
	/**
	* ����������� ��������� ���������� �������
	*/
	SearchEngine() {
		nlohmann::json config = ConverterJSON::getJSONText(ConverterJSON::configPath);
		if (!config.contains("config") || !config["config"].contains("name") || !config["config"].contains("version")
			|| !config["config"].contains("max_responses")) {
			std::cerr << "**Invalid config file**\n\n";
			successStart = false;
		}

		name = config["config"]["name"];
		version = config["config"]["version"];
		if (name.empty()) successStart = false;

		else if (version.empty()) successStart = false;

		else if (config["config"]["max_responses"] <= 0) successStart = false;

		else if (config["files"].empty()) successStart = false;

		else
			successStart = true;

	}

	/**
	* ����� ���������� ���������
	* @return ���������� ��������� �������
	*/
	static bool IsSuccessStart() { return successStart; }
	/**
	* ����� ��������� ������
	*/
	static void startSearch();


private:
	static std::string name; // �������� ������
	static std::string version; // ������
	static int maxResponses; // ���-�� �������
	static bool successStart; // ������ �������
	const static std::string cmd; // ����������, ����������� ����
};