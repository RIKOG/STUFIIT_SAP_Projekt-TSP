#include <stdio.h>
#include <stdlib.h>

//Richard Gajdosik, IDE  = CLION, Windows 10

void ukladanie_hodnot(char *a, int rozmer, int **matica, int *min) {
    int dlzka_cesty = 0;
    for (int i = 0; i < rozmer; i++) {                  //iterácia ide až dokým neprejde celou maticou
        int dalsi_dom = a[i + 1] - 'a';
        dlzka_cesty += matica[a[i] - 'a'][dalsi_dom]; // spočítanie doteraz prejdenej dlžky, matica funguje štýlom, prvý index = kde som, druhý index = kam chcem ísť
        if (dlzka_cesty > *min) {
            break;                                     // ak sme napríklad na pol ceste a už sme prekročili doteraz najmenšiu nameranú cestu spraví sa break, kedže není dôvod pokračovať a iba zbytočne by to zaberalo výkon
        }
    }
    if (dlzka_cesty < *min) {
        *min = dlzka_cesty;                             //ak sme našli novú najmenšiu, zapíšeme si to do min
    }
}

void permutacia(char *str, long long moznosti, int rozmer, int **matica, int *min) {
    int i, j;
    char c;
    while (moznosti--) {                                //while cyklus sa vykonáva kým sa nám neminú všetky možnosti(cesty)
        ukladanie_hodnot(str, rozmer, matica, min);     //vždy na začiatku iterácie vyskúšame vygenerovanú cestu
        i = 2;
        while (str[i - 1] < str[i]) {                   //nájde na ktorom indexe není ľavá strana menšia ako pravá, edcb
            i++;
        }
        j = 1;                                          //výmena začína na prvom indexe a nie na nultom, nakoľko na nultom indexe sa nám momentálne nachádza Ačko ktoré swapovať nechceme
        while (str[j] < str[i]) {                       //nájde na ktorom indexe není ľavá strana menšia ako pravá, porovná prvý index s tým indexom kde sa nachádza i
            j++;
        }
        c = str[j];                                     //uskutoční výmenu
        str[j] = str[i];
        str[i] = c;
        i--;
        for (j = 1; j < i; i--, j++) {
            c = str[i];
            str[i] = str[j];
            str[j] = c;
        }
    }
    for (int l = 0; l < rozmer; l++) {                 //uvoľnenie pamäte
        free(matica[l]);
    }
    free(matica);
    free(str);
}

char *vytvorenie_arrayu(char *str, int *rozmer) {
    int a = 1;
    str = (char *) calloc(*rozmer * 2, sizeof(char));       // allocujeme si dostatočný počet pamäte
    if (str == NULL){                                                       // ak sa nepodarilo alokovat pamat
        printf("Chyba pri alokacii pamate.");
        getchar();
        exit(-1);
    }
    for (int i = *rozmer - 1; i >= 1; i--, a++) {                           // kvôli spôsobu akým funguje moje iteratívne hľadanie možností musím vygenerovať prvotnú vzorku odzadu v podobe "edcb" s tým že začíname na 1 indexe
        str[a] = 'a' + i;
    }
    str[0] = 'a';                                                           // kedže vždy začíname na prvom domčeku, pridáme na nultý index ačko
    str[*rozmer] = 'a';                                                     // a na koniec vzorovej cesty pridáme tiež ačko kedže sa chceme vrátiť na začiatok
    return str;
}

int **vytvorenie_matice_faktorialu(int *rozmer, int **matica, long long *moznosti) {
    matica = (int **) calloc(*rozmer * 2, sizeof(int *));  // vytvoríme si dvojrozmerné pole matica ktorému callocneme pamäť
    if (matica == NULL){                                                  // ak sa nepodarilo alokovat pamat
        printf("Chyba pri alokacii pamate.");
        getchar();
        exit(-1);
    }
    for (int i = 0; i < *rozmer; i++) {
        matica[i] = (int *) calloc(*rozmer, sizeof(int));
    }
    for (int i = 0; i < *rozmer; i++) {                                   // načítame do matice zadané údaje na vstupe
        for (int j = 0; j < *rozmer; j++) {
            scanf("%d", &matica[i][j]);
        }
    }
    *moznosti = 1;                                         // možnosti(faktorial) su nastavené na 1, kedže keby použijem 0 tak mi nasledujúci výpočet na faktoriál nefunguje, kedže 0 * n je stále 0
    for (int i = 1; i <= *rozmer - 1; ++i) {              // spravíme si faktoriál, n-1! kvoli tomu že vždy začíname na prvom domčeku čo nám zmenšuje počet kombinácii
        *moznosti *= i;
    }
    return matica;
}

int main() {
    int **matica, rozmer, min = 10000;
    long long moznosti = 1;
    char *str;
    while (fscanf(stdin, "%d", &rozmer) != EOF) {                               // zacyklené načítavania, vždy po zadaní vstupu správne načíta a vypíše výsledok, po vstupe treba zadať iba enter
        matica = vytvorenie_matice_faktorialu(&rozmer, matica, &moznosti);              // vytvorenie matice o veľkosti počtu domov, zároven vytvorenie n-1! (počet možností ktoré budeme musieť vyskúšať)
        str = vytvorenie_arrayu(str, &rozmer);                                          // vytvorenie charrového arrayu do ktorého si uložíme prvotnú verziu postupnosti po matici ktorú potom budeme vymienať
        permutacia(str, moznosti, rozmer, matica, &min);                                // samotné tvorenie všetkých možností a ich testovanie
        printf("%d\n", min);                                                   // printf samotného finálneho výsledku
        min = 10000;                                                                    // zresetovanie minimum na veľkú hodnotu z dôvodu načítanie ďalšieho výpočtu
    }
    return 0;
}
