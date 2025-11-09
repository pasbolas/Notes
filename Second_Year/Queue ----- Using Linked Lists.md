

FIFO

front ------->1 2 3 4 5 6 7 <------ rear


## Code 

### Enqueue

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

void enqueue(int value) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (rear == NULL) {  // queue empty
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    printf("%d enqueued\n", value);
}
```

### Dequeue
```c
void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct Node* temp = front;
    printf("%d dequeued\n", front->data);
    front = front->next;

    if (front == NULL)  // if queue became empty
        rear = NULL;

    free(temp);
}
```


