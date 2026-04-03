#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define righe 80
#define colonne 80
#define Num_Oggetti 1000

/*Prototipi*/
void inizializza_griglia(char griglia[righe][colonne]);
void disposizione_oggetti(char griglia[righe][colonne]);
void visualizza_scacchiera(char griglia[righe][colonne]);
void evoluzione_cellule(char griglia_corrente[righe][colonne], char griglia_seguente[righe][colonne]);


int main(){
    char griglia_corrente[righe][colonne];
    char griglia_seguente[righe][colonne];

    //Inizializza la griglia e distribuisce gli oggetti
    inizializza_griglia(griglia_corrente);
    disposizione_oggetti(griglia_corrente);

    //Array per contenere il numero di step desiderati
    int num_step[]={1,2,3,4,5,10,20,30,40,50,100,150,200,250,300,350,400,450,500,550,600,700,800};
    int totale_steps= sizeof(num_step)/sizeof(num_step[0]);

    //Esegue l'evouluzione delle cellule per ogni step
    for(int step=0; step<totale_steps;step++){
        evoluzione_cellule(griglia_corrente,griglia_seguente);

        //Stampa il numero degli step e visualizza la griglia
        printf("Step %d:\n",num_step[step]);
        visualizza_scacchiera(griglia_seguente);

        // Copia la griglia seguente nella griglia corrente per il prossimo step
        for (int i=0;i<righe;i++){

            for(int j=0;j<colonne;j++){

                griglia_corrente[i][j]=griglia_seguente[i][j];
            }
        }
    }
    return 0;
}







//Inizializza una griglia vuota
//Input-Matrice bidimensionale
//Output:Matrice bidimensionale griglia con caratteri di spazio vuoto (' ').
void inizializza_griglia(char griglia[righe][colonne]){
    for (int i=0;i<righe;i++){
        for (int j=0;j<colonne;j++){
            griglia[i][j]= ' ';
        }
    }
}

//Function per distribuire casualmente gli oggetti sulla griglia di gioco
//Input: Matrice bidimensionale
//Output: La matrice bidimensionale contiene caratteri '*' che rappresentano oggetti disposti casualmente.
void disposizione_oggetti(char griglia[righe][colonne]){
    srand(time(NULL));
    for (int i=0;i<Num_Oggetti;i++){
        int x= rand() % righe;
        int y= rand() % colonne;
        griglia[x][y] = '*';
    }
}

//Function per visualizzare a schermo la griglia di gioco
//Input: Matrice bidimensionale
//Output:Mostra a video il contenuto della matrice bidimensionale
void visualizza_scacchiera(char griglia[righe][colonne]){
    for (int i=0;i<righe;i++){
        for (int j=0;j<colonne;j++){
            printf("%c", griglia[i][j]);
        }
        printf("\n");
    }
}


//Function per l'evoluzione delle cellule secondo le regole descritte nell'Introduzione
//Input:Matrice bidimensionale corrente
//Output: Matrice bidimensionale seguente
void evoluzione_cellule(char griglia_corrente[righe][colonne], char griglia_seguente[righe][colonne]){

    //// Itera su ogni cella nella griglia corrente
    for (int i=0;i<righe;i++){
        for (int j=0;j<colonne;j++){

            int cellule_nere=0;

            //I due cicli for permettono il conteggio delle 8 celle adiacenti alle cella stessa
            for(int ni=-1;ni<=1;ni++){

                for(int nj=-1;nj<=1;nj++){

                    //Calcola l'indice della cella vicina utilizzando la matematica dei modulari per attraversare i bordi
                    int ni_index=(i+ni+righe) %righe;
                    int nj_index=(j+nj+colonne) %colonne;

                    //Controlla se la cella vicina è nera

                    if(griglia_corrente[ni_index][nj_index]== '*'){
                        cellule_nere++;
                    }
                }
            }
            //Applica le regole per determinare lo stato della cella nella griglia successiva

            if(cellule_nere<4 || cellule_nere==5){
                griglia_seguente[i][j]= ' ';
            }
            else if(cellule_nere==4 || cellule_nere>6){
                griglia_seguente[i][j]= '*';
            }
        }
    }
}

