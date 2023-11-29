#include "../inc/libmx.h"

void mx_pop_front(t_list **head) {
	t_list *p = NULL;
	
	if (!*head) return;
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
	} else {
		p = (*head)->next;
	    	free(*head);
	    	*head = p;
	}
}


