#ifndef TRANSACTION_REGISTRY_H
#define TRANSACTION_REGISTRY_H

#include "Transaction.h" // Transaction
#include <memory> // std::unique_ptr

// manages all transactions in a linked list
class TransactionRegistry
{
public:

	// initialize transaction registry
	TransactionRegistry();

	// add a new transaction to the registry
	void insertTransaction( Transaction&& transaction );

	// TEST PRINT
	void TEST_PRINT() const;

private:

	// manages a single node in the registry
	class TransactionNode
	{
	public:

		// initialize transaction node
		TransactionNode( Transaction&& transaction );

		// transaction object
		std::unique_ptr< Transaction > m_user;

		// next transaction node
		std::unique_ptr< TransactionNode > m_next;

		// prev transaction node
		TransactionNode* m_prev;
	};
	// head node
	std::unique_ptr< TransactionNode > m_head;

	// tail node
	TransactionNode* m_tail;
};

#endif // TRANSACTION_REGISTRY_H