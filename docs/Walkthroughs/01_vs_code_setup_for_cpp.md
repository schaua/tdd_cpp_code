# Setup Instructions for TDD with C++ and VS Code

## Installed Software

The following should be installed in the environment.  Details instructions are included in the [README.md](../README.md).

1. Install Visual Studio Code  
2. Install g++ compiler  
3. Add C/C++ Extension Pack to Visual Studio Code
4. Install CMake for Windows  
5. Install Git for Windows  
    
---

## Download this repository
1. Open a command prompt.
2. Change directory to wherever you wish to be working (e.g. `C:\projects\`).
3. Clone the class repository.  (You can download the zip and uninstall it if you would rather not clone).
```cmd
git clone https://github.com/schaua/tdd_cpp_code.git
```
4. Each walkthrough has a branch in the repository.  Change to the branch of interest to examine the code.
```cmd
git checkout main
```
5. This is the reference repository.  While you can work in this directory, it is recommended that you create a parallel directory and initialize a local repository for your own efforts.  
```cmd
cd ..
mkdir tdd_app
cd tdd_app
git init
```
6. Make sure that you have set the git configuration to have the user.name and user.email properties set before trying to commit anything into a repository.  You can check using the `git config --global --list` command.

## Create Test Application
1. Working in the new _project_ directory just created, open Visaul Studio Code using the current directory as the folder to open.
```
code .
```  
2. Create a new CMake configuration file named `CMakeLists.txt`  
* Add `cmake_minimum_required` to set the CMake version number to the current CMake version or at least 3.10.    

```
cmake_minimum_required(VERSION 3.28)
``` 
    
* Add `project` to set the project name to `FirstApp` and the application's version number to 1.0 and the language to C++ (CXX);   
        
```
project(FirstApp VERSION 1.0 CXX)
```  
    
* Add `CMAKE_CXX_STANDARD` and `CMAKE_CXX_STANDARD_REQUIRED` to set the target language version to C++20.  
    
```
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```
    
* Add `add_executable` to build the project and pass in the course code file that will be created in the next section.  
    
```
add_executable(FirstApp main.cpp)
```

3. Create a new C++ source code file named `main.cpp`.
4. Add a `main` function that will be the entry point for the application.  
5. Add code to print `'Hello World!'` to the console.    
```cpp
#include <iostream>
int main(int argc, char** argv)
{
    std::cout << "Hello World!" << std::endl;
}
```
6. Build the application using CMake by clicking on the Build button in the bottom status bar.   If the Build is not displayed the reload Visual Studio Code. 
7. Run the newly build application.  In Visual Studio Code click on the run icon in the bottom status bar.

## Summary
Output of "Hello World!" to the terminal indicates that the environment is setup correctly and that we will be able to proceed with the TDD examples and challenges.
