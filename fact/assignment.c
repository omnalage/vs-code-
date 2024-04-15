#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define structures for food items, special items, and orders
struct FoodItem
{
    char name[50];
    float price;
    int quantity;
    int serviceTime;
};

struct SpecialItem
{
    char name[50];
    float price;
};

struct Order
{
    char userName[50];
    char userPhoneNumber[15];
    char userAddress[100];
    char foodItem[50];
    int quantity;
    int orderTime;
    int deliveryTime;
};

struct Restaurant
{
    char name[50];
    char address[100];
    struct FoodItem foodItems[50];
    struct SpecialItem specialItems[10];
    struct FoodItem itemOfDay;
    int numFoodItems;
    int numSpecialItems;
};
struct Restaurant restaurants[10] = {
    {"Veggietude",
     "Ring Road Trimurti Nagar",
     {{"Chilli Paneer", 190.0, 10, 15},
      {"Chilli Machorian", 170.0, 10, 15},
      {"Paneer Tikka Masala", 160.0, 10, 15},
      {"Biryani", 180.0, 10, 15},
      {"Dum Aloo", 150.0, 10, 15}},
     {{"Chicken Handi", 600.0},
      {"Paneer Angari", 300.0},
     },
     {"Paneer Tikka Biryani", 400.0, 10, 30},
     6,
     2},
    {"Shree Ganesh Sagar",
     "Main Road Dhantoli",
     {{"Butter Kulcha", 150.0, 10, 15},
      {"Keema Kastori", 180.0, 10, 15},
      {"Mutton Biryani", 250.0, 10, 15},
      {"Tandori Aloo", 200.0, 10, 15},
      {"Kadhai Paneer", 200.0, 10, 15}},
     {{"Hyderabadi Biryani", 300.0},
      {"Veg Makhanwala", 280.0},
     },
     {"Mutton Do Pyaza", 350.0, 10, 30},
     6,
     2
     },
     {"Ashvaryum Restaurant",
      "Beltarodi Road Besa road",
        {{"Laccha Paneer",280.0,10,15},
        {"Egg Curry",180.0,10,15}, 
        {"Veg Kofta",270.0,10,15}, 
        {"Chicken Curry",330.0,10,15}, 
        {"Laccha Chicken",350.0,10,15}},
        { {"Punjabi Chicken ",350.0}, 
        {"Veg Cheesy Kofta",290.0},
        },
        {"Punjabi Mutton",400.0,10,30},
        6,
        2
     },
     { "Euphoria Restaurant ",
        "Nandanvan Road Nandanvan Colony",
        {{"Thai Noodles",200.0,10,15}, 
        {"Paneer Hakka Noodles",150.0,10,15},
        {"Paneer Saoji",210.0,10,20},
        {"Bhindi Kurkura",230.0,10,15},
        {"Sev Bhaji",190.0,10,15}},
        {{"Euphoria Special Sabzi",550.0},
        {"Punjabi Paneer Masala",500.0},
        },
        {"Euphoria Special Pizza",400.0,10,30},
        6,
        2
     },
     {
        "Durva Restaurant",
        "Stadium Road dhantoli",
        {{"Veg Kofta ",210.0,10,15},
        {"Palak Paneer",200.0,10,20},
        {"Kadhai Veg",230.0,10,15},
        {"Palak Corn",150.0,10,15},
        {"Handi Veg",250.0,10,15}},
     {{"Mexican Fried Rice",300.0},
     {"Paneer Taka Tak",350.0},
     },
     {"Special King Kofta",400.0,10,30},
     6,
     2
     },
     {
        "Anandam Restaurant",
        "Kachimet Amravati road",
        {{"Fish Finger",180.0,10,15},
        {"Mutton Kali Miri",250.0,10,15},
        {"Veg Ball Asian Style",300.0,10,20},
        {"Jain Bhindi Kurkuri",200.0,10,20}, 
        {"Double Dal Tadka",230.0,10,20}},
        { {"Baby Corn Mushroom Laziz",350.0},
        {"Bhindi Do Pyaz",300.0},
        },
        {"Penne Aglio Olio Sauce Pasta",600.0,10,30},
        6,
        2
     },
     {
       "Food links",
        "C A Road Central Avenue Road",
        {{"Palak Paneer",230.0,10,15},
        {"Paneer Masala",190.0,10,15},
        {"Dal Tadka",160.0,10,15},
        {"Rassa Patodi",200.0,10,15},
        {"Gobi Aloo Matar",180.0,10,15}},
        {{"Mushroom Cheese Pizza",300.0},
        {"Mysore Cheese Masala Dosa",250.0},
        },
        {"Fried Mini Chocolate Idli",400.0,10,30},
        6,
        2 
     },
     { "Aaradhya Restro",
        "Umred road Umrer",
        {{"Chana Masala",170.0,10,15},
        {"Methi Matar Malai",190,10,15},
        {"Navratna Korma",250.0,10,15},
        {"Kaju Curry",200.0,10,15},
        {"Tomato Chutney",150.0,10,15}},
        { {"Diwani Handi",300.0},
        {"Haryali Kofta",350.0},
        },
        { "Garden Glory",550.0,10,30},
        6,
        2
     },
     { "Ratnakar restaurants",
        "Gangabai Ghat Road Bagadganj",
        {{"Keema Kastori",230.0,10,15},
        {"Saoji Curry",200.0,10,15},
        {"Veg Kadhai",180.0,10,15},
        {"Veg Pataila",160,10,15},
        {"Sev Bhaji",150.0,10,15}},
        {{"Special Veg Kolhapuri",250.0},
        {"Veg Khus Khus",300.0},
        },
         { "Special Dal Kolhapuri",650.0,10,30},
         6,
         2
     },
     {"Babuji South Indian Restraurant",
        "College road chandan nagar",
        {{"Biryani",250.0,10,15},
        {"Junglee Paneer",300.0,10,15},
        {"Chilli Pepper Potato",230.0,10,15},
        {"Veg Crunchy",260.0,10,15},
        {"Gobi 69",240.0,10,15}},
       {{"Veg Garden",300},
       {"Dragon Pizza",450},},
       {"Paneer Mumtaz",656.0,10,15},
       6,
       2
     },
};

