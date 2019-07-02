#pragma once
#ifndef TREE_DEF_H
#define TREE_DEF_H

enum Color { RED, BLACK };

class Node {
public:
	Color color;
	int val;
	Node *left;
	Node *right;
	Node *parent;

	Node(Color color, int val, Node *left, Node *right, Node *parent):
		color{color}, val{val}, left{left}, right{right}, parent{parent} {}

};

class Tree {
	Node* root;

public:
	Tree();
	~Tree();

	Node* search(int val);

	void insert(int val);

	void remove(int val);

	void print_tree();

	void pre_order();
	void in_order();
	void post_order();
private:
	void pre_order(Node* root) const;
	void in_order(Node* root) const;
	void post_order(Node* root) const;

	Node* search(Node* node, int val) const;

	void insert(Node* root, Node *node);

	void remove(Node* root, Node *node);
	void removefix(Node* root, Node* node);

	void print_tree(Node* root, std::string order);

	void LRotate(Node* root, Node* node);
	void RRotate(Node* root, Node* node);

	void destroy(Node* node);


};

#endif