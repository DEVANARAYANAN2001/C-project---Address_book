#ifndef MAIN_H
#define MAIN_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define e_FAILURE 0
#define e_SUCCESS 1
#define SAVE_FILE "backup.txt"
#define BACKUP_FILE "save.txt"
#define NAME_COUNT 1
#define PHONE_NUM_COUNT 5
#define EMAIL_ID_COUNT 5
#define NAME_LEN 25
#define PHONE_NUM_LEN 11
#define EMAIL_ID_LEN 30


typedef struct 
{
    char *name;
    char *phone_no[PHONE_NUM_COUNT];
    char *email_id[EMAIL_ID_COUNT];
    int s_no;
    char count;
    FILE *fptr;
    FILE *f;
    int save_phone_num_count;
    int save_email_id_count;
}Address_book;

typedef enum
{
    e_failure,
    e_success
}status; 

void main_menu(void);
void contact_menu(Address_book *add_book,int,int);
void menu_header(const char *str);
void backup(Address_book *add_book);

status addcontact(Address_book *add_book);
status list_contact(Address_book *add_book);
status search_contact(Address_book *add_book);
status edit_contact(Address_book *add_book);
status save_address_book(Address_book *add_book);
status delete_contact(Address_book *add_book);


status save_list(Address_book *add_book);
status sub_edit_contact(Address_book *add_book);
status sub_delete_contact(Address_book *add_book);
status search_s_no_contact(Address_book *add_book,int,int);
status search_name_email_phone_no_contact(Address_book *add_book,char *,int);


#endif
