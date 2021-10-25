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

int Umetni(Position p);
int UmetniNaKraj(Position p);
int UnesiPodatke(Position p);
int Ispis(Position p);
int Izbrisi(Position p, char* prezime);

Position PronadiPosljedni(Position p);
Position Pronadi(Position p);
Position PronadiPrethodni(Position p, char* prezime);


int UnesiPodatke(Position p) {
	printf("Upisi ime: ");
	scanf("%s", p->ime);
	printf("Upisi prezime: ");
	scanf("%s", p->prezime);
	printf("Upisi godinu rodenja: ");
	scanf("%d", &p->god_rodenja);
	return 0;
};
int Umetni(Position p) {
	Position q = NULL;
	q = (Position)malloc(sizeof(Student));
	if (q == NULL) {
		return -1;
	}
	UnesiPodatke(q);
	q->next = p->next;
	p->next = q;
	return 0;
};

int UmetniNaKraj(Position p) {
	Position last = NULL;
	last = PronadiPosljedni(p);
	Umetni(last);
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

int Izbrisi(Position p) {
	Position prev = NULL;
	Position curr = NULL;

	char prezime[MAX_LENGTH];
	printf("\n Unesi prezime koje zelis maknuti: ");
	scanf("%s", prezime);
	prev = PronadiPrethodni(p, prezime);
	if (prev == NULL) {
		return -1;
	};
	curr = prev->next;
	prev->next = prev->next->next;
	free(curr);
	printf("\nElement uspjesno izbrisan\n");
	return 0;
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

Position Pronadi(Position p) {
	int i = 0;
	char prezime[MAX_LENGTH];
	printf("\n Unesi prezime koje zelis naci: ");
	scanf("%s", &prezime);
	while (p != NULL && strcmp(p->prezime, prezime) != 0) {
		p = p->next;
		i++;
	}

	if (p == NULL) {
		printf("Takav element ne postoji");
	}
	printf("\nElement pronaden na %d poziciji\n", i + 1);
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

	printf("DRUGI ZADATAK: LISTE\n");
	while (isActive) {
		printf("1. Umetni na pocetak liste\n2. Umetni na kraj liste\n3. Pronadi odredeni element po prezimenu\n"
			"4. Izbrisi odredeni element po prezimenu \n5. Ispisi listu\n6. Kraj unosa\n");
		scanf(" %c", &ch);
		switch (ch) {
		case '1':  Umetni(head);
			break;
		case '2': UmetniNaKraj(head);
			break;
		case '3': Pronadi(head->next);
			break;
		case '4': Izbrisi(head->next);
			break;
		case '5': Ispis(head->next);
			break;
		case '6': isActive = 0;
			break;
		}
		printf("\n");
	}

	return 0;
};