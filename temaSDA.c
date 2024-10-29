#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertSort(int *tab,int n){
    for(int i = 1;i<n;i++){
        int element = tab[i];
        int precedent = i - 1;
        //
        while(precedent >= 0 && tab[precedent] > element){
            tab[precedent + 1] = tab[precedent];
            precedent--;
        }
        tab[precedent + 1] = element;
    }
    printf("\n");
    printf("Tabloul sortat de insertSort: ");
    for(int i = 0;i<n;i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void selectSort(int *tab,int n){
    for(int i = 0; i<n-1;i++){
        //luam minimul primul element
        int minim = i;
        for(int j = i+1;j<n;j++){
            //gasim elementul minim
            if(tab[j] < tab[minim]){
                minim = j;
            }
        }
        //schimbam elementul
        if(minim != i){
            int aux = tab[i];
            tab[i] = tab[minim];
            tab[minim] = aux;
        }
    }
    printf("Tabloul sortat de selectSort: ");
    for(int i = 0;i<n;i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void bubbleSort(int *tab, int n){
    for(int i = 0;i<n-1;i++){
        //flag pentru verificare de schimbari
        int flag = 0;
        //comparam elementele
        for(int j = 0;j<n-i-1;j++){
            if(tab[j] > tab[j+1]){
                //schimbam elementele
                int aux = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = aux;
                flag = 1; //schimbare
            }
        }
        //nu-s schimbari, tabloul sortat
        if(!flag){
            break;
        }
    }
    printf("Tabloul sortat de bubbleSort: ");
    for(int i = 0;i<n;i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void shakerSort(int *tab, int n){
    int start = 0;
    int end = n-1;
    int flag;

    do{
        flag = 0;
        //stanga->dreapta
        for(int i = start;i<end;i++){
            if(tab[i] > tab[i+i]){
                //schimbam elementele
                int aux = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = aux;
                flag = 1;
            }
        }
        end--; //reducem capatul superior
        if(!flag) break; //nimic schimbari, tablou sortat
        flag = 0;
        //dreapta->stanga
        for(int i = end;i>start;i--){
            if(tab[i] < tab[i-i]){
                //schimbam elementele
                int aux = tab[i];
                tab[i] = tab[i-1];
                tab[i-1] = aux;
                flag = 1;
            }
        }
        start++; //crestem capatul inferior
    }while(flag);
    printf("Tabloul sortat de shakerSort: ");
    for(int i = 0;i<n;i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}


int main(){

    int n;

    //n
    printf("Introduceti n: ");
    scanf("%d", &n);

    //alocam memoria
    int *tablou = (int*)malloc(n * sizeof(int));

    //verificam memoria
    if(tablou == NULL){
        printf("Eroare la alocare");
    }

    //punem elementele in tablou
    for(int i = 0;i<n;i++){

        //descrescator
        tablou[i] = n - i;

        //pentru numere random(0-99)
        //tablou[i] = rand() % 100;
    }

    //afisam tabloul
    printf("Tabloul este: ");
    for(int i = 0;i<n;i++){
        printf("%d ", tablou[i]);
    }
    printf("\n");

    time_t inceput = time(NULL); //timp de inceput
    insertSort(tablou,n);
    //selectSort(tablou,n);
    //bubbleSort(tablou,n);
    //shakerSort(tablou,n);
    time_t sfirsit = time(NULL); //timp de sfarsit
    double timp_total = difftime(sfirsit,inceput);
    printf("Timp de executie: %f sec\n", timp_total);

    //eliberam memoria
    free(tablou);

    return 0;
}
