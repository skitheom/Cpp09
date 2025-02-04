/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:09:48 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/03 23:50:03 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

const std::string BitcoinExchange::kDefaultFileName = "data.csv";

const std::string BitcoinExchange::ERR_FILE_OPEN_FAILED = "could not open file";
const std::string BitcoinExchange::ERR_NEGATIVE_NUM = "not a positive number.";
const std::string BitcoinExchange::ERR_BAD_INPUT = "bad input => ";
const std::string BitcoinExchange::ERR_TOO_LARGE = "too large a number.";

BitcoinExchange::BitcoinExchange() : bitcoinRates_(readCSV(kDefaultFileName)) {}

BitcoinExchange::BitcoinExchange(const std::string &fileName)
    : bitcoinRates_(readCSV(fileName)) {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : bitcoinRates_(other.bitcoinRates_) {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other) {
    bitcoinRates_ = other.bitcoinRates_;
  }
  return *this;
}

std::map<time_t, double> BitcoinExchange::readCSV(const std::string &fileName) {
  std::map<time_t, double> rates;
  std::ifstream inFile(fileName.c_str());
  std::string line;

  if (!inFile.is_open()) {
    throw std::runtime_error(ERR_FILE_OPEN_FAILED + ": " + fileName);
  }
  if (!std::getline(inFile, line, '\n')) {
    inFile.close();
    throw std::runtime_error(ERR_FILE_OPEN_FAILED + ": " + fileName);
  }
  while (std::getline(inFile, line)) {
    size_t commaIndex = line.find(',');
    if (commaIndex == std::string::npos) {
      throw std::logic_error(ERR_BAD_INPUT + line);
    }
    if (line.empty()) {
      throw std::logic_error(ERR_BAD_INPUT + "empty");
    }
    std::string dateStr = trim(line.substr(0, commaIndex));
    std::string rateStr = trim(line.substr(commaIndex + 1));
    rates.insert(std::make_pair(parseDate(dateStr), parseRate(rateStr)));
  }
  inFile.close();
#ifdef DISPLAY_DEBUG_MSG
  if (!rates.empty()) {
    std::map<time_t, double>::iterator itStart = rates.begin();
    std::map<time_t, double>::iterator itEnd = rates.end();
    --itEnd;
    std::cerr << "[Debug] Exchange rate data in " << fileName
              << " loaded successfully!\n"
              << "[Debug] Oldest date: " << timeToDateStr(itStart->first)
              << ", Latest date: " << timeToDateStr(itEnd->first) << "\n";
  } else {
    std::cerr << "[Debug] No valid exchange rate data found in " << fileName
              << "!\n";
  }
#endif
  return rates;
}

