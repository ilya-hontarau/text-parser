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






int main()
{
	setlocale(LC_ALL, "Russian");
	fs::path path("D:\\test");
	IndexerManager in(path);
	//in.Process(IndexerManager::Recursive::NonRecursive);
	in.Read("data\\test_data");
	in.PrintConsole();
	//in.WriteFile();
	//in.Read();
	//in.Find("Minsk");
}