#ifndef __GLUETHREAD__
#define __GLUETHREAD__

/* macros */
#define IS_LIST_EMPTY(ptr)	\
	((ptr)->right == NULL && (ptr)->left == NULL)

#define GLTHREAD_TO_STRUCT(func_name, struct_name, field)	\
static inline struct_name * func_name(glthread_t *glptr) {	\
	return ((struct_name *)((char *)(glptr) - 		\
		(char *)&(((struct_name *)0)->field)));		\
}

#define BASE(glptr) ((glptr)->right)

#define ITERATE_GL_BEGIN(glstart, glptr) {			\
	glthread_t *glthread_ptr = 0;				\
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
gl_search(glthread_t *base, void *(*thread_to_struct_func)(glthread_t *),
		void *key, int (*comp_fn)(void *, void *));
#endif


typedef struct glthread_ {
	struct glthread_ *left;
	struct glthread_ *right;
} glthread_t;

/* public APIs to do glthread operations */
void
add_next_to (glthread_t *curr, glthread_t *New);

void
add_before (glthread_t *curr, glthread_t *New);

void
remove_glthread (glthread_t *glthread);

void
init_glthread (glthread_t *glthread);

void
add_to_last (glthread_t *head, glthread_t *New);

void
delete_gl_list (glthread_t *base);

unsigned int
get_gl_list_count (glthread_t *base);

void
glthread_priority_insert (glthread_t *head, glthread_t *New,
		int (*comp_fn)(void *, void *), int offset);

/* endif __GLUETHREAD__ */
#endif
