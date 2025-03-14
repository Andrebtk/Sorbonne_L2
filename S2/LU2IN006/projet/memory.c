#include "memory.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
MemoryHandler *memory_init(int size) {
	MemoryHandler *new = malloc(sizeof(MemoryHandler));
	new->memory=malloc(size*sizeof(void*));

	/*demander pour **memory
	for(int i=0; i< ???; i++){
		new->momery[i]=NULL;
	}
	*/
	new->total_size=size;

	Segment *seg = malloc(sizeof(Segment));
	seg->start = 0;
	seg->size = size;
	seg->next = NULL;
	
	new->free_list = seg;
	new->allocated = hashmap_create();
	
	return new;
}

Segment* find_free_segment(MemoryHandler* handler, int start, int size, Segment** prev) {
	Segment* tmp = handler->free_list;
	while(tmp) {
		if ((tmp->start <= start) && (tmp->start+tmp->size >= start+size)) {
			return tmp;
		}
		*prev = tmp;
		tmp = tmp->next;
	}
	
	return NULL;
}

int create_segment(MemoryHandler *handler, const char *name, int start, int size) {
	Segment *prev = NULL;
	Segment *n = find_free_segment(handler, start, size, &prev);
	
	if(n != NULL) {
		Segment *new_seg = malloc(sizeof(Segment));
		new_seg->start = start;
		new_seg->size = size;
		new_seg->next = NULL;
		hashmap_insert(handler->allocated, name, (void*) new_seg);

		if (n->start == new_seg->start && n->size == new_seg->size) { //tout
			if (prev) {
				prev->next = n->next;
			} else {
				handler->free_list = n->next;
			}
			free(n);
		}else if(n->start == new_seg->start){ //debut
			n->start +=new_seg->size;
			n->size -= new_seg->size;
		}else if(n->start + n->size == new_seg->size){//fin
			n->size -= new_seg->size;
		}else { //cas general
			Segment *free2=malloc(sizeof(Segment));
			free2->start = start+size;
			free2->size = n->start + n->size - (start+size);
			free2->next = n->next;
			
			n->size = start - n->start;
			n->next = free2;
		}

	}
	return 0;// ne sais pas quoi retourner
}

int remove_segment(MemoryHandler *handler, const char *name){
	Segment *new = hashmap_get(handler->allocated, name);
	hashmap_remove(handler->allocated,name);
	Segment *seg_free=handler->free_list;
	Segment *prec;

	while (seg_free && seg_free->start < new->start) {
        prec = seg_free;
        seg_free = seg_free->next;
    }

    if (prec && prec->start + prec->size == new->start) {
        prec->size +=new->size;
        free(new);
        new = prec;
    } else {
        new->next = seg_free;
        if (prec) prec->next = new;
        else handler->free_list = new;
    }

    if (seg_free && new->start + new->size == seg_free->start) {
        new->size += seg_free->size;
        new->next =seg_free->next;
        free(seg_free);
    }
	return 0;
}
