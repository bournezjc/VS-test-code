#include "tree_def.h"
#include <string>
#include <stdexcept>
#include <iostream>

using namespace std;

Node* Tree::search(int val) {
	return search(root, val);
}
Node* Tree::search(Node* node, int val) const {
	if (node == nullptr) return node;
	if (node->val == val) {
		return node;
	}

	if (val < node->val) {
		return search(node->left, val);
	}
	else {
		return search(node->right, val);
	}
}

/*
left rotation:
         px                            px
	    /                             /
	   x                             y
      / \            -->            / \
	 lx  y                         x   ry
	    / \                       / \
	   ly  ry                    lx  ly

*/
void Tree::LRotate(Node* root, Node* node) {
	Node* y = node->right;
	node->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = node;
	}

	if (node == root) {
		root = y;
	}
	else {
		if (node->parent->left == node) {
			node->parent->left = y;
		}
		else {
			node->parent->right = y;
		}
	}
	y->parent = node->parent;
	node->parent = y;
	y->left = node;

}

/*
right rotation:
		 px                            px
		/                             /
	   x                             y
	  / \            -->            / \
	 y   rx                       ly   x
    / \                               / \
   ly  ry                            ry  rx

*/

void Tree::RRotate(Node* root, Node* node) {
	Node* y = node->left;
	node->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = node;
	}

	if (node == root) {
		root = y;
	}
	else {
		if (node->parent->left == node) {
			node->parent->left = y;
		}
		else {
			node->parent->right = y;
		}
	}
	y->parent = node->parent;
	node->parent = y;
	y->right = node;

}

void Tree::insert(int val) {
	Node* node = new Node(RED, val, nullptr, nullptr, nullptr);
	insert(root, node);
}

void Tree::insert(Node* root, Node* node) {
	if (root == nullptr) {
		root = node;
		node->color = BLACK;
		return;
	}

	Node* curnode = root;
	Node* prenode;
	while (curnode != nullptr) {
		prenode = curnode;
		if (node->val == curnode->val) {
			delete node;
			return;
		}
		else if (node->val < curnode->val) {
			curnode = curnode->left;
		}
		else {
			curnode = curnode->right;
		}
	}



	if (node->val < prenode->val) { //insert left 
		prenode->left = node;
		node->parent = prenode;
	}
	else { //insert right
		prenode->right = node;
		node->parent = prenode;
	}
	//if black, do not have to do anything
	//if red, we have to consider cases
	Node* tmpnode = node;
	while (tmpnode->parent != nullptr && tmpnode->parent->color == RED) {
		if (tmpnode->parent->parent->left == tmpnode->parent) { //if node's parent is node's grandparent's left child.
			if (tmpnode->parent->right != nullptr && tmpnode->parent->right->color == RED) { // if uncle node exists and is red.
				tmpnode->parent->color = BLACK;
				tmpnode->parent->right->color = BLACK;
				tmpnode->parent->parent->color = RED;
				tmpnode = tmpnode->parent->parent;
				continue;
			}
			else { //if uncle node does not exist or is black.
				if (tmpnode->parent->right == tmpnode) { //if curnode is its parent's right child
					LRotate(root, tmpnode->parent);
					tmpnode = tmpnode->left;
				}

				// if curnode is its parent's left child
				tmpnode->parent->color = BLACK;
				tmpnode->parent->parent->color = RED;
				RRotate(root, tmpnode->parent->parent);
			}
		}
		else { // node's parent is grandparent's right child
			if (tmpnode->parent->left != nullptr && tmpnode->parent->left->color == RED) { // if uncle node exists and is red.
				tmpnode->parent->color = BLACK;
				tmpnode->parent->left->color = BLACK;
				tmpnode->parent->parent->color = RED;
				tmpnode = tmpnode->parent->parent;
				continue;
			}
			else { //if uncle node does not exist or is black.
				if (tmpnode->parent->left == tmpnode) { //if curnode is its parent's left child
					RRotate(root, tmpnode->parent);
					tmpnode = tmpnode->right;
				}

				// if curnode is its parent's right child
				tmpnode->parent->color = BLACK;
				tmpnode->parent->parent->color = RED;
				LRotate(root, tmpnode->parent->parent);
			}
		}

	}

	root->color = BLACK;
}

