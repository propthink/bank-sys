#include "User.h" // implementing User
#include <random> // for random number generation
#include <iostream> // std::cout

// generates a random, unique user ID
bank_sys::USER_ID User::GENERATE_USER_ID()
{
	// get a random seed from the system
	static std::random_device random_device;

	// initialize a random number generator with the seed
	static std::mt19937 random_generator( random_device() );

	// define the range for generating 6-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000, 999999 );

	// store the generated user ID for comparison
	bank_sys::USER_ID new_user_id;

	do 
	{
		// keep generating a new user ID until it is unique
		new_user_id = rng_distribution( random_generator );

	// check if the user ID already exists
	} while( GENERATED_USER_IDS.find( new_user_id ) != GENERATED_USER_IDS.end() );

	// insert the new unique user ID into the set
	GENERATED_USER_IDS.insert( new_user_id );

	// return the newly generated unique user ID
	return new_user_id;
}

// tracks existing user IDs to enforce uniqueness
std::unordered_set< bank_sys::USER_ID > User::GENERATED_USER_IDS;

// initialize user information
User::UserInfo::UserInfo( const std::string& full_name, const std::string& phone_number,

	const std::string& email_address )

	: m_user_id( User::GENERATE_USER_ID() ), m_full_name( full_name ),

	m_phone_number( phone_number ), m_email_address( email_address ) { }

// initialize user
User::User( const User::UserInfo& user_info, const std::string& user_password )

	: m_user_info( user_info ), m_authenticator( user_password ) { }

// get the unique id associated with this user
bank_sys::USER_ID User::getUserId() const
{
	return m_user_info.m_user_id;
}

// returns true if the authenticator is locked
bool User::authenticatorLocked() const
{
	return m_authenticator.isLocked();
}

// unlocks the authenticator by comparing the input password to the user password
bool User::unlockAuthenticator( const std::string& password_attempt )
{
	return m_authenticator.unlock( password_attempt );
}

// manually locks the authenticator
void User::lockAuthenticator()
{
	m_authenticator.lock();
}