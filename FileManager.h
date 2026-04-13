#include <fstream>

class FileManager {
private:
    string fileName;
    fstream file = nullptr;

public:
    FileManager(const string& fileName) : fileName(fileName) {
        file.open(fileName, ios::in|ios::out|ios::binary);
        if (!file) return; // ci vorrebbe un'eccezione
    }

    ~FileManager() {
        if (!file) return;
        file.close();
    }

    int aggiungi(const Libro& l) { //, const Tree& idx)
        file.seekp(0, ios::end); // vai alla fine
        return aggiorna(l, file.tellp());
    }

    // KING
    int aggiorna(const Libro& l, int pos) { //, const Tree& idx)
        file.seekp(pos, ios::beg);
        file.write((const char*)&l, sizeof(Libro));
        return pos;
    }

    void cancella(int pos) {
        Libro err{"*"};
        aggiorna(err, pos);
    }

    Libro leggi(int pos) const { //, const Tree& idx)
        Libro l;
        f.seekg(pos, ios::begin);
        file.read((char*)&l, sizeof(Libro));
        return l;
    }
};





// il main usa entrambi
int main() {
    int pos = albero.ric();
    if (pos == -1)
        albero.add(titolo, file.aggiungi(libro));
    else
        file.aggiorna(libro, pos);
}

// indice controlla file
albero.add(libro) {
    int pos = albero.ric();
    if (pos == -1) {
        pos = file.aggiungi(libro);
        nuovo_nodo(libro.titolo, pos);
    }
    else file.aggiorna(libro, pos);
}

// file controlla indice
file.aggiungi(libro, albero) {
    int pos = albero.ric(libro);
    if (pos == -1) {
        pos = aggiungi(libro);
        albero.nuovo_nodo(libro.titolo, pos);
    }
    else {
        file.aggiorna(libro, pos);
        // non agisco sull'albero
    }
}