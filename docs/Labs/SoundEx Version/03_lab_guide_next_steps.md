# Lab
1. Choosing the next test
Looking at the To-Do list the next candidate for a test looks like rule #2 that describes how to replace consonants with digits after processing the first letter.  We can start with any of those letters in the first group, so `b` is as good as any, perhaps more so since it is the first in the list, and requires less through about why we chose it.  

The following steps run through one possible choice for the next test to write.

2. We write a new small failing test.
```cpp
TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
}
```
We are back to Red again and need to fix that.  We could add an if statement that checks for "Ab" and returns "A100", but that is not moving us forward towards the desired solution.  Not every word will be "Ab" and we don't want some huge nexted if structure adding complexity to the solution.
```cpp
std::string Soundex::encode(const std::string word) const
{
    auto encoded = word.substr(0,1);
    if (word.length() > 1)
    {
        encoded += "1";
    }
    return zeroPad(encoded);
}
```
But the test still fails.  It turns out that the result coming back is "A1000" instead of "A100".  

3. We need to fix the zeroPad logic to get back to Green.
```cpp
std::string Soundex::zeroPad(const std::string& word) const{
    auto zerosNeeded = 4 - word.length();
    return word + std::string(zerosNeeded, '0');
}
```
Now we are back to Green and can look at further clean up.  Looking at the `encode` method it could be made easier to ready.  If we consider the purpose is to keep the first character and numerically encode the rest we can re-write the method to make that more obvious and greatly simplify the `encode` method itself.  
```cpp
std::string Soundex::encode(const std::string word) const
{
    return zeroPad(firstChar(word) + encodedDigits(word));
}
```
4. This requires the addition of two more helper functions.
```cpp
// soundex.h
class Soundex 
{
public:
    std::string encode(const std::string& word) const;
private:
    std::string zeroPad(const std::string& word) const;
    std::string firstChar(const std::string& word) const;
    std::string encodedDigits(const std::string& word) const;
};
```
5. Implement the two helper functions in `soundex.cpp`
```cpp
    std::string Soundex::firstChar(const std::string& word) const
    {
        return word.substr(0,1);
    }

    std::string Soundex::encodedDigits(const std::string& word) const
    {
        if (word.length() > 1)
        {
            return 1;
        }
        return "";
    }
```
6. Now the refactoring has provided an `encode` method that reads more like the requirements itself.  There are still a few refactoring changes that we might consider like replacing the magic number for the overall length of the zero padded string with a more descriptive constant instead of the literal value of `4`.
```cpp
// soundex.h
static const size_t MaxCodeLength{4};

// soundex.cpp
std::string Soundex::zeroPad(const std::string& word) const{
    auto zerosNeeded = MaxCodeLength - word.length();
    return word + std::string(zerosNeeded, '0');
}
```

7. Now we want to drive the conversion of the `encode` behavior to something that is more general and will handle different words.  This could be done with a new test, but if we look at the concept behind the `ReplacesConsonantsWithAppropriateDigits` this lays out our goal fairly well.  Normally the preference is one assert per test, but by adding a second assert to this test we can drive the update to the `encode` method
```cpp
TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    ASSERT_THAT(soundex.encode("Ab"), Eq("A100"));
    ASSERT_THAT(soundex.encode("Ac"), Eq("A200"));
}
```
8. There is a slight problem here.  If both of these tests fail, we would like to know it, so we need to change the first assert from the `ASSERT_THAT` macro to instead use the `EXPECT_THAT` version. This will still cause the overall test to fail, but will not prevent the second part of the test from running as well.  This will provide use with better feedback.
```cpp
TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    ASSERT_THAT(soundex.encode("Ac"), Eq("A200"));
}
```
These could both be written as `EXPECT_THAT` without any problems, and might be a better solution just in case a third case needs to be incorporated as well.
```cpp
TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    EXPECT_THAT(soundex.encode("Ab"), Eq("A100"));
    EXPECT_THAT(soundex.encode("Ac"), Eq("A200"));
}
```
9. Add minimal code to get back to Green will be to add an if statement to the `encodedDigits` method.
```cpp
std::string Soundex::encodedDigits(const std::string& word) const
{
    if (word.length() > 1)
    {
        if (word[1] == 'b') return "1";
        else if (word[1] == 'c') return "2";
    }
    return "";

}
```

10. Back to Green and time to refactor.  We can extract the tests for the character to a new helper function named `encodedDigit` that takes a character and returns the encoding.  (Adding the declaration to the soundex.h file as well.)
```cpp
// soundex.h
std::string encodedDigit(char letter) const;

// soundex.cpp
std::string Soundex::encodedDigits(const std::string& word) const
{
    if (word.length() > 1)
    {
        return encodedDigit(word[1]);
    }
    return "";
}

std::string Soundex::encodedDigit(char letter) const
{
    if (letter == 'b') return "1";
    else if (letter == 'c') return "2";
}
```

