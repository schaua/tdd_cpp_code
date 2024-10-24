# Part 1 - Custom Mock Walkthrough
Consider the following scenario for a Stock Quote Application.  

A StockTickerService is needed.  It should use an http connection to obtain a stock quote for our application.  The use of an actual http connection would make the test less reliable in that it could fail for reasons other than the code being wrong.  This situation is an excellent opportunity to use a double to help isolate the test and make it more reliable and repeatable.  

An important aspect of this walkthrough is to emphasize the use of TDD to drive the development of code, including the code for the test itself.  

To accomplish this:  
- Build frequently
- Identify failure
- Address each failure in order to proceed to the next step  

The first approach will be to use a custom double, later we will add in a mocking framework.

The code for this walkthrough will be added as a sub-directory of the current project.  The existing CMakeLists.txt will work fine.

1. Setup create a subfolder under `src` named `stocks`.

2. Write a custom double by writing a test.  (This is TDD so we start with the test, of course.)  

3. Create the preliminary test specification in the `test` directory in a file named `stockQuoteTests.cpp`.  The object under test should take a network connection as a constructor argument.

```cpp
// stockQuoteTests.cpp
#include <gtest/gtest.h>
#include "../include/stocktickerservice.h"

TEST(StockQuoteTest, MakeRequestReturnsQuote)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};
    StockTickerService serviceUnderTest(http);
}
```
4. This won't compile since StockTickerService is not yet defined.  Add the StockTickerService to `src/include/stocktickerservice.h` and include this header file in `stockQuoteTests.cpp`.

```cpp
// stocktickerservice.h
class StockTickerService{};
```

5. The compiler is still complaining because there is no constructor that takes the `http` reference.  Update the constructor for `StockTickerService`.

```cpp
// stocktickerservice.h
class StockTickerService 
{
public:
    StockTickerService(Http& http){}
};
```
6. There are still compiler errors because Http is undefined.  Add the missing type in a header file in `src/include`.
```cpp
class Http
{

};
```
7. This still won't compile since an instance of http is not available in the test context.  Change the test from TEST to TEST_F to take advantage of a fixture that can provide the http reference to each test.  This will drive the creation of a fixture class. Add `StockQuoteService` as the fixture class to the `test` directory.  It will provide the Http connection to the tests.  We don't want to provide the production http reference, so for testing provide an HttpStub.

```cpp
// stockquotetest.h
#include <gtest/gtest.h>
#include <http.h> // defines Http

class StockQuoteTest : public testing::Test
{
    public:
    HttpStub http;
};
```
8. This now requires the definition of the HttpStub class for testing.
```cpp
#include <http.h>
class HttpStub : public Http
{

};
```

This should get us back to Green and we can continue working on the test.  

9. Add in a call to `getQuote` on the `serviceUnderTest` instance passing the `validUrl` returning a string.  
```cpp
#include <gtest/gtest.h>
#include <stocktickerservice.h>
#include "stockquotetest.h"

TEST_F(StockQuoteTest, MakeRequestReturnsQuote)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};
    StockTickerService serviceUnderTest{http};
    std::string quote = serviceUnderTest.getQuote(validUrl);
}
```
10. Back to Red which drives the addition of `getQuote` to the `StockTickerService` class.

```cpp
// src/stocktickerservice.h
class StockTickerService
{
public:
    StockTickerService(Http http) {}
    std::string getQuote(const std::string& url) const { 
        return "";
    }
};
```
11. Back to Green, so we can complete this test by adding the assert that the quote returned matches the expected value.
```cpp
#include <gtest/gtest.h>
#include <stocktickerservice.h>
#include "stockquotetest.h"

TEST_F(StockQuoteTest, MakeRequestReturnsQuote)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};
    StockTickerService serviceUnderTest(http);
    std::string quote = serviceUnderTest.getQuote(validUrl);
    ASSERT_EQ(quote, "42.0");
}
```

The build is clean at this point, and we have completed the basic logic of the test.  Run the first test.  

13. It fails since `getQuote` simply returns and empty string.  To get quickly back to Green, modify `getQuote` to return `"42.0"`.

```cpp
std::string getQuote(const std::string& url) const { return "42.0";}
```
This compiles and passes the test.  Great, but the application is not doing what it is supposed to do, which is call a url to get the quote.  Time to refactor.

14. Modify `getQuote` to use the `http` reference passed to the constructor to call the `get` method passing the `url` argument and returning the result.  This will drive the addition of the field of type `Http&` to the `StockTickerService` and initialize the reference in the constructor.

```cpp
class StockTickerService 
{
public:
    StockTickerService(Http& http):http(http){}
    std::string getQuote(const std::string& url) const { return http.get(url);}
private:
    Http& http;
};
```
15. This will drive the definition of the `get` method on the `Http` interface.
```cpp
class Http 
{
public:
    virtual std::string get(const std::string& url) const = 0;
};
```
16. That will require `HttpStub` to override the pure virtual function.

