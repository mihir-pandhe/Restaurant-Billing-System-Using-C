#include <stdio.h>

#define TAX_RATE 0.10
#define DISCOUNT_RATE 0.05

void displayMenu()
{
    printf("Restaurant Menu\n");
    printf("Starters:\n");
    printf("1. Salad - $5\n");
    printf("Main Course:\n");
    printf("2. Pizza - $10\n");
    printf("3. Burger - $7\n");
    printf("Desserts:\n");
    printf("4. Ice Cream - $4\n");
}

float calculateSubtotal(int choice, int quantity)
{
    float subtotal = 0.0;
    switch (choice)
    {
    case 1:
        subtotal = 5 * quantity;
        break;
    case 2:
        subtotal = 10 * quantity;
        break;
    case 3:
        subtotal = 7 * quantity;
        break;
    case 4:
        subtotal = 4 * quantity;
        break;
    default:
        printf("Invalid choice.\n");
        return -1;
    }
    return subtotal;
}

float applyDiscount(float amount)
{
    return amount * (1 - DISCOUNT_RATE);
}

float calculateTax(float amount)
{
    return amount * TAX_RATE;
}

int main()
{
    int choice;
    int quantity;
    float subtotal = 0.0;
    float discount = 0.0;
    float tax = 0.0;
    float total = 0.0;

    displayMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    subtotal = calculateSubtotal(choice, quantity);
    if (subtotal == -1)
    {
        return 1;
    }

    printf("Subtotal: $%.2f\n", subtotal);

    discount = applyDiscount(subtotal);
    printf("Subtotal after discount: $%.2f\n", discount);

    tax = calculateTax(discount);
    printf("Tax: $%.2f\n", tax);

    total = discount + tax;
    printf("Total Bill: $%.2f\n", total);

    return 0;
}
