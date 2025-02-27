#include "User.h"
#include <random> // for random number generation

// generates a random, unique user ID
Utils::USER_ID GENERATE_USER_ID()
{
	// get a random seed from the system
	std::random_device random_device;

	// initialize a random number generator with the seed
	std::mt19937 random_generator( random_device() );

	// define the range for generating 6-digit IDs
	std::uniform_int_distribution<> rng_distribution( 100000, 999999 );

	// store the generated user ID for comparison
	Utils::USER_ID new_user_id;

	// keep generating a new user ID until it is unique
	do {
		new_user_id = rng_distribution( random_generator );

		// check if the user ID already exists
	} while( GENERATED_USER_IDS.find( new_user_id ) != GENERATED_USER_IDS.end() );

	// insert the new unique user ID into the set
	GENERATED_USER_IDS.insert( new_user_id );

	// return the newly generated unique user ID
	return new_user_id;
}

// tracks existing user IDs to enforce uniqueness
std::unordered_set< Utils::USER_ID > GENERATED_USER_IDS;

// initialize user data
UserInfo::UserInfo(

	Utils::USER_ID user_id, std::string full_name,

	std::string phone_number, std::string email_address )

	: m_user_id( user_id ), m_full_name( full_name ),

	m_phone_number( phone_number ), m_email_address( email_address ) { }

// initialize user
User::User( const UserInfo& user_info )

	: m_user_info( user_info ) { }

// get the unique id associated with this user
Utils::USER_ID User::getUserId() const
{
	return m_user_info.m_user_id;
}

// add an account to this user
void User::addAccount( std::unique_ptr< IAccount > new_account )
{
	m_user_accounts.push_back( std::move( new_account ) );
}

// initialize node with user
UserNode::UserNode( std::unique_ptr< User > user )

	: m_user( std::move( user ) ), m_next( nullptr ), m_prev( nullptr ) { }

// initialize the user registry
UserRegistry::UserRegistry()

	: m_head( nullptr ), m_tail( nullptr ) { }

// add a user at the end of the list
void UserRegistry::addUser( std::unique_ptr< User > user )
{
	// create a new node to store the user
	auto new_node = std::make_unique< UserNode >( std::move( user ) );

	// if the list is empty...
	if( !m_head )
	{
		// make the new node both the head and tail
		m_head = std::move( new_node );

		m_tail = m_head.get();

	}
	else // add the new node at the end of the list
	{
		// attach the new node to the current tail
		m_tail -> m_next = std::move( new_node );

		// the prev pointer of the new node is the current tail
		m_tail -> m_next -> m_prev = m_tail;

		// update the tail pointer to the newly added node
		m_tail = m_tail -> m_next.get();
	}
}

// search for a user by user id
UserNode* UserRegistry::findUser( Utils::USER_ID user_id )
{
	// start from the head of the list
	UserNode* current_node = m_head.get();

	// iterate through the linked list
	while( current_node )
	{
		// check if the current node's user id matches the target user id
		if( current_node -> m_user.get() -> getUserId() == user_id )
		{
			return current_node; // return the node if the user id matches
		}
		// move to the next node on the list
		current_node = current_node -> m_next.get();
	}
	return nullptr; // return nullptr if user is not found
}