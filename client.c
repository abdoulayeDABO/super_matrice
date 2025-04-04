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

    // Affichage de l'élément à la position (1, 2)
    printf("Element a la position (1, 2) : %5.2f\n", acces(sm, 1, 2));


    // Vérification de la contiguïté
    int result = contiguite(sm);
    printf("Resultat de la verification de la contiguite : %d\n", result);
    if (result == 2) {
        printf("Les lignes de la supermatrice sont contigues en ordre.\n");
    } else if (result == 1) {
        printf("Les lignes de la supermatrice sont contigues en desordre.\n");
    } else {
        printf("Les lignes de la supermatrice ne sont pas contigues.\n");
    }

    // Libération de la mémoire
    libererSupermat(sm);

    return 0;
}

