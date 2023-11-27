#include "main.h"
status save_address_book(Address_book *add_book)
{
    char option;
    menu_header("SAVE CONTACTS:\n");
    add_book->fptr=fopen(SAVE_FILE,"r");
    if(add_book->fptr==NULL)
    {
	printf("FILE OPEN ERROR\n");
	return e_FAILURE;
    }
    FILE *fun_ptr = fopen(BACKUP_FILE,"w+");
    if(fun_ptr==NULL)
    {
	printf("FILE OPEN ERROR\n");
	return e_FAILURE;
    }
    printf("Enter y to save the contacts :");
    scanf(" %c",&option);
    if(option=='y')
    {
	rewind(add_book->fptr);
	char ch;
	ch=fgetc(add_book->fptr);
	while(ch!=EOF)
	{
	    putc(ch,fun_ptr);
	    ch=fgetc(add_book->fptr);
	}
	fclose(add_book->fptr);
	fclose(fun_ptr);
	printf("Every Contact will be stored in save.txt file\n");
    }
    else
	printf("Contact will not stored\n");

    return e_SUCCESS;
}
