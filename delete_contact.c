#include "main.h"

void contact_menu2(Address_book *add_book,int ,int );
int flag2=1;
status delete_contact(Address_book *add_book)
{
    int option=1,s_no;
    static int num=0;
    char name[30],email[30],phone_no[11],ch;
    add_book->fptr=fopen(SAVE_FILE,"r+");
    if(add_book->fptr==NULL)
    {
	printf("file open error\n");
	return e_FAILURE;
    }
    do
    {
	menu_header("SEARCH CONTACT to DELETE:\n0. EXIT\n1. S_NO\n2. NAME\n3. PHONE_NUMBER\n4. EMAIL_ID\n");
	printf("Enter your option : ");
	scanf("%d",&option);
	switch(option)
	{
	    case 1:
		do
		{
		    printf("enter the s_ number :");
		    scanf(" %d",&s_no);
		    flag2=1;
		    search_s_no_contact(add_book,s_no,flag2);
		    printf("enter the 'q' to goback 's' Select :");
		    scanf(" %c",&ch);
		    if(ch=='s')
		    {
			sub_delete_contact(add_book);
		    }
		}while(ch!='q');

		break;
	    case 2:
		do
		{
		    printf("Enter the searching name : ");
		    scanf(" %[^\n]",name);
		    flag2=1;
		    search_name_email_phone_no_contact(add_book,name,flag2);
		    printf("enter the 'q' to goback 's' Select :");
		    scanf(" %c",&ch);
		    if(ch=='s')
		    {
			sub_delete_contact(add_book);
			break;
		    }
		}while(ch!='q');
		break;
	    case 3:
		do
		{
		    printf("Enter the searching phone_number : ");
		    scanf(" %[^\n]",phone_no);
		    flag2=1;
		    search_name_email_phone_no_contact(add_book,phone_no,flag2);
		    printf("enter the 'q' to goback 's' Select :");
		    scanf(" %c",&ch);
		    if(ch=='s')
		    {
			sub_delete_contact(add_book);
			break;
		    }
		}while(ch!='q');
		break;
	    case 4:
		do
		{
		    printf("Enter the searching name : ");
		    scanf(" %[^\n]",email);
		    flag2=1;
		    search_name_email_phone_no_contact(add_book,email,flag2);
		    printf("enter the 'q' to goback 's' Select :");
		    scanf(" %c",&ch);
		    if(ch=='s')
		    {
			sub_delete_contact(add_book);
			break;
		    }
		}while(ch!='q');
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

status sub_delete_contact(Address_book *add_book)
{
    int op,num=0,m=0,l=0,count=0,ph_count=0,email_count=0,option;
    char *token,*var,str[400],edit;
    fseek(add_book->fptr,2l,SEEK_SET);
    printf("Select the serial number (s_no) to edit : ");
    scanf(" %d",&op);
    while(fgets(str,sizeof(str),add_book->fptr))
    {
	if(++count==op)
	{
	    add_book->name=malloc(NAME_LEN*sizeof(char));
	    for(int k=0;k<=PHONE_NUM_COUNT;k++)
		add_book->phone_no[k]=malloc(PHONE_NUM_LEN*sizeof(char));
	    for(int k=0;k<=EMAIL_ID_COUNT;k++)
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
		var=strstr(token,"@gmail.com");
		if(var==NULL&&token[0]!='0') 
		    strcpy(add_book->name,token);
		if(token[0]=='0') 
		{
		    strcpy(add_book->phone_no[m++],token);
		    ph_count=m;
		}
		if(var!=NULL)  
		{ 
		    strcpy(add_book->email_id[l++],token);
		    email_count=l;
		}
		token=strtok(NULL,",\n");
	    }
	    m=0;
	    l=0;
	    for(int k=0;k<PHONE_NUM_COUNT;k++)
	    {
		if(strcmp(add_book->phone_no[k],""))
		    add_book->save_phone_num_count=++m;
		if(strcmp(add_book->email_id[k],""))
		    add_book->save_email_id_count=++l;
	    }
	    m=0;
	    l=0;
	    int i1=0,j1=0,opt;
	    menu_header("ADD CONTACT\n");
	    do
	    {
		contact_menu2(add_book,m,l);
		scanf(" %d",&option);
		switch(option)
		{
		    case 1:
			printf("enter the 's' name_edit 'n' go next :");
			scanf(" %c",&edit);
			if(edit=='s')
			{
			    rewind(add_book->fptr);
			    add_book->s_no--;
			    fprintf(add_book->fptr,"%d",add_book->s_no);
			    fseek(add_book->fptr,0l,SEEK_END);
			    do
			    {
				FILE *fp = fopen("saveing.txt","w");
				fseek(add_book->fptr,0l,SEEK_SET);
				while(fgets(str,sizeof(str),add_book->fptr))
				{
				    if(num++!=op)
				    {
					fputs(str,fp);
				    }
				}
				fclose(fp);


				remove(SAVE_FILE);
				rename("saveing.txt",SAVE_FILE);
				printf("name delete success \n");
				printf("Enter option  '0' to back : ");
				scanf("%d",&opt);

			    }while(opt!=0);
			}
			else
			    break;
			break;
		    case 2:
			printf("enter the 's' phone_number_edit (or) 'n' go next :");
			scanf(" %c",&edit);
			if(edit=='s')
			{
			    i1=m++;
			    for(int i=i1;i<add_book->save_phone_num_count-1;i++)
			    {
				strcpy(add_book->phone_no[i1],add_book->phone_no[i1+1]);
			    }
			    strcpy(add_book->phone_no[i1],"");
			    add_book->save_phone_num_count--;
			}
			else if(edit=='n')
			    m++;
			break;
		    case 3:
			printf("enter the 's' email_id_edit (or) 'n' go next :");
			scanf(" %c",&edit);
			if(edit=='s')
			{
			    j1=l++;
			    for(int i=j1;i<add_book->save_email_id_count-1;i++)
			    {
				strcpy(add_book->email_id[j1],add_book->email_id[j1+1]);
			    }
			    strcpy(add_book->email_id[j1],"");
			    add_book->save_email_id_count--;
			}
			else if(edit=='n')
			    l++;
			break;
		    case 0:
			break;
		    default:
			printf("enter the correct option \n");
			break;
		}

	    }while(option!=0);
	}
    }
}

void contact_menu2(Address_book *add_book,int m,int l)
{
    menu_header("ADD CONTACT\n");
    printf("0 . BACK       : \n");
    printf("1 . NAME       : %s\n",add_book->name);
    printf("2 . PHONE_NO %d : %s\n",m+1,add_book->phone_no[m]);
    printf("3 . EMAIL_ID %d : %s\n",l+1,add_book->email_id[l]);
    printf("\n");
    printf("*********************** pleasei select the option : ");
}