// Function to get the minimum delivery time for a given food item and quantity
void
getMinTime(struct Restaurant restaurants[], int numRestaurants, char foodItem[], int quantity)
{
    int minTime = -1;
    char minRestaurantName[50];
    char minRestaurantAddress[100];

    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        for (int j = 0; j < restaurant.numFoodItems; j++)
        {
            struct FoodItem item = restaurant.foodItems[j];
            if (strcmp(item.name, foodItem) == 0 && item.quantity >= quantity)
            {
                int totalTime = item.serviceTime * quantity;
                if (minTime == -1 || totalTime < minTime)
                {
                    minTime = totalTime;
                    strcpy(minRestaurantName, restaurant.name);
                    strcpy(minRestaurantAddress, restaurant.address);
                }
            }
        }
    }

    if (minTime != -1)
    {
        printf("Restaurant: %s\n", minRestaurantName);
        printf("Address: %s\n", minRestaurantAddress);
        printf("Delivery Time: %d minutes\n", minTime);
    }
    else
    {
        printf("Food item not available in any restaurant.\n");
    }
}

// Function to get the availability and prices of a food item in all restaurants
void getItemAvailability(struct Restaurant restaurants[], int numRestaurants, char foodItem[])
{
    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        for (int j = 0; j < restaurant.numFoodItems; j++)
        {
            struct FoodItem item = restaurant.foodItems[j];
            if (strcmp(item.name, foodItem) == 0)
            {
                printf("Restaurant: %s\n", restaurant.name);
                printf("Price for %d %s: $%.2f\n", item.quantity, item.name, item.price);
            }
        }
    }
}

// Function to place an order
int placeOrder(struct Restaurant restaurants[], int numRestaurants, char foodItem[], int quantity,
               char userName[], char userPhoneNumber[], char userAddress[])
{
    long orderTime = time(NULL); // Get the current time as the order time

    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        for (int j = 0; j < restaurant.numFoodItems; j++)
        {
            struct FoodItem item = restaurant.foodItems[j];
            if (strcmp(item.name, foodItem) == 0 && item.quantity >= quantity)
            {
                int deliveryTime = item.serviceTime * quantity + orderTime;
                // Create and store the order
                struct Order order;
                strcpy(order.userName, userName);
                strcpy(order.userPhoneNumber, userPhoneNumber);
                strcpy(order.userAddress, userAddress);
                strcpy(order.foodItem, foodItem);
                order.quantity = quantity;
                order.orderTime = orderTime;
                order.deliveryTime = deliveryTime;

                // Update the quantity of the food item in the restaurant
                restaurants[i].foodItems[j].quantity -= quantity;

                // Assuming orderID is a unique identifier, you can generate it using the current time
                int orderID = orderTime;

                return orderID;
            }
        }
    }

    return -1; // Order placement failed
}

