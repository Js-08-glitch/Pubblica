#include <iostream>
using namespace std;

class albero
{
private:
	struct node {
		int value;
		node* left;
		node* right;

		node(int val) : value(val), left(nullptr), right(nullptr) {}
	};

	node* root; // RICORDA INIT A NULLPTR!

public:
	albero() : root(nullptr) {}

	void ins_albero(int val)
	{
		node* cur = root;

		node* n_ins = new node(val);

		if (!cur) {
			root = n_ins;
			cout << "Albero vuoto: inserito il primo nodo " << n_ins->value << endl;
		}
		else
			while (cur)
			{
				if (n_ins->value < cur->value) {
					if (!cur->left) {
						cur->left = n_ins;
						cout << "Inserito a sinistra di " << cur->value << endl;
						return;
					}
					else {
						cout << "Proseguo a sinistra di " << cur->value << endl;
						cur = cur->left;
					}
				}
				else {
					if (!cur->right) {
						cur->right = n_ins;
						cout << "Inserito a destra di " << cur->value << endl;
						return;
					}
					else {
						cout << "Proseguo a destra di " << cur->value << endl;
						cur = cur->right;
					}
				}
			}
	}
};

int main()
{
	albero a;
	int val;

	cout << "Inserire un valore (negativo per finire): ";
	do {
		cin >> val;
		if (val >= 0)
			a.ins_albero(val);
	} while (val >= 0);

	return 0;
}