#include "encryption.hpp"

#include <fstream>
#include <sodium/crypto_secretbox.h>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <filesystem>
#include <iostream>

namespace enc
{
	void encrypt_to_file(const std::string& plaintext, const std::string& filepath, const unsigned char key[crypto_secretbox_KEYBYTES])
	{
		//random nonce
		unsigned char nonce[crypto_secretbox_NONCEBYTES];
		randombytes_buf(nonce, sizeof(nonce));

		//ciphertext is plaintext size + MAC overhead
		std::vector<unsigned char> ciphertext(crypto_secretbox_MACBYTES + plaintext.size());	
		crypto_secretbox_easy(ciphertext.data(), reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size(), nonce, key);

		//write nonce + cyphertext to file
		std::ofstream file(filepath, std::ios::binary);
		if(!file) throw std::runtime_error("Could not open file for writing");
		file.write(reinterpret_cast<char*>(nonce), sizeof(nonce));
		file.write(reinterpret_cast<char*>(ciphertext.data()), ciphertext.size());
	}

	std::string decrypt_from_file(const std::string& filepath, const unsigned char key[crypto_secretbox_KEYBYTES])
	{
		std::ifstream file(filepath, std::ios::binary);
		if(!file) throw std::runtime_error("Could not open file for reading");

		// read nonce
		unsigned char nonce[crypto_secretbox_NONCEBYTES];
		file.read(reinterpret_cast<char*>(nonce), sizeof(nonce));

		// read rest as cypherbytes
		std::vector<unsigned char> ciphertext(std::istreambuf_iterator<char>(file), {});
		std::vector<unsigned char> plaintext(ciphertext.size() - crypto_secretbox_MACBYTES);

		if(crypto_secretbox_open_easy(plaintext.data(), ciphertext.data(), ciphertext.size(), nonce, key) != 0)
			throw std::runtime_error("Decryption failed - file altered or incorrect key");

		return std::string(plaintext.begin(), plaintext.end());
	}

	void generate_keyfile(const std::string& keypath)
	{
		unsigned char key[crypto_secretbox_KEYBYTES];
		randombytes_buf(key, sizeof(key));
		std::ofstream file(keypath, std::ios::binary);
		file.write(reinterpret_cast<char*>(key), sizeof(key));
	}

	void load_keyfile(const std::string& keypath, unsigned char key[crypto_secretbox_KEYBYTES])
	{
		if(!std::filesystem::exists(keypath)) generate_keyfile(keypath);

		std::ifstream file(keypath, std::ios::binary);
			if(!file) throw std::runtime_error("Something went really wrong in load_keyfile, key is being generated in unknown location!");
		file.read(reinterpret_cast<char*>(key), crypto_secretbox_KEYBYTES);
	}

	[[nodiscard]]enc::ToonHQLogin fetch_creds(const std::string& keypath, const std::string& credpath)
	{
		enc::ToonHQLogin credentials;

		unsigned char key[crypto_secretbox_KEYBYTES];

		if(!std::filesystem::exists(keypath))
			generate_keyfile(keypath);

		load_keyfile(keypath, key);

		// if the dir doesn't exist, don't load anything
		if(std::filesystem::exists(credpath))
		{
			std::string data = decrypt_from_file(credpath, key);
			size_t delim = data.find('\n');
			credentials.username = data.substr(0, delim);
			credentials.password = data.substr(delim + 1);
		}
		return credentials;
	}

	[[nodiscard]]std::vector<enc::ToontownLogins> fetch_toontownCreds(const std::string& keypath, const std::string& credpath, uint8_t storedCreds)
	{
		std::vector<enc::ToontownLogins> parsed_creds;

		unsigned char key[crypto_secretbox_KEYBYTES];

		if(!std::filesystem::exists(keypath))
			generate_keyfile(keypath);

		load_keyfile(keypath, key);

		// if the dir doesn't exist, don't load anything
		if(std::filesystem::exists(credpath))
		{
			std::string data = decrypt_from_file(credpath, key);
			std::istringstream stream(data);
		
			size_t delim = data.find('\n');
			for(uint8_t i = 0; i < storedCreds; i++)
			{
				ToontownLogins tmp;
				std::getline(stream, tmp.username);
				std::getline(stream, tmp.password);
				std::getline(stream, tmp.alias);
				std::getline(stream, tmp.launcherPath);
				parsed_creds.push_back(tmp);
			}
		}
		return parsed_creds;
	}


