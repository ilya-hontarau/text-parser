#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

class Indexer {
public:
	struct Options {
		size_t sent_number;
		size_t offset_number;
	};

	explicit Indexer(const std::filesystem::path& path) ;
	
	void Process();

	void PrintConsole() const;
	void WriteFile(std::ofstream& out)const;
	std::optional<std::vector<Options>> Find(const std::string& search_word) const ;

	friend std::ostream& operator<<(std::ostream& out, const std::vector<Options>& options);

	std::string GetFileName() const {return path_.filename().string();}

	void Read(std::ifstream& in);
private:
	std::vector<std::string> sentences;
	std::vector<std::string> words;
	std::unordered_map<std::string, std::vector<Options>> words_data;
	std::filesystem::path path_;
	void WriteFileWords(std::ofstream& out) const;
	void WriteFileSentences(std::ofstream& out) const;
	enum class WordRegister {
		Upper,
		Lower,
	};
	void AddWord(const std::string& word, const Options& option, WordRegister wr);
	void ProcessWord(const std::string& word, const Options& option);
	
	void PrintSentences() const;
	void PrintWords() const;

	std::string Edit(const std::string& str);

	bool CheckWord(const std::string& word) const;
};

