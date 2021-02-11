#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "poly.h"

#include <x86intrin.h>

p_polyf_t creer_polynome(int degre)
{
  p_polyf_t p;

  p = (p_polyf_t)malloc(sizeof(polyf_t));
  p->degre = degre;

  p->coeff = (float *)malloc((degre + 1) * sizeof(float));

  return p;
}

void detruire_polynome(p_polyf_t p)
{
  free(p->coeff);
  free(p);
}

void init_polynome(p_polyf_t p, float x)
{
  register unsigned int i;

  for (i = 0; i <= p->degre; ++i)
    p->coeff[i] = x;
}

p_polyf_t lire_polynome_float(char *nom_fichier)
{
  FILE *f;
  p_polyf_t p;
  int degre;
  int i;
  int cr;

  f = fopen(nom_fichier, "r");
  if (f == NULL)
  {
    fprintf(stderr, "erreur ouverture %s \n", nom_fichier);
    exit(-1);
  }

  cr = fscanf(f, "%d", &degre);
  if (cr != 1)
  {
    fprintf(stderr, "erreur lecture du degre\n");
    exit(-1);
  }
  p = creer_polynome(degre);

  for (i = 0; i <= degre; i++)
  {
    cr = fscanf(f, "%f", &p->coeff[i]);
    if (cr != 1)
    {
      fprintf(stderr, "erreur lecture coefficient %d\n", i);
      exit(-1);
    }
  }

  fclose(f);

  return p;
}

void ecrire_polynome_float(p_polyf_t p)
{
  int i;

  printf("%f + %f x ", p->coeff[0], p->coeff[1]);

  for (i = 2; i <= p->degre; i++)
  {
    printf("+ %f X^%d ", p->coeff[i], i);
  }

  printf("\n");

  return;
}

int egalite_polynome(p_polyf_t p1, p_polyf_t p2)
{
  register unsigned int i;

  if (p1->degre != p2->degre)
  {
    return 0;
  }
  for (i = 0; i <= p1->degre; i++)
  {
    if (p1->coeff[i] != p2->coeff[i])
    {
      return 0;
    }
  }
  return 1;
}

p_polyf_t addition_polynome(p_polyf_t p1, p_polyf_t p2)
{
  p_polyf_t p3;
  register unsigned int i;

  p3 = creer_polynome(max(p1->degre, p2->degre));

  for (i = 0; i <= min(p1->degre, p2->degre); ++i)
  {
    p3->coeff[i] = p1->coeff[i] + p2->coeff[i];
  }

  if (p1->degre > p2->degre)
  {
    for (i = (p2->degre + 1); i <= p1->degre; ++i)
      p3->coeff[i] = p1->coeff[i];
  }
  else if (p2->degre > p1->degre)
  {
    for (i = (p1->degre + 1); i <= p2->degre; ++i)
      p3->coeff[i] = p2->coeff[i];
  }

  return p3;
}

p_polyf_t multiplication_polynome_scalaire(p_polyf_t p, float alpha)
{
  p_polyf_t p2;
  register unsigned int i;

  p2 = creer_polynome(p->degre);

  for (i = 0; i <= p->degre; i++)
  {
    p2->coeff[i] = p->coeff[i] * alpha;
  }

  return p2;
}

float eval_polynome(p_polyf_t p, float x)
{
  register float res = 0.0;
  register unsigned int i;
  for (i = 0; i <= p->degre; i++)
  {
    res += p->coeff[i] * pow(x, i);
  }
  return res;
}

p_polyf_t multiplication_polynomes(p_polyf_t p1, p_polyf_t p2)
{
  p_polyf_t p3;
  register unsigned int i;
  register unsigned int j;

  p3 = creer_polynome(p1->degre + p2->degre);

  init_polynome(p3, 0.0);

  for (i = 0; i <= p1->degre; i++)
  {
    for (j = 0; j <= p2->degre; j++)
    {
      p3->coeff[i + j] += p1->coeff[i] * p2->coeff[j];
    }
  }
  return p3;
}

