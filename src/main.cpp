#include "DoublyLinkedList.h"
#include "User.h"
#include "Common.h"
#include "CheckingAccount.h"
#include "Vault.h"
#include "TransactionUtilities.h"
#include "BankingException.h"
#include <iostream>

// enter main
int main()
{
	// DoublyLinkedList is a template class used to manage memory for linked list structures
	DoublyLinkedList< User > user_list;

	User user_1 { User::UserInfo( "Joe", "555-5555", "joe@email" ), "password" };

	User user_2 { User::UserInfo( "Ben", "667-7777", "ben@email" ), "password" };

	bank_sys::USER_ID user_1_id = user_1.getUserId();

	bank_sys::USER_ID user_2_id = user_2.getUserId();

	// add the new users to the linked list
	user_list.insert( std::move( user_1 ) );

	user_list.insert( std::move( user_2 ) );

	// print the contents of the linked list to the console
	user_list.forEach( 
		
		[]( const User& user ) { user.printUserInfo();  } ); std::cout << '\n';

	// Users implement callable objects to define specific interactions with the underlying data.

	// find an existing user
	User* find_user = user_list.findIf( 
		
		[ user_1_id ]( const User& user ) { return user.getUserId() == user_1_id; } );

	if( !find_user )
	{
		std::cout << "User not found! \n"; std::cout << '\n';
	}
	else
	{
		find_user -> printUserInfo(); std::cout << '\n';
	}
	// delete an existing user
	if( !user_list.removeIf(

		[ user_1_id ]( const User& user ) { return user.getUserId() == user_1_id; } ) )
	{
		std::cout << "User not found! \n"; std::cout << '\n';
	}
	else
	{
		// print the contents of the linked list to the console
		user_list.forEach(

			[]( const User& user ) { user.printUserInfo();  } ); std::cout << '\n';
	}
	// The UserRegistry and TransactionRegistry classes use the DoublyLinkedList structure internally
	// to perform specific operations related to manual memory management.

	// The banking system also utilizes custom exceptions to handle errors related to banking functionality.
	try
	{
		Vault bank_vault; //

		CheckingAccount user_account; //

		// This will throw an InvalidTransactionError
		TransactionUtilities::depositToAccount( user_account, bank_vault, -500 );

		// This will throw an InsufficientFundsError
		// TransactionUtilities::withdrawFromAccount( user_account, bank_vault, 50000 );
	}
	catch( const InvalidTransactionError& error )
	{
		std::cout << "InvalidTransactionError: " << error.what() << '\n';
	}
	catch( const VaultTransactionError& error )
	{
		std::cout << "VaultTransactionError: " << error.what() << '\n';
	}
	catch( const AccountTransactionError& error )
	{
		std::cout << "AccountTransactionError: " << error.what() << '\n';
	}
	catch( const InsufficientFundsError& error )
	{
		std::cout << "InsufficientFundsError: " << error.what() << '\n';
	}
}