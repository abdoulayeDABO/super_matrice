#include <stdio.h>
#include <stdlib.h>
#include "supermat.h"

int main(){

    int nl = 3, nc = 4;
    

    // Allocation de la supermatrice
    SUPERMRT sm = allouerSupermat(nl, nc);
    if (sm == NULL) {
        return 1;
    }


    // Remplissage de la supermatrice avec des valeurs de test
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            sm->ligne[i][j] = i * nc + j + 1;
        }
    }

    afficher(sm);
    printf("Element a la position (1, 2) : %5.2f\n", acces(sm, 1, 2));


    // Vérification de la contiguïté
    int result = contiguite(sm);
    if (result == 2) {
        printf("Les lignes de la supermatrice sont contigues en ordre.\n");
    } else if (result == 1) {
        printf("Les lignes de la supermatrice sont contigues en desordre.\n");
    } else {
        printf("Les lignes de la supermatrice ne sont pas contigues.\n");
    }


    // Test de la fonction sousMatrice()
    int l1 = 1, l2 = 2, c1 = 1, c2 = 2;
    SUPERMRT sm_sous = sousMatrice(sm, l1, l2, c1, c2);
    if (sm_sous == NULL) {
        printf("Erreur lors de la creation de la sous-matrice.\n");
    } else {
        // Affichage de la sous-matrice
        printf("Sous-matrice extraite de (%d,%d) a (%d,%d) :\n", l1, c1, l2, c2);
        afficher(sm_sous);
        // Libération de la mémoire de la sous-matrice
        rendreSupermat(sm_sous);
    }

    rendreSupermat(sm);

    return 0;
}
