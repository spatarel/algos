#include <cstdlib>

const int SIGMA = 26;
const char FIRST_CHAR = 'a';

class Trie {
private:
    struct Node {
        bool isWord;
        Node* sons[SIGMA];
    };
    Node* root;

    Node* new_node() {
        int i;
        Node* node = (Node*) malloc(sizeof(Node));
        node->isWord = false;
        for (i = 0; i < SIGMA; ++i) {
        	node->sons[i] = NULL;
        }
        return node;
    }

    void free_node(Node* node) {
        int i;
        for (i = 0; i < SIGMA; ++i) {
            if (node->sons[i] != NULL) {
                this->free_node(node->sons[i]);
            }
        }
        free(node);
    }

public:
    Trie() {
        this->root = this->new_node();
    }

    void add(char* S) {
        int i;
        Node* pos;
        for (i = 0, pos = this->root; S[i] != 0; pos = pos->sons[S[i] - FIRST_CHAR], ++i) {
            if (pos->sons[S[i] - FIRST_CHAR] == NULL) {
                pos->sons[S[i] - FIRST_CHAR] = this->new_node();
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
        this->free_node(this->root);
    }
};
