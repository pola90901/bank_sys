#include<stdio.h>
#include<stdlib.h>
#include"grad.h"
typedef struct bank_account node;
struct bank_account
{
	char name_s[100];
	char address_s[100];
	int national_ID_s;
	int age_s;
	int bank_account_ID_s;
	int guardian_s;
	int guardian_ID_s;
	int account_status_s;
	int balance_s;
	int pw_s;	
	node*next;
	node*pre;	
};
node*ptr;
node*first=NULL;
node*last=NULL;
int Global_Admin_user_name=2022;
int Global_Admin_password=1234;
void creat_dummy_account(void){
	node*ptr_dummy=(node*)malloc(sizeof(node));
	ptr_dummy->next=NULL;
	ptr_dummy->pre=NULL;
	first=ptr_dummy;
	last=ptr_dummy;
	
}
void creat_new_account(void){
	
	node*ptr_new=(node*)malloc(sizeof(node));
	ptr_new->pre=last;
	ptr_new->next=NULL;
	last->next=ptr_new;
	last=ptr_new;

	printf("please enter your full name 'at least first four names':");
	scanf(" %[^\n]",ptr_new->name_s);	
	printf("please enter your Full Address:");
	scanf(" %[^\n]",ptr_new->address_s);
	printf("please enter your National ID'at least 14 digits'");
	scanf("%d",&ptr_new->national_ID_s);
	printf("please enter your age");
	scanf("%d",&ptr_new->age_s);
	if(ptr_new->age_s<21)
	{
		printf("please enter your guardian name");
		scanf(" %[^\n]",ptr_new->guardian_s);
		printf("please enter your guardian National ID'at least 14 digits'");
		scanf("%d",&ptr_new->national_ID_s);
	}
	printf("please enter your balance");
	scanf("%d",&ptr_new->balance_s);
	ptr_new->account_status_s=1;
	printf("please enter bank account ID");
	scanf("%d",&ptr_new->bank_account_ID_s);
	printf("please enter your password");
	scanf("%d",&ptr_new->pw_s);
}
void open_exisiting_account(void){
	int choice;
	printf("to make transaction press: 1 \n ");
	printf("to change status press: 2 \n ");
	printf("to get cash press: 3 \n ");
	printf("to deposit  press: 4 \n ");
	printf("to return to main menu press: 5 \n ");
	scanf("%d",&choice);	
	switch(choice)
	{
		case 1:
		{ int id1,id2,amount;
			printf("please enter the account id to transfer from");
			scanf("%d",&id1);
			printf("please enter the account id to transfer to");
			scanf("%d",&id2);
			printf("please enter the amount to  be transfered");
			scanf("%d",&amount);
		make_transaction(id1,id2,amount);
		}
		break;
		case 2:
		{
			int id; 
			printf("please enter the account id to change the statues");
			scanf("%d",&id);
			Change_Account_Status(id);
		}
		break;
		case 3:
		{	int id4,amount1; 
			printf("please enter the account id to get cash ");
			scanf("%d",&id4);
			printf("please enter the amount to get");
			scanf("%d",&amount1);
			Get_cash(id4,amount1);
		}
		break;
		case 4:
		{
			int id5,amount2; 
			printf("please enter the account id to deposit cash ");
			scanf("%d",&id5);
			printf("please enter the amount to deposit");
			scanf("%d",&amount2);			
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
void make_transaction(int bank_account_ID_trans_from,int bank_account_ID_trans_to,int amount_of_money){
	int flag1=0,flag2=0;
	ptr=first;
	while(ptr!=NULL)
	{	
			if(bank_account_ID_trans_from==ptr->bank_account_ID_s&& ptr->account_status_s==1&&ptr->balance_s>amount_of_money)
			{
				flag1=1;			
			}
			if(bank_account_ID_trans_to==ptr->bank_account_ID_s && ptr->account_status_s==1)
			{	
				flag2=1;
			}
		ptr=ptr->next;
	}
	if(flag1==1&&flag2==1)
	{	ptr=first;
		while(ptr!=NULL)
		{
			if(bank_account_ID_trans_from==ptr->bank_account_ID_s&& ptr->account_status_s==1)
			{
				printf("your balance was :%d \n",ptr->balance_s);
				ptr->balance_s-=amount_of_money;
				printf("your balance now is :%d \n",ptr->balance_s);
			}
			if(bank_account_ID_trans_to==ptr->bank_account_ID_s && ptr->account_status_s==1)
			{
				printf("your balance was :%d \n",ptr->balance_s);
				ptr->balance_s+=amount_of_money;	
				printf("your balance now is :%d \n",ptr->balance_s);
			}
		ptr=ptr->next;	
		}
	}else{printf("the entered accounts either not active or not existing\n");}
	
}	
void Change_Account_Status(int bank_account_ID){
	int choice;
	printf("please enter the bank account statues 1 for active 2 for restricted 3 for closed ");
	scanf("%d",&choice);
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
void Get_cash(int bank_account_ID,int amount_required_to_get){
	ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->bank_account_ID_s==bank_account_ID&&ptr->balance_s>amount_required_to_get&&ptr->account_status_s==1)
				{	
					printf("your balance was  :%d \n",ptr->balance_s);
					ptr->balance_s-=amount_required_to_get;
					printf("your balance now is :%d \n",ptr->balance_s);
				}
				ptr=ptr->next;			
			}
}	

void Deposit_in_Account(int bank_account_ID,int amount_required_to_put){
	
	ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->bank_account_ID_s==bank_account_ID&&ptr->account_status_s==1)
				{	
					printf("your balance was :%d \n",ptr->balance_s);
					ptr->balance_s+=amount_required_to_put;
					printf("your balance now is :%d \n",ptr->balance_s);
				}
				ptr=ptr->next;			
			}
	
	
	
}

