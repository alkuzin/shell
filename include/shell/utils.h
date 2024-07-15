/* Shell - simple implementation of Linux shell.
 * Copyright (C) 2024 Alexander (@alkuzin)
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

/**
 * @file  utils.h
 * @brief Provides auxilar functions used in shell. 
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   14.07.2024
 */

#ifndef _SHELL_UTILS_H_
#define _SHELL_UTILS_H_

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Get user input.
 * 
 * @param [out] input - given buffer to store user input.
 * @param [in] size - given max size of the input to store.
 */
void shell_getinput(char *input, size_t size);

/**
 * @brief Get number of shell command arguments. 
 * 
 * @param [in] args - given shell arguments list.
 * @return number of arguments.
 */
int32_t shell_getargc(char **args);

/**
 * @brief Compares two strings pointed to by the given pointers. 
 * 
 * @param [in] p1 - given pointer to the first string to compare.
 * @param [in] p2 - given pointer to the second string to compare.
 * 
 * @return a positive value if @a p1 is greater  @a p2.
 * @return 0, if @a p1 equals @a p2.
 * @return a negative if @a p1 is less than @a p2.
 */
int32_t shell_cmpstr(const void *p1, const void *p2);

#endif /* _SHELL_UTILS_H_ */