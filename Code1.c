/*
Drew franke
3131934
Lab session: Wednesday 1:00pm
Lab Assignment: 05-1
Description: Given 12 monthly sales figures in an input file, the program generates 
the following reports:
1. Monthly Sales Report: Display the month and sales in two columns.
2. Sales Summary Report: Show the minimum, maximum, and average monthly sales.
3. Six-Month Moving Average Report.
4. Sales Report (Highest to Lowest): Display the sales from highest to lowes
*/
#include <stdio.h>
#include <stdlib.h>

// define months for easy reference
const char *months[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

// function prototypes
void monthly_sales_report(double sales[]);
void sales_summary_report(double sales[]);
void six_month_moving_avg_report(double sales[]);
void sales_highest_to_lowest_report(double sales[]);

int main() {
    // array to hold 12 monthly sales
    double sales[12];
    FILE *file = fopen("sales.txt", "r");

    // check if file opened successfully
    if (file == NULL) {
        printf("Error: Could not open file 'sales.txt'.\n");
        return 1;
    }

    // read the sales data from the file
    for (int i = 0; i < 12; i++) {
        if (fscanf(file, "%lf", &sales[i]) != 1) {
            printf("Error: Invalid data in 'sales.txt'.\n");
            fclose(file);
            return 1;
        }
    }

    // close the file after reading
    fclose(file);

    // generate the reports
    monthly_sales_report(sales);
    sales_summary_report(sales);
    six_month_moving_avg_report(sales);
    sales_highest_to_lowest_report(sales);

    return 0;
}

// monthly sales report
void monthly_sales_report(double sales[]) {
    printf("Monthly Sales Report for 2024\n");
    printf("%-12s %s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {
        printf("%-12s $%.2f\n", months[i], sales[i]);
    }
    printf("\n");
}

// sales summary report
void sales_summary_report(double sales[]) {
    double min_sales = sales[0], max_sales = sales[0], total_sales = 0;
    int min_month = 0, max_month = 0;

    for (int i = 0; i < 12; i++) {
        total_sales += sales[i];
        if (sales[i] < min_sales) {
            min_sales = sales[i];
            min_month = i;
        }
        if (sales[i] > max_sales) {
            max_sales = sales[i];
            max_month = i;
        }
    }

    double avg_sales = total_sales / 12.0;

    printf("Sales Summary Report:\n");
    printf("Minimum sales: $%.2f (%s)\n", min_sales, months[min_month]);
    printf("Maximum sales: $%.2f (%s)\n", max_sales, months[max_month]);
    printf("Average sales: $%.2f\n\n", avg_sales);
}

// six-month moving average report
void six_month_moving_avg_report(double sales[]) {
    printf("Six-Month Moving Average Report:\n");
    for (int i = 0; i <= 6; i++) {
        double sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        double avg = sum / 6.0;
        printf("%s-%s: $%.2f\n", months[i], months[i + 5], avg);
    }
    printf("\n");
}

// sales report (high-low)
void sales_highest_to_lowest_report(double sales[]) {
    // temporary array for sorting
    double sorted_sales[12];
    int sorted_indices[12];

    // initialize sorted arrays
    for (int i = 0; i < 12; i++) {
        sorted_sales[i] = sales[i];
        sorted_indices[i] = i;
    }

    // sort sales (descending) using a simple selection sort
    for (int i = 0; i < 12 - 1; i++) {
        for (int j = i + 1; j < 12; j++) {
            if (sorted_sales[i] < sorted_sales[j]) {
                // swap sales values
                double temp_sale = sorted_sales[i];
                sorted_sales[i] = sorted_sales[j];
                sorted_sales[j] = temp_sale;

                // swap indices to keep track of months
                int temp_index = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp_index;
            }
        }
    }

    // print sorted sales
    printf("Sales Report (Highest to Lowest):\n");
    printf("%-12s %s\n", "Month", "Sales");
    for (int i = 0; i < 12; i++) {
        int month_index = sorted_indices[i];
        printf("%-12s $%.2f\n", months[month_index], sorted_sales[i]);
    }
}