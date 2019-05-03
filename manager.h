#pragma once
#include "index.h"
class IndexerManager {
public:
	IndexerManager(const std::filesystem::path& path) :path_(path) {}

	enum class Recursive {
		Recursive,
		NonRecursive
	};

	void Process(Recursive rec);

	void PrintConsole() const;

	void WriteFile();

	void Find(const std::string& search_word) const ;

	void Read(const std::filesystem::path& path);
private:
	std::filesystem::path path_;
	std::vector<Indexer> indexer_data;
};