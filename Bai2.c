#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char drinkName[100];
    float price;
    char size;
} DrinkOrder;

typedef struct DrinkNode {
    DrinkOrder order;
    struct DrinkNode* next;
} DrinkNode;

// Queue
typedef struct {
    DrinkNode* front;
    DrinkNode* rear;
} Queue;

// Stack
typedef struct {
    DrinkNode* top;
} Stack;
//Ham khoi tao ngan xep
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}
//Ham khoi tao hang doi
void initStack(Stack* s) {
    s->top = NULL;
}
//Ham kiem tra hang doi co trong hay k
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}
//Ham kiem tra ngan xep co trong hay k
int isStackEmpty(Stack* s) {
    return s->top == NULL;
}
//Ham them phan tu o hang doi
void enqueue(Queue* q, DrinkOrder order) {
    DrinkNode* node = (DrinkNode*)malloc(sizeof(DrinkNode));
    node->order = order; node->next = NULL;
    if (isQueueEmpty(q)) {
        q->front = q->rear = node;
    }
    else {
        q->rear->next = node;
        q->rear = node;
    }
}
//Ham xoa phan tu o ngan xep
DrinkOrder dequeue(Queue* q) {
    DrinkOrder dummy = {"", 0, ' '};
    if (isQueueEmpty(q)) {
        return dummy;
    }
    DrinkNode* temp = q->front;
    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }
    DrinkOrder order = temp->order;
    free(temp);
    return order;
}

void push(Stack* s, DrinkOrder order) {
    DrinkNode* node = (DrinkNode*)malloc(sizeof(DrinkNode));
    node->order = order;
    node->next = s->top;
    s->top = node;
}

DrinkOrder pop(Stack* s) {
    DrinkOrder dummy = {"", 0, ' '};
    if (isStackEmpty(s)) {
        return dummy;
    }
    DrinkNode* temp = s->top;
    s->top = s->top->next;
    DrinkOrder order = temp->order;
    free(temp);
    return order;
}

void printQueue(Queue* q) {
    printf("Danh sach order la:\n");
    DrinkNode* temp = q->front;
    while (temp) {
        printf("%s | %.2f | Size: %c\n", temp->order.drinkName, temp->order.price, temp->order.size);
        temp = temp->next;
    }
}

int main() {
    Queue orders;
    Stack cancel;
    initQueue(&orders);
    initStack(&cancel);
    int choice;
    DrinkOrder order;
    do {
        printf("\n     MENU COFFEE   \n");
        printf("1. Goi mon moi\n");
        printf("2. Huy mon vua goi\n");
        printf("3. Dat lai mon vua bi huy\n");
        printf("4. Hien thi toan bo cac mon dang cho phuc vu\n");
        printf("5. Thoat chuong trinh\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                printf("Ten do uong: ");
                fgets(order.drinkName, 100, stdin);
                order.drinkName[strcspn(order.drinkName, "\n")] = '\0';
                printf("Gia: ");
                scanf("%f", &order.price);
                getchar();
                printf("Size (S/M/L): ");
                scanf("%c", &order.size);
                enqueue(&orders, order);
                break;
            case 2:
                if (!isQueueEmpty(&orders)) {
                    push(&cancel, dequeue(&orders));
                }
                else {
                    printf("Khong co don nao de CANCEL.\n");
                }
                break;
            case 3:
                if (!isStackEmpty(&cancel)) {
                    enqueue(&orders, pop(&cancel));
                }
                else {
                    printf("Khong co don nao de REORDER.\n");
                }
                break;
            case 4:
                printQueue(&orders);
                break;
            case 5:
                printf("Thoat chuong trinh thanh cong.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 5);
    return 0;
}
