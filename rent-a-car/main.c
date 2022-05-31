#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

int main(void) {

	int odgovor = 1;

	char* datotekaKorisnici = "korisnici.bin";
	char* datotekaAutomobili = "automobili.bin";
	char* racun = "racun.txt";

	kreiranjeDatoteke(datotekaKorisnici);
	kreiranjeDatoteke(datotekaAutomobili);

	while (odgovor) {
		odgovor = izbornik(datotekaKorisnici, datotekaAutomobili, racun);
	}

	printf("\nKraj programa");

	return 0;
}