#ifndef USER_H
#define USER_H

#include "Utilities.h" // for utils
#include <string> // for std::string
#include <memory> // for std::unique_ptr

// stores user information, including user id, name, phone, and email
struct UserInfo
{
	UserInfo(
	
		IdUtils::USER_ID user_id, std::string full_name,

		std::string phone_number, std::string email_address

		); // initialize user data

	IdUtils::USER_ID m_user_id; // unique user id

	std::string m_full_name; // user full name

	std::string m_phone_number; // user phone number

	std::string m_email_address; // user email address
};

// represents a user with personal information
class User
{
public:

	User( const UserInfo& user_info ); // initialize user

	// get the unique id associated with this user
	IdUtils::USER_ID getUserId() const;

private:

	UserInfo m_user_info; // user info
};

// a node in a doubly linked list that manages a user object
class UserNode
{
public:

	UserNode( std::unique_ptr< User > user ); // initialize node with user

	std::unique_ptr< User > m_user; // the actual user object

	std::unique_ptr< UserNode > m_next; // pointer to the next node

	UserNode* m_prev; // pointer to the previous node
};

// a registry that stores users in a doubly linked list
class UserRegistry
{
public:

	UserRegistry(); // initialize the user registry

	// add a user at the end of the list
	void addUser( std::unique_ptr< User > user );

	// search for a user by user id
	UserNode* findUser( IdUtils::USER_ID user_id );

private:

	// pointer to the head of the list
	std::unique_ptr< UserNode > m_head;

	// pointer to the tail of the list
	UserNode* m_tail;
};

#endif // USER_H