void change_pw(int old_pw,int new_pw,int bank_account_ID){
	ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->pw_s==old_pw&&bank_account_ID==ptr->bank_account_ID_s)
				{	
					ptr->pw_s=new_pw;
				}
				ptr=ptr->next;			
			}
}

void admin_mode(int *ext){
	int user,pw,choice;
	printf("please enter the user name of admin :");
	scanf("%d",&user);
	printf("please enter the password for admin :");
	scanf("%d",&pw);
	if(user==Global_Admin_user_name &&pw==Global_Admin_password)
	{
		printf("          welcome our admin\n");
		printf("please select from the below menu\n");
		printf("1:creat new account\n");
		printf("2:open existing account\n");
		printf("3:Exit system \n");
		scanf("%d",&choice);
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
			break;
		}
	}else{
		printf("incorrect user name or pw for admin\n");
	}
}

void client_mode(void){
	
	int bank_account_ID1,pw1;
	printf("please enter the bank account ID :");
	scanf("%d",&bank_account_ID1);
	printf("please enter the password for bank account :");
	scanf("%d",&pw1);
	ptr=first;
	while(ptr!=NULL)
	{
		if (bank_account_ID1== ptr->bank_account_ID_s&&pw1==ptr->pw_s)
		{
			int choice1;
			printf("welcome our dear client\n");
			printf("please select from the below menu:\n");
			printf("1:make transaction\n");
			printf("2:change account password\n");
			printf("3:Get cash\n");
			printf("4:Deposite in the account \n");
			printf("5:return to main menu \n");
			printf("your choice :");
			scanf("%d",&choice1);
			switch(choice1)
			{
				case 1:
				{	
					int bank_ID_from, bank_ID_to, amount;
					printf("please enter the bank account ID trans from \n");
					scanf("%d",&bank_ID_from);
					printf("please enter the bank account ID trans to \n");
					scanf("%d",&bank_ID_to);
					printf("please enter the amount of money \n");
					scanf("%d",&amount);
					make_transaction(bank_ID_from, bank_ID_to, amount);
					return;
				}
				break;
				case 2:
				{	
					int new,old,id;
					printf("please enter the old password");
					scanf("%d",&old);
					printf("please enter the new password");
					scanf("%d",&new);
					printf("please enter the account bank id");
					scanf("%d",&id);
					scanf("%d",&new);
					change_pw(old,new,id);
					return;
					
				}
				break;
				case 3:
				{
					int get,id;
					printf("please enter the amount of cash needed ");
					scanf("%d",&get);
					printf("please enter the bank account id  ");
					scanf("%d",&id);
					Get_cash(id,get);	
					return;
				}
				break;
				case 4:
				{
					int dep,id;
					printf("please enter the amount of cash to deposit ");
					scanf("%d",&dep);
					printf("please enter the account bank id");
					scanf("%d",&id);
					Deposit_in_Account(id,dep);
					return;
				}
				break;
				case 5:
				return;
				break;	
				
				default:
				printf("wrong choice :)\n");
				break;
			}
		}	
		ptr=ptr->next;
	}	
}
