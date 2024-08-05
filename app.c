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
    float total = 0.0;
    float subtotal = 0.0;

    displayMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

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
        return 1;
    }

    total = subtotal;
    printf("Subtotal: $%.2f\n", subtotal);
    printf("Total Bill: $%.2f\n", total);
    return 0;
}
