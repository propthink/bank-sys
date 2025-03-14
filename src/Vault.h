#ifndef VAULT_H
#define VAULT_H

#include "Common.h" // bank_sys
#include "Transaction.h" // Transaction
#include "TransactionRegistry.h" // TransactionRegistry

// a central repository for managing the deposit and withdrawal of bank funds
class Vault
{
public:

	// initialize the vault with an initial balance
	Vault( bank_sys::US_CENTS initial_balance = 0 );

	// get the unique id associated with the vault
	bank_sys::ACCOUNT_ID getVaultId() const;

	// get the current balance of the vault
	bank_sys::US_CENTS getVaultBalance() const;

	// deposit money into the vault
	bool deposit( bank_sys::US_CENTS deposit_amount );

	// withdraw money from the vault
	bool withdraw( bank_sys::US_CENTS withdrawal_amount );

	// log a transaction with the vault
	void logVaultTransaction( Transaction&& vault_transaction );

private:

	// the current balance in the vault
	bank_sys::US_CENTS m_current_balance;

	// the transaction history associated with the vault
	TransactionRegistry m_transaction_history;
};

#endif // VAULT_H