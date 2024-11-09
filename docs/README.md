# Test Driven Development Using C++ and VS Code

These examples illustrate the concepts in TDD development.  Specific walkthroughs are provided to demonstrate writing tests that drive the development of the code.  The examples and challenges are written to run from within Visual Studio Code and use CMake and GCC/G++.  The following setup is suggested.  

## Setup
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

## Frameworks
The setup for the testing framework uses a local copy of the framework to fetch the library from.  This could be modified to the github repository if desired.  Download either or both of the following libraries.

1. Clone GoogleTest
    * https://github.com/google/googletest  
    * Click `<>Code`  
    * Copy HTTPS url  
    * Open a terminal window and navigate to desired location (e.g. `C:\projects\`)      
    * `git clone https://github.com/google/googletest.git`
2. Clone Catch2
    * https://github.com/catchorg/Catch2/tree/devel  
    * Click `<>Code`  
    * Copy HTTPS url  
    * Open a terminal window and navigate to desired location (e.g. `C:\projects\`)  
    * `git clone https://github.com/catchorg/Catch2.git`

## Examples and Challenges

Once the environment is setup the examples provide step by step instructions to walkthrough various concepts.  The challenges have less detailed instructions to allow for some flexibility.

The examples work through a financial calculator application.

### Examples

1. [Setting Up VS Code](./Walkthroughs/01_vs_code_setup_for_cpp.md)
2. [TDD without Framework](./Walkthroughs/02_no_framework_tdd.md)
3. [Project Structure](./Walkthroughs/03_project_structure.md)
4. [Catch2 Installation](./Walkthroughs/04_catch_setup.md)
5. [GoogleTest Installation](./Walkthroughs/05_gtest_setup.md)
6. [Update Tests with gTest](./Walkthroughs/06_update_tests.md)
7. [Triangulation of Behavior](./Walkthroughs/07_triangulation.md)
8. [Refactoring with Fixture](./Walkthroughs/08_fixture_refactoring.md)
9. [Refactoring with Parameters](./Walkthroughs/09_parameterized_refactoring.md)
10. [Handling Exceptions](./Walkthroughs/10_exceptions.md)
11. [Doubles and Mocks](./Walkthroughs/11_doubles_mock.md)
12. [gMock](./Walkthroughs/12_gmock_mock.md)
13. [CI/CD Pipelines](./Walkthroughs/13_gitlab.md)

The challenges are build around a stock portfolio manager application.

### Challenges

1. [Starting TDD Process](./Labs/01_lab_guide_initial_steps.md)
2. [Refactoring Tests](./Labs/02_lab_guide_fixtures.md)
3. [Exception Handling](./Labs/03_lab_guide_exceptions.md)
4. [Mocking Dependencies](./Labs/04_lab_guide_mocks.md)
5. [CI/CD Pipeline](./Labs/05_lab_guide_ci_cd.md)