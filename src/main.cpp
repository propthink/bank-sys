#include "Vault.h"
#include "IAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "TransactionUtilities.h"

#include <memory> // std::unique_ptr

//
int main()
{
	Vault bank_vault;

	std::unique_ptr< IAccount > checking_account = std::make_unique< CheckingAccount >();

	std::unique_ptr< IAccount > savings_account = std::make_unique< SavingsAccount >();

	TransactionUtilities::depositToAccount( *checking_account, bank_vault, 50000 );

	TransactionUtilities::depositToAccount( *savings_account, bank_vault, 50000 );

	if( checking_account -> calculateInterest() != 0 )
	{
		TransactionUtilities::transferFromVaultToAccount( *checking_account, bank_vault, checking_account -> calculateInterest() );
	}
	if( savings_account -> calculateInterest() != 0 )
	{
		TransactionUtilities::transferFromVaultToAccount( *savings_account, bank_vault, savings_account -> calculateInterest() );
	}
	checking_account -> printAccountInfo();

	savings_account -> printAccountInfo();

	bank_vault.printVaultInfo();
}