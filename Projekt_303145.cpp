#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define CHUNK 1
#define znakiAlFAB 26
#define MAX 26
#define iloscLITER 9 

struct wezel {
    char znak = NULL;
    double prawodopod = NULL;
    struct wezel* nastepny = NULL;
    struct wezel* lewy = NULL;
    struct wezel* prawy = NULL;
};

struct kod_bitowo {
    char znak = NULL;
    char kod_dla_znaku[26] = "";
};

wezel stworzLisc(double war, int znak) {
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
void licz_znaki(const char* ciag, int* liczba_znakow, int rozmiar) {
    char znak = NULL;
    for (int k = 0; k < rozmiar - 1; k++) {
        znak = *(ciag + k);
        *(liczba_znakow + (znak - 97)) = *(liczba_znakow + (znak - 97)) + 1;
    }
}
void licz_prawdopodobienstwo(int* liczba_znakow, double* prawodopod, int rozmiar, int* ile_liter) {
    for (int k = 0; k < 26; k++) {
        if (liczba_znakow[k] > 0) {
            prawodopod[k] = (double(liczba_znakow[k]) / double(rozmiar - 1));
        }
        else
            prawodopod[k] = 0.00;
        if (prawodopod[k] > 0) *(ile_liter) = *(ile_liter)+1;
    }
}
void stworz_tabele_wezlow(wezel* tabela_wezlow, double* prawodopod) {
    for (int k = 0; k < 26; k++) {
        tabela_wezlow[k] = stworzLisc(prawodopod[k], k);
    }
}


void sorotwanieStructury(wezel* tabela, int n) {
    int i = 0, j = 0;
    double tmp = 0;
    char znk = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if ((tabela[j].prawodopod) < (tabela[i].prawodopod) && tabela[i].prawodopod >= 0) {
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

void polacz_wezly_w_liste(struct wezel* element_1, struct wezel* element_2) {
    if (element_2->prawodopod != 0)
        element_1->nastepny = *&(element_2);
    else
    {
        element_1->nastepny = NULL;
    }
}

void zbudujStruktureDrzewsiasta(struct wezel*& root) {
    struct wezel* wezel_tmp, * r, * v1, * v2;
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

        if (root == 0 || (wezel_tmp->prawodopod <= root->prawodopod)) {
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

void wystwietlZnak(struct wezel* root, char znak, char* kod, struct kod_bitowo* kopia_kodu) {
    char kopia[MAX] = "";
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
        if (root != NULL) {
            strncat(kod, pz, 1);
            wystwietlZnak(root->prawy, znak, kod, kopia_kodu);
        }
    }
}
int convert(int n) {
    int dec = 0, i = 0, rem;
    while (n != 0) {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}

int main()
{
    struct wezel tabela_wezlow[26];
    struct kod_bitowo tabela_kodow[znakiAlFAB];
    FILE* ciag_skompresowany = fopen("ciag_skompresowany.txt", "w");
    FILE* ciag_skompresowany_zakodowany = fopen("ciag_skompresowany_zakodowany.txt", "w");
    FILE* tekst = fopen("tekst.txt", "r");
    char znak;
    int  pozycja = 0;
    int  rozmiar = 0;
    int ile_liter = 0;
    int liczba_bitow = 0;
    char* ciag = NULL;
    char* ciag_tmp = NULL;
    ciag = (char*)malloc(1 * sizeof(*ciag));

    while (1) {

        znak = fgetc(tekst);
        znak = tolower(znak);
        if ((znak >= 97 && znak <= 122) || znak == EOF) {
            if (znak == EOF) {
                rozmiar += 1;
                ciag_tmp = (char*)realloc(ciag, rozmiar);
                ciag = ciag_tmp;
                ciag[pozycja++] = '\0';
                break;
            }
            if (rozmiar <= pozycja) {
                rozmiar += 1;
                ciag_tmp = (char*)realloc(ciag, rozmiar);
                if (!ciag_tmp) {
                    free(ciag);
                    ciag_tmp = NULL;
                    break;
                }
                ciag = ciag_tmp;
            }
            ciag[pozycja++] = znak;
        }
        else continue;
    }
    printf("Ciag: %s\n", ciag);
    printf("Liczba obliczonych znakow to: %d\n", rozmiar - 1);

    int  liczba_znakow[26] = { 0 };
    double prawodopod[26] = { 0 };

    licz_znaki(ciag, liczba_znakow, rozmiar);
    licz_prawdopodobienstwo(liczba_znakow, prawodopod, rozmiar, &ile_liter);
    stworz_tabele_wezlow(tabela_wezlow, prawodopod);
    sorotwanieStructury(tabela_wezlow, znakiAlFAB);

    for (int i = 0; i < znakiAlFAB - 1; i++) {
        if (tabela_wezlow[i].prawodopod > 0)
            polacz_wezly_w_liste(&tabela_wezlow[i], &tabela_wezlow[i + 1]);
    }

    struct wezel* root = (struct wezel*)malloc(sizeof(*root));
    root = &tabela_wezlow[znakiAlFAB - ile_liter];
    zbudujStruktureDrzewsiasta(root);

    for (int z = 0; z < znakiAlFAB; z++) {
        char kod[MAX] = "";
        char const zerujKod[MAX] = "";
        strcpy(kod, zerujKod);
        if (liczba_znakow[z] > 0) {
            char zn = z + 97;
            wystwietlZnak(root, zn, kod, &tabela_kodow[z]);
        }
    }
    for (int i = 0; i < rozmiar - 1; i++) {
        int war = ciag[i] - 97;
        fprintf(ciag_skompresowany, "%s", tabela_kodow[war].kod_dla_znaku);
    }

    fclose(ciag_skompresowany);
    fclose(tekst);
    ciag_skompresowany = fopen("ciag_skompresowany.txt", "r");

    rozmiar = 0;
    pozycja = 0;

    char kompresja[9] = "";
    char kompresja_zerowanie[9] = "";

    int osiem = 1;
    znak = NULL;
    while (1) {

        znak = fgetc(ciag_skompresowany);
        if (znak == EOF) {
            if (osiem > 1) {
                while (osiem <= 8 && osiem > 1) {
                    char uzupelnienie = '1';
                    strncat(kompresja, &uzupelnienie, 1);
                    osiem++;
                }
                printf("8_bit:%s     ", kompresja);
                int x = atoi(kompresja);
                printf("Wartosc: %d      ", convert(x));
                printf("Znak dla wartosci: %c \n", convert(x));
                fprintf(ciag_skompresowany_zakodowany, "%c", convert(x));
            }
            break;
        }
        liczba_bitow++;
        strncat(kompresja, &znak, 1);
        if (osiem == 8) {
            printf("8_bit:%s     ", kompresja);
            int x = atoi(kompresja);
            printf("Wartosc: %d      ", convert(x));
            printf("Znak dla wartosci: %c \n", convert(x));
            fprintf(ciag_skompresowany_zakodowany, "%c", convert(x));
            strcpy(kompresja, kompresja_zerowanie);
            osiem = NULL;

        }
        osiem++;
    }

    int bity = 0;
    znak = NULL;



    fclose(ciag_skompresowany);
    remove("ciag_skompresowany.txt");
    fclose(ciag_skompresowany_zakodowany);
    ciag_skompresowany_zakodowany = fopen("ciag_skompresowany_zakodowany.txt", "a");
    fprintf(ciag_skompresowany_zakodowany, "#CS%d", liczba_bitow);
    fclose(ciag_skompresowany_zakodowany);



    free(ciag);
    return 0;
}
