#include "supermat.h"
#include <stdbool.h> // Pour le type bool

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


/**
    * @brief Vérifie si les lignes de la supermatrice sont contiguës en mémoire.
    * @param sm Pointeur vers la supermatrice à vérifier.
    * @return 2 si les lignes sont contiguës en ordre, 2 contiguës en desordre et 0 dans les autres cas.  
*/
int contiguite(SUPERMRT sm) {
    bool contigu = 0; 
    if (sm == NULL || sm->ligne == NULL) {
        return contigu;
    }

    // Vérification de la contiguïté dans l'ordre
    // Verifier que l'addresse du 1er élément de la ligne i+1 est égale à l'adresse de la ligne i + 1 est nc fois plus loin de l'adresse de la ligne i
    // Une autre façon de faire est de vérifier que l'adresse de la ligne i decalée de nc donne l'adresse de la ligne i + 1
    // &(sm->ligne[i + 1]) == &(sm->ligne[i + nc])
    for (int i = 0; i < sm->nl - 1; i++) {
        if ((sm->ligne[i + 1] - sm->ligne[i]) != sm->nc) {
            contigu = 1;
            break; // Arrêt si on trouve une ligne non contiguë
        }else{
            contigu = 2; 
        }

        // if(&(sm->ligne[i + 1]) != &(sm->ligne[i + sm -> nc])){
        //     contigu = 1;
        //     break; 
        // }else{
        //     contigu = 2; 
        // }
    }

    return contigu;
}
