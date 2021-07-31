#include "TRIE.h"

int main() {

	TRIE test;
	test.CreateDictionary("dictionary.txt");

	Vector<string> v = test.wordList();
}