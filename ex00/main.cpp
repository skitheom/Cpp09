

#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <string>

void printDebugMsg(const std::string &msg) {
#ifdef DISPLAY_DEBUG_MSG
  std::cerr << "[Debug] " << msg << std::endl;
#endif
  (void)msg;
}

void printError(const std::string &msg) {
  std::cerr << "Error: " << msg << std::endl;
}

int main(int argc, const char *argv[]) {

  BitcoinExchange tmp; // 後でdata.csvを読み込むように初期化プロセスを修正

  if (argc != 0) {
    for (int i = 0; i < argc; ++i) {
      std::cout << "argv[" << i << "]: " << argv[i] << std::endl;
    }
  }
  if (argc != 2) {
    printError("could not open file.");
  }
  std::ifstream inFile(argv[1], std::ios::in);
  if (!inFile.is_open()) {
    printError("Failed to open input file");
    return EXIT_FAILURE;
  }

  printDebugMsg("File OK");

  std::string line;

  while (std::getline(inFile, line)) {
    std::cout << "Line: " << line << std::endl;
    // BitcoinExchangeクラスを使ってline に対する処理をする
  }
  inFile.close();
  return 0;
}

/*

TODO LIST:

- data.csvファイルを読み込めるようにする

 */
