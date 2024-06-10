#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 5
#define MOBILE_MONEY 1
#define VISA_CARD 2

typedef struct {
    char name[50];
    float price;
} MenuItem;

typedef struct {
    int item_id;
    int quantity;
} OrderItem;

float calculate_total(OrderItem order[], int count, MenuItem menu[]) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += order[i].quantity * menu[order[i].item_id].price;
    }
    return total;
}

void display_menu(MenuItem menu[], int count) {
    printf("Welcome to Global Foods Restaurant!\n");
    printf("Menu:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, menu[i].name, menu[i].price);
    }
}

void save_order_receipt(OrderItem order[], int order_count, MenuItem menu[], float total_amount) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char filename[50];
    sprintf(filename, "receipt_%d%d%d_%d%d%d.txt", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "Receipt Date: %d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        fprintf(fp, "Items ordered:\n");
        for (int i = 0; i < order_count; i++) {
            fprintf(fp, "%s - %d\n", menu[order[i].item_id].name, order[i].quantity);
        }
        fprintf(fp, "Total Amount: $%.2f\n", total_amount);
        fclose(fp);
    } else {
        printf("Failed to save the receipt.\n");
    }
}

int main() {
    MenuItem menu[MAX_ITEMS] = {
        {"Burger", 5.99},
        {"Pizza", 8.99},
        {"Salad", 4.99},
        {"Fries", 2.49},
        {"Drink", 1.99}
    };

    while(1) {
        OrderItem order[MAX_ITEMS];
        int order_count = 0;

        int choice;
        do {
            display_menu(menu, MAX_ITEMS);
            printf("Enter item number to order (0 to finish): ");
            scanf("%d", &choice);
            if (choice >= 1 && choice <= MAX_ITEMS) {
                int quantity;
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                order[order_count].item_id = choice - 1;
                order[order_count].quantity = quantity;
                order_count++;
            }
        } while (choice != 0 && order_count < MAX_ITEMS);

        float total_amount = calculate_total(order, order_count, menu);
        printf("Your total amount is: $%.2f\n", total_amount);

        int payment_option;
        printf("Choose payment option:\n");
        printf("1. Mobile Money\n");
        printf("2. Visa Card\n");
        scanf("%d", &payment_option);

        char payment_info[20];
        if (payment_option == MOBILE_MONEY) {
            printf("Enter mobile money number: ");
            scanf("%s", payment_info);
        } else if (payment_option == VISA_CARD) {
            printf("Enter visa card number: ");
            scanf("%s", payment_info);
        }

        save_order_receipt(order, order_count, menu, total_amount);

        int cont;
        printf("Do you want to make another order? (1 for Yes / 0 for No): ");
        scanf("%d", &cont);
        if (cont != 1)
            break;
    }

    printf("Thank you for choosing Global Foods Restaurant. Have a great day!\n");

    return 0;
}
