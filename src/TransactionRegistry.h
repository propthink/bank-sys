#ifndef TRANSACTION_REGISTRY_H
#define TRANSACTION_REGISTRY_H

#include "Common.h" // bank_sys
#include "Transaction.h" // Transaction
#include "DoublyLinkedList.h" // DoublyLinkedList

// manages all transactions in a linked list
class TransactionRegistry
{
public:

	// initialize transaction registry
	TransactionRegistry() = default;

	// add a new transaction
	void insertTransaction( Transaction&& transaction );

	// print the transaction registry to the console
	void printTransactionRegistry() const;

	// filter the transaction registry by account number
	void printFilteredTransactions( bank_sys::ACCOUNT_ID account_id ) const;

private:

	// implementation of the linked list
	DoublyLinkedList< Transaction > m_transactions;
};

#endif // TRANSACTION_REGISTRY_H