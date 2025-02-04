/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:09:54 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/03 23:49:48 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {
public:
  BitcoinExchange();
  BitcoinExchange(const std::string &fileName);
  BitcoinExchange(const BitcoinExchange &other);
  ~BitcoinExchange();

  BitcoinExchange &operator=(const BitcoinExchange &other);

  void processInput(const std::string &inputFile);

private:
  static const std::string kDefaultFileName;
  static const std::string ERR_FILE_OPEN_FAILED;
  static const std::string ERR_NEGATIVE_NUM;
  static const std::string ERR_BAD_INPUT;
  static const std::string ERR_TOO_LARGE;

  std::map<time_t, double> bitcoinRates_;

  std::map<time_t, double> readCSV(const std::string &fileName);
  time_t parseDate(const std::string &dateStr);
  double parseRate(const std::string &rateStr);

  bool isValidDate(int year, int month, int day);
  bool isValidRate(const std::string &rateStr);
  bool isLeapYear(int year);

  std::string trimLeft(const std::string &s);
  std::string trimRight(const std::string &s);
  std::string trim(const std::string &s);

  void processLine(const std::string &line);

  std::string timeToDateStr(time_t time);
  int elapsedDays(time_t from, time_t to);
};

#endif // BITCOINEXCHANGE_HPP
