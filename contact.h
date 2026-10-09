#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

// Contact Structure 
typedef struct
{
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Address Book Structure 
typedef struct
{
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

// Contact Operations 
void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

// Validation Functions 
int validName(char name[]);
int validPhone(char phone[]);
int validEmail(char email[]);

// Duplicate Checking 
int duplicatePhone(AddressBook *addressBook, char phone[]);
int duplicateEmail(AddressBook *addressBook, char email[]);

#endif