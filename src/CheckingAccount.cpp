#include "CheckingAccount.h" // implementing CheckingAccount.h

// deposit money into account
bool CheckingAccount::deposit( bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		// reject invalid deposit
		return false;
	}
	// update balance
	m_current_balance += deposit_amount;

	// log transaction
	m_transaction_registry.insertTransaction(

		Transaction( BAccount::m_account_id, deposit_amount ) );

	// update session transaction counter
	m_session_transaction_counter += 1;

	// transaction successful
	return true;
}

// withdraw money from account
bool CheckingAccount::withdraw( bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount is valid
	if( withdrawal_amount <= 0 )
	{
		// reject invalid withdrawal
		return false;
	}
	// check if the account has sufficient funds
	if( BAccount::m_current_balance - withdrawal_amount < 0 )
	{
		// check if overdraft protection is applied
		if( !m_overdraft_protection.applyOverdraftProtection( BAccount::m_current_balance, withdrawal_amount ) )
		{
			// unable to apply overdraft protection
			return false;
		}
		// overdraft protection approved, apply fee and log transaction
		m_current_balance -= m_overdraft_protection.getOverdraftFee();

		m_transaction_registry.insertTransaction(

			Transaction( BAccount::m_account_id, -m_overdraft_protection.getOverdraftFee() ) );
	}
	// update balance
	m_current_balance -= withdrawal_amount;

	// log transaction
	m_transaction_registry.insertTransaction(

		Transaction( BAccount::m_account_id, -withdrawal_amount ) );

	// update session transaction counter
	m_session_transaction_counter += 1;

	// transaction successful
	return true;
}

// apply maintenance fee if applicable
bool CheckingAccount::applyMaintenanceFee()
{
	// check if the minimum number of transactions has been met to waive the fee
	if( m_session_transaction_counter >= sm_MIN_TRANSACTIONS_TO_WAIVE_FEE )
	{
		// fee waived
		return false;
	}
	// apply the maintenance fee to the account
	if( !withdraw( sm_ACCOUNT_MAINTENANCE_FEE ) )
	{
		// transaction rejected
		return false;
	}
	// transaction successful
	return true;
}

// apply overdraft protection if the withdrawal exceeds the current balance,
// but only if the transaction stays within the specified overdraft limit
bool CheckingAccount::OverdraftProtection::applyOverdraftProtection( bank_sys::US_CENTS account_balance,

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

// get the overdraft fee
bank_sys::US_CENTS CheckingAccount::OverdraftProtection::getOverdraftFee() const
{
	return m_overdraft_fee;
}