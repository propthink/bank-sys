#include "TransactionUtilities.h" // implementing TransactionUtilities.h

// user deposits money into their account
// vault gains money, user account gains money
bool TransactionUtilities::depositToAccount(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		// reject invalid deposit
		return false;
	}
	// attempt to add money to the vault
	if( !bank_vault.deposit( deposit_amount ) )
	{
		// vault could not process deposit
		return false;
	}
	// attempt to add money to the user account
	if( !user_account.deposit( deposit_amount ) )
	{
		// roll back funds from the vault
		bank_vault.withdraw( deposit_amount );

		// user account could not process deposit
		return false;
	}
	// log the transaction for the vault
	bank_vault.logVaultTransaction( Transaction(

		user_account.getAccountId(), bank_vault.getVaultId(), deposit_amount ) );

	// log the transaction for the user account
	user_account.logAccountTransaction( Transaction(

		user_account.getAccountId(), deposit_amount ) );

	// transaction successful
	return true;
}

// user withdraws money from their account
// vault loses money, user account loses money
bool TransactionUtilities::withdrawFromAccount(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount is valid
	if( withdrawal_amount <= 0 )
	{
		// reject invalid withdrawal
		return false;
	}
	// attempt to remove money from the vault
	if( !bank_vault.withdraw( withdrawal_amount ) )
	{
		// vault could not process withdrawal
		return false;
	}
	// attempt to remove money from the user account
	if( !user_account.withdraw( withdrawal_amount ) )
	{
		// return funds to the vault
		bank_vault.deposit( withdrawal_amount );

		// user account could not process withdrawal
		return false;
	}
	// log the transaction for the vault
	bank_vault.logVaultTransaction( Transaction(

		bank_vault.getVaultId(), user_account.getAccountId(), -withdrawal_amount ) );

	// log the transaction for the user account
	user_account.logAccountTransaction( Transaction(

		user_account.getAccountId(), -withdrawal_amount ) );

	// check if the user account balance is negative
	if( user_account.getAccountBalance() < 0 )
	{
		// check if there is a valid overdraft fee
		if( user_account.getOverdraftProtectionFee() > 0 )
		{
			// log the overdraft fee transaction for the vault
			bank_vault.logVaultTransaction( Transaction(

				user_account.getAccountId(), bank_vault.getVaultId(), user_account.getOverdraftProtectionFee() ) );

			// log the overdraft fee transaction for the user account
			user_account.logAccountTransaction( Transaction(

				user_account.getAccountId(), bank_vault.getVaultId(), -user_account.getOverdraftProtectionFee() ) );
		}
	}
	// transaction successful
	return true;
}

// bank transfers money to user account (e.g. interest)
// vault loses money, user account gains money
bool TransactionUtilities::transferFromVaultToAccount(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount )
{
	// check if the transfer amount is valid
	if( transfer_amount <= 0 )
	{
		// reject invalid transfer
		return false;
	}
	// attempt to remove money from the vault
	if( !bank_vault.withdraw( transfer_amount ) )
	{
		// vault could not process withdrawal
		return false;
	}
	// attempt to add money to the user account
	if( !user_account.deposit( transfer_amount ) )
	{
		// return funds to the vault
		bank_vault.deposit( transfer_amount );

		// user account could not process deposit
		return false;
	}
	// log the transaction for the vault
	bank_vault.logVaultTransaction( Transaction(

		bank_vault.getVaultId(), user_account.getAccountId(), -transfer_amount ) );

	// log the transaction for the user account
	user_account.logAccountTransaction( Transaction(

		bank_vault.getVaultId(), user_account.getAccountId(), transfer_amount ) );

	// transaction successful
	return true;
}

// user account transfers money to bank (e.g. fees)
// vault gains money, user account loses money
bool TransactionUtilities::transferFromAccountToVault(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount )
{
	// check if the transfer amount is valid
	if( transfer_amount <= 0 )
	{
		// reject invalid transfer
		return false;
	}
	// attempt to add money to the vault
	if( !bank_vault.deposit( transfer_amount ) )
	{
		// vault could not process deposit
		return false;
	}
	// attempt to remove money from the user account
	if( !user_account.withdraw( transfer_amount ) )
	{
		// roll back funds from the vault
		bank_vault.withdraw( transfer_amount );

		// user account could not process withdraw
		return false;
	}
	// log the transaction for the vault
	bank_vault.logVaultTransaction( Transaction(

		user_account.getAccountId(), bank_vault.getVaultId(), transfer_amount ) );

	// log the transaction for the user account
	user_account.logAccountTransaction( Transaction(

		user_account.getAccountId(), bank_vault.getVaultId(), -transfer_amount ) );

	// check if the user account balance is negative
	if( user_account.getAccountBalance() < 0 )
	{
		// check if there is a valid overdraft fee
		if( user_account.getOverdraftProtectionFee() > 0 )
		{
			// log the overdraft fee transaction for the vault
			bank_vault.logVaultTransaction( Transaction(

				user_account.getAccountId(), bank_vault.getVaultId(), user_account.getOverdraftProtectionFee() ) );

			// log the overdraft fee transaction for the user account
			user_account.logAccountTransaction( Transaction(

				user_account.getAccountId(), bank_vault.getVaultId(), -user_account.getOverdraftProtectionFee() ) );
		}
	}
	// transaction successful
	return true;
}

// user account transfers money to user account (e.g. transfer)
// from_account loses money, to_account gains money, no effect on vault
bool TransactionUtilities::transferFromAccountToAccount(

	IAccount& from_account, IAccount& to_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount )
{
	// check if the transfer amount is valid
	if( transfer_amount <= 0 )
	{
		// reject invalid transfer
		return false;
	}
	// attempt to remove money from the source account
	if( !from_account.withdraw( transfer_amount ) )
	{
		// source account could not process withdrawal
		return false;
	}
	// attempt to add money to the destination account
	if( !to_account.deposit( transfer_amount ) )
	{
		// return funds to the source account
		from_account.deposit( transfer_amount );

		// destination account could not process deposit
		return false;
	}
	// log the transaction for the source account
	from_account.logAccountTransaction( Transaction(

		from_account.getAccountId(), to_account.getAccountId(), -transfer_amount ) );

	// log the transaction for the destination account
	to_account.logAccountTransaction( Transaction(

		from_account.getAccountId(), to_account.getAccountId(), transfer_amount ) );

	// check if the user account balance is negative
	if( from_account.getAccountBalance() < 0 )
	{
		// check if there is a valid overdraft fee
		if( from_account.getOverdraftProtectionFee() > 0 )
		{
			// log the overdraft fee transaction for the vault
			bank_vault.logVaultTransaction( Transaction(

				from_account.getAccountId(), bank_vault.getVaultId(), from_account.getOverdraftProtectionFee() ) );

			// log the overdraft fee transaction for the user account
			from_account.logAccountTransaction( Transaction(

				from_account.getAccountId(), bank_vault.getVaultId(), -from_account.getOverdraftProtectionFee() ) );
		}
	}
	// transaction successful
	return true;
}