#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Utility.h" // for utils
#include <string> // for std::string
#include <memory> // for std::unique_ptr

// holds the details of a single financial transaction
class Transaction
{
public:

	// initialize transaction
	Transaction( const Utils::ACCOUNT_ID account_id, const Utils::US_CENTS transaction_amount );

	// print the transaction details to the console
	void printTransaction() const;

private:

	Utils::ACCOUNT_ID m_account_id; // account id

	Utils::US_CENTS m_amount; // amount of transaction

	std::string m_description; // brief text description

	std::string m_timestamp; // timestamp
};

// represents a single node in the transaction history linked list
class TransactionNode
{
public:

	// initialize transaction node
	TransactionNode( const Transaction& transaction );

	// the actual transaction object
	std::unique_ptr< Transaction > m_transaction;

	// pointer to the next node
	std::unique_ptr< TransactionNode > m_next;

	// pointer to the previous node
	TransactionNode* m_prev;
};

// manages a doubly linked list of transactions
class TransactionLog
{
public:

	// initialize transaction log
	TransactionLog();

	// add a new transaction at the end of the list
	void addTransaction( const Transaction& transaction );

	// print the entire transaction log
	void printTransactionLog() const;

	// checks if the transaction log is empty
	bool isEmpty() const;

private:

	// head of the log
	std::unique_ptr< TransactionNode > m_head;

	// tail of the log
	TransactionNode* m_tail;
};

#endif // TRANSACTION_H