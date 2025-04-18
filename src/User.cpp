#include "User.h" // implementing User.h
#include "InputValidation.h" // input validation
#include <iostream> // std::cout
#include <random> // rng

// initialize new user info
User::UserInfo::UserInfo( const std::string& full_name, const std::string& phone_number,

	const std::string& email_address )

	: m_user_id( User::GENERATE_USER_ID() ), m_full_name( full_name ),

	m_phone_number( phone_number ), m_email_address( email_address ) { }

// initialize pre-existing user info
User::UserInfo::UserInfo( bank_sys::USER_ID user_id, const std::string& full_name,

	const std::string& phone_number, const std::string& email_address )

	: m_user_id( user_id ), m_full_name( full_name ),

	m_phone_number( phone_number ), m_email_address( email_address ) { }

// initialize user
User::User( User::UserInfo&& user_info, const std::string& user_password )

	: m_user_info( std::move( user_info ) ), m_authenticator( user_password ) { }

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

// update the user info associated with this user
void User::updateUserInfo( const UserInfo& user_info )
{
	m_user_info = user_info;
}

// add a new account to this user
void User::addAccount( std::unique_ptr<IAccount> new_account )
{
	// iterate through the vector of accounts
	for( const auto& current_account : m_user_accounts )
	{
		// check if the account already exists
		if( current_account -> getAccountId() == new_account -> getAccountId() )
		{
			return; // account already exists, exit without adding
		}
	}
	// add the new account to this user
	m_user_accounts.push_back( std::move( new_account ) );
}

// remove an existing account from this user
bool User::removeAccount( bank_sys::ACCOUNT_ID account_id )
{
	// iterate through the vector of accounts
	for( auto it = m_user_accounts.begin(); it != m_user_accounts.end(); ++it )
	{
		// if the current account id matches the input account id
		if( it -> get() -> getAccountId() == account_id )
		{
			// account found, remove it from the vector
			m_user_accounts.erase( it );

			return true; // account was removed
		}
	}
	return false; // account not found
}

// access an account associated with this user
IAccount* User::accessAccount() const
{
	// check if there is a valid account associated with this user
	if( m_user_accounts.empty() )
	{
		std::cout << "There are currently no accounts associated with this user \n";

		return nullptr;
	}
	// initialize the user input
	std::string user_input { "" };

	// input and validate the user input
	while( true )
	{
		std::cout << "Select one from the following accounts: \n";

		for( int i = 0; i < m_user_accounts.size(); ++i )
		{
			std::cout << "\n[" << ( i + 1 ) << "]: ";
			
			m_user_accounts.at( i ).get() -> printAccountInfo();
		}
		std::cout << "\nEnter your selection here: ";

		// capture the user input
		std::getline( std::cin, user_input );

		// validate the user input
		if( !user_input.empty() && isDigitsOnly( user_input )

			&& ( std::stoi( user_input ) > 0 ) && std::stoi( user_input ) <= m_user_accounts.size() )
		{
			break; // input is valid
		}
		std::cout << "Invalid input detected, please try again \n";
	}
	return m_user_accounts.at( std::stoi( user_input ) - 1 ).get();
}

// print the user details to the console
void User::printUserInfo() const
{
	std::cout << "USER ID: " << m_user_info.m_user_id;

	std::cout << " | NAME: " << m_user_info.m_full_name;

	std::cout << " | PHONE: " << m_user_info.m_phone_number;

	std::cout << " | EMAIL: " << m_user_info.m_email_address << '\n';
}

// print the account details to the console
void User::printAccountInfo() const
{
	if( m_user_accounts.empty() )
	{
		std::cout << "There are currently no accounts associated with this user \n";
	}
	else
	{
		for( const auto& account : m_user_accounts )
		{
			account -> printAccountInfo();

			std::cout << '\n';
		}
	}
}

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