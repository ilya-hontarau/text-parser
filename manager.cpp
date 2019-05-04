#include "manager.h"
#include <iostream>
#include <algorithm>
namespace fs = std::filesystem;

	void IndexerManager::Process(Recursive rec) {

		std::vector<fs::path> file_name_data;

		switch (rec)
		{
		case IndexerManager::Recursive::Recursive: {
			file_name_data = std::vector<fs::path>(fs::begin(std::filesystem::recursive_directory_iterator(path_)), fs::end(std::filesystem::recursive_directory_iterator(path_)));
			break;
		}
		case IndexerManager::Recursive::NonRecursive: {
			file_name_data = std::vector<fs::path>(fs::begin(std::filesystem::directory_iterator(path_)), fs::end(std::filesystem::directory_iterator(path_)));
			break;
		}
		default:
			break;
		}

		for (const auto& file_name : file_name_data) {
			//if (!fs::file_size(file_name)) {
				Indexer indexer(file_name);
				indexer.Process();
				indexer_data.push_back(std::move(indexer));
			//}
		}
	}

	void IndexerManager::PrintConsole() const {
		//string filename = "data\\" + path_.filename().string()+"_data";
		//ofstream write(filename, ios::binary);
		for (const auto& indexer : indexer_data) {
			indexer.PrintConsole();
		}
	}

	void IndexerManager::WriteFile() {
		if (!fs::exists("data\\")) {
			fs::create_directory("data\\");
		}
		std::string filename = "data\\" + path_.filename().string() + "_data";
		std::ofstream write(filename, std::ios::binary);
		for (const auto& indexer : indexer_data) {
			indexer.WriteFile(write);

		}
	}

	bool IndexerManager::Exist() const
	{
		fs::path search_file = "data\\"+path_.filename().string() + "_data";
		auto it_ = std::vector<fs::path>(fs::begin(std::filesystem::directory_iterator("data")), fs::end(std::filesystem::directory_iterator("data")));
		auto it = std::find(fs::begin(std::filesystem::directory_iterator("data")), fs::end(std::filesystem::directory_iterator("data")), search_file);
		if (it == fs::end(std::filesystem::directory_iterator(path_))) {
			return false;
		}
		else return true;
	}

	void IndexerManager::Find(const std::string& search_word)  const {
		std::cout << "-\t\"" << search_word << "\":" << std::endl;
		for (const auto& indexer : indexer_data) {
			auto indexers_ = indexer.Find(search_word);
			if (indexers_.has_value()) {
				std::cout << "\t\to " << "File \"" << indexer.GetFileName() << "\"" << std::endl;
				for (const auto& element : indexers_.value()) {
					std::cout << "\t\t\t* (Sent#" << element.sent_number << ", offset=" << element.offset_number << ")" << std::endl;
				}
			}
		}
	}

	void IndexerManager::Read(const fs::path& path) {
		std::string filename = "data\\" + path_.filename().string() + "_data";
		std::ifstream in(filename, std::ios::binary);
		if (!in.is_open()) throw std::invalid_argument("");
		in.ignore();
		while (!in.eof()) {
			Indexer indexer(filename);
			indexer.Read(in);
			indexer_data.push_back(std::move(indexer));

		}
	}
