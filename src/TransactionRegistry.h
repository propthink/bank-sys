#ifndef TRANSACTION_REGISTRY_H
#define TRANSACTION_REGISTRY_H

#include "Common.h"
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

	// print the entire transaction registry to the console
	void printTransactionRegistry() const;

	// filter the transaction registry by account number
	void printFilteredTransactions( bank_sys::ACCOUNT_ID account_id ) const;

private:

	// manages a single node in the registry
	class TransactionNode
	{
	public:

		// initialize transaction node
		TransactionNode( Transaction&& transaction );

		// transaction object
		std::unique_ptr< Transaction > m_transaction;

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