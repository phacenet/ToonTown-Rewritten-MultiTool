#include "ttr_api_reqs.hpp"

#include <algorithm>
#include <curl/curl.h>
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <optional>
#include <cassert>
#include <filesystem>
#include <QProcess>
#include <string>

// Have to increment nonce, or ToonHQ doesn't accept future calls
static uint64_t nonce = 0;

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userdata)
{
	// Cast contents to char and append it to userdata cast as string
	static_cast<std::string*>(userdata)->append(static_cast<char*>(contents), size * nmemb);
	return size * nmemb;
}

namespace ttr
{
	std::vector<InvasionInformation> fetchInvasions()
	{
		CURL* curl = curl_easy_init();
		curl_slist* list = nullptr;
		CURLcode res;
		std::string bodyBuffer;

		if(curl)
		{
			CURLcode result;
			curl_easy_setopt(curl, CURLOPT_URL, "https://www.toontownrewritten.com/api/invasions"); //set URL for HTTP request
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bodyBuffer);
			res = curl_easy_perform(curl);
			
			if(res != CURLE_OK)
				std::cerr << "printInvasionInfo failed: " << curl_easy_strerror(res);
			else
				std::cout << "printInvasionInfo retrieved: " << bodyBuffer << '\n';


			// ensure no error at start
			auto check_find = [](std::string::size_type result) { if(result == std::string::npos) std::cout << "Search failed inside fetchInvasion"; };
			auto verify_noErr = [&bodyBuffer, &check_find]()->int 
			{
				auto s1 = bodyBuffer.find("null,", 0);
				if(s1 == std::string::npos)
				{
					std::string::size_type cur_pos = 0;
					auto s2 = bodyBuffer.find("\"error\":", cur_pos);
					check_find(s2);
					cur_pos += (s2 + strlen("\"error\":"));
					
					auto s3 = bodyBuffer.find(',', cur_pos);
					check_find(s3);

					std::cout << "Error written as: " << bodyBuffer.substr(cur_pos, (s3 - cur_pos));
					return -1;
				}
				else
					return 0;
			};


			std::string::size_type cur = 0;
			std::vector<InvasionInformation> out;

			// Advance cursor to after token
			auto adv = [&](const std::string& token) -> bool 
			{
				auto pos = bodyBuffer.find(token, cur);
				if (pos == std::string::npos) return false;
				cur = pos + token.length();
				return true;
			};

			// Extract quoted string after key
			auto extract_string = [&](const std::string& key, std::string& outStr) -> bool 
			{
				auto pos = bodyBuffer.find(key, cur);
				if (pos == std::string::npos) return false;
				pos = bodyBuffer.find('"', bodyBuffer.find(':', pos)) + 1;
				auto end = bodyBuffer.find('"', pos);
				outStr = bodyBuffer.substr(pos, end - pos);
				return true;
			};

			// Extract integer after key
			auto extract_uint = [&](const std::string& key, uint64_t& outVal) -> bool 
			{
				auto pos = bodyBuffer.find(key, cur);
				if (pos == std::string::npos) return false;
				pos = bodyBuffer.find(':', pos) + 1;
				outVal = std::stoull(bodyBuffer.substr(pos));
				return true;
			};

			// Move to invasions object
			if (!adv("\"invasions\"")) throw std::runtime_error("Failed adv inside fetchInvasion");
			if (!adv("{")) throw std::runtime_error("Failed adv2 inside fetchInvasion");

			while (true) {
				// ---- Extract district name ----
				auto nameStart = bodyBuffer.find('"', cur);
				if (nameStart == std::string::npos) break;

				auto nameEnd = bodyBuffer.find('"', nameStart + 1);
				if (nameEnd == std::string::npos) break;

				InvasionInformation info;
				info.district = bodyBuffer.substr(nameStart + 1, nameEnd - nameStart - 1);

				cur = nameEnd + 1;

				// ---- Extract fields ----
				extract_uint("\"asOf\"", info.asOf);
				extract_string("\"type\"", info.cogType);

				// strip JSON \uXXXX escape sequences (stray control chars from API)
				std::string cleaned;
				for(size_t j = 0; j < info.cogType.size(); j++)
				{
					 if(info.cogType[j] == '\\' && j + 5 < info.cogType.size() && info.cogType[j + 1] == 'u')
					 {
						  j += 5; // skip \uXXXX
						  continue;
					 }
					 cleaned += info.cogType[j];
				}
				info.cogType = cleaned;

				// progress: "8884/9373"
				{
					std::string prog;
					extract_string("\"progress\"", prog);

					auto slash = prog.find('/');
					info.current = std::stoi(prog.substr(0, slash));
					info.total   = std::stoi(prog.substr(slash + 1));
				}

				extract_uint("\"startTimestamp\"", info.startTimestamp);
				out.push_back(info);

				// Move to next entry
            auto nextBrace = bodyBuffer.find('}', cur);
            if (nextBrace == std::string::npos) break;
					cur = nextBrace + 1;

            // check if hit the end of the invasions object
            auto nextChar = bodyBuffer.find_first_not_of(" \t\n\r", cur);
            if (nextChar == std::string::npos || bodyBuffer[nextChar] == '}')
					break;
			}

			curl_easy_cleanup(curl);
			return out;
		}