void Tree::remove(int val) {
	Node* tmp = search(root, val);
	if (tmp != nullptr) remove(root, tmp);
}
void Tree::remove(Node* root, Node* node) {
	Color nodecol;
	Node* child;
	//Node* parent;
	if (node->left != nullptr && node->right != nullptr) {
		Node* successor = node->right;
		while (successor->left != nullptr) {
			successor = successor->left;
		}

		if (node != root) {
			if (node->parent->left == node) {
				node->parent->left = successor;
			}
			else {
				node->parent->right = successor;
			}
		}
		else {
			root = successor;
		}

		child = successor->right;
		nodecol = successor->color;
		/*
		if (child != nullptr) {
			if (successor->parent != node) {
				child->parent = successor->parent;

				successor->parent->left = child;
				successor->right = node->right;
				node->right->parent = successor;
			}
		}
		else {
			if (successor->parent != node) {
				successor->parent->left = nullptr;
				successor->right = node->right;
				node->right->parent = successor;
			}
		}*/

		if (successor->parent != node) {
			if (child != nullptr) {
				child->parent = successor->parent;
			}
			successor->parent->left = child;
			successor->right = node->right;
			node->right->parent = successor;
			
		}

		successor->parent = node->parent;
		successor->color = node->color;
		successor->left = node->left;
		node->left->parent = successor;

		if (nodecol == BLACK) removefix(root, child);

		delete node;
		return;

	}
	else if (node->left != nullptr) {
		child = node->left;
	}
	else {
		child = node->right;
	}

	nodecol = node->color;
	//parent = node->parent;

	if (child != nullptr) {
		child->parent = node->parent;
	}

	if (node->parent != root) {
		if (node->parent->left == node) {
			node->parent->left = child;
		}
		else {
			node->parent->right = child;
		}
	}
	else {
		root = child;
	}

	if (nodecol == BLACK) removefix(root, child);

	delete node;

}

void Tree::removefix(Node* root, Node* node) {
	Node* sibling;
	while ((node != nullptr && node->color == BLACK) && node != root) {
		if (node->parent->left == node) {
			sibling = node->parent->right;
			if (sibling->color == RED) { //if sibling is red
				sibling->color = BLACK;
				node->parent->color = RED;
				LRotate(root, node->parent);
				sibling = node->parent->right; //update new sibling node in order to do next case
			}

			if ((sibling->left != nullptr && sibling->left->color == BLACK) &&
				(sibling->right != nullptr && sibling->right->color == BLACK)) {
				sibling->color = RED;
				node = node->parent;
				continue;
			}

			if ((sibling->left != nullptr && sibling->left->color == RED) &&
				(sibling->right != nullptr && sibling->right->color == BLACK)) { // if sibling' left child is red, right is black
				sibling->color = RED;
				sibling->left->color = BLACK;
				RRotate(root, sibling);
				sibling = node->parent->right; //update new sibling node to next case
			}

			if (sibling->right != nullptr && sibling->right->color == RED) { //if sibling's right child is red, left is any color
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->right->color = BLACK;
				LRotate(root, node->parent);
				node = root; //end case
				break;
			}
		}
		else {
			sibling = node->parent->left;
			if (sibling->color == RED) { //if sibling is red
				sibling->color = BLACK;
				node->parent->color = RED;
				RRotate(root, node->parent);
				sibling = node->parent->left; //update new sibling node in order to do next case
			}

			if ((sibling->left != nullptr && sibling->left->color == BLACK) &&
				(sibling->right != nullptr && sibling->right->color == BLACK)) {
				sibling->color = RED;
				node = node->parent;
				continue;
			}

			if ((sibling->left != nullptr && sibling->left->color == BLACK) &&
				(sibling->right != nullptr && sibling->right->color == RED)) { // if sibling' left child is black, right is red
				sibling->color = RED;
				sibling->right->color = BLACK;
				LRotate(root, sibling);
				sibling = node->parent->left; //update new sibling node to next case
			}

			if (sibling->left != nullptr && sibling->left->color == RED) { //if sibling's left child is red, right is any color
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->left->color = BLACK;
				RRotate(root, node->parent);
				node = root; //end case
				break;
			}
		}
	}

	if (node != nullptr) {
		node->color = BLACK;
	}
}