#pragma once
#include "cmdl_parser.h"
#include "manager.h"

class Executor {
public:
	Executor(const std::pair<CommandLineParser::Options, CommandLineParser::Parameters>& cmdl_args);

	void Process();
private:
	CommandLineParser::Options options_;
	CommandLineParser::Parameters parameters_;

	void Choose(IndexerManager& indexer_manager, CommandLineParser::ParseOpt rec);

	void Indexer(IndexerManager& indexer_manager, CommandLineParser::ParseOpt rec);

};