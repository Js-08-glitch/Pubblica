#include <iostream>
#include "piante.h"
using namespace std;

int main()
{
	Pianta p1("Ulivo", "albero da frutto", 10, 150);
	Pianta p2("Carpino", "albero inutile", 15, 200);
	for (int i = 0; i < 1006; i++) {
		p1.cresci();
		p2.cresci();
		// cin.get();
	}
	cout << "NUMERO DI SEMI RACCOLTI: " << p1.semi().size() << endl;
	cout << "NUMERO DI SEMI RACCOLTI: " << p2.semi().size() << endl;
	return 0;
}