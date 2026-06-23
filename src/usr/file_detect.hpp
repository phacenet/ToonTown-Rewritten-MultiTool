#pragma once
#include <filesystem>
#include <optional>

namespace fd
{
	std::filesystem::path getHomeDir();
	bool looksLikeTTREngine(const std::filesystem::path& p);
	std::optional<std::filesystem::path> findTTREngineAuto();
	std::string retrieve_installLoc_manually();
}
