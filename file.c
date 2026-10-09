#include <stdio.h>
#include <stdlib.h>
#include "contact.h" //addressbook & contact strcture defination
#include "file.h"    //function declaration for file operation

/* Save Contacts */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "w"); // Open file in write mode

    if(fp == NULL)      // cheak if file exists
    {
        printf("Error: Unable to open file for writing.\n");
        return;
    }

    fprintf(fp, "#%d\n", addressBook->contactCount);  //total number of contact
    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    fclose(fp); // Close the file
}

/* Load Contacts */
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r"); // Open in read mode

    addressBook->contactCount = 0; // Initialize contact count

    if (fp == NULL) // Check if file exists
        return;

    char firstLine[100];

    fgets(firstLine, sizeof(firstLine), fp); // Read and ignore the first line (#count)

    while (addressBook->contactCount < MAX_CONTACTS && // Check array limit
           fscanf(fp,"%49[^,],%19[^,],%49[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3)
    {
        addressBook->contactCount++;
    }

    fclose(fp); // Close the file
}    

