#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "dataType.h"

static int brojKorisnika = 0;
static int brojAutomobila = 0;

void kreiranjeDatoteke(const char* const dat) {

	FILE* fp = fopen(dat, "rb");

	// ak ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {
		fp = fopen(dat, "wb");

		if (strcmp(dat, "korisnici.bin") == 0) {
			fwrite(&brojKorisnika, sizeof(int), 1, fp);
		}
		
		if (strcmp(dat, "automobili.bin") == 0) {
			fwrite(&brojAutomobila, sizeof(int), 1, fp);
		}

		fclose(fp);
	}
	else {
		fclose(fp);
	}
}

void dodajKorisnika(const char* const dat) {

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Dodavanje korisnika");
		exit(EXIT_FAILURE);
	}

	//citamo prvi red datoteke i zapisujemo broj clanova u varijablu brojClanova
	fread(&brojKorisnika, sizeof(int), 1, fp);
	printf("Broj korisnika: %d\n\n", brojKorisnika);

	KORISNIK temp = { 0 };
	
	temp.id = brojKorisnika + 1;
	
	getchar();

	printf("Unesite ime korisnika: ");
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime korisnika: ");
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite adresu korisnika: ");
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite starost korisnika: ");
	scanf("%d", &temp.godine);

	temp.trenutnoPosuduje = 0;
	temp.idAutomobila = 0;

	//pomicemo se na kraj datoteke i zapisujemo novog clana tamo
	fseek(fp, sizeof(KORISNIK) * brojKorisnika, SEEK_CUR);
	fwrite(&temp, sizeof(KORISNIK), 1, fp);
	printf("Novi clan dodan.\n\n");

	// povratak na pocetak datoteke
	rewind(fp);
	brojKorisnika++;

	// zapis novog broja clanova
	fwrite(&brojKorisnika, sizeof(int), 1, fp);

	fclose(fp);
}

void dodajAutomobil(const char* const dat) {

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Dodavanje automobila");
		exit(EXIT_FAILURE);
	}

	fread(&brojAutomobila, sizeof(int), 1, fp);

	printf("Broj automobila: %d\n\n", brojAutomobila);

	AUTOMOBIL temp = { 0 };

	temp.id = brojAutomobila + 1;
	getchar();

	printf("Unesite marku automobila: ");
	scanf("%24[^\n]", temp.marka);
	getchar();

	printf("Unesite model automobila: ");
	scanf("%24[^\n]", temp.model);
	getchar();

	printf("Unesite godinu proizvodnje automobila: ");
	scanf("%d", &temp.godiste);
	getchar();

	printf("Unesite boju automobila: ");
	scanf("%24[^\n]", temp.boja);
	getchar();

	printf("Unesite cijenu automobila po danu (u HRK): ");
	scanf("%d", &temp.cijenaPoDanu);

	temp.idKorisnika = 0;
	temp.trenutnoPosuden = 0;

	fseek(fp, sizeof(AUTOMOBIL) * brojAutomobila, SEEK_CUR);
	fwrite(&temp, sizeof(AUTOMOBIL), 1, fp);

	printf("Novi automobil dodan\n");

	rewind(fp);
	brojAutomobila++;

	fwrite(&brojAutomobila, sizeof(int), 1, fp);

	fclose(fp);
}

void* ucitajKorisnike(const char* const dat) {
	FILE* fp = fopen(dat, "rb");

	if (fp == NULL) {
		perror("Ucitavanje korisnika");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojKorisnika, sizeof(int), 1, fp);

	KORISNIK* poljeKorisnika = (KORISNIK*)calloc(brojKorisnika, sizeof(KORISNIK));

	if (poljeKorisnika == NULL) {
		perror("Zauzimanje memorije za polje korisnika");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeKorisnika, sizeof(KORISNIK), brojKorisnika, fp);

	return poljeKorisnika;
}

void* ucitajAutomobile(const char* const dat) {
	
	FILE* fp = fopen(dat, "rb");

	if (fp == NULL) {
		perror("Ucitavanje automobila");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojAutomobila, sizeof(int), 1, fp);

	AUTOMOBIL* poljeAutomobila = (AUTOMOBIL*)calloc(brojAutomobila, sizeof(AUTOMOBIL));

	if (poljeAutomobila == NULL) {
		perror("Zauzimanje memorije za polje automobila");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeAutomobila, sizeof(AUTOMOBIL), brojAutomobila, fp);

	return poljeAutomobila;
}

