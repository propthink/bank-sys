#ifndef IACCOUNT_H
#define IACCOUNT_H

#include "Common.h" // bank_sys namespace

// a shared interface for interacting with derived account types
class IAccount
{
public:

	// initialize account
	IAccount() = default;

	// deallocate account
	virtual ~IAccount() = default;

	// get the unique id associated with this account
	virtual bank_sys::USER_ID getAccountId() const = 0;

	// get the current balance of this account
	virtual bank_sys::US_CENTS getCurrentBalance() const = 0;

	// deposit money into this account
	virtual bool deposit( bank_sys::US_CENTS deposit_amount ) = 0;

	// withdraw money from this account
	virtual bool withdraw( bank_sys::US_CENTS withdrawal_amount ) = 0;

	// TEST PRINT
	virtual void TEST_PRINT() const = 0;
};

#endif // IACCOUNT_H