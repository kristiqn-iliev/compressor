#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map> 

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void generateTextFile(const std::string& filename, int numChars, int minChar, int maxChar);

struct Node {
	std::pair<char, unsigned> pair;
	Node* left;
	Node* right;
	Node(std::pair<char, int> pair) {
		this->pair = pair;
		left = nullptr;
		right = nullptr;
	}
	Node(std::pair<char, int> pair, Node* left, Node* right) {
		this->pair = pair;
		this->left = left;
		this->right = right;
	}
};


class HuffmanTree {
private:
	Node* root;
	std::string text;
	std::string sorted;
	std::map<char, unsigned> freqTable;
	std::map<char, std::vector<bool>> codeTable;
	std::vector<Node*> leaves;
	std::vector<bool> encoded;

	void initFreqTable();
	void setLeaves();
	void constructTree();//към момента строи дървото по-различен начин от начина в условието но ефективността от към памет е запазена
	void traverse(Node* root, std::vector<bool>& code);
	void initCodeTable();
	void encodeText();

public:

	HuffmanTree(std::string text) : text(text), encoded({}) {
		sort(text.begin(), text.end());
		sorted = text;

		initFreqTable();
		setLeaves();
		//
		constructTree(); //Най-вероятно не е най-оптималния метод за построение на дървото(Предполагам може да се използва map, който спестява insertion sort-a)
		//
		initCodeTable();
		encodeText();
	}

	const std::vector<bool>& getEncodedText() {
		return encoded;
	}
};

void HuffmanTree::initFreqTable() {

	unsigned count = 1;
	char mostRecent = sorted[0];
	for (int i = 1; i < sorted.size(); ++i) {
		if (sorted[i] == mostRecent) {
			++count;
		}
		else {
			freqTable[mostRecent] = count;
			mostRecent = sorted[i];
			count = 1;
		}
	}

	freqTable[mostRecent] = count;
}

void HuffmanTree::setLeaves() {

	for (std::map<char, unsigned>::iterator it = freqTable.begin(); it != freqTable.end(); ++it) {
		leaves.push_back(new Node(std::pair<char, int>(it->first, it->second)));
	}
}

void HuffmanTree::constructTree() {
	while (leaves.size() > 1) {

		sort(leaves.begin(), leaves.end(), [](const Node* a, const Node* b) {
			return a->pair.second > b->pair.second;//descending - least is last
			});


		unsigned value = leaves[leaves.size() - 1]->pair.second + leaves[leaves.size() - 2]->pair.second;
		Node* node = new Node(std::pair<char, unsigned>({ '\0', value }), leaves[leaves.size() - 1], leaves[leaves.size() - 2]);
		leaves.pop_back();
		leaves.pop_back();
		leaves.push_back(node);
	
	}

	root = leaves[0];
}

void HuffmanTree::traverse(Node* root, std::vector<bool>& code) {
	if (root->left != nullptr) {
		code.push_back(0);
		traverse(root->left, code);
	}
	if (root->right != nullptr) {
		code.push_back(1);
		traverse(root->right, code);
	}
	if (root->right == nullptr && root->left == nullptr) {
		codeTable[root->pair.first] = code;
	}

	if(code.size() != 0)
		code.pop_back();
}

void HuffmanTree::initCodeTable() {
	std::vector<bool> dummy;
	traverse(root, dummy);
}

void HuffmanTree::encodeText() { 
	
	for (int i = 0; i < text.size(); ++i) {
		encoded.insert(encoded.end(), codeTable[text[i]].begin(), codeTable[text[i]].end());
	}
}

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

	printVec(HuffmanTree("alllahasdaflasldfkasdlflasldfkdasflijawrgialkwrgjaslkgjalksfvjalksrjairoairgj").getEncodedText());

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