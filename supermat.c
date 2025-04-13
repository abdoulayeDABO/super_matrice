#include "supermat.h"

/**
 * @brief Allouer l'espace mémoire pour une supermatrice de taille nl x nc.
 * @param nl 
 * @param nc 
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


void afficher(SUPERMRT a) {
    if (a == NULL || a->ligne == NULL) {
        printf("La supermatrice est vide.\n");
        return;
    }

    for (int i = 0; i < a->nl; i++) {
        for (int j = 0; j < a->nc; j++) {
            printf("%10.2f ", a->ligne[i][j]);
        }
        printf("\n");
    }
}


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


void rendreSupermat(SUPERMRT sm) {
    if (sm == NULL) return;
    for (int i = 0; i < sm->nl; i++) {
        free(sm->ligne[i]);
    }
    free(sm->ligne);
    free(sm);
}


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


SUPERMRT superProduit(SUPERMRT a, SUPERMRT b){
    SUPERMRT result;
    result->ligne = NULL; 
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


SUPERMRT matSupermat(double *m, int nld, int ncd, int nle, int nce){

    SUPERMRT sm;
     sm->ligne = NULL; 
     sm->nl = 0;
     sm->nc = 0;
 
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
     if (!sm->ligne) {
         sm->nl = 0;
         sm->nc = 0;
         return sm;
     }
 
     // Construction des pointeurs : chaque ligne[i] pointe vers le début de la ligne i dans le tableau 
     for (int i = 0; i < nle; i++) {
         sm->ligne[i] = m + i * ncd;
     }
     return sm;
}
 

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
 