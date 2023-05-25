# Mod Template

## Getting Started

### Prerequisites

* **[Visual Studio](https://visualstudio.microsoft.com/downloads/)** - **Make sure to select C++ support in the installer.**
* **[VSNASM](https://github.com/ShiftMediaProject/VSNASM/)**
* **[Python 3](https://www.python.org/downloads/)**
* **[CMake](https://cmake.org/download/)** - ZenovaAPI currently only supports 64-bit

* **Python Packages** - `pip3 install pywin32`

## Changing the Mod Name

**No spaces in the modname**

In the files change Example to your modname

**CMakeLists.txt**
```
set(ModName Example)
```
**resources/modinfo.json**
```
"nameId": "Example"
```

## Building

1. Open the CMake GUI application
2. Click on `Browse Source` and select the folder containing the repository
3. Create a new folder for the build output in the repository folder
4. Click on `Browse Build` and select your build folder
5. Click on `Configure` and select `Visual Studio 20XX` as the generator
6. Choose `x64` as the optional platform
7. After the configuration process finishes, click on `Generate` to create the Visual Studio solution and project files in the build folder
8. Open the solution file in Visual Studio. 
9. Build the project under the `Build` menu and selecting `Build Solution`
10. After the build is complete, the generated files will be placed in the mod folder located at `%zenova_data%/mods/`
