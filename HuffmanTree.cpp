#include "HuffmanTree.h"

Node::Node(std::pair<char, int> pair) {
		this->pair = pair;
		left = nullptr;
		right = nullptr;
	}

Node::Node(std::pair<char, int> pair, Node* left, Node* right) {
		this->pair = pair;
		this->left = left;
		this->right = right;
	}

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

HuffmanTree::HuffmanTree(std::string text) : text(text), encoded({}) {
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
	const std::vector<bool>& HuffmanTree::getEncodedText() {
		return encoded;
	}