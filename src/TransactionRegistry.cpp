#include "TransactionRegistry.h" // implementing

// add a new transaction
void TransactionRegistry::insertTransaction( Transaction&& transaction )
{
	m_transactions.insert( std::move( transaction ) );
}

// print the transaction registry to the console
void TransactionRegistry::printTransactionRegistry() const
{
	m_transactions.forEach(

		[]( const Transaction& transaction ){ transaction.printTransactionInfo(); }
	);
}

// filter the transaction registry by account number
void TransactionRegistry::printFilteredTransactions( bank_sys::ACCOUNT_ID account_id ) const
{
	m_transactions.forEach(

		[ account_id ]( const Transaction& transaction )
		{
			if( transaction.getFromAccountId() == account_id

				|| transaction.getToAccountId() == account_id )
			{
				transaction.printTransactionInfo();
			}
		}
	);
}