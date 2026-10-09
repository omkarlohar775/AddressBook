#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// 1)Name Validation.
int validName(char *name)
{
    int i;

    //Check name atleast 4 character
    if(strlen(name) < 4)
    {
        printf("Error: Name must contain at least 4 characters.\n");
        return 0;
    }

    //cheak the first character must be an alphabet.
    if(!isalpha(name[0]))
    {
        printf("Error: Name must start with an alphabet.\n");
        return 0;
    }

    // Check each character symbols or number.
    for(i = 0; name[i] != '\0'; i++)
    {
        if(!(isalpha(name[i]) || name[i] == ' '))
        {
            if(isdigit(name[i]))
                printf("Error: Numbers are not allowed in the name.\n");
            else
                printf("Error: Symbols are not allowed in the name.\n");

            return 0;
        }
    }
    return 1;
}

// 2)Phone Validation. 
int validPhone(char *phone)
{
    int i;

    // Check length 10 or not.
    if(strlen(phone) != 10)
    {
        printf("Phone number must contain exactly 10 digits.\n");
        return 0;
    }

    // Check first digit must be 6 to 9.
    if(phone[0] < '6' || phone[0] > '9')
    {
        printf("First digit must be between 6 and 9.\n");
        return 0;
    }

    // Check all characters are digits.
    for(i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
        {
            printf("Symbols and alphabets are not allowed in the phone number.\n");
            return 0;
        }
    }
    return 1;
}

// 3) Email Validation.
int validEmail(char *email)
{
    int i, at = 0, dot = 0; // Counters for '@' and '.'
    int atPos = -1, dotPos = -1; // Store positions of '@' and '.'

    // Count @ and find last
    for(i = 0; email[i] != '\0'; i++)
    {
        
        if(email[i] == '@') // Check for '@'
        {
            at++;
            atPos = i;
        }
        else if(email[i] == '.') // Check for '.'
        {
            dot++;
            dotPos = i;
        }
        else if(!isalnum(email[i])) // Reject invalid characters
        {
            printf("Invalid symbol.\n");
            return 0;
        }
    }

    if(at == 0)
    {
        printf("Missing '@'.\n");
        return 0;
    }

    if(at > 1)
    {
        printf("Multiple '@' symbols are not allowed.\n");
        return 0;
    }

    if(dot == 0)
    {
        printf("Missing '.'.\n");
        return 0;
    }

    // Ensure '.' is after '@'
    if(dotPos < atPos)
    {
        printf("'.' must come after '@'.\n");
        return 0;
    }
    
    // Check for missing domain name
    if(dotPos == atPos + 1)
    {
        printf("Domain name is missing.\n");
        return 0;
    }

    if(dotPos == strlen(email) - 1)
    {
        printf("Domain extension is missing.\n");
        return 0;
    }

    // Check domain and extension 
    for(i = atPos + 1; email[i] != '\0'; i++)
    {
        if(email[i] == '.')
            continue;

        if(!isalnum(email[i]))
        {
            printf("Invalid character after '@'.\n");
            return 0;
        }
    }
    return 1;
}

/* ---------------- Duplicate Phone ---------------- */
int duplicatePhone(AddressBook *ab, char *phone)
{
    for(int i = 0; i < ab->contactCount; i++)
    {
        if(strcmp(ab->contacts[i].phone, phone) == 0)
            return 1;
    }
    return 0;
}

/* ---------------- Duplicate Email ---------------- */
int duplicateEmail(AddressBook *ab, char *email)
{
    for(int i = 0; i < ab->contactCount; i++)
    {
        if(strcmp(ab->contacts[i].email, email) == 0)
            return 1;
    }
    return 0;
}
