#include "searchengine.h"

std::string SearchEngine::name;
std::string SearchEngine::version;
bool SearchEngine::successStart;
const std::string SearchEngine::cmd = "search";

void SearchEngine::startSearch() {
	std::unique_ptr<SearchEngine> searchEngine = std::make_unique<SearchEngine>();
	std::unique_ptr<InvertedIndex> indexes = std::make_unique<InvertedIndex>();
	indexes->updateDocumentBase(ConverterJSON::getTextDocuments());
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

		if (inCmd == "stop") {
			std::cout << "**Exit**\n\n";
			return;
		}

		if (!SearchEngine::IsSuccessStart()) {
			std::cerr << "**Start error**\n\n";
			continue;
		}

		SearchServer searchServer(*indexes);
		auto docsRelevance = searchServer.search(ConverterJSON::getRequests());

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

		ConverterJSON::putAnswers(answers);
	}
}