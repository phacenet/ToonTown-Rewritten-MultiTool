#include "file_detect.hpp"

#include <vector>
#include <cstdlib>
#include <QDir>

namespace fd
{

std::filesystem::path getHomeDir()
{
    return QDir::homePath().toStdString();
}

bool looksLikeTTREngine(const std::filesystem::path& p)
{
    std::error_code ec;

    if(!std::filesystem::is_regular_file(p, ec) || ec)
        return false;

    std::string filename = p.filename().string();

    #ifdef _WIN32
        if(filename != "TTREngine.exe")
            return false;
    #else
        if(filename != "TTREngine")
            return false;
    #endif

    auto perms = std::filesystem::status(p, ec).permissions();
    if(ec)
        return false;

    bool is_executable = (perms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
                         (perms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
                         (perms & std::filesystem::perms::others_exec) != std::filesystem::perms::none;

    return is_executable;
}
	std::optional<std::filesystem::path> findTTREngineAuto()
	{
		std::filesystem::path home = getHomeDir();
		if(home.empty())
			return std::nullopt;

		std::vector<std::filesystem::path> candidates;

		#ifdef __linux__
			//add more known locations, in order of priority, if i discover more
			candidates = 
			{
				home / ".var/app/com.toontownrewritten.Launcher/data/TTREngine"
			};
		#elif _WIN32
			if(const char* pf86 = std::getenv("ProgramFiles(x86)"))
				candidates.push_back(std::filesystem::path(pf86) / "Toontown Rewritten" / "TTREngine.exe");
			if(const char* pf = std::getenv("ProgramFiles"))
				candidates.push_back(std::filesystem::path(pf) / "Toontown Rewritten" / "TTREngine.exe");
		#endif

		for(const auto& cand : candidates)
		{
			std::error_code ec;
			if(std::filesystem::exists(cand, ec) && looksLikeTTREngine(cand))
				return cand;
		}
		return std::nullopt;
	}
}
