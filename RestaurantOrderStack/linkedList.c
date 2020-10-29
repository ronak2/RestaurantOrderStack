//Ronak Trivedi
//File name: linkedList.c
//This file is a toolkit of function definitions to interact with nodal linked list functions

#include "linkedNode.c" //Including the toolkit of functions for a nodal linked list structure

//Function to add a new customer to the linked list of orders
void doAdd(node** head, boolean debugMode)
{
 /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Add command requires an integer value of at least 0\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  

 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

 boolean in_house = TRUE; //Denoting that the customer is in the restaurant
 
 //Verifying that the name is not already on the linked list
 if(doesNameExist(head, name, debugMode) == TRUE)
 {
   printf("The given name is already on the list.\n"); //Printing the error message
   free(name);
   return;
 }
 else
 {
   addToList(head, name, NumBurgers, NumSalads, in_house, debugMode); //Adding the customer to the linked list
   printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name, NumBurgers, NumSalads);
 }
}

void doCallAhead(node** head, boolean debugMode)
{
   /* get number of burgers ordered from input */
 int NumBurgers = getPosInt();
 if (NumBurgers < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

  /* get number of salads ordered from input */
 int NumSalads = getPosInt(); 
 if (NumSalads < 0)
   {
    printf ("Error: Call-ahead command requires an integer value of at least 0\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }  


 /* get group name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
    printf ("  where:<# burgers> is the number of ordered burgers\n");
    printf ("        <# salads> is the number of ordered salads\n");
    printf ("        <name> is the name of the person putting the order\n");
    return;
   }

 boolean in_house = FALSE; //Denoting that the customer is in the restaurant
 
 //Verifying that the name is not already on the linked list
 if(doesNameExist(head, name, debugMode) == TRUE)
 {
   printf("The given name is already on the list.\n"); //Printing the error message
   free(name);
   return;
 }
 else
 {
   addToList(head, name, NumBurgers, NumSalads, in_house, debugMode); //Adding the customer to the linked list
   printf ("Adding call-ahead order for \"%s\": %d burgers and %d salads\n", name, NumBurgers, NumSalads);
 }
}

void doWaiting(node** head, boolean debugMode)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
   }

//Verifying that the customer's name is on the linked list and they are not checked-in yet
 if(doesNameExist(head, name, debugMode) == FALSE)
 {
   printf("The given name is not on the list.\n"); //Printing the error message
   return;
 }
 else if(updateStatus(head, name, debugMode) == FALSE)
 {
   printf("This customer is already marked as in-restaurant.\n"); //Printing the error message
   free(name);
   return;
 }
 else
 {
   printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
   free(name);
 }
}

void doRetrieve(node** head, boolean debugMode)
{
 /* get info of prepared food ready on the counter from input */
 int PreparedBurgers = getPosInt();
 if (PreparedBurgers < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }

 int PreparedSalads = getPosInt();
 if (PreparedSalads < 0)
   {
    printf ("Error: Retrieve command requires an integer value of at least 0\n");
    printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
    printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
    printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
    return;
   }   

 clearToEoln();
 printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n\n", PreparedBurgers ,PreparedSalads);

 //Retrieving the next order that can be fulfilled by the given prepared food
 char *retrieved;
 retrieved = (char*)malloc(sizeof(char)*30);
 retrieved = retrieveAndRemove(head, PreparedBurgers, PreparedSalads, debugMode);
 if (retrieved != NULL)
 {
   printf("%s's order is placed on the counter and removed from the order list.\n", retrieved); //Executes if an existing order can be fulfilled
   free(retrieved); //Freeing the customers name from memory
 }
}

void doList (node** head, boolean debugMode)
{
 /* get order name from input */
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

 printf ("Order for \"%s\" is behind the following orders:\n\n", name);

 //Verifying that the customer's name is on the linked list
 if(doesNameExist(head, name, debugMode) == FALSE)
 {
   printf("The given name is not on the list.\n"); //Printing the error message
   free(name);
   return;
 }
 else
 {
   //Printing details of all orders ahead of the given name
   displayOrdersAhead(head, name, debugMode);
   int numAhead = countOrdersAhead(head, name, debugMode);
   printf("\nTotal number of orders ahead of %s: %d\n\n", name, numAhead);
   free(name);
 }
}
 
void doDisplay(node** head)
{
 clearToEoln();
 printf ("Display information about all orders: \n\n");
 displayListInformation(head); //Printing order details for each order in the list
}

void doEstimateTime(node** head, boolean debugMode)
{
  /* get order name from input */
 
 char *name = getName();
 if (NULL == name)
   {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: t <name>\n");
    printf ("  where: <name> is the name of the order to inquire about\n");
    return;
   }

 //Verifying that the customer's name is on the linked list
 if(doesNameExist(head, name, debugMode) == FALSE)
 {
   printf("The given name is not on the list.\n"); //Printing the error message
   free(name);
   return;
 }
 else
 {
   //Printing the estimated waiting time for the given name
   int waitTime = displayWaitingTime(head, name, debugMode);
   printf("Estimated wait time for %s: %d minutes\n\n", name, waitTime);
   free(name);
 }
}

//Function to free the entire linked list from memory
void clear(node** head)
{ 
  //Declaring nodes to hold positions on the linked list during traversal
  node* next_node;
  node* current_node;

  //Freeing the linked list from memory
  current_node = *head;
  while(*head != NULL)
  {
    next_node = current_node->next;
    free(current_node->name);
    free(current_node);
    current_node = next_node;
  }
  free(*head);
}

