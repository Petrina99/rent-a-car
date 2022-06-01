#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

int izbornik(const char* const datKorisnici, const char* const datAuti, const char* const datRacun) {

	printf("\n====================================\n\n");
	printf("Odaberite jednu od ponudenih opcija: \n\n");
	printf("====================================\n\n");

	printf("Opcija 1: Dodavanje korisnika\n");
	printf("Opcija 2: Dodavanje automobila\n");
	printf("Opcija 3: Ispisi sve korisnike\n");
	printf("Opcija 4: Ispisi sve automobile\n");
	printf("Opcija 5: Pretrazi korisnika po ID-u\n");
	printf("Opcija 6: Pretrazi  automobil po ID-u\n");
	printf("Opcija 7: Ispisi slobodne automobile\n");
	printf("Opcija 8: Ispisi korisnike koji trenutno iznajmljuju automobil\n");
	printf("Opcija 9: Obrisi automobil\n");
	printf("Opcija 10: Obrisi korisnika\n");
	printf("Opcija 11: Iznajmi automobil\n");
	printf("Opcija 12: Kraj programa\n");

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

			ispisiSveAutomobile(poljeAutomobila);

			break;
		case 5:
			if (poljeKorisnika != NULL) {
				free(poljeKorisnika);
				poljeKorisnika = NULL;
			}

			poljeKorisnika = (KORISNIK*)ucitajKorisnike(datKorisnici);

			if (poljeKorisnika == NULL) {
				exit(EXIT_FAILURE);
			}

			pronadeniKorisnik = (KORISNIK*)pronadiKorisnikaPoId(poljeKorisnika);

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
		case 6:
			if (poljeAutomobila != NULL) {
				free(poljeAutomobila);
				poljeAutomobila = NULL;
			}

			poljeAutomobila = (AUTOMOBIL*)ucitajAutomobile(datAuti);

			if (poljeAutomobila == NULL) {
				exit(EXIT_FAILURE);
			}

			pronadeniAutomobil = (AUTOMOBIL*)pronadiAutomobilPoId(poljeAutomobila);

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
		default:
			odgovor = 0;
	}

	return odgovor;
}
