#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct osoba *poz;
struct osoba
{
	char ime[50];
	char prezime[50];
	int godina;
	poz next;
};

int Ispis(poz);
poz UnosOsobe(char*, char*, int);
int UnosNaPocetak(poz, poz);
int UnosNaKraj(poz, poz);
poz Trazi(poz, char*);
int Brisi(poz, char*);
poz TraziPrethodnika(poz, char*);
int UnosIza(poz, poz, char*);
int UnosIspred(poz, poz, char*);
int Sort(poz);
int UpisUDatoteku(poz);
int UnosIzDatoteke(poz);

int main()
{
	char c, Ime[50], Prezime[50], Prezimee[50];
	int Godina;
	poz temp;
	struct osoba head;
	head.next = NULL;
	while (1)
	{
		printf("\n \t IZBORNIK: \t \n a - unos na pocetak liste \n b - unos na kraj liste \n c - trazi osobu po prezimenu \n d - brise osobu po prezimenu \n q - kraj programa \n");
		printf(" e - unos iza osobe s trazenim prezimenom \n f - unos ispred osobe s trazenim prezimenom \n g - sortira listu po prezimenima \n h - upis liste u datoteku \n i - citanje liste iz datoteke \n");
		scanf(" %c", &c);
		switch (c)
		{
		case 'a':
			printf("Unesi ime: \n");
			scanf("%s", Ime);
			printf("Unesi prezime: \n");
			scanf("%s", Prezime);
			printf("Unesi godinu rodenja: \n");
			scanf("%d", &Godina);

			temp = UnosOsobe(Ime, Prezime, Godina);
			UnosNaPocetak(temp, &head);
			Ispis(&head);
			break;
		case 'b':
			printf("Unesi ime: \n");
			scanf("%s", Ime);
			printf("Unesi prezime: \n");
			scanf("%s", Prezime);
			printf("Unesi godinu rodenja: \n");
			scanf("%d", &Godina);

			temp = UnosOsobe(Ime, Prezime, Godina);
			UnosNaKraj(temp, &head);
			Ispis(&head);
			break;
		case 'c':
			printf("Unesi prezime koje trazis: \n");
			scanf("%s", Prezime);

			temp = Trazi(&head, Prezime);
			if (temp != NULL)
				printf("%s \t %s \t %d \n", temp->ime, temp->prezime, temp->godina);
			else
				printf("Trazeno prezime se ne nalazi u listi! \n");
			break;
		case 'd':
			printf("Unesi prezime koje trazis: \n");
			scanf("%s", Prezime);

			Brisi(&head, Prezime);
			Ispis(&head);
			break;
		case 'q':
			Ispis(&head);
			return EXIT_SUCCESS;
			break;
		case 'e':
			printf("Unesi prezime koje trazis: \n");
			scanf("%s", Prezimee);

			printf("Unesi ime: \n");
			scanf("%s", Ime);
			printf("Unesi prezime: \n");
			scanf("%s", Prezime);
			printf("Unesi godinu rodenja: \n");
			scanf("%d", &Godina);

			temp = UnosOsobe(Ime, Prezime, Godina);
			UnosIza(&head, temp, Prezimee);
			Ispis(&head);
			break;
		case 'f':
			printf("Unesi prezime koje trazis: \n");
			scanf("%s", Prezimee);

			printf("Unesi ime: \n");
			scanf("%s", Ime);
			printf("Unesi prezime: \n");
			scanf("%s", Prezime);
			printf("Unesi godinu rodenja: \n");
			scanf("%d", &Godina);

			temp = UnosOsobe(Ime, Prezime, Godina);
			UnosIspred(&head, temp, Prezimee);
			Ispis(&head);
			break;
		case 'g':
			Sort(&head);
			Ispis(&head);
			break;
		case 'h':
			UpisUDatoteku(&head);
			break;
		case 'i':
			UnosIzDatoteke(&head);
			break;
		}
	}
	return 0;
}
int UnosIzDatoteke(poz p)
{
	char ImeDat[50], c;
	int br=0;
	printf("Unesi ime datoteke iz koje citas listu: \n");
	scanf(" %s", ImeDat);

	FILE* datoteka = fopen(ImeDat, "r");
	if (!datoteka)
		printf("Greska! Krivo otvorena datoteka! \n");

	for (c = getc(datoteka); c != EOF; c = getc(datoteka))
	{
		if (c == '\n')
			br++;
	}
	rewind(datoteka);

	for (int i = 0; i < br; i++)
	{
		char Ime[50], Prezime[50];
		int Godina;
		fscanf(datoteka, " %s %s %d", Ime, Prezime, &Godina);
		poz q = UnosOsobe(Ime, Prezime, Godina);
		UnosNaPocetak(q, p);
	}
	Ispis(p);
	return 0;
}

int UpisUDatoteku(poz p)
{
	char ImeDat[50];
	printf("Unesi ime datoteke u koju upisujes listu: \n");
	scanf("%s", ImeDat);
	
	FILE* datoteka = fopen(ImeDat, "w");
	if (!datoteka)
		printf("Greska! Krivo otvorena datoteka!");
	
	p = p->next;
	if (p != NULL)
	{
		fprintf(datoteka, "Ime Prezime Godina \n");
		while (p != NULL)
		{
			fprintf(datoteka, "%s %s %d \n", p->ime, p->prezime, p->godina);
			p = p->next;
		}
	}
	else
		fprintf(datoteka, "Lista je prazna! \n");
	return 0;
}

int Sort(poz p)
{
	poz j, prev_j, temp, end;
	end = NULL;
	while(p->next != end)
	{
		prev_j = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return 0;
}

int UnosIspred(poz p, poz temp, char* prez)
{
	poz q = TraziPrethodnika(p, prez);
	temp->next = q->next;
	q->next = temp;

	return 0;
}

int UnosIza(poz p, poz temp, char* prez)
{
	poz q = Trazi(p, prez);
	temp->next = q->next;
	q->next = temp;

	return 0;
}

poz TraziPrethodnika(poz p, char* prez)
{
	poz prev = p;
	p = p->next;

	while (p != NULL && strcmp(p->prezime, prez) != 0)
	{
		prev = p;
		p = p->next;
	}
	if (p == NULL)
		return NULL;
	else
		return prev;
}

int Brisi(poz p, char* prez)
{
	poz prev = TraziPrethodnika(p, prez);

	if (prev != NULL)
	{
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
	else
		printf("Trazeno prezime se ne nalazi u listi! \n");
	return 0;
}

poz Trazi(poz p, char* prez)
{
	p = p->next;
	while (p != NULL)
	{
		if (strcmp(p->prezime, prez) == 0)
			return p;
		else
			p = p->next;
	}
	return p;
}

int UnosNaKraj(poz p, poz q)
{
	while (q->next != NULL)
		q = q->next;
	q->next = p;
	p->next = NULL;

	return 0;
}

int UnosNaPocetak(poz p, poz q)
{
	p->next = q->next;
	q->next = p;

	return 0;
}

poz UnosOsobe(char *Ime, char *Prezime, int Godina)
{
	poz p = (poz)malloc(sizeof(struct osoba));

	strcpy(p->ime, Ime);
	strcpy(p->prezime, Prezime);
	p->godina = Godina;

	return p;
}

int Ispis(poz p)
{
	p = p->next;
	if (p == NULL)
		printf("Lista je prazna! \n");
	printf("Lista: \n");
	while (p != NULL)
	{
		printf("%s \t %s \t %d \n", p->ime, p->prezime, p->godina);
		p = p->next;
	}
	return 0;
}