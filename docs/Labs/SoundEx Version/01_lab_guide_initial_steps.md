# Lab 
    NOTE: These lab instructions are based upon a project developing search capabilities.  The steps involved can be applied to any other development, so if there is something that would be more applicable to your future needs, feel free to substitute the specifics.

## Scenario
You are assigned to develop functionality that can improve the user experience when doing searches.  The requirement is to handle those times when the user input is not an actual match with the desired data.  It may include a misspelling, or alternate spelling that still produces useful matches during the search.  
* According to the design documents the Soundex class should encode a word into a letter plus three digits, allowing similar sounding words to be mapped to the same encoding.  

## Technical Requirements
The technical requirements are as listed:
1. Retain the first letter of the word.  Drop all occurrences of *a,e,i,o,u,y,h,w* that are not the first letter.
2. Replace consonants, that are not the first letter, with digits using the following mapping:
    * *b,f,p,v* : **1**
    * *c,g,j,k,q,s,x,z* : **2**
    * *d,t* : **3**
    * *l* : **4**
    * *m,n* : **5**
    * *r* : **6**
3. If two adjacent letters encode to the same number, encode them instead as a single number.  If two letters have the same number and are only separated by *h* or *w*, encode them as a single number.  If two letters have the same number and are only separated by a vowel, encode them twice.  This rule also applies to the first letter.
4. Stop when you have a letter and three digits.  Zero-pad if needed.

## Step 1
Looking over the requirements, what might be a short list of 3-5 To-Do tests that will get us started on the problem?
1. _____________________  
2. _____________________  
3. _____________________  
4. _____________________  
5. _____________________  
Work through this step individually or in a group and try to list one or two simple starting **tests** that we could work on.  
* Identify the test that looks like it would the quickest one to complete.

### Possible Solution
To move forward with this documentation assume that the following will be the first test to look at.  
* Return the first letter, no matter what.  

Seems like a good starting point.

## Step 2
Project Setup  
Use the notes from the slides to set up the project in a specific directory with a CMake file that includes google test.

### Step-by-Step
1. Create a new project directory called *SoundEx* and `cd` into that new directory.
2. Add a *CMakeLists.txt* to the directory that should look something like this:
```bash
cmake_minimum_required(VERSION 3.15...3.28)
set(PROJNAME SoundExProj)
set(CODE_UNDER_TEST SoundExCode)
set(TEST_SPECS SoundExTests)

project(${PROJNAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MY_CODE_UNDER_TEST "src/*.cpp")
file(GLOB_RECURSE MY_TEST_SPECS "test/*.cpp")

add_library(${CODE_UNDER_TEST} STATIC ${MY_CODE_UNDER_TEST})
target_include_directories(${CODE_UNDER_TEST} PUBLIC src/include)
target_compile_features(${CODE_UNDER_TEST} PUBLIC cxx_std_20)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

# For Windows: Prevent overriding the parent project's compiler/linker
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make the fetched content (GoogleTest) available
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(${TEST_SPECS} ${MY_TEST_SPECS})
target_link_libraries(${TEST_SPECS} PUBLIC ${CODE_UNDER_TEST} gtest gmock gtest_main)
include(GoogleTest)
gtest_discover_tests(${TEST_SPECS})
```
3. Add the three sub-directories mentioned in the CMakeLists
* *include*
* *test*
* *src*

## Step 2
Write the first test by adding a file to the *test* directory, adding in code for the first test which will immediately fail.

### Step-by-Step
1. Add *soundextest.cpp* to the test sub-directory.

2. Edit `soundextest.cpp` and add the first failing test for the project.
```cpp
#include <gtest/gtest.h>
TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    Soundex soundex;
}
```
This is immediately a failing (Red) test because there is no *Soundex* class defined in the project.  

3. So now we look at the minimum code necessary to get the test back to passing.  That would be to define the *Soundex* class.  
* Add the *soundex.h* file to the *src/include* sub-directory.
* Edit `soundex.h` and add the class declaration.
```cpp
class Soundex {};
```
The test should now be passing (Green).  Good, but it really doesn't test anything yet.  

4. Expand the current test to better describe the requirement.  
```cpp
#include <gtest/gtest.h>
TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    Soundex soundex;
    auto encoded = soundex.encode("A");
}
```
Once again we have a Red.  The Soundex class has no method named encode that takes a string as an argument and returns something.  The class needs to be updated to get us back to Green.  Before we jump into adding the method, it would be a good idea to consider the design.  What should the return value of the method be?  There is nothing in the test that would require one thing or the other, but the other requirements remind us that the encode is supposed to return the first character and three digits so a string might be worth considering for the return value.  

5. Implement the design for now.  We can always change it 
later if a problem arises.
```cpp
// soundex.h
#ifndef SOUNDEX_H
#define SOUNDEX_H
class Soundex 
{
    std::string encode(const std::string& word) const;
};
#endif

// soundex.cpp
#include <soundex.h>
std::string Soundex::encode(const std::string& word) const
{
    return "";
}
```
Great, now we have the required method and it compiles.  It doesn't return anything interesting yet, but the test hasn't required anything along those lines. 

6. Build the application and confirm that it now compiles.  Back to Green!  
  
The test still needs to be completed from a logic standpoint.  We have the arrange part, and the act part, but we need the assert part of the standard test.  

