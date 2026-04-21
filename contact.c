
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>
void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    printf("\n &&&&&&&&&&**List of contacts**&&&&&&&&&& \n\n");


    printf("----------------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-25s %-40s\n","Sl.No ","Name ", "Phone ", "Email                  |");
    printf("----------------------------------------------------------------------------------\n");
    if (addressBook->contactCount == 0)
    {
        printf("No contacts saved!!! \n");
        
    }
    else
    {
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("%-10d %-20s %-25s %-40s\n", i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
        printf("\n");
        
    }
    printf("----------------------------------------------------------------------------------\n");
    }
    printf("Total contact= %d",addressBook->contactCount);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50];
    int attempts=0,maxattempts=3;
    while(attempts<maxattempts)
    {
        int i;
        attempts++;
        printf("Enter the name (Attempts %d of %d): ",attempts,maxattempts);
        scanf(" %[^\n]",name); 

        for(i=0;name[i]!='\0';i++)
        {
            if(!isalpha(name[i])&&name[i]!=' ') 
            {
                printf("Name can only contain Alphabetic and spaces.\n");
                break; 
            }
        }
        if(name[i]=='\0')
        {
            break;
        }
        
    }
    
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);


    // ===== Phone Validation =====
    char number[20];    
    int attempt=0,maxattempt=3;
    while(attempt<maxattempt)
    {
        int i,duplicate=0;
        attempt++;
        printf("Enter the phone (Attempts %d of %d): ",attempt,maxattempt);
        scanf(" %[^\n]",number);

        if(strlen(number)!=10)
        {
            printf("Phone Number must be exactly 10 digits!\n");
            continue;
        }
        for(i=0;i<10;i++)
        {
            if(!isdigit(number[i]))
            {
                printf("Phone Number must contain only digits!\n");
                break;
            }
        }
        if(i!=10)continue;
        for(i=0;i<addressBook->contactCount;i++) 
        {
            if(strcmp(addressBook->contacts[i].phone, number) == 0)
            {
                printf("This phone number already exists!\n");
                duplicate = 1;
                break;
            }
        }
        if(duplicate)continue;  
        break;
    
    }

    strcpy(addressBook->contacts[addressBook->contactCount].phone, number);


   // ===== Email Validation =====
char mail[50];
int i;
int Attempts = 0, Maxattempts = 3;
int success = 0;  // flag for success

while (Attempts < Maxattempts)
{
    int count = 0, valid = 1;
    Attempts++;
    printf("Enter the email (Attempt %d of %d): ", Attempts, Maxattempts);
    scanf(" %[^\n]", mail);

    // Check lowercase
    for (i = 0; mail[i] != '\0'; i++)
    {
        if (isupper(mail[i]))
        {
            printf("Error: Email must be lowercase\n");
            valid = 0;
            break;
        }
    }
    if (!valid) continue;

    // Check exactly one '@'
    for (i = 0; mail[i] != '\0'; i++)
    {
        if (mail[i] == '@')
            count++;
    }
    if (count != 1)
    {
        printf("Error: Email must contain exactly one '@'\n");
        continue;
    }

    // Must end with ".com"
    int len = strlen(mail);
    if (len < 5 || strcmp(&mail[len - 4], ".com") != 0)
    {
        printf("Error: Email must end with '.com'\n");
        continue;
    }

    // Check allowed characters
    valid = 1;
    for (i = 0; mail[i] != '\0'; i++)
    {
        if (!(islower(mail[i]) || isdigit(mail[i]) ||
              mail[i] == '@' || mail[i] == '.' ||
              mail[i] == '_' || mail[i] == '-'))
        {
            printf("Error: Invalid character '%c'. Only letters, digits, @ . _ - allowed.\n", mail[i]);
            valid = 0;
            break;
        }
    }
    if (!valid) continue;

    // Check duplicate
    int duplicate = 0;
    for (int j = 0; j < addressBook->contactCount; j++)
    {
        if (strcmp(addressBook->contacts[j].email, mail) == 0)
        {
            printf("This email already exists\n");
            duplicate = 1;
            break;
        }
    }
    if (duplicate) continue;

    success = 1;  // mark as valid email
    break;
}

