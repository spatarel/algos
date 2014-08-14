#include <cstdio>
#include <queue>

using namespace std;

class AhoCorasickLinkedNode;

class AhoCorasickNode {
public:
	bool isFinal;
	AhoCorasickLinkedNode *sons;
	AhoCorasickNode *failure;
	AhoCorasickNode *output;
	int wordLength;

	AhoCorasickNode();
	AhoCorasickNode* sonExists(char character);
	AhoCorasickNode*& son(char character);
	AhoCorasickLinkedNode* newAhoCorasicLinkedNode(char character, AhoCorasickNode *son, AhoCorasickLinkedNode *next);
	void dump(int size, char* prefix);
};

class AhoCorasickLinkedNode {
public:
	char character;
	AhoCorasickNode *son;
	AhoCorasickLinkedNode *next;

	AhoCorasickLinkedNode();
};

AhoCorasickLinkedNode::AhoCorasickLinkedNode() {
	this->character = 0;
	this->son = NULL;
	this->next = NULL;
}

AhoCorasickNode::AhoCorasickNode() {
	this->isFinal = false;
	this->sons = NULL;
	this->failure = NULL;
	this->output = NULL;
	this->wordLength = 0;
}

AhoCorasickLinkedNode* AhoCorasickNode::newAhoCorasicLinkedNode(char character, AhoCorasickNode *son, AhoCorasickLinkedNode *next) {
	AhoCorasickLinkedNode* linkedNode = new AhoCorasickLinkedNode();
	linkedNode->character = character;
	linkedNode->son = son;
	linkedNode->next = next;
	return linkedNode;
}

AhoCorasickNode* AhoCorasickNode::sonExists(char character) {
	AhoCorasickLinkedNode* son;
	for (son = this->sons; son != NULL; son = son->next) {
		if (son->character == character) {
			return son->son;
		}
	}
	return NULL;
}

AhoCorasickNode*& AhoCorasickNode::son(char character) {
	AhoCorasickLinkedNode* son;
	for (son = this->sons; son != NULL; son = son->next) {
		if (son->character == character) {
			return son->son;
		}
	}
	this->sons = newAhoCorasicLinkedNode(character, new AhoCorasickNode(), this->sons);
	return this->sons->son;
}

void AhoCorasickNode::dump(int size, char* prefix) {
	AhoCorasickLinkedNode* son;
	prefix[size] = 0;
	printf("[%p]%s:", this, prefix);
	printf("failure(%p)", this->failure);
	if (this->output != NULL) {
		printf("outputWordLength(%d)", this->output->wordLength);
	}
	if (this->isFinal) {
		printf("isFinalWordLength(%d)", this->wordLength);
	}
	printf("\n");
	for (son = this->sons; son != NULL; son = son->next) {
		prefix[size] = son->character;
		son->son->dump(size + 1, prefix);
	}
}

class AhoCorasic {
private:
	AhoCorasickNode* root;

public:
	AhoCorasic() {
		this->root = new AhoCorasickNode();
		this->automataLink = this->root;
	}

	void addWord(char* word) {
		AhoCorasickNode* node;
		int i;
		for (i = 0, node = this->root; word[i] != 0; node = node->son(word[i]), ++i);
		node->wordLength = i;
		node->isFinal = true;
	}

	void computeLinks() {
		AhoCorasickLinkedNode* son;
		queue<AhoCorasickNode*> bfsQueue;

		this->root->failure = this->root;
		this->root->output = NULL;
		for (son = this->root->sons; son != NULL; son = son->next) {
			bfsQueue.push(son->son);
			son->son->failure = this->root;
			son->son->output = NULL;
		}

		while (!bfsQueue.empty()) {
			AhoCorasickNode* node = bfsQueue.front();
			bfsQueue.pop();
			for (son = node->sons; son != NULL; son = son->next) {
				bfsQueue.push(son->son);
				AhoCorasickNode* failNode = node->failure;
				while (failNode != this->root && !failNode->sonExists(son->character)) {
					failNode = failNode->failure;
				}
				if (failNode->sonExists(son->character)) {
					son->son->failure = failNode->son(son->character);
				} else {
					son->son->failure = this->root;
				}
				if (son->son->failure->isFinal) {
					son->son->output = son->son->failure;
				} else {
					son->son->output = son->son->failure->output;
				}
			}
		}
	}

	void dump() {
		char word[10001];
		word[0] = 0;
		return this->root->dump(0, word);
	}

	AhoCorasickNode* automataLink;

	void resetParser() {
		this->automataLink = this->root;
	}

	int parse(char character) {
		AhoCorasickNode* newAutomataLink;
		while (!(newAutomataLink = this->automataLink->sonExists(character)) &&
				this->automataLink != this->root) {
			this->automataLink = this->automataLink->failure;
		}
		if (newAutomataLink) {
			this->automataLink = newAutomataLink;
		}
		//printf("%c %p\n", character, this->automataLink);
		if (this->automataLink->isFinal) {
			return this->automataLink->wordLength;
		} else if (this->automataLink->output != NULL) {
			return this->automataLink->output->wordLength;
		} else {
			return 0;
		}
	}
};
