#include "FileSystem.h"

namespace Engine::Files
{
#ifdef DESKTOP
    static const std::filesystem::path ASSETS = "Assets";
    static const std::filesystem::path LOGS = "Logs";
    static const std::filesystem::path LOG = "Logs/Log.txt";
#endif

#ifdef WUEHANS
    static const std::filesystem::path ASSETS = "/Assets";
    static const std::filesystem::path LOGS = "/Logs";
    static const std::filesystem::path LOG = "/Logs/Log.txt";
#endif
}