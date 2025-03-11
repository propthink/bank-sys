#ifndef USER_H
#define USER_H

#include "Common.h" // bank_sys namespace
#include "Authenticator.h" // Authenticator
#include "IAccount.h" // account interface
#include <unordered_set> // std::unordered_set
#include <string> // std::string
#include <vector> // std::vector
#include <memory> // std::unique_ptr

// represents a single user with personal information and account details
class User
{
public:

	// generates a random, unique user ID
	static bank_sys::USER_ID GENERATE_USER_ID();

	// tracks existing user IDs to enforce uniqueness
	static std::unordered_set< bank_sys::USER_ID > GENERATED_USER_IDS;

	// stores user information including user id, name, phone number, and email address
	struct UserInfo
	{
		// initialize user information
		UserInfo( const std::string& full_name, const std::string& phone_number,

			const std::string& email_address );

		bank_sys::USER_ID m_user_id; // unique user id

		std::string m_full_name; // user full name

		std::string m_phone_number; // user phone number

		std::string m_email_address; // user email address
	};
	// initialize user
	User( const User::UserInfo& user_info, const std::string& user_password );

	// get the unique id associated with this user
	bank_sys::USER_ID getUserId() const;

	// returns true if the authenticator is locked
	bool authenticatorLocked() const;

	// unlocks the authenticator by comparing the input password to the user password
	bool unlockAuthenticator( const std::string& password_attempt );

	// manually locks the authenticator
	void lockAuthenticator();

	// add a new account to this user
	void addAccount( std::unique_ptr< IAccount > new_account );

	// remove an existing account from this user
	bool removeAccount( bank_sys::ACCOUNT_ID account_id );

	// deposit money into an account associated with this user
	bool depositToAccount( bank_sys::ACCOUNT_ID account_id, bank_sys::US_CENTS deposit_amount );

	// withdraw money from an account associated with this user
	bool withdrawFromAccount( bank_sys::ACCOUNT_ID account_id, bank_sys::US_CENTS withdrawal_amount );

	// TEST PRINT
	void TEST_PRINT() const;

private:

	// basic user information
	UserInfo m_user_info;

	// handles user authentication
	Authenticator m_authenticator;

	// accounts associated with this user
	std::vector< std::unique_ptr< IAccount > > m_user_accounts;
};

#endif // USER_H