p_polyf_t puissance_polynome(p_polyf_t p, int n)
{
  p_polyf_t p2;
  register unsigned int i;

  if (n == 0)
  {
    p2 = creer_polynome(0);
    p2->coeff[0] = 1.0;
    return p2;
  }

  p2 = p;
  for (i = 1; i < n; i++)
  {
    p2 = multiplication_polynomes(p2, p);
  }
  return p2;
}

p_polyf_t composition_polynome(p_polyf_t p, p_polyf_t q)
{
  register unsigned int i;
  p_polyf_t poq = creer_polynome(p->degre * q->degre);
  init_polynome(poq, 0);

  for (i = 0; i <= p->degre; i++)
  {
    poq = addition_polynome(poq, multiplication_polynome_scalaire(puissance_polynome(q, i), p->coeff[i]));
  }
  return poq;
}

//------------------------------------------------POLYNOMES CREUX---------------------------------------------------------------//

p_monome creer_monome()
{
  p_monome pmonome;
  pmonome = malloc(sizeof(monome));
  pmonome->degre = 0;
  pmonome->coeff = 0;
  pmonome->suivant = NULL;
  return pmonome;
}

void detruire_polynome_creux(p_monome monome)
{
  if (monome == NULL)
  {
    return;
  }
  detruire_polynome_creux(monome->suivant);
  free(monome);
  return;
}

int egalite_polynome_creux(p_monome m1, p_monome m2)
{
  while (m1 != NULL || m2 != NULL)
  {
    if (m1 == NULL || m2 == NULL) {
      return 0;
    }
    if (m1->coeff != m2->coeff || m1->degre != m2->degre)
    {
      return 0;
    }
    m1 = m1->suivant;
    m2 = m2->suivant;
  }
  return 1;
}

p_monome addition_polynome_creux(p_monome m1, p_monome m2)
{
  p_monome premier;
  p_monome m3 = creer_monome();
  p_monome precedent;
  
  if ((m1 != NULL || m2 != NULL) && (m1->degre == m2->degre))
    {
      m3->coeff = m1->coeff + m2->coeff;
      m3->degre = m1->degre;
      m1 = m1->suivant;
      m2 = m2->suivant;
    }
    else if (m1->degre > m2->degre || m1 == NULL)
    {
      m3->coeff = m2->coeff;
      m3->degre = m2->degre;
      m2 = m2->suivant;
    }
    else if (m1->degre < m2->degre || m2 == NULL)
    {
      m3->coeff = m1->coeff;
      m3->degre = m1->degre;
      m1 = m1->suivant;
    }

    premier = m3;
    precedent = m3;


  while (m1 != NULL || m2 != NULL)
  {
    m3 = creer_monome();

    
    if (m1 == NULL) {
      m3->coeff = m2->coeff;
      m3->degre = m2->degre;
      m2 = m2->suivant;
    }
    else if (m2 == NULL) {
      m3->coeff = m1->coeff;
      m3->degre = m1->degre;
      m1 = m1->suivant;
    }
    else if (m1->degre == m2->degre)
    {
      m3->coeff = m1->coeff + m2->coeff;
      m3->degre = m1->degre;
      m1 = m1->suivant;
      m2 = m2->suivant;
    }
    else if (m1->degre > m2->degre)
    {
      m3->coeff = m2->coeff;
      m3->degre = m2->degre;
      m2 = m2->suivant;
    }
    else if (m1->degre < m2->degre)
    {
      m3->coeff = m1->coeff;
      m3->degre = m1->degre;
      m1 = m1->suivant;
    }
    precedent->suivant = m3;
    precedent = m3;
  }

  
  return premier;
}

void ecrire_polynome_creux_float(p_monome p)
{
  int start = 0;

  while(p != NULL) {
    if(p->degre == 0) {
      printf("%f ", p->coeff);
      start = 1;
    }
    else if(p->degre == 1) {
      if(start == 1){
        printf("+ ");
      }
      printf("%f X ", p->coeff);
      start = 1;
    }
    else {
      if(start == 1){
        printf("+ %f X^%d ", p->coeff, p->degre);
      }
      else {
        printf("%f X^%d ", p->coeff, p->degre);
        start = 1;
      }
    }
    p = p->suivant;
  }
  printf("\n");
  return;
}

