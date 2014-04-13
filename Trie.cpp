#include <stdlib.h>

const int TRIE_SIZE = 26;

class Trie {
private:
    class TrieNode {
    public:
        bool exists;
        TrieNode* descendents[TRIE_SIZE];

        TrieNode() {
            int i;
            this->exists = false;
            for (i = 0; i < TRIE_SIZE; ++i) {
                this->descendents[i] = NULL;
            }
        }

        ~TrieNode() {
            int i;
            for (i = 0; i < TRIE_SIZE; ++i) {
                if (this->descendents[i] != NULL) {
                    delete this->descendents[i];
                }
            }
        }

    };

    char first;
    TrieNode* root;

public:
    Trie(char first, char last) {
        //assert(last - first + 1 == TRIE_SIZE);
        this->first = first;
        this->root = new TrieNode();
    }

    void add(char* word) {
        int i;
        TrieNode* pos;
        for (i = 0, pos = this->root; word[i] != 0; pos = pos->descendents[word[i] - this->first], ++i) {
            if (pos->descendents[word[i] - this->first] == NULL) {
                pos->descendents[word[i] - this->first] = new TrieNode();
            }
        }
        pos->exists = true;
    }

    bool exists(char* word) {
        int i;
        TrieNode* pos;
        for (i = 0, pos = this->root; word[i] != 0; pos = pos->descendents[word[i] - this->first], ++i) {
            if (pos->descendents[word[i] - this->first] == NULL) {
                return false;
            }
        }
        return pos->exists;
    }

    ~Trie() {
        delete this->root;
    }
};

