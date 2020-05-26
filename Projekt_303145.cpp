#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct wezel{
    char znak = NULL;
    float prawodopod = NULL;
    struct wezel* nastepny = NULL;
    struct wezel* lewy = NULL;
    struct wezel* prawy = NULL;
};
struct kod {
    char znak = NULL;
    char kod_dla_znaku[100] = "";
};
wezel stworzLisc(float war, int znak){
    struct wezel tmp;
    if (war > 0)
        tmp.prawodopod = war;
    else
        tmp.prawodopod = 0.00;
    tmp.znak = znak + 97;

    tmp.lewy = NULL;
    tmp.prawy = NULL;
    tmp.nastepny = NULL;

    return tmp;
}
void sorotwanieStructury(wezel* tabela, int n) {
    int i = 0, j = 0;
    float tmp = 0;
    char znk = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if ((tabela[j].prawodopod) < (tabela[i].prawodopod) && tabela[i].prawodopod >= 0){
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
void polacz_wezly_w_liste( struct wezel* element_1, struct wezel* element_2){
    if(element_2->prawodopod != 0)
        element_1->nastepny = *&(element_2);
    else
    {
        element_1->nastepny = NULL;
    }
}
void zbudujStruktureDrzewsiasta(struct wezel *&root){
    struct wezel* wezel_tmp, * r, * v1, *v2;
    while (true)
    {
        v1 = root;
        v2 = v1->nastepny;

        if (v2 == 0) break;

        root = v2->nastepny;

        wezel_tmp = (struct wezel*)malloc(sizeof(*wezel_tmp));

        wezel_tmp->lewy = v1;
        wezel_tmp->prawy = v2;
        wezel_tmp->prawodopod = v1->prawodopod + v2->prawodopod;

        if (root == 0 || (wezel_tmp->prawodopod <= root->prawodopod)){
            wezel_tmp->nastepny = root;
            root = wezel_tmp;   
            continue;
        }
        r = root;
        while (r->nastepny != 0 && (wezel_tmp->prawodopod > r->nastepny->prawodopod)) {

            r = r->nastepny;
        }

            wezel_tmp->nastepny = r->nastepny;
            r->nastepny = wezel_tmp;
    }
}
void wystwietlZnak(struct wezel* root, char znak, char *kod, struct kod* kopia_kodu) {
    char kopia[100] = "";
    char lz[2] = "0";
    char pz[2] = "1";
    if (root != NULL && znak == root->znak) {
        printf("Znak w wezle to: %c, ", root->znak);
        printf("To jest kod: %s \n", kod);
        strcpy(kopia_kodu->kod_dla_znaku, kod);
    }
    else
    {
        strcpy(kopia, kod);
        if (root != NULL) {
            strncat(kod, lz, 1);
            wystwietlZnak(root->lewy, znak, kod, kopia_kodu);
        }
        strcpy(kod, kopia);
        if (root != NULL){
            strncat(kod, pz, 1);
            wystwietlZnak(root->prawy, znak, kod, kopia_kodu);
        }
    }
}
int main()
{
    char znak;
    int liczba_znakow[26] = { 0 };
    float prawodopod[26] = { 0 };
    float dlugosc = 0;
    int ile_liter = 0;
    struct wezel tabelaLISCI[26];
    struct kod tabelaKODOW[26];

    char ciag1[] = "aaabbbcccddd";

    printf("Podany zostal ciag:  ");
    printf(ciag1); printf("\n");



            dlugosc = (sizeof(ciag1)) - 1;

            for (int k = 0; k < dlugosc; k++) {
                znak = ciag1[k];
                liczba_znakow[znak - 97]++;
            }
            for (int k = 0; k < 26; k++) {
                if (liczba_znakow[k] > 0) {
                    prawodopod[k] = (liczba_znakow[k] / dlugosc);
                    ile_liter++;
                }
                else
                    prawodopod[k] = 0.00;
            }
    /* for (int k = 0; k < 26; k++) {
         czyJeden += prawodopod[k];
     }

    for (int m = 0; m < 26; m++) {
        printf("Znak %c wystepuje: %d \n", (m + 97), liczba_znakow[m]);
    }
    printf("\n");
    

            

            for (int k = 0; k < 26; k++) {
               
                printf("Prawdopodobienstwo dla %c wynosi %f \n", tabelaLISCI[k].znak, tabelaLISCI[k].prawodopod);
            }
            printf("\n");

       

            printf("PO SORTOWANIU \n");
            printf("\n");

           for (int k = 0; k < 26; k++) {

               printf("Prawdopodobienstwo dla %c wynosi %f \n", tabelaLISCI[k].znak, tabelaLISCI[k].prawodopod);
           }
*/
            for (int k = 0; k < 26; k++) {

                tabelaLISCI[k] = stworzLisc(prawodopod[k], k);

            }

            sorotwanieStructury(tabelaLISCI, 26);

           for (int i = 0; i < 25; i++) {
               if (tabelaLISCI[i].prawodopod > 0)
                   polacz_wezly_w_liste(&tabelaLISCI[i], &tabelaLISCI[i + 1]);
           }

           struct wezel* root = (struct wezel*)malloc(sizeof(*root));
           root = &tabelaLISCI[26-ile_liter];
         
           zbudujStruktureDrzewsiasta(root);

           for (int z = 0; z <= 26; z++) {
               char kod[100] = "";
               char const zerujKod[100] = "";
               strcpy(kod, zerujKod);
               if (liczba_znakow[z] > 0) {
                   char zn = z + 97;
                    wystwietlZnak(root, zn, kod,&tabelaKODOW[z]);
               }
           }

           printf("Podany ciag w postaci skompresowanej: \n");
           for (int i = 0; i <= dlugosc; i++) {
               int war = ciag1[i] - 97;
              printf("%s", tabelaKODOW[war].kod_dla_znaku);
           }

    return 0;

}

