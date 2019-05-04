#include "cmdl_parser.h"

using namespace std;


	

CommandLineParser::CommandLineParser(int argc, char* argv[]){
	for (int i = 0; i < argc; ++i) {
		tokens.push_back(string(argv[i]));
	}
}

std::optional<std::pair<CommandLineParser::Options, CommandLineParser::Parameters>> CommandLineParser::GetOptions() {
		auto index_it = std::find(tokens.begin(), tokens.end(), "-i");
		auto search_it = std::find(tokens.begin(), tokens.end(), "-s");
		auto rec_it = std::find(tokens.begin(), tokens.end(), "-r");
		if (index_it != tokens.end() && search_it == tokens.end()) {
			Options opt = { RecOptions(ProcessOpt::Indexer, rec_it) };
			Parameters param = { {},tokens[2] };
			return make_pair(opt, param);
		}
		else if (index_it != tokens.end() && search_it != tokens.end()) {
			Options opt = { RecOptions(ProcessOpt::IndexerSearch, rec_it) };
			Parameters param = { tokens[4],tokens[2] };
			return make_pair(opt, param);
		}
		else if (index_it == tokens.end() && search_it != tokens.end()) {
			Options opt = { RecOptions(ProcessOpt::Search, rec_it) };
			Parameters param = { tokens[3],tokens[1] };
			return make_pair(opt, param);
		}
		else {
			return {};
		}
	}



CommandLineParser::Options CommandLineParser::RecOptions(ProcessOpt procces_opt, vector<std::string>::iterator rec_it) {
	if (rec_it != tokens.end()) {
		return { procces_opt, ParseOpt::Recursive };
	}
	else return { procces_opt, ParseOpt::NonRecursive };
}
