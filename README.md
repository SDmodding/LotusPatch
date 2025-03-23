# Lotus Patch
- Unofficial patch for Sleeping Dogs: Definitive Edition
- If you encounter an issue or have a request, simply open a new issue and fill out the provided template.

## Installation
1. You will need a compatible [Steam Executable v1.0](https://mega.nz/file/fK5SWARD#1fAWkxAHaKCIMDaJ5XAQKvjs6gK4RCQo5ZlvvtHWtVw). 
2. Download the latest `Release.zip` file from Releases or by [clicking here](https://github.com/SDModding/LotusPatch/releases/latest/download/Release.zip).
3. Extract all files into the game folder.
- Linux Users, add the following to the game's launch options: `WINEDLLOVERRIDES="dinput8=n,b" %command%`.

## Configuration
- You need to create a file named `LotusPatch.ini` inside the game's `plugins` folder.
- All the values shown below are the defaults, so you don’t need to include them in the file to enable/disable them.
```ini
AttachableProps = 1     ; Fixes an issue where attachable props fail to spawn properly.
UmbrellaColors = 1      ; Enables randomized umbrella colors, similar to the original version.
ValveTShirtPack = 1     ; Restores 5 DLC T-Shirts to your wardrobe
SkipIntroScreens = 0    ; Skips legal & intro movies screens.
Borderless = 0          ; Use borderless window mode.
```

## List of Patches
- Game window leaking to a second screen when running in fullscreen mode.
- Mouse 4 button couldn't be binded.
- Attachable props weren't spawning correctly.
- Umbrella Colors were all white and lacked variation.
- Missing Valve T-Shirt Pack DLC, adding five t-shirts to your wardrobe.
- Option to skip legal and intro movie screens.
- Option to use borderless window mode.