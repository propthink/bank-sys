#include "Common.h" // banksys
#include "CheckingAccount.h" // CheckingAccount
#include "SavingsAccount.h" // SavingsAccount
#include "TransactionUtilities.h" // TransactionUtilities
#include <iostream> // std::cout

// unit testing for CheckingAccount

void test_CheckingAccount_DepositValidAmount()
{
	CheckingAccount checking_account;

	if( checking_account.deposit( bank_sys::US_CENTS( 500 ) ) )
	{
		std::cout << "test_CheckingAccount_DepositValidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_CheckingAccount_DepositValidAmount FAILED \n";
	}
}

void test_CheckingAccount_DepositInvalidAmount()
{
	CheckingAccount checking_account;

	if( !checking_account.deposit( bank_sys::US_CENTS( -500 ) ) )
	{
		std::cout << "test_CheckingAccount_DepositInvalidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_CheckingAccount_DepositInvalidAmount FAILED \n";
	}
}

void test_CheckingAccount_WithdrawValidAmount()
{
	CheckingAccount checking_account;

	checking_account.deposit( bank_sys::US_CENTS( 500 ) );

	if( checking_account.withdraw( bank_sys::US_CENTS( 250 ) ) )
	{
		std::cout << "test_CheckingAccount_WithdrawValidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_CheckingAccount_WithdrawValidAmount FAILED \n";
	}
}

void test_CheckingAccount_WithdrawInvalidAmount()
{
	CheckingAccount checking_account;

	if( !checking_account.withdraw( bank_sys::US_CENTS( -250 ) ) )
	{
		std::cout << "test_CheckingAccount_WithdrawInvalidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_CheckingAccount_WithdrawInvalidAmount FAILED \n";
	}
}

void test_CheckingAccount_OverdraftProtectionEngaged()
{
	CheckingAccount checking_account;

	if( checking_account.withdraw( bank_sys::US_CENTS( 500 ) ) )
	{
		std::cout << "test_CheckingAccount_OverdraftProtectionEngaged PASSED \n";
	}
	else
	{
		std::cout << "test_CheckingAccount_OverdraftProtectionEngaged FAILED \n";
	}
}

// unit testing for SavingsAccount

void test_SavingsAccount_DepositValidAmount()
{
	SavingsAccount savings_account;

	if( savings_account.deposit( bank_sys::US_CENTS( 500 ) ) )
	{
		std::cout << "test_SavingsAccount_DepositValidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_SavingsAccount_DepositValidAmount FAILED \n";
	}
}

void test_SavingsAccount_DepositInvalidAmount()
{
	SavingsAccount savings_account;

	if( !savings_account.deposit( bank_sys::US_CENTS( -500 ) ) )
	{
		std::cout << "test_SavingsAccount_DepositInvalidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_SavingsAccount_DepositInvalidAmount FAILED \n";
	}
}

void test_SavingsAccount_WithdrawValidAmount()
{
	SavingsAccount savings_account;

	savings_account.deposit( bank_sys::US_CENTS( 30000 ) );

	if( savings_account.withdraw( bank_sys::US_CENTS( 250 ) ) )
	{
		std::cout << "test_SavingsAccount_WithdrawValidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_SavingsAccount_WithdrawValidAmount FAILED \n";
	}
}

void test_SavingsAccount_WithdrawInvalidAmount()
{
	SavingsAccount savings_account;

	if( !savings_account.withdraw( bank_sys::US_CENTS( -250 ) ) )
	{
		std::cout << "test_SavingsAccount_WithdrawInvalidAmount PASSED \n";
	}
	else
	{
		std::cout << "test_SavingsAccount_WithdrawInvalidAmount FAILED \n";
	}
}

