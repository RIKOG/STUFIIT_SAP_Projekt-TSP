#include <stdio.h>
/* Meno = Richard Gajdošík
 * IDE = CLION
 * MinGW-w64
*/
void sort(int *x, char *y, int sizex){
    for(int i=0; i<sizex; i++){         // porovnávame hodnoty indexov od 0...
        for(int j=0; j<sizex-1; j++){   // ... s ostatnými hodnotami indexov za indexom z prvého for cyklu
            if(x[j] > x[i]){            // ak sme zistili že hodnota v prvom for cykle je väčšia ako hodnota v druhom...
                if(y[j] == y[i]) {      //.. tak si porovnáme či sa zhoduje aj druh vojakov prvého a druhého for cyklu
                    int docasne = x[i]; // Ak áno, spravíme jedoduchú výmenu kde si hodnotu uložíme do nejakej dočasne premennej
                    x[i] = x[j];
                    x[j] = docasne;
                }
            }
        }
    }
}
int main() {
    int x[1000], sizex = 0, sizey = 0;
    char y[1000], c;
    do{
        c = getchar();                   // načítame druh vojaka
        scanf("%d", &x[sizex++]);        // načítame počet skúseností
        if(c >= 'A' && c <= 'Z') {       // zisťujeme či skutočne vojak patrí do našej armády
            y[sizey++] = c;              // zapíšeme druh vojaka do poľa
        }
        else{
            break;
        }
    }while((c = getchar()) != '\n');     // zistíme či nám vstup už skončil stlačením enteru
    sort(x, y, sizex);
    for(int a = 0; a <= sizey-1; a++) {
        printf("%c%d ", y[a], x[a]); // výpis
    }
    return 0;
}