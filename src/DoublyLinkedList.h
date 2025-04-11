#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <memory> // std::unique_ptr

// template class for doubly linked list implementation
template < typename T >
class DoublyLinkedList
{
public:

	// initialize doubly linked list
	DoublyLinkedList();

	// insert a new object
	void insert( T&& object );

	// remove an existing object
	template< typename Condition >
	bool removeIf( Condition&& condition );

	// find an existing object
	template< typename Condition >
	T* findIf( Condition&& condition ) const;

	// iterate through each object
	template< typename Operation >
	void forEach( Operation&& operation ) const;

private:

	// manages a single node in the linked list
	struct Node
	{
		// initialize the node
		Node( T&& object );

		// the object owned by the node
		std::unique_ptr< T > m_data;

		// the next node in the linked list
		std::unique_ptr< Node > m_next;

		// the prev node in the linked list
		Node* m_prev;
	};
	// head node
	std::unique_ptr< Node > m_head;

	// tail node
	Node* m_tail;
};

// initialize doubly linked list
template< typename T >
DoublyLinkedList< T >::DoublyLinkedList()

	: m_head( nullptr ), m_tail( nullptr ) { }

// insert a new object
template< typename T >
void DoublyLinkedList< T >::insert( T&& object )
{
	// initialize the new node
	auto new_node = std::make_unique< Node >( std::move( object ) );

	// check if the list is empty
	if( !m_head )
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

// remove an existing object
template< typename T >
template< typename Condition >
bool DoublyLinkedList< T >::removeIf( Condition&& condition )
{
	// check if the list is empty
	if( !m_head )
	{
		return false; // nothing to delete
	}
	// start from the head node
	auto current_node = m_head.get();

	// iterate through each node in the list
	while( current_node != nullptr )
	{
		// check the conditional
		if( condition( *current_node -> m_data ) )
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
			// return after successful deletion
			return true;
		}
		// move to the next node
		current_node = current_node -> m_next.get();
	}
	// object not found
	return false;
}

// find an existing object
template< typename T >
template< typename Condition >
T* DoublyLinkedList< T >::findIf( Condition&& condition ) const
{
	// check if the list is empty
	if( !m_head )
	{
		return nullptr; // nothing to delete
	}
	// start from the head node
	auto current_node = m_head.get();

	// iterate through each node in the list
	while( current_node != nullptr )
	{
		// check the conditional
		if( condition( *current_node -> m_data ) )
		{
			// return the object if found
			return current_node -> m_data.get();
		}
		// move to the next node
		current_node = current_node -> m_next.get();
	}
	// return nullptr if object is not found
	return nullptr;
}

// iterate through each object
template< typename T >
template< typename Operation >
void DoublyLinkedList< T >::forEach( Operation&& operation ) const
{
	// check if the list is empty
	if( !m_head )
	{
		return; // list is empty
	}
	// start from the head node
	auto current_node = m_head.get();

	// iterate through each node in the list
	while( current_node != nullptr )
	{
		// perform the operation on the current object
		operation( *current_node -> m_data );

		// move to the next node
		current_node = current_node -> m_next.get();
	}
}

// initialize the node
template< typename T >
DoublyLinkedList< T >::Node::Node( T&& object )

	: m_data( std::make_unique< T >( std::move( object ) ) ),

	m_next( nullptr ), m_prev( nullptr ) { }

#endif // DOUBLY_LINKED_LIST_H