7. Add ASSERT or EXPECT  
```cpp
#include <gtest/gtest.h>
TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    Soundex soundex;
    auto encoded = soundex.encode("A");
    ASSERT_EQ(encoded, "A");
}
```
The project should still compile just fine, but now when we run the tests we are back to Red.  That is a good thing.  Our encode method does not return the correct results for the test to pass, so now we have a reason to go back to the code to fix that.  Instead of returning an empty string return the expected value, the literal value "A".
```cpp
// soundex.cpp
#include <soundex.h>
std::string Soundex::encode(const std::string& word) const
{
    return "A";
}
```
Now we are back to Green.  The test passes.  As part of the TDD cycle we have gone from Red to Green and all that remains is to eliminate duplication and refactor while making sure that we remain Green.  

8.  Refactoring
* Change any code that is unclear or not easily readable.
* Eliminate duplication.  
In this case the test code seems clear, although adding in comments to separate the *Arrange*, *Act* and *Assert* sections might be useful.  That should have no impact on the tests, but run them anyway to make sure.
```cpp
#include <gtest/gtest.h>
TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    // Arrange
    Soundex soundex;
    // Act
    auto encoded = soundex.encode("A");
    // Assert
    ASSERT_EQ(encoded, "A");
}
```
How about duplication.  We do have a literal *magic* letter that appears in three different places in the code.  In addition, the code currently only works for the letter `A` and that is not the spirit of the test.  
Let's first change the implementation of the method to handle more than just the letter `A`.
```cpp
std::string Soundex::encode(const std::string& word) const
{
    return word;
}
```
For the current test, this will work just fine.  Even if we change the input to some other one-letter word.  Run the tests to make sure our thinking is correct.  

We still have some duplication in the test code itself.  The literal `A` is still repeated.  We can consider refactoring the test some more.
```cpp
#include <gtest/gtest.h>
TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    // Arrange
    Soundex soundex;
    std::string oneLetterWord{"A"};
    // Act
    auto encoded = soundex.encode(oneLetterWord);
    // Assert
    ASSERT_EQ(encoded, oneLetterWord);
}
```
Run all of the tests to make sure that we are still Green.  We have completed our first TDD cycle.  So now we can go back to the To-Do list and find the next test that weeks to be easy for us to implement.  We have the first part of rule #1 working so what is next.  We could continue with the next part of rule #1 but a real easy test sounds like the last part of rule #4.  Padding with zeros seems to follow naturally from the one letter test.

9. Next Test
Write a new failing test that checks for three zeros at the end of a single letter input.
```cpp
TEST(SoundexEncoding, PadsWithZerosToEnsureThreeDigitOutput)
{
    // Arrange
    Soundex soundex;
    std::string oneLetterWord{"I"};
    std::string expected = oneLetterWord + "000";
    // Act
    auto encoded = soundex.encode(oneLetterWord);
    // Assert
    ASSERT_EQ(encoded, expected);
}
```
We are back to Red with a failing test, which means we now have permission to write some code.  In order for the test to pass the `encode` method needs to append three zeros to the end of the one letter word that it is provided as input.  That is the minimal code that is required to get the test to pass.
```cpp
std::string Soundex::encode(const std::string& word) const
{
    return word + "000";
}
```
That was pretty simple.  The second test passes, but we are not back to Green.  This change has caused the first test to fail.  This failure means that we have not correctly interpreted the design requirements.  Let's fix the first test so that we can quickly get back to green and then look at refactoring.  There is a different ASSERT macro available in gmock that will accept different matchers including StartsWith and Eq.  An advantage of this macro is that is almost reads like english and can make the test clear and easy to follow.  ASSERT_THAT(2+2, Eq(4)) meaning assert that two plus two is equal to four. Update the test to check that the `encoded` variable starts with the oneLetterWord.
```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::StartsWith;

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    // Arrange
    Soundex soundex;
    std::string oneLetterWord{"A"};
    // Act
    auto encoded = soundex.encode(oneLetterWord);
    // Assert
    ASSERT_THAT(encoded, StartsWith(oneLetterWord));
}
```
Now we are back to Green and can look at refactoring.  Looking first at the `encode` method we can make this read better to convey the intent.  If we extract that ugly assignment of trailing zeros to a helper function with a descriptive name that can help simplify and clarify the behavior.
```cpp
// soundex.h
class Soundex 
{
public:
std::string encode(const std::string& word) const;
private:
std::string zeroPad(const std::string& word) const;

};
```
```cpp
// soundex.cpp
std::string Soundex::encode(const std::string& word) const
{
    return zeroPad(word);
}
std::string Soundex::zeroPad(const std::string& word) const
{
    return word + "000";
}
```
Still Green, so we can look at refactoring the test as well.  We notice that the way the test is currently written if the `oneLetterWord` is not one letter the test might still pass (check to see if it does) and that would violate the spirit of the test.  Let's add an assert that makes sure the input is only one letter.
```cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using testing::StartsWith;
using testing::Eq;

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord){
    // Arrange
    Soundex soundex;
    std::string oneLetterWord{"A"};
    // Act
    auto encoded = soundex.encode(oneLetterWord);
    // Assert
    ASSERT_THAT(oneLetterWord.length(), Eq(1));
    ASSERT_THAT(encoded, StartsWith(oneLetterWord));
}
```
Run to make sure that we are Green.  Note that there are now two asserts in the first test.  This is generally something to consider a redesign to avoid, but in this case they are testing the same concept.  In addition the way the test is currently written if the first assert fails the test fails. and the second assert is not event tested.  Since the second test only makes sense if the `oneLetterWord` is in fact one letter in length, this is appropriate.  

## Review TDD Thinking 
* Write a small failing test
* Get it to pass
