#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "dataType.h"

int main(void) {

	int odgovor = 1;

	printf("test");

	char* datotekaKorisnici = "korisnici.bin";
	char* datotekaAutomobili = "automobili.bin";
	char* racun = "racun.txt";

	while (odgovor) {
		odgovor = izbornik();
	}

	printf("\nKraj programa");

	return 0;
}