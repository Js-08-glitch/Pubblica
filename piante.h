#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

class Seme
{
protected:
	std::string nome;
	std::string cat; // posso confrontare alberi della stessa categoria (es. albero da frutto, infestante) in base ad altezza, produzione, ...
	int _eta = 0; // età in giorni
	int tGermoglio;  // tempo in giorni per germogliare e diventare pianta

public:
	Seme(const std::string& nome, const std::string& cat, int tempo)
		: nome(nome), cat(cat), tGermoglio(tempo) {}
	virtual ~Seme() = default;
};

class Pianta : public Seme
{
private:
	int MAX_ALTEZZA;
	int viva = true;
	bool fiori = false;
	int frutti = false;
	int _raccolto = 0;
	int _altezza = 0;

public:
	Pianta(const std::string& nome, const std::string& cat, int tempo, int max)
		: Seme(nome, cat, tempo), MAX_ALTEZZA(max) { srand(time(NULL)); }
	~Pianta() = default;

	void fiorisci()  { fiori = true;  }
	void sfiorisci() { fiori = false; }
	
	void produci()  { fiori = false; frutti += rand() % 5; } // da 0 a 4 frutti al giorno
	void raccogli() { _raccolto += frutti; frutti = 0; }

	bool isViva()   const { return viva;      }
	bool haFiori()  const { return fiori;     }
	bool haFrutti() const { return frutti;    }
	int eta()       const { return _eta;      }
	int altezza()   const { return _altezza;  }
	int raccolto()  const { return _raccolto; }

	// SIMULA IL CICLO DI VITA
	void cresci()
	{
		std::cout << *this << std::endl;

		if (!viva) return;

		_eta++;
		if (_eta < tGermoglio) return;
		if (_eta > 1000) { sradica(); return; }
		
		_altezza = std::min(_eta / 5, MAX_ALTEZZA); // ogni 5 giorni cresce di 1 cm fino a un massimo di MAX_ALTEZZA centimetri
		if (_altezza > 500) pota();
		
		int cur = _eta % 365; // ciclo di fiori e frutti di durata di un anno
		if      (25 < cur && cur < 37) fiorisci();
		else if (37 < cur && cur < 50) produci();

		// ogni 15 giorni raccogli i frutti
		if (cur % 15 == 0) raccogli();
	}

	void pota() { if (_altezza > 0) _altezza--; }
	// void trapianta() {}
	// void innesta() {}
	void sradica() { viva = false; fiori = false; frutti = 0; }

	std::vector<Seme> semi() {
		std::vector<Seme> seeds;
		for (int i = 0; i < _raccolto * 10; i++) // 10 semi a frutto
			seeds.push_back({ nome, cat, tGermoglio });
		_raccolto = 0;
		return seeds;
	}

	friend std::ostream& operator<<(std::ostream& os, const Pianta& p);
	friend bool operator<(const Pianta& lhs, const Pianta& rhs);
	friend bool operator==(const Pianta& lhs, const Pianta& rhs);
};

inline std::ostream& operator<<(std::ostream& os, const Pianta& p) {
	return os << p.nome                                             << ", "
	          << p.cat                                              << ", "
	          << ((p.viva) ? "viva" : "morta")                      << ", "
	          << p._eta << " giorni"                                << ", "
	          << ((p._eta > p.tGermoglio) ? "pianta" : "germoglio") << ", "
	          << ((p.fiori) ? "con fiori" : "senza fiori")          << ", "
	          << p.frutti << " frutti"                              << ", "
	          << p._raccolto << " frutti totali raccolti"           << ", "
	          << "altezza " << p._altezza << "/" << p.MAX_ALTEZZA << " cm";
}

inline bool operator<(const Pianta& lhs, const Pianta& rhs) {
	return (lhs._altezza < rhs._altezza);
}
inline bool operator>(const Pianta& lhs, const Pianta& rhs) {
	return (rhs < lhs);
}
inline bool operator<=(const Pianta& lhs, const Pianta& rhs) {
	return !(lhs > rhs);
}
inline bool operator>=(const Pianta& lhs, const Pianta& rhs) {
	return !(lhs < rhs);
}
inline bool operator==(const Pianta& lhs, const Pianta& rhs) {
	return (lhs._altezza == rhs._altezza);
}
inline bool operator!=(const Pianta& lhs, const Pianta& rhs) {
	return !(lhs == rhs);
}