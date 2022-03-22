////////////////////////////////////////////////////////
//  _ _ _ _ _ _ _
// |  - - - -    |
// | |      / /| |    Zachary Traczyk (ztraczyk)
// | |   / /   | |
// | |/ / _ _ _| |    2022 Winter CSE101 PA5
// |  _ _   _ _  |    Shuffle.c
// | |_ _| |_ _| |    Main program, performs a shuffle
// |_ _ _ _ _ _ _|    using the List ADT.
//
////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>

using std::cerr;
using std::string;
using std::ofstream;
using std::ifstream;

//
// main execution
//
int main(int argc, char **argv) {
	ifstream file_in;
	ofstream file_out;

	// Parse program argument ---------------
	if (argc != 3) {
		cerr << "Error: specify an input and an ouput file\n";
		return 1;
	}

	file_in.open(argv[1]);
	file_out.open(argv[2]);

	if (!(file_in.is_open() && file_out.is_open())) {
		cerr << "Error: cannot open specified files\n";
		return 1;
	}

	string line;
	string link;
	bool insideWiki = false;
	while (getline(file_in, line)) {
		for (int i = 0; i < line.length(); i++) {
			// Catch open bracket, make opening 1 bracket if double
			if (line[i] == '[') {
				if (insideWiki == false) {
					file_out << line[i++];
				} else {
					throw std::logic_error("[ found inside wiki link");
				}

				if (line[i] == '[') {
					insideWiki = true;
				} else {
					file_out << line[i];
				}
				// Catch closed bracket, make closing bracket and link
			} else if (line[i] == ']' && insideWiki) {
				file_out << line[i++];
				if (line[i] == ']') {
					file_out << "(./" << link << ".html)";
					link = "";
					insideWiki = false;
				} else {
					throw std::logic_error("] found inside wiki link without following ]");
				}
				// Keep normal character unchanged
			} else {
				file_out << line[i];
				if (insideWiki) {
					if (line[i] == ' ') {
						link += "-";
					} else {
						link += line[i];
					}
				}
			}
		}
		file_out << "\n";
	}

	file_in.close();
	file_out.close();

	return 0;
}
