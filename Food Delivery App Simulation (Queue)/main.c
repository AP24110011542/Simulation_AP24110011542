#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// Order structure
struct Order {
    int orderId;
    char customerName[50];
    char foodItem[50];
};

// Queue structure
struct Queue {
    int front;
    int rear;
    int count;
    struct Order orders[MAX];
};

void initQueue(struct Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

int isFull(struct Queue *q) {
    return q->count == MAX;
}

int isEmpty(struct Queue *q) {
    return q->count == 0;
}

// 1. Place Order
void placeOrder(struct Queue *q, int *nextId) {
    if (isFull(q)) {
        printf("\nQueue is FULL! Cannot place more orders.\n");
        return;
    }

    struct Order newOrder;
    newOrder.orderId = (*nextId)++;

    printf("\nEnter customer name: ");
    scanf(" %[^\n]", newOrder.customerName);

    printf("Enter food item: ");
    scanf(" %[^\n]", newOrder.foodItem);

    q->rear = (q->rear + 1) % MAX;
    q->orders[q->rear] = newOrder;
    q->count++;

    printf("\nOrder Placed Successfully! Order ID = %d\n", newOrder.orderId);
}

// 2. Deliver Order
void processOrder(struct Queue *q, int *servedCount) {
    if (isEmpty(q)) {
        printf("\nNo orders to deliver.\n");
        return;
    }

    struct Order o = q->orders[q->front];

    printf("\nOrder Delivered:\n");
    printf("Order ID   : %d\n", o.orderId);
    printf("Customer   : %s\n", o.customerName);
    printf("Food Item  : %s\n", o.foodItem);

    q->front = (q->front + 1) % MAX;
    q->count--;
    (*servedCount)++;
}

// 3. View All Orders
void viewOrders(struct Queue *q) {
    if (isEmpty(q)) {
        printf("\nNo pending orders.\n");
        return;
    }

    printf("\n--- Pending Orders (%d) ---\n", q->count);

    int i, index;
    for (i = 0, index = q->front; i < q->count; i++) {
        struct Order o = q->orders[index];
        printf("ID: %d | Customer: %s | Food: %s\n",
               o.orderId, o.customerName, o.foodItem);
        index = (index + 1) % MAX;
    }
}

// 4. Search Order by ID
void searchOrder(struct Queue *q) {
    int id;
    printf("\nEnter Order ID to search: ");
    scanf("%d", &id);

    int i, index;
    for (i = 0, index = q->front; i < q->count; i++) {
        if (q->orders[index].orderId == id) {
            printf("\nOrder Found!\n");
            printf("Customer: %s | Food: %s\n",
                   q->orders[index].customerName,
                   q->orders[index].foodItem);
            return;
        }
        index = (index + 1) % MAX;
    }

    printf("\nOrder NOT found.\n");
}

// 5. Cancel Order by ID
void cancelOrder(struct Queue *q) {
    if (isEmpty(q)) {
        printf("\nNo orders to cancel.\n");
        return;
    }

    int id, i, index;
    printf("\nEnter Order ID to cancel: ");
    scanf("%d", &id);

    int pos = -1;

    // Find position
    for (i = 0, index = q->front; i < q->count; i++) {
        if (q->orders[index].orderId == id) {
            pos = index;
            break;
        }
        index = (index + 1) % MAX;
    }

    if (pos == -1) {
        printf("\nOrder NOT found.\n");
        return;
    }

    // Shift left to fill gap
    int next;
    for (next = (pos + 1) % MAX; next != (q->rear + 1) % MAX; next = (next + 1) % MAX) {
        q->orders[pos] = q->orders[next];
        pos = next;
    }

    q->rear = (q->rear - 1 + MAX) % MAX;
    q->count--;

    printf("\nOrder Cancelled Successfully!\n");
}

int main() {
    struct Queue q;
    int choice;
    int nextOrderId = 1;
    int servedCount = 0;

    initQueue(&q);

    while (1) {
        printf("\n====== Food Delivery App (Queue Simulation) ======\n");
        printf("1. Place Order\n");
        printf("2. Deliver Order\n");
        printf("3. View Orders\n");
        printf("4. Search Order\n");
        printf("5. Cancel Order\n");
        printf("6. Total Orders Delivered\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: placeOrder(&q, &nextOrderId); break;
            case 2: processOrder(&q, &servedCount); break;
            case 3: viewOrders(&q); break;
            case 4: searchOrder(&q); break;
            case 5: cancelOrder(&q); break;
            case 6: 
                printf("\nTotal Orders Delivered: %d\n", servedCount);
                break;
            case 7: exit(0);
            default: printf("\nInvalid choice.\n");
        }
    }

    return 0;
}
