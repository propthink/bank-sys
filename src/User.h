#ifndef USER_H
#define USER_H

#include "Utilities.h" // for utils
#include "Account.h" // for accounts
#include <unordered_set> // for std::unordered_set
#include <string> // for std::string
#include <memory> // for std::unique_ptr
#include <vector> // for std::vector

// generates a random, unique user ID
Utils::USER_ID GENERATE_USER_ID();

// tracks existing user IDs to enforce uniqueness
extern std::unordered_set< Utils::USER_ID > GENERATED_USER_IDS;

// stores user information, including user id, name, phone, and email
struct UserInfo
{
	// initialize user data
	UserInfo(
	
		Utils::USER_ID user_id, std::string full_name,

		std::string phone_number, std::string email_address

		);

	Utils::USER_ID m_user_id; // unique user id

	std::string m_full_name; // user full name

	std::string m_phone_number; // user phone number

	std::string m_email_address; // user email address
};

// represents a user with personal information
class User
{
public:

	// initialize user
	User( const UserInfo& user_info );

	// get the unique id associated with this user
	Utils::USER_ID getUserId() const;

	// add an account to this user
	void addAccount( std::unique_ptr< IAccount > new_account );

private:

	// user information
	UserInfo m_user_info;

	// accounts associated with this user
	std::vector< std::unique_ptr< IAccount > > m_user_accounts;
};

// a node in a doubly linked list that manages a user object
class UserNode
{
public:

	// initialize node with user
	UserNode( std::unique_ptr< User > user );

	// the actual user object
	std::unique_ptr< User > m_user;

	// pointer to the next node
	std::unique_ptr< UserNode > m_next;

	// pointer to the previous node
	UserNode* m_prev;
};

// a registry that stores users in a doubly linked list
class UserRegistry
{
public:

	// initialize the user registry
	UserRegistry();

	// add a user at the end of the list
	void addUser( std::unique_ptr< User > user );

	// search for a user by user id
	UserNode* findUser( Utils::USER_ID user_id );

private:

	// pointer to the head of the list
	std::unique_ptr< UserNode > m_head;

	// pointer to the tail of the list
	UserNode* m_tail;
};

#endif // USER_H