#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
//#include <fstream>
#include <string>

using namespace std::literals;

class Ebook {
public:
	void Read(int reader, int page) {
		if (reader_page.count(reader)) {
			--page_readers[reader_page.at(reader)];
			reader_page[reader] = page;
			++page_readers[page];
		}
		else {
			reader_page[reader] = page;
			++page_readers[page];
		}
	}

	void Cheer(std::ostream& output, int reader) const {
		output << std::setprecision(6) << GetShare(reader) << std::endl;
	}

private:
	std::map<int, int> reader_page;
	std::map<int, int> page_readers;

	double GetShare(int reader) const {
		if (reader_page.empty() || !(reader_page.count(reader))) {
			return 0.0;
		}
		else if (reader_page.size() == 1 && reader_page.count(reader) == 1) {
			return 1.0;
		}

		auto it_readers_behind = page_readers.find(reader_page.at(reader));

		int num_readers_behind = std::accumulate(std::begin(page_readers), it_readers_behind, 0,
			[](int value, const std::map<int, int>::value_type& p)
			{return value + p.second; });
		double share = 1.0 * num_readers_behind / (reader_page.size() - 1);
		return share;
	}
};

//void TestRead() {
//	Ebook e;
//	std::ifstream input("input.txt");
//	std::ofstream output("output.txt");
//
//	std::string s;
//	std::getline(input, s);
//	int queries_count = stoi(s);
//	for (int i = 0; i != queries_count; ++i) {
//		int reader, page;
//		input >> s;
//		if (s == "READ"s) {
//			input >> reader >> page;
//			e.Read(reader, page);
//		}
//		else if (s == "CHEER"s) {
//			input >> reader;
//			e.Cheer(output, reader);
//		}
//	}
//}

int main() {
	//TestRead();
	Ebook e;
	int queries_count = 0;
	std::cin >> queries_count;

	for (int i = 0; i != queries_count; ++i) {
		int reader = 0;
		int page = 0;
		std::string command_string;
		std::cin >> command_string;
		if (command_string == "READ"s) {
			std::cin >> reader >> page;
			e.Read(reader, page);
		}
		else if (command_string == "CHEER"s) {
			std::cin >> reader;
			e.Cheer(std::cout, reader);
		}
	}
	return 0;
}