		throw std::runtime_error("curl_easiy_init inside fetchInvasions failed");
	}


	//----------------------------------------------------------------------------------------
	//ToonHQ specific code related to logins/group creation
	//----------------------------------------------------------------------------------------
	[[nodiscard]] std::string extract_token(std::string SearchBuffer, const char *key)
	{
		auto start_csrf = SearchBuffer.find(key);
		auto end_csrf = SearchBuffer.find(';', start_csrf);
		std::string csrftoken = SearchBuffer.substr(start_csrf + strlen(key), (end_csrf - (start_csrf + strlen(key))));
		return csrftoken;
	}

		[[nodiscard]] std::string retrieve_csrftoken()
		{
			CURL * curl = curl_easy_init();
			if(!curl) throw std::runtime_error("Failed to initialize CURL in subscribe_boarding");
			std::string headerBuffer;

			curl_easy_setopt(curl, CURLOPT_URL, "https://toonhq.org/");
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerBuffer);
			CURLcode res = curl_easy_perform(curl);

			if(res != CURLE_OK)
				std::cerr << "retrieve_csrftoken failed: " << curl_easy_strerror(res);
			else
				std::cout << "retrieve_csrftoken retrieved: " << headerBuffer << '\n';
			
			curl_easy_cleanup(curl);
			return ttr::extract_token(headerBuffer, "csrftoken=");
		}

	/* Parse the JSON return from the CURL to pull ToonInformation to select which Toon's ID should be used
	 * Other information is just for making selection easy - probably don't know each toons' ID without other info
	 * */
	std::vector<ttr::ToonHQToonInformation> extract_tooninfo(std::string bodyBuffer)
	{
		auto check_pos = [](std::string::size_type pos) {assert(pos != std::string::npos && "Failure in check_pos\n");};
		
		auto toons_pos = bodyBuffer.find("\"toons\":[{");
		check_pos(toons_pos);
		auto begin_parse_pos = bodyBuffer.find("\"id\":");
		check_pos(begin_parse_pos);

		size_t prev_e_pos = begin_parse_pos;

		// Intentionally non const ref
		auto extract = [&](std::vector<ttr::ToonHQToonInformation>& tooninfo) -> bool
		{
			ttr::ToonHQToonInformation toon_x;

			auto pull_info = [&](const std::string& key) -> std::string
			{
				auto find_pos = bodyBuffer.find(key, prev_e_pos);
				check_pos(find_pos);

				auto next_pos = bodyBuffer.find(':', find_pos);
				check_pos(next_pos);
				next_pos += 1;

				auto end_pos = bodyBuffer.find(',', next_pos);
				check_pos(end_pos);
				prev_e_pos = end_pos;

				//removing quotes around certain values
				if(bodyBuffer.at(next_pos) == '\"')
					return bodyBuffer.substr(next_pos + 1, (end_pos - next_pos) - 2);
				return bodyBuffer.substr(next_pos, end_pos - next_pos);
			};

				toon_x.ToonID = std::stoi(pull_info("\"id\""));
				toon_x.game = std::stoi(pull_info("\"game\""));
				toon_x.ToonName = pull_info("\"name\"");
				toon_x.ToonLaff = std::stoi(pull_info("\"laff\""));
				toon_x.ToonPhotoURL = pull_info("\"photo\"");

				tooninfo.push_back(toon_x);

				prev_e_pos = bodyBuffer.find("},{", prev_e_pos);
				if(prev_e_pos != std::string::npos)
					return true;
					
				return false;
		};

		std::vector<ttr::ToonHQToonInformation> tooninfo;
		while(extract(tooninfo));

		return tooninfo;
	}


	[[nodiscard]] std::optional<ttr::ToonHQLoginResult> login_request(const std::string &orig_csrftoken, 
			const std::string &username, const std::string &password)
	{
		CURL * curl = curl_easy_init();
		if(!curl) throw std::runtime_error("Failed to initialize CURL in subscribe_boarding");
		struct curl_slist *curl_headers = nullptr;
		std::string headerBuffer;
		std::string bodyBuffer;

		std::string x_csrftoken = "X-CSRFTOKEN: " + orig_csrftoken;
		std::string json_body = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"id\":null}";
		std::string cookie = "csrftoken=" + orig_csrftoken;

		curl_headers = curl_slist_append(curl_headers, x_csrftoken.c_str());
		curl_headers = curl_slist_append(curl_headers, "Origin: https://toonhq.org");
		curl_headers = curl_slist_append(curl_headers, "Content-Type: application/json;charset=utf-8");
		curl_headers = curl_slist_append(curl_headers, orig_csrftoken.c_str());
		curl_headers = curl_slist_append(curl_headers, x_csrftoken.c_str());

		curl_easy_setopt(curl, CURLOPT_URL, "https://toonhq.org/api/accounts/login/");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerBuffer);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bodyBuffer);
		CURLcode res = curl_easy_perform(curl);

		if(res != CURLE_OK)
		{
			curl_slist_free_all(curl_headers);
			curl_easy_cleanup(curl);
			return std::nullopt;
		}
		else
		{
			std::cout << "retrieve_csrftoken retrieved: " << headerBuffer << '\n';
		
			long http_code = 0;
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

			curl_slist_free_all(curl_headers);
			curl_easy_cleanup(curl);

			if(http_code != 200)
				return std::nullopt;

			std::cout << "LOGIN headerBuffer, right before extract_tokens: headerBuffer: " << headerBuffer << '\n';

			ttr::ToonHQLoginResult login_struct;
			login_struct.csrftoken = ttr::extract_token(headerBuffer, "csrftoken=");
			login_struct.sessionid = ttr::extract_token(headerBuffer, "sessionid=");
			login_struct.toonlist = ttr::extract_tooninfo(bodyBuffer);

			return login_struct;
		}
	}
	//----------------------------------------------------------------------------------------
	bool subscribe_boarding(const ToonHQLoginResult& login_struct, const ToonHQToonInformation& selectedToon, const std::string& websocket_sid)
	{
		CURL * curl = curl_easy_init();
		if(!curl) throw std::runtime_error("Failed to initialize CURL in subscribe_boarding");
		struct curl_slist *curl_headers = nullptr;
		std::string readBuffer;

		std::string x_csrftoken = "X-CSRFTOKEN: " + login_struct.csrftoken;
		std::string csrftoken = "csrftoken=" + login_struct.csrftoken;
		std::string sessionid = "sessionid=" + login_struct.sessionid;
		std::string toonid = std::to_string(selectedToon.ToonID);
		std::string cookie_compl = csrftoken + "; " + sessionid;

		curl_headers = curl_slist_append(curl_headers, x_csrftoken.c_str());
		curl_headers = curl_slist_append(curl_headers, "Origin: https://toonhq.org");
		curl_headers = curl_slist_append(curl_headers, "Content-Type: application/json;charset=utf-8");
		std::string json_body = "{\"toon\":" + toonid + ",\"sid\":\"" + websocket_sid + 
			"\",\"request\":\"subscribe\",\"nonce\":" + std::to_string(nonce++) + "}";

		curl_easy_setopt(curl, CURLOPT_URL, "https://toonhq.org/api/groups/boarding_request/");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, cookie_compl.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		CURLcode res = curl_easy_perform(curl);

		long http_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		std::cout << "subscribe_boarding HTTP " << http_code << ": " << readBuffer << '\n';

		if(res != CURLE_OK)
			std::cerr << "subscribe_boarding failed: " << curl_easy_strerror(res);
		else
			std::cout << "subscribe_boarding response: " << readBuffer << '\n';
		
		curl_slist_free_all(curl_headers);
		curl_easy_cleanup(curl);
			
		return http_code == 200;
	}

	//----------------------------------------------------------------------------------------
	void create_group(int type, int district, int location, const std::string &options, int num_players, 
			const ToonHQLoginResult& login_struct, const ToonHQToonInformation& selectedToon)
	{
		std::string x_csrftoken = "X-CSRFTOKEN: " + login_struct.csrftoken;
		std::string csrftoken = "csrftoken=" + login_struct.csrftoken;
		std::string sessionid = "sessionid=" + login_struct.sessionid;
		std::string toonid = std::to_string(selectedToon.ToonID);
		std::string cookie_compl = csrftoken + "; " + sessionid;

		CURL * curl = curl_easy_init();
		if(!curl) throw std::runtime_error("Failed to initialize CURL in subscribe_boarding");
		struct curl_slist *curl_headers = nullptr;
		std::string readBuffer;

		curl_headers = curl_slist_append(curl_headers, x_csrftoken.c_str());
		curl_headers = curl_slist_append(curl_headers, "Origin: https://toonhq.org");
		curl_headers = curl_slist_append(curl_headers, "Content-Type: application/json;charset=utf-8");
		std::string json_body = "{\"toon\":" + toonid + ",\"type\":" + std::to_string(type) +
										 ",\"district\":" + std::to_string(district) +
										 ",\"location\":" + std::to_string(location) +
										 ",\"options\":" + options +
										 ",\"max_players\":null,\"num_players\":" + std::to_string(num_players) +
										 ",\"note\":null,\"id\":null,\"game\":1}";

		curl_easy_setopt(curl, CURLOPT_URL, "https://toonhq.org/api/groups/create/");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_headers);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body.c_str());
		curl_easy_setopt(curl, CURLOPT_COOKIE, cookie_compl.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		CURLcode res = curl_easy_perform(curl);

		long http_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		std::cout << "create_group HTTP " << http_code << ": " << readBuffer << '\n';

		if(res != CURLE_OK)
			std::cerr << "create_group failed: " << curl_easy_strerror(res);
		else
			std::cout << "create_group response: " << readBuffer << '\n';
		
		curl_slist_free_all(curl_headers);
		curl_easy_cleanup(curl);
	}
	//----------------------------------------------------------------------------------------

	// Intentionally not taking by const reference or reference
	sio::client *link_information(ToonHQLoginResult login_struct, ToonHQToonInformation selected_toon, 
			std::function<void(bool)> onsubscribeResult)
	{
		// Heap alloc so not destroyed on return
		sio::client *client = new sio::client();

		std::map<std::string, std::string> ws_headers;
		ws_headers["Cookie"] = "csrftoken=" + login_struct.csrftoken + "; sessionid=" + login_struct.sessionid;
		std::cout << "DEBUG ws_headers Cookie: " << ws_headers["Cookie"] << "]\n";
		ws_headers["Origin"] = "https://toonhq.org";

		client->set_socket_open_listener([=](std::string const& nsp)
				{
					client->socket(nsp)->on("boarding_created", [=](sio::event& ev)
							{
								std::cout << "[EVENT] boarding_created received\n";
								auto data = ev.get_message()->get_map();
								int type = (int)data["type"]->get_int();
								int district = (int)data["district"]->get_int();
								int location = (int)data["location"]->get_int();
								int num_players = (int)data["num_players"]->get_int();

								//Build options JSON string from map
								std::string options = "{";
								auto opts = data["options"]->get_map();
								bool first = true;
								for(auto& kv : opts)
								{
									if(!first) options += ",";
										options += "\"" + kv.first + "\":" + std::to_string(kv.second->get_int());
									first = false;
								}
								options += "}";
								std::cout << "Creating group: type=" << type << " district=" << district
									<< " location=" << location << " options=" << options << '\n';
								ttr::create_group(type, district, location, options, num_players, login_struct, selected_toon);
							});
							
							client->socket(nsp)->on("boarding_destroyed", [](sio::event& ev)
									{
										std::cout << "[EVENT] boarding_destroyed received: " << ev.get_message()->get_string() << '\n'; 
									});

							client->socket(nsp)->on("group_updated", [](sio::event& ev)
									{
										std::cout << "[EVENT] group_updated received\n";
										auto msg = ev.get_message();
										if(msg->get_flag() == sio::message::flag_object)
										{
											auto map = msg->get_map();
											for(auto& kv : map)
											{
												std::cout << " key: " << kv.first << '\n';
											}
										}
									});
			
							client->socket(nsp)->on("group_deleted", [](sio::event& ev)
									{
										std::cout << "[EVENT] group_deleted received\n";
									});

							std::string sid = client->get_sessionid();
							std::cout << "sid: " << sid << '\n';
							bool subscribed = ttr::subscribe_boarding(login_struct, selected_toon, sid);
							if(onsubscribeResult)
								onsubscribeResult(subscribed);
				});

		client->set_open_listener([]()
				{
					std::cout << "Websocket open\n";
				});
		client->set_close_listener([](sio::client::close_reason const& reason)
		{
			 std::cout << "[SIO] Connection closed, reason: " << (int)reason << "\n";
		});

		client->set_fail_listener([]()
		{
			 std::cout << "[SIO] Connection FAILED\n";
		});

		client->set_reconnect_listener([](unsigned attempt, unsigned delay)
		{
			 std::cout << "[SIO] Reconnecting, attempt " << attempt << ", delay " << delay << "ms\n";
		});


		client->set_logs_verbose();
		client->connect("https://toonhq.org", {{"protocol", "3"}}, ws_headers);
		return client;
	}

	[[nodiscard]]ToontownLoginInformation toonLauncher_retrieveResponse(const std::string& username, const std::string& password)
	{
    CURL* curl = curl_easy_init();
    curl_slist* headers = nullptr;
    CURLcode res;
    std::string responseBody;

    curl_easy_setopt(curl, CURLOPT_URL, "https://www.toontownrewritten.com/api/login?format=json");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseBody);

    // URL-encode the credentials before building the body
    char* escUser = curl_easy_escape(curl, username.c_str(), 0);
    char* escPass = curl_easy_escape(curl, password.c_str(), 0);
    std::string body = std::string("username=") + escUser + "&password=" + escPass;
    curl_free(escUser);
    curl_free(escPass);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)body.size());

    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "Accept-Language: en-US");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        throw std::runtime_error("Failed to retrieve response body inside toonLauncher_retrieveResponse");

    int status = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
    std::cout << "HTTP status: " << status << '\n';
    std::cout << responseBody << '\n';

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);


	if(status != 200)
		return ToontownLoginInformation{.error_info = {.HTTP_code = status, .errorMsg = "HTTP Request Error"}};

	ToontownLoginInformation filled_struct;

	auto verify_find = [](std::string::size_type response, const std::string& searchParam = "")
	{
		if(response == std::string::npos)
			throw std::runtime_error("Extraction failed, optional identifier: " + searchParam);
	};

	auto extract_token = [&](const std::string& token)
	{
		//{"success":"true","gameserver":"gameserver.toontownrewritten.com:7198","cookie":"QdOzKzke1bCQzFTtphM4AtsZrIbNxBFuqrC35NsJnIDz8","manifest":"/content/patchmanifest.txt"}
		auto absStartPos = responseBody.find(token, 0);
		verify_find(absStartPos, "absStart");
		auto firstQuotPos = responseBody.find('\"', absStartPos);
		verify_find(firstQuotPos, "firstQuotPos");
		
		auto parseBeginPos = responseBody.find('\"', firstQuotPos + 1);
		verify_find(parseBeginPos, "parseBegin");
		auto parseEndPos = responseBody.find('\"', parseBeginPos + 1);
		verify_find(parseEndPos, "parseEnd");

		return responseBody.substr(parseBeginPos + 1, (parseEndPos - parseBeginPos)-1);
	 };


	auto status_validate_JSON = [&]()
	{
		//{"success":"false","banner":"Incorrect username and/or password."}
		if(extract_token("success") != "true")
			filled_struct.error_info.errorMsg = extract_token("banner");
	};


	status_validate_JSON();
	if(!filled_struct.error_info.errorMsg.empty())
		return filled_struct;

	filled_struct = 
	{
		.gameServer = extract_token("gameserver"), 
		.playCookie = extract_token("cookie") 
	};
	return filled_struct;
	}

	bool launch_toontown(const std::string& enginePath, const std::string& gameserver, const std::string& cookie)
	{
		 QProcess proc;
		 proc.setProgram(QString::fromStdString(enginePath));
		 proc.setWorkingDirectory(QString::fromStdString(
			  std::filesystem::path(enginePath).parent_path().string()));

		 QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
		 env.insert("TTR_GAMESERVER", QString::fromStdString(gameserver));
		 env.insert("TTR_PLAYCOOKIE", QString::fromStdString(cookie));
		 proc.setProcessEnvironment(env);
		 proc.setStandardOutputFile(QProcess::nullDevice());
		 proc.setStandardErrorFile(QProcess::nullDevice());

		 return proc.startDetached();
	}

	int estimateSecondsRemaining(const InvasionInformation& inv_info)
	{
		int64_t elapsed = inv_info.asOf - inv_info.startTimestamp;
		if(elapsed <= 0 || inv_info.current <= 0) return -1; //no data

		double rate = static_cast<double>(inv_info.current) / elapsed;
		int remaining = static_cast<int>((inv_info.total - inv_info.current) / rate);
		return std::max(remaining, 0);
	}

	std::string formatTime(int seconds)
	{
		if(seconds < 0) return "??:??";
		int m = seconds / 60;
		int s = seconds % 60;
		char buf[16];
		std::snprintf(buf, sizeof(buf), "%d:%02d", m, s);
		return buf;
	}

}


