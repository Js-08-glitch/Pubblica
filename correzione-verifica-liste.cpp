struct nodo { // richiesta
	char risorsa;
	int priorita;
	float t_attesa;
	float t_utilizzo;
	nodo* next;
};

struct ind_max {
	nodo* indirizzo;
	ind_max* next;
	ind_max* prec; // se doppiamente concatenata
};

// var globali
nodo *start = nullptr, *end = nullptr;
ind_max* start_max = nullptr;
ind_max* tempo_max = nullptr; // contiene tutti i nodi che hanno aspettato troppo, indipendentemente da tipo di risorsa utilizzata
int soglia_tempo_attesa;
int tempo;

void ins_testa(char risorsa, int priorita, float t_attesa, float t_utilizzo)
{
	nodo* nuovo = new nodo();
	nuovo->risorsa = risorsa;
	nuovo->priorita = risorsa;
	nuovo->t_attesa = t_attesa;
	nuovo->t_utilizzo = t_utilizzo;

	if (!start) end = nuovo;
	nuovo->next = start;
	start = nuovo;
}

void ins_testa_max(nodo* indirizzo, ind_max* start_max)
{
	ind_max* nuovo = new ind_max(); // con ()?!
	nuovo->indirizzo = indirizzo;

	nuovo->next = start_max;
	start_max = nuovo;
}

void cancella_lista_max()
{
	ind_max* temp;

	while (start_max) {
		temp = start_max->next;
		delete start_max;
		start_max = temp;
	}
}

bool lista_vuota()
{
	if (!start) return true;
	else return false;
}

// va ad inserire in testa il nodo contenente il massimo
int ricerca_max(char risorsacercata)
{
	/*
	 -1 lista vuota
	  0 tutto ok
	*/
	if (lista_vuota())
		return -1;

	nodo* temp = start;
	int max = -1;

	while (temp) {
		if (temp->risorsa == risorsacercata) {
			if (temp->priorita >= max)
			{
				if (temp->priorita == max)
					ins_testa_max(temp, start_max);
				else {
					max = temp->priorita;
					cancella_lista_max();
					ins_testa_max(temp, start_max);
				}
			}

			if (temp->t_attesa >= soglia_tempo_attesa) {
				ins_testa_max(temp, tempo_max); // ma su un'altra lista!
			}
		}

		temp = temp->next;
	}
}

// inserire in coda
void ins_coda(ind_max* start_coda, ind_max* start_max)  // start_coda è punto ingresso della coda specifica per ogni risorsa, start_max è punto ingresso lista che contiene tutti i massimi
{
	ind_max* temp = start_max, *temp1;
	while (temp)
	{
		// TODO: estrazione nodo dalla lista di attesa
		temp1 = temp->next;
		temp->next = start_coda;
		start_coda->prec = temp; // se doppiamente concatenata
		start_coda = temp;
		temp = temp1;
	}
}

void estrazione_coda(ind_max* start_coda)  // start_coda è punto ingresso della coda specifica per ogni risorsa, start_max è punto ingresso lista che contiene tutti i massimi
{
	while (tempo)
		tempo--;

	// vado all'ultimo nodo
	ind_max* temp = start_coda;
	if (!temp) return;
	while (temp->next)
		temp = temp->next;

	tempo = temp->indirizzo->t_utilizzo;

	temp->prec->next = nullptr; // se doppiamente concatenata

	delete temp;
}

int main()
{
	ind_max *temp_a, *temp_b, *temp_c;
	
	// TODO: inserire elementi in lista con aggiornamento tempi di attesa

	if (!lista_vuota()) {
		ricerca_max('A');
		temp_a = start_max;

		ricerca_max('B');
		temp_b = start_max;

		ricerca_max('C');
		temp_c = start_max;
	}
}