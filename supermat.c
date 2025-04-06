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

        // Methode alternative pour vérifier la contiguïté
        // if(&(sm->ligne[i + 1]) != &(sm->ligne[i + sm -> nc])){
        //     contigu = 1;
        //     break; 
        // }else{
        //     contigu = 2; 
        // }
    }

    return contigu;
}

 //---------------------------------------------------------------------------------------------------------//
//---------------------------------fonction superProduit---------------------------------------------------//


/**
    * @brief calcule le produit matriciel de deux  supermatrices a et b 
    * @param  a  Première supermatrice (dimensions : a.nl x a.nc)
    * @param  b  Deuxième supermatrice (dimensions : b.nl x b.nc)
    * @return Une nouvelle supermatrice représentant le produit a × b,
 *            ou une supermatrice invalide (ex. result.ligne == NULL) 
 *            si la multiplication n’est pas possible ou en cas d’erreur d’allocation.  
*/

SUPERMRT superProduit(SUPERMRT a, SUPERMRT b)
{
    SUPERMRT result;
    result->ligne = NULL; 
    // 1) Pour que a × b soit défini, a->nc doit être égal à b->nl
    if (a->nc != b->nl) {return result;}

    // 2) Allouer la supermatrice résultat de taille (a->nl × b->nc)
    result = allouerSupermat(a->nl, b->nc);
    if (result->ligne == NULL) {
        // Échec d’allocation mémoire
        return result;
    }

    // 3) Effectuer la multiplication : result[i,j] = somme sur k de (a[i,k] * b[k,j])
    for (int i = 0; i < a->nl; i++) {
        for (int j = 0; j < b->nc; j++) {
            double somme = 0.0;
            for (int k = 0; k < a->nc; k++) {
                somme += a->ligne[i][k] * b->ligne[k][j];
            }
            result->ligne[i][j] = somme;
        }
    }

    return result;
}

 //-------------------------------------------------------------------------------------------------------//
//---------------------------------fonction permuterLignes-----------------------------------------------//


/**
    * @brief permuter deux lignes i et j de la matrice a:
     échanger deux lignes revient simplement à échanger les adresses stockées dans le tableau->
      Cela signifie que, pour permuter les lignes i et j, on échange les pointeurs a->ligne[i] et a->ligne[j] 
      sans avoir à copier l'intégralité des éléments de chaque ligne
    * @param  a  supermatrice (dimensions : a->nl x a->nc)
    * @param  i  index de la première ligne a permuter
    * @param  j  index de la deuxième ligne a permuter
    */

    void permuterLignes(SUPERMRT a, int i, int j){
    // controle si les lignes entré existes dans la matrce
    if (i < 0 || i >= a->nl || j < 0 || j >= a->nl) {
        return;
    }

    // Si cest la meme ligne, pas besoin de permuter
    if (i == j) {
        return;
    }

    // Échange des pointeurs de lignes
    double *temp = *(a->ligne + i);
    *(a->ligne + i) = *(a->ligne + j);
    *(a->ligne + j) = temp;
}

 //-------------------------------------------------------------------------------------------------------//
//---------------------------------fonction matSupermat--------------------------------------------------//

/**
 * @brief Transforme une matrice ordinaire en supermatrice, 
 *        - La zone mémoire doit être suffisamment grande pour contenir nLd * nCd éléments->
 *        - nLe et nCe doivent être ≤ nLd et nCd respectivement->
 *        - En cas d’échec d’allocation du tableau de pointeurs, la supermatrice retournée 
 *          aura sm->ligne == NULL 
 *
 * @param m    Adresse du premier élément de la matrice ordinaire->
 * @param nLd  Nombre de lignes "déclaré" de la matrice ordinaire->
 * @param nCd  Nombre de colonnes "déclaré" de la matrice ordinaire->
 * @param nLe  Nombre de lignes "effectif" à considérer dans la supermatrice->
 * @param nCe  Nombre de colonnes "effectif" à considérer dans la supermatrice->
 * @return     Un descripteur de supermatrice qui référence la même zone mémoire que m,
 *             mais n’alloue que le tableau des pointeurs de lignes->
 */

 SUPERMRT matSupermat(double *m, int nLd, int nCd, int nLe, int nCe){

    SUPERMRT sm;
     sm->ligne = NULL; 
     sm->nl = 0;
     sm->nc = 0;
 
     // Vérification de la coherences des parametres
     if (!m || nLd <= 0 || nCd <= 0 || nLe <= 0 || nCe <= 0
         || nLe > nLd || nCe > nCd) {
         
         return sm;
     }
 
     // Initialisation du descripteur
     sm->nl = nLe;
     sm->nc = nCe;
     // Allocation du tableau de pointeurs pour les lignes
     sm->ligne = (double **) malloc(nLe * sizeof(double *));
     if (!sm->ligne) {
         sm->nl = 0;
         sm->nc = 0;
         return sm;
     }
 
     // Construction des pointeurs : chaque ligne[i] pointe vers le début de la ligne i dans le tableau 
     for (int i = 0; i < nLe; i++) {
         sm->ligne[i] = m + i * nCd;
     }
 
     return sm;
 }
 


 //-------------------------------------------------------------------------------------------------------//
//---------------------------------fonction supermatMat--------------------------------------------------//

/**
 * @brief Copie les coefficients d’une supermatrice vers une matrice ordinaire ->
            - Les valeurs QLe et QCe doivent être ≤ sm->nl et sm->nc (pour ne pas dépasser la supermatrice)->
 *          - Elles doivent aussi être ≤ QLd et QCd (pour ne pas dépasser la zone mémoire de destination)->
 *          - Aucune allocation n’est réalisée ici : on suppose m déjà alloué 
 *              pour QLd * QCd éléments->
 *
 * @param sm   Descripteur de la supermatrice source (dimensions : sm->nl x sm->nc)->
 * @param m    Adresse du premier élément de la matrice ordinaire destination->
 * @param QLd  Nombre de lignes "déclaré" de la matrice ordinaire destination->
 * @param QCd  Nombre de colonnes "déclaré" de la matrice ordinaire destination->
 * @param QLe  Nombre de lignes "effectif" à recopier->
 * @param QCe  Nombre de colonnes "effectif" à recopier->
 */
 
 void supermatMat(SUPERMRT sm, double *m, int QLd, int QCd, int QLe, int QCe)
 {
     // Vérification si sm et m existe
     if (!sm->ligne || !m) {
         return;
     }
 
     // Vérifier de les parametres sont coherents 
     if (QLe <= 0 || QCe <= 0 || QLe > sm->nl || QCe > sm->nc
         || QLe > QLd || QCe > QCd) {
         // Paramètres incohérents : on ne fait rien ou on gère l’erreur
         return;
     }
 
     // Recopie des éléments (par lignes)
     for (int i = 0; i < QLe; i++) {
         for (int j = 0; j < QCe; j++) {
             // Position dans la destination : i*QCd + j
             m[i * QCd + j] = sm->ligne[i][j];
         }
     }
 }
 