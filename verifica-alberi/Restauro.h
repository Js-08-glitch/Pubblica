#pragma once
#include <string>
using namespace std;

class Restauro {
private:
	string restauratore;
	string data_inizio;
	string data_fine;

public:
	Restauro() = default;

	// TODO: controllo invariante nel costruttore e nei setter
	Restauro(const string& restauratore, const string& data_inizio, const string& data_fine)
		: restauratore(restauratore), data_inizio(data_inizio), data_fine(data_fine) {}

	string getRestauratore() const { return restauratore; }
	string getDataInizio()   const { return data_inizio;  }
	string getDataFine()     const { return data_fine;    }
	
	void setRestauratore(const string& restauratore) { this->restauratore = restauratore; }
	void setDataInizio(const string& data_inizio)    { this->data_inizio = data_inizio;   }
	void setDataFine(const string& data_fine)        { this->data_fine = data_fine;       }

};