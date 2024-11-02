# Non-failing tests

This exercise steps through on approach to dealing with a non-failing test.

1. Let's take a look at the part of rule #1 that says to drop any of the letters `a,e,i,o,u,w,h,y` unless they are the first letter.  A test for that can now be written.
```cpp
TEST_F(SoundexEncoding, IgnoresVowelListLetters)
{
    ASSERT_THAT(soundex.encode("Aeiouwhybcdx"), Eq("A123"));
}
```
This test passed immediately.  Perhaps it is not necessary.  But the test proves that we satisfy a particular portion of rule #1, and it is possible that in the future we may break that and needs this test to catch it for us.  So let's leave it in place and move on to the next rule.  
> Generally the TDD principle is to write a failing test.  The fact that this passed immediately might indicate that we are not taking small enough steps, and should consider our future moves carefully.  If this becomes a common occurrence we should look at taking smaller incremental steps.
*NOTE: At first I was just returning `second` from the result of `find` on the `map` which in fact threw an exception when this test was added.  That caused me to refactor the `encodedDigit` to check that find was actually successful.*

2. Continuing the process.  We have the encoding started, but if two letters result in the same encoding we are supposed to mash those together into a single digit.  Create the next test.
```cpp
TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
    ASSERT_THAT(soundex.encode("Apvxztd"), Eq("A123"));
}
```
3. We are back to Red since this test fails since this current returns "A112".  Before we get into fixing the code, we might want to fix the test.  It is not clear here that the pairs of letters equate to the same encoding.  We could add in some pre-condition tests that communicate this to the reader.  Something like the following:  
```cpp
TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
    // Pre-condition tests prove the encodings are the same
    // Encodes as "A100"
    ASSERT_THAT(soundex.encode("Ap"), Eq(soundex.encode("Av")));
    // Encodes as "A200"
    ASSERT_THAT(soundex.encode("Ax"), Eq(soundex.encode("Az")));
    // Encodes as "A300"
    ASSERT_THAT(soundex.encode("At"), Eq(soundex.encode("Ad")));
    // Final test to drive the development
    ASSERT_THAT(soundex.encode("Apvxztd"), Eq("A123"));
}
```
4. You can experiment with this structure by setting one of the pre-condition tests to fail.  Also consider whether these pre-condition tests should be `EXPECT_THAT` or `ASSERT_THAT`.  If one of them fails then the final test is nonsense.  
5. So we are back to Red for the new test and need to update the code under test.
```cpp
std::string encodedDigits(const std::string& word) const
{
    std::string encoding{};
    for (auto letter : word)
    {
        if (isComplete(encoding)) break;
        if (encodedDigit(letter) != lastDigit(encoding))
        {
            encoding += encodedDigit(letter);
        }
    }
    return encoding;
}
```
6. Back to Green, but I am starting to see duplication everywhere.  Here we call `encodedDigit` twice with the same argument.  We could refactor that out at this point.
```cpp
std::string encodedDigits(const std::string& word) const
{
    std::string encoding{};
    for (auto letter : word)
    {
        if (isComplete(encoding)) break;
        auto proposedDigit = encodedDigit(letter);
        if (proposedDigit != lastDigit(encoding))
        {
            encoding += proposedDigit;
        }
    }
    return encoding;
}
```
7. Refactored and still Green.  

