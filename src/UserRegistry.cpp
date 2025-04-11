#include "UserRegistry.h" // implementing

// insert a new user
void UserRegistry::insertUser( User&& user )
{
	m_users.insert( std::move( user ) );
}

// delete an existing user
bool UserRegistry::deleteUser( bank_sys::USER_ID user_id )
{
	return m_users.removeIf(
		
			[ user_id ]( const User& user ){ return user.getUserId() == user_id; }
	);
}

// find an existing user
User* UserRegistry::findUser( bank_sys::USER_ID user_id ) const
{
	return m_users.findIf(

		[ user_id ]( const User& user ){ return user.getUserId() == user_id; }
	);
}

// update an existing user
bool UserRegistry::updateUser( bank_sys::USER_ID user_id, const User::UserInfo& user_info )
{
	User* update_user = findUser( user_id );

	if( update_user )
	{
		update_user -> updateUserInfo( user_info );

		return true;
	}
	return false;
}

// print the user registry to the console
void UserRegistry::printUserRegistry() const
{
	m_users.forEach(

		[]( const User& user ) { user.printUserInfo();  }
	);
}