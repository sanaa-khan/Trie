#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


template <typename T>
class Vector {
private:
	T* ptr;
	int size_;
	int c_index;
	int cap;

public:
	Vector() : ptr(NULL), size_(0), c_index(0), cap(0) {};

	Vector(int size) : size_(0), c_index(0), cap(size) {
		ptr = new T[cap];
	}

	Vector(int size, const T& iv) : size_(size), c_index(size_) {
		ptr = new T[size_];

		for (int i = 0; i < size_; i++)
			ptr[i] = iv;
	}

	Vector(const Vector<T>& obj) : size_(obj.size_), c_index(obj.c_index), cap(obj.cap) {
		ptr = new T[cap];

		for (int i = 0; i < size_; i++)
			ptr[i] = obj.ptr[i];
	}

	~Vector() {
		delete[]ptr;
	}

	const T& operator = (const T& obj) {

		if (size_ == cap) {
			Vector<T> copy(*this);
			~*this;

			cap *= 2;
			ptr = new T[cap];

			for (int i = 0; i < size_; i++)
				ptr[i] = copy.ptr[i];

			delete[]copy.ptr;
		}

		size_++;
		ptr[size_] = obj;
		return ptr[size_];
	}

	T* begin() {
		return ptr;
	}

	T* end() {
		return (ptr + size_ - 1);
	}

	int size() {
		return size_;
	}

	void resize(int x) {
		if (x == cap)
			return;

		else if (x > cap) {
			Vector<T> copy(*this);
			delete[]ptr;

			cap = x;
			ptr = new T[cap];

			for (int i = 0; i < size_; i++)
				ptr[i] = copy[i];

			delete[]copy.ptr;

			return;
		}

		else {
			Vector<T> copy(*this);
			delete[]ptr;

			cap = x;
			ptr = new T[cap];

			if (size_ > cap)
				size_ = cap;

			for (int i = 0; i < size_; i++)
				ptr[i] = copy[i];

			delete[]copy.ptr;

			return;
		}
	}

	bool empty() {
		if (size_ == -1)
			return true;

		return false;
	}

	void shrink_to_fit(int x) {

		Vector<T> copy(*this);
		delete[]ptr;

		cap = x;
		ptr = new T[cap];

		if (size_ > cap)
			size_ = cap;

		for (int i = 0; i < size_; i++)
			ptr[i] = copy[i];

		delete[]copy.ptr;
	}

	T& operator [] (int index) {
		return ptr[index];
	}

	T& front() {
		return ptr[0];
	}

	T& back() {
		return ptr[size_ - 1];
	}

	void push_back(const T& value) {

		if (size_ == cap)
			this->resize(cap * 2);

		ptr[size_] = value;
		size_++;
	}

	void pop_back() {
		size_--;
	}

	void swap(Vector<T>& other) {
		Vector<T> temp(*this);
		delete[]ptr;

		cap = other.cap;
		size_ = other.size_;
		c_index = other.c_index;
		ptr = new T[cap];

		for (int i = 0; i < size_; i++)
			ptr[i] = other.ptr[i];

		delete[]other.ptr;

		other.size_ = temp.size_;
		other.c_index = temp.c_index;
		other.cap = temp.cap;
		other.ptr = new T[other.cap];

		for (int i = 0; i < other.size_; i++)
			other.ptr[i] = temp.ptr[i];

		delete[]temp.ptr;
	}

	void clear() {
		//c_index = 0;
		size_ = -1;
	}

	int capacity() {
		return cap;
	}
};

class TRIE {

	struct trieNode {
		char value;
		string meaning;
		Vector<string> synonyms;
		trieNode* childNodes[26];
		bool completeWord;
		
		trieNode() : value('\0'), synonyms(10), completeWord(false), meaning("") {
			for (int i = 0; i < 26; i++)
				childNodes[i] = NULL;

		}
	};

	trieNode* root;

public:

	TRIE() {
		root = new trieNode;
		root->value = '\0';
	}

	int letterIndex(char letter) {
		return (letter - 97);
	}

	trieNode* insertWord(const std::string& word) {

		char letter;
		int lIndex;

		bool flag = true;
		trieNode* current = root;

		for (int i = 0; i < word.length(); i++) {

			if (word[0] == '-' && flag) {
				i++;
				flag = false;
			}

			letter = word[i];
			lIndex = letterIndex(letter);

			if (current->childNodes[lIndex] == NULL) {
				trieNode* tmp;
				tmp = new trieNode;
				tmp->value = letter;
				current->childNodes[lIndex] = tmp;
			}

			current = current->childNodes[lIndex];

			if (i == word.length() - 1) {
				current->completeWord = true;
			}
		}

		return current;
	}

	void CreateDictionary(const std::string& filename) {

		ifstream in(filename);

		if (in.is_open()) {

			char c = in.get(); // reading '-'
			string str;

			in >> str;

			while (!in.eof()) {
			
				trieNode* insertedNode;
				insertedNode = insertWord(str); // insert word into tree

				c = in.get(); // '-'
				c = in.get(); // '-'

				getline(in, str); // 

				if (str[0] == '-')
					str = str.substr(1, str.length());

				insertedNode->meaning = str;

				getline(in, str);

				bool flag = true;

				while (str[0] != '-' && flag) {
					if (in.eof())
						flag = false;

					insertedNode->synonyms.push_back(str);
					getline(in, str);
				}
			}
		} 
	}