// only add contact if valid email was entered
if (success)
{
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
    addressBook->contactCount++;
    printf("Contact added successfully!\n");
}
else
{
    printf("Failed to add contact after %d attempts.\n", Maxattempts);
}
}
void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice;
    char search[50];
    int found=0;

    if(addressBook->contactCount==0)
    {
        printf("\nNo contacts to search.\n");
        return;
    }
    do
    {
       printf("\nSearch By:\n");
       printf("1.Name\n");
       printf("2.Phone Number\n");
       printf("3.Email\n");
       printf("4.Back to main menu.\n");

       printf("Enter your choice:");
       scanf("%d",&choice);
       switch(choice)
       {
        //search using name
        case 1: 
        printf("Enter Name to search:");
        scanf(" %[^\n]",search);

        printf("----------------------------------------------------------------------------------\n");
        printf("%-10s %-20s %-25s %-40s\n","Sl.No ","Name ", "Phone ", "Email                  |");
        printf("----------------------------------------------------------------------------------\n");


        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].name,search)==0)
            {
                printf("%-10d %-20s %-25s %-40s\n", i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
                printf("\n");
                found=1;
            }
        }
        printf("----------------------------------------------------------------------------------\n");
        if(!found)
        {
            printf("No contact found searching by this name:%s\n",search);
        }
        return;
        
        
        case 2://search using number
        printf("Enter Phone number to search: ");
        scanf(" %[^\n]",search);

        printf("----------------------------------------------------------------------------------\n");
        printf("%-10s %-20s %-25s %-40s\n","Sl.No ","Name ", "Phone ", "Email                  |");
        printf("----------------------------------------------------------------------------------\n");
         for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].phone,search)==0)
            {
                printf("%-10d %-20s %-25s %-40s\n", i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
                printf("\n");
                found=1;
            }
        }
        printf("----------------------------------------------------------------------------------\n");
        if(!found)
        {
            printf("No contact found searching by this number:%s\n",search);
        }
        return;
        //search by email
        case 3:
        printf("Enter Email to search:");
        scanf(" %[^\n]",search);

        printf("----------------------------------------------------------------------------------\n");
        printf("%-10s %-20s %-25s %-40s\n","Sl.No ","Name ", "Phone ", "Email                  |");
        printf("----------------------------------------------------------------------------------\n");
        
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(addressBook->contacts[i].email,search)==0)
            {
                printf("%-10d %-20s %-25s %-40s\n", i+1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
                printf("\n");
                found=1;
            }
        }
        printf("----------------------------------------------------------------------------------\n");
        if(!found)
        {
            printf("No contact found searching by this name:%s\n",search);
        }
        return;
        
        case 4:printf("\n");;break;
        default:printf("Invalid choice. Please try again.\n");
       }
    } while(choice!=4);
}   
          
        

