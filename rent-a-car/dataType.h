#ifndef DATATYPE_H
#define DATATYPE_h

typedef struct korisnik {
	int id;
	char ime[25];
	char prezime[25];
	int godine;
	char adresa[50];
	int trenutnoPosuduje;
	int idAutomobila;
}KORISNIK;

typedef struct automobil {
	int id;
	char marka[25];
	char model[25];
	int godiste;
	char boja[25];
	int cijenaPoDanu;
	int trenutnoPosuden;
	int idKorisnika;
}AUTOMOBIL;

typedef struct racun {
	int id;
	int idAutomobila;
	int idKorisnika;
	char marka[25];
	char imeKorisnika[25];
	char prezimeKorisnika[25];
	int trajanjePosudbe;
	int cijena;
}RACUN;

#endif