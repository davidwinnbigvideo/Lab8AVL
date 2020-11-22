#include <iostream>
#include "Node.h"

	int Node::getData() const {
    return data;
  }

	NodeInterface * Node::getLeftChild() const {
    return leftChild;
  }

	NodeInterface * Node::getRightChild() const {
    return rightChild;
  }

	int Node::getHeight() {
		int leftBranchHeight = 0;
		int rightBranchHeight = 0;
		if (leftChild != NULL) {
			leftBranchHeight = leftChild->getHeight();
		}
		if (rightChild != NULL) {
			rightBranchHeight = rightChild->getHeight();
		}
    if (leftBranchHeight >= rightBranchHeight) {
      return leftBranchHeight + 1;
    }
    if (rightBranchHeight > leftBranchHeight) {
      return rightBranchHeight + 1;
    }
	}

	int Node::getBalance() {
		int right;
		int left;
		if (rightChild != NULL) {
			right = rightChild->getHeight();
		}
		else {
		right = 0;
    }
		if (leftChild != NULL) {
			left = leftChild->getHeight();
		}
		else {
		left = 0;
    }
		return right - left;
	}