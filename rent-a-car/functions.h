#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "dataType.h"

int izbornik(const char* const, const char* const, const char* const);
void kreiranjeDatoteke(const char* const);
void* ucitajKorisnike(const char* const);
void* ucitajAutomobile(const char* const);
void dodajKorisnika(const char* const);
void dodajAutomobil(const char* const);
void* pronadiKorisnika(KORISNIK* const);
void* pronadiAutomobil(AUTOMOBIL* const);
void ispisiSveKorisnike(const KORISNIK* const);
void ispisiSveAutomobile(const AUTOMOBIL* const, int);
void ispisiSlobodneAutomobile(AUTOMOBIL* const);
void ispisiKorisnikeKojiIznajmljuju(KORISNIK* const);
void brisanjeAutomobila(AUTOMOBIL* const, const char* const);
void brisanjeKorisnika(KORISNIK* const, const char* const);
void azurirajKorisnika(KORISNIK*, const char* const);
void azurirajAutomobil(AUTOMOBIL*, const char* const);
void pronadiKorisnikaPrezime(KORISNIK* const);
void pronadiAutomobilPoMarki(AUTOMOBIL*);
void iznajmljivanje(KORISNIK*, AUTOMOBIL*, const char* const, const char* const, const char* const);

#endif