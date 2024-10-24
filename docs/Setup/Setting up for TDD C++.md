# TDD in C++ Setup Instructions
## Setting up **Windows** for **C++**
1. Install Visual Studio Code  
    * https://code.visualstudio.com/download
2. Install Extensions:
    * Open VS Code and navigate to the Extensions view (click on the square icon on the sidebar or use `Ctrl+Shift+X`).
    * Search for and install the following extensions:
        * **C/C++ Extension Pack**: Popular extensions for C++ development in Visual Studio Code.  
2. Install g++ compiler
    * Follow the instructions on this web page  
    * https://code.visualstudio.com/docs/cpp/config-mingw  
    * Step #1 download the installer from MSYS2 page https://www.msys2.org/  
    * Continue with Steps #2 through #7
3. Install CMake for Windows  
    * https://github.com/Kitware/CMake/releases/download/v3.29.0-rc1/cmake-3.29.0-rc1-windows-x86_64.msi  
    * Run the *msi* file.
    * For the install options select *Add CMake to the system PATH for all users*
    * Accept defaults for the remaining settings.
4. Install Git for Windows
    * https://git-scm.com/downloads  
    * Click `Download for Windows`
    * Download the latest version and install with the default settings.
5. Clone GoogleTest
    * https://github.com/google/googletest  
    * Click `<>Code`  
    * Copy HTTPS url  
    * Open a terminal window and navigate to desired location (e.g. C:\GTest)      
    * `git clone https://github.com/google/googletest.git`
6. Clone Catch2
    * https://github.com/catchorg/Catch2/tree/devel  
    * Click `<>Code`  
    * Copy HTTPS url  
    * Open a terminal window and navigate to desired location (e.g. C:\Catch2)  
    * `git clone https://github.com/catchorg/Catch2.git`

## Test Project To Confirm Setup
1. Create a new project directory and change to that directory and open it in VS Code.  
    ```bash
    mkdir firstApp && cd firstApp
    code .
    ```
2. Create a source code file named main.cpp that prints 'Hello World!' to the console.    
    ```cpp
    #include <iostream>
    int main()
    {
        std::cout << "Hello World!" << std::endl;
    }
    ```
3. Press the play button in the top right corner of the editor.
4. Choose *C/C++ g++.exe build and debug active file* from the list of detected compilers.  
5. The output `Hello World!` should appear in the integrated *Terminal* of VS Code.
6. This confirms that Visual Studio Code and the C++ compiler are all set. 