11. Now we're back to Green, so lets push the generalized solution a bit further.  Add a third case to the `ReplacesConstantsWithAppropriateDigits` test.
```cpp
    EXPECT_THAT(soundex.encode("Ad"), Eq("A300"));
```

12. We would continue with the `else if` approach but it might be more flexible to create a map between the character and the returning digit. Let's update `encodeDigit` to include a map of the encodings and return the value as long as the key was found.
```cpp
std::string Soundex::encodedDigit(char letter) const
{
    const std::unordered_map<char, std::string> encodings {
        {'b', "1"}, 
        {'c', "2"}, 
        {'d', "3"}};
    auto search = encodings.find(letter);
    if (search != encodings.end()) return search->second;
    return "";
}
```

13. Back to Green.  We could keep see-sawing back and forth, but it can be argued that it is a reasonable step to add in the actual mapping from the requirements at this point and that no additional asserts are required to drive that change.
```cpp
std::string Soundex::encodedDigit(char letter) const
{
    const std::unordered_map<char, std::string> encodings {
        {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"}, 
        {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"}, 
        {'d', "3"},{'t', "3"},
        {'l', "4"},
        {'m', "5"},{'n', "5"},
        {'r', "6"},
        };
    auto search = encodings.find(letter);
    if (search != encodings.end()) return search->second;
    return "";
}
```

14. Confirm that we are still Green and then look at the test.  Do we really need three asserts to remain confident that the rule is being met?  Probably not, so lets eliminate two of them, set the remaining back to `ASSERT_THAT` and choose a different value, just as a bonus to boost our confidence.
```cpp
TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}
```
15. So we're are all set.  Clear clean code and a test to cover it.  However, there is a possibility that the value passed in as the word does not follow the happy path of being alphabetic characters.  The design needs to think about what the response should be in those cases.  
That is not really part of the current direction, so let's place that on the To-Do list for future consideration and move on to the next step in encoding the happy path.
The encode should work with multiple consonants.
```cpp
TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
    ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}
```

16. Looking at the `encode` method, this looks pretty complicated.  Perhaps if we refactor encode it can be made simpler.  STOP!  Refactoring is only allowed when we have come back to Green.  We should not refactor in order to write a new test.  We like the idea behind this test, but in order to refactor while Green we need to disable it temporarily.  That could be done by commenting it out, or we can take advantage of the `DISABLED_` prefix to ask Google Test to skip over this one.
```cpp
TEST_F(SoundexEncoding, DISABLED_ReplacesMultipleConsonantsWithDigits)
{
    ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}
```
17. Now we are back to Green, with an information message that one test is currently disabled.  Great, let's take a look at `encode` and see how we want to refactor.  Perhaps if we only send the remaining characters of the word along to `encodedDigits` that will make life easier.
```cpp
std::string Soundex::encode(const std::string& word) const
{
    return zeroPad(firstChar(word) + encodedDigits(remainingChars(word)));
}

std::string Soundex::remainingChars(const std::string& word) const
{
    return word.substr(1);
}

std::string Soundex::encodedDigits(const std::string& word) const
{
    if (word.empty()) return "";
    return encodedDigit(word.front());
}
```
18. Okay.  We're still Green after refactoring and can re-enable the test, which will now fail.  So let's handle multiple consonants in `encodedDigits`.
```cpp
std::string Soundex::encodedDigits(const std::string& word) const
{
    if (word.empty()) return "";
    std::string encoding{};
    for (auto letter: word) encoding += encodedDigit(letter);
    return encoding;
}
```
19. Back to Green and ready to refactor out the check for an empty word.  If the word is empty the returned encoding will also be empty, just like we want.
```cpp
std::string Soundex::encodedDigits(const std::string& word) const
{
    std::string encoding{};
    for (auto letter: word) encoding += encodedDigit(letter);
    return encoding;
}
```
20. Still Green!  Let's move on to the next test.  How about limiting the output to four characters.  That sounds reasonably easy.
```cpp
TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
    ASSERT_THAT(soundex.encode("Dcrfd").length(), Eq(4u));
}
```
21. This fails like we wanted, but not because the test logic failed.  There is an exception thrown during testing.  The framework captures that and reports it as a test failure.  In this case the problem is in `zeroPad`.  We are ending up with a negative number for creating a new string to concatenate the zeros.  We can modify `zeroPad` or perhaps a better solution is to modify `encodedDigits` to stop once it has encoded enough letters.
```cpp
std::string Soundex::encodedDigits(const std::string& word) const
{
    std::string encoding{};
    for (auto letter: word) 
    {
        if (encoding.length() == MaxCodeLength - 1) break;
        encoding += encodedDigit(letter);
    }
    return encoding;
}
```
22. Back to Green, but the if statement isn't that clear what the intent is so lets refactor that to be cleaner.
```cpp
        if (isComplete(encoding)) break;
```

23. And add the isComplete helper method.
```cpp
bool Soundex::isComplete(const std::string& encoding) const
{
    return encoding.length() == MaxCodeLength - 1;
}
```
Clean and Green!
