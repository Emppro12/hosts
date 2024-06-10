#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLACES 5
#define MOBILE_MONEY 1
#define VISA_CARD 2

typedef struct {
    char name[50];
    float price;
} TravelPackage;

typedef struct {
    char name[50];
    char site[100];
} TravelPlace;

typedef struct {
    char customer_name[50];
    char payment_method[20];
    char payment_info[20];
    float total_amount;
    time_t booking_time;
} Booking;

typedef struct {
    TravelPackage packages[MAX_PLACES];
    TravelPlace places[MAX_PLACES];
    int package_count;
    int place_count;
} TourismCompany;

void initialize_company(TourismCompany *company) {
    company->package_count = 0;
    company->place_count = 0;
}

void add_package(TourismCompany *company, char name[], float price) {
    if (company->package_count < MAX_PLACES) {
        strcpy(company->packages[company->package_count].name, name);
        company->packages[company->package_count].price = price;
        company->package_count++;
    } else {
        printf("Max packages reached.\n");
    }
}

void add_place(TourismCompany *company, char name[], char site[]) {
    if (company->place_count < MAX_PLACES) {
        strcpy(company->places[company->place_count].name, name);
        strcpy(company->places[company->place_count].site, site);
        company->place_count++;
    } else {
        printf("Max places reached.\n");
    }
}

void display_packages(TourismCompany company) {
    printf("Travel Packages offered by Powers Travels:\n");
    for (int i = 0; i < company.package_count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, company.packages[i].name, company.packages[i].price);
    }
}

void display_places(TourismCompany company) {
    printf("Travel Places:\n");
    for (int i = 0; i < company.place_count; i++) {
        printf("%d. %s - %s\n", i + 1, company.places[i].name, company.places[i].site);
    }
}

float calculate_total(TravelPackage package[], int count, int selections[]) {
    float total = 0;
    for (int i = 0; i < count; i++) {
        total += package[selections[i]].price;
    }
    return total;
}

void save_booking_info(Booking booking) {
    time_t t = booking.booking_time;
    struct tm *tm = localtime(&t);
    char filename[50];
    sprintf(filename, "booking_%d%d%d_%d%d%d.txt", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        fprintf(fp, "Booking Time: %d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        fprintf(fp, "Customer Name: %s\n", booking.customer_name);
        fprintf(fp, "Total Amount: $%.2f\n", booking.total_amount);
        fprintf(fp, "Payment Method: %s\n", booking.payment_method);
        fprintf(fp, "Payment Info: %s\n", booking.payment_info);
        fclose(fp);
    } else {
        printf("Failed to save booking information.\n");
    }
}

int main() {
    TourismCompany company;
    initialize_company(&company);

    add_package(&company, "Beach Trip", 200.0);
    add_package(&company, "Mountain Hiking", 300.0);
    add_place(&company, "Beach Resort", "www.beachresort.com");
    add_place(&company, "Mountain Peak", "www.mountainpeak.com");

    Booking booking;
    int selections[MAX_PLACES];
    int selection_count = 0;
    float total_amount;

    printf("Welcome to Powers Travels!\n");
    display_packages(company);
    printf("Select packages by entering their numbers (0 to finish): ");
    int choice;
    while (1) {
        scanf("%d", &choice);
        if (choice >= 1 && choice <= company.package_count) {
            selections[selection_count++] = choice - 1;
        } else if (choice == 0) {
            break;
        } else {
            printf("Invalid choice. Please enter a valid package number.\n");
        }
    }

    total_amount = calculate_total(company.packages, selection_count, selections);
    printf("Total Amount: $%.2f\n", total_amount);

    int payment_option;
    printf("Choose payment option:\n");
    printf("1. Mobile Money\n");
    printf("2. Visa Card\n");
    scanf("%d", &payment_option);

    if (payment_option == MOBILE_MONEY) {
        strcpy(booking.payment_method, "Mobile Money");
        printf("Enter mobile money number: ");
        scanf("%s", booking.payment_info);
    } else if (payment_option == VISA_CARD) {
        strcpy(booking.payment_method, "Visa Card");
        printf("Enter visa card number: ");
        scanf("%s", booking.payment_info);
    }

    printf("Enter customer name: ");
    scanf("%s", booking.customer_name);

    booking.total_amount = total_amount;
    booking.booking_time = time(NULL);

    save_booking_info(booking);
    printf("Booking successful! Booking details saved.\n");

    return 0;
}
