#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENU 10

// Structure for menu item
typedef struct {
    int id;
    char name[30];
    float price;
} MenuItem;

// Structure for doubly linked list (orders)
typedef struct OrderNode {
    MenuItem item;
    int quantity;
    struct OrderNode* prev;
    struct OrderNode* next;
} OrderNode;

// Function declarations
void displayMenu(MenuItem menu[], int size);
int binarySearch(MenuItem menu[], int size, int id);
void addOrder(OrderNode** head, MenuItem item, int quantity);
void displayBill(OrderNode* head);

int main() {
    MenuItem menu[MAX_MENU] = {
        {1, "Burger", 120.00},
        {2, "Coke", 40.00},
        {3, "Fries", 60.00},
        {4, "Pasta", 150.00},
        {5, "Pizza", 250.00}
    };
    int menuSize = 5;

    OrderNode* orderList = NULL;
    int choice, quantity;

    printf("=== Welcome to DSA Restaurant ===\n");

    while (1) {
        displayMenu(menu, menuSize);
        printf("Enter Item ID to order (0 to finish): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Exiting.\n");
            break;
        }

        if (choice == 0) break;

        int index = binarySearch(menu, menuSize, choice);
        if (index == -1) {
            printf("Item not found. Try again.\n");
            continue;
        }

        printf("Enter quantity: ");
        if (scanf("%d", &quantity) != 1 || quantity <= 0) {
            printf("Invalid quantity! Try again.\n");
            continue;
        }

        addOrder(&orderList, menu[index], quantity);
    }

    printf("\n==== Final Bill ====\n");
    displayBill(orderList);
    printf("🙏 Thank you! Visit again.\n");

    return 0;
}

// Show the menu
void displayMenu(MenuItem menu[], int size) {
    printf("\nMenu:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %-10s - ₹%.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

// Binary search (requires sorted menu)
int binarySearch(MenuItem menu[], int size, int id) {
    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (menu[mid].id == id) return mid;
        else if (menu[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// Add new order to the doubly linked list
void addOrder(OrderNode** head, MenuItem item, int quantity) {
    OrderNode* newNode = (OrderNode*)malloc(sizeof(OrderNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->item = item;
    newNode->quantity = quantity;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        OrderNode* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Print final bill
void displayBill(OrderNode* head) {
    float total = 0.0;
    OrderNode* temp = head;

    while (temp != NULL) {
        float cost = temp->item.price * temp->quantity;
        printf("%-10s x%d\t₹%.2f\n", temp->item.name, temp->quantity, cost);
        total += cost;
        temp = temp->next;
    }

    printf("----------------------------\n");
    printf("Total:\t\t₹%.2f\n", total);
}
