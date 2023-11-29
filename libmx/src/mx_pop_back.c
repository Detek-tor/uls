#include "../inc/libmx.h"

void mx_pop_back(t_list **head) {
	if (!*head) return;
	if ((*head)->next == NULL) {
		free(*head);
		*head = NULL;
	} else {
		t_list *p = *head;
		while (p->next->next) {
			p = p->next;
		}
		
		free(p->next);
		p->next = NULL;
	}
}


