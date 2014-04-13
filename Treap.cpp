#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace std;

template<class Type>
class Treap {
    template<class NodeType>
    class TreapNode {
    public:
        Type data;
        TreapNode<NodeType> *left;
        TreapNode<NodeType> *right;
        int size;

        long long priority;

        TreapNode(const NodeType &data) {
            this->data = data;
            this->left = NULL;
            this->right = NULL;
            this->size = 1;
            this->priority = ((long long)rand() << 31) | rand();
        }
    };

    TreapNode<Type> *root;

    void updateSize(TreapNode<Type> **root) {
        (*root)->size = 1 +
                ((*root)->left == NULL ? 0 : (*root)->left->size) +
                ((*root)->right == NULL ? 0 : (*root)->right->size);
    }

    void raise(TreapNode<Type> **root) {
        if ((*root)->left != NULL && (*root)->left->priority > (*root)->priority) {
            TreapNode<Type> *oldRoot = *root;
            TreapNode<Type> *middleTree = (*root)->left->right;
            *root = (*root)->left;
            (*root)->right = oldRoot;
            (*root)->right->left = middleTree;
            updateSize(&((*root)->right));
        } else if ((*root)->right != NULL && (*root)->right->priority > (*root)->priority) {
            TreapNode<Type> *oldRoot = *root;
            TreapNode<Type> *middleTree = (*root)->right->left;
            *root = (*root)->right;
            (*root)->left = oldRoot;
            (*root)->left->right = middleTree;
            updateSize(&((*root)->left));
        }
    }

    void sinq(TreapNode<Type> **root) {
        if ((*root)->left != NULL && (*root)->right != NULL) {
            if ((*root)->left->priority > (*root)->right->priority) {
                if ((*root)->left != NULL && (*root)->left->priority > (*root)->priority) {
                    TreapNode<Type> *oldRoot = *root;
                    TreapNode<Type> *middleTree = (*root)->left->right;
                    *root = (*root)->left;
                    (*root)->right = oldRoot;
                    (*root)->right->left = middleTree;
                    sinq(&((*root)->right));
                }
            } else {
                if ((*root)->right != NULL && (*root)->right->priority > (*root)->priority) {
                    TreapNode<Type> *oldRoot = *root;
                    TreapNode<Type> *middleTree = (*root)->right->left;
                    *root = (*root)->right;
                    (*root)->left = oldRoot;
                    (*root)->left->right = middleTree;
                    sinq(&((*root)->left));
                }
            }
        } else {
            if ((*root)->left != NULL && (*root)->left->priority > (*root)->priority) {
                TreapNode<Type> *oldRoot = *root;
                TreapNode<Type> *middleTree = (*root)->left->right;
                *root = (*root)->left;
                (*root)->right = oldRoot;
                (*root)->right->left = middleTree;
                sinq(&((*root)->right));
            }
            if ((*root)->right != NULL && (*root)->right->priority > (*root)->priority) {
                TreapNode<Type> *oldRoot = *root;
                TreapNode<Type> *middleTree = (*root)->right->left;
                *root = (*root)->right;
                (*root)->left = oldRoot;
                (*root)->left->right = middleTree;
                sinq(&((*root)->left));
            }
        }
        (*root)->size = 1 +
                ((*root)->left == NULL ? 0 : (*root)->left->size) +
                ((*root)->right == NULL ? 0 : (*root)->right->size);
    }

    void insert(TreapNode<Type> **root, TreapNode<Type> *newNode) {
        if (*root == NULL) {
            *root = newNode;
        } else {
            if (newNode->data < (*root)->data) {
                insert(&(*root)->left, newNode);
            } else {
                insert(&(*root)->right, newNode);
            }
            raise(root);
            (*root)->size = 1 +
                    ((*root)->left == NULL ? 0 : (*root)->left->size) +
                    ((*root)->right == NULL ? 0 : (*root)->right->size);
        }
    }

    bool remove(TreapNode<Type> **root, const Type &data) {
        bool removed = false;
        if (*root != NULL) {
            if (data < (*root)->data) {
                removed = remove(&(*root)->left, data);
            } else if (data == (*root)->data) {
                TreapNode<Type> *toDelete = *root;
                if ((*root)->left == NULL) {
                    *root = (*root)->right;
                } else if ((*root)->right == NULL) {
                    *root = (*root)->left;
                } else {
                    TreapNode<Type> **next = &(*root)->right;
                    while((*next)->left != NULL) {
                        --(*next)->size;
                        next = &((*next)->left);
                    }
                    TreapNode<Type> *nextRight = (*next)->right;
                    (*next)->left = (*root)->left;
                    (*next)->right = (*root)->right;
                    *root = *next;
                    *next = nextRight;
                    if (*root == (*root)->right) {
                        (*root)->right = nextRight;
                    }
                    sinq(root);
                }
                assert(toDelete->data == data);
                delete toDelete;
                removed = true;
            } else {
                removed = remove(&(*root)->right, data);
            }
            if (*root != NULL) {
                (*root)->size = 1 +
                        ((*root)->left == NULL ? 0 : (*root)->left->size) +
                        ((*root)->right == NULL ? 0 : (*root)->right->size);
            }
        }
        return removed;
    }

public:

