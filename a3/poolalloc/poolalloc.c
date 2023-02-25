#include "dbll.h"
#include <stdlib.h>
#include "poolalloc.h"

/*
   a pool-based allocator that uses doubly-linked lists to track
   allocated and free blocks
 */

/* create and initialize a memory pool of the required size */
/* use malloc() or calloc() to obtain this initial pool of memory from the system */
struct memory_pool *mpool_create(size_t size)
{
  /* set start to memory obtained from malloc */
  /* set size to size */
  struct memory_pool *new_pool = (struct memory_pool *) malloc(sizeof(struct memory_pool));
  new_pool->start = (char*) malloc(size * sizeof(char));
  new_pool->size = size;

  /* create a doubly-linked list to track allocations */
  /* create a doubly-linked list to track free blocks */
  new_pool->alloc_list = dbll_create();
  new_pool->free_list = dbll_create();

  /* create a free block of memory for the entire pool and place it on the free_list */
  struct alloc_info *new_info = (struct alloc_info *) malloc(sizeof(struct alloc_info));
  new_info->offset = 0;
  new_info->size = size;
  dbll_append(new_pool->free_list, new_info);

  /* return memory pool object */
  return new_pool;
}

/* ``destroy'' the memory pool by freeing it and all associated data structures */
/* this includes the alloc_list and the free_list as well */
void mpool_destroy(struct memory_pool *p)
{
  /* make sure the allocated list is empty (i.e. everything has been freed) */
  /* free the alloc_list dbll */
  /* free the free_list dbll  */
  /* free the memory pool structure */
  dbll_free(p->alloc_list);
  dbll_free(p->free_list);
  free(p);
}


/* allocate a chunk of memory out of the free pool */

/* Return NULL if there is not enough memory in the free pool */

/* The address you return must be aligned to 1 (for size=1), 2 (for
   size=2), 4 (for size=3,4), 8 (for size=5,6,7,8). For all other
   sizes, align to 16.
*/

void *mpool_alloc(struct memory_pool *p, size_t size)
{

  /* check if there is enough memory for allocation of `size` (taking
	 alignment into account) by checking the list of free blocks */

  /* search the free list for a suitable block */
  /* there are many strategies you can use: first fit (the first block that fits),
	 best fit (the smallest block that fits), etc. */

  /* if no suitable block can be found, return NULL */

  /* if found, create an alloc_info node, store start of new region
	 into offset, set size to allocation size (take alignment into
	 account!), set free to null */

  /* add the new alloc_info node to the memory pool's allocated
	 list */

  /* return pointer to allocated region*/

  struct llnode *free_curr = p->free_list->first;
  if (free_curr == NULL) return NULL;

  struct alloc_info *free_curr_data = free_curr->user_data;

  size_t alloc_size;
  if (size == 1) alloc_size = 1;
  else if (size == 2) alloc_size = 2;
  else if ((size == 3) || (size == 4)) alloc_size = 4;
  else if ((size >= 5) && (size <= 8)) alloc_size = 8;
  else alloc_size = 16;

  while (free_curr != NULL) {
    if (free_curr_data->size >= alloc_size) break;
    free_curr = free_curr->next;
    if (free_curr == NULL) return NULL;
    free_curr_data = free_curr->user_data;
  }

  struct llnode *alloc_curr = p->alloc_list->last;
  size_t padding = 0;

  struct alloc_info *new_info = (struct alloc_info *) malloc(sizeof(struct alloc_info));
  new_info->request_size = size;
  new_info->size = alloc_size;

  if (alloc_curr != NULL) {
    struct alloc_info *alloc_curr_data = alloc_curr->user_data;
    if (alloc_size > (alloc_curr_data->offset + alloc_curr_data->size)) {
      padding = alloc_size - (alloc_curr_data->offset + alloc_curr_data->size);
    }
    new_info->offset = alloc_curr_data->offset + alloc_curr_data->size + padding;
  } else {
    new_info->offset = 0;
  }
  
  if (free_curr_data->size > alloc_size) {
    struct alloc_info *newly_cut = (struct alloc_info *) malloc(sizeof(struct alloc_info));
    newly_cut->size = free_curr_data->size - alloc_size;
    newly_cut->offset = free_curr_data->offset + alloc_size;
    dbll_insert_before(p->free_list, free_curr, newly_cut);
  }
  dbll_remove(p->free_list, free_curr);
  dbll_append(p->alloc_list, new_info);
  
  return p->start;
}

/* Free a chunk of memory out of the pool */
/* This moves the chunk of memory to the free list. */
/* You may want to coalesce free blocks [i.e. combine two free blocks
   that are are next to each other in the pool into one larger free
   block. Note this requires that you keep the list of free blocks in order */
void mpool_free(struct memory_pool *p, void *addr)
{
  /* search the alloc_list for the block */
  /* move it to the free_list */
  /* coalesce the free_list */
}
