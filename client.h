#ifndef CLIENT_H
#define CLIENT_H
#include"STD_types.h"

void change_pw(u32 old_pw,u32 new_pw,u32 bank_account_ID);
void make_transaction(u32 bank_account_ID_trans_from,u32 bank_account_ID_trans_to,u32 amount_of_money);
void Get_cash(u32 bank_account_ID,u32 amount_required_to_get);
void Deposit_in_Account(u32 bank_account_ID,u32 amount_required_to_put);
void client_mode(void);




#endif	


