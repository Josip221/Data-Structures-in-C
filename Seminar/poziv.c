#include "Funkcije.h"
 
int hashFunkcija(int key){
	return key % MAX_HASH_TABLE_SIZE;
}

PozicijaStablo StvoriCvorStabla(PozicijaKontakt kontakt){
	PozicijaStablo q = malloc(sizeof(CvorPoziv));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->kontakt = kontakt;
	q->id_poziv = 0;
	q->datum = StvoriRandomDatum();
	q->trajanje_poziva = StvoriVrijemeTrajanjaPoziva();
	q->lijevo = NULL;
	q->desno = NULL;
	return q;
}

HashTab SvoriHashTab(){
	HashTab hash = NULL;
	int i = 0;

	hash = (HashTab) malloc(sizeof(HashT));
	if(hash == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	hash->headPoziv = (PozicijaStablo*) malloc(sizeof(PozicijaStablo) * MAX_HASH_TABLE_SIZE);
	if(hash->headPoziv == NULL){
		printf("Greska pri alociranju memorije");
		return NULL;
	}

	for(i = 0; i < MAX_HASH_TABLE_SIZE; i++){
		hash->headPoziv[i] = NULL;	
	}
	return hash;
}

int DodajUHashTablicu(HashTab hashTable,  PozicijaStablo q){
	int index = 0, isActive = 0;
	PozicijaStablo korijen = NULL, tmp = NULL;

	q->id_poziv = RandomBroj(5000, 1);
	index = hashFunkcija(q->id_poziv);
	korijen = hashTable->headPoziv[index];

	if(korijen == NULL){
		hashTable->headPoziv[index] = q;
		printf("Uspjesno dodan poziv: ");
		PrintDatum(q->datum);
		printf(" %dm %ds", q->trajanje_poziva / 60, q->trajanje_poziva % 60);
		printf(" %s %s %s\n", q->kontakt->ime, q->kontakt->prezime, q->kontakt->pozivni_broj);
	}
	else{
		tmp = NadiCvorPoID(korijen, hashFunkcija(q->id_poziv));
		if(tmp == NULL){
				//ne postoji poziv s istim id-om, dodaj
				korijen = DodajCvorUStablo(korijen, q);
				printf("Uspjesno dodan poziv: ");
				PrintDatum(korijen->datum);
				printf(" %dm %ds", q->trajanje_poziva / 60, q->trajanje_poziva % 60);
				printf(" %s %s %s\n", q->kontakt->ime, q->kontakt->prezime, q->kontakt->pozivni_broj);
		}
		else{
				//vec postoji poziv s ovim id-om, probaj ponovno s novim id
				DodajUHashTablicu(hashTable, q);
		}
	}
	return EXIT_SUCCESS;
}

PozicijaStablo NadiCvorPoID(PozicijaStablo p, int id_poziv){
	if(p == NULL){
		return NULL;
	}
	else if(p->id_poziv == id_poziv){
		return p;
	}
	else if(p->id_poziv > id_poziv){
		return NadiCvorPoID(p->lijevo, id_poziv);
	}
	else if(p->id_poziv < id_poziv){
		return NadiCvorPoID(p->desno, id_poziv);
	}
}

PozicijaStablo DodajCvorUStablo(PozicijaStablo p, PozicijaStablo q){
	if(p == NULL){
		p = q;
	}
	else{
		if(UsporediDatume(q->datum, p->datum) > 0){
			p->desno = DodajCvorUStablo(p->desno, q);
		}
		if(UsporediDatume(q->datum, p->datum) < 0){
			p->lijevo = DodajCvorUStablo(p->lijevo, q);
		}
	}
	return p;
}

//
// Poziv lista funkcije
//


PozicijaLista StvoriClanListe(){
	PozicijaLista q = NULL;
	q = (PozicijaLista) malloc(sizeof(Lista));
	if(!q){
		printf("Greska pri alociranju memorije");
		return NULL;
	}
	q->poziv = NULL;
	q->sljedeci = NULL;
	return q;
}

int HashTablicuUListu(HashTab hashTable, PozicijaLista headPozivLista){
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++){
		StabloUListu(hashTable->headPoziv[i], headPozivLista);
	}
	return EXIT_SUCCESS;
}

int StabloUListu(PozicijaStablo p, PozicijaLista headPozivLista){
	if(p == NULL){
		return EXIT_FAILURE;
	}
	StabloUListu(p->lijevo, headPozivLista);
	DodajPozivUListu(p, headPozivLista);
	StabloUListu(p->desno, headPozivLista);
	return EXIT_SUCCESS;
}

