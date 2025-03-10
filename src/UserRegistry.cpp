#include "UserRegistry.h" // implementing UserRegistry

// initialize user registry
UserRegistry::UserRegistry()

	: m_head( nullptr ), m_tail( nullptr ) { }

// add a new user to the registry
void UserRegistry::insertUser( User&& user )
{
	// initialize user node
	auto new_node = std::make_unique< UserNode >( std::move( user ) );

	// check if the list is empty
	if( m_head == nullptr )
	{
		// set the head to the new node
		m_head = std::move( new_node );

		// set the tail to the head
		m_tail = m_head.get();

	}
	else
	{
		// set the current tail's next pointer to the new node
		m_tail -> m_next = std::move( new_node );

		// set the prev pointer of the new tail to the old tail
		m_tail -> m_next -> m_prev = m_tail;

		// update the tail to the new node
		m_tail = m_tail -> m_next.get();
	}
}

// delete an existing user from the registry
void UserRegistry::deleteUser( bank_sys::USER_ID user_id )
{
	// check if the list is empty
	if( m_head == nullptr )
	{
		return; // nothing to delete
	}
	// start from the head
	auto current_node = m_head.get();

	// iterate through each node in the list
	while( current_node != nullptr )
	{
		// check if the user id matches
		if( current_node -> m_user.get() -> getUserId() == user_id )
		{
			// if the current node is the head node
			if( current_node == m_head.get() )
			{
				// if there is only one node in the list
				if( m_head.get() == m_tail )
				{
					// list becomes empty
					m_head = nullptr;

					m_tail = nullptr;
				}
				else
				{
					// move the head forward
					m_head = std::move( m_head -> m_next );

					m_head -> m_prev = nullptr;
				}
			} // if the current node is the tail node
			else if( current_node == m_tail )
			{
				// move the tail backwards
				m_tail = m_tail -> m_prev;

				m_tail -> m_next = nullptr;

			} // if the current node is a middle node
			else
			{
				// set the prev pointer of the next node to the previous node
				current_node -> m_next -> m_prev = current_node -> m_prev;

				// move the next node into the previous node's next pointer
				current_node -> m_prev -> m_next = std::move( current_node -> m_next );
			}
			// return after deletion
			return;
		}
		// move to the next node
		current_node = current_node -> m_next.get();
	}
	// user id not found
}

// search for a user in the registry
User* UserRegistry::findUser( bank_sys::USER_ID user_id )
{
	// check if the list is empty
	if( m_head == nullptr )
	{
		// return nullptr if empty
		return nullptr;
	}
	// start from the head node
	auto current_node = m_head.get();

	// iterate through each node in the list
	while( current_node != nullptr )
	{
		// check if the user id matches
		if( current_node -> m_user.get() -> getUserId() == user_id )
		{
			// return the user if found
			return current_node -> m_user.get();
		}
		// move to the next node
		current_node = current_node -> m_next.get();
	}
	// user id not found
	return nullptr;
}

// initialize user node
UserRegistry::UserNode::UserNode( User&& user )

	: m_user( std::make_unique< User >( std::move( user ) ) ), 
	
	m_next( nullptr ), m_prev( nullptr ) { }