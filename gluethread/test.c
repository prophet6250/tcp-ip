#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "glthread.h"

#define OFFSET(struct_name, field) (unsigned int)&(((struct_name *)0)->field)

typedef struct emp_ {
	int id;
	glthread_t glue;
} emp_t;

GLTHREAD_TO_STRUCT(thread_to_struct, emp_t, glue);

int
ID(emp_t *e1, emp_t *e2)
{
	if (e1->id == e2->id) return 0;
	if (e1->id < e2->id) return 1;
	return -1;
}

int main() 
{
	emp_t e[5];
	glthread_t base;
	glthread_t *curr = NULL;
	init_glthread(&base);

	
	/* aligning the structure to the start of memory, i.e, NULL */
	memset(e, 0, sizeof(emp_t) * 5);
	
	/* making some records */
	e[0].id = 1;
	e[1].id = 2;
	e[2].id = 3;
	e[3].id = 4;
	e[4].id = 5;

	/* priority insertion of records, using the comparator function "ID" */
	glthread_priority_insert(&base, &e[0].glue, ID, OFFSET(emp_t,glue));	
	glthread_priority_insert(&base, &e[1].glue, ID, OFFSET(emp_t,glue));
	glthread_priority_insert(&base, &e[2].glue, ID, OFFSET(emp_t,glue));
	glthread_priority_insert(&base, &e[3].glue, ID, OFFSET(emp_t,glue));
	glthread_priority_insert(&base, &e[4].glue, ID, OFFSET(emp_t,glue));
	printf("all records inserted in the list\n");
	
	/* printing the list */
	ITERATE_GL_BEGIN(&base, curr) {
		emp_t *E = thread_to_struct(curr);
		printf("ID = %d\n", E->id);
	} ITERATE_GL_END(&base, curr);

	return 0;
}

