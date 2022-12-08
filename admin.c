#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"STD_types.h"
#include"admin.h"
#include"client.h"
node*ptr;
node*first=NULL;
node*last=NULL;
u32 global_pw=2000;
u32 Global_id=999999999;
u32 Global_Admin_user_name=2022;
u32 Global_Admin_password=1234;
/*-function (creat_dummy_account) used to take no arguments (used by admin mode only)
	- creating an empty node to avoid looping on empty list and to be  easy creat a node to be added at the last of the list
*/
void creat_dummy_account(void){
	node*ptr_dummy=(node*)malloc(sizeof(node));
	ptr_dummy->next=NULL;
	ptr_dummy->pre=NULL;
	first=ptr_dummy;
	last=ptr_dummy;
	
}
/*-function (creat_new_account) used to take no arguments (used by admin mode only)
	- creating a node to be added at the last of the Linked list 
	-asking the user to enter his details like name,address,age ...etc with checking the constraint of each input 
	-you will find constraint in the attached PDF file associated with the project 
	- if the input wasn't correct the user will stuck in a loop untill he put the correct input
	- if  inputs are passed the inout will be added to the created node 
*/
void creat_new_account(void){
	
	node*ptr_new=(node*)malloc(sizeof(node));
	ptr_new->pre=last;
	ptr_new->next=NULL;
	last->next=ptr_new;
	last=ptr_new;
	u8 count=0;
	do{
		count=0;
	printf("please enter your full name 'at least first four names' seperated by space:");
	scanf(" %[^\n]",ptr_new->name_s);
	fflush(stdin);
	
	for(u32 i=0;i<strlen(ptr_new->name_s);i++)
	{
			if((ptr_new->name_s[i]==' ')&&((ptr_new->name_s[i+1]!=' ')&&(ptr_new->name_s[i+1]!='\0')))
			{
				count++;
			}
	}
	if(count>=3)
		break;
	}while(1);
	printf("please enter your Full Address:");
	scanf(" %[^\n]",ptr_new->address_s);
	fflush(stdin);
	do{
	printf("please enter your National ID'at least 14 digits'");
	scanf("%lld",&ptr_new->national_ID_s);
	fflush(stdin);
	
	}while((ptr_new->national_ID_s)<9999999999999||(ptr_new->national_ID_s)>99999999999999);
	
	do{
	printf("please enter your age");
	setbuf(stdout, NULL);
	scanf("%u",(u32*)&(ptr_new->age_s));
	fflush(stdin);
	}while(!((ptr_new->age_s>=5)&&(ptr_new->age_s<=100)));
		if(ptr_new->age_s<21)
	{
		printf("please enter your guardian name");
		scanf(" %[^\n]",ptr_new->guardian_s);
		fflush(stdin);
		do{
			printf("please enter your guardian National ID'at least 14 digits'");
			scanf("%lld",&ptr_new->guardian_ID_s);
			fflush(stdin);
			
		  }while((ptr_new->guardian_ID_s)<9999999999999||(ptr_new->guardian_ID_s)>99999999999999);
	}
	
	do{
	printf("please enter your balance");
	setbuf(stdout, NULL);
	scanf(" %ld",(u64 *)&(ptr_new->balance_s));
	fflush(stdin);
	}while(ptr_new->balance_s<=0);
	ptr_new->account_status_s=1;
	u32 new_id,new_pw;
	new_id=func_generate_ID();
	ptr_new->bank_account_ID_s=new_id;
	printf("your ID is  %d\n",new_id);
	new_pw=func_generate_pw();
	ptr_new->pw_s=new_pw;
	printf("your password is  %d\n",new_pw);
}
/*
   -function (func_generate_ID) used to take no arguments (used by admin mode only)
	-used to generate new id each time the user creat new account 
*/
u32 func_generate_ID(){
	Global_id++;
}