p_monome lire_polynome_creux_float(char *nom_fichier)
{
  FILE *f;
  int degre;
  float cr;

  f = fopen(nom_fichier, "r");
  if (f == NULL)
  {
    fprintf(stderr, "erreur ouverture %s \n", nom_fichier);
    exit(-1);
  }

  cr = fscanf(f, "%d", &degre);
  if (cr != 1)
  {
    fprintf(stderr, "erreur lecture du degre\n");
    exit(-1);
  }

  p_monome tete;
  p_monome tmp = creer_monome();
  tete = tmp;
  int i = 0;
  int j;
  j = fscanf(f, "%f", &cr);
  while (j == 1)

  {
    if (cr != 0)
    {
      p_monome monome = creer_monome();
      tmp->suivant = monome;
      monome->coeff = cr;
      monome->degre = i;
      tmp = monome;
    }
    i++;
    j = fscanf(f, "%f", &cr);
  }
  return tete->suivant;
}

p_monome multiplication_polynome_creux_scalaire (p_monome p, float alpha) {

  p_monome current;
  p_monome tete;

  if(p != NULL) {
    current = creer_monome();
    tete = current;
    current->coeff = p->coeff * alpha;
    current->degre = p->degre;
    current->suivant = p->suivant;
    p = p->suivant;
  }
  while (p!=NULL) {
    p_monome suiv = creer_monome();
    suiv->coeff = p->coeff * alpha;
    suiv->degre = p->degre;
    current->suivant = suiv;
    current = current->suivant;
    p = p->suivant;
  }
  return tete;

}

float eval_polynome_creux (p_monome p, float x) {

  register float res = 0.0;
  while (p != NULL)
  {
    res += p->coeff * pow(x, p->degre);
    p = p->suivant;
  }
  return res;

}

p_monome multiplication_polynomes_creux (p_monome p1, p_monome p2) {

  p_monome retour = creer_monome();
  p_monome tetep2 = p2;

  retour->coeff = p1->coeff * p2->coeff;
  retour->degre = p1->degre + p2->degre;
  retour->suivant = NULL;

  if (p2->suivant == NULL) {
    p1 = p1->suivant;
  }
  else {
    p2 = p2->suivant;
  }

  p_monome tete;
  p_monome prec;

  while (p1 != NULL) {
    while (p2 != NULL) {
      p_monome current = creer_monome();
      current->degre = p1->degre + p2->degre;
      current->coeff = p1->coeff * p2->coeff;
      tete = retour;
      while (tete != NULL && tete->degre < current->degre) {
        prec = tete;
        tete = tete->suivant;
      }
      if (tete != NULL && tete->degre == current->degre) {
        tete->coeff += current->coeff;
      }
      else {
        prec->suivant = current;
        current->suivant = tete;
      }
      p2 = p2->suivant;
    }
    p1 = p1->suivant;
    p2 = tetep2;
  }  

  return retour;
}

p_monome puissance_polynome_creux(p_monome p, int n) {
  p_monome p2;
  register unsigned int i;

  if (n == 0)
  {
    p2 = creer_monome();
    p2->coeff = 1.0;
    p2->degre = 0;
    p2->suivant = NULL;
    return p2;
  }

  p2 = p;
  
  for (i = 1; i < n; i++)
  {
    p2 = multiplication_polynomes_creux(p2, p);
  }
  return p2;
}

p_monome composition_polynome_creux (p_monome p, p_monome q) {
  p_monome poq = creer_monome();
  p_monome tmp = creer_monome();
  tmp = p;
  while(tmp != NULL) {
    poq = addition_polynome_creux(multiplication_polynome_creux_scalaire(puissance_polynome_creux(q, tmp->degre), tmp->coeff), poq);
    tmp = tmp->suivant;
  }
  return poq;
}