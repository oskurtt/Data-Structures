/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++(){
	//assert(0 && "rope_iterator operator++ not implemented!");
	// if i have right subtree, find left most element of those
    if (ptr_->right != NULL) {
      ptr_ = ptr_->right;
      while (ptr_->left != NULL)
        ptr_ = ptr_->left;
    } else {
      // Keep going up as long as I'm my parent's right child
      while (ptr_->parent && ptr_->parent->right == ptr_)
        ptr_ = ptr_->parent;
      // Go up one more time
      ptr_ = ptr_->parent;
    }
    return *this;
	
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	//assert(0 && "rope_iterator begin() not implemented!");
	Node* tmp = root;
	while (tmp->left){
		tmp = tmp->left;
	}
	return rope_iterator(tmp);
}

Rope::Rope(){
	//assert(0 && "Rope default constructor not implemented!");
	root = nullptr;
	size_ = 0;
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	//assert(0 && "Rope constructor from Node not implemented!");
	size_ = 0;
	root = p;
	Node* tmp = root;
	set_rope_size(p, size_);
}

void Rope::set_rope_size(Node* p, int &size_){
	//stop recursing if you are at leaf node
	if(!p->left && !p->right ){
		size_ += p->weight;
		//return;
	}
	else{
		//recurseivley go through all the nodes and add to the size
		if (p->left){
			set_rope_size(p->left, size_);
		}
		if (p->right){
			set_rope_size(p->right, size_);
		}
	}
}

Rope::~Rope(){
	//assert(0 && "Rope destructor not implemented!");
	this->destroy_tree(root);
}


void Rope::set_weight(Node* p, int& w){
	//same as set rope size but for weight
	if(!p->left && !p->right ){
		w += p->weight;
	}
	else{
		if (p->left){
			set_weight(p->left, w);
		}
		if (p->right){
			set_weight(p->right, w);
		}
	}
}
Rope::Rope(const Rope& r){
	//assert(0 && "Rope copy constructor not implemented!");
	//set the rope size and copy the rope
	set_rope_size(r.root, size_);
	root = copy_rope(r.root);
}

Rope& Rope::operator= (const Rope& r){
	//assert(0 && "Rope assignment not implemented!");
	size_= 0;
	if (this->expose_root() != r.root){
		size_ = 0;
		this->destroy_tree(root);
		set_rope_size(r.root, size_);
		root = copy_rope(r.root);
	}
	return *this;
}

Node* Rope::copy_rope(Node* old_root){
	//if old_root is NULL, return
	if (!old_root) return 0;
	Node* ret = new Node();
	//set the parent, weight, and value 
	ret->parent = old_root->parent;
	ret->weight = old_root->weight;
	ret->value = old_root->value;
	//copy the left side and right side
	ret->left = copy_rope(old_root->left);
	ret->right = copy_rope(old_root->right);
	//set the size
	size_ = 0;
	set_rope_size(ret, size_);
	return ret;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	Node* tmp = root;
	//go left if index is smaller than weight, other wise go right and decrement index
	if ((i >= size_) || (i<0)) return false;
	while (tmp->left || tmp->right){
		if (i < tmp->weight){
			tmp = tmp->left;
		}
		else{
			i -= tmp->weight;
			tmp = tmp->right;
		} 
	}
	c = tmp->value[i];
	return true;;
}
//used for splitting and return the index number when indexing
int Rope::split_index(int i, Node* &tmp) const{
	if ((i >= size_) || (i<0)) return 0;
	while (tmp->left || tmp->right){
		if (i < tmp->weight){
			tmp = tmp->left;
		}
		else{
			i -= tmp->weight;
			tmp = tmp->right;
		} 
	}
	return i;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	//assert(0 && "Rope concat() not implemented!");
	//create a new node and its left to the left rope and the right to the right rope
	Node* tmp = new Node();
	tmp->left = this->root;
	tmp->left->parent = tmp;
	tmp->weight = this->size_;
	//copy right rope over
	tmp->right = copy_rope(r.root);
	tmp->right->parent = tmp;
	//set size
	size_ = 0;
	set_rope_size(tmp, size_);
	this->root = tmp;
}

