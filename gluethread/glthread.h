#ifndef __GLUETHREAD__
#define __GLUETHREAD__

/* macros */
#define IS_LIST_EMPTY(ptr)	\
	((ptr)->right == NULL && (ptr)->left == NULL)

#define GLTHREAD_TO_STRUCT(func_name, struct_name, field)	\
static inline struct_name * func_name(glthread *glptr) {	\
	return ((struct_name *)((char *)(glptr) - 		\
		(char *)&(((struct_name *)0)->field)));		\
}

#define BASE(glptr) ((glptr)->right)

#define ITERATE_GL_BEGIN(glstart, glptr) {			\
	glthread *glthread_ptr = 0;				\
	if (BASE(glstart)) { 					\
		glthread_ptr = BASE(glstart);			\
	}							\
	glptr = glthread_ptr;					\
	for (; glthread_ptr; glptr = glthread_ptr) {		\
		glthread_ptr = glptr->right;			\

#define ITERATE_GL_END(glstart, glptr) }}

#define GET_DATA_FROM_OFFSET(glptr, offset)	\
	(void *)((char *)(glptr) - offset)

#if 0
void *
gl_search(glthread *base, void *(*thread_to_struct_func)(glthread *),
		void *key, int (*comp_fn)(void *, void *));
#endif


typedef struct glthread_ {
	struct glthread_ *left;
	struct glthread_ *right;
} glthread;

/* public APIs to do glthread operations */
void
add_next_to (glthread *curr, glthread *New);

void
add_before (glthread *curr, glthread *New);

void
remove_glthread (glthread *glthread);

void
init_glthread (glthread *glthread);

void
add_to_last (glthread *head, glthread *New);

void
delete_gl_list (glthread *base);

unsigned int
get_gl_list_count (glthread *base);

void
glthread_priority_insert (glthread *head, glthread *New,
		int (*comp_fn)(void *, void *), int offset);

/* endif __GLUETHREAD__ */
#endif
