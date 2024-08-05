#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAX_RATE 0.10
#define DISCOUNT_RATE 0.05
#define MAX_USERS 10
#define MAX_ORDERS 100
#define MAX_MENU_ITEMS 50
#define MENU_FILE "menu.txt"

typedef struct
{
    char username[50];
    char password[50];
    int orderCount;
    float orderHistory[MAX_ORDERS];
} User;

typedef struct
{
    char name[50];
    float price;
} MenuItem;

User users[MAX_USERS] = {
    {"admin", "admin", 0, {0}}};

MenuItem menu[MAX_MENU_ITEMS];
int menuItemCount = 0;
int userCount = 1;
User *loggedInUser = NULL;

void displayMenu()
{
    printf("Restaurant Menu\n");
    for (int i = 0; i < menuItemCount; i++)
    {
        printf("%d. %s - $%.2f\n", i + 1, menu[i].name, menu[i].price);
    }
}

float calculateSubtotal(int choice, int quantity)
{
    if (choice < 1 || choice > menuItemCount)
    {
        printf("Invalid choice.\n");
        return -1;
    }
    return menu[choice - 1].price * quantity;
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

void saveMenuToFile()
{
    FILE *file = fopen(MENU_FILE, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }
    fprintf(file, "%d\n", menuItemCount);
    for (int i = 0; i < menuItemCount; i++)
    {
        fprintf(file, "%s %f\n", menu[i].name, menu[i].price);
    }
    fclose(file);
}

void loadMenuFromFile()
{
    FILE *file = fopen(MENU_FILE, "r");
    if (file == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }
    fscanf(file, "%d", &menuItemCount);
    for (int i = 0; i < menuItemCount; i++)
    {
        fscanf(file, "%s %f", menu[i].name, &menu[i].price);
    }
    fclose(file);
}

void addMenuItem()
{
    if (menuItemCount >= MAX_MENU_ITEMS)
    {
        printf("Menu item limit reached.\n");
        return;
    }
    printf("Enter name of the new item: ");
    scanf("%s", menu[menuItemCount].name);
    printf("Enter price of the new item: ");
    scanf("%f", &menu[menuItemCount].price);
    menuItemCount++;
    saveMenuToFile();
}

void updateMenuItem()
{
    int choice;
    displayMenu();
    printf("Enter the number of the item to update: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > menuItemCount)
    {
        printf("Invalid choice.\n");
        return;
    }
    printf("Enter new name of the item: ");
    scanf("%s", menu[choice - 1].name);
    printf("Enter new price of the item: ");
    scanf("%f", &menu[choice - 1].price);
    saveMenuToFile();
}

void deleteMenuItem()
{
    int choice;
    displayMenu();
    printf("Enter the number of the item to delete: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > menuItemCount)
    {
        printf("Invalid choice.\n");
        return;
    }
    for (int i = choice - 1; i < menuItemCount - 1; i++)
    {
        menu[i] = menu[i + 1];
    }
    menuItemCount--;
    saveMenuToFile();
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
    char addMore;

    loadMenuFromFile();

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

    do
    {
        printf("1. Place an Order\n");
        printf("2. Add Menu Item\n");
        printf("3. Update Menu Item\n");
        printf("4. Delete Menu Item\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice)
        {
        case 1:
            do
            {
                displayMenu();
                printf("Enter your choice: ");
                scanf("%d", &choice);
                printf("Enter quantity: ");
                scanf("%d", &quantity);

                float itemSubtotal = calculateSubtotal(choice, quantity);
                if (itemSubtotal == -1)
                {
                    return 1;
                }

                subtotal += itemSubtotal;

                printf("Do you want to add more items to your order? (y/n): ");
                scanf(" %c", &addMore);
            } while (addMore == 'y' || addMore == 'Y');

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
            break;
        case 2:
            addMenuItem();
            break;
        case 3:
            updateMenuItem();
            break;
        case 4:
            deleteMenuItem();
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }

        printf("Do you want to perform another action? (1 for Yes, 0 for No): ");
        scanf("%d", &userChoice);
    } while (userChoice == 1);

    return 0;
}
