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

	// Open files ----------------------
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

	// Parse files ----------------------
	string line;
	string name; // Shown Hypertext
	string link; // valid link
	bool insideWiki = false; // inside [[ ]]
	bool rename = false;	 // renaming with |
	bool image = false;		 // Link is image (starts with !)
	while (getline(file_in, line)) {
		for (int i = 0; i < line.length(); i++) {

			// Change [[ --> [
			if (line[i] == '[') {
				if (insideWiki) {
					throw std::logic_error("[ found inside wiki link");
				}

				// Check for second [
				file_out << line[i++];
				if (line[i] != '[') { // not a WikiLink
					file_out << line[i];
					continue;
				}

				insideWiki = true;

				// Check if image
				if (i > 1 && line[i-2] == '!') image = true;
				continue;
			} 
			// Change ]] --> ](link)
			else if (line[i] == ']' && insideWiki) {

				file_out << name;
				file_out << line[i++];

				if (line[i] != ']') {
					throw std::logic_error("] found inside wiki link without following ]");
				}

				file_out << "(./" << link;
				if (!image) file_out << ".html"; // for page links
				file_out << ")";

				// Reset
				link = "";
				name = "";
				image = false;
				insideWiki = false;
				continue;
			}

			// Generate link and name (inside [[]])
			if (insideWiki) {
				// Insert - instead of space in links
				if (line[i] == ' ') {
					link += "-";
				} else {
					link += line[i];
				}

				name += line[i];

				// Make Name string after |
				if (line[i] == '|') {
					name = "";
				}
				continue;
			}

			// Default
			file_out << line[i];
		}
		file_out << "\n";
	}

	file_in.close();
	file_out.close();
	return 0;
}
