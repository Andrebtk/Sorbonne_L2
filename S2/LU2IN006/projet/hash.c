#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fonction pour affichier une structure Hashmap
void afficher_hashmap(HashMap* hp){
	if (hp == NULL) return;
	printf("size : %d\n", hp->size);
	printf("current_mem : %d\n", hp->current_mem);

	for (int i = 0; i < TABLE_SIZE; i++) {
		char *k = hp->table[i].key;
		void *v = hp->table[i].value;
		if (k && k != TOMBSTONE && v && v != TOMBSTONE) {
		  printf("table[%d] : key = %s, value = %d\n",
				 i, k, *(int*)v);
		}
	  }
}

//Fonction de hachage
unsigned long simple_hash(const char *str) {
	unsigned long res=0;
	
	for(int i=0; str[i] != '\0';i++) {
		res += (int) (str[i]);
	}
	
	return res % TABLE_SIZE;
}

//Fonction de probing
int h(const char *str, int i) {
	return (int) (simple_hash(str) + i);
}

//Fonction qui alloue et initialise une table de hachage
HashMap *hashmap_create() {
	HashMap *new = malloc(sizeof(HashMap));
	new->size = TABLE_SIZE;
	new->table = malloc(sizeof(HashEntry) * TABLE_SIZE );

	for (int i=0; i < TABLE_SIZE; i++) {
		new->table[i].value = NULL;
        new->table[i].key = NULL;
	}
	return new;
}

//Fonction qui insère un élément dans la table de hachage map
int hashmap_insert(HashMap *map, const char *key, void *value) {
	int i=0;
	unsigned long k = h(key,i);
	
	while ((map->table[k].key != TOMBSTONE) && (map->table[k].key != NULL)) {
		i++;
		k = (h(key,i) % map->size);
		if (i > map->size){
			return -1; // pas de place insertion raté
		}
	}
	map->table[k].key = strdup(key);
	map->table[k].value = value;

	return 0; //insertion réussi
}

//Fonction permettant de récupérer un élément à partir de sa clé
void *hashmap_get(HashMap *map, const char *key) {
	int i=0;
	unsigned long k = h(key,i);
	
	while (map->table[k].key != NULL) {
		if(strcmp(map->table[k].key,key)==0) {
			return map->table[k].value;
		}
		i++;
		k = (h(key,i) % map->size); 	
	}
	return NULL;
}

//Fonction qui supprime un élément dans la table de hachage map
int hashmap_remove(HashMap *map, const char *key) {
    int i = 0;
    unsigned long k = h(key, i);

    while (map->table[k].key != NULL) {
        if (strcmp(map->table[k].key, key) == 0) {
            map->table[k].key = TOMBSTONE;
            map->table[k].value = TOMBSTONE;
            return 0; //suppression réussi
        }
        i++;
        k = (h(key, i) % map->size);
    }
    return -1; //suppression ratée
}

//Fonction qui libère la mémoire alloué par la table de hachage map
void free_HashMap(HashMap *hm) {
    if (hm != NULL) {
        for (int i = 0; i < hm->size; i++) {
			if(hm->table[i].key != NULL && hm->table[i].key != TOMBSTONE){
				free(hm->table[i].key);
			}

			if(hm->table[i].value != NULL && hm->table[i].value != TOMBSTONE){
				free(hm->table[i].value);
			}
		}
		free(hm->table);
		free(hm);
	}
}
