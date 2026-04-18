#include <iostream>
#include <vector>
#include "Libro.h"
#include "Restauro.h"
#include "Albero.h"
#include "FileManager.h"
using namespace std;

// HELPER FUNCTION
Libro inputLibro() { // DOVREBBE OCCUPARSENE IL GRUPPO "LIBRO"
    string t, a, ap;
    cout << "Inserisci il titolo: ";
    cin >> t;
    cout << "Inserisci l'autore: ";
    cin >> a;
    cout << "Inserisci l'anno di pubblicazione: ";
    cin >> ap;
    return { t, a, ap };
}

// OVERLOAD OPERATORE << PER LA STAMPA DEL LIBRO
ostream& operator<<(ostream& os, const Libro& l) { // DOVREBBE OCCUPARSENE IL GRUPPO "LIBRO"
    return os << "LIBRO: " << l.getTitolo() << " di " << l.getAutore() << ", anno " << l.getAnno();
}

int main()
{
    Albero indice;

    FileManager file("database.db");
    if (!file.isOpen()) {
        cout << "[ERR] Impossibile aprire il file!" << endl;
        return -1;
    }
    
    bool running = true;
    while (running) {
        cout << "- - - - - - - - - - - - - - -\n";
        cout << "OPERAZIONI DISPONIBILI\n";
        cout << "1) aggiungi un nuovo libro (a/A)\n";
        cout << "2) aggiorna un libro esistente (u/U)\n";
        cout << "3) cancella un libro (d/D)\n";
        cout << "4) visualizza i dati di un libro specifico (s/S)\n";
        cout << "5) esci dal programma (q/Q)\n";
        cout << "Scegli un'opzione: ";
        
        string scelta;
        cin >> scelta;
        
        switch (scelta[0]) {
            case 'a': case 'A': { // add
                Libro l = inputLibro();
                int pos = indice.ric(l.getTitolo());
                if (pos == -1) indice.add(l.getTitolo(), file.aggiungi(l));
                else cout << "[INFO] Il libro e' gia' presente, per modificarlo usare l'opzione u/U!" << endl;
                break;
            }
        
            case 'u': case 'U': { // update
                Libro l = inputLibro();
                int pos = indice.ric(l.getTitolo());
                if (pos == -1) cout << "[INFO] Il libro non e' gia' presente, per inserirlo usare l'opzione a/A!" << endl;
                else {
                    indice.canc(l.getTitolo()); // rimuovi la vecchia voce dall'indice
                    indice.add(l.getTitolo(), file.aggiorna(pos, l)); // aggiungi la nuova voce nell'indice
                }
                break;
            }
        
            case 'd': case 'D': { // delete
                string title;
                cout << "Inserire il titolo del libro da cancellare: ";
                cin >> title;
                
                int pos = indice.ric(title);
                if (pos != -1) {
                    indice.canc(title);
                    file.cancella(pos);
                }
                break;
            }
        
            case 's': case 'S': { // show
                string title;
                cout << "Inserire il titolo del libro da visualizzare: ";
                cin >> title;
            
                int pos = indice.ric(title);
                if (pos != -1) cout << file.restituisci(pos) << endl;
                else cout << "[INFO] Il libro cercato non esiste ancora" << endl;
                break;
            }
        
            case 'q': case 'Q': { // quit
                cout << "[INFO] Uscita..." << endl;
                running = false;
                break;
            }
        
            default:
                cout << "[ERR] Opzione inesistente!" << endl;
        }
    }

    return 0;
}