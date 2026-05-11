#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"




void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
     int n = addressBook->contactCount;
     Contact temp;

     // printing contact details by normal method
    if (sortCriteria == 4) 
    {
        printf("%-30s %-15s %-30s\n",  "Name", "Phone", "Email");

        for (int i = 0; i < n; i++) 
        {
           printf("%-30s %-15s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

        }
        return;
    }

    // sorting contact details by name /by phone no/ by email using bubble sort method
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            int cmp = 0;
            
            if (sortCriteria == 1)
            {
                cmp = strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
            }
           
            else if (sortCriteria == 2)
            {
                cmp = strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
            }
          
            else if (sortCriteria == 3)
            {
                cmp = strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            
         // swap 
            if (cmp > 0) 
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("%-30s %-15s %-30s\n", "Name", "Phone", "Email");

    for (int i = 0; i < n; i++) 
    {
        printf("%-30s %-15s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

    }
}
        
    

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
  //  populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char tname[50];
    char tphone[11];
    char temail[20];
    int n = addressBook->contactCount;    

    printf("Enter the name: \n");
    scanf(" %[^\n]", tname);

    // validate user entered name
    int ret_n = validate_name(tname, addressBook);
    if(ret_n == 0)
    {
        printf("Invalid name\n");
        return;
    }


    printf("Enter the phone no. : \n");
    scanf(" %[^\n]", tphone);

    // validate user entered phone no.
    int ret_p = validate_phone(tphone, addressBook);
    if(ret_p == 0)
    {
        printf("Invalid phone no. \n");
        return;
    }
    
    printf("Enter the email : \n");
    scanf(" %[^\n]", temail);

    // validate user entered email
    int ret_e = validate_email(temail, addressBook);
    if(ret_e == 0)
    {
        printf("Invalid email\n");
        return;
    }

    // copy / store the user entered name in the addressbook
    strcpy(addressBook->contacts[n].name, tname);
    strcpy(addressBook->contacts[n].phone, tphone);
    strcpy(addressBook->contacts[n].email, temail);
    // increase the count of contacts present in the addressbook
    addressBook->contactCount++;


    // print created contact details
    printf("%-30s %-15s %-30s\n", "Name", "Phone", "Email");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-30s %-15s %-30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

    }

    
}


