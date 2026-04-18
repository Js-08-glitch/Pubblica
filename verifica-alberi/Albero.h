#pragma once
#include <string>
using namespace std;

struct Albero {

private:
	struct Node {
		string titolo;
		int pos;
		Node* l;
		Node* r;
	};
	
	Node* root = nullptr;

	void deleteTree(Node* root) {
		if (!root) return;
		deleteTree(root->l);
		deleteTree(root->r);
		delete root;
	}

public:
	~Albero() { deleteTree(root); }
	
	// INSERIMENTO
	Node* add(Node* root, const string& title, int pos) {
		if (!root) return new Node{ title, pos, nullptr, nullptr };
		if (title < root->titolo)
			root->l = add(root->l, title, pos);
		else
			root->r = add(root->r, title, pos);
		return root;
	}

	void add(const string& title, int pos) { root = add(root, title, pos); } // overload

	// CANCELLAZIONE
	Node* findMin(Node* root) {
		if (!root) return nullptr;
		if (!root->l) return root;
		return findMin(root->l);
	}

	Node* canc(Node* root, const string& title) {
		if (!root) return nullptr;
		if (title < root->titolo)
			root->l = canc(root->l, title);
		else if (title > root->titolo)
			root->r = canc(root->r, title);
		else {
			if (!root->l && !root->r) {
				delete root;
				return nullptr;
			}
			
			if (!root->l) {
				Node* tmp = root->r;
				delete root;
				return tmp;
			}

			if (!root->r) {
				Node* tmp = root->l;
				delete root;
				return tmp;
			}

			Node* newRoot = findMin(root->r);
			root->titolo = newRoot->titolo;
			root->pos = newRoot->pos;
			root->r = canc(root->r, root->titolo);
		}

		return root;
	}

	void canc(const string& title) { root = canc(root, title); }
	
	// RICERCA
	Node* ric(Node* root, const string& title) {
		if (!root) return nullptr;
		if (root->titolo == title) return root;
		if (title < root->titolo)
			return ric(root->l, title);
		if (title > root->titolo)
			return ric(root->r, title);
		// non inserire duplicati
	}

	int ric(const string& title) { // overload
		Node* result = ric(root, title);
		if (!result) return -1;
		return result->pos;
	}
};