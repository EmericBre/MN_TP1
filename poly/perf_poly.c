#include <stdio.h>
#include <stdlib.h>

#include "poly.h"

#include <x86intrin.h>

static const float duree_cycle = (float) 1 / (float) 2.6 ; // duree du cycle en nano seconde 10^-9

void calcul_flop (char *message, int nb_operations_flottantes, unsigned long long int cycles)
{
  printf ("%s %d operations %f GFLOP/s\n", message, nb_operations_flottantes, ((float) nb_operations_flottantes) / (((float) cycles) * duree_cycle)) ;
  return ;
}

int main (int argc, char **argv)
{
  p_polyf_t p1, p2, p3, p4, p5, p6 ;
  p_monome p1creux, p2creux, p3creux;
  unsigned long long start, end ;
  
  if (argc != 3)
    {
      fprintf (stderr, "deux paramètres (polynomes,fichiers) sont à passer \n") ;
      exit (-1) ;
    }
      
  p1 = lire_polynome_float (argv [1]) ;
  p2 = lire_polynome_float (argv [2]) ;
  p1creux = lire_polynome_creux_float (argv [1]) ;
  p2creux = lire_polynome_creux_float (argv [2]) ;

  printf ("p1 plein = ") ;
  ecrire_polynome_float (p1) ;

  printf ("p2 plein = ") ;
  ecrire_polynome_float (p2) ;

  printf ("p1 creux = ") ;
  ecrire_polynome_creux_float (p1creux) ;

  printf ("p2 creux = ") ;
  ecrire_polynome_creux_float (p2creux) ;

  /*
    ajouter du code pour tester les fonctions
    sur les polynomes
  */
  printf("\n");

  start = _rdtsc () ;
  
        p3 = addition_polynome (p1, p2) ;

  end = _rdtsc () ;

  printf ("Addition polynôme plein : p3 = ") ;
  ecrire_polynome_float (p3) ;
  
  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;
  detruire_polynome (p3) ;

  printf("\n");

  start = _rdtsc () ;
  
        p3creux = addition_polynome_creux (p1creux, p2creux) ;

  end = _rdtsc () ;

  printf ("Addition polynôme creux : p3 = ") ;
  ecrire_polynome_creux_float (p3creux) ;
  
  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1creux->degre, p2creux->degre)+1, end-start) ;
  detruire_polynome_creux (p3creux) ;

  printf("\n");

  start = _rdtsc () ;
  
        p3 = multiplication_polynomes (p1, p2) ;

  end = _rdtsc () ;

  printf ("Multiplication polynôme plein : p3 = ") ;
  ecrire_polynome_float (p3) ;
  
  printf ("multiplication %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;
  detruire_polynome (p3) ;

  printf("\n");

  start = _rdtsc () ;
  
        p3creux = multiplication_polynomes_creux (p1creux, p2creux) ;

  end = _rdtsc () ;

  printf ("Multiplication polynôme creux : p3 = ") ;
  ecrire_polynome_creux_float (p3creux) ;
  
  printf ("multiplication %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1creux->degre, p2creux->degre)+1, end-start) ;
  detruire_polynome_creux (p3creux) ;

  printf("\n");

  start = _rdtsc () ;
  
        p3 = composition_polynome (p1, p2) ;

  end = _rdtsc () ;

  printf ("Composition polynôme plein : p3 = ") ;
  ecrire_polynome_float (p3) ;
  
  printf ("composition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1->degre, p2->degre)+1, end-start) ;
  detruire_polynome (p3) ;

  printf("\n");

  start = _rdtsc () ;
  
        p3creux = composition_polynome_creux (p1creux, p2creux) ;

  end = _rdtsc () ;

  printf ("Composition polynôme creux : p3 = ") ;
  ecrire_polynome_creux_float (p3creux) ;
  
  printf ("composition %Ld cycles\n", end-start) ;
  calcul_flop ("p1+p2", min(p1creux->degre, p2creux->degre)+1, end-start) ;
  detruire_polynome_creux (p3creux) ;

  printf("\n");

  p4 = creer_polynome (1024) ;
  p5 = creer_polynome (1024) ;

  init_polynome (p4, 1.0) ;
  init_polynome (p5, 2.0) ;

    start = _rdtsc () ;
  
        p6 = addition_polynome (p4, p5) ;

  end = _rdtsc () ;

  printf ("addition %Ld cycles\n", end-start) ;
  calcul_flop ("p4+p5", min(p4->degre, p5->degre)+1, end-start) ;
  detruire_polynome (p6) ;

  printf("\n");

  start = _rdtsc () ;
  
        p6 = multiplication_polynomes (p4, p5) ;

  end = _rdtsc () ;

  printf ("multiplication %Ld cycles\n", end-start) ;
  calcul_flop ("p4+p5", min(p4->degre, p5->degre)+1, end-start) ;
  detruire_polynome (p6) ;
  
  
}
