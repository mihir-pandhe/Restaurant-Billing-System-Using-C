#include <stdio.h>

void displayMenu()
{
    printf("Restaurant Menu\n");
    printf("1. Pizza - $10\n");
    printf("2. Burger - $7\n");
    printf("3. Pasta - $8\n");
}

int main()
{
    int choice;
    int quantity;
    float total = 0.0;

    displayMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    switch (choice)
    {
    case 1:
        total = 10 * quantity;
        break;
    case 2:
        total = 7 * quantity;
        break;
    case 3:
        total = 8 * quantity;
        break;
    default:
        printf("Invalid choice.\n");
        return 1;
    }

    printf("Total Bill: $%.2f\n", total);
    return 0;
}
