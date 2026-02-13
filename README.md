# vulkan stereoscopy

sample code on how to do stereoscopy (or quadbuffer) in vulkan on Windows

## requirements

- Windows and Visual Studio
- CMake
- Vulkan SDK
- VCPKG
- system compatible with quad-buffered stereo
  - surface capabilities -> `maxImageArrayLayers` must be 2 (or higher?)
  - workstation NVIDIA Quadro/Quadro RTX/RTX cards are known to work
  - 3D must be enabled in Windows display settings
