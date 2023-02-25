#include <stdlib.h>
#include "dbll.h"

/* Routines to create and manipulate a doubly-linked list */

/* create a doubly-linked list */
/* returns an empty list or NULL if memory allocation failed */
struct dbll *dbll_create()
{
  struct dbll *newDbll = (struct dbll *) malloc(sizeof(struct dbll));
  if (newDbll == NULL) return NULL;

  newDbll->first = NULL;
  newDbll->last = NULL;

  return newDbll;
}

int isListEmpty(struct dbll *list) {
  if (list->first == NULL) return 1;
  return 0;
}

int isNodeInList(struct dbll *list, struct llnode *node) {
  if (isListEmpty(list) == 1) return 0;

  struct llnode *curr = list->first;

  while (curr != NULL) {
    if (curr == node) return 1;
    curr = curr->next;
  }

  return 0;
}

/* frees all memory associated with a doubly-linked list */
/* this must also free all memory associated with the linked list nodes */
/* assumes user data has already been freed */
void dbll_free(struct dbll *list)
{
  if (list == NULL) return;
  struct llnode *curr = list->first;

  while (curr != NULL) {
    list->first = list->first->next;
    free(curr);
    curr = list->first;
  }

  free(list);
}

/* iterate over items stored in a doubly-linked list */

/* begin iteration from node start, end iteration at node stop (include stop in iteration) */
/* the list is traversed using the next pointer of each node */

/* if start is NULL, then start is the first node */
/* if end is NULL, then end is the last node */

/* at each node, call the user function f with a pointer to the list,
   a pointer to the current node, and the value of ctx */

/* if f returns 0, stop iteration and return 1 */

/* return 0 if you reached the end of the list without encountering end */
/* return 1 on successful iteration */

int dbll_iterate(struct dbll *list,
				 struct llnode *start,
				 struct llnode *end,
				 void *ctx,
				 int (*f)(struct dbll *, struct llnode *, void *))
{
  struct llnode *curr;
  if (start == NULL) {
    curr = list->first;
  } else {
    curr = start;
  }

  if (end == NULL) end = list->last;

  if (isNodeInList(list, end) == 0) return 0;

  while (curr != end->next) {
    if (f(list, curr, ctx) == 0) return 1;
    curr = curr->next;
  }
  return 1;
}

/* similar to dbll_iterate, except that the list is traversed using
   the prev pointer of each node (i.e. in the reverse direction).

   Adjust accordingly. For example if start is NULL, then start is the
   last node in the list.  If end is NULL, then end is the first node
   in the list.

*/

int dbll_iterate_reverse(struct dbll *list,
						 struct llnode *start,
						 struct llnode *end,
						 void *ctx,
						 int (*f)(struct dbll *, struct llnode *, void *)
						 )
{
  struct llnode *curr;
  if (start == NULL) {
    curr = list->last;
  } else {
    curr = start;
  }

  if (end == NULL) end = list->first;

  if (isNodeInList(list, end) == 0) return 0;

  while (curr != end->prev) {
    if (f(list, curr, ctx) == 0) return 1;
    curr = curr->prev;
  }
  return 1;
}


/* Remove `llnode` from `list` */
/* Memory associated with `node` must be freed */
/* You can assume user_data will be freed by somebody else (or has already been freed) */
void dbll_remove(struct dbll *list, struct llnode *node)
{
  if (list == NULL) return;
  if (isListEmpty(list) == 1) return ;
  if (isNodeInList(list, node) == 0) return;

  if (list->first == node) {
    list->first = node->next;
    if (list->first != NULL) {
      list->first->prev = NULL;
    } else {
      list->last = NULL;
    }
  } else if (list->last == node) {
    list->last = node->prev;
    if (list->last != NULL) {
      list->last->next = NULL;
    } else {
      list->first = NULL;
    }
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  node->prev = NULL;
  node->next = NULL;
  free(node);
}

/* Create and return a new node containing `user_data` */
/* The new node must be inserted after `node` */
/* if node is NULL, then insert the node at the end of the list */
/* return NULL if memory could not be allocated */
struct llnode *dbll_insert_after(struct dbll *list, struct llnode *node, void *user_data)
{
  if (list == NULL) return NULL;
  struct llnode *insertNode = (struct llnode *) malloc(sizeof(struct llnode));
  insertNode->user_data = user_data;

  if (isListEmpty(list) == 1) {
    insertNode->prev = NULL;
    insertNode->next = NULL;
    list->first = insertNode;
    list->last = insertNode;

    return insertNode;
  }

  if (node == NULL) {
    insertNode->prev = list->last;
    insertNode->next = NULL;
    list->last->next = insertNode;
    list->last = insertNode;
  } else if (isNodeInList(list, node) == 1) {
    insertNode->prev = node;
    insertNode->next = node->next;
    if (list->last == node) list->last = insertNode;
    else node->next->prev = insertNode;
    node->next = insertNode;
  }

  return insertNode;
}

/* Create and return a new node containing `user_data` */
/* The new node must be inserted before `node` */
/* if node is NULL, then insert the new node at the beginning of the list */
/* return NULL if memory could not be allocated */
struct llnode *dbll_insert_before(struct dbll *list, struct llnode *node, void *user_data)
{
  if (list == NULL) return NULL;
  struct llnode *insertNode = (struct llnode *) malloc(sizeof(struct llnode));
  insertNode->user_data = user_data;

  if (isListEmpty(list) == 1) {
    insertNode->prev = NULL;
    insertNode->next = NULL;
    list->first = insertNode;
    list->last = insertNode;

    return insertNode;
  }

  if (node == NULL) {
    insertNode->prev = NULL;
    insertNode->next = list->first;
    list->first->prev = insertNode;
    list->first = insertNode;
  } else if (isNodeInList(list, node) == 1) {
    insertNode->prev = node->prev;
    insertNode->next = node;
    if (list->first == node) list->first = insertNode;
    else node->prev->next = insertNode;
    node->prev = insertNode;
  }

  return insertNode;
}

/* create and return an `llnode` that stores `user_data` */
/* the `llnode` is added to the end of list */
/* return NULL if memory could not be allocated */
/* this function is a convenience function and can use the dbll_insert_after function */
struct llnode *dbll_append(struct dbll *list, void *user_data)
{
  return dbll_insert_after(list, NULL, user_data);
}
