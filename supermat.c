#include "supermat.h"

// Fonction d'allocation d'une supermatrice
SUPERMRT allouerSupermat(int nl, int nc) {
    // Allocation du descripteur de la supermatrice
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(Supermatrice));
    if (sm == NULL) {
        fprintf(stderr, "Erreur d'allocation de la supermatrice\n");
        return NULL;
    }

    // Initialisation des dimensions
    sm->nl = nl;
    sm->nc = nc;

    // Allocation du tableau de pointeurs vers les lignes
    sm->ligne = (double**)malloc(nl * sizeof(double*));
    if (sm->ligne == NULL) {
        fprintf(stderr, "Erreur d'allocation des pointeurs de ligne\n");
        free(sm);
        return NULL;
    }

    // Allocation d'un bloc mémoire unique pour stocker tous les éléments
    double *data = (double*)malloc(nl * nc * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Erreur d'allocation de la mémoire des coefficients\n");
        free(sm->ligne);
        free(sm);
        return NULL;
    }

    // Attribution des pointeurs de ligne
    for (int i = 0; i < nl; i++) {
        sm->ligne[i] = &data[i * nc];
    }

    return sm;
}

// Fonction de libération de la mémoire allouée pour une supermatrice
void libererSupermat(SUPERMRT sm) {
    if (sm != NULL) {
        if (sm->ligne != NULL) {
            free(sm->ligne[0]); // Libère le bloc de données
            free(sm->ligne);     // Libère le tableau de pointeurs
        }
        free(sm); // Libère le descripteur
    }
}
