#ifndef UNIT_TEST_H
#define UNIT_TEST_H

// unit testing for CheckingAccount

void test_CheckingAccount_DepositValidAmount();

void test_CheckingAccount_DepositInvalidAmount();

void test_CheckingAccount_WithdrawValidAmount();

void test_CheckingAccount_WithdrawInvalidAmount();

void test_CheckingAccount_OverdraftProtectionEngaged();

// unit testing for SavingsAccount

void test_SavingsAccount_DepositValidAmount();

void test_SavingsAccount_DepositInvalidAmount();

void test_SavingsAccount_WithdrawValidAmount();

void test_SavingsAccount_WithdrawInvalidAmount();

void test_SavingsAccount_MinimumBalanceEngaged();

void test_SavingsAccount_WithdrawalLimitEngaged();

// unit testing for TransactionUtilities

//void test_TransactionUtilities_DepositToAccount();
//
//void test_TransactionUtilities_WithdrawFromAccount();
//
//void test_TransactionUtilities_TransferFromVaultToAccount();
//
//void test_TransactionUtilities_TransferFromAccountToVault();
//
//void test_TransactionUtilities_TransferFromAccountToAccount();

#endif // UNIT_TEST_H