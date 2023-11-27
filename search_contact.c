#include "main.h"
static int flag=1;
status search_contact(Address_book *add_book)
{
    int option,s_no;
    char name[30],email[30],phone_no[11],ch;
    add_book->fptr=fopen(SAVE_FILE,"r+");
    if(add_book->fptr==NULL)
    {
	printf("file open error\n");
	return e_FAILURE;
    }
    do
    {
	menu_header("SEARCH CONTACT:\n0. EXIT\n1. S_NO\n2. NAME\n3. PHONE_NUMBER\n4. EMAIL_ID\n");
	printf("Enter your option : ");
	scanf("%d",&option);
	switch(option)
	{
	    case 1:
		do
		{
	            menu_header("SEARCH CONTACT:\n0. EXIT\n1. S_NO\n2. NAME\n3. PHONE_NUMBER\n4. EMAIL_ID\n");
		    printf("enter the s_ number :");
		    scanf(" %d",&s_no);
		    flag=1;
		    if(search_s_no_contact(add_book,s_no,flag)==e_FAILURE)
			printf("the serial number %d is not present \n",s_no);
		    printf("enter the q to cancel :");
		    scanf(" %c",&ch);
		}while(ch!='q');
		break;
	    case 2:
		printf("Enter the searching name : ");
		scanf(" %[^\n]",name);
		flag=1;
		search_name_email_phone_no_contact(add_book,name,flag);
		break;
	    case 3:
		printf("Enter the searching phone_number : ");
		scanf(" %[^\n]",phone_no);
		flag=1;
		search_name_email_phone_no_contact(add_book,phone_no,flag);
		break;
	    case 4:
		printf("Enter the searching name : ");
		scanf(" %[^\n]",email);
		flag=1;
		search_name_email_phone_no_contact(add_book,email,flag);
		break;
	    case 0:
		break;
	    default :
		printf("enter the proper option \n");
		break;
	}
    }while(option!=0);
    fclose(add_book->fptr);
}

status search_s_no_contact(Address_book *add_book,int num,int flag)
{
    int m=0,l=0,count=0;
    char *token,*var,str[400];
    fseek(add_book->fptr,2l,SEEK_SET);

	while(fgets(str,sizeof(str),add_book->fptr))
	{
	    if(++count==num)
	    {
		add_book->name=malloc(NAME_LEN*sizeof(char));
		for(int k=0;k<PHONE_NUM_COUNT;k++)
		    add_book->phone_no[k]=malloc(PHONE_NUM_LEN*sizeof(char));
		for(int k=0;k<EMAIL_ID_COUNT;k++)
		    add_book->email_id[k]=malloc(EMAIL_ID_LEN*sizeof(char));
		strcpy(add_book->name,"  ");
		for(int k=0;k<PHONE_NUM_COUNT;k++)
		{
		    strcpy(add_book->phone_no[k],"  ");
		    strcpy(add_book->email_id[k],"  ");
		}
		token = strtok (str,",\n ");
		while(token!=NULL)
		{
		    if(flag)
		    {
			printf("------------------------------------------------------------------------\n");
			printf(":S.NO	NAME			PHONE_NUMBER	EMAIL_ID		\n");
			printf("------------------------------------------------------------------------\n");
			flag=0;
		    }
		    var=strstr(token,"@gmail.com");
		    if(var==NULL&&token[0]!='0') 
			strcpy(add_book->name,token);
		    if(token[0]=='0') 
			strcpy(add_book->phone_no[m++],token);
		    if(var!=NULL)   
			strcpy(add_book->email_id[l++],token);
		    token=strtok(NULL,",\n");
		}		    
		int a=0;
		printf(" %d	%s              %s             %s\n",num,add_book->name,add_book->phone_no[a],add_book->email_id[a]);
		for(int i=1;i<PHONE_NUM_COUNT;i++)
		{
		    printf("                              %s              %s     \n",add_book->phone_no[i],add_book->email_id[i]);
		}
		printf("----------------------------------------------------------------------------\n");

	    return e_SUCCESS;
	}
    }
	return e_FAILURE;
}

status search_name_email_phone_no_contact(Address_book *add_book,char *str,int flag)
{
    char *token,ch;
    char ptr[400];
    int count=0;
    fseek(add_book->fptr,2l,SEEK_SET);
    do
    {
	while(fgets(ptr,sizeof(ptr),add_book->fptr))
	{
	    int flag1=1;
	    ++count;
	    token = strtok (ptr,",\n ");
	    while(token!=NULL)
	    {
		if(!strcmp(token,str))
		{
		    if(flag1)
		    {
			flag1=0;
			search_s_no_contact(add_book,count,flag);
			flag=0;
		    }
		}
		token=strtok(NULL,",\n");
	    }	
	}
	printf("enter the q to Go back :");
	scanf(" %c",&ch);
    }while(ch!='q');

}
