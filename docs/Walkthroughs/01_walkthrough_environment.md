# Setup Instructions for TDD with C++ and VS Code

## Installed Software

The following should already be installed in the VM.  If interested in setting up the same environment on another machine, the following steps are required.

1. Install Visual Studio Code  
    https://code.visualstudio.com/download
2. Install g++ compiler  
    https://www.msys2.org/
3. Add C/C++ Extension to Visual Studio Code
    * C/C++ 
    * C/C++ Extension Pack
    * C/C++ Themes (optional)
4. Install CMake for Windows  
    https://github.com/Kitware/CMake/releases/download/v3.29.0-rc1/cmake-3.29.0-rc1-windows-x86_64.msi
5. Install Git for Windows  
    https://git-scm.com/downloads
    
---

## Download the class repository
1. Open a command prompt.
2. Change directory to wherever you wish to be working.
3. Clone the class repository.  (You can download the zip and uninstall it if you would rather not clone).
```cmd
git clone https://github.com/schaua/tdd_cpp_code.git
```
4. Each walkthrough has a branch in the repository.  Change to the branch of interest to examine the code.
```cmd
git checkout main
```
5. This is a reference repository.  It is recommended that you work in a parallel local repository and directory structure for your own efforts.  
```cmd
mkdir ../working
cd ../working
git init
```

## Create Test Project
1. Create a new project directory and change to that directory  
    `mkdir firstApp && cd firstApp`
2. Create a source code file named main.cpp that prints 'Hello World!' to the console.    
    ```cpp
    #include <iostream>
    int main(int argc, char** argv)
    {
        std::cout << "Hello World!" << std::endl;
    }
    ```
3. Create a new CMake file named CMakeLists.txt  
    * Add `cmake_minimum_required` to set the CMake version number to the current CMake version or at least 3.10.  
    `cmake_minimum_required(VERSION 3.28)`  
    * Add `project` to set the project name to `FirstApp` and the application's version number to 1.0  
    `project(FirstApp VERSION 1.0)`  
    * Add `CMAKE_CXX_STANDARD` and `CMAKE_CXX_STANDARD_REQUIRED` to set the target language to C++20.  
    `
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    `
    * Add `add_executable` to build the project and pass in the course code file(s).  
    `add_executable(FirstApp main.cpp)

4. Create a sub-directory named build and navigate to that directory.  
    `mkdir build && cd build`

5. Have CMake generate the build system in the current directory.  
    `cmake ../ -G "MinGW Makefiles"`
    * Confirm that the CXX compiler is GNU in the output.  

6. Call the build system to compile and link the project.  
    `cmake --build .`

7. Run the newly build application, which should now be in the current directory.  
    `./FirstApp`

This demonstrates that Visual Studio Code, the C++ compiler and CMake are all set.  

