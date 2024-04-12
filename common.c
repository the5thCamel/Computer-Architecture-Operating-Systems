#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mymodule1.h>

struct Node
{
	char* word;
	int wordNum;
	struct Node *next;
	struct Node *prev;
};

struct List
{
	struct Node *head;
	struct Node *tail;
	
};

struct Node *create_node(char *words, int wordNumber) {
  struct Node *node = malloc(sizeof(struct Node));
  if (node == NULL) {
    fprintf (stderr, "%s: Couldn't create memory for the node; %s\n", "linkedlist", strerror(errno));
    exit(-1);
  }
  node->word = strdup(words);
  node->wordNum = wordNumber;
  node->next = NULL;
  node->prev = NULL;
  return node;
}
struct List *create_list() {
  struct List *list = malloc(sizeof(struct List));
  if (list == NULL) {
    fprintf (stderr, "%s: Couldn't create memory for the list; %s\n", "linkedlist", strerror (errno));
    exit(-1);
  }
  list->head = NULL;
  list->tail = NULL;
  
  return list;
}
//this will rid the list of duplicates and sort it simultaneusly. I will do this by performing a modified insertion sort that will remove duplicate nodes.

void make_unique_sort(struct List *list) {
  struct Node *ptr3;
  struct Node *placeholder = list->head;
  struct Node *tmp = placeholder;
  struct Node *tempStor;
  struct Node *tmp2;
  int val = 0;
  placeholder = placeholder->next;
  ptr3 = placeholder;
  tempStor = placeholder->next; //this
  //this loop is responsible for moving the placeholder pointer throughout the linked list
  while(placeholder != NULL) {
     
     //this loop is responsible for moving the current value to the left of all the values it is less than
     
    while(strcmp(ptr3->word, tmp->word) <= 0 && tmp != NULL) {
    //this option will find duplicates and deallocate the duplicate, while changing the next pointer of the original
      if(val == 0) { 
        tmp->next = ptr3->next;
        ptr3 = NULL;
        //free(ptr3);
        break;
      }
      //this option will sort the words by reassigning the pointers of tmp, placeholder, and ptr3. Specifically we will make
      
      else {
      	
      	tmp2 = ptr3->next;
        ptr3->prev = tmp->prev; //this will put ptr3 in front of tmp
        tmp->prev = ptr3; //this will put tmp behind ptr3
        ptr3->next = tmp; //this out ptr3 infront of tmp
        tmp->next = tmp2;//this wil point to the next variable in line crucial. It can't point to 
        placeholder = tempStor->prev;
        //does placeholder even need to be in here? We'll get on that later today alright?
        tmp = ptr3->prev; //this will point tmp to the next lowest term for comparison
        
      }
    }
    
    //this needs to be scrapped for a new method
    tempStor = tempStor->next;
    placeholder = tempStor->prev;
    ptr3 = placeholder;
    tmp = placeholder->prev;
  }
  free(placeholder);
  free(ptr3);
  free(tmp);
  free(tempStor);
  free(tmp2);
  
}

void insert_tail(struct Node *node, struct List *list) {
  if (list->head == NULL && list->tail == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  }
}

void print_list(struct List *list) {
  struct Node *ptr = list->head;  
  
  while (ptr != NULL) {
    printf("%s ", ptr->word);
    ptr = ptr->next;
  }
  free(ptr);
}

void output_list(struct List *list, char *out) {
  struct Node *ptr2 = list->head;
  FILE *output;
  output = fopen(out, "w");
  while(ptr2 != NULL) {
    fprintf(output, "(%s,%d) \n", ptr2->word, ptr2->wordNum);
    ptr2 = ptr2->next;
    
  }
  free(ptr2);
}

//
void destroy_list(struct List *list) {
  struct Node *ptr = list->head;
  struct Node *tmp;  
  while (ptr != NULL) {
    free(ptr->word);
    tmp = ptr;
    ptr = ptr->next;
    free(tmp);
  }
  free(list);
}

//now we need to come up with a way to store unique words in a llist. The llist data structure should limit us to an insertion sort.Are there any other ways of doing this
int main(int argc, char *argv[]) {
	int counter = 1;
	int n = 2;
	int num = argc - 1;
	FILE *stream;
	char *temp;
	struct List *list = create_list();
	struct Node *tmp = NULL;
	while(n <= num - 1)
	{
		//error check
		stream = fopen(argv[n], "r");
		printf("%s", argv[n]);
		if(stream == NULL)
		{
			printf("Could not read file");
			exit(-1);
		}
		else
		{
			//we need to finish this stuff unless we will be in trouble
			//this is how one passes a dynamic string from a file
			while(fscanf(stream, "%ms", &temp) == 1 ) {
				
				tmp = create_node(temp, counter);
				insert_tail(tmp, list);
				free(temp);
				//free(tmp);
				
				//counter += 1;
			}
			fclose(stream);      
		}
		n += 1;
		counter++;
		// this needs to be checked **num++;
		//make_unique(list);
	}
	
	make_unique_sort(list);
	//print_list(list);
	output_list(list, argv[num]);
	destroy_list(list);
	
	return 0;
}
