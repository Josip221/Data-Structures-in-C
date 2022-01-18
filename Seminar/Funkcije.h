#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SIZE 30
#define MAX_HASH_TABLE_SIZE 11
#define MAX_BROJ_POZIVA 1000

typedef struct _Datum {
	int godina;
	int mjesec;
	int dan;
} Datum;

typedef struct _BrojPoziva {
	int broj_poziva;
	char pozivni_broj[MAX_STRING_SIZE];
} BrojPoziva;

struct _Kontakt;
typedef struct _Kontakt* PozicijaKontakt;
typedef struct _Kontakt{
	char pozivni_broj[MAX_STRING_SIZE];
	char ime[MAX_STRING_SIZE];
	char prezime[MAX_STRING_SIZE];
	PozicijaKontakt prethodni;
	PozicijaKontakt sljedeci;
} Kontakt;

struct _CvorPoziv;
typedef struct _CvorPoziv* PozicijaStablo;
typedef struct _CvorPoziv {
	int id_poziv;
	int trajanje_poziva;
 	Datum datum;
 	PozicijaKontakt kontakt;
	PozicijaStablo lijevo;
	PozicijaStablo desno;
} CvorPoziv;

struct _HashT;
typedef struct _HashT* HashTab;
typedef struct _HashT{
	int ukupni_broj_poziva;
	PozicijaStablo* headPoziv;
} HashT;

struct _Lista;
typedef struct _Lista* PozicijaLista;
typedef struct _Lista{
	PozicijaStablo poziv;
	PozicijaLista sljedeci;
} Lista;

//Opcije
int OpcijaDodajNoviKontakt(PozicijaKontakt);
int OpcijaNapraviPoziv(PozicijaKontakt, HashTab);
int OpcijaIzmjeniKontakt(PozicijaKontakt);
int OpcijaIzbrisiKontakt(PozicijaKontakt);
int OpcijaDatoteka(PozicijaKontakt, HashTab, PozicijaLista);

//Kontakt funkcije
PozicijaKontakt StvoriKontakt();
PozicijaKontakt NadiKontaktPoBroju(PozicijaKontakt, char*);
int DodajKontaktUListu(PozicijaKontakt, char*, char*, char*);
int IzbrisiKontaktIzListe(PozicijaKontakt);
int AzurirajKontaktIzListe(PozicijaKontakt, PozicijaKontakt);
int ProcitajKontaktDatoteku(char *, PozicijaKontakt);
int PrintKontaktLista(PozicijaKontakt);
int ProvjeriDaliPostojiVecBroj(char* , PozicijaKontakt);
int SpremiKontakte(PozicijaKontakt, char*);

//Poziv funkcije 
HashTab SvoriHashTab();
PozicijaStablo NadiCvorPoID(PozicijaStablo, int);
int DodajUHashTablicu(HashTab, PozicijaStablo);
PozicijaStablo StvoriCvorStabla(PozicijaKontakt);
PozicijaStablo DodajCvorUStablo(PozicijaStablo, PozicijaStablo);
int PrintHash(HashTab);
int StabloUListu(PozicijaStablo, PozicijaLista);
int PrintPozivLista(PozicijaLista);
int HashTablicuUListu(HashTab, PozicijaLista);
int DodajPozivUListu(PozicijaStablo, PozicijaLista);
int SpremiStablo(PozicijaStablo, char*);

//Pomocne funkcije
int PrintPhoneBookMenu();
int BrojIspravan(char*);
int StvoriVrijemeTrajanjaPoziva();
int RandomBroj(int, int);
int MenuStop();
int PrintDatotekaMenu();
int PrintBorder();
int OdstraniS(char*);
int StringBezSlova();
int PrintVrijeme(int);
int PrintImePrezimeBroj(PozicijaKontakt);

//Datum funkcije
Datum StvoriRandomDatum();
int UsporediDatume(Datum, Datum);
int PrintDatum(Datum);
int ProvjeriDatum(char*);
Datum PretvoriStringUDatum(char*);

//Pretrazivanja
int KolikoPutaJeKontaktNazvan(char* , PozicijaLista);
int NajduljiPoziv(PozicijaLista);
int UkupnoVrijemePoziva(PozicijaLista);
int NadiPoziveUVremenskomRazdoblju(PozicijaLista, Datum , Datum );
int ObavljeniPozivi(PozicijaLista, PozicijaKontakt);

//Oslobadanje memorije
int OslobodiKontakte(PozicijaKontakt);
int OslobodiPozivListu(PozicijaLista);
int OslobodiStablo(PozicijaStablo);
int OslobodiHashTablicu(HashTab);

#endif