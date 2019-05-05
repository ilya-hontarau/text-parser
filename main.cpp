#include "index.h"
#include "manager.h"
#include "cmdl_parser.h"
#include "executor.h"
#include <iostream>


/*
how to run:
run programm exe with this flags
1)index folder
	-i [folder_path] [-r]
	-r -recursive searching(none recursiving is setting by default)
	NOTE: programm asks for printing information indexing folder
2) search word in indexing folder
	[folder_path] -s
	NOTE: you should index file before searching
3) index and search 
	-i [folder_path] -s "word" [-r]
	-r - recursive searching(none recursiving is setting by default)
*/

void Solution(int argc, char* argv[]) {
	try{
	CommandLineParser cmdlp(argc, argv);
	auto opt = cmdlp.GetOptions();
	if (opt.has_value()) {
			Executor exe(opt.value());
			exe.Process();
		}
	}
	catch (const std::exception& ex) {
	  std::cout << ex.what() << std::endl;
	}
}

int main(int argc, char* argv[]){
	setlocale(LC_ALL, "Russian");
	Solution(argc, argv);
}
