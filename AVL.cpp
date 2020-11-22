#include "NodeInterface.h"
#include "Node.h"
#include "AVL.h"
#include <algorithm>
#include <sstream>
#include <queue>
#include <string>
using namespace std;



string tsb(Node* bst) {
    queue<NodeInterface*> readQ; // used to read in the levels of the tree, contains Node*
    stringstream ss; // used to store the values of the nodes and the level-order sequence
    int depth = 0; // the depth of a node on the tree
    if (bst == NULL) {
        return "BST is empty\n";
    }
    readQ.push(bst); // push the root node of the tree into the queue
    while (!readQ.empty()) { // as long as the queue has a remaining node:
        int i = readQ.size(); // store the number of nodes on this level of the tree
        ss << depth << ":  ";
        for (; i > 0; i--) { // for each node on this level,
            NodeInterface* nextNode = readQ.front(); // store the next node in the queue
            ss << nextNode->getData() << " "; // store the data from the node into the ss
            if (nextNode->getLeftChild() != NULL) { // if there is a left child, push the left child into the queue
                readQ.push(nextNode->getLeftChild());
            }
            if (nextNode->getRightChild() != NULL) { // if there is a right child, push the left child into the queue
                readQ.push(nextNode->getRightChild());
            }
            readQ.pop(); // pop the node off of the queue, leaving its children in the queue
        }
        ss << "\n"; // push an endl into the ss to distinguish levels
        depth++;
    }
    return ss.str();
}

NodeInterface * AVL::getRootNode() const {
	return root;
}

bool AVL::add(int data) {
	addFunction(root, data);
}

bool AVL::addFunction(Node*& myNode, int value) {
	if (myNode == NULL) {
		myNode = new Node(value);
		myNode->height = 0;
		return true;
	}
	if (myNode->data == value) {
		return false;
	}
	if (myNode->data > value) {
		bool fluff = addFunction(myNode->leftChild, value);
		if (fluff == true) {
			if (myNode->getBalance() > 1) {
				balanceLeft(myNode);
      }
			if (myNode->getBalance() < -1) {
				balanceRight(myNode);
      }
		}
		return fluff;
	}

	if (myNode->data < value) {
		bool fluff2 = addFunction(myNode->rightChild, value);
		if (fluff2 == true) {
			if (myNode->getBalance() > 1) {
				balanceLeft(myNode);
      }
			if (myNode->getBalance() < -1) {
				balanceRight(myNode);
      }
		}
		return fluff2;
	}
	if (myNode->getBalance() > 1) {
		balanceLeft(myNode);
  }
	if (myNode->getBalance() < -1) {
		balanceRight(myNode);
  }
	return false;
}

bool AVL::remove(int data) {
		bool fluff5;
		fluff5 = removeFunction(root, data);
		balance(root);
		return fluff5;
}

bool AVL::removeFunction(Node*& myNode, int value) {
	if (myNode == NULL) {
		return false;
	}
	if (myNode->data > value) {
		bool fluff3 = removeFunction(myNode->leftChild, value);
		balance(myNode);
		return fluff3;
	}
	if (myNode->data < value) {
		bool fluff4 = removeFunction(myNode->rightChild, value);
		balance(myNode);
		return fluff4;
	}
  // no next of kin
	if (myNode->rightChild == NULL && myNode->leftChild == NULL) {
		delete myNode;
		myNode = NULL;
		return true;
	}
  //one child
	if (myNode->rightChild == NULL || myNode->leftChild == NULL) {
		Node* temp;
		temp = myNode->leftChild;
		if (myNode->leftChild == NULL) {
			temp = myNode->rightChild;
		}
		delete myNode;
		myNode = temp;
		balance(myNode);
		return true;
	}
	Node* temp = fosterParent(myNode->leftChild);
	temp->leftChild = myNode->leftChild;
	temp->rightChild = myNode->rightChild;
	delete myNode;
	myNode = temp;
	return true;
}

Node* AVL::fosterParent(Node*& myNode) {
	if (myNode->rightChild == NULL) {
		Node* temp = myNode;
		myNode = myNode->leftChild;
		return temp;
	}
	Node* temp = fosterParent(myNode->rightChild);
	balance(myNode);
	return temp;
}

void AVL::clear() {
	clearFunction(root);
	root = NULL;
}

void AVL::clearFunction(Node*& myNode) {
	if (myNode == NULL) {
		return;
	}
	if (myNode->leftChild != NULL) {
		clearFunction(myNode->leftChild);
	}
	if (myNode->rightChild != NULL) {
		clearFunction(myNode->rightChild);
	}
	delete myNode;
	return;
}

void AVL::balanceRight(Node*& myNode) {
	if (myNode == NULL) {
		return;
  }
	if (myNode->leftChild->getBalance() >= 1) {
		rotateLeft(myNode->leftChild);
	}
	rotateRight(myNode);
}

void AVL::balanceLeft(Node*& myNode) {
	if (myNode == NULL) {
		return;
  }
	if (myNode->rightChild->getBalance() <= -1) {
		rotateRight(myNode->rightChild);
	}
	rotateLeft(myNode);
}

void AVL::rotateRight(Node*& myNode) {
	Node* temp = myNode->leftChild;
	myNode->leftChild = temp->rightChild;
	temp->rightChild = myNode;
	myNode = temp;
}

void AVL::rotateLeft(Node*& myNode) {
	Node* temp = myNode->rightChild;
	myNode->rightChild = temp->leftChild;
	temp->leftChild = myNode;
	myNode = temp;
}

void AVL::balance(Node*& myNode) {
	if (myNode == NULL) {
		return;
  }
	if (myNode->getBalance() > 1) {
		balanceLeft(myNode);
  }
	else if (myNode->getBalance() < -1) {
		balanceRight(myNode);
  }
	balance(myNode->leftChild);
	balance(myNode->rightChild);
}