#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


int READLINE_READ_SIZE = 512;
char* STORAGE = NULL;

void init_my_readline(int initialize) {
    READLINE_READ_SIZE = initialize;
}

struct Node {
	char* array;
	struct Node* next;
};

int my_strlen(char* ptr) {
	int index = 0;
	while (ptr[index] != '\0') {
		index += 1;
	}

	return index;
}

void print_head(struct Node** headRef) {
	struct Node* head = *headRef;
	while (head != NULL) {
		printf("%s\n", head->array);
		head = head->next;
	}
}

void my_strcpy_linked_list(struct Node** headRef, char** ptrRef) {
	struct Node* head = *headRef;
	char* ptr = *ptrRef;
	int index = 0;
	int index_1 = 0;

	while (head != NULL) {
		index_1 = 0;
		while (head->array[index_1] != '\0') {
			ptr[index] = head->array[index_1];
			index += 1;
			index_1 += 1;
		}
		head = head->next;
	}
	ptr[index] = '\0';
}

struct Node* Create_Node(struct Node** new_NodeRef) {
	struct Node* new_Node = *new_NodeRef;
	new_Node = (struct Node*)malloc(sizeof(struct Node));
	new_Node->array = (char*)malloc((READLINE_READ_SIZE + 1) * sizeof(char));

	return new_Node;
}

int fill_array(int fd, struct Node** currentNodeRef) {
	struct Node* current = *currentNodeRef;
	int sz;
	sz = read(fd, current->array, READLINE_READ_SIZE);
	current->array[sz] = '\0';
	if (sz <= 0) {
		current = NULL;
	}
	
	return sz;
}

void buffer(char**ptrRef, int fd) {
	char* ptr = *ptrRef;
	struct Node* head = Create_Node(&head);
	int sz = fill_array(fd, &head);
	head->next = NULL;

	if (sz <= 0) {
		ptr = NULL;
	}
	else if (sz <= READLINE_READ_SIZE) {
		int size = sz;
		struct Node* current = NULL;

		int node = 1;
		while (sz == READLINE_READ_SIZE) {
			if (sz < READLINE_READ_SIZE) {
				break;
			}
			else if (node == 1) {
				current = head;
			}
			struct Node* new_node = Create_Node(&new_node);
			current->next = new_node;
			current = new_node;
			
			sz = fill_array(fd, &current);
			size += sz;

			current->next = NULL;
			node += 1;
		}

		ptr = (char*)malloc((size + 1) * sizeof(char));
		my_strcpy_linked_list(&head, &ptr);
		
		READLINE_READ_SIZE = 0;
		*ptrRef = ptr;
	}
	struct Node* current = NULL;
	while (head != NULL) {
		current = head;
		head = head->next;
		free(current->array);
		free(current);
		current = NULL;
	}
}

void my_strcpy(char** ptrRef, char** strRef) {
	char* ptr = *ptrRef;
	char* str = *strRef;
	int index = READLINE_READ_SIZE;
	int index_1 = 0;

	while (ptr[index] != '\n') {
		if (ptr[index] == '\0') {
			break;
		}
		str[index_1] = ptr[index];
		index += 1;
		index_1 += 1;
	}
	str[index_1] = '\0';
	READLINE_READ_SIZE = index + 1;

	*strRef = str;
}

char* my_readline(int fd) {
	if (fd == 0) {
		char* str_1 = NULL;
		return str_1;
	}
	else {
		if (STORAGE == NULL) {
			char* ptr = NULL;
			buffer(&ptr, fd);
			STORAGE = ptr;
		}

		char* ptr = STORAGE;
		if (ptr == NULL) {
			free(ptr);
			return NULL;
		}
		else {
			char* str = NULL;
			int index = READLINE_READ_SIZE;

            if (ptr[index] == '\0') {
				free(ptr);
			}
			else {
				int size = my_strlen(ptr);
				str = (char*)malloc((size + 1) * sizeof(char));
				my_strcpy(&ptr, &str);
            }
            return str;
		}
	}
}

