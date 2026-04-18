#pragma once
#include <fstream>
#include <string>
#include <algorithm> // serve per std::fill
#include "Libro.h"
using namespace std;

class FileManager {
private:
    fstream file;
    string fileName;

    // Libro e Restauro contengono stringhe, che al loro interno contengono puntatori: se provo a scriverle e leggerle così come sono non funzionerà niente
    void serializzaLibro(const Libro & l);
    Libro deserializzaLibro();
    void serializzaRestauro(const Restauro& r);
    Restauro deserializzaRestauro();

public:
    FileManager(const string& fileName);
    ~FileManager();
    
    bool isOpen() const { return (bool)file; }

    int aggiungi(const Libro& nuovo);
    int aggiorna(int posVecchio, const Libro& nuovo);
    void cancella(int posVecchio);
    Libro restituisci(int pos);
};

FileManager::FileManager(const string& fileName) : fileName(fileName)
{
    // Creo il file se non esiste, lo sovrascrivo se esiste già
    // (altrimenti dovrei salvare anche l'albero da qualche parte)
    ofstream out(fileName);
    if (!out) return; // errore
    out.close();

    // Ora sono sicuro che il file esiste e posso aprirlo in lettura/scrittura
    file.open(fileName, ios::in | ios::out | ios::binary);
    if (!file) return; // ci vorrebbe un'eccezione
}

FileManager::~FileManager()
{
    if (!file) return;
    file.close();
}

int FileManager::aggiungi(const Libro& nuovo)
{
    file.clear(); // reset dei flag di errore
    file.seekp(0, ios::end); // vai in fondo
    auto pos = file.tellp();
    serializzaLibro(nuovo);
    return pos;
}

int FileManager::aggiorna(int posVecchio, const Libro& nuovo)
{
    // Cancella il libro vecchio e aggiunge quello nuovo, restituendo la nuova posizione
    cancella(posVecchio);
    return aggiungi(nuovo);
}

void FileManager::cancella(int posVecchio)
{
    // Aggiorna con un libro non valido i cui campi hanno la stessa lunghezza dell'originale ma sono riempiti con asterischi
    Libro originale = restituisci(posVecchio);
    string t(originale.getTitolo().length(), '*');
    string a(originale.getAutore().length(), '*');
    string ap(originale.getAnno().length(), '*');
    Libro non_valido(t, a, ap);
    
    // Sovrascrivi
    file.clear(); // reset dei flag di errore
    file.seekp(posVecchio, ios::beg); // vai in fondo
    serializzaLibro(non_valido);
}

Libro FileManager::restituisci(int pos)
{
    file.clear(); // reset dei flag di errore
    file.seekg(pos, ios::beg);
    return deserializzaLibro();
}

void FileManager::serializzaLibro(const Libro& l)
{
    // Serializza titolo
    string titolo = l.getTitolo();
    size_t len = titolo.size();
    file.write((const char*)&len, sizeof(len));
    file.write(titolo.data(), len); // data() restituisce già un const char *

    // Serializza autore
    string autore = l.getAutore();
    len = autore.size();
    file.write((const char*)&len, sizeof(len));
    file.write(autore.data(), len);

    // Serializza anno
    string anno = l.getAnno();
    len = anno.size();
    file.write((const char*)&len, sizeof(len));
    file.write(anno.data(), len);

    // Serializza i restauri
    len = l.getNumeroRestauri();
    file.write((const char*)&len, sizeof(len));
    for (int i = 0; i < len; i++)
        serializzaRestauro(l.getRestauro(i));
}

Libro FileManager::deserializzaLibro()
{
    string titolo, autore, anno;
    size_t len;

    // Deserializza titolo
    file.read((char*)&len, sizeof(len));
    titolo.resize(len);
    file.read((char*)titolo.data(), len);

    // Deserializza autore
    file.read((char*)&len, sizeof(len));
    autore.resize(len);
    file.read((char*)autore.data(), len);

    // Deserializza anno
    file.read((char*)&len, sizeof(len));
    anno.resize(len);
    file.read((char*)anno.data(), len);

    Libro l(titolo, autore, anno);

    // Deserializza i restauri
    file.read((char*)&len, sizeof(len));
    for (int i = 0; i < len; i++)
        l.add_r(deserializzaRestauro());

    return l;
}

void FileManager::serializzaRestauro(const Restauro& r)
{
    // Serializza restauratore
    string restauratore = r.getRestauratore();
    size_t len = restauratore.size();
    file.write((const char*)&len, sizeof(len));
    file.write(restauratore.data(), len);

    // Serializza data di inizio
    string data_inizio = r.getDataInizio();
    len = data_inizio.size();
    file.write((const char*)&len, sizeof(len));
    file.write(data_inizio.data(), len);

    // Serializza data di fine
    string data_fine = r.getDataFine();
    len = data_fine.size();
    file.write((const char*)&len, sizeof(len));
    file.write(data_fine.data(), len);
}

Restauro FileManager::deserializzaRestauro()
{
    string restauratore, data_inizio, data_fine;
    size_t len;

    // Deserializza titolo
    file.read((char*)&len, sizeof(len));
    restauratore.resize(len);
    file.read((char*)restauratore.data(), len);

    // Deserializza autore
    file.read((char*)&len, sizeof(len));
    data_inizio.resize(len);
    file.read((char*)data_inizio.data(), len);

    // Deserializza anno
    file.read((char*)&len, sizeof(len));
    data_fine.resize(len);
    file.read((char*)data_fine.data(), len);

    return { restauratore, data_inizio, data_fine };
}