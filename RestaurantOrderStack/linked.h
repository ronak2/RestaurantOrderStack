//Ronak Trivedi
//File name: linked.h
//Header file for linked list of nodes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//Defining true and false as boolean types
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

//Declaring debug mode
extern boolean debugMode;

//Defining linked list node structure
typedef struct linkedNode
{
  int numBurger; //Variable to hold number of bugers ordered by the customer
  int numSalad; //Variable to hold number of salads ordered by the customer
  boolean inHouse; //Variable denoting if the customer is in or out of the restaurant
  char *name; //Variable to hold customer name, maximum name length of 30 letters
  struct linkedNode *next; // Pointer to the next node in the linked list
}node;

/* 
The following functions are defined in the file: linkedNode.c 
*/

//Function to initialize the linked list
node* nodeInit(char* customer_name, int num_burgers, int num_salads, boolean in_house);

//Function to insert a new node onto the linked list
void addToList(node** head, char* customer_name, int num_burgers, int num_salads, boolean in_house, boolean debugMode);

//Function to return a boolean value indicating whether a name already exists in the linked list
boolean doesNameExist(node** head, char* customer_name, boolean debugMode);

//Function to change the in-restaurant status when a call-ahead order arrives at the restaurant
//This operation will return a FALSE value if that order is already marked as being in the restaurant
boolean updateStatus(node** head, char* customer_name, boolean debugMode);

//Function to to find the first in-restaurant order that matches the order prepared for pick up at the counter 
//This operation is to return the name of group. This group is to be removed from the linked list
char* retrieveAndRemove(node** head, int burgersPrepared, int saladsPrepared, boolean debugMode);

//Function to return the number of orders waiting ahead of an order with a specific name
int countOrdersAhead(node** head, char* current_name, boolean debugMode);

//Function to traverse down the list until a specific ordername is encountered. 
//For each node that is traversed through, that node’s orders are printed.
void displayOrdersAhead(node** head, char* current_name, boolean debugMode);

//Function to traverse down the entire list from beginning to end.  
//As each node is traversed, that node’s name, order details, and in-restaurant status is printed.
void displayListInformation(node** head);

//Function to return the estimated waiting time for the specific name. 
//The function will check the number of burgers and salads ordered ahead of the specified name 
//The function uses known preparing time (10 minutes for burger and 5 minutes for salad) to calculate the estimated wait time.
int displayWaitingTime(node** head, char* current_name, boolean debugMode);

//Function to print order details of a given node
//Predominantly used for debug mode
void printNode(node* current_node);

/* 
The following functions are defined in the file: linkedList.c 
*/

//Function to add a new in-restaurant customer to the linked list of orders
void doAdd(node** head, boolean debugMode);

//Function to add a new out-of-restaurant customer to the linked list of orders
void doCallAhead(node** head, boolean debugMode);

//Function to mark the call ahead order as in-restaurant using a given name 
void doWaiting(node** head, boolean debugMode);

//Function retrieve and remove the first order on the order list that is waiting in the restaurant 
//The returned order must contain less than or equal to number of prepared burgers and salads
void doRetrieve(node** head, boolean debugMode);

//Function to list the complete order details and total number of all orders that are ahead of a given name on the order list
void doList (node** head, boolean debugMode);

//Function to list the complete order details and total number of all orders on the order list
void doDisplay(node** head);

//Function to display an estimated waiting time for a given name 
//Burger preparation takes 10 minutes and salad preparation takes 5 minutes
void doEstimateTime(node** head, boolean debugMode);

//Function to free the entire linked list from memory
void clear(node** head);

/* 
The following functions are defined in the file: userInterface.c 
*/

//Function to read in the customer name until the end of the input
char* getName();

//Function to clear input until next end of line character
void clearToEoln();

//Function to read in the next positive integer, counting zero as a positive number
int getPosInt ();