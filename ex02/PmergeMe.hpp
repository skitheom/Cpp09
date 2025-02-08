/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 15:33:10 by sakitaha          #+#    #+#             */
/*   Updated: 2025/02/08 15:40:30 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe {
public:
  PmergeMe();
  PmergeMe(const PmergeMe &other);
  ~PmergeMe();

  PmergeMe &operator=(const PmergeMe &other);

private:
};

#endif // PMERGEME_HPP
