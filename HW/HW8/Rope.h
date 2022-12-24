/*
You may add things to this .h file as needed. 
However keep in mind that Rope_provided.cpp will always be compiled in Submitty tests.
So you should not delete or change any methods that are implemented in Rope_provided.cpp
All your implementation should go in Rope_student.cpp
*/

#ifndef _ROPE_H
#define _ROPE_H

#include <string>
#include <vector>
#include <iostream>

class Node{
public:
	Node() : left(NULL), right(NULL), parent(NULL), weight(0) {}
	Node* left;
	Node* right;
	Node* parent;
	int weight;
	std::string value;
};

class Rope;

class rope_iterator{
public:
	rope_iterator();
	rope_iterator(Node* p);
	rope_iterator& operator++();
	rope_iterator operator++(int);
	int weight() const;
	const std::string& value() const;
	friend class Rope;
	bool operator!=(const rope_iterator& it2) const;
	
private:
	Node* ptr_;
};

class Rope{
public:
	Rope();
	~Rope();
	Rope(Node* p);
	Rope(const Rope& r);
	Rope& operator= (const Rope& r);

	bool index(int i, char& c) const; //Get a single character
	int split_index(int i, Node* &tmp) const;
	void concat(const Rope& r); //Add the other string to me
	void concat_no_copy(Node*& r1, Node*& r2);
	bool report(int i, int j, std::string& s) const; //Substring
	Rope& split(int i, Rope& rhs); //Split the string at index i into this (LHS) and a new Rope rhs

	rope_iterator begin() const;
	rope_iterator end() const;

	int size() const;
	void print(std::ostream& out) const;
	void print_strings(std::ostream& out) const;
	Node* expose_root() const;

private:
	void print(std::ostream& out, Node* head, int depth) const;
private:
	int size_;
	Node *root;
	void destroy_tree(Node* p);
	void set_rope_size(Node* p, int &size_);
	void set_weight(Node* p, int& w);
	Node* copy_rope(Node* old_root);
};

bool is_leaf(Node* p);


#endif
