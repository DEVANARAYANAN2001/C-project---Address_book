#include "main.h"
int main ()
{
    Address_book add_book;
    int option,len;
    char *length;
    add_book.fptr=fopen(SAVE_FILE,"a+");
    if(add_book.fptr==NULL)
	printf("FILE OPEN FAILURE\n");
    else
    {
	fseek(add_book.fptr,0l,SEEK_END);
	len=ftell(add_book.fptr);
	if(len)
	{
	    rewind(add_book.fptr);
	    fscanf(add_book.fptr,"%s",length);
	    add_book.s_no=atoi(length);
	    fclose(add_book.fptr);
	}
	else
	{
	    add_book.s_no=0;
	    rewind(add_book.fptr);
	    fprintf(add_book.fptr,"\n\n");
	    fseek(add_book.fptr,0l,SEEK_END);
	    fclose(add_book.fptr);
	}
    }
    do
    {
	main_menu();
	scanf("%d",&option);
	switch(option)
	{
	    case 1:
		addcontact(&add_book) ;
		break;
	    case 2:
		search_contact(&add_book);
		break;
	    case 3:
		edit_contact(&add_book) ;
		break;
	    case 4:
		delete_contact(&add_book) ;
		break;
	    case 5:
		list_contact(&add_book);
		break;
	    case 6:
		save_address_book(&add_book);
		option=0;
		break;
	    case 0:
		break;
	    default :
		printf("enter the proper option \n");
		break;
	}
    }while(option!=0);

}
void menu_header(const char *str)
{
    fflush(stdout);
    system("clear");
    printf("##################### ADDRESS BOOK #####################\n");
    if(*str!='\0')
	printf("##################### %s\n",str);
}

void main_menu(void)
{
    menu_header("FEATURE:\n");
    printf("0. EXIT\n");
    printf("1. ADD CONTACT\n");
    printf("2. SEARCH CONTACT\n");
    printf("3. EDIT CONTACT\n");
    printf("4. DELETE CONTACT\n");
    printf("5. LIST CONTACT\n");
    printf("6. SAVE CONTACT\n");
    printf("\n");
    printf("Please enter the option : ");
}





