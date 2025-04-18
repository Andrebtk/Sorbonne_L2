#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


int main(void) {
  int i;
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie=10;

  srand(time(NULL));
  //printf("%f\n",rand());

  Animal *a1 = creer_animal(0,10, energie);
  Animal *a2 = creer_animal(15,35, energie);
  Animal *a3 = creer_animal(2,42, energie);
  Animal *a4 = creer_animal(18,13, energie);
  
  a1->suivant=a2;
  a2->suivant=a3;
  a3->suivant=a4;

  liste_proie=a1;
  ajouter_animal(2,5, energie, &liste_proie);

  Animal *a5 = creer_animal(2,5, energie);
  Animal *a6 = creer_animal(15,35, energie);
  Animal *a7 = creer_animal(9,22, energie);
  Animal *a8 = creer_animal(17,3, energie);
  
  a5->suivant=a6;
  a6->suivant=a7;
  a7->suivant=a8;

  liste_predateur=a5;
  
  bouger_animaux(liste_proie);

  afficher_ecosys(liste_proie,liste_predateur);

  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);

  return 0;
}