void BitcoinExchange::processInput(const std::string &inputFile) {
  std::ifstream inFile(inputFile.c_str());
  std::string line;

  if (!inFile.is_open()) {
    throw std::runtime_error(ERR_FILE_OPEN_FAILED + ": " + inputFile);
  }
  if (!std::getline(inFile, line, '\n')) {
    inFile.close();
    throw std::runtime_error(ERR_FILE_OPEN_FAILED + ": " + inputFile);
  }
  while (std::getline(inFile, line)) {
    try {
      processLine(line);
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
  inFile.close();
}

void BitcoinExchange::processLine(const std::string &line) {
#ifdef DISPLAY_DEBUG_MSG
  std::cerr << "--------------------------------------------\n";
  std::cerr << "[Debug] Input:\t" << line << "\n";
#endif
  if (line.empty()) {
#ifdef DISPLAY_DEBUG_MSG
    std::cerr << "[Debug] Skipping empty line.\n";
#endif
    return;
  }
  size_t pipeIndex = line.find('|');
  if (pipeIndex == std::string::npos) {
    throw std::logic_error(ERR_BAD_INPUT + line);
  }
  const std::string dateStr = trim(line.substr(0, pipeIndex));
  const std::string rateStr = trim(line.substr(pipeIndex + 1));

  time_t date = parseDate(dateStr);
  double rate = parseRate(rateStr);

  std::map<time_t, double>::iterator it = bitcoinRates_.lower_bound(date);

  if (it == bitcoinRates_.end() || it->first > date) {
    if (it == bitcoinRates_.begin()) {
      throw std::runtime_error("no available exchange rate found.");
    }
    --it;
  }
  const int kMaxStaleDays = 30;
  if (elapsedDays(it->first, date) > kMaxStaleDays) {
    throw std::runtime_error("no recent exchange rate available for " +
                             timeToDateStr(date) + ".");
  }

  double exchangeRate = it->second;
  double result = rate * exchangeRate;

#ifdef DISPLAY_DEBUG_MSG
  std::cerr << "[Debug] Found:\t" << timeToDateStr(it->first) << " | "
            << it->second << "\n";
#endif
  std::cout << dateStr << " => " << rate << " = " << result << std::endl;
}

time_t BitcoinExchange::parseDate(const std::string &dateStr) {
  if (dateStr.empty()) {
    throw std::runtime_error(ERR_BAD_INPUT + "(empty date)");
  }
  if (dateStr.size() != 10) {
    throw std::runtime_error(ERR_BAD_INPUT + dateStr);
  }

  struct std::tm tm = {};
  std::istringstream ss(dateStr);
  char hyphen1, hyphen2;

  ss >> tm.tm_year >> hyphen1 >> tm.tm_mon >> hyphen2 >> tm.tm_mday;
  if (ss.fail() || hyphen1 != '-' || hyphen2 != '-' ||
      !isValidDate(tm.tm_year, tm.tm_mon, tm.tm_mday)) {
    throw std::runtime_error(ERR_BAD_INPUT + dateStr);
  }
  tm.tm_year -= 1900;
  tm.tm_mon -= 1;

  time_t date = mktime(&tm);

  if (date > time(0)) {
    throw std::runtime_error("future dates are not supported.");
  }
  return date;
}

double BitcoinExchange::parseRate(const std::string &rateStr) {
  if (rateStr.empty()) {
    throw std::runtime_error(ERR_BAD_INPUT + "(empty value)");
  }

  std::istringstream iss(rateStr);
  double rate;

  if (!isValidRate(rateStr) || !(iss >> rate)) {
    throw std::runtime_error(ERR_BAD_INPUT + rateStr);
  }
  if (rate < 0) {
    throw std::runtime_error(ERR_NEGATIVE_NUM);
  }
  if (rate > std::numeric_limits<int>::max()) {
    throw std::runtime_error(ERR_TOO_LARGE);
  }
  return rate;
}

bool BitcoinExchange::isValidDate(int year, int month, int day) {
  if (year < 1900 || month < 1 || month > 12 || day < 1) {
    return false;
  }

  const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int maxDay = daysInMonth[month - 1];

  if (month == 2 && isLeapYear(year)) {
    maxDay = 29;
  }
  return day <= maxDay;
}

bool BitcoinExchange::isValidRate(const std::string &rateStr) {
  bool hasPeriod = false;

  if (rateStr.empty()) {
    return false;
  }
  for (size_t i = 0; i < rateStr.size(); ++i) {
    if (i == 0 && rateStr[i] == '-') {
      continue;
    }
    if (rateStr[i] == '.') {
      if (hasPeriod || i == 0 || i == rateStr.size() - 1)
        return false;
      hasPeriod = true;
    } else if (!std::isdigit(static_cast<unsigned char>(rateStr[i]))) {
      return false;
    }
  }
  return true;
}

bool BitcoinExchange::isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string BitcoinExchange::trimLeft(const std::string &s) {
  size_t start = 0;
  while (start < s.size() && std::isspace(s[start])) {
    ++start;
  }
  return s.substr(start);
}

std::string BitcoinExchange::trimRight(const std::string &s) {
  size_t end = s.size();
  while (end > 0 && std::isspace(s[end - 1])) {
    --end;
  }
  return s.substr(0, end);
}

std::string BitcoinExchange::trim(const std::string &s) {
  return trimLeft(trimRight(s));
}

std::string BitcoinExchange::timeToDateStr(time_t time) {
  char buffer[11];
  struct tm *tm = localtime(&time);
  strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm);
  return buffer;
}

int BitcoinExchange::elapsedDays(time_t from, time_t to) {
  return (to - from) / (60 * 60 * 24);
}
