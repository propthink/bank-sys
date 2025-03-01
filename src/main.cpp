#include "User.h"
#include "Account.h"
#include "Utility.h"
#include <iostream> // for std::cout
#include <memory> // for std::make_unique

int main()
{
	// create a new user
	User new_user( UserInfo(

		GENERATE_USER_ID(),

		"John M. Wayne",

		"123-456-7890",

		"john@wayne.org"
	) );
	// create a new account
	BAccount new_account( GENERATE_ACCOUNT_ID() );

	// deposit into the account
	new_account += Utils::US_CENTS { 500 };

	// withdraw from the account
	new_account -= Utils::US_CENTS { 150 };

	// print the account info and transaction history
	std::cout << new_account << '\n';

	// save the account ID for demonstration purposes
	Utils::ACCOUNT_ID account_id = new_account.getAccountId();

	// associate the account with the user
		// NOTE: password is 'password'
	new_user.addAccount( std::make_unique< BAccount >( std::move( new_account ) ) );

	// deposit into the account
	new_user.depositToAccount( account_id, Utils::US_CENTS { 250 } );

	// withdraw from the account
	new_user.withdrawFromAccount( account_id, Utils::US_CENTS { 50 } );

	// print the user info, account info and transaction history
	new_user.printUser();

	// return to os
	return 0;
}