// Function to get the list of food items in a restaurant in sorted order
void getItemListInSortedOrder(struct Restaurant restaurant)
{
    int numItems = restaurant.numFoodItems;
    struct FoodItem sortedItems[numItems];
    memcpy(sortedItems, restaurant.foodItems, numItems * sizeof(struct FoodItem));

    // Sort the items based on item name
    for (int i = 0; i < numItems - 1; i++)
    {
        for (int j = 0; j < numItems - i - 1; j++)
        {
            if (strcmp(sortedItems[j].name, sortedItems[j + 1].name) > 0)
            {
                struct FoodItem temp = sortedItems[j];
                sortedItems[j] = sortedItems[j + 1];
                sortedItems[j + 1] = temp;
            }
        }
    }

    printf("Food Items at %s, %s:\n", restaurant.name, restaurant.address);
    for (int i = 0; i < numItems; i++)
    {
        printf("%s - $%.2f\n", sortedItems[i].name, sortedItems[i].price);
    }
}

// Function to get the list of food items available in a given area in sorted order
void getItemListInAreaSortedOrder(struct Restaurant restaurants[], int numRestaurants, char area[])
{
    printf("Food Items in %s:\n", area);

    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        if (strstr(restaurant.address, area) != NULL)
        {
            getItemListInSortedOrder(restaurant);
        }
    }
}

// Function to get all special items in sorted order
void getAllSpecialItemListInSortedOrder(struct Restaurant restaurants[], int numRestaurants)
{
    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        printf("Special Items at %s, %s:\n", restaurant.name, restaurant.address);
        for (int j = 0; j < restaurant.numSpecialItems; j++)
        {
            printf("%s - $%.2f\n", restaurant.specialItems[j].name, restaurant.specialItems[j].price);
        }
    }
}

// Function to get all items of the day in sorted order
void getItemOfDayListInSortedOrder(struct Restaurant restaurants[], int numRestaurants, char area[])
{
    printf("Item of the Day in %s:\n", area);

    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        if (strstr(restaurant.address, area) != NULL)
        {
            printf("%s - $%.2f at %s, %s\n", restaurant.itemOfDay.name, restaurant.itemOfDay.price,
                   restaurant.name, restaurant.address);
        }
    }
}

// Function to find common food items in the restaurant list
void getCommonItem(struct Restaurant restaurants[], int numRestaurants)
{
    if (numRestaurants == 0)
    {
        printf("No restaurants in the list.\n");
        return;
    }

    // Create a set of food items for the first restaurant
    int numCommonItems = restaurants[0].numFoodItems;
    struct FoodItem commonItems[numCommonItems];
    memcpy(commonItems, restaurants[0].foodItems, numCommonItems * sizeof(struct FoodItem));

    // Compare with the food items of other restaurants
    for (int i = 1; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        int numItems = restaurant.numFoodItems;
        struct FoodItem tempItems[numItems];
        memcpy(tempItems, restaurant.foodItems, numItems * sizeof(struct FoodItem));

        int commonCount = 0;
        for (int j = 0; j < numItems; j++)
        {
            for (int k = 0; k < numCommonItems; k++)
            {
                if (strcmp(tempItems[j].name, commonItems[k].name) == 0)
                {
                    commonItems[commonCount++] = tempItems[j];
                    break;
                }
            }
        }

        numCommonItems = commonCount;
    }

    // Sort the common items by name
    for (int i = 0; i < numCommonItems - 1; i++)
    {
        for (int j = 0; j < numCommonItems - i - 1; j++)
        {
            if (strcmp(commonItems[j].name, commonItems[j + 1].name) > 0)
            {
                struct FoodItem temp = commonItems[j];
                commonItems[j] = commonItems[j + 1];
                commonItems[j + 1] = temp;
            }
        }
    }

    // Print the common items and their prices
    printf("Common Food Items in the Restaurant List:\n");
    for (int i = 0; i < numCommonItems; i++)
    {
        printf("%s - $%.2f\n", commonItems[i].name, commonItems[i].price);
    }
}

// Function to get all unique items in each restaurant
void getAllUniqueItem(struct Restaurant restaurants[], int numRestaurants)
{
    for (int i = 0; i < numRestaurants; i++)
    {
        struct Restaurant restaurant = restaurants[i];
        printf("Unique Food Items at %s, %s:\n", restaurant.name, restaurant.address);
        for (int j = 0; j < restaurant.numFoodItems; j++)
        {
            int isUnique = 1;
            struct FoodItem currentItem = restaurant.foodItems[j];
            for (int k = 0; k < numRestaurants; k++)
            {
                if (k != i)
                {
                    for (int l = 0; l < restaurants[k].numFoodItems; l++)
                    {
                        if (strcmp(currentItem.name, restaurants[k].foodItems[l].name) == 0)
                        {
                            isUnique = 0;
                            break;
                        }
                    }
                    if (!isUnique)
                    {
                        break;
                    }
                }
            }
            if (isUnique)
            {
                printf("%s - $%.2f\n", currentItem.name, currentItem.price);
            }
        }
    }
}

