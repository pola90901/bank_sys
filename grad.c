#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"grad.h"
typedef struct bank_account node;
struct bank_account
{
	char name_s[100];
	char address_s[100];
	unsigned long long int national_ID_s;
	unsigned int age_s;
	unsigned int bank_account_ID_s;
	char guardian_s[100];
	long long int guardian_ID_s;
	unsigned int account_status_s;
	unsigned int balance_s;
	unsigned int pw_s;	
	node*next;
	node*pre;	
};
node*ptr;
node*first=NULL;
node*last=NULL;

int global_pw=2000;
int Global_id=999999999;

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
	char count=0;
	do{
		count=0;
	printf("please enter your full name 'at least first four names':");
	scanf(" %[^\n]",ptr_new->name_s);
	fflush(stdin);
	
	for(int i=0;i<strlen(ptr_new->name_s);i++)
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
	scanf("%u",(unsigned int*)&(ptr_new->age_s));
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
	scanf(" %ld",(long int *)&(ptr_new->balance_s));
	fflush(stdin);
	}while(ptr_new->balance_s<=0);
	ptr_new->account_status_s=1;
	int new_id,new_pw;
	new_id=func_generate_ID();
	ptr_new->bank_account_ID_s=new_id;
	printf("your ID is  %d\n",new_id);
	new_pw=func_generate_pw();
	ptr_new->pw_s=new_pw;
	printf("your password is  %d\n",new_pw);
}
int func_generate_ID(){
	Global_id++;
}
int func_generate_pw(){
	global_pw++;
}


void open_exisiting_account(void){
	int choice;
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
		{ int id1,id2,amount;
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
			int id; 
			printf("please enter the account id to change the statues");
			scanf(" %d",&id);
			fflush(stdin);
			Change_Account_Status(id);
		}
		break;
		case 3:
		{	int id4,amount1; 
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
			int id5,amount2; 
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
				printf("your balance was : %d \n",ptr->balance_s);
				ptr->balance_s-=amount_of_money;
				printf("your balance now is : %d \n",ptr->balance_s);
			}
			if(bank_account_ID_trans_to==ptr->bank_account_ID_s && ptr->account_status_s==1)
			{
				printf("your balance was : %d \n",ptr->balance_s);
				ptr->balance_s+=amount_of_money;	
				printf("your balance now is : %d \n",ptr->balance_s);
			}
		ptr=ptr->next;	
		}
	}else{printf("the entered accounts either not active or not existing or the ammount exceed the limits\n");}
	
}	
void Change_Account_Status(int bank_account_ID){
	int choice;
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
void Get_cash(int bank_account_ID,int amount_required_to_get){
	ptr=first;
			while(ptr!=NULL)
			{
				if( ptr->bank_account_ID_s==bank_account_ID&&ptr->balance_s>amount_required_to_get&&ptr->account_status_s==1)
				{	
					printf("your balance was  : %d \n",ptr->balance_s);
					ptr->balance_s-=amount_required_to_get;
					printf("your balance now is : %d \n",ptr->balance_s);
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
					printf("your balance was : %d \n",ptr->balance_s);
					ptr->balance_s+=amount_required_to_put;
					printf("your balance now is : %d \n",ptr->balance_s);
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
					printf("password changed succefully\n");
				}
				ptr=ptr->next;			
			}
}

void admin_mode(int *ext){
	int user,pw,choice;
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

void client_mode(void){
	
	int bank_account_ID1,pw1;
	printf("please enter the bank account ID :");
	scanf(" %d",&bank_account_ID1);
	fflush(stdin);
	printf("please enter the password for bank account :");
	scanf(" %d",&pw1);
	fflush(stdin);/****************************************************/
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
			scanf(" %d",&choice1);
			fflush(stdin);
			switch(choice1)
			{
				case 1:
				{	
					int bank_ID_from, bank_ID_to, amount;
					printf("please enter the bank account ID trans from \n");
					scanf(" %d",&bank_ID_from);
					fflush(stdin);
					printf("please enter the bank account ID trans to \n");
					scanf(" %d",&bank_ID_to);
					fflush(stdin);
					printf("please enter the amount of money \n");
					scanf(" %d",&amount);
					fflush(stdin);
					make_transaction(bank_ID_from, bank_ID_to, amount);
					return;
				}
				break;
				case 2:
				{	
					int new,old,id;
					printf("please enter the old password");
					scanf(" %d",&old);
					fflush(stdin);
					printf("please enter the new password");
					scanf(" %d",&new);
					fflush(stdin);
					printf("please enter the account bank id");
					scanf(" %d",&id);
					fflush(stdin);
					
					change_pw(old,new,id);
					return;
					
				}
				break;
				case 3:
				{
					int get,id;
					printf("please enter the amount of cash needed ");
					scanf(" %d",&get);
					fflush(stdin);
					printf("please enter the bank account id  ");
					scanf("  %d",&id);
					fflush(stdin);
					Get_cash(id,get);	
					return;
				}
				break;
				case 4:
				{
					int dep,id;
					printf("please enter the amount of cash to deposit ");
					scanf(" %d",&dep);
					fflush(stdin);
					printf("please enter the account bank id");
					scanf("  %d",&id);
					fflush(stdin);
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
