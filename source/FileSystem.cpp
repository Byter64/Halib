#include "FileSystem.h"

namespace Engine::Files
{
#ifdef DESKTOP
    static const std::filesystem::path ASSETS = "Assets";
#endif

#ifdef WUEHANS
    static const std::filesystem::path ASSETS = "/Assets";
#endif
}