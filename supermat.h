#ifndef SUPERMAT_H
#define SUPERMAT_H

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure de la supermatrice
typedef struct {
    int nl;       // Nombre de lignes
    int nc;       // Nombre de colonnes
    double **ligne; // Tableau de pointeurs vers les lignes de la matrice
} Supermatrice;

// Définition du type SUPERMRT comme un pointeur vers Supermatrice
typedef Supermatrice* SUPERMRT;

// Prototype de la fonction d'allocation
SUPERMRT allouerSupermat(int nl, int nc);

// Prototype de la fonction de libération de mémoire
void libererSupermat(SUPERMRT sm);

#endif // SUPERMAT_H


