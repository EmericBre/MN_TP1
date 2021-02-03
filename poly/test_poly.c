#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "poly.h"


int main (int argc, char **argv)
{
  p_polyf_t p1, p2 ;
  
  if (argc != 3)
    {
      fprintf (stderr, "deux paramètres (polynomes,fichiers) sont à passer \n") ;
      exit (-1) ;
    }
      
  p1 = lire_polynome_float (argv [1]) ;
  p2 = lire_polynome_float (argv [2]) ;

  ecrire_polynome_float (p1) ;
  ecrire_polynome_float (p2) ;

  printf("\nTESTS POLYNOMES PLEINS \n");

  printf("\nEgalité : \n");
  printf("%d\n",egalite_polynome(p1,p2));
  printf("\nAddition : \n");
  ecrire_polynome_float(addition_polynome(p1, p2));
  printf("\nMultiplication : \n");
  ecrire_polynome_float(multiplication_polynomes(p1, p2));
  printf("\nMultiplication scalaire : \n");
  ecrire_polynome_float(multiplication_polynome_scalaire(p1, 5.0));
  printf("\nEvaluation : \n");
  printf("%f",eval_polynome(p1, 2.0));
  printf("\nPuissance : \n");
  ecrire_polynome_float(puissance_polynome(p1, 2));
  printf("\nComposition : \n");
  ecrire_polynome_float(composition_polynome(p1, p2));


  /*
    ajouter du code pour tester les fonctions
    sur les polynomes
  */
}
