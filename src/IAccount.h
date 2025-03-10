#ifndef IACCOUNT_H
#define IACCOUNT_H

#include "Common.h" // for bank_sys namespace

// a shared interface for interacting with derived account types
class IAccount
{
public:

	// initialize account
	IAccount() = default;

	// deallocate account
	virtual ~IAccount() = default;

	// deposit money into the account
	virtual bool deposit( bank_sys::US_CENTS deposit_amount ) = 0;

	// withdraw money from the account
	virtual bool withdraw( bank_sys::US_CENTS withdrawal_amount ) = 0;

	// TEST_PRINT
	virtual void TEST_PRINT() const = 0;
};

#endif // IACCOUNT_H