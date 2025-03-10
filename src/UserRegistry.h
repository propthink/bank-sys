#ifndef USER_REGISTRY_H
#define USER_REGISTRY_H

#include "User.h" // User
#include "Common.h" // bank_sys namespace
#include <memory> // std::unique_ptr

// manages all users in a linked list
class UserRegistry
{
public:

	// initialize user registry
	UserRegistry();

	// add a new user to the registry
	void insertUser( User&& user );

	// delete an existing user from the registry
	void deleteUser( bank_sys::USER_ID user_id );

	// search for a user in the registry
	User* findUser( bank_sys::USER_ID user_id );

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