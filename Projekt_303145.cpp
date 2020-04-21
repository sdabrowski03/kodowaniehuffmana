#include <stdio.h>
#include <string.h>
struct lisc {
    float prawodopod;
    char znak;
    struct lisc* lewy;
    struct lisc* prawy;

};

struct wezel{
    char znak;
    float prawodopod; 
    struct wezel* lewy;
    struct wezel* prawy;
};

lisc stworzLisc(float war, int znak){
    struct lisc tmp;

    tmp.prawodopod = war;
    tmp.znak = znak + 97;

    tmp.lewy = NULL;
    tmp.prawy = NULL;

    return tmp;
}
/*void  znajdzDwaNajmiejsze(float tablica_prawdopodobienstw[], float* war_1, float* war_2, int* index_1, int* index_2){
    for (int k = 0; k < 26; k++) {
        if ((tablica_prawdopodobienstw[k] < *war_1) && (tablica_prawdopodobienstw[k] != 0)) {
            *war_1 = tablica_prawdopodobienstw[k];
            *index_1 = k;
        }  
    }
    for (int k = 0; k < 26; k++) {
        if ((tablica_prawdopodobienstw[k] < *war_2) && (tablica_prawdopodobienstw[k] != 0) && (k != *index_1)){
            *war_2 = tablica_prawdopodobienstw[k];
            *index_2 = k;
        }
    }
}
*/
void sorotwanieStructury(lisc* tabela, int n) {
    int i = 0, j = 0;
    float tmp = 0;
    char znk = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if ((tabela[j].prawodopod) < (tabela[i].prawodopod)){
                 tmp = (tabela[i].prawodopod);
                 znk = (tabela[i].znak);
                 (tabela[i].prawodopod) = (tabela[j].prawodopod);
                 (tabela[i].znak) = (tabela[j].znak);
                 (tabela[j].prawodopod) = tmp;
                 (tabela[j].znak) = znk;
            }
            else;
        }
    }
}

int main()
{
    char ciag1[] = "aaabbbbbcccaaabcbcbbca";
    printf("Podany zostal ciag:  ");

    printf(ciag1); printf("\n");

    char znak;
    int liczba_znakow[26] = { 0 };
    float prawodopod[26] = { 0 };
    float dlugosc = 0;
    int ile = 0;
    /*
    float war_1 = 1;
    float war_2 = 1;
    float war_3 = 1;
    int index_1 = 0;
    int index_2 = 0;
    int index_3 = 1;
    */
    //struct wezel liczbaLISCI[10];
    //struct wezel liczbaWezlow[10];

    
    struct lisc tabelaLISCI[26];
    struct lisc tabelaWEZLOW[26];
    dlugosc = (sizeof(ciag1)) - 1;

    for (int k = 0; k < dlugosc; k++) {
        znak = ciag1[k];
        liczba_znakow[znak - 97]++;
    }
    for (int k = 0; k < 26; k++) {
        prawodopod[k] = (liczba_znakow[k] / dlugosc);
        if (prawodopod[k] > 0) ile+=1;
    }
    /* for (int k = 0; k < 26; k++) {
         czyJeden += prawodopod[k];
     }*/

    for (int m = 0; m < 26; m++) {
        printf("Znak %c wystepuje: %d \n", (m + 97), liczba_znakow[m]);
    }
    printf("\n");
/*
    for (int m = 0; m < 26; m++) {
        printf("Prawdopodobienstwo dla %c wynosi: %f \n", (m + 97), prawodopod[m]);
    }
    war_3 = prawodopod[1];
    printf("Suma prawdopodobienstw wynosi: %f \n", czyJeden);
    znajdzDwaNajmiejsze(prawodopod, &war_1, &war_2, &index_1, &index_2);
    printf("WAR_1: %f WAR_2: %f Index_1: %d, Index_2: %d \n", war_1, war_2, index_1, index_2);
*/

/*
        a.prawodopod = war_1;
        a.znak = index_1;

        b.prawodopod = war_2;
        b.znak = index_2;

        ab.prawodopod = war_1 + war_2;
        ab.lewy = &a;
        ab.prawy = &b;

        liczbaLISCI[0] = dodajLISC(&war_1, &index_1);
        liczbaLISCI[1] = dodajLISC(&war_2, &index_2);
        liczbaLISCI[2] = dodajLISC(&war_3, &index_3);

        liczbaWezlow[0].prawodopod = (liczbaLISCI[0].prawodopod + liczbaLISCI[1].prawodopod);
        liczbaWezlow[0].lewy = &liczbaLISCI[0];
        liczbaWezlow[0].prawy = &liczbaLISCI[1];

        liczbaWezlow[1].prawodopod = (liczbaWezlow[0].prawodopod + liczbaLISCI[2].prawodopod);
        liczbaWezlow[1].lewy = &liczbaWezlow[0];
        liczbaWezlow[1].prawy = &liczbaLISCI[2];
        */
            for (int k = 0; k <= 26; k++) {
                if (prawodopod[k] != 0) {
                    tabelaLISCI[k] = stworzLisc(prawodopod[k], k);
                }
                else;
            }

            for (int k = 0; k < ile; k++) {

                printf("Prawdopodobienstwo dla %c wynosi %f \n", tabelaLISCI[k].znak, tabelaLISCI[k].prawodopod);
            }
            printf("\n");

       sorotwanieStructury(tabelaLISCI,3);

            printf("PO SORTOWANIU \n");
            printf("\n");

           for (int k = 0; k < ile; k++) {

               printf("Prawdopodobienstwo dla %c wynosi %f \n", tabelaLISCI[k].znak, tabelaLISCI[k].prawodopod);
           }

        /*

           tabelaWEZLOW[0].lewy = &tabelaLISCI[0];
           tabelaWEZLOW[1].lewy = &tabelaWEZLOW[0];

           printf("pradwopodobienstwo: %f", tabelaWEZLOW[1].lewy->lewy->prawodopod);

        */
           
    return 0;

}

