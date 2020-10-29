//Ronak Trivedi
//File name: linkedNode.c
//This file is a toolkit of function definitions for a nodal linked list structure

#include "linked.h" //Including the nodal linked list header file

//Function to initialize the linked list
node* nodeInit(char* customer_name, int num_burgers, int num_salads, boolean in_house)
{   
    //Allocating memory for a new node structure
    node *new_node;
    new_node = (node*)malloc(sizeof(node));

    //Initializing the new customer data
    new_node->name = customer_name;
    new_node->numBurger = num_burgers;
    new_node->numSalad = num_salads;
    new_node->inHouse = in_house;
    
    new_node->next = NULL; //Setting the link to the next customer to null
    return new_node; //Returning the newly intialized node
}

//Function to insert a new node onto the linked list
void addToList(node** head, char* customer_name, int num_burgers, int num_salads, boolean in_house, boolean debugMode)
{
    //Creating a new node to be attached to the linked list
    node *new_node;
    new_node = nodeInit(customer_name, num_burgers, num_salads, in_house);
    
    //Checking if the linked list is empty
    if(*head == NULL)
    {
        *head = new_node; //Setting the new node to be the head of the linked list
        return;
    }
    else
    {
        //Allocating memory for a temporary node to act as head of linked list
        node* temp_node;
        temp_node = *head;
        
        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
            printf("Debug Mode: in addToList()\n\n");
            printNode(temp_node);
        }
        //Iterating to the bottom of the linked list
        while(temp_node->next != NULL)
        {
            temp_node = temp_node->next;
            //--Debug Mode--
            if(debugMode == TRUE)
            {
                printNode(temp_node);
            }
        }
        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
        }
        temp_node->next = new_node; //Linking the new_node to the bottom node in the linked list
        return;
    }
}

//Function to return a boolean value indicating whether a name already exists in the linked list
boolean doesNameExist(node** head, char* customer_name, boolean debugMode)
{
    //Verifying that the list is not empty
    if (*head == NULL)
    {
        return FALSE;
    }
    else
    {
        //Allocating memory for a temporary node to act as head of linked list
        node *temp_node;
        //temp_node = (node*)malloc(sizeof(node));
        temp_node = *head;
        
        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
            printf("Debug Mode: in doesNameExist()\n\n");
        }

        int count = 0;//Variable to hold the number of items being traversed through
        
        //Traversing through the list, checking each node for the given name
        while(temp_node != NULL)
        {
            if(strcmp((temp_node->name), customer_name) == 0)
            {
                //--Debug Mode--
                if(debugMode == TRUE)
                {
                    if (count == 0)
                    {
                        printf("-------------------------------------------------------------------\n");
                        printf("Debug Mode: in doesNameExist()\n\n");
                        printNode(*head);
                        printf("-------------------------------------------------------------------\n");
                    }
                    else
                    {
                        printf("-------------------------------------------------------------------\n");
                    } 
                }
                //free(temp_node);
                return TRUE; //Executes if the given name matches a name on the list
            }
            else
            {
                count++;
                //--Debug Mode--
                if(debugMode == TRUE)
                {
                    printNode(temp_node);
                }
                temp_node = temp_node->next; //Changing the current node in the traversal to the next node
            }
        }
        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
        }
        //free(temp_node); //Freeing the temporary head node from memory
        return FALSE; //Executes if name is not found
    }
}

//Function to change the in-restaurant status when a call-ahead order arrives at the restaurant
//This operation will return a FALSE value if that order is already marked as being in the restaurant
boolean updateStatus(node** head, char* customer_name, boolean debugMode)
{
    //Allocating memory for a temporary node to act as head of linked list
    node* temp_node;
    //temp_node = (node*)malloc(sizeof(node));
    temp_node = *head;

    //--Debug Mode--
    if(debugMode == TRUE)
    {
        printf("-------------------------------------------------------------------\n");
        printf("Debug Mode: in updateStatus()\n\n");
        printNode(temp_node);
    }
    
    //Traversing through the list, checking each node for the given name
    while(temp_node != NULL)
    {
        if((strcmp((temp_node->name), customer_name) == 0) && temp_node->inHouse == FALSE)
        {
            temp_node->inHouse = TRUE; //Executes if the given name is not marked as in-restaurant
            if(debugMode == TRUE)
            {
                printf("-------------------------------------------------------------------\n");
            }
            return TRUE;
        }
        else
        {
            temp_node = temp_node->next; //Changing the current node in the traversal to the next node
            //--Debug Mode--
            if(debugMode == TRUE)
            {
                printNode(temp_node);
            }
        }
    }
    //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
        }
    //free(temp_node); //Freeing the temporary head node from memory
    return FALSE; //Executes if customer is already waiting in restaurant
}


