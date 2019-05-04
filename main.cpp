#include <iostream>
#include <filesystem>
#include <vector>
#include <string_view>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "index.h"
#include "manager.h"
using namespace std;
namespace fs=filesystem;


void foo() {
	cout << "byrik lox ";
	return;
	cout << "pidr";
}

/*
name.exe -i folder -f -r
name.exe -i folder -s word -r(nonr -  deafault)
name.exe -s word(
if file has processed, output
else out "file doesnt't processed", want to process [y/n], if rec wrtie (y -r) ) 
*/

int main(int argc, char* argv[]){
	setlocale(LC_ALL, "Russian");
	cout << argc;
	if (argc == 3) {
		if (argv[1] == "-i") {
			IndexerManager indexer_manager(argv[2]);
			indexer_manager.Process(IndexerManager::Recursive::NonRecursive);
			indexer_manager.PrintConsole();
		}
	}

	//fs::path path("D:\\test");
	//IndexerManager in(path);
	////in.Process(IndexerManager::Recursive::NonRecursive);
	//in.Read("data\\test_data");
	//in.PrintConsole();
	////in.WriteFile();
	////in.Read("");
	////in.Find("Minsk");
}