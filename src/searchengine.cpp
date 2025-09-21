#include "searchengine.h"

std::string SearchEngine::name;
std::string SearchEngine::version;
bool SearchEngine::successStart;

void SearchEngine::startSearch() {
	std::unique_ptr<SearchEngine> searchEngine = std::make_unique<SearchEngine>();
	std::unique_ptr<InvertedIndex> indexes = std::make_unique<InvertedIndex>();
	indexes->updateDocumentBase(ConverterJSON::getTextDocuments());

	if (!SearchEngine::IsSuccessStart()) {
		std::cerr << "**Start error**\n\n";
		return;
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
