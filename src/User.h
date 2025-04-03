#ifndef USER_H
#define USER_H

#include "Common.h" // bank_sys
#include "IAccount.h" // IAccount
#include "Authenticator.h" // Authenticator
#include <string> // std::string
#include <memory> // std::unique_ptr
#include <unordered_set> // std::unordered_set
#include <vector> // std::vector

// represents a single user with personal information and account details
class User
{
public:

	// stores user information including user id, name, phone number, and email address
	struct UserInfo
	{
		// initialize new user info
		UserInfo( const std::string& full_name, const std::string& phone_number,

			const std::string& email_address );

		// initialize pre-existing user info
		UserInfo( bank_sys::USER_ID user_id, const std::string& full_name, 
			
			const std::string& phone_number, const std::string& email_address );

		bank_sys::USER_ID m_user_id; // unique user id

		std::string m_full_name; // user full name

		std::string m_phone_number; // user phone number

		std::string m_email_address; // user email address
	};
	// initialize user
	User( User::UserInfo&& user_info, const std::string& user_password );

	// get the unique id associated with this user
	bank_sys::USER_ID getUserId() const;

	// returns true if the authenticator is locked
	bool authenticatorLocked() const;

	// unlocks the authenticator by comparing the input password to the user password
	bool unlockAuthenticator( const std::string& password_attempt );

	// manually locks the authenticator
	void lockAuthenticator();

	// update the user info associated with this user
	void updateUserInfo( const UserInfo& user_info );

	// add a new account to this user
	void addAccount( std::unique_ptr<IAccount> new_account );

	// remove an existing account from this user
	bool removeAccount( bank_sys::ACCOUNT_ID account_id );

	// print the user details to the console
	void printUserInfo() const;

private:

	// generates a random, unique user ID
	static bank_sys::USER_ID GENERATE_USER_ID();

	// tracks existing user IDs to enforce uniqueness
	static std::unordered_set< bank_sys::USER_ID > GENERATED_USER_IDS;

	// basic user information
	UserInfo m_user_info;

	// handles user authentication
	Authenticator m_authenticator;

	// accounts associated with this user
	std::vector< std::unique_ptr< IAccount > > m_user_accounts;
};

#endif // USER_H