int searchContact(AddressBook *addressBook) 
{
    int n = addressBook->contactCount;
    printf("Contact Searching Menu: \n");
    printf("1. Search by name: \n");
    printf("2. Search by phone: \n");
    printf("3. Search by email: \n");

    //select the choice to search by name / by phone no. / by email
    int schoice;
    printf("Enter your searching choice: \n");
    scanf(" %d", &schoice);

    char name[20];
    char phone[20];
    char email[20];

    int found;
    switch(schoice)
    {
        case 1: 
        {

            printf("Enter the name to search: \n");
            scanf(" %[^\n]", name);
              found = 0;
      
            //check if user entered name is present in the addressbook or not
            for(int i = 0; i < n; i++)
            {
                if(strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    if(found == 0)
                    {
                        printf("%-10s %-30s %-15s %-30s\n","Index","Name","Phone","Email");
                    }

                    printf("%-10d %-30s %-15s %-30s\n", i,addressBook->contacts[i].name,  addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
                
            }
            if(found == 0)
            {
                printf("This name is not found\n");
            }
            break;   
        }

        case 2: 
        {

            printf("Enter the phone number to search: \n");
            scanf(" %[^\n]", phone);

            found = 0;
            
            //check if user entered phone no. is present in the addressbook or not
            for(int i = 0; i < n; i++)
            {
                if(strcasecmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    if(found == 0)
                    {
                          printf("%-10s %-30s %-15s %-30s\n","Index","Name","Phone","Email");
                    }
                    printf("%-10d %-30s %-15s %-30s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if(found == 0)
            {
                printf("This phone number is not found\n");
            }
            break;   
        }

        case 3: 
        {
            printf("Enter the email to search: \n");
            scanf(" %[^\n]", email);
             found = 0;
            
            //check if user entered email is present in the addressbook or not
            for(int i = 0; i < n; i++)
            {
                if(strcasecmp(addressBook->contacts[i].email, email) == 0)
                {
                    if(found == 0)
                    {
                       printf("%-10s %-30s %-15s %-30s\n", "Index", "Name", "Phone", "Email");
                    }
                    printf("%-10d %-30s %-15s %-30s\n", i, addressBook->contacts[i].name, addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    found = 1;
                }
            }
            if(found == 0)
            {
                printf("This email is not found\n");  
            }
            break;   
        }

        default: 
        {
            printf("Invalid selection\n");
            break;
        }
    }
    if(found == 0)
    {
        return 0;   // contact is not found
    }
    else
    {
        return 1;    // contact is found
    }
}




void editContact(AddressBook *addressBook)
{

    /* Define the logic for Editcontact */
    printf("\nEnter the name / phone no. / email id you want to search :\n");

    // search contact to edit
    int ret = searchContact(addressBook);
    if(ret == 0)
    {
        return;   // searched contact not found
    }
    
    else
    {
      // searhced contact found. if multiple matches found then edit by accessing contact index
        int index;
        printf("Enter the contact index you want to edit: \n");
        scanf("%d", &index);

        printf("Edit Menu \n");
        printf("1. Edit name\n");
        printf("2. Edit phone\n");
        printf("3. Edit email\n");

        int choice;
        printf("Please enter what you want to edit: \n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                char name[20];
                printf("Enter new name: ");
                scanf(" %[^\n]", name);
    
            // check if user entered name is valid or not
            int ret_n = validate_name(name, addressBook);
            if(ret_n == 0)
            {
                printf("Invalid name\n");
               return;
            }
            strcpy(addressBook->contacts[index].name, name); // edit the name and store it in addressbook
            printf("Contact Edited.\n");
                break;
            }
            
            case 2:
            {
                char phone[20];
                printf("Enter new phone no.: ");
                scanf(" %[^\n]", phone);

                // check if user entered phone is valid or not
                int ret_p = validate_phone(phone, addressBook);
                if(ret_p == 0)
                { 
                    printf("Invalid phone no.\n");
                    return;
                }
                strcpy(addressBook->contacts[index].phone, phone);    // edit the phone no. and store it in addressbook
                printf("Contact Edited.\n");
                break;
                }

            case 3:
            {
                char email[20];
                printf("Enter new email: ");
                scanf(" %[^\n]", email);

                // check if user entered email is valid or not
                int ret_e = validate_email(email, addressBook);
                if(ret_e == 0)
                {
                    printf("Invalid email id\n");
                    return;
                }
                strcpy(addressBook->contacts[index].email, email);  // edit the email and store it in addressbook
                printf("Contact Edited.\n");
                break;
            }
            default:
            {
                printf("Invalid choice\n");
            }
        }
 
        // print edited contact
        printf("\nEdited Contact:\n");

        printf("%-10s %-30s %-15s %-30s\n", "Index", "Name", "Phone", "Email");

        printf("%-10d %-30s %-15s %-30s\n", index, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
    
    }
}

   

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

    printf("\nEnter the name / phone no. / email id you want to delete :\n");

    // search the contact to delete
    int ret = searchContact(addressBook);
    if(ret == 0)
    {
        return;     // searched contact is not found
    }
    
    else
    {
        // searched contact found. If multiple matches found delete by user entered index
        int index;
        printf("Enter the contact index you want to delete: \n");
        scanf("%d", &index);


        // shift the contact you want to delete to the last
         for(int i = index; i < addressBook->contactCount - 1; i++)
         {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
         }
        // decrement the contactcount of addressbook
         addressBook->contactCount = addressBook->contactCount - 1;
         printf("Contact deleted\n");
    }
     
}
