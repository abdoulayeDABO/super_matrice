#ifndef SUPERMAT_H
#define SUPERMAT_H

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure de la supermatrice
typedef struct {
    int nl;       // Nombre de lignes
    int nc;       // Nombre de colonnes
    double **ligne; // Tableau de pointeurs vers les lignes de la matrice ( ou un pointeur vers un pointeur sur double)
} Supermatrice;

// Définition du type SUPERMRT comme un pointeur vers Supermatrice
typedef Supermatrice* SUPERMRT;

/** 
    * @brief Macro pour accéder à l'élément de la supermatrice à la position (i, j).
    * @param a Pointeur vers la supermatrice.
    * @param i Indice de la ligne.
    * @param j Indice de la colonne.
 */
 /**
    * (*a).ligne == a->ligne
    * ligne est un pointeur ==> ligne[i] = &(ligne + i)
    * (*a).ligne[i] -> accède à la ième ligne de la supermatrice
    * (*a).ligne[i][j] -> accède à l'élément de la ième ligne et de la jème colonne de la supermatrice 
  */
// syntaxe : #define nom_de_la_macro corps_de_la_macro
// Avantages: plus rapide que les fonctions, pas de surcharge d'appel de fonction
#define acces(a, i, j) ((a)->ligne[i][j])


// Prototype de la fonction d'allocation
SUPERMRT allouerSupermat(int nl, int nc);

// Prototype de la fonction de libération de mémoire
void libererSupermat(SUPERMRT sm);

// Prototype de la fonction d'affichage d'un message
int contiguite(SUPERMRT sm);


#endif


