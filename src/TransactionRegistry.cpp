#include "TransactionRegistry.h" // implementing TransactionRegistry.h

// initialize transaction registry
TransactionRegistry::TransactionRegistry()

	: m_head( nullptr ), m_tail( nullptr ) { }

// add a new transaction to the registry
void TransactionRegistry::insertTransaction( Transaction&& transaction )
{
	// initialize transaction node
	auto new_node = std::make_unique< TransactionNode >( std::move( transaction ) );

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

// print the entire transaction registry to the console
void TransactionRegistry::printTransactionRegistry() const
{
	auto current_node = m_head.get();

	while( current_node )
	{
		if( current_node -> m_transaction )
		{
			current_node -> m_transaction -> printTransactionInfo();
		}
		current_node = current_node -> m_next.get();
	}
}

// filter the transaction registry by account number
void TransactionRegistry::printFilteredTransactions( bank_sys::ACCOUNT_ID account_id ) const
{
	auto current_node = m_head.get();

	while( current_node )
	{
		if( current_node -> m_transaction )
		{
			if( current_node -> m_transaction -> getFromAccountId() == account_id

				|| current_node -> m_transaction -> getToAccountId() == account_id )
			{
				current_node -> m_transaction -> printTransactionInfo();
			}
		}
		current_node = current_node -> m_next.get();
	}
}

// initialize transaction node
TransactionRegistry::TransactionNode::TransactionNode( Transaction&& transaction )

	: m_transaction( std::make_unique< Transaction >( std::move( transaction ) ) ),

	m_next( nullptr ), m_prev( nullptr ) { }