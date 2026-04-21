#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{

    FILE *fptr=fopen("contact.txt","w");
    if(fptr==NULL) 
    {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if (addressBook->contacts[i].name[0] == '\0') 
        {
            continue; // it will skip empty contacts
        }
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}


void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr=fopen("contact.txt","r");
    if(fptr==NULL) 
    {
        printf("No existing file found. Starting fresh.\n");
        addressBook->contactCount = 0;
        return;
    }
    addressBook->contactCount = 0; // start fresh
    while (fscanf(fptr,"%[^,],%[^,],%s\n",addressBook->contacts[addressBook->contactCount].name, addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email) == 3) 
    {
        addressBook->contactCount++;
    }
    fclose(fptr);
}