	bool FindWord(const std::string& key) {

		if (root == NULL)
			return false;

		trieNode* current = root;

		char letter;
		int lIndex;
		int i;

		for (i = 0; i < key.length(); i++) {
			letter = key[i];
			lIndex = letterIndex(letter);

			if (current->childNodes[lIndex] != NULL && current->childNodes[lIndex]->value == letter)
				current = current->childNodes[lIndex];
			else
				break;
		}

		if (i == key.length() && current->completeWord == true)
			return true;
		return false;
	}

	Vector<string> FindSynonyms(const std::string& key) {
		trieNode* current = root;

		char letter;
		int lIndex;
		int i;

		for (i = 0; i < key.length(); i++) {
			letter = key[i];
			lIndex = letterIndex(letter);

			if (current->childNodes[lIndex] != NULL && current->childNodes[lIndex]->value == letter)
				current = current->childNodes[lIndex];
			else
				break;
		}

		// word(key) is found
		if (i == key.length() && current->completeWord == true) {
			return current->synonyms;
		}
	}

	string FindMeaning(const std::string& key) {
		trieNode* current = root;

		char letter;
		int lIndex;
		int i;

		for (i = 0; i < key.length(); i++) {
			letter = key[i];
			lIndex = letterIndex(letter);

			if (current->childNodes[lIndex] != NULL && current->childNodes[lIndex]->value == letter)
				current = current->childNodes[lIndex];
			else
				break;
		}

		// word(key) is found
		if (i == key.length() && current->completeWord == true) {
			return current->meaning;
		}
	}

	Vector<string> OutputPrefix(const std::string& prefix) {
		trieNode* current = root;

		char letter;
		int lIndex;

		for (int i = 0; i < prefix.length(); i++) {
			letter = prefix[i];
			lIndex = letterIndex(letter);

			if (current->childNodes[lIndex] != NULL && current->childNodes[lIndex]->value == letter)
				current = current->childNodes[lIndex];
		}

		Vector<string> prefixWords;

		string word = prefix;
		trieNode* tmp = current;

		for (int i = 0; i < 26; i++) {
			if (current->childNodes[i] != NULL) {

				bool flag = true;

				while (current->completeWord != true || flag) {
					flag = false;
					word += current->childNodes[i]->value;
				}
			}
		}

		return prefixWords;
	}

	Vector<string> permutations(std::string str, int i, int n) {

		static Vector<string> perms;

		// base condition
		if (i == n - 1) {
			cout << str << endl;
			perms.push_back(str);
			return perms;
		}

		for (int j = i; j < n; j++) {
			swap(str[i], str[j]); 
			permutations(str, i + 1, n);
			swap(str[i], str[j]);
		}
	}

	Vector<string> OutputAnagrams(const std::string& key) {

		Vector<string> temp, toReturn;
		string str = key;

		temp = permutations(str, 0, str.length());

		for (int i = 0; i < temp.size(); i++) {
			if (this->FindWord(temp[i]))
				toReturn.push_back(temp[i]);
		}

		return toReturn;
	}

	bool noChildren(trieNode* node) {
		for (int i = 0; i < 26; i++) {
			if (node->childNodes[i] != NULL)
				return false;
		}

		return true;
	}

	bool isLeafNode(trieNode* node) {
		for (int i = 0; i < 26; i++) {
			if (node->childNodes[i] != NULL)
				return false;
		}

		return true;
	}

	Vector<string> AllWords(trieNode* node, char str[], int level) {

		static Vector<string> words;

		if (isLeafNode(root)) {
			str[level] = '\0';
			cout << str << endl;
			words.push_back(str);
		}

		int i;

		for (i = 0; i < 26; i++) {
			if (node->childNodes[i] != NULL) {
				str[level] = i + 'a';
				AllWords(node->childNodes[i], str, level + 1);
			}
		}

		return words;
	}

	Vector<string> wordList() {
		char str[20];
		Vector<string> words = AllWords(root, str, 0);
		return words;
	}

	Vector<string> matchingWords(trieNode* node, std::string& prefix) {

		static Vector<string> words;

		if (node->completeWord) {
			words.push_back(prefix);
		}

		if (isLeafNode(node))
			return words;

		for (int i = 0; i < 26; i++) {
			if (node->childNodes[i]) {
				prefix.push_back(97 + i);

				matchingWords(node->childNodes[i], prefix);
			}
		}

		return words;
	}

	Vector<string> OutputAscending() {
		Vector<string> toReturn = this->wordList();

		// sort the vector in ascending
	}

	Vector<string> OutputDescending() {
		Vector<string> toReturn = this->wordList();

		// sort the vector in descending
	}

	Vector<string> OutputSmaller(int length) {
		Vector<string> temp = this->wordList();
		Vector<string> temp2;

		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].length() < length)
				temp2.push_back(temp[i]);
		}

		return temp2;
	}

	Vector<string> OutputSE(int length) {
		Vector<string> temp = this->wordList();
		Vector<string> temp2;

		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].length() <= length)
				temp2.push_back(temp[i]);
		}

		return temp2;
	}

	Vector<string> OutputGreater(int length) {
		Vector<string> temp = this->wordList();
		Vector<string> temp2;

		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].length() > length)
				temp2.push_back(temp[i]);
		}

		return temp2;
	}
};