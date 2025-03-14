#include "CheckingAccount.h" // implementing CheckingAccount.h

// get the overdraft fee associated with the account (if applicable)
bank_sys::US_CENTS CheckingAccount::getOverdraftProtectionFee() const
{
	return m_overdraft_protection.getOverdraftFee();
}

// get the account maintenance fee associated with the account (if applicable)
bank_sys::US_CENTS CheckingAccount::getAccountMaintenanceFee() const
{
	return ( m_session_transaction_counter < sm_MIN_TRANSACTIONS_TO_WAIVE_FEE )

		? sm_ACCOUNT_MAINTENANCE_FEE : 0;
}

// deposit money into the account
bool CheckingAccount::deposit( bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		// reject invalid deposit
		return false;
	}
	// update the account balance
	m_current_balance += deposit_amount;

	// increment transaction counter
	m_session_transaction_counter += 1;

	// deposit valid
	return true;
}

// withdraw money from the account
bool CheckingAccount::withdraw( bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount is valid
	if( withdrawal_amount <= 0 )
	{
		// reject invalid withdrawal
		return false;
	}
	// check if the balance is sufficient
	if( m_current_balance < withdrawal_amount )
	{
		// check if overdraft protection is available
		if( m_overdraft_protection.isActive()

			&& m_overdraft_protection.applyOverdraftProtection( m_current_balance, withdrawal_amount ) )
		{
			// overdraft protection activated
			m_current_balance -= m_overdraft_protection.getOverdraftFee();
		}
		else
		{
			// insufficient balance
			return false;
		}
	}
	// update the account balance
	m_current_balance -= withdrawal_amount;

	// increment transaction counter
	m_session_transaction_counter += 1;

	// withdrawal is valid
	return true;
}

// initialize overdraft protection logic
CheckingAccount::OverdraftProtection::OverdraftProtection(

	bank_sys::US_CENTS overdraft_limit,

	bank_sys::US_CENTS overdraft_fee,

	bool overdraft_protection_active )

	: m_overdraft_limit( overdraft_limit ), m_overdraft_fee( overdraft_fee ),

	m_overdraft_protection_active( overdraft_protection_active ) { }

// apply overdraft protection if the withdrawal exceeds the current balance,
// but only if the transaction stays within the specified overdraft limit
bool CheckingAccount::OverdraftProtection::applyOverdraftProtection(

	bank_sys::US_CENTS account_balance,

	bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount exceeds the account balance
	// while staying within the overdraft limit
	if( account_balance - withdrawal_amount >= -m_overdraft_limit )
	{
		return true; // overdraft protection applied
	}
	return false; // overdraft protection denied
}

// check if overdraft protection is active
bool CheckingAccount::OverdraftProtection::isActive() const
{
	return m_overdraft_protection_active;
}

// get the overdraft fee
bank_sys::US_CENTS CheckingAccount::OverdraftProtection::getOverdraftFee() const
{
	return m_overdraft_fee;
}

// get the text string associated with the account type (for logging purposes)
std::string CheckingAccount::getAccountString() const
{
	return "Checking";
}