int DodajPozivUListu(PozicijaStablo poziv, PozicijaLista headPozivLista){
	PozicijaLista q = StvoriClanListe();
	q->poziv = poziv;
	while(headPozivLista->sljedeci !=NULL){
		if(q->poziv->id_poziv == headPozivLista->sljedeci->poziv->id_poziv ){
			//veci postoji poziv s tim id
			return EXIT_FAILURE;
		}
		if(UsporediDatume(q->poziv->datum, headPozivLista->sljedeci->poziv->datum) < 0){
			break;
		}
		headPozivLista = headPozivLista->sljedeci;
	}
	q->sljedeci = headPozivLista->sljedeci;
	headPozivLista->sljedeci = q;
	return EXIT_SUCCESS;
}

int PrintPozivLista(PozicijaLista headPozivLista){
	int i = 0;
	if(headPozivLista == NULL){
		printf("Lista poziva je trenutno prazna");
		return EXIT_SUCCESS;
	}
	printf("Lista poziva: \n");
	while(headPozivLista != NULL){
		PrintDatum(headPozivLista->poziv->datum);
		printf(" %dm %ds", headPozivLista->poziv->trajanje_poziva / 60, headPozivLista->poziv->trajanje_poziva % 60);
		printf(" %s %s %s\n", headPozivLista->poziv->kontakt->ime, headPozivLista->poziv->kontakt->prezime, headPozivLista->poziv->kontakt->pozivni_broj);
		headPozivLista = headPozivLista->sljedeci;
		i++;
	}
	printf("Prikazano %d poziva", i);
	MenuStop();
	return EXIT_SUCCESS;
}

int ProcitajPozivDatoteku(HashTab hashTab, PozicijaLista headPoziv, PozicijaKontakt headKontakt, char* imeDat){
	FILE* dat = NULL;
	PozicijaKontakt tmpKontakt = NULL;
	PozicijaStablo tmpStablo = NULL;
	char tmpDatum[MAX_STRING_SIZE] = {0}, tmpIme[MAX_STRING_SIZE] = {0}, tmpPrezime[MAX_STRING_SIZE] = {0}, tmpBroj[MAX_STRING_SIZE] = {0};
	char tmpVrijeme[MAX_STRING_SIZE] = {0};
	int i = 0;

	tmpKontakt = StvoriKontakt();
	dat = fopen(imeDat, "r");
	if(!dat){
		printf("Greska pri otvaranju poziv datoteke. Probajte ponovno");
		return EXIT_FAILURE;
	}
	while(!feof(dat)){
		fscanf(dat, "%s %s %s %s %s", tmpDatum, tmpVrijeme, tmpIme, tmpPrezime, tmpBroj);
		if(BrojIspravan(tmpBroj) == EXIT_SUCCESS && ProvjeriDatum(tmpDatum) == EXIT_SUCCESS){
			tmpKontakt = NadiKontaktPoBroju(headKontakt, tmpBroj);
			if(tmpKontakt == NULL){
				printf(" %dm %ds", OdstraniS(tmpVrijeme) / 60, OdstraniS(tmpVrijeme)  % 60);
				printf(" %s %s %s\n", tmpIme, tmpPrezime, tmpBroj);
				continue;
			}
			tmpStablo = StvoriCvorStabla(tmpKontakt);
			tmpStablo->trajanje_poziva = OdstraniS(tmpVrijeme);
			tmpStablo->datum = PretvoriStringUDatum(tmpDatum);
			DodajUHashTablicu(hashTab, tmpStablo);
			i++;
		}
		else{
			printf("Ne uspjesno dodan poziv: ");
			printf(" %dm %ds", OdstraniS(tmpVrijeme) / 60, OdstraniS(tmpVrijeme)  % 60);
			printf(" %s %s %s\n", tmpIme, tmpPrezime, tmpBroj);
		}
	}
	printf("Dodano %d poziva\n", i);
	fclose(dat);
	return EXIT_SUCCESS;
}

int SpremiPozive(HashTab hashTab, char* imeDat){
	int i = 0;
	for(i = 0; i < MAX_HASH_TABLE_SIZE; i++){
		SpremiStablo(hashTab->headPoziv[i], imeDat);
	}
	printf("Datoteka poziva uspjesno snimljena");
	return EXIT_SUCCESS;
}

int SpremiStablo(PozicijaStablo p, char* imeDat){
	FILE* dat = NULL;
	dat = fopen(imeDat, "a");
	if(!dat){
		printf("Greska pri otvaranju datoteke");
		return EXIT_FAILURE;
	}

	if(p == NULL){
		return EXIT_FAILURE;
	}
	fprintf(dat, "%d-%d-%d", p->datum.dan, p->datum.mjesec, p->datum.godina);
	fprintf(dat, "  %ds %s %s %s\n", p->trajanje_poziva, p->kontakt->ime, p->kontakt->prezime, p->kontakt->pozivni_broj);
	fclose(dat);
	SpremiStablo(p->lijevo, imeDat);
	SpremiStablo(p->desno, imeDat);
	return EXIT_SUCCESS;
}