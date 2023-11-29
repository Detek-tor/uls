#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
	if (!*list) {
		*list = mx_create_node(data);
		return;
	}
	
	t_list *p = *list;
	
	while (p->next) {
		p = p->next;
	}
	p->next = mx_create_node(data);
}


