#include "converterjson.h"

const std::string ConverterJSON::configPath = "config/config.json";
const std::string ConverterJSON::requestsPath = "config/requests.json";

nlohmann::json ConverterJSON::getJSONText(const std::string & path) {
	std::ifstream configFile(path);
	nlohmann::json configText;
	if (configFile.is_open()) {
		configFile >> configText;
		configFile.close();
	}
	else
		std::cerr << "**Invalid file path**\n\n";
	return configText;
}

const std::string getName(){
	nlohmann::json config = getJSONText(configPath);
	std::string name = confi["config"]["name"];
	return name;
}

const std::string getVersion(){
	nlohmann::json config = getJSONText(configPath);
	std::string version = confi["config"]["version"];
	return version;
}

static std::string normalizeWord(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

std::vector<std::string> ConverterJSON::getTextDocuments() {
	std::vector<std::string> fileContent;
	const std::string filesKey = "files";
	std::vector<std::string> filePaths;
	nlohmann::json configText = getJSONText(configPath);
	if (configText.contains(filesKey)) {
		filePaths = configText[filesKey].get<std::vector<std::string>>();
	}
	else {
		std::cerr << "**Empty files list**\n\n";
		return filePaths;;
	}

	for (auto& path : filePaths) {
		std::ifstream fileText(path);
		std::stringstream buffer;
		buffer << fileText.rdbuf();
		fileContent.push_back(buffer.str());
	}
	
	return fileContent;
}

int ConverterJSON::getResponsesLimit(){
	nlohmann::json configText = getJSONText(configPath);
	int responsesLimit = 0;
	if (!configText.contains("config") || !configText["config"].contains("max_responses")) {
		std::cerr << "**Not found responses limit**\n\n";
		return -1;
	}
	responsesLimit = configText["config"]["max_responses"];

	if (responsesLimit <= 0) {
		std::cerr << "**Invalid responses value**\n\n";
		return -1;
	}

	return responsesLimit;
}

std::vector<std::string> ConverterJSON::getRequests() {
	nlohmann::json requestsText = getJSONText(requestsPath);
	std::vector<std::string> requests;
	if (!requestsText.contains("requests")) {
		std::cerr << "**Invalid file content**\n\n";
		return requests;
	}
	
	if (!requestsText.empty())
		return requests = requestsText["requests"].get<std::vector<std::string>>();
	else {
		std::cerr << "**Empty requests**\n\n";
		return requests;
	}
}

void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>> answers) {
	nlohmann::json root = nlohmann::json::object();
	nlohmann::json answersJSON = nlohmann::json::object();

	for (size_t i = 0; i < answers.size(); ++i) {
		int reqNum = static_cast<int>(i) + 1;
		std::string requestId = std::string("request") +
			(reqNum < 10 ? "00" : (reqNum < 100 ? "0" : "")) +
			std::to_string(reqNum);
		const auto& docs = answers[i];
		if (docs.empty()) {
			answersJSON[requestId]["result"] = "false";
		}
		else if (docs.size() == 1) {
			answersJSON[requestId]["result"] = "true";
			answersJSON[requestId]["docid"] = docs[0].first;
			double roundedRank = std::round(docs[0].second * 1000.0) / 1000.0;
			answersJSON[requestId]["rank"] = roundedRank;
		}
		else {
			answersJSON[requestId]["result"] = "true";
			nlohmann::json relevance_array = nlohmann::json::array();
			for (const auto& [docid, rank] : docs) {
				nlohmann::json doc_json;
				doc_json["docid"] = docid;
				double roundedRank = std::round(rank * 1000.0) / 1000.0;
				doc_json["rank"] = roundedRank;
				relevance_array.push_back(doc_json);
			}
			answersJSON[requestId]["relevance"] = relevance_array;
		}
	}
	root["answers"] = answersJSON;
	std::ofstream ofs("config/answers.json");
	if (!ofs.is_open()) {
		std::cerr << "Cannot open answers.json for writing" << std::endl;
		return;
	}
	ofs << std::setw(4) << root << std::endl;
	std::cout << "\n**Success**\n\n";
}



