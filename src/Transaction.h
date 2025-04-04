#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Common.h" // bank_sys
#include <string> // std::string

// holds the details of a single financial transaction
class Transaction
{
public:

	// initialize a transaction with two accounts
	Transaction(

		bank_sys::ACCOUNT_ID from_account,

		bank_sys::ACCOUNT_ID to_account,

		bank_sys::US_CENTS transaction_amount );

	// initialize a transaction with a single account
	Transaction( bank_sys::ACCOUNT_ID account_id, bank_sys::US_CENTS transaction_amount );

	// get the from_account id
	bank_sys::ACCOUNT_ID getFromAccountId() const;

	// get the to_account id
	bank_sys::ACCOUNT_ID getToAccountId() const;

	// print the transaction details to the console
	void printTransactionInfo() const;

private:

	// from_account id
	bank_sys::ACCOUNT_ID m_from_account;

	// to_account id
	bank_sys::ACCOUNT_ID m_to_account;

	// transaction amount
	bank_sys::US_CENTS m_transaction_amount;

	// timestamp
	std::string m_timestamp;

	// description
	std::string m_description;
};

#endif // TRANSACTION_H