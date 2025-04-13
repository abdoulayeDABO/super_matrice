#ifndef SUPERMAT_H
#define SUPERMAT_H

#include <stdio.h>
#include <stdlib.h>


#define acces(a, i, j) ((a)->ligne[i][j])

typedef struct {
    int nl;   
    int nc;    
    double **ligne; // tableau de pointeurs vers les lignes
} Supermatrice;


typedef Supermatrice* SUPERMRT;


void afficher(SUPERMRT a);

SUPERMRT allouerSupermat(int nl, int nc);

SUPERMRT superProduit(SUPERMRT a, SUPERMRT b);

void permuterLignes(SUPERMRT a, int i, int j);

SUPERMRT sousMatrice(SUPERMRT a, int Ll, int L2, int cl, int c2);

SUPERMRT matSupermat(double *m, int nld, int ncd, int nle, int nce);

void supermatMat(SUPERMRT sm, double *m, int nld, int ncd, int nle, int nce);

int contiguite(SUPERMRT sm);

void rendreSupermat(SUPERMRT sm);

#endif
