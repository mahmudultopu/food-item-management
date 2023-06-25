#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define clear() printf("\033[H\033[J")

void displaySplashScreen();
void adminmenu();
int validateLogin(char admin[], char pass[]);
void customermenu();
struct node* createadmin(struct node* head, int data, char foodname[50], float price);
struct node* createcustomer(struct node* head, int data, int quantity);
struct node* delete(int data, struct node* head);
int deleteadmin(struct node** head);
int deletecustomer(struct node** head);
void displayList(struct node* head);
void displaycustomerlist(struct node* head);
float totalsales(struct node* head);
void deleteList(struct node** head);

struct node {
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node* next;
};

void displaySplashScreen() {
    clear();
   printf("\n");
    printf("===========================================\n");
    printf("         WELCOME TO THE FOOD ITEM          \n");
    printf("       MANAGEMENT SYSTEM (SYSTEM NAME)     \n");
    printf("===========================================\n");
    printf("\n");
    printf("Loading...\n");

}

int validateLogin(char admin[], char pass[]) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Username: ");
    scanf("%19s", username);

    printf("Password: ");
    scanf("%19s", password);

    if (strcmp(username, admin) == 0 && strcmp(password, password) == 0)
        return 1;
    else
        return 0;
}

void adminmenu() {
    int choice;
    struct node* heada = NULL;

    do {
        clear();
        printf("=== ADMIN MENU ===\n\n");
        printf("1. Add Food Item\n");
        printf("2. Delete Food Item\n");
        printf("3. Display Food List\n");
        printf("4. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int data;
                char foodname[50];
                float price;

                printf("Enter Food ID: ");
                scanf("%d", &data);

                printf("Enter Food Name: ");
                scanf("%49s", foodname);

                printf("Enter Food Price: ");
                scanf("%f", &price);

                heada = createadmin(heada, data, foodname, price);
                break;
            }
            case 2: {
                int data;

                printf("Enter Food ID to Delete: ");
                scanf("%d", &data);

                heada = delete(data, heada);
                break;
            }
            case 3: {
                displayList(heada);
                break;
            }
            case 4: {
                deleteList(&heada);
                clear();
                printf("Exiting admin menu...\n");
                sleep(2);
                break;
            }
            default: {
                clear();
                printf("Invalid choice! Please try again.\n");
                sleep(2);
                break;
            }
        }
    } while (choice != 4);
}

void customermenu() {
    int choice;
    struct node* headc = NULL;

    do {
        clear();
        printf("=== CUSTOMER MENU ===\n\n");
        printf("1. Order Food\n");
        printf("2. Delete Order\n");
        printf("3. Display Order List\n");
        printf("4. Total Sales\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int data;
                int quantity;

                printf("Enter Food ID: ");
                scanf("%d", &data);

                printf("Enter Quantity: ");
                scanf("%d", &quantity);

                headc = createcustomer(headc, data, quantity);
                break;
            }
            case 2: {
                int data;

                printf("Enter Food ID to Delete: ");
                scanf("%d", &data);

                headc = delete(data, headc);
                break;
            }
            case 3: {
                displaycustomerlist(headc);
                break;
            }
            case 4: {
                float total = totalsales(headc);
                printf("Total Sales: $%.2f\n", total);
                sleep(2);
                break;
            }
            case 5: {
                deleteList(&headc);
                clear();
                printf("Exiting customer menu...\n");
                sleep(2);
                break;
            }
            default: {
                clear();
                printf("Invalid choice! Please try again.\n");
                sleep(2);
                break;
            }
        }
    } while (choice != 5);
}

struct node* createadmin(struct node* head, int data, char foodname[50], float price) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = data;
    strcpy(newNode->foodname, foodname);
    newNode->price = price;
    newNode->quantity = 1;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return head;
}

struct node* createcustomer(struct node* head, int data, int quantity) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = data;
    newNode->quantity = quantity;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return head;
}

struct node* delete(int data, struct node* head) {
    struct node* temp = head;
    struct node* prev = NULL;

    if (temp != NULL && temp->data == data) {
        head = temp->next;
        free(temp);
        return head;
    }

    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Food ID not found!\n");
        sleep(2);
        return head;
    }

    prev->next = temp->next;
    free(temp);

    return head;
}

int deleteadmin(struct node** head) {
    struct node* temp = *head;
    struct node* next;

    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;

    return 1;
}

int deletecustomer(struct node** head) {
    struct node* temp = *head;
    struct node* next;

    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;

    return 1;
}

void displayList(struct node* head) {
    clear();
    printf("=== FOOD LIST ===\n\n");

    if (head == NULL) {
        printf("No food items available.\n");
    } else {
        struct node* temp = head;
        while (temp != NULL) {
            printf("Food ID: %d\n", temp->data);
            printf("Food Name: %s\n", temp->foodname);
            printf("Price: $%.2f\n", temp->price);
            printf("\n");
            temp = temp->next;
        }
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();
}

void displaycustomerlist(struct node* head) {
    clear();
    printf("=== ORDER LIST ===\n\n");

    if (head == NULL) {
        printf("No orders available.\n");
    } else {
        struct node* temp = head;
        while (temp != NULL) {
            printf("Food ID: %d\n", temp->data);
            printf("Quantity: %d\n", temp->quantity);
            printf("\n");
            temp = temp->next;
        }
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();
}

float totalsales(struct node* head) {
    float total = 0.0;

    struct node* temp = head;
    while (temp != NULL) {
        total += temp->price * temp->quantity;
        temp = temp->next;
    }

    return total;
}

void deleteList(struct node** head) {
    struct node* current = *head;
    struct node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

int main(void) {
    displaySplashScreen();

    if (validateLogin("admin", "password")) {
        clear();
        printf("Login Successful!\n");
        sleep(2);
        adminmenu();
    } else {
        clear();
        printf("Invalid username or password!\n");
        sleep(2);
        return 0;
    }

    return 0;
}
