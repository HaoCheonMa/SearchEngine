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
	* Метод получения содержащегося файла
	* @return Возвращает список с содержащими файлами перечисленных
	* в config.json
	*/
	static std::vector<std::string> getTextDocuments(); 
	/**
	* Метод считает поле max_responses для определения
	* предельного количества ответов на один запрос
	* @return
	*/
	static int getResponsesLimit();
	/**
	* Метод получения запросов из файла requests.json
	* @return возвращает список запросов из файла requests.json
	*/
	static std::vector<std::string> getRequests();
	/**
	* Положить в файл answers.json результаты поисковых запросов
	*/
	static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
	/**
	* Метод получения текста из JSON файлов
	* @param path принимает путь к файлу
	* @return возвращает информацию содержащуюся в JSON файле
	*/
	static nlohmann::json getJSONText(const std::string& path);
	static const std::string configPath; // путь к конфиг файлу

	static const std::string getName();
	static const std::string getVersion();

private:
	static const std::string requestsPath; // путь к файлу запросов
};
