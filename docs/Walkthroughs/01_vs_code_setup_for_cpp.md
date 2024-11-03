# Setup Instructions for TDD with C++ and VS Code

## Installed Software

The following tools should be installed in the environment.  Details instructions are included in the [README.md](../README.md).

1. Install Visual Studio Code  
2. Install g++ compiler  
3. Add C/C++ Extension Pack to Visual Studio Code
4. Install CMake for Windows  
5. Install Git for Windows  
    
---

## Download this repository
1. Open a command prompt.
2. Change directory to wherever you wish to be working (e.g. `C:\projects\`).
3. Clone the class repository.  (You can download the zip and extract into the project directory if you would rather not clone it).
```cmd
git clone https://github.com/schaua/tdd_cpp_code.git
```
4. The final result of each walkthrough is a branch in the repository.  Change to the branch of interest to examine the code.  Change to the preceding branch as a starting point to code along with the walkthrough. _It is recommended that you create a new branch before you start coding to give a fallback point if needed._
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
7. Also make sure to create a `.gitignore` file before you start work to ignore any of the intermediate output of the build process, and if a shared project, you will likely want to ignore the Visual Studio Code settings as they might be different for each developer.  An example `.gitignore` might look like this:
```
# ignore the build output files
build/   
# ignore the VS Code settings
.vscode/ 
# ignore any executable output
*.exe    
*.dll    
```

## Create Test Application
1. Working in the new _project_ directory just created, open Visaul Studio Code using the current directory as the folder to open.
```
code .
```  
2. Create a new CMake configuration file named `CMakeLists.txt`  
* Add `cmake_minimum_required` to set the CMake version number to the current CMake version or at least 3.10.    

```
cmake_minimum_required(VERSION 3.10...3.28)
``` 
    
* Add `project` to set a variable `PROJNAME` to be used for the project name.  Initialize it to `FirstApp`.  Then define the project using the variable, `${PROJNAME}` along with a version number ` VERSION 1.0` and language `CXX`.  
        
```
set (PROJNAME FirstApp)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
```  
    
* Add `CMAKE_CXX_STANDARD` and `CMAKE_CXX_STANDARD_REQUIRED` to set the target language version to C++20 and require standard C++ syntax.  
    
```
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```
    
* Finally add the executable with  `add_executable`.  This will build the project with the provided name, use the variable again, and pass in the application code file.  This file will be created in the next section.  
    
```
add_executable(${PROJNAME} runner.cpp)
```

The final file would look like this:
```
cmake_minimum_required(VERSION 3.10...3.28)
set (PROJNAME FirstApp)
project(${PROJNAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(${PROJNAME} runner.cpp)
```


3. Create the new C++ application source code file in the project directory and name it `runner.cpp`.

4. Add the `main` function that will be the entry point for the application.  The function will return an `int` and take two arguments.  The first is an `int` for the argument count, and the second is an array of all the command line arguments.  
```cpp
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
```
5. Add code to `main` to print the string `Hello World!` to the console.  This will require adding the standard library header file for `iostream`.
```cpp
#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Hello World!" << std::endl;
    return
}
```
6. Build the make files using CMake.  This it typically triggered by saving changes to the `CMakeLists.txt` file.  The first time it will be neccessary to reload Visual Studio Code to recognize the file. 
- On the `View` menu select `Command Palette...`
- Type `reload` into the textbox
- Select `Developer: Reload Window` from the available options.  
- Then press the `Enter KEY`.
- When prompted select the GCC kit for CMake.

7. The result wil show in the output window.
```
[cmake] -- Build files have been written to: C:/projects/working_copy/build
```
8. Build the application by clicking on the `Build` button in the bottom taskbar of Visual Studio Code.  The results of the build should be:
```
[build] Build finished with exit code 0
```
9. Run the application by clicking on the triangle button in the bottom taskbar just to the right of the Build button.

10. Confirm that the result displays in the terminal window:
```
C:\projects\tdd_app\build>"C:/projects/tdd_app/build/FirstApp.exe"
Hello World!
```


## Summary
Output of "Hello World!" to the terminal indicates that the environment is setup correctly and that we will be able to proceed with the TDD examples and challenges.  The completed code for this walkthrough is in branch `w01`.