//Function to to find the first in-restaurant order that matches the order prepared for pick up at the counter 
//This operation is to return the name of the group. This group is to be removed from the linked list
char* retrieveAndRemove(node** head, int burgersPrepared, int saladsPrepared, boolean debugMode)
{
    //Allocating memory for a variable to hold the name of the customer to be removed
    char *name_removed;

    if(*head == NULL) //Checking if we are trying to remove a node from an empty linked list
    {
        //Printing the error message and breaking out of the function
        printf("There are no customers on the list.\n\n");
        return NULL;
    }
    
    else if((*head)->next == NULL) //Checking if there is only 1 order on the list
    {
        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
            printf("Debug Mode: in retrieveAndRemove()\n\n");
            printNode(*head);
            printf("-------------------------------------------------------------------\n");
        }
        if(((*head)->inHouse == TRUE) && ((*head)->numBurger <= burgersPrepared) && ((*head)->numSalad <= saladsPrepared))
        {
            name_removed = (*head)->name;
            *head = NULL;
            return(name_removed);
        }
        else
        {
            printf("No orders were fulfilled.\n\n");
            return NULL;
        }
    }
    
    else
    {
        //Allocating memory for a temporary node to act as head of linked list
        node* temp_node;
        //temp_node = (node*)malloc(sizeof(node));
        temp_node = *head;

        //Allocating memory for a node to hold the previous node to the target node
        node* prev_node;
        //prev_node = (node*)malloc(sizeof(node));

        int position_count = 0; //Variable to keep track of the position number during the traversal

        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
            printf("Debug Mode: in retrieveAndRemove()\n\n");
            printNode(temp_node);
        }

        //Traversing until a fulfillable order is reached on the list
        while((temp_node != NULL) && ((temp_node->inHouse == FALSE) || (temp_node->numBurger > burgersPrepared) || (temp_node->numSalad > saladsPrepared)))
        {
            prev_node = temp_node;
            temp_node = temp_node->next;
            position_count++;
            //--Debug Mode--
            if(debugMode == TRUE)
            {
                printNode(temp_node);
            }
        }
        //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
        }
        if(temp_node == NULL)
        {
            printf("No orders were fulfilled.\n"); //Executes if no orders on the list match the prepared food
            free(temp_node);
            return NULL;
        }
        else
        {
            if(position_count == 0)
            {
                name_removed = temp_node->name;
                *head = temp_node->next;
                //free(temp_node);
                return(name_removed);
            }
            else
            {
                name_removed = temp_node->name; //Storing the name to be removed
                prev_node->next = temp_node->next; //Re-linking the nodes, skipping the node to be removed
                //free(temp_node); //Freeing the node to be removed from memory
                return(name_removed);
            }
        }
        
    }
}

//Function to return the number of orders waiting ahead of an order with a specific name
int countOrdersAhead(node** head, char* current_name, boolean debugMode)
{
    int num_ahead = 0; //Variable to store the number of orders ahead of a given order

    //Allocating memory for a temporary node to act as head of linked list
    node* temp_node;
    //temp_node = (node*)malloc(sizeof(node));
    temp_node = *head;

    //--Debug Mode--
    if(debugMode == TRUE)
    {
        printf("-------------------------------------------------------------------\n");
        printf("Debug Mode: in countOrdersAhead()\n\n");
        printNode(temp_node);
    }
    
    //Traversing through the linked list
    while(temp_node != NULL)
    {
        //Checking each node for the given name 
        if(strcmp(temp_node->name,current_name) == 0)
        {
            if(debugMode == TRUE)
            {
                printf("-------------------------------------------------------------------\n");
            }
            return num_ahead; //Returning when the given name is reached in the traversal
        }
        else
        {
            num_ahead++; //Incrementing when the current node in the traversal does not match the given name
            temp_node = temp_node->next;
            //--Debug Mode--
            if(debugMode == TRUE)
            {
                printNode(temp_node);
            }
        }
    }
    //--Debug Mode--
        if(debugMode == TRUE)
        {
            printf("-------------------------------------------------------------------\n");
        }
    //free(temp_node); //Freeing the temporary node from memory
}

