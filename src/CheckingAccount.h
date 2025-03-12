#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "BAccount.h" // inherits from BAccount
#include "Common.h" // bank_sys namespace

// checking account (intended for frequent transactions)
// no minimum balance, no transaction limits, no interest earned on balance
// overdraft protection (negative balanced allowed, for a fee)
// monthly fee (unless certain conditions are met, e.g. # of transactions)
class CheckingAccount : public BAccount
{
public:

	// initialize checking account
	CheckingAccount() = default;

	// deallocate checking account
	~CheckingAccount() override = default;

	// deposit money into account
	bool deposit( bank_sys::US_CENTS deposit_amount ) override;

	// withdraw money from account
	bool withdraw( bank_sys::US_CENTS withdrawal_amount ) override;

	// apply maintenance fee if applicable
	bool applyMaintenanceFee();

private:

	// manage overdraft protection for checking account
	class OverdraftProtection
	{
	public:

		// initialize overdraft limit and fee
		OverdraftProtection() = default;

		// apply overdraft protection if the withdrawal exceeds the current balance,
		// but only if the transaction stays within the specified overdraft limit
		bool applyOverdraftProtection( bank_sys::US_CENTS account_balance,

			bank_sys::US_CENTS withdrawal_amount );

		// get the overdraft fee
		bank_sys::US_CENTS getOverdraftFee() const;

	private:

		// overdraft limit, default limit = $200
		bank_sys::US_CENTS m_overdraft_limit = 20000;

		// overdraft fee, default fee = $25
		bank_sys::US_CENTS m_overdraft_fee = 2500;
	};
	// manage overdraft protection
	OverdraftProtection m_overdraft_protection;

	// account maintenance fee, default fee = $25
	static const bank_sys::US_CENTS sm_ACCOUNT_MAINTENANCE_FEE = 2500;

	// enforces the minimum number of transactions per session to waive fee
	static const unsigned int sm_MIN_TRANSACTIONS_TO_WAIVE_FEE = 10;

	// tracks the total number of transactions during the current session
	unsigned int m_session_transaction_counter = 0;
};

#endif // CHECKING_ACCOUNT_H