#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "contact.h"
#include "file.h"

// Initialize 
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

// 6) Save & Exit 
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    printf("Contacts saved. Exiting...\n");
    exit(0);
}

// 5)List Contacts 
void listContacts(AddressBook *addressBook)
{
    if (addressBook== NULL) // check the list is null or not
    {
        printf("Address Book is NULL.\n");
        return;
    }

    if (addressBook->contactCount <= 0) // Check the list is empty or not
    {
        printf("\nNo contacts found.\n");
        return;
    }

    printf("\n==========================================================================\n");
    printf("                  * LIST OF ALL CONTACTS *               ");

    /**     LOGIC TO SORT THE CONTACTS BEFORE LIST   **/
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            // Name is  used here to sort the contacts
            if (strcasecmp(addressBook->contacts[j].name,
                           addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }  
        }
    }
    // List the contacts
    printf("\n==========================================================================\n");
    printf("%-5s %-20s %-15s %-30s\n", "S.No", "Name", "Phone", "Email");
    printf("==========================================================================\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    //printf("==========================================================================\n");
}

// 1)Create Contact 

void createContact(AddressBook *addressBook)
{
    char name[50], phone[20], email[50];
    int valid, attempt;

    /* NAME */ 
    valid = 0; attempt = 0;
    while (!valid && attempt < 3) // Repeat until valid name or 3 attempts
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);

        valid=validName(name); //fun call to validation

        if(!valid) // If name is invalid
            attempt++;
    }
    if(!valid) return; // Exit the  function

    /* PHONE */
    valid = 0; attempt = 0;
    while (!valid && attempt < 3)
    {
        printf("Enter Phone: ");
        scanf("%s", phone);

        valid=validPhone(phone); //fun call to validation
       
        if (!valid)
            attempt++;
    }
    if(!valid) return;
    
    /* EMAIL */
    valid = 0; attempt = 0;
    while (!valid && attempt < 3)
    {
        printf("Enter Email: ");
        scanf("%s", email);
         // First character must be an alphabet
        if (!isalpha((unsigned char)email[0]))
        {
            printf("Starting character should be an alphabet.\n");
            attempt++; 
            continue;
        }
        valid = validEmail(email); //fun call to validation

        if(!valid)
            attempt++;
    }
    if(!valid) return;

    // STORE 
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;

    saveContactsToFile(addressBook);
    printf("Contact added successfully.\n");
}

