#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"
#include "dataType.h"

int izbornik(const char* const datKorisnici, const char* const datAuti, const char* const datRacun) {

	printf("\n\t\t====================================\n\n");
	printf("\t\tOdaberite jednu od ponudenih opcija: \n\n");
	printf("\t\t====================================\n\n");

	printf("\t\tOpcija 1: Dodavanje korisnika\n");
	printf("\t\tOpcija 2: Dodavanje automobila\n");
	printf("\t\tOpcija 3: Pretrazi korisnika po ID-u\n");
	printf("\t\tOpcija 4: Pretrazi  automobil po ID-u\n");
	printf("\t\tOpcija 5: Ispisi slobodne automobile\n");
	printf("\t\tOpcija 6: Ispisi korisnike koji trenutno iznajmljuju automobil\n");
	printf("\t\tOpcija 7: Obrisi automobil\n");
	printf("\t\tOpcija 8: Obrisi korisnika\n");
	printf("\t\tOpcija 9: Iznajmi automobil\n");
	printf("\t\tOpcija 10: Kraj programa\n");

	printf("\n\t\t====================================\n\n");

	int odgovor = 0;
	
	static KORISNIK* poljeKorisnika = NULL;
	static AUTOMOBIL* poljeAutomobila = NULL;

	scanf("%d", &odgovor);

	switch (odgovor) {
		case 1:
			dodajKorisnika(datKorisnici);
			break;
		case 2: 
			dodajAutomobil(datAuti);
		default:
			odgovor = 0;
	}
	return 0;
}