void Rope::concat_no_copy(Node*& r1, Node*& r2){
	//does same as concat but don't copy anything
	this->root = new Node;
	this->root->left = r1;
	this->root->left->parent = root;
	this->root->right = r2;
	this->root->right->parent = root;
	size_ = 0;
	set_rope_size(root, size_);
	
	int w = 0;
	Node* p = root;
	//set the weight
	set_weight(p->left, w);
	this->root->weight = w;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	//assert(0 && "Rope report() not implemented!");
	//iterate through the rope and make the string and then edit the 's' that was passed through
	std::string tmp;
	s.clear();
	for(rope_iterator it = begin(); it!= end(); it++){
		tmp+=it.value();
	}
	for (int a = i; a <= j; a++){
		s+=tmp[a];
	}
	if (s.size() > 0) return true;
	else return false;
}

//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	//assert(0 && "Rope split() not implemented!");
	//create a vector of nodes in case we need to concat multiple nodes
	//create a pointer node to the root and find what the index number is
	std::vector<Node*> v;
	int num;
	Node* tmp = root;
	num = split_index(i, tmp);
	//if num = 0 (no need to split node)
	if (num == 0){
		//if what you are splitting is on the right
		if (tmp == tmp->parent->right){
			//pushback the leaf node and cut it off the rope
			v.push_back(tmp);
			tmp = tmp->parent;
			tmp->right = NULL;
			//move up as long as you're your parents right
			while (tmp == tmp->parent->right){
				tmp = tmp->parent;
			}
			//if you are your parent's left, iterate up and cut off every right node
			//pushback the cut off node to the vector to be concated later
			while ((tmp->parent != NULL) && (tmp == tmp->parent->left)){
				tmp = tmp->parent;
				v.push_back(tmp->right);
				int w = 0;
				Node* p = tmp;
				set_weight(p->left, w);
				tmp->weight = w;
				tmp->right = NULL;
			}
		}
		//if you are you're parents left move up as long as you're your parents left
		else if (tmp == tmp->parent->left){
			tmp = tmp->parent;
			while (tmp == tmp->parent->left){
				tmp = tmp->parent;
			}
			//move up one more time and cut off the right node and add it to the vector
			tmp = tmp->parent;
			v.push_back(tmp->right);
			tmp->right = NULL;
		}
	}
	else{
		//create two nodes if you need to split the leaf node
		//set each node to corresponding weight
		//set each node's parent to the current node's parent
		//set each nodes value by substringing the string
		tmp->weight = num;
		tmp->left = NULL;
		tmp->right = NULL;
		Node* tmp_left = new Node();
		Node* tmp_right = new Node();
		tmp->left = tmp_left;
		tmp_left->parent = tmp;
		tmp_left->weight = num;
		tmp->left->value = tmp->value.substr(0, num);
		tmp->right = tmp_right;
		tmp->right->parent = tmp;
		tmp_right->weight = tmp->value.size()-num;
		tmp->right->value = tmp->value.substr(num, tmp->value.size()-1);
		tmp->value.clear();
		return *this;
	}
	//if there is only one thing in the vector, no need to concat
	if (v.size() == 1){
		rhs = v[0];
		return *this;
	}
	std::vector<Node*>::iterator it1 = v.begin();
	std::vector<Node*>::iterator it2 = v.begin()+1;
	//concat the elements in the vector
	while (it2 != v.end()){
		rhs.concat_no_copy((*it1), (*it2));
		it2++;
	}
	//set the size
	size_ = 0;
	set_rope_size(root, size_);
	root->weight = size_;

	return *this;
}

void Rope::destroy_tree(Node* p){
	//delete the left and rights of the tree recursively
    if (!p) return;
    destroy_tree(p->left);
    destroy_tree(p->right);
    delete p;
	size_ = 0;
  }
