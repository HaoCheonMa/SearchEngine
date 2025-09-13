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
	SearchEngine() {
		nlohmann::json config = ConverterJSON::GetJSONText(ConverterJSON::configPath);
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

	static bool IsSuccessStart() { return successStart; }


private:
	static std::string name;
	static std::string version;
	static int maxResponses;
	static bool successStart;
	const static std::string cmd;
};

std::string SearchEngine::name;
std::string SearchEngine::version;
bool SearchEngine::successStart;
const std::string SearchEngine::cmd = "search";

int main() {
	
	std::unique_ptr<SearchEngine> searchEngine = std::make_unique<SearchEngine>();
	std::unique_ptr<InvertedIndex> indexes = std::make_unique<InvertedIndex>();
	indexes->UpdateDocumentBase(ConverterJSON::GetTextDocuments());
	std::string inCmd;

	while (true) {
		std::cout << "Enter command: ";
		std::getline(std::cin, inCmd);
		if (inCmd.empty()) continue;

		{
			std::stringstream cmdStr(inCmd);
			cmdStr >> inCmd;
			cmdStr.clear();
		}

		if (inCmd != "search" && inCmd != "stop") {
			std::cerr << "**Unknown command**\n\n";
			continue;
		}

		if (inCmd == "stop"){
			std::cout << "**Exit**\n\n";
			return 1;
		}

		if (!SearchEngine::IsSuccessStart()) {
			std::cerr << "**Start error**\n\n";
			continue;
		}

		SearchServer searchServer(*indexes);
		auto docsRelevance = searchServer.search(ConverterJSON::GetRequests());

		std::vector<std::vector<std::pair<int, float>>> answers;
		answers.reserve(docsRelevance.size());
		for (const auto& docList : docsRelevance) {
			std::vector<std::pair<int, float>> converted;
			converted.reserve(docList.size());
			for (const auto& rel : docList) {
				converted.emplace_back((int)(rel.docId), rel.rank);
			}
			answers.push_back(std::move(converted));
		}

		// Çàïèñûâàåì answers â JSON
		ConverterJSON::putAnswers(answers);
	}
}
