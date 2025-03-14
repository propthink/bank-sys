#ifndef TRANSACTION_UTILITIES_H
#define TRANSACTION_UTILITIES_H

#include "Common.h" // bank_sys
#include "IAccount.h" // IAccount
#include "Vault.h" // Vault

// manages low-level transaction logic between program entities
namespace TransactionUtilities
{
	// user deposits money into their account
	// vault gains money, user account gains money
	bool depositToAccount(

		IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS deposit_amount );

	// user withdraws money from their account
	// vault loses money, user account loses money
	bool withdrawFromAccount(

		IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS withdrawal_amount );

	// bank transfers money to user account (e.g. interest)
	// vault loses money, user account gains money
	bool transferFromVaultToAccount(

		IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount );

	// user account transfers money to bank (e.g. fees)
	// vault gains money, user account loses money
	bool transferFromAccountToVault(

		IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount );

	// user account transfers money to user account (e.g. transfer)
	// from_account loses money, to_account gains money, no effect on vault
	bool transferFromAccountToAccount(

		IAccount& from_account, IAccount& to_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount );
}

#endif // TRANSACTION_UTILITIES_H