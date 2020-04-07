#include "glthread.h"
#include <stdlib.h>

/* add New next to the curr gl pointer */
void
add_next_to (glthread *curr, glthread *New)
{
	glthread *curr_right = curr->right;

	if (curr_right == NULL) {
		curr->right = New;
		New->left = curr;
		New->right = NULL;
	}
	else {
		curr->right = New;
		New->left = curr;
		New->right = curr_right;
		curr_right->left = New;
	}
	return;
}

/* add New before the curr gl pointer */
void
add_before (glthread *curr, glthread *New)
{
	glthread *curr_left = curr->left;

	curr->left = New;
	New->right = curr;
	
	if (curr_left == NULL) {
		New->left = NULL;
	}
	else {
		curr_left->right = New;
		New->left = curr_left;
	}
	return;
}

/* remove the curr glthread, irrespective of its position in the list */
void
remove_glthread (glthread *curr)
{
	if (curr == NULL) return;

	glthread *curr_left, *curr_right;
	curr_left = curr->left;
	curr_right = curr->right;
	curr = NULL;
	curr->left = NULL, curr->right = NULL;

	if (curr_left == NULL && curr_right == NULL) {
		return;	
	}
	else if (curr_left == 0) {
		curr_right->left = NULL;
	}
	else if (curr_right == 0) {
		curr_left->right = NULL;
	}
	/* there are nodes at both sides of the curr glthread node */
	else {
		curr_left->right = curr_right;
		curr_right->left = curr_left;
	}

	/* free (curr); */
	return;
}

void
init_glthread(glthread *glptr)
{
	glptr->left = NULL, glptr->right = NULL;
	return;
}

/* add New node to the last of the glthread list */
void 
add_to_last (glthread *head, glthread *New)
{
	glthread *temp = NULL, *last = NULL;

	/* last will be the pointer to the last node, temp will go beyond the
	 * last node */
	ITERATE_GL_BEGIN(head, temp) {
		last = temp;
	} ITERATE_GL_END(head, temp);

	if (last == NULL) 
		add_next_to (head, New);
	else 
		add_next_to (last, New);
	return;
}

/* delete the entire GL DLL */
void
delete_gl_list (glthread *base)
{
	glthread *temp = NULL;
	ITERATE_GL_BEGIN(base, temp) {
		remove_glthread (temp);
	} ITERATE_GL_END(base, temp);
	return;
}

/* return the count of all the nodes in the list */
unsigned int
get_gl_list_count (glthread *base)
{
	unsigned int count = 0;
	glthread *temp = NULL;

	ITERATE_GL_BEGIN(base, temp) {
		count += 1;
	} ITERATE_GL_END(base, temp);

	/* as an extra NULL node will also be counted in this process */
	return count - 1;
}

void
glthread_priority_insert (glthread *head, glthread *New,
		int (*comp_fn)(void *, void *), int offset)
{
	init_glthread(New);

	glthread *head_right = NULL, 
		   *last = NULL, 
		   *temp = NULL;

	/* if the list has only one node in it */
	if (IS_LIST_EMPTY(head)) {
		add_next_to(head, New);
		return;
	}
	
	head_right = head->right;

	/* one node in front of the base pointer */
	if (head_right->right == NULL) {
		
		/* if the base->right node is the required node, 
		 * insert the New there */
		if (comp_fn (GET_DATA_FROM_OFFSET(head_right,offset),
			GET_DATA_FROM_OFFSET(New,offset)) == -1) {

			add_next_to(head_right, New);
		}
		/* else add the New node next to the base node */
		else {
			add_next_to(head, New);
		}
		return;
	}

	/* two nodes in front of base pointer */
	if (comp_fn(GET_DATA_FROM_OFFSET(New, offset), 
		GET_DATA_FROM_OFFSET(head_right, offset)) == -1) {

		add_next_to(head, New);
		return;
	}

	/* three or more nodes in front of the base pointer */
	ITERATE_GL_BEGIN(head, temp) {
		if (comp_fn(GET_DATA_FROM_OFFSET(New, offset),
			GET_DATA_FROM_OFFSET(temp, offset)) == -1) {

			add_next_to(temp, New);
			return;
		}
		last = temp;
	} ITERATE_GL_END(head, temp);

	/* target node not found, appending at the end of the list */
	add_next_to(last, New);
	return;
}

