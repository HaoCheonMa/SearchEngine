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
	* Конструктор проверяет успешность запуска
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
	* Метод возвращает результат
	* @return возвращает результат запуска
	*/
	static bool IsSuccessStart() { return successStart; }
	/**
	* Метод запускает движок
	*/
	static void startSearch();


private:
	static std::string name; // название движка
	static std::string version; // версия
	static int maxResponses; // кол-во ответов
	static bool successStart; // статус запуска
	const static std::string cmd; // переменная, принимающая ввод
};