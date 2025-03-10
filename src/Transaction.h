#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Common.h" // bank_sys namespace
#include <string> // std::string

// holds the details of a single financial transaction
class Transaction
{
public:

	// initialize the transaction
	Transaction( bank_sys::ACCOUNT_ID account_id, bank_sys::US_CENTS transaction_amount );

	// TEST PRINT
	void TEST_PRINT() const;

private:

	// account id
	bank_sys::ACCOUNT_ID m_account_id;

	// amount of transaction
	bank_sys::US_CENTS m_amount;

	// brief text description
	std::string m_description;

	// timestamp
	std::string m_timestamp;
};

#endif // TRANSACTION_H