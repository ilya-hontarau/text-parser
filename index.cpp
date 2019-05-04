#include "index.h"
#include <iostream>

bool IsUpper(char ch) {
	if ((ch >= 'À' && ch <= 'ß') || (ch >= 'A' && ch <= 'Z')) {
		return true;
	}
	return false;
}

bool IsAlpha(char ch) {
	if ((ch >= 'À' && ch <= 'ÿ') || (ch >= 'A' && ch <= 'z')) {
		return true;
	}
	return false;
}

bool IsPunct(wchar_t symbol) {
	std::vector<wchar_t> symbols{ '?','!','.' ,',',';',':' };
	for (wchar_t ch : symbols) {
		if (symbol == ch) {
			return true;
		}
	}

	return false;
}


Indexer::Indexer(const std::filesystem::path& path) :path_(path) {
	//std::ifstream in(path);
	//if (!in.is_open()) {
	//	throw std::invalid_argument("wrong file");
	//}
	//std::string sentence;
	//size_t sent_counter = 0, offset_counter = 0;
	//while (!in.eof()) {
	//	std::string word;
	//	in >> word;
	//	sentence += word + " ";
	//	ProcessWord(Edit(word), { sent_counter, offset_counter });
	//	offset_counter = sentence.size();
	//	if (*prev(word.end()) == '.' || *prev(word.end()) == '!' || *prev(word.end()) == '?') {
	//		sentences.push_back(sentence.substr(0, sentence.size() - 1));
	//		sentence.clear();
	//		++sent_counter;
	//		offset_counter = 0;
	//	}

	//}

}

void Indexer::Process() {
	if (!std::filesystem::is_directory(path_)) {
		std::ifstream in(path_);
		if (!in.is_open()) {
			throw std::invalid_argument("wrong file");
		}
		std::string sentence;
		size_t sent_counter = 0, offset_counter = 0;
		while (!in.eof()) {
			std::string word;
			in >> word;
			sentence += word + " ";
			ProcessWord(Edit(word), { sent_counter, offset_counter });
			offset_counter = sentence.size();
			if (*prev(word.end()) == '.' || *prev(word.end()) == '!' || *prev(word.end()) == '?') {
				sentences.push_back(sentence.substr(0, sentence.size() - 1));
				sentence.clear();
				++sent_counter;
				offset_counter = 0;
			}

		}
	}
}

void Indexer::PrintSentences() const {
	for (size_t i = 0; i < sentences.size(); ++i) {
		std::cout << "Sent#" << i << ": \"" << sentences[i] << "\"" << std::endl;

	}
}

void Indexer::PrintWords() const {
	for (const auto& word : words) {
		std::cout << "Word: \"" << word << "\":{" << path_.filename() << "," << words_data.at(word) << std::endl;
	}
}

void Indexer::WriteFileSentences(std::ofstream & out) const {
	out << std::endl << sentences.size() << std::endl;
	for (size_t i = 0; i < sentences.size(); ++i) {
		out << sentences[i] << std::endl;
	}
}

void Indexer::PrintConsole() const {
	PrintSentences();
	PrintWords();
}

void Indexer::WriteFile(std::ofstream & out) const {
	WriteFileSentences(out);
	WriteFileWords(out);
}

void Indexer::WriteFileWords(std::ofstream & out) const {
	out << std::endl << words.size();
	for (const auto& word : words) {
		out << std::endl << word << " " << words_data.at(word).size() << " ";
		for (const auto& [sent, offset] : words_data.at(word)) {
			out << sent << " " << offset << " ";
		}
	}
}

std::optional<std::vector<Indexer::Options>> Indexer::Find(const std::string & search_word)const {
	auto it = words_data.find(search_word);
	if (it != words_data.end()) {
		return it->second;
	}
	else {
		return {};
	}
}

void Indexer::Read(std::ifstream & in) {
	if (!in.eof()) {
		size_t sent_number;
		in >> sent_number;
		in.ignore();
		for (size_t i = 0; i < sent_number; ++i) {
			std::string line;
			std::getline(in, line);
			sentences.push_back(std::move(line));
		}
		size_t word_number;
		in >> word_number;
		for (size_t i = 0; i < word_number; ++i) {
			std::string word;
			in >> word;
			size_t options_number;
			in >> options_number;
			for (size_t j = 0; j < options_number; ++j) {
				Options option;
				in >> option.sent_number >> option.offset_number;
				ProcessWord(word, option);

			}
		}
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


void Indexer::AddWord(const std::string & word, const Options & option, WordRegister wr) {
	std::string edited_word = word;
	switch (wr) {
	case WordRegister::Upper: {
		edited_word[0] = tolower(word[0]);
		break;
	}
	case WordRegister::Lower: {
		edited_word[0] = toupper(word[0]);
		break;
	}
	}

	if (words_data.find(edited_word) != words_data.end()) {
		words_data[edited_word].push_back(option);
		words_data[word].push_back(option);
	}
	else {
		words.push_back(word);
		words_data[edited_word].push_back(option);
		words_data[word].push_back(option);
	}

}

void Indexer::ProcessWord(const std::string & word, const Options & option) {
	if (IsUpper(word[0]) && IsAlpha(word[0])) {
		AddWord(word, option, WordRegister::Upper);
	}
	else if (!IsUpper(word[0]) && IsAlpha(word[0])) {
		AddWord(word, option, WordRegister::Lower);
	}
	else {
		words.push_back(word);
		words_data[word].push_back(option);
	}
}

std::ostream& operator<<(std::ostream & out, const std::vector<Indexer::Options> & options) {
	for (auto it = options.begin(); it != options.end(); it++) {

		if (it != prev(options.end())) {
			out << "(Sent#" << it->sent_number << ", " << "offset = " << it->offset_number << "), ";
		}
		else {
			out << "(Sent#" << it->sent_number << ", " << "offset = " << it->offset_number << "), ";
		}
	}
	return out;
}


std::string Indexer::Edit(const std::string & str) {
	if (str.size() == 0) throw std::invalid_argument("incorrect file");
		if (IsPunct(*prev(str.end()))) {
			return str.substr(0, str.size() - 1);
		}
	return str;
}