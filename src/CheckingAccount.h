#ifndef CHECKING_ACCOUNT_H
#define CHECKING_ACCOUNT_H

#include "Common.h" // bank_sys
#include "BAccount.h" // BAccount

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

	// get the overdraft fee associated with the account (if applicable)
	bank_sys::US_CENTS getOverdraftProtectionFee() const override;

	// get the account maintenance fee associated with the account (if applicable)
	bank_sys::US_CENTS getAccountMaintenanceFee() const override;

	// deposit money into the account
	bool deposit( bank_sys::US_CENTS deposit_amount ) override;

	// withdraw money from the account
	bool withdraw( bank_sys::US_CENTS withdrawal_amount ) override;

	// get the text string associated with the account type (for logging purposes)
	std::string getAccountString() const override;

private:

	// manage overdraft protection logic for the checking account
	class OverdraftProtection
	{
	public:

		// initialize overdraft protection logic
		OverdraftProtection(

			bank_sys::US_CENTS overdraft_limit = 20000,

			bank_sys::US_CENTS overdraft_fee = 2500,

			bool overdraft_protection_active = true
		);

		// apply overdraft protection if the withdrawal exceeds the current balance,
		// but only if the transaction stays within the specified overdraft limit
		bool applyOverdraftProtection(

			bank_sys::US_CENTS account_balance,

			bank_sys::US_CENTS withdrawal_amount );

		// check if overdraft protection is active
		bool isActive() const;

		// get the overdraft fee
		bank_sys::US_CENTS getOverdraftFee() const;

	private:

		// overdraft limit, default limit = $200
		bank_sys::US_CENTS m_overdraft_limit;

		// overdraft fee, default fee = $25
		bank_sys::US_CENTS m_overdraft_fee;

		// overdraft protection is active by default
		bool m_overdraft_protection_active;
	};
	// manage overdraft protection logic for the checking account
	OverdraftProtection m_overdraft_protection;

	// account maintenance fee, default fee = $25
	static const bank_sys::US_CENTS sm_ACCOUNT_MAINTENANCE_FEE = 2500;

	// enforces the minimum number of transactions per session to waive fee
	static const unsigned int sm_MIN_TRANSACTIONS_TO_WAIVE_FEE = 10;

	// tracks the total number of transactions during the current session
	unsigned int m_session_transaction_counter = 0;
};

#endif // CHECKING_ACCOUNT_H