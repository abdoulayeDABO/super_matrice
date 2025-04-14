#include <stdio.h>
#include <stdlib.h>
#include "supermat.h"

int main(){

    int nl = 4, nc = 4;
    

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

    // Affichage de la supermatrice
    printf("Supermatrice initiale :\n");
    printf("==========================================================\n");
    afficher(sm);
    printf("\n\n");

    // ===========================================================
    // Test du macro acces
    // ===========================================================

    printf("Test de la macro acces :\n");
    printf("==========================================================\n");
    printf("Element a la position (1, 2) : %5.2f\n", acces(sm, 1, 2));
    printf("Element a la position (2, 3) : %5.2f\n", acces(sm, 2, 3));
    printf("Element a la position (3, 0) : %5.2f\n", acces(sm, 3, 0));
    printf("\n\n");

    // ===========================================================
    // Vérification de la contiguïté
    // ===========================================================
    printf("Test de la contiguite :\n");
    printf("==========================================================\n");
    int result = contiguite(sm);
    printf("Contiguite de la supermatrice : %d \n", result);
    if (result == 2) {
        printf("Les lignes de la supermatrice sont contigues en ordre.\n");
    } else if (result == 1) {
        printf("Les lignes de la supermatrice sont contigues en desordre.\n");
    } else {
        printf("Les lignes de la supermatrice ne sont pas contigues.\n");
    }
    printf("\n\n");

    // ===========================================================
    // Test de la fonction sousMatrice()
    // ===========================================================

    printf("Test de la fonction sousMatrice :\n");
    printf("==========================================================\n");
    int l1 = 1, l2 = 2, c1 = 1, c2 = 2;
    SUPERMRT sm_sous = sousMatrice(sm, l1, l2, c1, c2);
    if (sm_sous == NULL) {
        printf("Erreur lors de la creation de la sous-matrice.\n");
    } else {
        // Affichage de la sous-matrice
        printf("Sous-matrice extraite de ligne (%d -> %d) et colone (%d -> %d) :\n", l1, l2, c1, c2);
        afficher(sm_sous);
        // Libération de la mémoire de la sous-matrice
        rendreSupermat(sm_sous);
    }
    printf("\n\n");

    // ===========================================================
    // Test de la fonction superProduit()
    // ===========================================================

    printf("Test de la fonction superProduit :\n");
    printf("==========================================================\n");
    SUPERMRT sm2 = allouerSupermat(nc, nl); // Matrice de dimensions inversées
    if (sm2 == NULL) {
        rendreSupermat(sm);
        return 1;
    }
    // Remplissage de la seconde supermatrice avec des valeurs de test
    for (int i = 0; i < nc; i++) {
        for (int j = 0; j < nl; j++) {
            sm2->ligne[i][j] = (i + 1) * (j + 1);
        }
    }
    // Affichage de la premiere supermatrice
    printf("Premiere supermatrice :\n");
    afficher(sm);
    printf("\n");

    // Affichage de la seconde supermatrice
    printf("Seconde supermatrice :\n");
    afficher(sm2);
    printf("\n");

    // =============================================================
    // Produit des supermatrices
    // =============================================================
    SUPERMRT sm_produit = superProduit(sm, sm2);
    if (sm_produit == NULL) {
        printf("Erreur lors du produit des supermatrices.\n");
    } else {
        // Affichage du résultat
        printf("Produit des supermatrices :\n");
        afficher(sm_produit);
        // Libération de la mémoire du produit
        rendreSupermat(sm_produit);
    }
    // Libération de la mémoire de la seconde supermatrice
    rendreSupermat(sm2);
    printf("\n\n");

    // =============================================================
    // Test de la fonction supermatMat()
    // =============================================================
    printf("Test de la fonction supermatMat :\n");
    printf("==========================================================\n");
    double m1[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };
    supermatMat(sm, (double *)m1, 4, 4, 4, 4);
    // Affichage de la supermatrice après remplissage   
    printf("Supermatrice apres remplissage :\n");
    afficher(sm);
    printf("\n\n");


    // ===============================================================
    // Test de la fonction permuterLignes()
    // ===============================================================
    printf("Test de la fonction permuterLignes :\n");
    printf("==========================================================\n");
    int i = 1, j = 2;
    printf("Avant permutation des lignes %d et %d :\n", i, j);
    afficher(sm);
    permuterLignes(sm, i, j);
    printf("Apres permutation des lignes %d et %d :\n", i, j);
    afficher(sm);
    printf("\n\n");

    // =============================================================
    // Test de la fonction matSupermat()
    // =============================================================

    printf("Test de la fonction matSupermat :\n");
    printf("==========================================================\n");
    double m2[4][4] = {
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3},
        {4, 4, 4, 4}
    };
    SUPERMRT sm2_test = matSupermat((double *)m2, 4, 4, 4, 4);
    if (sm2_test == NULL) {
        printf("Erreur lors de la creation de la supermatrice a partir du tableau.\n");
    } else {
        // Affichage de la supermatrice créée
        printf("Supermatrice creee a partir du tableau :\n");
        afficher(sm2_test);
        // Libération de la mémoire de la supermatrice créée
        rendreSupermat(sm2_test);
    }
    printf("\n\n");


    // ===================================================
    // Test de la fonction supermatMat()
    // ===================================================
    printf("Test de la fonction supermatMat :\n");
    printf("==========================================================\n");
    double m3[4][4] = {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {1, 1, 1, 1}
    };

    supermatMat(sm, (double *)m3, 4, 4, 4, 4);
    // Affichage de la supermatrice après remplissage
    printf("Supermatrice apres remplissage :\n");
    afficher(sm);
    printf("\n\n");

    // Libération de la mémoire de la supermatrice a la fin
    rendreSupermat(sm);
    return 0;
}
