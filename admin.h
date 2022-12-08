#ifndef ADMIN_H
#define ADMIN_H
#include"STD_types.h"
typedef struct bank_account node;
struct bank_account 
{
	u8 name_s[100];
	u8 address_s[100];
	ul64 national_ID_s;
	u32 age_s;
	u32 bank_account_ID_s;
	u8 guardian_s[100];
	ul64 guardian_ID_s;
	u32 account_status_s;
	u32 balance_s;
	u32 pw_s;	
	node*next;
	node*pre;	
};

void creat_new_account(void); 
void open_exisiting_account(void);	
void Change_Account_Status(u32 bank_account_ID);
void admin_mode(u8 *ext); 
void creat_dummy_account(void);
u32 func_generate_ID(void);
u32 func_generate_pw(void);





#endif 