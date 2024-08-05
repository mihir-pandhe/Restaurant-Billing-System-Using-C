#include <stdio.h>

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

int main()
{
    int choice;
    int quantity;
    float subtotal = 0.0;
    float total = 0.0;

    displayMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    switch (choice)
    {
    case 1:
        subtotal = 5 * quantity;
        printf("Item: Salad, Quantity: %d, Subtotal: $%.2f\n", quantity, subtotal);
        break;
    case 2:
        subtotal = 10 * quantity;
        printf("Item: Pizza, Quantity: %d, Subtotal: $%.2f\n", quantity, subtotal);
        break;
    case 3:
        subtotal = 7 * quantity;
        printf("Item: Burger, Quantity: %d, Subtotal: $%.2f\n", quantity, subtotal);
        break;
    case 4:
        subtotal = 4 * quantity;
        printf("Item: Ice Cream, Quantity: %d, Subtotal: $%.2f\n", quantity, subtotal);
        break;
    default:
        printf("Invalid choice.\n");
        return 1;
    }

    total = subtotal;
    printf("Total Bill: $%.2f\n", total);
    return 0;
}
