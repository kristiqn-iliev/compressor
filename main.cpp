#include "HuffmanTree.h"

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void generateTextFile(const std::string& filename, int numChars, int minChar, int maxChar);

template <typename T>
void printVec(const std::vector<T>& vec) {
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
	}
	std::cout << std::endl;
}

int main()
{	
    /*
	generateTextFile("textfile.txt", 500000, 65, 90);

	std::ifstream ifs("textfile.txt", std::ios::binary | std::ios::ate);

	// Get the size of the file
	std::streamsize size = ifs.tellg();
	ifs.seekg(0, std::ios::beg); // Go back to the start of the file

	// Allocate memory for file content
	std::string buffer(size, '\0');

	// Read the whole file into the buffer
	if (ifs.read(&buffer[0], size)) {
		std::cout << "File read successfully. Here is the content:\n" << std::endl;
	}
	else {
		std::cerr << "Error occurred while reading the file." << std::endl;
		return 1;
	}

	ifs.close();

	std::ofstream outFile("encoded_file.txt", std::ios::binary);
	if (!outFile) {
		std::cerr << "Failed to open file for writing." << std::endl;
		return 1;
	}

	// Prepare to pack bits into bytes
	unsigned char bitBuffer = 0;
	int bitCount = 0;

	std::vector<bool> data = HuffmanTree(buffer).getEncodedText();

	for (size_t i = 0; i < data.size(); i++) {
		// Set the appropriate bit in bitBuffer
		if (data[i]) {
			bitBuffer |= (1 << bitCount);
		}

		bitCount++;

		// If we've filled this byte or are at the end of the array, write it out
		if (bitCount == 8 || i == data.size() - 1) {
			outFile.write(reinterpret_cast<char*>(&bitBuffer), sizeof(bitBuffer));
			bitBuffer = 0; // Reset the buffer
			bitCount = 0;  // Reset the bit count
		}
	}

	outFile.close();
	*/
	printVec(HuffmanTree("kriskobeatsloraloraloraeizatvagovoravlizaiuzatvorashtetiviknahoraputkatashtiporanqmambratumorapeqsnashtevhora").getEncodedText());

	return 0;
}

/*
class HuffmanTree { 
	Node* root;
	std::string text;
	std::string sorted;
	std::map<char, unsigned> freqTable;
	std::map<char, std::vector<bool>> codeTable;
	std::vector<Node*> leaves;
	std::string encodedText;

	void initFreqTable();
	void setLeaves();
	void constructTree();//към момента строи дървото по-различен начин от начина в условието но ефективността от към памет е запазена
	void traverse(Node* root, std::vector<bool>& code);
	void initCodeTable();
	void encodeText();
}*/

void generateTextFile(const std::string& filename, int numChars, int minChar, int maxChar) {
	std::ofstream ofs(filename);
	if (!ofs) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}

	srand(time(NULL)); // Seed the random number generator

	for (int i = 0; i < numChars; ++i) {
		// Generate a random character within the specified range
		char ch = static_cast<char>(minChar + rand() % (maxChar - minChar + 1));
		ofs << ch;
	}

	ofs.close();
	std::cout << "File generated successfully with " << numChars << " characters." << std::endl;
}