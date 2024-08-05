#include <stdio.h>
#include <string.h>

#define TAX_RATE 0.10
#define DISCOUNT_RATE 0.05
#define MAX_USERS 10
#define MAX_ORDERS 100

typedef struct
{
    char username[50];
    char password[50];
    int orderCount;
    float orderHistory[MAX_ORDERS];
} User;

User users[MAX_USERS] = {
    {"admin", "admin", 0, {0}}};

int userCount = 1;
User *loggedInUser = NULL;

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

int authenticateUser()
{
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
        {
            loggedInUser = &users[i];
            return 1;
        }
    }
    printf("Invalid credentials.\n");
    return 0;
}

void registerUser()
{
    if (userCount >= MAX_USERS)
    {
        printf("User limit reached.\n");
        return;
    }
    char username[50];
    char password[50];
    printf("Enter new username: ");
    scanf("%s", username);
    printf("Enter new password: ");
    scanf("%s", password);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    users[userCount].orderCount = 0;
    userCount++;
    printf("User registered successfully.\n");
}

void displayOrderHistory()
{
    if (loggedInUser == NULL)
    {
        printf("No user logged in.\n");
        return;
    }
    printf("Order History for %s:\n", loggedInUser->username);
    for (int i = 0; i < loggedInUser->orderCount; i++)
    {
        printf("Order %d: $%.2f\n", i + 1, loggedInUser->orderHistory[i]);
    }
}

int main()
{
    int choice;
    int quantity;
    float subtotal = 0.0;
    float discount = 0.0;
    float tax = 0.0;
    float total = 0.0;
    int userChoice;

    printf("1. Login\n");
    printf("2. Register\n");
    printf("Enter choice: ");
    scanf("%d", &userChoice);

    if (userChoice == 1)
    {
        if (!authenticateUser())
        {
            return 1;
        }
    }
    else if (userChoice == 2)
    {
        registerUser();
        if (!authenticateUser())
        {
            return 1;
        }
    }
    else
    {
        printf("Invalid choice.\n");
        return 1;
    }

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

    if (loggedInUser != NULL && loggedInUser->orderCount < MAX_ORDERS)
    {
        loggedInUser->orderHistory[loggedInUser->orderCount] = total;
        loggedInUser->orderCount++;
    }

    printf("Do you want to view your order history? (1 for Yes, 0 for No): ");
    scanf("%d", &userChoice);
    if (userChoice == 1)
    {
        displayOrderHistory();
    }

    return 0;
}
