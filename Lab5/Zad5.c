#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct _StogElement;
typedef struct _StogElement* Pozicija;
typedef struct _StogElement {
	double broj;
	Pozicija next;
} StogElement;

int IzracunajPostfixIzDat(char* imeDat, double* rezultat);
char* ProcitajDat(char* imeDat);
int StringUPostfix(char* buffer, double* rezultat);
int NadiRezultatUStogu(Pozicija head, double* rezultat);
Pozicija StvoriElementStoga(double broj);
int UnesiNakon(Pozicija head, Pozicija noviElementStoga);
int IsprintajStog(Pozicija prvi);
int Izbaci(Pozicija head, double* rezultat);
int IzbaciIObaviOperaciju(Pozicija head, char operacija, double* rezultat);

int main(){
	double rezultat = 0;

	
	if(IzracunajPostfixIzDat("postfiks.txt", &rezultat) == EXIT_SUCCESS){
		printf("Rezultat je: %0.1lf\n", rezultat);
	}
	
	return EXIT_SUCCESS;
}

int IzracunajPostfixIzDat(char* imeDat, double* rezultat){
	char* buffer = NULL;
	int status = 0;

	buffer = ProcitajDat(imeDat);
	if(buffer == NULL){
		return EXIT_FAILURE;
	}

	status = StringUPostfix(buffer, rezultat);
	if(status != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
char* ProcitajDat(char* imeDat){
	FILE* dat = NULL;
	int datDuljina = 0;
	char* buffer = NULL;;
	
	dat = fopen(imeDat, "rb");
	if(!dat){
		perror("Datoteka se nemoze otvoriti\n");
		return NULL;
	}

	fseek(dat, 0, SEEK_END);
	datDuljina = ftell(dat);

	buffer = (char*)calloc(datDuljina + 1, sizeof(char));
	if(!buffer){
		perror("Nemoguce alocirati memoriju!\n");
		return NULL;
	}

	rewind(dat);
	fread(buffer, sizeof(char), datDuljina, dat);
	printf("|%s|\n", buffer);
	fclose(dat);
	return buffer;
};
int StringUPostfix(char* buffer, double* rezultat){
	StogElement head = {.broj = 0, .next = NULL};
	char* trenutniBuffer = buffer;
	int status = 0;
	int numBytes = 0;
	char operacija = 0;
	double broj = 0.0;
	Pozicija noviElementStoga = NULL;

	while(strlen(trenutniBuffer) > 0){
		status = sscanf(trenutniBuffer, "%lf %n", &broj, &numBytes);
		if(status != 1){
			sscanf(trenutniBuffer, " %c %n", &operacija, &numBytes);
			status = IzbaciIObaviOperaciju(&head, operacija, rezultat);

			if(status != EXIT_SUCCESS){
				return EXIT_FAILURE;
			}
			broj = *rezultat;
		}
		noviElementStoga = StvoriElementStoga(broj);
		if(!noviElementStoga){
			return EXIT_FAILURE;
		}

		trenutniBuffer += numBytes;
		printf("|%s| <-->", trenutniBuffer);

		UnesiNakon(&head, noviElementStoga);
	}
	return NadiRezultatUStogu(&head, rezultat);
};
int NadiRezultatUStogu(Pozicija head, double* rezultat){
	int status = EXIT_SUCCESS;
	status = Izbaci(head, rezultat);

	if(status != EXIT_SUCCESS){
		return status;
	}

	if(head->next) {
		printf("Ne valjan postfix, probaj opet!\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
};
Pozicija StvoriElementStoga(double broj){
	Pozicija noviElementStoga = NULL;
	noviElementStoga = (Pozicija)malloc(sizeof(StogElement));
	if(!noviElementStoga){
		perror("Nemoguce alocirati memoriju!\n");
		return NULL;
	}

	noviElementStoga->broj = broj;
	noviElementStoga->next = NULL;
	return noviElementStoga;
};
int UnesiNakon(Pozicija head, Pozicija noviElementStoga){
	noviElementStoga->next = head->next;
	head->next = noviElementStoga;
	IsprintajStog(head->next);
	return EXIT_SUCCESS;
};
int IsprintajStog(Pozicija prvi){
	Pozicija temp = prvi;
	while(temp){
		printf(" %0.1lf", temp->broj);
		temp = temp->next;
	}
	printf("\n");
	return EXIT_SUCCESS;
};
int Izbaci(Pozicija head, double* rezultat){
	Pozicija zaIzbrisat = NULL;
	zaIzbrisat = head->next;
	if(!zaIzbrisat) {
		perror("Stog je prazan! Nista za izbaciti\n");
		return -1;
	}
	head->next = zaIzbrisat->next;
	*rezultat = zaIzbrisat->broj;
	free(zaIzbrisat);
	return EXIT_SUCCESS;
}
int IzbaciIObaviOperaciju(Pozicija head, char operacija, double* rezultat){
	double operand1 = 0;
	double operand2 = 0;
	int status1 = 0;
	int status2 = 0;

	status1 = Izbaci(head, &operand1);
	if(status1 != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	status2 = Izbaci(head, &operand2);
	if(status2 != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	switch (operacija)
    {
    case '+':
        *rezultat = operand2 + operand1;
        break;
    case '-':
        *rezultat = operand2 - operand1;
        break;
    case '*':
        *rezultat = operand2 * operand1;
        break;
    case '/':
        *rezultat = operand2 / operand1;
        break;
    default:
        printf("Operation %c nije podržana!\r\n", operacija);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
};
