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

    // Test de la fonction sousMatrice()
    // Extraire une sous-matrice de la supermatrice
    int Ll = 1, L2 = 2, cl = 1, c2 = 2;  // On extrait les lignes 1 à 2 et les colonnes 1 à 2
    SUPERMRT sm_sous = sousMatrice(sm, Ll, L2, cl, c2);
    if (sm_sous == NULL) {
        printf("Erreur lors de la création de la sous-matrice.\n");
    } else {
        // Affichage de la sous-matrice
        printf("Sous-matrice extraite de (%d,%d) à (%d,%d) :\n", Ll, cl, L2, c2);
        for (int i = 0; i < sm_sous->nl; i++) {
            for (int j = 0; j < sm_sous->nc; j++) {
                printf("%5.2f ", sm_sous->ligne[i][j]);
            }
            printf("\n");
        }
        // Libération de la mémoire de la sous-matrice
        libererSupermat(sm_sous);
    }

    // Libération de la mémoire
    libererSupermat(sm);

    return 0;
}

