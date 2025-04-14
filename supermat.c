#include "supermat.h"

/**
 * @brief Allouer l'espace mémoire pour une supermatrice de taille nl x nc.
 * @param nl: nombre de lignes
 * @param nc: nombre de colonnes
 * @return SUPERMRT 
 */
SUPERMRT allouerSupermat(int nl, int nc) {

    // Allocation de la supermatrice
    SUPERMRT sm = (SUPERMRT)malloc(sizeof(Supermatrice));
    if (sm == NULL) {
        fprintf(stderr, "Erreur d'allocation de la supermatrice\n");
        return NULL;
    }

    // Initialisation des dimensions
    sm->nl = nl;
    sm->nc = nc;

    // Allocation d'un tableau de pointeurs pour les lignes
    sm->ligne = (double**)malloc(nl * sizeof(double*));
    if (sm->ligne == NULL) {
        fprintf(stderr, "Erreur d'allocation des pointeurs de ligne\n");
        free(sm);
        return NULL;
    }

    // Allocation d'un tableau de coefficients
    double *data = (double*)malloc(nl * nc * sizeof(double));
    if (data == NULL) {
        fprintf(stderr, "Erreur d'allocation de la mémoire des coefficients\n");
        free(sm->ligne);
        free(sm);
        return NULL;
    }

    // Initiasation du tableau de pointeurs contenant les adresses des lignes
    for (int i = 0; i < nl; i++) {
        sm->ligne[i] = &data[i * nc]; // on decale chaque fois de nc pour assigner  a ligne[i] l'addresse de la ieme ligne
    }

    return sm;
}


/**
 * @brief Affche les coeficients de la supermatrice.
 * 
 * @param sm : la supermatrice a afficher
 * @return void 
 */
void afficher(SUPERMRT sm) {
    if (sm == NULL || sm->ligne == NULL) {
        printf("La supermatrice est vide.\n");
        return;
    }

    for (int i = 0; i < sm->nl; i++) {
        for (int j = 0; j < sm->nc; j++) {
            printf("%10.2f ", sm->ligne[i][j]);
        }
        printf("\n");
    }
}


/**
 * @brief Verifie si les lignes de la supermatrice est contigue ou non.
 * 
 * @param sm : la supermatrice
 * @return int : 0 si les lignes ne sont pas contigues, 1 si elles le sont mais en desordre, 2 si elles le sont en ordre.
 */
int contiguite(SUPERMRT sm) {
    int contigu = 0; 
    if (sm == NULL || sm->ligne == NULL) {
        return contigu;
    }

    for (int i = 0; i < sm->nl - 1; i++) {

         if ((sm->ligne[i + 1] - sm->ligne[i]) != sm->nc) {
            contigu = 1;
            break;
        }

        // Erreur d'implementation : apres le break contigu est tj a 1
        // if ((sm->ligne[i + 1] - sm->ligne[i]) != sm->nc) {
        //     contigu = 1;
        //     break;
        // }else{
        //     contigu = 2; 
        // }

        // Methode alternative pour vérifier la contiguïté
        // if(&(sm->ligne[i + 1]) != &(sm->ligne[i + sm -> nc])){
        //     contigu = 1;
        // }
    }

    contigu = 2; 
    return contigu;
}


/**
 * @brief Liber la mémoire allouée pour la supermatrice.
 * 
 * @param sm 
 * @return void 
 */
void rendreSupermat(SUPERMRT sm) {
    if (sm == NULL) return;
    for (int i = 0; i < sm->nl; i++) {
        free(sm->ligne[i]);
    }
    free(sm->ligne);
    free(sm);
}


/**
 * @brief Extrait une sous-matrice de la supermatrice donnée.
 * 
 * @param a : la supermatrice d'origine
 * @param l1 : indice de la première ligne de la sous-matrice
 * @param l2 : indice de la dernière ligne de la sous-matrice
 * @param c1 : indice de la première colonne de la sous-matrice
 * @param c2 : indice de la dernière colonne de la sous-matrice
 * @return SUPERMRT : Un pointeur vers la nouvelle supermatrice contenant la sous-matrice extraite.
 */
SUPERMRT sousMatrice(SUPERMRT a, int l1, int l2, int c1, int c2) {
    // Vérification de la validité des indices
    if (l1 < 0 || l2 >= a->nl || c1 < 0 || c2 >= a->nc || l1 > l2 || c1 > c2) {
        fprintf(stderr, "Indices invalides pour la sous-matrice.\n");
        return NULL; // Retourne NULL si les indices sont incorrects
    }

    // Allouer la nouvelle supermatrice pour la sous-matrice (seulement la structure)
    SUPERMRT sm_sous = (SUPERMRT)malloc(sizeof(Supermatrice));
    if (sm_sous == NULL) {
        fprintf(stderr, "Erreur d'allocation de la supermatrice.\n");
        return NULL; 
    }

    // Initialiser les dimensions de la sous-matrice
    sm_sous->nl = l2 - l1 + 1;
    sm_sous->nc = c2 - c1 + 1;

    // Allouer un tableau de pointeurs vers les lignes de la sous-matrice
    sm_sous->ligne = (double**)malloc(sm_sous->nl * sizeof(double*));
    if (sm_sous->ligne == NULL) {
        fprintf(stderr, "Erreur d'allocation des pointeurs de ligne de la sous-matrice.\n");
        free(sm_sous);
        return NULL;  
    }

    // Configurer les lignes de la sous-matrice pour qu'elles pointent vers les lignes correspondantes de la supermatrice
    for (int i = l1; i <= l2; i++) {
        sm_sous->ligne[i - l1] = &a->ligne[i][c1];
    }
    return sm_sous;
}

