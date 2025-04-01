#include <stdio.h>
#include <stdlib.h>

// #inclure supermat.h pour pouvoir utiliser les fonctions de supermat.c
#include "supermat.h"

int main(){
    // test des focntions de supermat.c

    // afficheMessage();

    int nl = 3, nc = 4;
    
    // Allocation de la supermatrice
    SUPERMRT sm = allouerSupermat(nl, nc);
    if (sm == NULL) {
        return 1; // Erreur d'allocation
    }

    // Remplissage de la supermatrice avec des valeurs de test
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            sm->ligne[i][j] = i * nc + j + 1;
        }
    }

    // Affichage de la supermatrice
    printf("Supermatrice de taille %dx%d :\n", nl, nc);
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            printf("%5.2f ", sm->ligne[i][j]);
        }
        printf("\n");
    }

    // Libération de la mémoire
    libererSupermat(sm);

    return 0;
}


