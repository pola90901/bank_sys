#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"STD_types.h"
#include"admin.h"
#include"client.h"
extern node*ptr;
extern node*first;
extern node*last;
/*-function (make_transaction) used to take 3 arguments account id to transfer from and account id to tranfer to and the amount to be transfered 
	-looping on Linked list done to look if the ids  exisits  and the accounts are active 
	-if the ids found and both account are active
	- tranfer will be done succefully	
	-(used by admin mode and client mode)
*/
void make_transaction(u32 bank_account_ID_trans_from,u32 bank_account_ID_trans_to,u32 amount_of_money){
	u8 flag1=0,flag2=0;
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
				printf("the account to transfer from balance was : %d \n",ptr->balance_s);
				ptr->balance_s-=amount_of_money;
				printf("the account to transfer from balance now is : %d \n",ptr->balance_s);
			}
			if(bank_account_ID_trans_to==ptr->bank_account_ID_s && ptr->account_status_s==1)
			{
				printf("the account to transfer to balance was : %d \n",ptr->balance_s);
				ptr->balance_s+=amount_of_money;	
				printf("the account to transfer to balance now is : %d \n",ptr->balance_s);
			}
		ptr=ptr->next;	
		}
	}else{printf("the entered accounts either not active or not existing or the ammount exceed the limits\n");}
	
}	

/*-function (Get_cash) used to take 2 arguments account id  and the amount to be get  (used by admin mode and client mode)
	-looping on Linked list done to look if the id  exisits  and the account is active 
	-if the id found and account is active
	- transaction will be done succefully	
*/
void Get_cash(u32 bank_account_ID,u32 amount_required_to_get){
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

/*-function (Deposit_in_Account) used to take 2 arguments account id  and the amount of cash to be added (used by admin mode and client mode)
	-looping on Linked list done to look if the id  exisits  and the account is active 
	-if the id found and  account is active
	- transaction will be done succefully	
*/
void Deposit_in_Account(u32 bank_account_ID,u32 amount_required_to_put){
		
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
/*-function (change_pw) used to take 3 arguments account id ,old and new password (used by  client mode only)
	-looping on Linked list done to look if the ids  exisits  and the accounts are active 
	-if the id found and old pw is found 
	- changing the password  will be done succefully	
*/	
void change_pw(u32 old_pw,u32 new_pw,u32 bank_account_ID){
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
/*-function (client_mode) used to take no arguments 
	- printing a list of choice to navigate through out the programm with the all valid option of the user
	-according of the user choice the desired functions will be called
*/
void client_mode(void){
	
	u32 bank_account_ID1,pw1;
	printf("please enter the bank account ID :");
	scanf(" %d",&bank_account_ID1);
	fflush(stdin);
	printf("please enter the password for bank account :");
	scanf(" %d",&pw1);
	fflush(stdin);
	ptr=first;
	u8 flag=0;
	while(ptr!=NULL)
	{
		if (bank_account_ID1== ptr->bank_account_ID_s&&pw1==ptr->pw_s)
		{
			u8 choice1;
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
			flag++;
			switch(choice1)
			{
				case 1:
				{	
					u32 bank_ID_from, bank_ID_to, amount;
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
					u32 new,old,id;
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
					u32 get,id;
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
					u32 dep,id;
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
	if (flag==0)
	{
		printf("incorrect id or PW\n");
	}
}