```cpp
class HttpStub : public Http
{
public:
    std::string get(const std::string& url) const override
    {
        return "42.0";
    }
};
```
That eliminates the compiler error. And the test once more passes.

The `HttpStub` class is a stub for the production version of `Http` that will retrieve resources based upon a URL, but that either is not yet available, or is being provided through a double to keep the unit test isolated.

# Part 2 - Using Mock Tools 
Another option, instead of spending time writing our own double classes is to  use mocking tools like those provided by existing frameworks.  

Here we will look at Google Mock (gmock) as an example.  We already include gmock in the list of libraries that our application links to.

1. The testing starts out in about the same way, with a test.  

```cpp
TEST_F(StockQuoteTest, DifferentSymbolsReturnDifferentResults)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};

    StockTickerService serviceUnderTest(http);
}
```
This compiles due to the work with the fixture from Part 1.  

Now we are going to use the gmock library.  

2. Modify the test to add an `EXPECT_CALL` macro that looks for a call to the `get` method of the `http`.

```cpp
TEST_F(StockQuoteTest, DifferentSymbolsReturnDifferentResults)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};

    StockTickerService serviceUnderTest(http);
    EXPECT_CALL(http, get(validUrl)).WillOnce(Return "42.0");
}
```

This causes an error like the following.  

```sh
error: 'class HttpStub' has no member named 'gmock_get'
   19 |     EXPECT_CALL(http, get(validUrl)).WillOnce(Return "42.0");
```
This error is because `EXPECT_CALL` is looking for *gmock_get* and the `HttpStub` has not defined the mock method.  

3. Edit the `HttpStub` class and use `MOCK_METHOD` define a mock `get` method instead of actually define it.  

```cpp
class Http // API for the production service
{
    public:
    virtual std::string get(const std::string& url) const { return "0.0";}
};

class HttpStub : public Http // stub to mock the production service
{
    public:
    MOCK_METHOD(std::string, get, (const std::string&), (const, override));
};
```
4. This breaks the earlier test, which will need to be modified to use the EXPECT_CALL macro as well.  Make that fix and confirm that only the new test is still failing.  We haven't made a call to `getQuote` yet.  Add that to the test.  The `stockQuoteTests.cpp` should look something like this.
```cpp
TEST_F(StockQuoteTest, MakeRequestReturnsQuote)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};
    StockTickerService serviceUnderTest(http);
    EXPECT_CALL(http, get(validUrl)).WillOnce(Return("42.0"));
    std::string quote = serviceUnderTest.getQuote(validUrl);
    ASSERT_EQ(quote, "42.0");
}

TEST_F(StockQuoteTest, DifferentSymbolsReturnDifferentResults)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};

    StockTickerService serviceUnderTest(http);
    EXPECT_CALL(http, get(validUrl)).WillOnce(Return ("42.0"));
    std::string quote = serviceUnderTest.getQuote(validUrl);
    ASSERT_EQ(quote, "42.0");
}
```
5. Now the tests pass, and we have used the gmock macros to generate a mock object to represent the `Http` interface that returns the string "42.0" when its `get` method is called.  

The new test still has a problem in that it doesn't do what the name says.  

6. We need to make a second call to `getQuote` and confirm that a different value is returned.

```cpp
TEST_F(StockQuoteTest, DifferentSymbolsReturnDifferentResults)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};

    StockTickerService serviceUnderTest(http);
    EXPECT_CALL(http, get(validUrl)).WillOnce(Return ("42.0"));
    std::string quote = serviceUnderTest.getQuote(validUrl);
    validUrl = "https://www.stockprices.are.us.com?sym=bmw";
    std::string quote2 = serviceUnderTest.getQuote(validUrl);
    ASSERT_EQ(quote, "42.0");
    ASSERT_EQ(quote2, "7.0");
}
```
This fails because we haven't trained the mock to return a different value for the new url.  

7. Add a second use of EXPECT_CALL after the first call to `service.UnderTest.getQuote` that returns "7.0" when the bmw stock is requested.
```cpp
TEST_F(StockQuoteTest, DifferentSymbolsReturnDifferentResults)
{
    std::string validUrl{"https://www.stockprices.are.us.com?sym=ibm"};

    StockTickerService serviceUnderTest(http);
    EXPECT_CALL(http, get(validUrl)).WillOnce(Return ("42.0"));
    std::string quote = serviceUnderTest.getQuote(validUrl);
    validUrl = "https://www.stockprices.are.us.com?sym=bmw";
    EXPECT_CALL(http, get(validUrl)).WillOnce(Return ("7.0"));
    std::string quote2 = serviceUnderTest.getQuote(validUrl);
    ASSERT_EQ(quote, "42.0");
    ASSERT_EQ(quote2, "7.0");
}
```

## Discussion Questions
- Does our final test actually prove anything?
- What might be improved to make these tests better?
- Should we ever allow the production Http implementation to be used here?
