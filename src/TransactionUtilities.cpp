#include "TransactionUtilities.h" // implementing TransactionUtilities.h
#include "BankingException.h" // custom exception handling for banking functionality

// user deposits money into their account
// vault gains money, user account gains money
void TransactionUtilities::depositToAccount(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS deposit_amount )
{
	// check if the deposit amount is valid
	if( deposit_amount <= 0 )
	{
		throw InvalidTransactionError( "Deposit amount must be greater than 0." );
	}
	// attempt to add money to the vault
	if( !bank_vault.deposit( deposit_amount ) )
	{
		throw VaultTransactionError( "Vault could not process deposit." );
	}
	// attempt to add money to the user account
	if( !user_account.deposit( deposit_amount ) )
	{
		// roll back funds from the vault
		bank_vault.withdraw( deposit_amount );

		throw AccountTransactionError( "Account could not process deposit." );
	}
	// log the transaction for the vault
	bank_vault.logVaultTransaction( Transaction(

		user_account.getAccountId(), bank_vault.getVaultId(), deposit_amount ) );

	// log the transaction for the user account
	user_account.logAccountTransaction( Transaction(

		user_account.getAccountId(), deposit_amount ) );
}

// user withdraws money from their account
// vault loses money, user account loses money
void TransactionUtilities::withdrawFromAccount(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS withdrawal_amount )
{
	// check if the withdrawal amount is valid
	if( withdrawal_amount <= 0 )
	{
		throw InvalidTransactionError( "Withdrawal amount must be greater than 0." );
	}
	// attempt to remove money from the vault
	if( !bank_vault.withdraw( withdrawal_amount ) )
	{
		throw VaultTransactionError( "Vault could not process withdrawal." );
	}
	// attempt to remove money from the user account
	if( !user_account.withdraw( withdrawal_amount ) )
	{
		// return funds to the vault
		bank_vault.deposit( withdrawal_amount );

		if( ( user_account.getAccountBalance() - withdrawal_amount ) < 0 )
		{
			throw InsufficientFundsError( "Insufficient funds for transaction!" );
		}
		else
		{
			throw AccountTransactionError( "Account could not process withdrawal." );
		}
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
}

// bank transfers money to user account (e.g. interest)
// vault loses money, user account gains money
void TransactionUtilities::transferFromVaultToAccount(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount )
{
	// check if the transfer amount is valid
	if( transfer_amount <= 0 )
	{
		throw InvalidTransactionError( "Transfer amount must be greater than 0." );
	}
	// attempt to remove money from the vault
	if( !bank_vault.withdraw( transfer_amount ) )
	{
		throw VaultTransactionError( "Vault could not process withdrawal." );
	}
	// attempt to add money to the user account
	if( !user_account.deposit( transfer_amount ) )
	{
		// return funds to the vault
		bank_vault.deposit( transfer_amount );

		throw AccountTransactionError( "Account could not process deposit." );
	}
	// log the transaction for the vault
	bank_vault.logVaultTransaction( Transaction(

		bank_vault.getVaultId(), user_account.getAccountId(), -transfer_amount ) );

	// log the transaction for the user account
	user_account.logAccountTransaction( Transaction(

		bank_vault.getVaultId(), user_account.getAccountId(), transfer_amount ) );
}

// user account transfers money to bank (e.g. fees)
// vault gains money, user account loses money
void TransactionUtilities::transferFromAccountToVault(

	IAccount& user_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount )
{
	// check if the transfer amount is valid
	if( transfer_amount <= 0 )
	{
		throw InvalidTransactionError( "Transfer amount must be greater than 0." );
	}
	// attempt to add money to the vault
	if( !bank_vault.deposit( transfer_amount ) )
	{
		throw VaultTransactionError( "Vault could not process deposit." );
	}
	// attempt to remove money from the user account
	if( !user_account.withdraw( transfer_amount ) )
	{
		// roll back funds from the vault
		bank_vault.withdraw( transfer_amount );

		if( ( user_account.getAccountBalance() - transfer_amount ) < 0 )
		{
			throw InsufficientFundsError( "Insufficient funds for transaction!" );
		}
		else
		{
			throw AccountTransactionError( "Account could not process withdrawal." );
		}
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
}

// user account transfers money to user account (e.g. transfer)
// from_account loses money, to_account gains money, no effect on vault
void TransactionUtilities::transferFromAccountToAccount(

	IAccount& from_account, IAccount& to_account, Vault& bank_vault, bank_sys::US_CENTS transfer_amount )
{
	// check if the transfer amount is valid
	if( transfer_amount <= 0 )
	{
		throw InvalidTransactionError( "Transfer amount must be greater than 0." );
	}
	// attempt to remove money from the source account
	if( !from_account.withdraw( transfer_amount ) )
	{
		if( ( from_account.getAccountBalance() - transfer_amount ) < 0 )
		{
			throw InsufficientFundsError( "Insufficient funds for transaction!" );
		}
		else
		{
			throw AccountTransactionError( "Account could not process withdrawal." );
		}
	}
	// attempt to add money to the destination account
	if( !to_account.deposit( transfer_amount ) )
	{
		// return funds to the source account
		from_account.deposit( transfer_amount );

		// destination account could not process deposit
		throw AccountTransactionError( "Account could not process deposit." );
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
}