	void storeState_toFile(const std::string& filepath)
	{
		if(std::filesystem::exists(filepath)) return;
		else
		{
			std::ofstream state(filepath);
			if(!state.is_open())
				throw std::runtime_error("Failed to create state.bin");
			state.close();
			return;
		}
	}

	//returns true if a state is stored
	bool readState_fromFile(const std::string& filepath)
	{	
		if(std::filesystem::exists(filepath)) return true;
		else
			return false;
	}

	void delete_storeState(const std::string& filepath)
	{
		if(std::filesystem::exists(filepath))
			std::filesystem::remove(filepath);
	}

	void store_numCreds(uint8_t numCredsStored, const std::string& filepath)
	{
		if(!std::filesystem::exists(filepath))
			std::ofstream{filepath};

		std::ofstream file(filepath, std::ios::binary);
		if(!file) throw std::runtime_error("Failed to open " + filepath + " for writing");

		std::cout << "storing numCreds as: " << static_cast<int>(numCredsStored) << '\n';
		file.write(reinterpret_cast<const char*>(&numCredsStored), sizeof(numCredsStored));
		file.close();
	}

	uint8_t read_numCreds(const std::string& filepath)
	{
		if(!std::filesystem::exists(filepath))
			return 0;

		std::ifstream file(filepath, std::ios::binary);
		if(!file) throw std::runtime_error("Failed to open " + filepath + " for reading");

		uint8_t num = 0;
		if(!file.read(reinterpret_cast<char*>(&num), sizeof(num)))
			throw std::runtime_error("Failed to read numCreds");
		
		std::cout << "read num as: " << static_cast<int>(num) << '\n';
		return num;
	}

void encrypt_to_file_append(const std::string& plaintext, const std::string& filepath, const unsigned char key[crypto_secretbox_KEYBYTES])
{
    std::string existing;
    if(std::filesystem::exists(filepath))
        existing = decrypt_from_file(filepath, key);

    existing += plaintext;
    encrypt_to_file(existing, filepath, key);
}

	void remove_from_file( const std::string& keypath, const std::string& credpath, 
			uint8_t storedCreds, uint8_t which_entry, const unsigned char key[crypto_secretbox_KEYBYTES])
	{
		std::vector<ToontownLogins> decrypted = fetch_toontownCreds(keypath, credpath, storedCreds);
		auto it = decrypted.begin() + (which_entry - 1);
		decrypted.erase(it);
		
		std::string plaintext;
		for(const auto& Toon : decrypted)
		{
			plaintext += Toon.username + '\n';
			plaintext += Toon.password + '\n';
			plaintext += Toon.alias + '\n';
			plaintext += Toon.launcherPath + '\n';
		}
		encrypt_to_file(plaintext, credpath, key);
	}

	void update_installPath(const std::string& keypath, const std::string& credpath, uint8_t numCreds,
			uint8_t which_one, const unsigned char* key, const std::string& newpath)
	{
		std::vector<ToontownLogins> all = fetch_toontownCreds(keypath, credpath, numCreds);
		all[which_one - 1].launcherPath = newpath;

		std::string blob;
		for(const auto& e : all)
			blob += e.username + '\n' + e.password + '\n' + e.alias + '\n' + e.launcherPath + '\n';
		
		//overwrite, not append
		encrypt_to_file(blob, credpath, key);
	}

	void write_plaintext(const std::string& filepath, const std::vector<std::string>& trickLabels)
	{
		std::ofstream file(filepath);
		if(!file)
			throw std::runtime_error("Failed to open file for write_plaintext");
		
		for(const auto& trick : trickLabels)
			file << trick << '\n';

		file.close();
	}

	std::vector<std::string> read_plaintext(const std::string& filepath)
	{
		std::vector<std::string> lines;
		std::ifstream file(filepath);
		for (std::string line; std::getline(file, line);)
			 lines.push_back(std::move(line));
		return lines;
	}
}

