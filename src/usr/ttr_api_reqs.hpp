#pragma once

#include <string>
#include <cstdint>
#include <vector>
#include <optional>
#include <curl/curl.h>
#include <sio_client.h>


namespace ttr
{
	struct ToonHQToonInformation
	{
		bool activeConnection = false;
		bool m_badLoad = false;
		uint32_t ToonID;
		int game;
		std::string ToonName;
		int ToonLaff;
		std::string ToonPhotoURL;
	};

	struct ToonHQLoginResult
	{
		std::string csrftoken;
		std::string sessionid;
		std::vector<ToonHQToonInformation> toonlist;
	};

	struct Opt_Error
	{
		int HTTP_code;
		std::string errorMsg;
	};

	struct ToontownLoginInformation
	{
		std::string gameServer;
		std::string playCookie;
		Opt_Error error_info;
	};

	struct InvasionInformation
	{
		std::string district;
		std::string cogType;
		int current;
		int total;
		uint64_t startTimestamp;
		uint64_t asOf;
	};

	std::vector<InvasionInformation> fetchInvasions();
	[[nodiscard]] std::string extract_token(std::string SearchBuffer, const char *key);
	[[nodiscard]] std::string retrieve_csrftoken();
	std::vector<ToonHQToonInformation> extract_tooninfo(std::string bodyBuffer);
	[[nodiscard]] std::string extract_token(std::string SearchBuffer, const char *key);
	[[nodiscard]] std::optional<ToonHQLoginResult> login_request(const std::string &orig_csrftoken, 
			const std::string &username, const std::string &password);

		void create_group(int type, int district, int location, const std::string &options, int num_players, 
			const ToonHQLoginResult& login_struct, const ToonHQToonInformation& selectedToon);
		bool subscribe_boarding(const ToonHQLoginResult& login_struct, const ToonHQToonInformation& selectedToon, const std::string& websocket_sid);
		sio::client *link_information(ToonHQLoginResult login_struct, ToonHQToonInformation selected_toon, 
			std::function<void(bool)> onsubscribeResult = nullptr);

		[[nodiscard]]ToontownLoginInformation toonLauncher_retrieveResponse(const std::string& username, const std::string& password);

		bool launch_toontown(const std::string& enginePath, const std::string& gameserver, const std::string& cookie);

		int estimateSecondsRemaining(const InvasionInformation& inv_info);
		std::string formatTime(int seconds);

}
