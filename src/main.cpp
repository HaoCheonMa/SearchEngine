#include "searchengine.h"
#include "converterjson.h"

int main() { 
  SearchEngine::startSearch(); 
  std::cout << ConverterJSON::getName() << "[" << ConverterJSON::getVersion() << "] finish job\n";
}
