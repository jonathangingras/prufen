#ifndef _PRUF_APPEND_H_
#define _PRUF_APPEND_H_

#include "restrict_include.h"

#define pruf_declare_append(declare_name, container_type, element_type)\
void pruf_##declare_name##_append(container_type container, element_type element) {\
	if(!container->first) {\
		container->first = element;\
	}\
	\
	if(!container->last) {\
		container->last = element;\
	} else {\
		container->last->next = element;\
		container->last = element;\
	}\
	\
	container->size++;\
}

#endif
