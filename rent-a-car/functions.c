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
	printf("Broj clanova: %d\n\n", brojKorisnika);

	KORISNIK temp = {NULL};
	
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

	if (polje == NULL) {
		printf("Polje clanova prazno\n");
		return;
	}

	int i;

	for (i = 0; i < brojKorisnika; i++) {
		printf("ID: %d  Ime: %s  Prezime: %s  Adresa: %s  Trenutno posuduje: %s  ID posudenog automobila: %d\n\n",
			(polje + i)->id,
			(polje + i)->ime,
			(polje + i)->prezime,
			(polje + i)->adresa,
			(polje + i)->trenutnoPosuduje == 1 ? "Da" : "Ne",
			(polje + i)->idAutomobila);
	}
}

void ispisiSveAutomobile(const AUTOMOBIL* const polje) {
	
	if (polje == NULL) {
		printf("Polje automobila prazno\n");
		return;
	}

	int i;

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
void* pronadiKorisnikaPoId(KORISNIK* const polje) {

	if (polje == NULL) {
		printf("Polje clanova prazno\n");
		return NULL;
	}

	int i, trazeniId;

	printf("Unesite ID korisnika kojeg trazite: ");
	scanf("%d", &trazeniId);

	for (i = 0; i < brojKorisnika; i++) {
		
		if (trazeniId == (polje + i)->id) {
			printf("Clan pronaden\n");

			return (polje + i);
		}
	}

	return NULL;
}

void* pronadiAutomobilPoId(AUTOMOBIL* const polje) {

	if (polje == NULL) {
		printf("Polje automobila prazno\n");
		return NULL;
	}

	int i, trazeniId;

	printf("Unesite ID automobila kojeg trazite: ");
	scanf("%d", &trazeniId);

	for (i = 0; i < brojAutomobila; i++) {
		
		if (trazeniId == (polje + i)->id) {
			printf("Clan pronaden\n");

			return (polje + i);
		}
	}

	return NULL;
}