void ispisiSveKorisnike(const KORISNIK* const polje) {

	if (brojKorisnika == 0) {
		printf("Polje clanova prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojKorisnika; i++) {
		printf("ID: %d  Ime: %s  Prezime: %s  Adresa: %s  Godine: %d  Trenutno posuduje: %s  ID posudenog automobila: %d\n\n",
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->adresa,
			(polje + i)->godine,
			(polje + i)->trenutnoPosuduje == 1 ? "Da" : "Ne",
			(polje + i)->idAutomobila);
	}
}

void zamjena(AUTOMOBIL* const veci, AUTOMOBIL* const manji) {
	AUTOMOBIL temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void* sortitajPoCijeni(const AUTOMOBIL* polje) {

	int min = -1;
	for (int i = 0; i < brojAutomobila - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < brojAutomobila; j++)
		{
			if ((polje + j)->cijenaPoDanu < (polje + min)->cijenaPoDanu) {
				min = j;
			}
		}
		zamjena((polje + i), (polje + min));
	}

	return polje;
}

// nacin ovdje predstavlja jel ispisujemo automobile po ID-u ili po cijeni
void ispisiSveAutomobile(const AUTOMOBIL* polje, int nacin) {
	
	if (brojAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return;
	}

	int i;

	if (nacin == 1) {
		polje = sortitajPoCijeni(polje);
	}

	for (i = 0; i < brojAutomobila; i++) {
		printf("ID: %d  Marka: %s  Model: %s  Boja: %s  Godiste: %d.  Cijena po danu: %d KN  Trenutno posuden: %s  ID korisnika: %d\n\n",
			(polje + i)->id,
			(polje + i)->marka,
			(polje + i)->model,
			(polje + i)->boja,
			(polje + i)->godiste,
			(polje + i)->cijenaPoDanu,
			(polje + i)->trenutnoPosuden == 1 ? "Da" : "Ne",
			(polje + i)->idKorisnika);
	}
}

void* pronadiKorisnika(KORISNIK* const polje) {

	if (brojKorisnika == 0) {
		printf("Polje clanova prazno\n");
		return NULL;
	}

	int i, trazeniId;

	printf("Unesite ID korisnika kojeg trazite: ");
	
	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojKorisnika) {
			printf("Korisnik s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojKorisnika);

	for (i = 0; i < brojKorisnika; i++) {
		
		if (trazeniId == (polje + i)->id) {
			printf("Clan pronaden\n");

			return (polje + i);
		}
	}

	return NULL;
}

void* pronadiAutomobil(AUTOMOBIL* const polje) {

	if (brojAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return NULL;
	}

	int i, trazeniId;

	printf("Unesite ID automobila kojeg trazite: ");
	
	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojAutomobila) {
			printf("Automobil s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojAutomobila);

	for (i = 0; i < brojAutomobila; i++) {
		
		if (trazeniId == (polje + i)->id) {
			printf("Clan pronaden\n");

			return (polje + i);
		}
	}

	return NULL;
}

void ispisiSlobodneAutomobile(AUTOMOBIL* const polje) {

	if (brojAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return;
	}

	int i, counter = 0;

	printf("Trenutno slobodni automobili: \n");

	for (i = 0; i < brojAutomobila; i++) {

		if ((polje + i)->trenutnoPosuden == 0) {
			printf("ID: %d  Marka: %s  Model: %s  Godiste: %d  Boja: %s  Cijena po danu: %d HRK\n\n",
				(polje + i)->id,
				(polje + i)->marka,
				(polje + i)->model,
				(polje + i)->godiste,
				(polje + i)->boja,
				(polje + i)->cijenaPoDanu
			);

			counter++;
		}
	}

	if (counter == 0) {
		printf("Nazalost trenutno nema slobodnih automobila\n");
	}
}

void ispisiKorisnikeKojiIznajmljuju(KORISNIK* const polje) {

	if (brojKorisnika == 0) {
		printf("Polje korisnika prazno");
		return;
	}

	int i, counter = 0;

	printf("Korisnici koji trenutno iznajmljuju automobil: \n");

	for (i = 0; i < brojKorisnika; i++) {

		if ((polje + i)->trenutnoPosuduje == 1) {
			printf("ID: %d  Ime: %s  Prezime: %s  Adresa: %s  Godine: %d ID automobila kojeg posuduje: %d\n\n",
				(polje + i)->id,
				(polje + i)->ime,
				(polje + i)->prezime,
				(polje + i)->adresa,
				(polje + i)->godine,
				(polje + i)->idAutomobila
			);

			counter++;
		}
	}

	if (counter == 0) {
		printf("Trenutno nema korisnika koji iznajmljuju automobil\n");
	}
}

void brisanjeAutomobila(AUTOMOBIL* const polje, const char* const dat) {

	if (brojAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje automobila");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID automobila kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojAutomobila) {
			printf("Automobil s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
		if ((polje + trazeniId - 1)->trenutnoPosuden == 1) {
			printf("Automobil s unesenim ID-em je trenutno posuden i nemoguce ga je obrisati u ovom trenutku.");
		}
	} while (trazeniId < 1 || trazeniId > brojAutomobila || (polje + trazeniId - 1)->trenutnoPosuden == 1);

	AUTOMOBIL* pomocnoPolje = (AUTOMOBIL*)calloc(brojAutomobila - 1, sizeof(AUTOMOBIL));

	int counter = 0;

	for (i = 0; i < brojAutomobila; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(AUTOMOBIL), 1, fp);
			counter++;
		}
	}
	
	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Automobil je uspjesno obrisan\n");
}

void brisanjeKorisnika(KORISNIK* const polje, const char* const dat) {

	if (brojKorisnika == 0) {
		printf("Polje korisnika prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Brisanje korisnika");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID korisnika kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojKorisnika) {
			printf("Korisnik s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
		if ((polje + trazeniId - 1)->trenutnoPosuduje == 1) {
			printf("Korisnik s unesenim ID-em trenutno posuduje automobil i nemoguce ga je obrisati prije nego li ga vrati.\n");
			return;
		}
	} while (trazeniId < 1 || trazeniId > brojKorisnika || (polje + trazeniId - 1)->trenutnoPosuduje == 1);

	KORISNIK* pomocnoPolje = (KORISNIK*)calloc(brojKorisnika - 1, sizeof(KORISNIK));

	int counter = 0;

	for (i = 0; i < brojKorisnika; i++) {

		if (trazeniId != (polje + i)->id) {
			*(pomocnoPolje + counter) = *(polje + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(KORISNIK), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje);
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Korisnik je uspjesno obrisan\n");
}

void azurirajKorisnika(KORISNIK* polje, const char* const dat) {

	if (brojKorisnika == 0) {
		printf("Polje korisnika prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Azuriranje korisnika");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID korisnika kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojKorisnika) {
			printf("Korisnik s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojKorisnika);

	KORISNIK temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite ime korisnika (trenutno: %s): ", (polje + trazeniId - 1)->ime);
	scanf("%24[^\n]", temp.ime);
	getchar();

	printf("Unesite prezime korisnika (trenutno %s): ", (polje + trazeniId - 1)->prezime);
	scanf("%24[^\n]", temp.prezime);
	getchar();

	printf("Unesite adresu korisnika (trenutno %s): ", (polje + trazeniId - 1)->adresa);
	scanf("%49[^\n]", temp.adresa);
	getchar();

	printf("Unesite starost korisnika (trenutno %d): ", (polje + trazeniId - 1)->godine);
	scanf("%d", &temp.godine);

	temp.trenutnoPosuduje = (polje + trazeniId - 1)->trenutnoPosuduje;
	temp.idAutomobila = (polje + trazeniId - 1)->idAutomobila;

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(KORISNIK) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(KORISNIK), 1, fp);

	printf("Korisnik uspjesno azuriran\n");

	fclose(fp);
}

void azurirajAutomobil(AUTOMOBIL* polje, const char* const dat) {

	if (brojAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return;
	}

	FILE* fp = fopen(dat, "rb+");

	if (fp == NULL) {
		perror("Azuriranje automobila");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID automobila kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojAutomobila) {
			printf("Automobil s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojAutomobila);

	AUTOMOBIL temp = { 0 };

	temp.id = trazeniId;

	getchar();
	printf("Unesite marku automobila (trenutno: %s): ", (polje + trazeniId - 1)->marka);
	scanf("%24[^\n]", temp.marka);
	getchar();

	printf("Unesite model automobila (trenutno: %s): ", (polje + trazeniId - 1)->model);
	scanf("%24[^\n]", temp.model);
	getchar();

	printf("Unesite godinu proizvodnje automobila (trenutno: %d.): ", (polje + trazeniId - 1)->godiste);
	scanf("%d", &temp.godiste);
	getchar();

	printf("Unesite boju automobila (trenutno %s): ", (polje + trazeniId - 1)->boja);
	scanf("%24[^\n]", temp.boja);
	getchar();

	printf("Unesite cijenu automobila po danu (u HRK) (trenutno: %d HRK): ", (polje + trazeniId - 1)->cijenaPoDanu);
	scanf("%d", &temp.cijenaPoDanu);

	temp.idKorisnika = (polje + trazeniId - 1)->idKorisnika;
	temp.trenutnoPosuden = (polje + trazeniId - 1)->trenutnoPosuden;

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(AUTOMOBIL) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(AUTOMOBIL), 1, fp);

	printf("Automobil uspjesno azuriran\n");

	fclose(fp);
}


void pronadiKorisnikaPrezime(KORISNIK* const polje) {
	
	if (brojKorisnika == 0) {
		printf("Polje korisnika prazno\n");
		return;
	}

	char trazenoPrezime[25];

	printf("Unesite prezime koje trazite: ");
	getchar();
	scanf("%24[^\n]", trazenoPrezime);

	int i, counter = 0;

	for (i = 0; i < brojKorisnika; i++) {

		if (strcmp(trazenoPrezime, (polje + i)->prezime) == 0) {
			
			printf("ID: %d  Ime: %s  Prezime: %s  Adresa: %s  Godine: %d  Trenutno posuduje: %s  ID posudenog automobila: %d\n\n",
				(polje + i)->id,
				(polje + i)->ime,
				(polje + i)->prezime,
				(polje + i)->adresa,
				(polje + i)->godine,
				(polje + i)->trenutnoPosuduje == 1 ? "Da" : "Ne",
				(polje + i)->idAutomobila);

			counter++;
		}
	}

	if (counter == 0) {
		printf("Nema korisnika s unesenim prezimenom\n");
		return;
	}
} 

void pronadiAutomobilPoMarki(AUTOMOBIL* polje) {

	if (brojAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return;
	}

	char trazenaMarka[25];

	printf("Unesite marku koje trazite: ");
	getchar();
	scanf("%24[^\n]", trazenaMarka);

	int i, counter = 0;

	printf("\n");

	for (i = 0; i < brojAutomobila; i++) {

		if (strcmp(trazenaMarka, (polje + i)->marka) == 0) {

			printf("ID: %d  Marka: %s  Model: %s  Godiste: %d.  Boja: %s  Cijena: %d HRK Trenutno posuden: %s ID korisnika: %d\n\n",
				(polje + i)->id,
				(polje + i)->marka,
				(polje + i)->model,
				(polje + i)->godiste,
				(polje + i)->boja,
				(polje + i)->cijenaPoDanu,
				(polje + i)->trenutnoPosuden == 1 ? "Da" : "Ne",
				(polje + i)->idKorisnika);

			counter++;
		}
	}

	if (counter == 0) {
		printf("Nema automobila te marke\n");
		return;
	}
}

void iznajmljivanje(KORISNIK* poljeKorisnika, AUTOMOBIL* poljeAutomobila, const char* const datKorisnici, const char* const datAuti, const char* const racun) {

	if (brojKorisnika == 0) {
		printf("Polje korisnika prazno\n");
		return;
	}

	if (poljeAutomobila == 0) {
		printf("Polje automobila prazno\n");
		return;
	}

	FILE* fpk = fopen(datKorisnici, "rb+");

	if (fpk == NULL) {
		perror("Ucitavanje korisnika");
		exit(EXIT_FAILURE);
	}

	FILE* fpa = fopen(datAuti, "rb+");

	if (fpa == NULL) {
		perror("Ucitavanje automobila");
		exit(EXIT_FAILURE);
	}

	FILE* fpr = fopen(racun, "w");

	if (fpr == NULL) {
		printf("Pogreska pri stvaranju racuna");
		return;
	}

	int trazeniClan;

	ispisiSveKorisnike(poljeKorisnika);

	printf("\nUnesite ID clana koji posuduje automobil: ");

	do {
		scanf("%d", &trazeniClan);

		if (trazeniClan < 1 || trazeniClan > brojKorisnika) {
			printf("Korisnik s unesenim ID-om ne postoji, unesite ispravan ID: ");
		}
	} while (trazeniClan < 1 || trazeniClan > brojKorisnika);

	printf("Odaberite jedan od slobodnih automobila\n");

	ispisiSlobodneAutomobile(poljeAutomobila);

	int trazeniAutomobil = 0;

	printf("Unesite ID automobila kojeg zelite iznajmiti: ");

	do {
		scanf("%d", &trazeniAutomobil);

		if ((poljeAutomobila + trazeniAutomobil)->trenutnoPosuden == 1) {
			printf("Odabrali ste automobil koji se trenutno posuduje, odaberite neki drugi automobil: ");
			ispisiSlobodneAutomobile(poljeAutomobila);
		}

		if (trazeniAutomobil < 1 || trazeniAutomobil > brojAutomobila) {
			printf("Automobil s unesenim ID-om ne postoji, unesite ispravan ID: ");
			ispisiSlobodneAutomobile(poljeAutomobila);
		}
	} while ((poljeAutomobila + trazeniAutomobil)->trenutnoPosuden == 1 || trazeniAutomobil < 1 || trazeniAutomobil > brojAutomobila);

	(poljeKorisnika + trazeniClan - 1)->trenutnoPosuduje = 1;
	(poljeKorisnika + trazeniClan - 1)->idAutomobila = trazeniAutomobil;

	(poljeAutomobila + trazeniAutomobil - 1)->trenutnoPosuden = 1;
	(poljeAutomobila + trazeniAutomobil - 1)->idKorisnika = trazeniClan;

	rewind(fpk);
	fseek(fpk, sizeof(int) * 1, SEEK_CUR);
	fseek(fpk, sizeof(KORISNIK) * (trazeniClan - 1), SEEK_CUR);
	fwrite((poljeKorisnika + trazeniClan - 1), sizeof(KORISNIK), 1, fpk);

	rewind(fpa);
	fseek(fpa, sizeof(int) * 1, SEEK_CUR);
	fseek(fpa, sizeof(AUTOMOBIL) * (trazeniAutomobil - 1), SEEK_CUR);
	fwrite((poljeAutomobila + trazeniAutomobil - 1), sizeof(AUTOMOBIL), 1, fpa);

	fclose(fpa);
	fclose(fpk);

	int brojDana;

	printf("Koliko dana zelite posudivati automobil (max 30 dana): ");

	do {
		scanf("%d", &brojDana);

		if (brojDana < 1 || brojDana > 30) {
			printf("Nemozete posudivati automobil toliko dana. Unesite manji broj dana (max 30): \n");
		}
	} while (brojDana < 1 || brojDana > 30);

	int brojRacuna = 0 + (float)rand() / RAND_MAX * (99999 - 0);

	fprintf(fpr, "===================================================\n\n");
	fprintf(fpr, "\t\t RENT-A-CAR OSIJEK\n\n");
	fprintf(fpr, "===================================================\n\n");
	fprintf(fpr, "Racun broj: %d\n", brojRacuna);
	fprintf(fpr, "===================================================\n\n");
	fprintf(fpr, "Ime : %s\n", (poljeKorisnika + trazeniClan - 1)->ime);
	fprintf(fpr, "Prezime : %s\n", (poljeKorisnika + trazeniClan - 1)->prezime);
	fprintf(fpr, "Adresa : %s\n", (poljeKorisnika + trazeniClan - 1)->adresa);
	fprintf(fpr, "ID automobila : %d\n", (poljeAutomobila + trazeniAutomobil - 1)->id);
	fprintf(fpr, "Marka : %s\n", (poljeAutomobila + trazeniAutomobil - 1)->marka);
	fprintf(fpr, "Model : %s \n", (poljeAutomobila + trazeniAutomobil - 1)->model);
	fprintf(fpr, "Boja : %s\n", (poljeAutomobila + trazeniAutomobil - 1)->boja);
	fprintf(fpr, "Cijena po danu : %d HRK\n", (poljeAutomobila + trazeniAutomobil - 1)->cijenaPoDanu);
	fprintf(fpr, "Trajanje posudbe : %d dana\n\n", brojDana);
	fprintf(fpr, "===================================================\n\n");
	fprintf(fpr, "Ukupna cijena za platit : %d HRK", brojDana * (poljeAutomobila + trazeniAutomobil - 1)->cijenaPoDanu);

	printf("Automobil uspjesno iznajmljen. Racun se nalazi u mapi programa.\n");

	fclose(fpr);
}