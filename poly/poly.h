/*
  polyf_t   : structure polynome
  p_polyf_t : pointeur sur un polynome
*/

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef struct {
  int degre ;
  float *coeff;
} polyf_t, *p_polyf_t;

p_polyf_t creer_polynome (int degre) ;

void init_polynome (p_polyf_t p, float x) ;

void detruire_polynome (p_polyf_t p) ;

p_polyf_t lire_polynome_float (char *nom_fichier) ;

void ecrire_polynome_float (p_polyf_t p) ;

int egalite_polynome (p_polyf_t p1, p_polyf_t p2) ;

p_polyf_t addition_polynome (p_polyf_t p1, p_polyf_t p2) ;

p_polyf_t multiplication_polynome_scalaire (p_polyf_t p, float alpha) ;

float eval_polynome (p_polyf_t p, float x) ;

p_polyf_t multiplication_polynomes (p_polyf_t p1, p_polyf_t p2) ;

p_polyf_t puissance_polynome (p_polyf_t p, int n) ;

p_polyf_t composition_polynome (p_polyf_t p, p_polyf_t q) ;

typedef struct mon {
  int degre ;
  float coeff;
  struct mon *suivant;
} monome, *p_monome;

p_monome creer_polynome_creux (int degre) ;

p_monome creer_monome();

void detruire_polynome_creux(p_monome monome);

int egalite_polynome_creux (p_monome m1, p_monome m2) ;

p_monome addition_polynome_creux (p_monome p1, p_monome p2) ;

void detruire_polynome_creux (p_monome p) ;

void ecrire_polynome_creux_float (p_monome p);

p_monome lire_polynome_creux_float (char *nom_fichier) ;

void init_polynome_creux (p_monome p, float x) ;

p_monome multiplication_polynome_creux_scalaire (p_monome p, float alpha) ;

float eval_polynome_creux (p_monome p, float x) ;

p_monome multiplication_polynomes_creux (p_monome p1, p_monome p2) ;

p_monome puissance_polynome_creux (p_monome p, int n) ;

p_monome composition_polynome_creux (p_monome p, p_monome q) ;

