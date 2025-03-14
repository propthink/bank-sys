#include "Vault.h" // implementing Vault.h

// initialize the vault with an initial balance
Vault::Vault( bank_sys::US_CENTS initial_balance )

	: m_current_balance( initial_balance ) { }

// get the unique id associated with the vault
bank_sys::ACCOUNT_ID Vault::getVaultId() const
{
	return bank_sys::VAULT_ID;
}

// get the current balance of the vault
bank_sys::US_CENTS Vault::getVaultBalance() const
{
	return m_current_balance;
}

// deposit money into the vault
bool Vault::deposit( bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		// reject invalid deposit
		return false;
	}
	// update the vault balance
	m_current_balance += deposit_amount;

	// deposit valid
	return true;
}

// withdraw money from the vault
bool Vault::withdraw( bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount is valid
	if( withdrawal_amount <= 0 )
	{
		// reject invalid withdrawal
		return false;
	}
	// update the vault balance
	m_current_balance -= withdrawal_amount;

	// withdrawal valid
	return true;
}

// log a transaction with the vault
void Vault::logVaultTransaction( Transaction&& vault_transaction )
{
	m_transaction_history.insertTransaction( std::move( vault_transaction ) );
}