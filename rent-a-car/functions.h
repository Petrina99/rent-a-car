#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const, const char* const, const char* const);
void kreiranjeDatoteke(const char* const);
void* ucitajKorisnike(const char* const);
void* ucitajAutomobile(const char* const);
void dodajKorisnika(const char* const);
void dodajAutomobil(const char* const);
void* pronadiKorisnikaPoId(KORISNIK* const);
void* pronadiAutomobilPoId(AUTOMOBIL* const);
void ispisiSveKorisnike(const KORISNIK* const);
void ispisiSveAutomobile(const AUTOMOBIL* const);

#endif