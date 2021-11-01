#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LENGTH 30

struct _Student;
typedef struct _Student* Position;
typedef struct _Student {
	char ime[MAX_LENGTH];
	char prezime[MAX_LENGTH];
	int god_rodenja;

	Position next;
} Student;

int UmetniNakon(Position, char*, Student);
int UmetniPrije(Position, char*, Student);
int Sortiraj(Position);

int UpisiDatoteku(char* , Position);
int ProcitajDatoteku(char *, Position);

int Umetni(Position, Student);
int Ispis(Position);

Position PronadiPosljedni(Position);
Position Pronadi(Position);
Position PronadiPrethodni(Position, char*);

int UpisiDatoteku(char* ime, Position p) {
	FILE* fp = fopen(ime, "w");
	if (fp == NULL)
		return -2;
	for (; p != NULL; p = p->next) {
		fprintf(fp, "%s %s %d\n", p->ime, p->prezime, p->god_rodenja);
	}
	fclose(fp);
}

int ProcitajDatoteku(char* ime, Position p) {
	FILE* fp = fopen(ime, "r");
	if (fp == NULL)
		return -2;
	Student temp;
	while (fscanf(fp, "%s %s %d", temp.ime, temp.prezime, &temp.god_rodenja) != EOF) {
		Position q = NULL;
		q = (Position)malloc(sizeof(Student));
		if (q == NULL) {
			return -1;
		}
		if (p == NULL)
			return -1;
		strcpy(q->ime, temp.ime);
		strcpy(q->prezime, temp.prezime);
		q->god_rodenja = temp.god_rodenja;
		p->next = q;
		p = p->next;

	}
	fclose(fp);
}

int Sortiraj(Position p) {
	Position a = NULL, b = NULL, prev = NULL, kraj = NULL;
	for (a = p; a->next != kraj;) {
		prev = a;
		for (b = a->next; b->next != kraj; b = b->next) {
			if (strcmp(b->prezime, b->next->prezime) > 0) {
				Position tmp = b->next;
				prev->next = tmp;
				b->next = tmp->next;
				tmp->next = b;
				b = tmp;
			}
			prev = b;

		}
		kraj = b;
	}
	printf("\nLista sortirana\n");
}

int UmetniNakon(Position p, char* prezime, Student st) {
	Position prev = NULL;
	prev = Pronadi(p, prezime);
	if (prev == NULL)
		return -1;
	Umetni(prev, st);
	return 0;
}

int UmetniPrije(Position p, char* prezime, Student st) {
	Position prevp = NULL;
	prevp = PronadiPrethodni(p, prezime);
	if (prevp == NULL)
		return -1;
	Umetni(prevp, st);
	return 0;
}


int Umetni(Position p, Student st) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Student));
	if (q == NULL) {
		return -1;
	}
	strcpy(q->ime, st.ime);
	strcpy(q->prezime, st.prezime);
	q->god_rodenja = st.god_rodenja;

	q->next = p->next;
	p->next = q;
	return 0;
};


Position PronadiPosljedni(Position p) {
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
};

int Ispis(Position p) {
	int i = 0;
	if (p == NULL) {
		printf("Nema elementa, lista je prazna!");
		return -1;
	}
	else {
		printf("Ispis liste: \n");
		printf("RED\t IME\tPREZIME\t GOD RODENJA\n");
		while (!p == NULL) {
			printf("%d\t%s\t %s\t %d\n", i + 1, p->ime, p->prezime, p->god_rodenja);
			p = p->next;
			i++;
		}
		printf("\n");
	}
};


Position PronadiPrethodni(Position p, char* prezime) {
	Position prev = NULL, curr = NULL;
	prev = p;
	curr = prev->next;
	while (curr != NULL && strcmp(curr->prezime, prezime) != 0) {
		prev = curr;
		curr = prev->next;
	}
	if (curr = NULL) {
		return -1;
	}
	return prev;
};

Position Pronadi(Position p, char* prezime) {
	while (p != NULL && strcmp(p->prezime, prezime) != 0) {
		p = p->next;
	}

	if (p == NULL) {
		printf("Takav element ne postoji");
	}
	return p;
};

int main() {
	char ch;
	int isActive = 1;
	Position head = NULL;
	head = (Position)malloc(sizeof(Student));
	if (head == NULL) {
		return -1;
	}
	head->next = NULL;


	//Pocetni studenti u listi
	Student st1, st2, st3;
	strcpy(st1.ime, "1A");
	strcpy(st1.prezime, "1B");
	st1.god_rodenja = 2000;

	strcpy(st2.ime, "2A");
	strcpy(st2.prezime, "2B");
	st2.god_rodenja = 2001;

	strcpy(st3.ime, "3A");
	strcpy(st3.prezime, "3B");
	st3.god_rodenja = 2002;

	Umetni(head, st2);
	Umetni(head, st1);
	Umetni(head, st3);

	//Student za ubacivanje kroz komande
	Student st4;

	strcpy(st4.ime, "4A");
	strcpy(st4.prezime, "4B");
	st4.god_rodenja = 2004;

	while (isActive) {
		printf("1. Dodaj element iza odredenog elementa\n2. Dodaj element ispred odredenog elementa \n3. Sortiraj listu po po prezimenu"
			"\n4. Upisuje listu u datoteku\n5. Cita listu iz datoteke \n6. Ispis liste\n7. Kraj unosa\n");

		scanf(" %c", &ch);
		switch (ch) {
			case '1':
				UmetniNakon(head, "2B", st4);
				break;
			case '2':
				UmetniPrije(head, "2B", st4);
				break;
			case '3':
				Sortiraj(head);
				break;
			case '4': 
				UpisiDatoteku("out.txt", head->next);
				break;
			case '5': 
				ProcitajDatoteku("in.txt", head);
				break;
			case '6': Ispis(head->next);
				break;
			case '7': isActive = 0;
				printf("Kraj unosa");
				break;
			default: printf("Probajte opet\n");
				break;
		}
		printf("\n");
	}

	return 0;
};
