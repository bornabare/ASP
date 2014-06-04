#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "datoteka.h"


void ispisStoga (Stog *stog){
    int brojac; //- provjerava koliko je datoteka ispisano (57 treba ispast)
    Datoteka element; //element koji cemo skinit s glavnog stoga i prebacit na pomocni, on je tipa Datoteka (ocito)
    Stog pomocni; //pomocni stog na kojeg cemo skidat elemente s glavnog stoga
    init_stog(&pomocni);
    brojac = 0;

    while (skini(&element, stog)){ //skini element sa stoga
        printf ("%c %d %s\n", element.vrsta, element.velicina, element.putanja);
        dodaj(element, &pomocni); // stavi ga na pomocni stog
    }

    while (skini(&element, &pomocni)){ //skini sa pomocnog stoga
            ++brojac;
        dodaj(element, stog); // .. i stavi na glavni stog
    }

    printf("Ukupno datoteka na stogu: %d\n", brojac);
}

void ispisStoga2 (Stog *stog) { //bez pomocnog stoga, izvedeno rekurzijom
    Datoteka element;
    while (skini (&element, stog)) {
        printf("%c %-40s %-10d \n", element.vrsta, element.putanja, element.velicina); //ispisi taj element
        ispisStoga2 (stog);
    }
    dodaj(element, stog);
    return;        
}

void najveceDatoteke(char *mapa, Stog *s){
    int broj, i;
    Datoteka max; //oznacava najvecu datoteku u trenutnoj mapi
    Datoteka *poljeDatoteka = NULL; // ovdje ce pisati podatci o svim datotekama u trenutnoj mapi

    broj = vratiDatoteke(mapa,&poljeDatoteka); // funkcija vraca broj datoteka u trenutnoj mapi, a njihove podatke zapisuje u poljeDatoteka
    max.velicina = 0;



    for (i = 0; i < broj; ++i){
        if ( (poljeDatoteka[i].vrsta == 'F') && (poljeDatoteka[i].velicina > max.velicina) ) //ako je datoteka bas datoteka (nije folder)
              prepisiDatoteku(&max, &poljeDatoteka[i]); //... i ako je veca od svih dosad obradjenih datoteka u tom folderu, onda je ona trenutno najveca
    }
    if (max.velicina > 0) dodaj (max, s); //ako postoji datoteka u tom folderu, dodaj ju na stog.
    // Ukoliko je max.velicina == 0, to znaci da je mapa prazna ili da sadrzi samo podmape
    for (i = 0; i < broj; ++i){ //udji u svaku podmapu (vrsta == D)
        if (poljeDatoteka[i].vrsta == 'D')
            najveceDatoteke(poljeDatoteka[i].putanja, s); //i tamo opet nadji najvecu datoteku
    }

    free(poljeDatoteka); //oslobodi memoriju koju si zauzeo funkcijom vratiDatoteke
}

int main(void){
    printf("Pocetak\n");
    Stog stog; // varijabla "stog" je tipa "Stog"
    init_stog(&stog);
    najveceDatoteke("G:", &stog);
    printf ("Stog popunjen - - - \n\n");
    ispisStoga2(&stog);

    return 0;
}



