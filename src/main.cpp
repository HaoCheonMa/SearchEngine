#include "searchengine.h"

int main() { 
  SearchEngine::startSearch(); 
  std::cout << SearchEngine::name << "[" << SearchEngine::version << "] finish job\n";
}
