#include "Common.h"
#include "User.h"
#include "UserRegistry.h"
#include "Transaction.h"
#include "TransactionRegistry.h"
#include "IAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "Vault.h"
#include "TransactionUtilities.h"

#include <iostream>

// enter main
int main()
{
	// the user registry is implemented as a doubly linked list that can add, find, update, and delete users
	UserRegistry user_registry;
	
	User new_user_1( User::UserInfo( "Joe", "555-5555", "joe@email" ), "password" );

	User new_user_2( User::UserInfo( "Bob", "667-7775", "bob@email" ), "password" );

	bank_sys::USER_ID user_1_id = new_user_1.getUserId();

	// add new users to the registry
	user_registry.insertUser( std::move( new_user_1 ) );

	user_registry.insertUser( std::move( new_user_2 ) );

	// print the user registry to the console
	user_registry.printUserRegistry(); std::cout << '\n';

	// find an existing user in the registry
	User* find_user = nullptr;

	find_user = user_registry.findUser( user_1_id );

	// print the user info to the console
	if( !find_user )
	{
		std::cout << "User not found! \n";
	}
	else
	{
		find_user -> printUserInfo(); std::cout << '\n';
	}
	// update the user info for an existing user
	user_registry.updateUser( user_1_id, User::UserInfo( user_1_id, "Joe", "555-2929", "new@email" ) );

	// print the user registry to the console
	user_registry.printUserRegistry(); std::cout << '\n';

	// delete an existing user from the registry
	user_registry.deleteUser( user_1_id );

	// print the user registry to the console
	user_registry.printUserRegistry(); std::cout << '\n';

	// the transaction registry is implemented as a doubly linked list that can manage existing transactions
	// and filter transactions according to the associated account ids
	TransactionRegistry transaction_registry;

	// add new transactions to the registry
	transaction_registry.insertTransaction( Transaction( 000000000, 000000000, 500 ) );

	transaction_registry.insertTransaction( Transaction( 000000000, 123456789, 1000 ) );

	transaction_registry.insertTransaction( Transaction( 000000000, 000000000, -100 ) );

	// print the transaction registry to the console
	transaction_registry.printTransactionRegistry(); std::cout << '\n';

	// filter the transaction registry according to account id
	transaction_registry.printFilteredTransactions( 123456789 ); std::cout << '\n';

	// specific account types contain special helper classes to assist with specific banking functionalities
	CheckingAccount checking_account; // includes overdraft protection

	SavingsAccount savings_account; // includes interest calculation

	Vault bank_vault; // needed to complete transactions in the system

	// account interface allows other areas of the program to interact with derived account types
	IAccount* checking_ptr = &checking_account;

	IAccount* savings_ptr = &savings_account;

	// overdraft protection allows checking accounts to spend past their account balance to a limit, for a fee
	// if the checking account has $100:
	TransactionUtilities::depositToAccount( *checking_ptr, bank_vault, 10000 );

	// and the user attempts to withdraw $150:
	TransactionUtilities::withdrawFromAccount( *checking_ptr, bank_vault, 15000 );

	// this transaction is allowed, and incurs a fee that is paid to the bank
	// the deposit, withdrawal, and fee can be seen in the account transaction registry:
	checking_ptr -> printAccountInfo(); std::cout << '\n';

	// however, if a savings account has $100:
	TransactionUtilities::depositToAccount( *savings_ptr, bank_vault, 10000 );

	// and the user attempts to withdraw $150:
	TransactionUtilities::withdrawFromAccount( *savings_ptr, bank_vault, 15000 );

	// this transaction is not allowed, as can be seen in the account transaction registry:
	savings_ptr -> printAccountInfo(); std::cout << '\n';

	// while savings accounts are not eligible for overdraft protection, they do accrue interest paid out by the bank
	// checking accounts do not apply interest to their balances
	if( checking_ptr -> calculateInterest() > 0 )
	{
		TransactionUtilities::transferFromVaultToAccount(

			*checking_ptr, bank_vault, checking_ptr -> calculateInterest() );
	}
	if( savings_ptr -> calculateInterest() > 0 )
	{
		TransactionUtilities::transferFromVaultToAccount(

			*savings_ptr, bank_vault, savings_ptr -> calculateInterest() );
	}
	// printing the transaction registries to the console shows that interest was applied only to the savings account:
	checking_ptr -> printAccountInfo();

	savings_ptr -> printAccountInfo(); std::cout << '\n';

	// return to OS
	return 0;
}