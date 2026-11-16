#include "kotor/Profile.h"

#include "kotor/Formats.h"

namespace ke::kotor {

namespace {

bool isFile(const std::filesystem::path& path)
{
    return std::filesystem::is_regular_file(path);
}

} // namespace

const char* gameKindName(GameKind kind)
{
    switch (kind) {
    case GameKind::KotOR1: return "kotor1";
    case GameKind::KotOR2: return "kotor2";
    case GameKind::Unknown: return "unknown";
    }
    return "unknown";
}

GameProfile GameProfile::detect(const std::filesystem::path& gameDir)
{
    GameProfile profile;
    const std::filesystem::path chitinkey = gameDir / "chitin.key";
    const std::filesystem::path dialogtlk = gameDir / "dialog.tlk";
    const std::filesystem::path rim001EBO = gameDir / "Modules" / "001EBO.rim";
    const std::filesystem::path rim001ebo = gameDir / "Modules" / "001ebo.rim";
    if (isFile(chitinkey) && (isFile(rim001EBO) || isFile(rim001ebo))) {
        profile.kind = GameKind::KotOR2;
        profile.name = "Knights of the Old Republic II";
        profile.executable = "chitin.key";
        profile.buildSha256 = sha256File(chitinkey);
        profile.recognized = true;
        return profile;
    }
    if (isFile(chitinkey) && isFile(dialogtlk)) {
        profile.kind = GameKind::KotOR1;
        profile.name = "Knights of the Old Republic";
        profile.executable = "chitin.key";
        profile.buildSha256 = sha256File(chitinkey);
        profile.recognized = true;
        return profile;
    }
    profile.name = "not a KotOR install";
    profile.recognized = false;
    return profile;
}

} // namespace ke::kotor