## New Requirements?
8. While working on the tests, the question has come up about case sensitivity.  We have been assuming that the first letters is upper-case and that the remaining letters are lower-case.  After all, the `encodings` map only uses lower-case keys.  Is this the desired behavior.  
9. Look back over the requirements.  Does it say anything about case at all? <span style='color:red;'>*No*</span>  
10. Do we make the assumption and this is an error and adding in case to the solution? <span style='color:red;'>*Not without checking back with the Product Owner*</span>  
11. So this gets added to the To-Do list and must be addressed later.  We definitely need to address this as currently upper-case letters will be ignored by `encodedDigit`.  
12. Let's assume that we get a quick answer back that the first letter of the encoding should always be upper-case and the remaining letters need to be case insensitive so the 'B' and 'b' both encode the same.  We can start with a test for the latter part of this ruling.
```cpp
TEST_F(SoundexEncoding, EncodingIsCaseInsensitive)
{
    ASSERT_THAT(soundex.encode("ABCD"), Eq(soundex.encode("Abcd")));
}
```
13. This fails because `encodings` only has lower-case keys.  Modify the code to convert the letter to lower before doing the search.
```cpp
    auto search = encodings.find(tolower(letter));
```
14. Now the test passes and we can move on the the first part of the new ruling.  That the first character is always uppercase after encoding.  Notice that we don't even care what the rest of the encoding looks like for this test.
```cpp
TEST_F(SoundexEncoding, UppercaseFirstLetter)
{
    ASSERT_THAT(soundex.encode("bcdf"), StartsWith("B"));
}
```
15. Back to Red, so we need to update `firstChar` to upper-case the first letter every time.
```cpp
std::string Soundex::firstChar(const std::string& word) const
{
    auto firstCharacter = word.substr(0,1);
    firstCharacter[0] = toupper(firstCharacter[0]);
    return firstCharacter;
}
```
16. While we are refactoring now that it is Green again we can modify the `UppercaseFirstLetter` to also confirm that even if the first letter is a vowel, it is correctly returned as uppercase.
```cpp
TEST_F(SoundexEncoding, UppercaseFirstLetter)
{
    ASSERT_THAT(soundex.encode("ecdf"), StartsWith("E"));
}
```
17. That brings up another question.  What happens if there are more than two digits in a row that are the same.  According to the rules we want them to compress into a single digit.  Let's add a test for that while we are Green.
```cpp
TEST_F(SoundexEncoding, ThreeOrMoreMatchingEncodingsCompressToSingleDigit)
{
    ASSERT_THAT(soundex.encode("bfpvcgjdt"), Eq("B123"));
}
```
18. We are going off script a little here.  This test passes without any additional code needing to be written.  So we did not first write a failing test, like TDD recommends, yet this is an important requirement and we should leave the test as part of the test suite.

## Vowel separation rule

19. Now what about the part of rule #3 that says that if two encodings are the same **AND** are separated by a vowel (not *h* or *w*) that we repeat the encoding.  Let's write a test for that.
```cpp
TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByAVowel){
    ASSERT_THAT(soundex.encode("Abibchc"), Eq("A112"));
}
```
20. Back to Red.  We are getting "A120" instead of "A112" for this encoding.  We are going to need to modify `encodedDigits` to pay attention not only to the letter being encoded, but to the letter that precedes it.  Is it a vowel then we don't compress the encodings.  This is going to change the logic in `encodedDigits` since we need the index that we so we can get adjacent letters and we need to start with the first letter when comparing, not just the remaining letters.  That means the call to `encodeDigits` will change as well.  Remember, make small changes and test along the way to make sure that we are keeping to the requirements.
```cpp
std::string Soundex::encodedDigits(const std::string& word) const
{
    std::string encoding{};
    for (auto i = 1u; i < word.length(); i++)
    {
        if (!isComplete(encoding))
            encodeLetter(encoding, word[i], word[i-1]);
    }
    return encoding;
}
void Soundex::encodeLetter(std::string& encoding, char letter, char lastLetter) const
{
    auto digit = encodedDigit(letter);
    if (digit != "" && (digit != lastDigit(encoding) || isVowel(lastLetter)))
        encoding += digit;
}

bool Soundex::isVowel(char letter) const
{
    return std::string("aeiouy").find(tolower(letter)) != std::string::npos;
}
```
21. And update the `encode` method to call encodedDigits passing the entire word, and not just the remaining characters since we need to look back at the first character and process the second character.
```cpp
std::string Soundex::encode(const std::string& word) const
{
    return zeroPad(firstChar(word) + encodedDigits(word));
}
```
22. Back to Green, but we can refactor now.  We are not using `remainingChars` any more and can delete that method.

## What is next?
What tests are we missing?  What other scenarios might we can to consider?  Where to go from here?  All good questions, but for now we can look at the Soundex class that we have created with some confidence that is meeting all of these requirements, because we have the tests to prove it.  
