#ifndef USER_REGISTRY_H
#define USER_REGISTRY_H

#include "Common.h" // bank_sys
#include "User.h" // User
#include "DoublyLinkedList.h" // DoublyLinkedList

// manages all users in a linked list
class UserRegistry
{
public:

	// initialize user registry
	UserRegistry() = default;

	// insert a new user
	void insertUser( User&& user );

	// delete an existing user
	bool deleteUser( bank_sys::USER_ID user_id );

	// find an existing user
	User* findUser( bank_sys::USER_ID user_id ) const;

	// update an existing user
	bool updateUser( bank_sys::USER_ID user_id, const User::UserInfo& user_info );

	// print the user registry to the console
	void printUserRegistry() const;

private:

	// implementation of the linked list
	DoublyLinkedList< User > m_users;
};

#endif // USER_REGISTRY_H