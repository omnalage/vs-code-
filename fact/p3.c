#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

struct Restaurant
{
    char name[50];
    char address[100];
    char FoodItems[10][50];
    float FoodPrices[10];
    char specialItems[10][50];
    float specialPrices[10];
    char itemOfDay[50];
    float itemOfDayPrice;
    float serviceTime;
};

struct Order
{
    char userName[50];
    char userPhoneNumber[15];
    char userAddress[100];
    char foodItem[50];
    int quantity;
    float orderTime;
    float deliveryTime;
};

struct Restaurant restaurants[10] = {
  {
        "Veggietude",
        "Ring Road Trimurti Nagar",
        {"Chilli Paneer", "Chilli Manchorian", "Paneer Tikka Masala", "Biryani", "Dum Aloo"},
        {190.0, 170.0, 160.0, 180.0, 150.0},
        {"Chicken Handi", "Paneer Angari"},
        {600.0, 300.0},
        "Paneer Tikka Biryani",
        250.0
    },
    {
        "Shree Ganesh Sagar",
        "Main Road Dhantoli",
        {"Butter Kulcha", "Keema Kastori", "Mutton Biryani", "Tandori Aloo", "Kadhai Paneer"},
        {150.0, 180.0, 250.0, 200.0, 200.0},
        {"Hyderabadi Biryani", "Veg Makhanwala"},
        {300.0, 280.0},
        "Mutton Do Pyaza",
        350.0
    },
    {
        "Ashvaryum Restaurant",
        "Beltarodi Road Besa road",
        {"Laccha Paneer", "Egg Curry", "Veg Kofta", "Chicken Curry", "Laccha Chicken"},
        {280.0, 180.0, 270.0, 330.0, 350.0},
        {"Punjabi Chicken ", "Veg Cheesy Kofta"},
        {350.0, 290.0},
        "Punjabi Mutton",
        400.0
    },
    {
        "Euphoria Restaurant ",
        "Nandanvan Road Nandanvan Colony",
        {"Thai Noodles", "Paneer Hakka Noodles", "Paneer Saoji", "Bhindi Kurkura", "Sev Bhaji"},
        {280.0, 230.0, 300.0, 230.0, 220.0},
        {"Euphoria Special Sabzi", "Punjabi Paneer Masala"},
        {550.0, 320.0},
        "Euphoria Special Pizza",
        310.0
    },
    {
        "Durva Restaurant",
        "Stadium Road dhantoli",
        {"Veg Kofta ", "Palak Paneer", "Kadhai Veg", "Palak Corn", "Handi Veg"},
        {335.0, 335.0, 320.0, 355.0, 320.0},
        {"Mexican Fried Rice", "Paneer Taka Tak"},
        {320.0, 355.0},
        "Special King Kofta",
        400.0
    },
    {
        "Anandam Restaurant",
        "Kachimet Amravati road",
        {"Fish Finger", "Mutton Kali Miri", "Veg Ball Asian Style", "Jain Bhindi Kurkuri", "Double Dal Tadka"},
        {280.0, 490.0, 300.0, 300.0, 210.0},
        {"Baby Corn Mushroom Laziz", "Bhindi Do Pyaz"},
        {375.0, 325.0},
        "Penne Aglio Olio Sauce Pasta",
        450.0
    },
    {
        "Food links",
        "C A Road Central Avenue Road",
        {"Palak Paneer", "Paneer Masala", "Dal Tadka", "Rassa Patodi", "Gobi Aloo Matar"},
        {150.0, 190.0, 120.0, 120.0, 120.0},
        {"Mushroom Cheese Pizza", "Mysore Cheese Masala Dosa"},
        {190.0, 210.0},
        "Fried Mini Chocolate Idli",
        300.0
    },
    {
        "Aaradhya Restro",
        "Umred road Umrer",
        {"Chana Masala", "Methi Matar Malai", "Navratna Korma", "Kaju Curry", "Tomato Chutney"},
        {220.0, 270.0, 270.0, 300.0, 240.0},
        {"Diwani Handi", "Haryali Kofta"},
        {260.0, 260.0},
        "Garden Glory",
        330.0
    },
    {
        "Ratnakar restaurants",
        "Gangabai Ghat Road Bagadganj",
        {"Keema Kastori", "Saoji Curry", "Veg Kadhai", "Veg Pataila", "Sev Bhaji"},
        {250.0, 270.0, 260.0, 230.0, 290.0},
        {"Special Veg Kolhapuri", "Veg Khus Khus"},
        {300.0, 350.0},
        "Special Dal Kolhapuri",
        450.0
    },
    {
        "Babuji South Indian Restraurant",
        "College road chandan nagar",
        {"Biryani", "Junglee Paneer", "Chilli Pepper Potato", "Veg Crunchy", "Gobi 69"},
        {300.0, 290.0, 270.0, 270.0, 500.0},
        {"Veg Garden", "Dragon Pizza"},
        {450.0, 550.0},
        "Paneer Mumtaz",
        700.0
    }

};

