# The support for C++ seems to have been removed from the Selenium project

Checkout [Selenium Repository](https://github.com/SeleniumHQ/selenium) for the current options.

# Demonstration of WebDriver++

1. **Install Selenium Server**: Before running any examples we will need the Selenium IDE.  It can be downloaded from [Selenium Downloads](https://www.seleniumhq.dev/downloads/).

    - Scroll down and select Selenium IDE for Edge 
    - Add the extension to the browser.


2. Run the **selenium-server**. 

3. **Include Webdriver++ in Your Project**:
   ```cpp
   #include <webdriverxx/webdriverxx.h>
   using namespace webdriverxx;
   ```

4. **Example Usage**:
   ```cpp
   int main() {
       // Start Firefox browser
       WebDriver firefox = Start(Firefox());
       firefox.Navigate("http://google.com");
       firefox.FindElement(ByCss("input[name=q]")).SendKeys("Hello, world!").Submit();
       return 0;
   }
   ```
## Other browsers
- Starting different browsers:
     ```cpp
     WebDriver ff = Start(Firefox());
     WebDriver gc = Start(Chrome());
     WebDriver ie = Start(InternetExplorer());
     ```

- Using a proxy:
     ```cpp
     WebDriver ie = Start(InternetExplorer().SetProxy(SocksProxy("127.0.0.1:3128")
         .SetUsername("user")
         .SetPassword("12345")
         .SetNoProxyFor("custom.host")));
     WebDriver ff = Start(Firefox().SetProxy(DirectConnection()));
     ```