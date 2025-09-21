#include "searchengine.h"
#include "converterjson.h"

int main() { 
  SearchEngine::startSearch(); 
  std::cout << converter.getName() << "[" << converter.getVersion() << "] finish job\n";
}
