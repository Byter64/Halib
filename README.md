# Halib is coming, Morty!

# Changelog
## v3.0
- Added: .wav support (only for RIFF container)
- Added: Abstraction layer for audio
- Added: Halib::audiosystem
- Added: Sprite::ResetAnimation() function

- Removed: Fetch of json library (not needed)

- Fixed: target framerate could not be set higher than 30 fps on Desktop
- Fixed: Leftover functions for abandoned tilemap feature had not been removed
- Fixed: wrong path to fetch Hall repo

## v2.0
- Added: Halib::SetTargetFramerate(...)
- Added: Halib::Update(), which updates inputs, deltaTime, all entities and draws all of them
- Added: Halib::Entity class
- Added: Halib::GetButtonDown, GetButtonPressed, GetbuttonReleased
- Added: Halib::Sprite
- Added: Halib::Camera
- Added: Math.h
- Added: Vectors (VecI2, Vec3, etc.) as typedefs from GLM
- Added: wrapper functions for glm vector operations in Halib namespace

- Updated: Hall version from v1.0 to v2.1.1

## v1.0

- Added Graphic.h for graphic related classes and functions
- Added Font support through freetype
- Added Color class
- Added GetTimeSinceStartup function (System.h)
- Added basic control flow functions (System.h)
- Added basic Draw functions for Images, Text and color indexed images
- Added bmp file support for Image class
- Added Image class
- Added README.md
