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
	* Ìåòîä ïîëó÷åíèÿ ñîäåðæèìîãî ôàéëîâ
	* @return Âîçâðàùàåò ñïèñîê ñ ñîäåðæèìûì ôàéëîâ ïåðå÷èñëåííûõ
	* â config.json
	*/
	static std::vector<std::string> getTextDocuments(); 
	/**
	* Ìåòîä ñ÷èòûâàåò ïîëå max_responses äëÿ îïðåäåëåíèÿ ïðåäåëüíîãî
	* êîëè÷åñòâà îòâåòîâ íà îäèí çàïðîñ
	* @return
	*/
	static int getResponsesLimit();
	/**
	* Ìåòîä ïîëó÷åíèÿ çàïðîñîâ èç ôàéëà requests.json
	* @return âîçâðàùàåò ñïèñîê çàïðîñîâ èç ôàéëà requests.json
	*/
	static std::vector<std::string> getRequests();
	/**
	* Ïîëîæèòü â ôàéë answers.json ðåçóëüòàòû ïîèñêîâûõ çàïðîñîâ
	*/
	static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);
	/**
	* Ìåòîä ïîëó÷åíèÿ òåêñòà èç JSON ôàéëîâ
	* @param path ïðèíèìàåò ïóòü ê ôàéëó
	* @return âîçâðàùàåò èíôîðìàöèþ ñîäåðæàùóþñÿ â JSON ôàéëå
	*/
	static nlohmann::json getJSONText(const std::string& path);
	static const std::string configPath; // ïóòü ê êîíôèã ôàéëó

	static const std::string getName();
	static const std::string getVersion();

private:
	static const std::string requestsPath; // ïóòü ê ôàéëó çàïðîñîâ
};