    Treap() {
        this->root = NULL;
    }

    int size() {
        if (this->root == NULL) {
            return 0;
        } else {
            return this->root->size;
        }
    }

    void insert(const Type &data) {
        TreapNode<Type> *newNode = new TreapNode<Type>(data);
        insert(&this->root, newNode);
    }

    bool exists(const Type &data) {
        TreapNode<Type> *node = this->root;
        while (node != NULL) {
            if (data < node->data) {
                node = node->left;
            } else if (data == node->data) {
                return true;
            } else {
                node = node->right;
            }
        }
        return false;
    }

    int indexOf(const Type &data) {
        int answer = 1;
        TreapNode<Type> *node = this->root;
        while (node != NULL) {
            if (data < node->data) {
                node = node->left;
            } else if (data == node->data) {
                answer += (node->left == NULL) ? 0 : node->left->size;
                return answer;
            } else {
                answer += (node->left == NULL) ? 1 : node->left->size + 1;
                node = node->right;
            }
        }
        return -1;
    }

    int countBetween(const Type &smallData, const Type &largeData) {
        int beforeSmallData = 0;
        TreapNode<Type> *node = this->root;
        while (node != NULL) {
            if (smallData < node->data) {
                node = node->left;
            } else if (smallData == node->data) {
                node = node->left;
            } else {
                beforeSmallData += (node->left == NULL) ? 1 : node->left->size + 1;
                node = node->right;
            }
        }
        int beforeLargeData = 0;
        node = this->root;
        while (node != NULL) {
            if (largeData < node->data) {
                node = node->left;
            } else if (largeData == node->data) {
                beforeLargeData += (node->left == NULL) ? 1 : node->left->size + 1;
                node = node->right;
            } else {
                beforeLargeData += (node->left == NULL) ? 1 : node->left->size + 1;
                node = node->right;
            }
        }
        return beforeLargeData - beforeSmallData;
    }

    bool remove(const Type &data) {
        return remove(&this->root, data);
    }

    Type* findByIndex(int index) {
        TreapNode<Type> *node = this->root;
        if (!(1 <= index && index <= node->size)) {
            return NULL;
        } else {
            while (true) {
                if (node->left == NULL) {
                    if (index == 1) {
                        return &(node->data);
                    } else {
                        node = node->right;
                        --index;
                    }
                } else {
                    if (index <= node->left->size) {
                        node = node->left;
                    } else if (index == node->left->size + 1) {
                        return &(node->data);
                    } else {
                        index -= node->left->size + 1;
                        node = node->right;
                    }
                }
            }
            return Type();
        }
    }

    void assertion(TreapNode<Type> **root) {
        if (*root != NULL) {
            assert((*root)->size == 1 +
                    ((*root)->left == NULL ? 0 : (*root)->left->size) +
                    ((*root)->right == NULL ? 0 : (*root)->right->size));
            if ((*root)->left != NULL) {
                assert((*root)->priority > (*root)->left->priority);
                assert((*root)->data >= (*root)->left->data);
                assertion(&((*root)->left));
            }
            if ((*root)->right != NULL) {
                assert((*root)->priority > (*root)->right->priority);
                assert((*root)->data <= (*root)->right->data);
                assertion(&((*root)->right));
            }
        }
    }

    void assertion() {
        assertion(&this->root);
    }
};

int main() {
    Treap<int> treap;
    int i;
    treap.insert(1);
    treap.remove(1);
    for (i = 0; i < 100000; ++i) {
        treap.insert(i);
    }
    //printf("%d\n", treap.countBetween(7, 29));
    for (i = 0; i < 100000; ++i) {
        //printf("%d\n", *treap.findByIndex(i + 1));
        treap.findByIndex(i + 1);
        //printf("%d\n", treap.indexOf(i));
        treap.indexOf(i);
    }
    for (i = 0; i < 100000; ++i) {
        assert(true == treap.exists(i));
        treap.remove(i);
        assert(false == treap.exists(i));
        assert(100000 - i - 1 == treap.size());
        //printf("%d\n", i);
    }
    for (i = 0; i < 1000000; ++i) {
        //treap.assertion();
        treap.insert(rand() % 100000);
        treap.insert(rand() % 100000);
        treap.remove(rand() % 100000);
        //printf("%d\n", i);
    }
    return 0;
}
