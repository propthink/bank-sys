#include "Vault.h" // Vault
#include "IAccount.h" // IAccount
#include "CheckingAccount.h" // CheckingAccount
#include "SavingsAccount.h" // SavingsAccount
#include "TransactionUtilities.h" // TransactionUtilities 
#include "User.h" // User
#include <memory> // std::unique_ptr
#include <iostream> // std::cout

//
int main()
{
	// The vault is a simple abstraction meant to represent the funds controlled by the bank.
	// It is only responsible for managing its current balance and logging its transaction history.

	Vault bank_vault;

	// The polymorphic heirarchy of account types is implemented through the IAccount interface.

	// Next, the BAccount abstract base class implements shared functionality across all derived types.

	// Finally, specific derived types like CheckingAccount and SavingsAccount extend the shared 
	// functionality to implement their own unique logical requirements.

	std::unique_ptr< IAccount > checking_account = std::make_unique< CheckingAccount >();

	std::unique_ptr< IAccount > savings_account = std::make_unique< SavingsAccount >();

	// Meanwhile, the TransactionUtilities namespace utilizes several functions to organize transactions
	// between accounts (through the IAccount interface) and/or the vault

	// The accounts and the vault are completely independent, and the TransactionUtilities namespace
	// can operate on all derived types through the IAccount interface, keeping everything modular and scalable

	// The accounts and the vault focus on managing their internal state, while the TransactionUtilities
	// namespace organizes transactions between entities and ensures that everything is logged properly

	// The depositToAccount function adds funds to the vault while making those funds available to the account:

	TransactionUtilities::depositToAccount( *checking_account, bank_vault, bank_sys::US_CENTS( 50000 ) )
		
		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	TransactionUtilities::depositToAccount( *savings_account, bank_vault, bank_sys::US_CENTS( 100000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	// The withdrawFromAccount function removes funds from the vault and makes them unavailable to the account:

	TransactionUtilities::withdrawFromAccount( *checking_account, bank_vault, bank_sys::US_CENTS( 5000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	TransactionUtilities::withdrawFromAccount( *savings_account, bank_vault, bank_sys::US_CENTS( 5000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	// The transferFromVaultToAccount moves funds from the vault to the account, such as for an interest payment:

	TransactionUtilities::transferFromVaultToAccount( *checking_account, bank_vault, bank_sys::US_CENTS( 2000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	TransactionUtilities::transferFromVaultToAccount( *savings_account, bank_vault, bank_sys::US_CENTS( 2000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	// The transferFromAccountToVault moves funds from the account to the vault, such as for an overdraft fee:

	TransactionUtilities::transferFromAccountToVault( *checking_account, bank_vault, bank_sys::US_CENTS( 2500 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	TransactionUtilities::transferFromAccountToVault( *savings_account, bank_vault, bank_sys::US_CENTS( 2500 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	// Finally, transferFromAccountToAccount moves funds between two accounts, which does not affect the vault balance:

	TransactionUtilities::transferFromAccountToAccount( *checking_account, *savings_account, bank_vault, bank_sys::US_CENTS( 10000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	// Derived types can enforce their own requirements for deposit and withdraw logic. For example, checking accounts
	// include overdraft protection to allow negative balances, while savings accounts enforce a strict minimum balance:

		// current balance = $345, withdrawal = $350, final balance = $-30 (including $25 overdraft fee)
		// this transaction is allowed because of overdraft protection
	TransactionUtilities::withdrawFromAccount( *checking_account, bank_vault, bank_sys::US_CENTS( 35000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

		// curent balance = $1045, withdrawal = $1000
		// this transaction is not allowed because of enforced minimum balance requirements
	TransactionUtilities::withdrawFromAccount( *savings_account, bank_vault, bank_sys::US_CENTS( 100000 ) )

		? std::cout << "Transaction successful! \n" : std::cout << "Transaction failed! \n";

	// Accounts can be associated with specific users, and account information (including the complete 
	// transaction history) can be printed to the console:

	User user( User::UserInfo( "joe", "555-5555", "joe@email" ), "password" );

	user.addAccount( std::move( checking_account ) );

	user.addAccount( std::move( savings_account ) );

	user.printUserInfo();

	// Note that TransactionUtilities is able to appropriately indicate the source and destination account 
	// (or vault) for each transaction (or indicate none, in the case of a single-account deposit or withdrawal).

	// The vault can also output its transaction history to the console, including information about the
	// specific accounts involved in its operations:

	// (Note that while they have a similar functionality, the vault is not a type of account, nor does it
	// implement the IAccount interface, because conceptually it is a different entity. This part of the example 
	// is meant to demonstrate the program's ability to track interactions between objects.)

	bank_vault.printVaultInfo();

	return 0;
}