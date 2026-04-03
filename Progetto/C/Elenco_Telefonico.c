#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>  //contiene le dichiarazioni in C/C++ per le funzioni delle Windows API.

// Struttura dati per un contatto nella rubrica
typedef struct {
    char *nome;
    char *cognome;
    long long int numero;
    int chiamate_entrata;
    int chiamate_uscita;
} identificativo;

// Prototipi
void opzioni();
void visualizza_numero(char *,char*);
void crea_Rubrica();
void visual_array();
void ordinamento();
void inserire_nuovo_numero();
void elimina_contatto();
void ricerca_ricorsiva(int primo, int ultimo, char cognome[], char nome[]);
void trova_chiamate(long long int numero);

// Array di struct che contiene i contatti nella rubrica
identificativo Rubrica[30];

// Variabile che contiene il numero di contatti attualmente nella rubrica
int numeri_in_rubrica = 6;

int main() {
    // Inizializza la rubrica con alcuni contatti di esempio
    crea_Rubrica();

    opzioni();
    return 0;
}

// Funzione che stampa il menu delle opzioni disponibili
//Input:Prende come input un carattere a scelta dell'utente
//Output: Non da un output diretto, a seconda della scelta può variare la Rubrica
void opzioni() {
    char scelta;
    char cognome[25];
    char nome[25];
    long long int numero;


    while (1) {

        // Ordina l'array di contatti prima di stamparlo
        ordinamento();
        visual_array();
        printf("[1] Inserire nuovo numero\n");
        printf("[2] Eliminare un contatto\n");
        printf("[3] Ricerca numero attraverso Cognome e Nome\n");
        printf("[4] Registro chiamate attraverso numero di telefono\n");
        printf("[5] Exit\n");
        printf("\nInserire scelta: ");
        scanf(" %c", &scelta);

        switch (scelta) {
            case '1':
                inserire_nuovo_numero();
                break;
            case '2':
                elimina_contatto();
                printf("\n");
                system("pause");
                break;

            case '3':
                printf("Inserisci il Cognome e il Nome da ricercare: ");
                scanf("%s", cognome); scanf("%s",nome);
                fflush(stdin);
                visualizza_numero(cognome,nome);
                printf("\n");
                system("pause");
                break;
            case '4':
                printf("Inserisci il numero telefonico: ");
                scanf("%lld",&numero);
                trova_chiamate(numero);
                printf("\n");
                system("pause");
                break;

            case '5':
                return;
        }

        system("cls");
    }
}

// Funzione che stampa il registro delle chiamate per un dato numero di telefono
//Input: Prende dall'utente un numero intero
//Output: Stampa a video le caratteristiche relative al numero se è presente nella rubrica, se non è presente stampa a video "Numero non trovato"
void trova_chiamate(long long int numero) {
    int i;

    for (i = 0; i < numeri_in_rubrica; i++) {
        if (Rubrica[i].numero == numero) {
            printf("\nIl numero telefonico e' di: %s %s", Rubrica[i].cognome,Rubrica[i].nome);
            printf("\nLe chiamate in entrata sono: %d", Rubrica[i].chiamate_entrata);
            printf("\nLe chiamate in uscita sono: %d", Rubrica[i].chiamate_uscita);
            return;
        }
    }

    printf("\nNumero non trovato nella rubrica.");
}




// Funzione che stampa il numero di telefono associato a un cognome e un nome
// Input: Prende dall'utente Nome e Cognome per la ricerca
// Output: Se viene trovato stampa il suo numero di telefono, sennò stampa "contatto non trovato"
void visualizza_numero(char cognome[], char nome[]) {

    int primo = 0;
    int ultimo = numeri_in_rubrica - 1;

    ricerca_ricorsiva(primo, ultimo, cognome, nome);
}

// Funzione di supporto per la ricerca ricorsiva di un contatto nella rubrica
void ricerca_ricorsiva(int primo, int ultimo, char cognome[], char nome[]) {
    if (primo > ultimo) {
        printf("\nIl contatto non si trova nella rubrica!\n");
        return;
    }

    int medio = (primo + ultimo) / 2;

    if (strcmp(Rubrica[medio].cognome, cognome) == 0 && strcmp(Rubrica[medio].nome, nome) == 0) {
        printf("\nIl numero telefonico e': %lld", Rubrica[medio].numero);
        return;
    }

    if (strcmp(Rubrica[medio].cognome, cognome) > 0 || (strcmp(Rubrica[medio].cognome, cognome) == 0 && strcmp(Rubrica[medio].nome, nome) > 0)) {
        ricerca_ricorsiva(primo, medio - 1, cognome, nome);
    }
    else {
        ricerca_ricorsiva(primo + 1, ultimo, cognome, nome);
    }
}


