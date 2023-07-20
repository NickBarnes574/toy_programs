# Setting up SDL2 on Ubuntu 20.04

## Installation
Install SDL2 by running the following command in a terminal:
```bash
sudo apt-get install libsdl2-dev
```
NOTE: If you don't already have `cmake`, make sure to install it as well

## Adding the SDL2 Path to your VS Code Workspace
1. Open up the command palette by using `ctrl + shift + p`

2. Search for "C/C++: Edit Configurations (JSON)" and click on it

3. "c_cpp_properties.json" file will be created on your workspace

4. add "/usr/include/SDL2/" to your "c_cpp_properties.json"
    ```json
    {
        "configurations": [
            {
                "name": "Linux",
                "includePath": [
                    "${workspaceFolder}/**",
                    "/usr/include/SDL2/"
                ],
                "defines": [],
                "compilerPath": "/usr/bin/clang-12",
                "cStandard": "c17",
                "cppStandard": "c++14",
                "intelliSenseMode": "linux-clang-x64",
                "configurationProvider": "ms-vscode.cmake-tools"
            }
        ],
        "version": 4
    }
    ```
## Using SDL2 with CMake
You need to create a `CMakeLists.txt` file for your project that includes `SDL2` and compiles a simple program.

```CMake
cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test Main.cpp)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES})
```