void test_SavingsAccount_MinimumBalanceEngaged()
{
	SavingsAccount savings_account;

	savings_account.deposit( bank_sys::US_CENTS( 25000 ) );

	if( !savings_account.withdraw( bank_sys::US_CENTS( 250 ) ) )
	{
		std::cout << "test_SavingsAccount_MinimumBalanceEngaged PASSED \n";
	}
	else
	{
		std::cout << "test_SavingsAccount_MinimumBalanceEngaged FAILED \n";
	}
}

void test_SavingsAccount_WithdrawalLimitEngaged()
{
	SavingsAccount savings_account;

	savings_account.deposit( bank_sys::US_CENTS( 50000 ) );

	savings_account.withdraw( bank_sys::US_CENTS( 250 ) );

	savings_account.withdraw( bank_sys::US_CENTS( 250 ) );

	savings_account.withdraw( bank_sys::US_CENTS( 250 ) );

	savings_account.withdraw( bank_sys::US_CENTS( 250 ) );

	savings_account.withdraw( bank_sys::US_CENTS( 250 ) );

	savings_account.withdraw( bank_sys::US_CENTS( 250 ) );

	if( !savings_account.withdraw( bank_sys::US_CENTS( 250 ) ) )
	{
		std::cout << "test_SavingsAccount_WithdrawalLimitEngaged PASSED \n";
	}
	else
	{
		std::cout << "test_SavingsAccount_WithdrawalLimitEngaged FAILED \n";
	}
}

// unit testing for TransactionUtilities

//void test_TransactionUtilities_DepositToAccount()
//{
//	CheckingAccount account;
//
//	Vault vault;
//
//	if( TransactionUtilities::depositToAccount( account, vault, 500 ) )
//	{
//		std::cout << "test_TransactionUtilities_DepositToAccount PASSED \n";
//	}
//	else
//	{
//		std::cout << "test_TransactionUtilities_DepositToAccoun FAILED \n";
//	}
//}
//
//void test_TransactionUtilities_WithdrawFromAccount()
//{
//	CheckingAccount account;
//
//	Vault vault;
//
//	account.deposit( 1000 );
//
//	if( TransactionUtilities::withdrawFromAccount( account, vault, 500 ) )
//	{
//		std::cout << "test_TransactionUtilities_WithdrawFromAccount PASSED \n";
//	}
//	else
//	{
//		std::cout << "test_TransactionUtilities_WithdrawFromAccount FAILED \n";
//	}
//}
//
//void test_TransactionUtilities_TransferFromVaultToAccount()
//{
//	CheckingAccount account;
//
//	Vault vault;
//
//	if( TransactionUtilities::withdrawFromAccount( account, vault, 500 ) )
//	{
//		std::cout << "test_TransactionUtilities_TransferFromVaultToAccount PASSED \n";
//	}
//	else
//	{
//		std::cout << "test_TransactionUtilities_TransferFromVaultToAccount FAILED \n";
//	}
//}
//
//void test_TransactionUtilities_TransferFromAccountToVault()
//{
//	CheckingAccount account;
//
//	Vault vault;
//
//	account.deposit( 1000 );
//
//	if( TransactionUtilities::withdrawFromAccount( account, vault, 500 ) )
//	{
//		std::cout << "test_TransactionUtilities_TransferFromAccountToVault PASSED \n";
//	}
//	else
//	{
//		std::cout << "test_TransactionUtilities_TransferFromAccountToVault FAILED \n";
//	}
//}
//
//void test_TransactionUtilities_TransferFromAccountToAccount()
//{
//	CheckingAccount account_1;
//
//	SavingsAccount account_2;
//
//	Vault vault;
//
//	account_1.deposit( 1000 );
//
//	if( TransactionUtilities::transferFromAccountToAccount( account_1, account_2, vault, 500 ) )
//	{
//		std::cout << "test_TransactionUtilities_TransferFromAccountToAccount PASSED \n";
//	}
//	else
//	{
//		std::cout << "test_TransactionUtilities_TransferFromAccountToAccount FAILED \n";
//	}
//}