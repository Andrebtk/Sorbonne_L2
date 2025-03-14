#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned long simple_hash(const char *str) {
	unsigned long res=0;
	
	for(int i=0; str[i] != '\0';i++) {
		res += (int) (str[i]);
	}
	
	return res % TABLE_SIZE;
}

int h(const char *str, int i) {
	return (int) (simple_hash(str) + i);
}


HashMap *hashmap_create() {
	HashMap *new = malloc(sizeof(HashMap));
	new->size = TABLE_SIZE;
	new->table = malloc(sizeof(HashEntry*) * TABLE_SIZE );

	for (int i=0; i < TABLE_SIZE; i++) {
		new->table[i].value = NULL;
	}
	
	return new;
}

int hashmap_insert(HashMap *map, const char *key, void *value) {
	 HashEntry* elem = malloc(sizeof(HashEntry));;
	 elem->key = strdup(key);
	 elem->value = value;
	 
	 int i=0;
	 unsigned long k = h(key,i);
	 
	 while ((map->table[k].key != TOMBSTONE) && (map->table[k].key != NULL)) {
	 	i++;
	 	k = (h(key,i) % map->size); 	
	 }
	 map->table[k].key = elem->key;
	 map->table[k].value = elem->value;
	 return k;
}


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


int hashmap_remove(HashMap *map, const char *key) {
    int i = 0;
    unsigned long k = h(key, i);

    while (map->table[k].key != NULL) {
        if (strcmp(map->table[k].key, key) == 0) {
            map->table[k].key = TOMBSTONE;
            map->table[k].value = TOMBSTONE;
            return 1;
        }
        i++;
        k = (h(key, i) % map->size);
    }

    return 0;
}





void hashmap_destroy(HashMap *map) {
    for (int i = 0; i < map->size; i++) {
        if (map->table[i].key != NULL && map->table[i].key != TOMBSTONE) {
            free(map->table[i].key);
			free(map->table[i].value);
        }
    }
    free(map->table);
    free(map);
}



/*parce que tu n'as pas de main.c
#include <stdio.h>
#include "hash.h"
#include "memory.h" 
#include "hash.c"
#include "memory.c" 

void print_free_list(MemoryHandler *handler) {
    Segment *current = handler->free_list;
    printf("free_list:\n");
    while (current != NULL) {
        printf("  Start: %d, Size: %d\n", current->start, current->size);
        current = current->next;
    }
}



int main() {
    // Initialisation du gestionnaire de mémoire
    MemoryHandler *handler= memory_init(1024);

    printf("\nCréation de segments mémoire\n");
    create_segment(handler, "test1", 100, 50);
    create_segment(handler, "test2", 200, 75);
    create_segment(handler, "test3", 500, 100);
    print_free_list(handler);
    printf("\n");
    printf("\nSuppression de test2\n");
    remove_segment(handler, "test2");
    print_free_list(handler);
    printf("\n");


    return 0;
}
}*/
