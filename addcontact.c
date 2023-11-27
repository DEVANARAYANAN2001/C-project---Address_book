#include "main.h"

status addcontact(Address_book *add_book)
{
    int i=0,j=0,i1=0,j1=0;
    int option,f1=1,f2=1,flag1=0,flag2=0,flag3=0;
    char ch;
    add_book->save_phone_num_count=i;
    add_book->save_email_id_count=j;
    add_book->name="";
    for(int k=0;k<PHONE_NUM_COUNT;k++)
    {
	add_book->phone_no[k]="";
	add_book->email_id[k]="";
    }
    do
    {
	contact_menu(add_book,i1,j1);           //function call for menu dispaly
	scanf("%d",&option);
	switch(option)
	{
	    case 0:
		break;
	    case 1:
		flag3=1;
		printf("Enter the name : ");
		add_book->name=malloc(NAME_LEN*sizeof(char));      //dynamic memory allocaion for names 
		scanf(" %[^\n]",add_book->name);                     //rea the name from the user
		break;
	    case 2:
		flag3=1;
		printf("Enter the phone number : ");
		printf("Please enter the same option for alter phone number (max number  %d): ",PHONE_NUM_COUNT-add_book->save_phone_num_count);
		if(f1)
		{
		    for(int k=0;k<PHONE_NUM_COUNT;k++)
			add_book->phone_no[k]=malloc(PHONE_NUM_LEN*sizeof(char));            //memory allocation for phone number
		    f1=0;
		}
		char ph_no[20];
		scanf(" %[^\n]",ph_no);                                               //to reading the phone number 
		if(  ph_no[0]=='0' && strlen(ph_no)==PHONE_NUM_LEN )
		{
		    i1=i++;
		    strcpy(add_book->phone_no[i1],ph_no);                           //to storing the structure member
		    add_book->save_phone_num_count=i;
		}
		else
		{
		    i1=i;
		    strcpy(add_book->phone_no[i1],"invalid number");
		}
		if(i==PHONE_NUM_COUNT-1)
		    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MAXIMUM COUNT OF PHONE NUMBER IS REACHED \n");
		break;
	    case 3:
		flag3=1;
		printf("Enter the mail_id : ");
		printf("Please enter the same option for alter email_id (max email_id  %d): ",EMAIL_ID_COUNT-add_book->save_email_id_count);
		if(f2)
		{
		    for(int k=0;k<EMAIL_ID_COUNT;k++)
			add_book->email_id[k]=malloc(EMAIL_ID_LEN*sizeof(char));        //memory allocation for the email_id 
		    f2=0;
		}
		char mail_id[30];
		scanf(" %[^\n]",mail_id);                               //to read the email_id from the user
		char *var=strstr(mail_id,"@gmail.com");
		if(var!=NULL)
		{
		    j1=j++;
		    strcpy(add_book->email_id[j1],mail_id);                 //to store the email_id to the structure member
		    add_book->save_email_id_count=j;
		}
		else
		{
		    j1=j;
		    strcpy(add_book->email_id[j1],"invalid email_id");
		}
		if(j==EMAIL_ID_COUNT-1)
		    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MAXIMUM COUNT OF EMAIL-ID REACHED \n");

		break;
	    default:
		printf("enter the correct option \n");
		break;
	}
    }while(option!=0);

    if(flag3)
    {

	if(strcmp(add_book->phone_no[i1],"invalid number")==0)
	{
	    strcpy(add_book->phone_no[i1],"");
	}
	if(strcmp(add_book->email_id[j1],"invalid email_id")==0)
	{
	    strcpy(add_book->email_id[j1],"");
	}

	if(add_book->name!=NULL)
	{
	    add_book->s_no+=1;
	    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>%d\n",add_book->s_no);
	    add_book->fptr=fopen(SAVE_FILE,"a+");          //to open the file appending mode
	    if(add_book->fptr==NULL)
	    {
		printf("FILE OPEN ERROR\n");
		return e_FAILURE;                          //if file is not opened return Filaure
	    }
	    else
	    {
		save_list(add_book);                    //function call for to save the name and the phone number and the email_id to file
	    }
	    return e_SUCCESS;
	}
    }
}

status save_list(Address_book *add_book)
{
    fprintf(add_book->fptr, "%s,",add_book->name);                   //to store the name to file form the structure
    for(int i=0;i<PHONE_NUM_COUNT;i++)
    {
	fprintf(add_book->fptr, "%s,",add_book->phone_no[i]);            //to storing the phone number from the structure to file
    }
    for(int j=0;j<EMAIL_ID_COUNT;j++)
    {
	fprintf(add_book->fptr, "%s,",add_book->email_id[j]);               //to storing the email_id form the structure to file
    }
    fprintf(add_book->fptr,",,,,,,\n");
    add_book->name="";
    for(int k=0;k<PHONE_NUM_COUNT;k++)
    {
	add_book->phone_no[k]="";
	add_book->email_id[k]="";
    }

    fclose(add_book->fptr);
    add_book->fptr=fopen(SAVE_FILE,"r+");
    rewind(add_book->fptr);
    fprintf(add_book->fptr,"%d",add_book->s_no);
    fseek(add_book->fptr,0l,SEEK_END);
    fclose(add_book->fptr);

}


void contact_menu(Address_book *add_book,int i1,int j1)
{
    menu_header("ADD CONTACT\n");
    printf("0 . BACK       : \n");
    printf("1 . NAME       : %s\n",add_book->name);
    printf("2 . PHONE_NO %d : %s\n",i1+1,add_book->phone_no[i1]);
    printf("3 . EMAIL_ID %d : %s\n",j1+1,add_book->email_id[j1]);
    printf("\n");
    printf("*********************** pleasei select the option : ");
}
