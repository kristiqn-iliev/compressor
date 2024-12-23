#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map> 

struct Node {
	std::pair<char, unsigned> pair;
	Node* left;
	Node* right;
	Node(std::pair<char, int> pair);
	Node(std::pair<char, int> pair, Node* left, Node* right);
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

	HuffmanTree(std::string text);
	const std::vector<bool>& getEncodedText();
};

