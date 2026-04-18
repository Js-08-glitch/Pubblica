#pragma once
#include <string>
#include "Restauro.h"
using namespace std;

#define MAX_DIM 5

class Libro {
private:
	string tit;
	string aut;
	string anpub;
	Restauro r[MAX_DIM];
	int i = 0;

public:
	Libro() = default;

	// TODO: controllo invariante nel costruttore e nei setter
	Libro(const string& titolo, const string& autore, const string& anno)
		: tit(titolo), aut(autore), anpub(anno) { }

	string getTitolo() const { return tit;   }
	string getAutore() const { return aut;   }
	string getAnno()   const { return anpub; }

	Restauro getRestauro(int idx) const {
		if (0 <= idx && idx < MAX_DIM) return r[idx];
		return {}; // restauro vuoto
	}

	int getNumeroRestauri() const { return i; }
	
	void setTitolo(const string& titolo) { tit = titolo; }
	void setAutore(const string& autore) { aut = autore; }
	void setAnno(const string& anno)     { anpub = anno; }

	void add_r(const Restauro& r) {
		if (i < MAX_DIM)
			this->r[i] = r;
	}
};