#include <cstdlib>

const int SIGMA = 26;
const char FIRST_CHAR = 'a';

class Trie {
private:
    class Node {
        bool isWord;
        Node* sons[SIGMA];

        Node() {
            int i;
            this->isWord = false;
            for (i = 0; i < SIGMA; ++i) {
                this->sons[i] = NULL;
            }
        }

        ~Node() {
            int i;
            for (i = 0; i < SIGMA; ++i) {
                if (this->sons[i] != NULL) {
                    delete this->sons[i];
                }
            }
        }
    };
    Node* root;

public:
    Trie() {
        this->root = new Node();
    }

    void add(char* S) {
        int i;
        Node* pos;
        for (i = 0, pos = this->root; S[i] != 0; pos = pos->sons[S[i] - FIRST_CHAR], ++i) {
            if (pos->sons[S[i] - FIRST_CHAR] == NULL) {
                pos->sons[S[i] - FIRST_CHAR] = new Node();
            }
        }
        pos->isWord = true;
    }

    bool exists(char* S) {
        int i;
        Node* pos;
        for (i = 0, pos = this->root; S[i] != 0; pos = pos->sons[S[i] - FIRST_CHAR], ++i) {
            if (pos->sons[S[i] - FIRST_CHAR] == NULL) {
                return false;
            }
        }
        return pos->isWord;
    }

    ~Trie() {
        delete this->root;
    }
};
