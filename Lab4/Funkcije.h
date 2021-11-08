#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define MAX 100

struct Poly_;
typedef struct Poly_* Position;
typedef struct Poly_ {
	int baza;
	int exp;
	Position next;
} Poly;

int DodajClanSortirano(int, int, Position);
int Ispis(Position);
int OslobodiMemoriju(Position);
int IzbrisiNakon(Position);

int PomnoziPolinome(Position, Position, Position);
int ZbrojiPolinome(Position, Position, Position);
int ProcitajDatoteku(char *, char*, Position);
Position StvoriCvor();

#endif