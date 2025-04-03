#include "Common.h"
#include "User.h"
#include "UserRegistry.h"

#include <iostream>

// enter main
int main()
{
	// init user registry
	UserRegistry user_registry;

	// init new user
	User new_user( User::UserInfo( "Joe", "555-5555", "joe@email" ), "password" );

	bank_sys::USER_ID user_id = new_user.getUserId();

	// add user to registry
	user_registry.insertUser( std::move( new_user ) );

	user_registry.printUserRegistry();

	// find uswr in registry
	User* find_user = nullptr;

	find_user = user_registry.findUser( user_id );

	if( find_user == nullptr )
	{
		std::cout << "find_user is null \n";
	}
	else
	{
		find_user -> printUserInfo();
	}

	// update user
	User::UserInfo new_info( user_id, "Joe", "777-7777", "new@email" );

	if( !user_registry.updateUser( user_id, new_info ) )
	{
		std::cout << "could not update user info \n";
	}
	else
	{
		user_registry.printUserRegistry();
	}
	// delete user
	if( !user_registry.deleteUser( user_id ) )
	{
		std::cout << "could not delete user \n";
	}
	else
	{
		user_registry.printUserRegistry();
	}
	// return to OS
	return 0;
}