#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string> // std::string

// handles user authentication to lock/unlock user based on password evaluation
class Authenticator
{
public:

	// initialize the authenticator with the plain text password
	Authenticator( const std::string& password_text );

	// returns true if the authenticator is locked
	bool isLocked() const;

	// unlocks the authenticator by comparing the input password to the user password
	bool unlock( const std::string& password_attempt );

	// manually locks the authenticator
	void lock();

private:

	// authenticator is locked by default
	bool m_locked = true;

	// salt used for hashing
	std::string m_password_salt;

	// store the hashed password in the authenticator
	std::string m_password_hash;
};

#endif // AUTHENTICATOR_H