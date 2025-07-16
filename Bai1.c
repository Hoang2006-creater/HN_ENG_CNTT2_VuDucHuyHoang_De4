#include<stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  {
    int id;
    char name[100];
    char category[100];
    float price;
}Food;
typedef struct Node{
    Food food;
    struct Node* next;
}Node;
typedef struct DNode {
    Food food;
    struct DNode* next;
    struct DNode* prev;
}DNode;
Node*createNode(Food food) {
    Node*newNode=(Node*)malloc(sizeof(Node));
    newNode->food=food;
    newNode->next=NULL;
    return newNode;
}
Node*createDNode(Food food) {
    DNode* newNode=(DNode*)malloc(sizeof(DNode));
    newNode->food=food;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}
//Ham nhap du lieu
Food inputFood() {
    Food food;
    printf("Moi ban nhap ma cua mon an: ");
    scanf("%d",&food.id);
    printf("Moi ban nhap ten cua mon an: ");
    getchar();
    fgets(food.name,100,stdin);
    food.name[strcspn(food.name,"\n")]='\0';
    printf("Moi ban nhap danh muc mon an: ");
    fgets(food.category,100,stdin);
    food.category[strcspn(food.category,"\n")]='\0';
    printf("Moi ban nhap gia mon an: ");
    scanf("%f",&food.price);
    return food;
}
//Ham hien thi
void printFood(Food food) {
    printf("ID: %d| Name: %s| Category: %s| Price: %.2f\n",food.id,food.name,food.category,food.price);
}
//Ham them moi mon a
void addFood(Node**head) {
    Food food=inputFood();
    Node*newNode=createNode(food);
    newNode->next=*head;
    *head=newNode;
    printf("Da them mon an thanh cong");
}
//Ham hien thi mon an
void displayFood(Node*head) {
    if(!head){
        printf("Danh sach trong");
        return;
    }
    printf("Danh sach mon an la: ");
    printf("\n");
    while(head) {
        printFood(head->food);
        head=head->next;
    }
}
//Ham cap nhat mon an
void updateFood(Node*head) {
    int keyId;
    printf("Moi ban nhap thong tin id mon an muon cap nhat: ");
    scanf("%d",&keyId);
    while(head) {
        if(head->food.id==keyId) {
            printf("Moi ban nhap ten cua mon an: ");
            getchar();
            fgets(head->food.name,100,stdin);
            head->food.name[strcspn(head->food.name,"\n")]='\0';
            printf("Moi ban nhap danh muc mon an: ");
            fgets(head->food.category,100,stdin);
            head->food.category[strcspn(head->food.category,"\n")]='\0';
            printf("Moi ban nhap gia mon an: ");
            scanf("%f",&head->food.price);
            printf("Da cap nhat thanh cong");
            return;
        }
        head=head->next;
    }
    printf("Khong thay mon an");
}
//Ham danh dau mon an
void markAsCompeleted(Node**sellingFood,DNode**completedSelling) {
    int keyId;
    printf("Moi ban nhap id mon an muon danh dau: ");
    scanf("%d",&keyId);
    Node*curr=*sellingFood,*prev=NULL;
    while(curr) {
        if(curr->food.id==keyId) {
            if(prev) {
                prev->next=curr->next;
            }else {
                *sellingFood=curr->next;
            }
            DNode* newNode=(DNode*)malloc(sizeof(DNode));
            if (!*completedSelling) {
                *completedSelling=newNode;
            }else {
             DNode*tail=*completedSelling;
             while(tail->next) {
                 tail=tail->next;
             }
                tail->next=newNode;
                newNode->next=NULL;
                newNode->prev=tail;
            }
            free(curr);
            printf("Da danh dau thanh cong");
            return;
        }
       printf("Khong tim thay mon an");
    }
}
void displayCompletedSelling(DNode*head) {
   if(!head) {
       printf("Danh sach hoan toan rong");
       return;
    }
    printf("Danh sach mon an da ngung ban la: ");
    while(head) {
        printFood(head->food);
        head=head->next;
    }
}

//Ham tim kiem mon an
void searchFoodByName(Node*head) {
    char keyWord[100];
    printf("Moi ban nhap ten mon an");
    getchar();
    fgets(keyWord,100,stdin);
    keyWord[strcspn(keyWord,"\n")]='\0';
    int found=0;
    while(head) {
        if (strstr(head->food.name,keyWord)) {
            printFood(head->food);
            found=1;
        }
        head=head->next;
    }
    if(!found) {
        printf("Khong thay mon an qua ten ban da nhap: ");
    }
}
void sortFoodByPrice(Node*head) {
    for (Node*i=head;i&&i->next;i=i->next) {
        for (Node*j=i->next;j;j=j->next) {
            if (i->food.price>j->food.price) {
                Node* temp=i->next;
                i->next=j->next;
                j->next=temp;
            }
        }
    }
    printf("Da sap xep thanh cong danh sach");
    printf("Vui long chon lai 2. de xem lai danh sach");
}
void freeStorage(Node*head1,DNode*head2) {
    while(head1) {
        Node*temp=head1;
        head1=head1->next;
        free(temp);
    }
    while(head2) {
        DNode*temp=head2;
        head2=head2->next;
        free(temp);
    }
}
int main(){
    Node*sellingList=NULL;
    DNode*completedSelling=NULL;
    int choice;
    do {
        printf("\n      MENU      \n");
        printf("1. Them moi mon an\n");
        printf("2. Hien thi danh sach mon an dang ban\n");
        printf("3. Cap nhat mon an\n");
        printf("4. Danh dau mon an da ngung ban\n");
        printf("5. Hien thi danh sach mon an da ngung kinh doanh\n");
        printf("6. Tim kiem mon an theo ten\n");
        printf("7. Sap xep theo gia\n");
        printf("8. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addFood(&sellingList);
                break;
            case 2:
                displayFood(sellingList);
                break;
            case 3:
                updateFood(sellingList);
                break;
            case 4:
               markAsCompeleted(&sellingList, &completedSelling);
                break;
            case 5:
                displayCompletedSelling(completedSelling);
                break;
            case 6:
                searchFoodByName(sellingList);
                break;
            case 7:
                sortFoodByPrice(sellingList);
                break;
            case 8:
                freeStorage(sellingList,completedSelling);
                printf("Thoat chuong trinh thanh cong");
                break;
                default:
                printf("Gia tri ban nhap khong hop le.Vui lui nhap lai\n");
        }
    }while(choice!=8);
    return 0;
}