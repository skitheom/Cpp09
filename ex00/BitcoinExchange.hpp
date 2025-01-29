

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
private:
  std::map<std::string, double> bitcoinRates;

public:
  BitcoinExchange();
  BitcoinExchange(const BitcoinExchange &other);
  ~BitcoinExchange();

  BitcoinExchange &operator=(const BitcoinExchange &other);

private:
  bool validateInputDate();
};

#endif // BITCOINEXCHANGE_HPP

/*

#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, double> bitcoinRates;

    // データベースを読み込み（例）
    bitcoinRates["2021-01-01"] = 29.0;
    bitcoinRates["2021-01-02"] = 31.5;
    bitcoinRates["2021-01-03"] = 30.0;

    // ユーザー入力の処理
    std::string inputDate = "2021-01-02";
    double inputValue = 2.0;

    // 入力された日付のレートを検索
    auto it = bitcoinRates.find(inputDate);
    if (it != bitcoinRates.end()) {
        std::cout << inputDate << " => " << inputValue
                  << " = " << inputValue * it->second << std::endl;
    } else {
        std::cout << "Error: Date not found." << std::endl;
    }

    return 0;
}

Date and Time Parsing in C++

// C++ Program to implement Date and Time parsing using
// <ctime>
#include <ctime>
#include <iostream>
using namespace std;

// function to parse a date or time string.
time_t parseDateTime(const char* datetimeString, const char* format)
{
        struct tm tmStruct;
        strptime(datetimeString, format, &tmStruct);
        return mktime(&tmStruct);
}

// Function to format a time_t value into a date or time string.
string DateTime(time_t time, const char* format)
{
        char buffer[90];
        struct tm* timeinfo = localtime(&time);
        strftime(buffer, sizeof(buffer), format, timeinfo);
        return buffer;
}
int main()
{
        const char* datetimeString = "2023-06-17 12:36:51";
        const char* format = "%Y-%m-%d %H:%M:%S";
        time_t parsedTime = parseDateTime(datetimeString, format);
        string formattedTime = DateTime(parsedTime, format);
        cout << "Parsed Time--> " << parsedTime << endl;
        cout << "Formatted Time--> " << formattedTime << endl;
        return 0;
}

 */

/*


Validate Traditional DateTime Format (YYYY-MM-DD HH:MM:SS)


// C++ code to validate the
// DateTime(YYYY-MM-DD HH:MM:SS) using Regular
// Expression

#include <iostream>
#include <regex>
using namespace std;

// Function to validate the
// DateTime(YYYY-MM-DD HH:MM:SS)
string isValid_DateTime(string str)
{

        // Regex to check valid
        // DateTime(YYYY-MM-DD HH:MM:SS).
        const regex pattern(
                "^([0-9]{4})-((01|02|03|04|05|06|07|08|09|10|11|12|"
                "(?:J(anuary|u(ne|ly))|February|Ma(rch|y)|A(pril|"
                "ugust)|(Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|"
                "Nov|Dec)|(JANUARY|FEBRUARY|MARCH|APRIL|MAY|JUNE|"
                "JULY|AUGUST|SEPTEMBER|OCTOBER|NOVEMBER|DECEMBER)|("
                "September|October|November|December)|(jan|feb|mar|"
                "apr|may|jun|jul|aug|sep|oct|nov|dec)|(JAN|FEB|MAR|"
                "APR|MAY|JUN|JUL|AUG|SEP|OCT|NOV|DEC)))|(january|"
                "february|march|april|may|june|july|august|"
                "september|october|november|december))-([0-3][0-9])"
                "\\s([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])"
                "$");

        // If the str
        // is empty return false
        if (str.empty()) {
                return "false";
        }

        // Return true if the str
        // matched the ReGex
        if (regex_match(str, pattern)) {
                return "true";
        }
        else {
                return "false";
        }
}

// Driver Code
int main()
{
        // Test Case 1:
        string str1 = "2023-01-01 01:01:01";
        cout << isValid_DateTime(str1) << endl;

        // Test Case 2:
        string str2 = "1998-07-12 18:01:01";
        cout << isValid_DateTime(str2) << endl;

        // Test Case 3:
        string str3 = "1998-07-12";
        cout << isValid_DateTime(str3) << endl;

        // Test Case 4:
        string str4 = "12/07/1998 12:00";
        cout << isValid_DateTime(str4) << endl;

        // Test Case 5:
        string str5 = "1998-13-12 23:01:01";
        cout << isValid_DateTime(str5) << endl;

        return 0;
}


 */

/*


Program to check if a date is valid or not


// C++ program to check if
// given date is valid or not.
#include<iostream>
using namespace std;

const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;

// Returns true if
// given year is valid.
bool isLeap(int year)
{
// Return true if year
// is a multiple of 4 and
// not multiple of 100.
// OR year is multiple of 400.
return (((year % 4 == 0) &&
                (year % 100 != 0)) ||
                (year % 400 == 0));
}

// Returns true if given
// year is valid or not.
bool isValidDate(int d, int m, int y)
{
        // If year, month and day
        // are not in given range
        if (y > MAX_VALID_YR ||
                y < MIN_VALID_YR)
        return false;
        if (m < 1 || m > 12)
        return false;
        if (d < 1 || d > 31)
        return false;

        // Handle February month
        // with leap year
        if (m == 2)
        {
                if (isLeap(y))
                return (d <= 29);
                else
                return (d <= 28);
        }

        // Months of April, June,
        // Sept and Nov must have
        // number of days less than
        // or equal to 30.
        if (m == 4 || m == 6 ||
                m == 9 || m == 11)
                return (d <= 30);

        return true;
}

// Driver code
int main(void)
{
isValidDate(10, 12, 2000)? cout << "Yes\n" :
                                                cout << "No\n";

isValidDate(31, 11, 2000)? cout << "Yes\n" :
                                                cout << "No\n";
}

 */
