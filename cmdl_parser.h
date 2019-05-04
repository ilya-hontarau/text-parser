#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <optional>
class CommandLineParser {
public:
	CommandLineParser(int argc, char* argv[]);

	enum class ProcessOpt {
		Indexer,
		IndexerSearch,
		Search
	};

	enum class ParseOpt {
		Recursive,
		NonRecursive
	};

	struct Parameters {
		std::string search_word;
		std::filesystem::path path_;
	};

	struct Options {
		ProcessOpt process_opt;
		ParseOpt parse_opt;
	};

	std::optional<std::pair<Options, Parameters>> GetOptions();

private:
	std::vector<std::string> tokens;

	Options RecOptions(ProcessOpt procces_opt, std::vector<std::string>::iterator rec_it);
};