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
	static std::vector<std::string> GetTextDocuments(); 
	/**
	* Ìåòîä ñ÷èòûâàåò ïîëå max_responses äëÿ îïðåäåëåíèÿ ïðåäåëüíîãî
	* êîëè÷åñòâà îòâåòîâ íà îäèí çàïðîñ
	* @return
	*/
	static int GetResponsesLimit();
	/**
	* Ìåòîä ïîëó÷åíèÿ çàïðîñîâ èç ôàéëà requests.json
	* @return âîçâðàùàåò ñïèñîê çàïðîñîâ èç ôàéëà requests.json
	*/
	static std::vector<std::string> GetRequests();
	/**
	* Ïîëîæèòü â ôàéë answers.json ðåçóëüòàòû ïîèñêîâûõ çàïðîñîâ
	*/
	static void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

	static nlohmann::json GetJSONText(const std::string& path);
	static const std::string configPath;

private:
	static const std::string requestsPath;
	static const std::string answersPath;
};
