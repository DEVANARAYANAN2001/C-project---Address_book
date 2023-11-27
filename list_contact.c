#include "main.h"
status list_contact(Address_book *add_book)
{
    add_book->fptr=fopen(SAVE_FILE,"r");
    if(add_book->fptr==NULL)
    {
	printf("file open error\n");
	return e_FAILURE;
    }
    else
    {
	fseek(add_book->fptr,2l,SEEK_SET);
	int m=0,l=0,flag=1,count=0,ch;
	char *token,*var,str[400];
	do
	{
	    menu_header("LIST CONTACT:\n");
	    while(fgets(str,sizeof(str),add_book->fptr))
	    {
		++count;
		add_book->name=malloc(NAME_LEN*sizeof(char));
		for(int k=0;k<PHONE_NUM_COUNT;k++)
		    add_book->phone_no[k]=malloc(PHONE_NUM_LEN*sizeof(char));
		for(int k=0;k<EMAIL_ID_COUNT;k++)
		    add_book->email_id[k]=malloc(EMAIL_ID_LEN*sizeof(char));
		strcpy(add_book->name,"");
		for(int k=0;k<PHONE_NUM_COUNT;k++)
		{
		    strcpy(add_book->phone_no[k],"");
		    strcpy(add_book->email_id[k],"");
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
		m=0;
		l=0;
		int a=0;
		printf(" %d	%s	           %s 	    %s\n",count,add_book->name,add_book->phone_no[a],add_book->email_id[a]);
		for(int i=1;i<PHONE_NUM_COUNT;i++)
		{
		    printf("                            %s",add_book->phone_no[i]);
		    printf("	 	     %s",add_book->email_id[i]);
		    printf("\n");
		}
		printf("----------------------------------------------------------------------------\n");
		strcpy(add_book->name,"");
		for(int k=0;k<PHONE_NUM_COUNT;k++)
		{
		    strcpy(add_book->phone_no[k],"");
		    strcpy(add_book->email_id[k],"");
		}
	    }
	    printf("enter to 0 for Go back : ");
	    scanf("%d",&ch);
	}while(ch!=0);
	fclose(add_book->fptr);
    }
}







