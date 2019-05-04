#include "index.h"
#include "manager.h"
#include "cmdl_parser.h"
#include "executor.h"
#include <iostream>


/*
name.exe -i folder -r(?)
if file has processed , ask for it
name.exe -i folder -s word -r(nonr -  deafault)
name.exe folder -s word -r(
if file has processed, output
else out "file hasnt't processed", want to process [y/n], if rec wrtie (y -r) ) 
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
	catch (const std::exception ex) {
	  std::cout << ex.what() << std::endl;
	}
}

int main(int argc, char* argv[]){
	setlocale(LC_ALL, "Russian");
	Solution(argc, argv);
}