/*
   -function (func_generate_pw) used to take no arguments (used by admin mode only)
	-used to generate new password each time the user creat new account 
*/
u32 func_generate_pw(){
	global_pw++;
}
/*
   -function (open_exisiting_account) used to take no arguments
	-used to to navigate through out the programm (used by admin mode only)
	-with options make transaction,change status,get cash,deposit or return to main menu
	- according to the choices made the function will call the desired function to do the task 
*/
void open_exisiting_account(void){
	u32 choice;
	printf("to make transaction press: 1 \n ");
	printf("to change status press: 2 \n ");
	printf("to get cash press: 3 \n ");
	printf("to deposit  press: 4 \n ");
	printf("to return to main menu press: 5 \n ");
	scanf("  %d",&choice);	
	fflush(stdin);
	switch(choice)
	{
		case 1:
		{ u32 id1,id2,amount;
			printf("please enter the account id to transfer from");
			scanf(" %d",&id1);
			fflush(stdin);
			printf("please enter the account id to transfer to");
			scanf(" %d",&id2);
			fflush(stdin);
			printf("please enter the amount to  be transfered");
			scanf(" %d",&amount);
			fflush(stdin);
		make_transaction(id1,id2,amount);
		}
		break;
		case 2:
		{
			u32 id; 
			printf("please enter the account id to change the statues");
			scanf(" %d",&id);
			fflush(stdin);
			Change_Account_Status(id);
		}
		break;
		case 3:
		{	u32 id4,amount1; 
			printf("please enter the account id to get cash ");
			scanf(" %d",&id4);
			fflush(stdin);
			printf("please enter the amount to get");
			scanf(" %d",&amount1);
			fflush(stdin);
			Get_cash(id4,amount1);
		}
		break;
		case 4:
		{
			u32 id5,amount2; 
			printf("please enter the account id to deposit cash ");
			scanf(" %d",&id5);
			printf("please enter the amount to deposit");
			scanf(" %d",&amount2);			
			Deposit_in_Account(id5,amount2);
		}
		break;
		case 5:
				return;
		break;
		default:
		printf("wrong choice\n");
		break;
		
	}
}
/*
   -function (Change_Account_Status) used to take 1 argument (the account id to change its status)
	-(used by admin mode only)
	-looping on the Linked List to check if the id account exits or no 
	- if exists the user will be asked to choose the status of the account (active, restricted or closed)
*/
void Change_Account_Status(u32 bank_account_ID){
	u32 choice;
	printf("please enter the bank account statues 1 for active 2 for restricted 3 for closed ");
	scanf(" %d",&choice);
	fflush(stdin);
    switch(choice)
	{
		case 1:
			ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->bank_account_ID_s==bank_account_ID)
				{
					ptr->account_status_s=1;
				}
				ptr=ptr->next;			
			}
		break;
		case 2:
			ptr=first;
			while(ptr!=NULL)
				{
					if( ptr->bank_account_ID_s==bank_account_ID)
					{
						ptr->account_status_s=2;
					}
				ptr=ptr->next;					
				}
		break;
		case 3:
			ptr=first;
			while(ptr!=NULL)
				{
					if( ptr->bank_account_ID_s==bank_account_ID)
					{
						ptr->account_status_s=3;
					}	
					ptr=ptr->next;					
				}
		break;
		default:
		printf("wrong choice \n");
		break;
	}
}
/*-function (admin_mode) used to take 1 argument to check about exit state of the whole programm 
	- printing a list of choice to navigate through out the programm with the all valid option of the admin 
	-checking for id and pw and the admin to be able to acces admin mode (ID: 2022 and password: 1234)
	-according of the admin choices the desired functions will be called
	-
*/
void admin_mode(u8 *ext){
	u32 user,pw,choice;
	printf("please enter the user name of admin :");
	scanf(" %d",&user);
	fflush(stdin);
	printf("please enter the password for admin :");
	scanf(" %d",&pw);
	fflush(stdin);
	if(user==Global_Admin_user_name &&pw==Global_Admin_password)
	{
		printf("          welcome our admin\n");
		printf("please select from the below menu\n");
		printf("1:creat new account\n");
		printf("2:open existing account\n");
		printf("3:Exit system \n");
		scanf(" %d",&choice);
		switch(choice)
		{
			case 1:
			creat_new_account();
			break;
			case 2:
			open_exisiting_account();
			break;
			case 3:
			*ext=1;
			break;
			default:
			printf("wrong choice\n");
			break;
		}
	}else{
		printf("incorrect user name or pw for admin\n");
	}
}