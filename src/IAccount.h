#ifndef IACCOUNT_H
#define IACCOUNT_H

#include "Common.h" // bank_sys
#include "Transaction.h" // Transaction
#include <string> // std::string

// a shared interface for interacting with derived account types
class IAccount
{
public:

	// initialize account
	IAccount() = default;

	// deallocate account
	virtual ~IAccount() = default;

	// get the unique id associated with the account
	virtual bank_sys::ACCOUNT_ID getAccountId() const = 0;

	// get the current balance of the account
	virtual bank_sys::US_CENTS getAccountBalance() const = 0;

	// get the overdraft protection fee associated with the account (if applicable)
	virtual bank_sys::US_CENTS getOverdraftProtectionFee() const = 0;

	// get the account maintenance fee associated with the account (if applicable)
	virtual bank_sys::US_CENTS getAccountMaintenanceFee() const = 0;

	// calculate the interest amount associated with the account (if applicable)
	virtual bank_sys::US_CENTS calculateInterest() const = 0;

	// deposit money into the account
	virtual bool deposit( bank_sys::US_CENTS deposit_amount ) = 0;

	// withdraw money from the account
	virtual bool withdraw( bank_sys::US_CENTS withdrawal_amount ) = 0;

	// log a transaction with the account
	virtual void logAccountTransaction( Transaction&& account_transaction ) = 0;

	// get the text string associated with the account type (for logging purposes)
	virtual std::string getAccountString() const = 0;

	// print the account details to the console
	virtual void printAccountInfo() const = 0;

	// print the transaction history to the console
	virtual void printTransactionHistory() const = 0;
};

#endif // IACCOUNT_H