// Funzione che ordina l'array di contatti in base al cognome e al nome
//La function non presenta input o output diretti ma cambia lo stato della rubrica andandolo a riordinare prima per il cognome e poi per il nome
void ordinamento() {
int i, j;
identificativo el_da_ins;

for (i = 1; i < numeri_in_rubrica; i++) {
    el_da_ins = Rubrica[i];
    j = i - 1;

    // Ordina per cognome e poi per nome
    while (j >= 0 && (strcmp(el_da_ins.cognome, Rubrica[j].cognome) < 0 ||
                      (strcmp(el_da_ins.cognome, Rubrica[j].cognome) == 0 &&
                       strcmp(el_da_ins.nome, Rubrica[j].nome) < 0))) {
        Rubrica[j + 1] = Rubrica[j];
        j--;
    }

    Rubrica[j + 1] = el_da_ins;
}
}

// Funzione che inserisce un nuovo contatto nella rubrica
// Input: Dati da inserire nelle Rubrica
// Output: se la rubrica è piena stampa "Rubrica piena", sennò aggiunge il contatto in rubrica
void inserire_nuovo_numero() {
    identificativo Persona;

    if (numeri_in_rubrica == 30) {
        printf("\nRubrica piena!!");
    } else {
        numeri_in_rubrica++;
        printf("\nInserire nel seguente ordine Nome, Cognome e numero telefonico: ");

        Persona.nome = malloc(50 * sizeof(char));
        Persona.cognome = malloc(50 * sizeof(char));

        scanf("%s", Persona.nome); scanf("%s", Persona.cognome); scanf("%lld", &Persona.numero);
        fflush(stdin);


         Persona.chiamate_entrata = rand() % 10;
         Persona.chiamate_uscita = rand() % 10;

        Rubrica[numeri_in_rubrica - 1] = Persona;


    }

}

// Funzione che stampa l'elenco dei contatti nella rubrica
// Input: Array
//Output: Stampa a video l'array
void visual_array() {
    printf("Sono ora presenti in rubrica:\n");
    int i;
    for (i = 0; i < numeri_in_rubrica; i++) {
        printf("%s %s\n%lld\n\n", Rubrica[i].cognome,Rubrica[i].nome,Rubrica[i].numero);
    }
}

// Funzione che elimina un contatto dalla rubrica
//Input: Nome e Cognome del contatto da eliminare
//Output: Contatto eliminato se vi è nella rubrica, sennò stampa "contatto non trovato"
void elimina_contatto() {
    char cognome[25];
    char nome[25];
    int i;

    printf("Inserisci il Cognome e il Nome del contatto da eliminare: ");
    scanf("%s", cognome);scanf("%s",nome);

    for (i = 0; i < numeri_in_rubrica; i++) {
        if (strcmp(Rubrica[i].cognome, cognome) == 0 && strcmp(Rubrica[i].nome, nome) == 0) {
            int j;

            // Sposta tutti gli elementi successivi di una posizione indietro
            for (j = i; j < numeri_in_rubrica - 1; j++) {
                Rubrica[j] = Rubrica[j + 1];
            }

            numeri_in_rubrica--;
            printf("Contatto eliminato con successo.\n");
            return;
        }
    }
    printf("Il cognome specificato non e' presente nella rubrica.\n");

}

// Funzione che inizializza la rubrica con alcuni contatti di esempio
//La function inizializza una Rubrica con alcuni contatti senza prendere alcun input e non da output diretti
void crea_Rubrica() {
    Rubrica[0].nome = "Rolando";
    Rubrica[0].cognome = "Mattei";
    Rubrica[0].numero = 3262561717;
    Rubrica[0].chiamate_entrata = rand() % 10;
    Rubrica[0].chiamate_uscita = rand() % 10;

    Rubrica[1].nome = "Girolamo";
    Rubrica[1].cognome = "Taddeo";
    Rubrica[1].numero = 3202005050;
    Rubrica[1].chiamate_entrata = rand() % 10;
    Rubrica[1].chiamate_uscita = rand() % 10;

    Rubrica[2].nome = "Mario";
    Rubrica[2].cognome = "Rossi";
    Rubrica[2].numero = 3006001232;
    Rubrica[2].chiamate_entrata = rand() % 10;
    Rubrica[2].chiamate_uscita = rand() % 10;

    Rubrica[3].nome="Giuseppe";
    Rubrica[3].cognome="Verdi";
    Rubrica[3].numero=4005006004;
    Rubrica[3].chiamate_entrata=rand()%10;
    Rubrica[3].chiamate_uscita=rand()%10;

    Rubrica[4].nome="Tommaso";
    Rubrica[4].cognome="Ventola";
    Rubrica[4].numero=2006001414;
    Rubrica[4].chiamate_entrata=rand()%10;
    Rubrica[4].chiamate_uscita=rand()%10;

    Rubrica[5].nome="Giovanni";
    Rubrica[5].cognome="Tommasi";
    Rubrica[5].numero=3001005047;
    Rubrica[5].chiamate_entrata=rand()%10;
    Rubrica[5].chiamate_uscita=rand()%10;

}


