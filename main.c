/*
Title       : Address Book Management System
Name        : Omkar Lohar
Date        : 08/07/2026
ID          : 26010_037
Description : This project is a console-based Address Book application developed in C.
              It allows users to manage contact details efficiently using fundamental
              programming concepts such as structures, arrays, pointers, file handling,
              and string manipulation.

              The Address Book stores multiple contacts, where each contact consists of
              a name, phone number, and email address. The application provides a
              user-friendly menu-driven interface to perform various operations.
              This addressBook allows us to:
                  1. Create contact
                  2. Search contact
                  3. Edit contact
                  4. Delete contacts
                  5. List all contacts
                  6. Save and Exit
                  7. Exit
*/
#include <stdio.h>
#include "contact.h"
#include "file.h"

int main()
{
    int choice;
    AddressBook addressBook;

    /* Initialize Address Book */
    initialize(&addressBook);

    do
    {
        printf("\n========================================\n");
        printf("        ADDRESS BOOK MENU\n");
        printf("========================================\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List All Contacts\n");
        printf("6. Save & Exit\n");
        printf("7. Exit\n");
        printf("========================================\n");

        printf("Enter your choice : ");
        scanf("%d", &choice);

        if(choice == 7){
        printf("Exited!\n");
        return 0;
        }
        
        switch(choice)
        {
            case 1:
                createContact(&addressBook);
                break;

            case 2:
                searchContact(&addressBook);
                break;

            case 3:
                editContact(&addressBook);
                saveContactsToFile(&addressBook);
                break;

            case 4:
                deleteContact(&addressBook);
                saveContactsToFile(&addressBook);
                break;

            case 5:
                listContacts(&addressBook);
                break;

            case 6:
                saveContactsToFile(&addressBook);
                printf("\nContacts saved successfully.\n");
                printf("Thank You!\n");
                break;
           
            default:
                printf("\nInvalid Choice! Please Try Again.\n");
        }

    } while(choice != 6);

    return 0;
}