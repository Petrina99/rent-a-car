#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

int izbornik(const char* const datKorisnici, const char* const datAuti, const char* const datRacun) {

	printf("\n====================================\n\n");
	printf("Odaberite jednu od ponudenih opcija: \n\n");
	printf("====================================\n\n");

	printf("[ 1 ]: Dodavanje korisnika\n");
	printf("[ 2 ]: Dodavanje automobila\n");
	printf("[ 3 ]: Ispisi sve korisnike\n");
	printf("[ 4 ]: Ispisi sve automobile\n");
	printf("[ 5 ]: Sortiraj automobile po cijeni\n");
	printf("[ 6 ]: Pretrazi korisnika po ID-u\n");
	printf("[ 7 ]: Pretrazi  automobil po ID-u\n");
	printf("[ 8 ]: Pretrazi korisnika po prezimenu:\n");
	printf("[ 9 ]: Pretrazi automobil po marki:\n");
	printf("[ 10 ]: Ispisi slobodne automobile\n");
	printf("[ 11 ]: Ispisi korisnike koji trenutno iznajmljuju automobil\n");
	printf("[ 12 ]: Azuriraj korisnika\n");
	printf("[ 13 ]: Azuriraj automobil\n");
	printf("[ 14 ]: Obrisi automobil\n");
	printf("[ 15 ]: Obrisi korisnika\n");
	printf("[ 16 ]: Iznajmi automobil\n");
	printf("[ 17 ]: Kraj programa\n");

	printf("\n====================================\n\n");

	int odgovor = 0;

	static KORISNIK* poljeKorisnika = NULL;
	static KORISNIK* pronadeniKorisnik = NULL;

	static AUTOMOBIL* poljeAutomobila = NULL;
	static AUTOMOBIL* pronadeniAutomobil = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
	case 1:
		dodajKorisnika(datKorisnici);
		break;
	case 2:
		dodajAutomobil(datAuti);
		break;
	case 3:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		ispisiSveKorisnike(poljeKorisnika);

		break;
	case 4:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		ispisiSveAutomobile(poljeAutomobila, 2);

		break;
	case 5:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		ispisiSveAutomobile(poljeAutomobila, 1);
		break;
	case 6:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		pronadeniKorisnik = (KORISNIK*)pronadiKorisnika(poljeKorisnika);

		if (pronadeniKorisnik != NULL) {
			printf("ID: %d\n", pronadeniKorisnik->id);
			printf("Ime: %s\n", pronadeniKorisnik->ime);
			printf("Prezime: %s\n", pronadeniKorisnik->prezime);
			printf("Godine: %d\n", pronadeniKorisnik->godine);
			printf("Adresa: %s\n", pronadeniKorisnik->adresa);
			printf("Trenutno posuduje: %s\n", pronadeniKorisnik->trenutnoPosuduje == 1 ? "da" : "ne");
			printf("ID automobila kojeg posuduje: %d", pronadeniKorisnik->idAutomobila);
		}

		break;
	case 7:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		pronadeniAutomobil = (AUTOMOBIL*)pronadiAutomobil(poljeAutomobila);

		if (pronadeniAutomobil != NULL) {
			printf("ID: %d\n", pronadeniAutomobil->id);
			printf("Marka: %s\n", pronadeniAutomobil->marka);
			printf("Model: %s\n", pronadeniAutomobil->model);
			printf("Boja: %s\n", pronadeniAutomobil->boja);
			printf("Godiste: %d.\n", pronadeniAutomobil->godiste);
			printf("Trenutno posuden: %s\n", pronadeniAutomobil->trenutnoPosuden == 1 ? "da" : "ne");
			printf("ID korisnika koji ga posuduje: %d", pronadeniAutomobil->idKorisnika);
		}

		break;
	case 8:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		pronadiKorisnikaPrezime(poljeKorisnika);
		break;
	case 9:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		pronadiAutomobilPoMarki(poljeAutomobila);
		break;
	case 10:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		ispisiSlobodneAutomobile(poljeAutomobila);
		break;
	case 11:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		ispisiKorisnikeKojiIznajmljuju(poljeKorisnika);
		break;
	case 12:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		azurirajKorisnika(poljeKorisnika, datKorisnici);
		break;
	case 13:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		azurirajAutomobil(poljeAutomobila, datAuti);
		break;
	case 14:
		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		brisanjeAutomobila(poljeAutomobila, datAuti);
		break;
	case 15:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		brisanjeKorisnika(poljeKorisnika, datKorisnici);
		break;
	case 16:
		if (poljeKorisnika != NULL) {
			free(poljeKorisnika);
			poljeKorisnika = NULL;
		}

		poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

		if (poljeAutomobila != NULL) {
			free(poljeAutomobila);
			poljeAutomobila = NULL;
		}

		poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

		iznajmljivanje(poljeKorisnika, poljeAutomobila, datKorisnici, datAuti, datRacun);
		break;
	default:
		odgovor = 0;
	}

	return odgovor;
}