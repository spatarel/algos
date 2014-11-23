#include <cstdlib>

const int SIGMA = 26;
const char FIRST_CHAR = 'a';

class Trie {
private:
    class TrieNode {
    public:
        bool isWord;
        TrieNode* descendents[SIGMA];

        TrieNode() {
            int i;
            this->isWord = false;
            for (i = 0; i < SIGMA; ++i) {
                this->descendents[i] = NULL;
            }
        }

        ~TrieNode() {
            int i;
            for (i = 0; i < SIGMA; ++i) {
                if (this->descendents[i] != NULL) {
                    delete this->descendents[i];
                }
            }
        }

    };

    TrieNode* root;

public:
    Trie() {
        this->root = new TrieNode();
    }

    void add(char* word) {
        int i;
        TrieNode* pos;
        for (i = 0, pos = this->root; word[i] != 0; pos = pos->descendents[word[i] - FIRST_CHAR], ++i) {
            if (pos->descendents[word[i] - FIRST_CHAR] == NULL) {
                pos->descendents[word[i] - FIRST_CHAR] = new TrieNode();
            }
        }
        pos->isWord = true;
    }

    bool exists(char* word) {
        int i;
        TrieNode* pos;
        for (i = 0, pos = this->root; word[i] != 0; pos = pos->descendents[word[i] - FIRST_CHAR], ++i) {
            if (pos->descendents[word[i] - FIRST_CHAR] == NULL) {
                return false;
            }
        }
        return pos->isWord;
    }

    ~Trie() {
        delete this->root;
    }
};

