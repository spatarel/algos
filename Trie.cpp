#include <stdlib.h>

#define QSIZE 26

class Trie {
private:
    char first;
    struct Nod {
        bool este;
        Nod* fii[QSIZE];
    };
    Nod* root;

    Nod* new_nod() {
        int i;
        Nod* nod = (Nod*) malloc(sizeof(Nod));
        nod->este = false;
        nod->fii['0' - this->first] = NULL;
        for (i = 'A' - this->first; i <= 'Z' - this->first; ++i) {
            nod->fii[i] = NULL;
        }
        for (i = 'a' - this->first; i <= 'z' - this->first; ++i) {
            nod->fii[i] = NULL;
        }
        return nod;
    }

    void free_nod(Nod* nod) {
        int i;
        for (i = 0; i < QSIZE; ++i) {
            if (nod->fii[i] != NULL) {
                free_nod(nod->fii[i]);
            }
        }
        free(nod);
    }

public:
    Trie(char first, char last) {
        //assert(last - first + 1 == QSIZE);
        this->first = first;
        this->root = new_nod();
    }

    void add(char* V) {
        int i;
        Nod* pos;
        for(i = 0, pos = this->root; V[i] != 0; pos = pos->fii[V[i] - this->first], ++i) {
            if (pos->fii[V[i] - this->first] == NULL) {
                pos->fii[V[i] - this->first] = new_nod();
            }
        }
        pos->este = true;
    }

    bool find(char* V) {
        int i;
        Nod* pos;
        for(i = 0, pos = this->root; V[i] != 0; pos = pos->fii[V[i] - this->first], ++i) {
            if (pos->fii[V[i] - this->first] == NULL) {
                return false;
            }
        }
        return pos->este;
    }

    ~Trie() {
        free_nod(this->root);
    }
};