int numRestaurants = 10;

void getMinTime(char foodItem[], int quantity)
{
    float minTime = -1;
    char minRestaurantName[50];
    char minRestaurantAddress[100];

    for (int i = 0; i < numRestaurants; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (strcmp(restaurants[i].FoodItems[j], foodItem) == 0)
            {
                float totalTime = restaurants[i].serviceTime * quantity;
                if (minTime == -1 || totalTime < minTime)
                {
                    minTime = totalTime;
                    strcpy(minRestaurantName, restaurants[i].name);
                    strcpy(minRestaurantAddress, restaurants[i].address);
                }
            }
        }
    }

    if (minTime == -1)
    {
        printf("Food item not found in any restaurant.\n");
    }
    else
    {
        printf("Restaurant Name: %s\n", minRestaurantName);
        printf("Restaurant Address: %s\n", minRestaurantAddress);
        printf("Delivery Time: %.2f minutes\n", minTime);
    }
}

void getItemAvailability(char foodItem[])
{
    printf("Restaurants offering %s:\n", foodItem);
    for (int i = 0; i < numRestaurants; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (strcmp(restaurants[i].FoodItems[j], foodItem) == 0)
            {
                printf("Restaurant: %s\n", restaurants[i].name);
                printf("Price: %.2f\n", restaurants[i].FoodPrices[j]);
            }
        }
    }
}

int placeOrder(char foodItem[], int quantity, char userName[], char userPhoneNumber[], char userAddress[])
{
    int orderID = rand() % 1000;

    float minTime = -1;
    int minRestaurantIndex = -1;

    for (int i = 0; i < numRestaurants; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (strcmp(restaurants[i].FoodItems[j], foodItem) == 0)
            {
                float totalTime = restaurants[i].serviceTime * quantity;
                if (minTime == -1 || totalTime < minTime)
                {
                    minTime = totalTime;
                    minRestaurantIndex = i;
                }
            }
        }
    }

    if (minRestaurantIndex == -1)
    {
        printf("Food item not found in any restaurant.\n");
        return -1;
    }
    else
    {
        struct Order order;
        strcpy(order.userName, userName);
        strcpy(order.userPhoneNumber, userPhoneNumber);
        strcpy(order.userAddress, userAddress);
        strcpy(order.foodItem, foodItem);
        order.quantity = quantity;
        order.orderTime = 0;
        order.deliveryTime = minTime;
        return orderID;
    }
}

int main()
{

     // Initialize random seed for generating order IDs
    // srand(time(NULL));

    // Variables to store user input
    char foodItem[50];
    int quantity;
    char userName[50];
    char userPhoneNumber[15];
    char userAddress[100];

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
    getMinTime(foodItem, quantity);

    // Place an order and get the order ID
    int orderID = placeOrder(foodItem, quantity, userName, userPhoneNumber, userAddress);

    if (orderID != -1) 
    {
        printf("Order placed successfully. Order ID: %d\n", orderID);
    } 
    else
     {
        printf("Order placement failed.\n");
    }

    // Calculate the total cost of the food items ordered
    float totalCost = 0.0;

    for (int i = 0; i < numRestaurants; i++) {
        for (int j = 0; j < 10; j++) {
            if (strcmp(restaurants[i].FoodItems[j], foodItem) == 0) {
                totalCost = restaurants[i].FoodPrices[j] * quantity;
            }
        }
    }

    printf("Total Cost of Food Items Ordered: ₹%f\n", totalCost);

    return 0;
}