void editContact(AddressBook *addressBook)
{
	char search[50];
    int found=0,choice;
    if(addressBook->contactCount==0) 
    {
        printf("No contacts to edit.\n");
        return;
    }
    do
    {
       printf("\nEdit By:\n");
       printf("1.Name\n");
       printf("2.Phone Number\n");
       printf("3.Email\n");
       printf("4.Back to main menu.\n");

       printf("Enter your choice:");
       scanf("%d",&choice);
            
       switch (choice) 
       {
        //edit by name
        case 1:
           printf("Enter Name to edit: ");
           scanf(" %[^\n]",search);
           found=0;
           int attempts=0,maxAttempts=3;

          for(int i=0;i<addressBook->contactCount;i++)
          {
             if(strcmp(addressBook->contacts[i].name,search)==0)
               {
                   found=1;
                   printf("\n*******************Contact found*******************\n");
            printf("---------------------------------------------------------------\n");
            printf("%-10s %-20s %-25s %-40s\n","No.","Name","Phone","Email");
            printf("---------------------------------------------------------------\n");
            printf("%-10d %-20s %-25s %-40s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

            while(attempts<maxAttempts)
            {
                int valid=1,len,j;
                attempts++;
                printf("Enter new name (Attempt %d of %d):",attempts,maxAttempts);
                scanf(" %[^\n]",addressBook->contacts[i].name);

                len=strlen(addressBook->contacts[i].name);

                if(len<3)
                {
                    printf("Invalid: Name must be at least 3 characters long.\n");
                    valid=0;
                }
                else if(!isupper(addressBook->contacts[i].name[0]))
                {
                    printf("Invalid: First letter must be uppercase.\n");
                    valid=0;
                }
                else
                {
                    for(j=0;j<len;j++)
                    {
                        if(!isalpha(addressBook->contacts[i].name[j])&&addressBook->contacts[i].name[j]!=' ')
                         {
                            printf("Invalid: Only alphabets and spaces are allowed.\n");
                            valid=0;
                            break;
                         }
                        if(addressBook->contacts[i].name[j] == ' '&&addressBook->contacts[i].name[j + 1] == ' ')
                        {
                            printf("Invalid: Multiple spaces are not allowed.\n");
                            valid=0;
                            break;
                        }
                    }
                }
                if(valid)
                {
                    printf("Valid name entered: %s\n", addressBook->contacts[i].name);
                    printf("Contact updated successfully.\n");
                    break;
                }

                if(attempts==maxAttempts)
                {
                    printf("Too many invalid attempts. Name not updated.\n");
                }
            }
            break;
        }
    }

    if (!found)
    {
        printf("No contact found with name:%s\n",search);
    }
    return;
    
      case 2:
      printf("Enter number to edit:");
      scanf(" %[^\n]",search);
      found=0;

     for(int i=0;i<addressBook->contactCount;i++) 
     {
        if(strcmp(addressBook->contacts[i].phone,search)==0)
        {
            found=1;
            printf("\n*******************Contact found*******************\n");
            printf("---------------------------------------------------------------\n");
            printf("%-10s %-20s %-25s %-40s\n","No.","Name","Phone","Email");
            printf("---------------------------------------------------------------\n");
            printf("%-10d %-20s %-25s %-40s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

        int k; 
     attempts=0;maxAttempts=3;

     while(attempts<maxAttempts)
     {
        int duplicate=0;
        attempts++;
        printf("Enter the Phone Number (Attempt %d of %d):",attempts,maxAttempts);
        scanf(" %19[^\n]",addressBook->contacts[i].phone);

        if(strlen(addressBook->contacts[i].phone)!=10) 
        {
            printf("Phone Number must be exactly 10 digits!\n");
            continue;
        }

        for(k=0;k<10;k++) 
        {
            if(!isdigit(addressBook->contacts[i].phone[k])) 
            {
                printf("Phone Number must contain only digits!\n");
                break;
            }
        }
        if(k!=10)continue;

        for(k=0;k<addressBook->contactCount;k++) 
        {
            if(k==i)continue;
            if (strcmp(addressBook->contacts[k].phone,addressBook->contacts[i].phone)==0) 
            {
                printf("This phone number already exists!\n");
                duplicate=1;
                break;
            }
        }
        if(duplicate)continue;

        printf("Phone Number accepted: %s\n",addressBook->contacts[i].phone);
        printf("Contact updated successfully.\n");
        break;
    }
     if(attempts==maxAttempts)
        {
        printf("Maximum attempts reached. Could not enter a valid phone number.\n");
        return;
        }
    }
     if (!found)
    {
        printf("No contact found with number: %s\n", search);
    }
    return;
}

      //edit by Email
      case 3:
      printf("Enter email to edit: ");
      scanf(" %[^\n]", search);
      found=0;
      
      for(int i=0;i<addressBook->contactCount;i++)
      {
    if(strcmp(addressBook->contacts[i].email,search)==0)
    {
        found=1;
        printf("\n*******************Contact found*******************\n");
            printf("---------------------------------------------------------------\n");
            printf("%-10s %-20s %-25s %-40s\n","No.","Name","Phone","Email");
            printf("---------------------------------------------------------------\n");
            printf("%-10d %-20s %-25s %-40s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

        char email[50];
        int attempts=0,maxAttempts=3;
        while(attempts<maxAttempts)
        {
            int valid=1,Count=0;
            attempts++;

            printf("Enter the new Email (Attempt %d of %d):",attempts,maxAttempts);
            scanf(" %[^\n]",email);

            if(strcmp(search,email)==0)
            {
                printf("This email is the same as the old one. Please enter a different email.\n");
                continue;
            }

            for(int j=0;email[j]!='\0';j++)
            {
                if(isupper(email[j]))
                {
                    printf("Error: Email must be lowercase only.\n");
                    valid=0;
                    break;
                }
            }
            if(!valid)continue;

            for(int j=0;email[j]!='\0';j++)
            {
                if(email[j]=='@')Count++;
            }
            if(Count!=1)
            {
                printf("Error: Email must contain exactly one '@'.\n");
                continue;
            }

            int len=strlen(email);
            if(len<5||strcmp(&email[len-4],".com")!=0)
            {
                printf("Error: Email must end with '.com'.\n");
                continue;
            }

            for(int j=0;email[j]!='\0';j++)
            {
                if(!(islower(email[j])||isdigit(email[j])||email[j]=='@'||email[j]=='.'||email[j]=='_'||email[j]=='-'))
                {
                    printf("Error: Invalid character '%c'. Allowed: letters, digits, @ . _ -\n",email[j]);
                    valid=0;
                    break;
                }
            }
            if(!valid)continue;

            int duplicate=0;
            for(int k=0;k<addressBook->contactCount;k++)
            {
                if(k==i) continue;
                if(strcmp(addressBook->contacts[k].email,email)==0)
                {
                    printf("This email already exists! Please enter a different email.\n");
                    duplicate=1;
                    break;
                }
            }
            if(duplicate)continue;

            strcpy(addressBook->contacts[i].email, email);
            printf("Contact updated successfully.\n");
            break;
        }

        if(attempts==maxAttempts)
        {
            printf("Maximum attempts reached. Could not update email.\n");
        }

        break;
    }
}

if(!found)
{
    printf("No contact found with Email: %s\n",search);
}
return;


        case 4:printf("\n");break;
        default:printf("Invalid choice. Please try again.\n");

    }
    }while(choice!=4);
    
}

	
  void deleteContact(AddressBook *addressBook) 
{
    /* Define the logic for deletecontact */
    if (addressBook->contactCount == 0) {
        printf("\nNo contacts to delete.\n");
        return;
    }

    while (1) {
        printf("\n#*#*#*#*#*#*#*Delete by*#*#*#*#*#*#\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");

        int choice;
        printf("Enter choice: ");
        scanf("%d", &choice);

        char search[100];
        int foundIndex = -1;

        if (choice == 4) {
            printf("Delete cancelled.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].name, search) == 0) {
                        foundIndex = i;
                        break;
                    }
                }
                break;

            case 2:
                printf("Enter phone: ");
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].phone, search) == 0) {
                        foundIndex = i;
                        break;
                    }
                }
                break;

            case 3:
                printf("Enter email: ");
                scanf(" %[^\n]", search);
                for (int i = 0; i < addressBook->contactCount; i++) {
                    if (strcmp(addressBook->contacts[i].email, search) == 0) {
                        foundIndex = i;
                        break;
                    }
                }
                break;

            default:
                printf("Invalid choice. Try again.\n");
                continue;
        }

        if (foundIndex != -1) {
            // Shift contacts left to overwrite deleted contact
            for (int i = foundIndex; i < addressBook->contactCount - 1; i++) {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }
            addressBook->contactCount--;

            printf("Contact deleted successfully!\n");
        } else {
            printf("No matching contact found.\n");
        }
    }
}
 
   
   


