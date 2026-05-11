#include <stdio.h>
#include "file.h"


void saveContactsToFile(AddressBook *addressBook) 
{
   FILE* fptr = fopen("contacts.csv", "w");
   if(fptr == NULL)
   {
        printf("File opening failed\n");
          return;
   }
   // print Total number of contacts to contacts.csv
   fprintf(fptr, "%d\n", addressBook->contactCount);
   
   // print each contact deatils to file (contacts.csv)
   for(int i = 0; i <  addressBook->contactCount; i++)
   {
      fprintf(fptr, "%s, %s, %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email );
   }

   fclose(fptr);
   printf("Contact saved!\n");

  
}

void loadContactsFromFile(AddressBook *addressBook)
 {
    FILE* fptr = fopen("contacts.csv", "r");
    if(fptr == NULL)
    {
        printf("File opening failed\n");
          return;
    }
   
    // read Total number of contacts from contacts.csv
    fscanf(fptr, "%d", &(addressBook->contactCount));

    // read each contact deatils from file (contacts.csv)
    for(int i = 0; i <  addressBook->contactCount; i++)
    {
       fscanf(fptr, "%[^,], %[^,], %[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email );
    }

    fclose(fptr);
    printf("Contact Loaded!\n");
}