int main()
{
    // Variables to store user input
    char foodItem[50];
    int quantity;
    char userName[50];
    char userPhoneNumber[15];
    char userAddress[100];
    int numRestaurants;


    // Get user input for food item and quantity
    printf("Enter the food item: ");
    scanf("%s", foodItem);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Get user information
    printf("Enter your name: ");
    scanf("%s", userName);
    printf("Enter your phone number: ");
    scanf("%s", userPhoneNumber);
    printf("Enter your address: ");
    scanf("%s", userAddress);

    // Calculate the total service time for the delivery
    // getMinTime(foodItem, quantity);

    // // Place an order and get the order ID
    // int orderID = placeOrder(foodItem, quantity, userName, userPhoneNumber, userAddress);

    // if (orderID != -1)
    // {
    //     printf("Order placed successfully. Order ID: %d\n", orderID);
    // }
    // else
    // {
    //     printf("Order placement failed.\n");
    // }

    // // Calculate the total cost of the food items ordered
    // float totalCost = 0.0;

    // for (int i = 0; i < numRestaurants; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    //         if (strcmp(restaurants[i].FoodItems[j], foodItem) == 0)
    //         {
    //             totalCost = restaurants[i].FoodPrices[j] * quantity;
    //         }
    //     }
    // }

    // printf("Total Cost of Food Items Ordered: $%f\n", totalCost);

    // Initialize some sample data
    // struct Restaurant restaurants[2];
    // strcpy(restaurants[0].name, "Restaurant A");
    // strcpy(restaurants[0].address, "123 Main St, City A");
    // restaurants[0].numFoodItems = 3;
    // restaurants[0].foodItems[0].quantity = 100;
    // strcpy(restaurants[0].foodItems[0].name, "Biryani");
    // restaurants[0].foodItems[0].price = 10.99;
    // restaurants[0].foodItems[0].serviceTime = 20;
    // restaurants[0].foodItems[1].quantity = 50;
    // strcpy(restaurants[0].foodItems[1].name, "Burger");
    // restaurants[0].foodItems[1].price = 6.99;
    // restaurants[0].foodItems[1].serviceTime = 15;
    // restaurants[0].numSpecialItems = 2;
    // strcpy(restaurants[0].specialItems[0].name, "Special Salad");
    // restaurants[0].specialItems[0].price = 8.99;
    // strcpy(restaurants[0].specialItems[1].name, "Special Dessert");
    // restaurants[0].specialItems[1].price = 4.99;
    // strcpy(restaurants[0].itemOfDay.name, "Pasta");
    // restaurants[0].itemOfDay.price = 9.99;

    // strcpy(restaurants[1].name, "Restaurant B");
    // strcpy(restaurants[1].address, "456 Oak St, City B");
    // restaurants[1].numFoodItems = 3;
    // restaurants[1].foodItems[0].quantity = 75;
    // strcpy(restaurants[1].foodItems[0].name, "Biryani");
    // restaurants[1].foodItems[0].price = 11.99;
    // restaurants[1].foodItems[0].serviceTime = 18;
    // restaurants[1].foodItems[1].quantity = 60;
    // strcpy(restaurants[1].foodItems[1].name, "Sushi");
    // restaurants[1].foodItems[1].price = 12.99;
    // restaurants[1].foodItems[1].serviceTime = 25;
    // restaurants[1].numSpecialItems = 1;
    // strcpy(restaurants[1].specialItems[0].name, "Special Soup");
    // restaurants[1].specialItems[0].price = 7.99;
    // strcpy(restaurants[1].itemOfDay.name, "Pasta");
    // restaurants[1].itemOfDay.price = 9.99;

    numRestaurants = 10;

    // Sample usage of the functions
    getMinTime(restaurants, numRestaurants, "Biryani", 3);
    getItemAvailability(restaurants, numRestaurants, "Biryani");

    int orderID = placeOrder(restaurants, numRestaurants, "Biryani", 2, "John Doe", "123-456-7890", "789 Elm St");
    if (orderID != -1) {
        printf("Order placed successfully. Order ID: %d\n", orderID);
    } else {
        printf("Order placement failed.\n");
    }

    getItemListInSortedOrder(restaurants[0]);
    getItemListInAreaSortedOrder(restaurants, numRestaurants, "City A");
    getAllSpecialItemListInSortedOrder(restaurants, numRestaurants);
    getItemOfDayListInSortedOrder(restaurants, numRestaurants, "City A");
    getCommonItem(restaurants, numRestaurants);
    getAllUniqueItem(restaurants, numRestaurants);

    return 0;
}