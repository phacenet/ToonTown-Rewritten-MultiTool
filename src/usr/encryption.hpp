#pragma once

#include <sodium.h>
#include <string>
#include <vector>


namespace enc
{
	struct ToonHQLogin
	{
		std::string username;
		std::string password;
	};

	struct ToontownLogins
	{
		std::string username;
		std::string password;
		std::string alias;
		std::string launcherPath;
	};


	void encrypt_to_file(const std::string& plaintext, const std::string& filepath, const unsigned char key[crypto_secretbox_KEYBYTES]);
	void encrypt_to_file_append(const std::string& plaintext, const std::string& filepath, const unsigned char key[crypto_secretbox_KEYBYTES]);
	std::string decrypt_from_file(const std::string& filepath, const unsigned char key[crypto_secretbox_KEYBYTES]);
	void generate_keyfile(const std::string& keypath);
	void load_keyfile(const std::string& keypath, unsigned char key[crypto_secretbox_KEYBYTES]);
	void remove_from_file( const std::string& keypath, const std::string& credpath, 
	uint8_t storedCreds, uint8_t which_entry, const unsigned char key[crypto_secretbox_KEYBYTES]);

	[[nodiscard]]ToonHQLogin fetch_creds(const std::string& keypath, const std::string& credpath);
	[[nodiscard]]std::vector<ToontownLogins> fetch_toontownCreds(const std::string& keypath, const std::string& credpath, uint8_t storedCreds);
	
	void storeState_toFile(const std::string& filepath = "config/storeState/state.bin");
	bool readState_fromFile(const std::string& filepath = "config/storeState/state.bin");
	void delete_storeState(const std::string& filepath = "config/storeState/state.bin");
	void update_installPath(const std::string& keypath, const std::string& credpath, uint8_t numCreds,
			uint8_t which_one, const unsigned char* key, const std::string& newpath);

	void store_numCreds(uint8_t numCredsStored, const std::string& filepath = "config/ToontownLogin/numCreds.bin");
	uint8_t read_numCreds(const std::string& filepath = "config/ToontownLogin/numCreds.bin");

	void write_plaintext(const std::string& filepath, const std::vector<std::string>& trickLabels);
	std::vector<std::string> read_plaintext(const std::string& filepath);
}