//  2) Search Contact
void searchContact(AddressBook *addressBook)
{
    int choice;
    char key[50];
    int index[100];
    int count = 0;

    printf("\nSearch By\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Exit\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);

    if(choice==4){
        printf("Exited!!");
        return;
    }

    switch(choice)
    {
        case 1:
            printf("Enter Name : ");
            scanf(" %[^\n]", key);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                //comper the stored contact and enterd key 
                if(strcmp(addressBook->contacts[i].name, key) == 0)
                {
                    //store matching index
                    index[count] = i;
                    //display the matching index of name,phone,email
                    printf("==========================================================================\n");
                    printf("%d. %-20s %-12s %-30s\n",
                           count + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    printf("==========================================================================\n");
                    count++;
                }
            }
            break;

        case 2:
            printf("Enter Phone : ");
            scanf("%s", key);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                //comper the stored contact and enterd key
                if(strcmp(addressBook->contacts[i].phone, key) == 0)
                {
                    //store matching index
                    index[count] = i;
                    //display the matching index of name,phone,email
                    printf("%d. %-20s %-12s %-30s\n",
                           count + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    count++;
                }
            }
            break;

        case 3:
            printf("Enter Email : ");
            scanf("%s", key);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                //comper the stored contact and enterd key
                if(strcmp(addressBook->contacts[i].email, key) == 0)
                {
                    //store matching index
                    index[count] = i;
                    //display the matching index of name,phone,email
                    printf("%d. %-20s %-12s %-30s\n",
                           count + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    count++;
                }
            }
            break;
        
        default:
            printf("Can not found\n"); 
            return;
    }

    if(count == 0) //when break form switch case then exicuted
    {
        printf("No Contact Found.\n");
        return;
    }
    // Allow user to select one contact if multiple matches exist
    if(count > 1)
    {
        int select;

        printf("\nSelect Contact (1-%d): ", count);
        scanf("%d", &select);

        if(select < 1 || select > count)
        {
            printf("Invalid Selection\n");
            return;
        }

        printf("\nSelected Contact\n");
        printf("Name  : %s\n", addressBook->contacts[index[select-1]].name);
        printf("Phone : %s\n", addressBook->contacts[index[select-1]].phone);
        printf("Email : %s\n", addressBook->contacts[index[select-1]].email);
    }
}

// 3) Edit Contact
void editContact(AddressBook *addressBook)
{
    int searchChoice, editChoice;
    char key[50];
    int index[100], count = 0, found = -1;

    printf("\nEdit Contact By\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email ID\n");
    printf("4. Exit\n");
    printf("Enter your choice : ");
    scanf("%d", &searchChoice);

    if(searchChoice == 4)
    {
        printf("Exited!!");
        return;
    }
    switch (searchChoice) //read serach key
    {
    case 1:
        printf("Enter Name : ");
        scanf(" %[^\n]", key);
        break;

    case 2:
        printf("Enter Phone Number : ");
        scanf(" %s", key);
        break;

    case 3:
        printf("Enter Email ID : ");
        scanf(" %s", key);
        break;

    default:
        printf("Invalid Choice\n");
        return;
    }

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        //Compere the addressbook contact and enterd key
        if((searchChoice == 1 && strcmp(addressBook->contacts[i].name,key)==0) ||
           (searchChoice == 2 && strcmp(addressBook->contacts[i].phone,key)==0) ||
           (searchChoice == 3 && strcmp(addressBook->contacts[i].email,key)==0))
        {
            // Store matching contact index
            index[count] = i;
            //display the matching index of name,phone,email
            printf("%d. %-20s %-12s %-30s\n",
                    count+1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);
            count++;
        }
    }
    // Check if contact is not found
    if(count == 0)
    {
        printf("Contact Not Found.\n");
        return;
    }
    // Select contact if multiple matches exist
    if(count == 1)
        found = index[0];
    else
    {
        int select;

        printf("Select Contact : ");
        scanf("%d",&select);

        if(select < 1 || select > count)
        {
            printf("Invalid Selection.\n");
            return;
        }
        // Store selected contact index
        found = index[select-1];
    }
    // Display edit options
    printf("\nEdit\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Enter your choice : ");
    scanf("%d",&editChoice);

    switch(editChoice)//Edit choice
    {
        case 1: //if (1) enter new name
        {
            char name[50];

            printf("Enter New Name : ");
            scanf(" %[^\n]",name);
            //cheacking odd name, if it is exit then diplay
            if(strcmp(name,addressBook->contacts[found].name)==0)
            {
                printf("Old and New Name are Same.\n");
                return;
            }

            if(!validName(name)) //fun call validphone if it is 1 then, invalid name
            {
                printf("Invalid Name.\n");
                return;
            }
            //Upadte to contact list
            strcpy(addressBook->contacts[found].name,name);
            break;
        }

        case 2: //if (2) enter new phone
        {
            char phone[20];

            printf("Enter New Phone : ");
            scanf("%s",phone);
            //comper the odd name, if it is exit then disply
            if(strcmp(phone,addressBook->contacts[found].phone)==0)
            {
                printf("Old and New Phone Number are Same.\n");
                return;
            }

            if(!validPhone(phone))//fun call validphone if it is 1 then, invalid ph.no
            {
                printf("Invalid Phone Number.\n");
                return;
            }

            if(duplicatePhone(addressBook,phone)) //fun call validation for duplicate or not
            {
                printf("Phone Number Already Exists.\n");
                return;
            }
            //Upadte to contact list
            strcpy(addressBook->contacts[found].phone,phone);
            break;
        }

        case 3:
        {
            char email[50];

            printf("Enter New Email : ");
            scanf("%s",email);

            if(strcmp(email,addressBook->contacts[found].email)==0)
            {
                printf("Old and New Email are Same.\n");
                return;
            }

            if(!validEmail(email))
            {
                printf("Invalid Email.\n");
                return;
            }

            if(duplicateEmail(addressBook,email))
            {
                printf("Email Already Exists.\n");
                return;
            }

            strcpy(addressBook->contacts[found].email,email);
            break;
        }

        default:
            printf("Invalid Choice.\n");
            return;
    }

    printf("Contact Updated Successfully.\n");
}

// 4) Delete contact
void deleteContact(AddressBook *addressBook)
{
    int choice;
    char key[50];
    int index[100];
    int count = 0;
    int found = -1;

    printf("\nDelete Contact By\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email ID\n");
    printf("4. Exit\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);

    if(choice == 4){
        printf("Exited!!");
        return;
    }
    else if(choice>3){
        printf("Invalid choice\n");
        return;
    }
    printf("Enter Search Value : ");
    scanf(" %[^\n]",key);
    // Search for matching contacts
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if((choice == 1 && strcmp(addressBook->contacts[i].name,key)==0) ||
           (choice == 2 && strcmp(addressBook->contacts[i].phone,key)==0) ||
           (choice == 3 && strcmp(addressBook->contacts[i].email,key)==0))
        {
            index[count] = i;

            printf("%d. %-20s %-12s %-30s\n",
                    count + 1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);

            count++;
        }
    }

    if(count == 0)
    {
        printf("Contact Not Found.\n");
        return;
    }

    if(count == 1)
    {
        found = index[0];
    }
    else
    {
        int select;

        printf("Select Contact : ");
        scanf("%d",&select);

        if(select < 1 || select > count)
        {
            printf("Invalid Selection.\n");
            return;
        }

        found = index[select - 1];
    }

    char confirm;

    printf("\nAre you sure you want to delete this contact? (Y/N): ");
    scanf(" %c", &confirm);

    if(confirm == 'Y' || confirm == 'y')
    {
        for(int i = found; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact Deleted Successfully.\n");
    }
    else if(confirm == 'N' || confirm == 'n')
    {
        printf("Delete Cancelled.\n");
    }
    else
    {
        printf("Invalid Choice.\n");
    }
}