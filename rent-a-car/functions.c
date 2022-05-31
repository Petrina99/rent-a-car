#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

static int brojKorisnika = 0;
static int brojAutomobila = 0;

void kreiranjeDatoteke(const char* const dat) {

	FILE* fp = fopen(dat, "rb");

	// ak ne postoji stvaramo novu datoteku sa wb, ako postoji samo zatvaramo
	if (fp == NULL) {
		fp = fopen(dat, "wb");
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

	fread(&brojKorisnika, sizeof(int), 1, fp);

	printf("Broj prijavljenih korisnika: %d\n\n", brojKorisnika);

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

	// svaki novi clan ima default vrijednosti za ova dva propa
	temp.trenutnoPosuduje = 0;
	temp.idAutomobila = 0;

	fseek(fp, sizeof(KORISNIK) * brojKorisnika, SEEK_CUR);
	fwrite(&temp, sizeof(KORISNIK), 1, fp);

	printf("Novi clan dodan\n");
	
	rewind(fp);
	brojKorisnika++;

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
	printf("Broj korisnika %d", brojKorisnika);

	KORISNIK* poljeKorisnika = (KORISNIK*)calloc(brojKorisnika, sizeof(KORISNIK));

	if (poljeKorisnika == NULL) {
		perror("Zauzimanje memorije za polje korisnika");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(poljeKorisnika, sizeof(KORISNIK), brojKorisnika, fp);

	printf("Svi clanovi uspjesno ucitani");

	return poljeKorisnika;
}