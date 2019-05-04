#include "executor.h"
#include <iostream>
Executor::Executor(const std::pair<CommandLineParser::Options, CommandLineParser::Parameters>& cmdl_args){
	auto [options, parameters] = cmdl_args;
	options_ = options;
	parameters_ = parameters;
}

void Executor::Process(){
	using Process=CommandLineParser::ProcessOpt;
	using Rec=CommandLineParser::ParseOpt;

	IndexerManager indexer_manager(parameters_.path_);
	switch (options_.process_opt)
	{
	case Process::Indexer: {
		if (indexer_manager.Exist()) {
			std::cout << "file has processed\nwould you like to process again[y/n]\n";
			char ch;
			std::cin >> ch;
			if (ch == 'n') {
				indexer_manager.Read("");
				indexer_manager.PrintConsole();
			}
			else if (ch == 'y') {
				Indexer(indexer_manager, options_.parse_opt);
			}
			else {
				throw std::invalid_argument("incorrect command");
			}
		}
		else {
			Indexer(indexer_manager, options_.parse_opt);
		}
		break;
	}
	case Process::Search: {
		if (indexer_manager.Exist()) {
			Choose(indexer_manager, options_.parse_opt);
			indexer_manager.Find(parameters_.search_word);
		}
		else { 
			std::cout << "file hasn't processed\n"; 
		}
		break;
	}
	case Process::IndexerSearch: {
		Choose(indexer_manager, options_.parse_opt);
		indexer_manager.Find(parameters_.search_word);
		break;
	}
	}
}

void Executor::Choose(IndexerManager& indexer_manager, CommandLineParser::ParseOpt rec){
	if (rec == CommandLineParser::ParseOpt::Recursive) {
		indexer_manager.Process(IndexerManager::Recursive::Recursive);
	}
	else {
		indexer_manager.Process(IndexerManager::Recursive::NonRecursive);
	}
}

void Executor::Indexer(IndexerManager& indexer_manager, CommandLineParser::ParseOpt rec){
	Choose(indexer_manager, rec);
	indexer_manager.PrintConsole();
	indexer_manager.WriteFile();
}