//Function to traverse down the list until a specific ordername is encountered. 
//For each node that is traversed through, that node’s orders are printed.
void displayOrdersAhead(node** head, char* current_name, boolean debugMode)
{
    int num_ahead = 0; //Variable to store the number of orders ahead of a given order

    //Allocating memory for a temporary node to act as head of linked list
    node* temp_node;
    //temp_node = (node*)malloc(sizeof(node));
    temp_node = *head;

    //--Debug Mode--
    if(debugMode == TRUE)
    {
        printf("-------------------------------------------------------------------\n");
        printf("Debug Mode: in displayOrdersAhead()\n\n");
        printNode(temp_node);
    }
    
    //Traversing through the linked list
    while(temp_node != NULL)
    {
        //Checking each node for the given name
        if(strcmp(temp_node->name,current_name) == 0)
        {
            if(debugMode == TRUE)
            {
                printf("-------------------------------------------------------------------\n");
            }
            return; //Returning when the given name is reached in the traversal
        }
        else
        {
            num_ahead++; //Incrementing when the current node in the traversal does not match the given name
            
            //Printing the order details of the current node in the traversal
            printf("Order #%d:  Name: %s\n",num_ahead,temp_node->name);
            printf("            Order Details: %d Burgers & %d Salads\n",temp_node->numBurger,temp_node->numSalad);
            if(temp_node->inHouse == FALSE)
            {
                printf("            In-Restaurant: No\n");
            }
            else
            {
                printf("            In-Restaurant: Yes\n");
            }
            temp_node = temp_node->next;
            //--Debug Mode--
            if(debugMode == TRUE)
            {
                printNode(temp_node);
            }
        }
    }
    //--Debug Mode--
    if(debugMode == TRUE)
    {
        printf("-------------------------------------------------------------------\n");
    }
    //free(temp_node); //Freeing the temporary node from memory
}

//Function to traverse down the entire list from beginning to end.  
//As each node is traversed, that node’s name, order details, and in-restaurant status is printed.
void displayListInformation(node** head)
{
    //Checking if the list is empty
    if(*head == NULL)
    {
        printf("The list is empty, there are no orders to display.\n\n");
        return;
    }
    int num_orders = 0; //Variable to store the total number of orders on the linked list

    //Allocating memory for a temporary node to act as head of linked list
    node* temp_node;
    //temp_node = (node*)malloc(sizeof(node));
    temp_node = *head;
    
    //Traversing through the entire linked list
    while(temp_node != NULL)
    {
      
        num_orders++; //Incrementing each time a node is reached in the traversal
        
        //Printing the order details of the current node in the traversal
        printf("Order #%d:  Name: %s\n", num_orders, temp_node->name);
        printf("            Order Details: %d Burgers & %d Salads\n",temp_node->numBurger,temp_node->numSalad);
        if(temp_node->inHouse == FALSE)
        {
            printf("            In-Restaurant: No\n\n");
        }
        else
        {
            printf("            In-Restaurant: Yes\n\n");
        }
        temp_node = temp_node->next;
    }
    printf("Total number of orders on the list: %d\n", num_orders);
    //free(temp_node); //Freeing the temporary node from memory
}

//Function to return the estimated waiting time for the specific name. 
//The function will check the number of burgers and salads ordered ahead of the specified name 
//The function uses known preparing time (10 minutes for burger and 5 minutes for salad) to calculate the estimated wait time.
int displayWaitingTime(node** head, char* current_name, boolean debugMode)
{
    int wait_time = 0; //Variable to store the estimated wait time for a given order

    //Allocating memory for a temporary node to act as head of linked list
    node* temp_node;
    //temp_node = (node*)malloc(sizeof(node));
    temp_node = *head;

    //--Debug Mode--
    if(debugMode == TRUE)
    {
        printf("-------------------------------------------------------------------\n");
        printf("Debug Mode: in displayWaitingTime()\n\n");
        printNode(temp_node);
    }
    
    //Traversing through the linked list
    while(temp_node != NULL)
    {
        //Checking each node for the given name
        if(strcmp(temp_node->name, current_name) == 0)
        {
            wait_time = wait_time + ((temp_node->numBurger) * 10) + ((temp_node->numSalad) * 5); //Updating the waiting time
            if(debugMode == TRUE)
            {
                printf("-------------------------------------------------------------------\n");
            }
            return wait_time; //Returning when the given name is reached in the traversal
        }
        else
        {
            wait_time = wait_time + ((temp_node->numBurger) * 10) + ((temp_node->numSalad) * 5); //Updating the waiting time
            temp_node = temp_node->next;
            //--Debug Mode--
            if(debugMode == TRUE)
            {
                printNode(temp_node);
            }
        }
    }
    //--Debug Mode--
    if(debugMode == TRUE)
    {
        printf("-------------------------------------------------------------------\n");
    }
    //free(temp_node); //Freeing the temporary node from memory
}

//Function to print order details of a given node
//Predominantly used for debug mode
void printNode(node* current_node)
{
    //Checking if the node to be printed exists
    if (current_node == NULL)
    {
        printf("Traversed through: NULL\n");
        return;
    }
    else
    {
        //Printing the order details of the current node in the traversal
        printf("Traversed through:  Name: %s\n", current_node->name);
        printf("                    Order Details: %d Burgers & %d Salads\n",current_node->numBurger,current_node->numSalad);
        if(current_node->inHouse == FALSE)
        {
            printf("                    In-Restaurant: No\n");
        }
        else
        {
            printf("                    In-Restaurant: Yes\n");
        }
        }
}
