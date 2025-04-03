#ifndef USER_REGISTRY_H
#define USER_REGISTRY_H

#include "Common.h" // bank_sys
#include "User.h" // User

// manages all users in a linked list
class UserRegistry
{
public:

	// initialize user registry
	UserRegistry();

	// add a new user to the registry
	void insertUser( User&& user );

	// delete an existing user from the registry
	bool deleteUser( bank_sys::USER_ID user_id );

	// search for a user in the registry
	User* findUser( bank_sys::USER_ID user_id );

	// update an existing user in the registry
	bool updateUser( bank_sys::USER_ID user_id, const User::UserInfo& user_info );

	// print the entire user registry to the console
	void printUserRegistry() const;

private:

	// manages a single node in the registry
	class UserNode
	{
	public:

		// initialize user node
		UserNode( User&& user );

		// user object
		std::unique_ptr< User > m_user;

		// next user node
		std::unique_ptr< UserNode > m_next;

		// prev user node
		UserNode* m_prev;
	};
	// head node
	std::unique_ptr< UserNode > m_head;

	// tail node
	UserNode* m_tail;
};

#endif // USER_REGISTRY_H