/**
 * @brief Fai  le produit de deux supermatrices.
 * 
 * @param a : La première supermatrice a
 * @param b : La deuxième supermatrice b
 * @return SUPERMRT : Un pointeur vers la supermatrice résultante du produit.
 */
SUPERMRT superProduit(SUPERMRT a, SUPERMRT b){
    SUPERMRT result = (SUPERMRT)malloc(sizeof(Supermatrice));
    if (result == NULL) {
        fprintf(stderr, "Erreur d'allocation de la supermatrice\n");
        return NULL;
    }
    // Pour que a × b soit défini, a->nc doit être égal à b->nl
    if (a->nc != b->nl) {return result;}

    //Allouer la supermatrice résultat de taille (a->nl × b->nc)
    result = allouerSupermat(a->nl, b->nc);
    if (result->ligne == NULL) {
        return result;
    }

    // Effectuer la multiplication : result[i,j] = somme sur k de (a[i,k] * b[k,j])
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

/**
 * @brief Permute les lignes i et j de la supermatrice sm.
 * 
 * @param i : indice de la première ligne
 * @param j : indice de la deuxième ligne
 * @return void
 */
void permuterLignes(SUPERMRT sm, int i, int j){
    // controle si les lignes entré existes dans la matrce
    if (i < 0 || i >= sm->nl || j < 0 || j >= sm->nl) {
        return;
    }

    // Si cest la meme ligne, pas besoin de permuter
    if (i == j) {
        return;
    }

    // Échange des pointeurs de lignes
    double *temp = *(sm->ligne + i);
    *(sm->ligne + i) = *(sm->ligne + j);
    *(sm->ligne + j) = temp;
}



/**
 * @brief Crée une supermatrice à partir d'un tableau de coefficients.
 * 
 * @param m : le tableau de coefficients
 * @param nld : nombre de lignes du tableau
 * @param ncd : nombre de colonnes du tableau
 * @param nle : nombre de lignes de la supermatrice
 * @param nce : nombre de colonnes de la supermatrice
 * @return SUPERMRT : Un pointeur vers la supermatrice créée.
 */
SUPERMRT matSupermat(double *m, int nld, int ncd, int nle, int nce){

    SUPERMRT sm = (SUPERMRT)malloc(sizeof(Supermatrice));
    if (sm == NULL) {
        fprintf(stderr, "Erreur d'allocation de la supermatrice\n");
        return NULL;
    }

     // Vérification de la coherences des parametres
     if (!m || nld <= 0 || ncd <= 0 || nle <= 0 || nce <= 0
         || nle > nld || nce > ncd) {
         
         return sm;
     }
 
     // Initialisation du descripteur
     sm->nl = nle;
     sm->nc = nce;

     // Allocation du tableau de pointeurs pour les lignes
     sm->ligne = (double **) malloc(nle * sizeof(double *));
     if (sm->ligne == NULL) {
         fprintf(stderr, "Erreur d'allocation de la supermatrice\n");
         return sm;
     }
 
     // Construction des pointeurs : chaque ligne[i] pointe vers le début de la ligne i dans le tableau 
     for (int i = 0; i < nle; i++) {
         sm->ligne[i] = m + i * ncd;
     }
     return sm;
}
 

/**
 * @brief Recopie les éléments d'une supermatrice dans un tableau de coefficients.
 * 
 * @param sm : la supermatrice à copier
 * @param m : le tableau de coefficients
 * @param nld : nombre de lignes du tableau
 * @param ncd : nombre de colonnes du tableau
 * @param nle : nombre de lignes de la supermatrice
 * @param nce : nombre de colonnes de la supermatrice
 * @return void 
 */
void supermatMat(SUPERMRT sm, double *m, int nld, int ncd, int nle, int nce){
     // Vérification si sm et m existe
     if (!sm->ligne || !m) {
         return;
     }
 
     // Vérifier de les parametres sont coherents 
     if (nle <= 0 || nce <= 0 || nle > sm->nl || nce > sm->nc
         || nle > nld || nce > ncd) {
         return;
     }
 
     // Recopie des éléments (par lignes)
     for (int i = 0; i < nle; i++) {
         for (int j = 0; j < nce; j++) {
             // Position dans la destination : i*ncd + j
             m[i * ncd + j] = sm->ligne[i][j];
         }
     }
}
 