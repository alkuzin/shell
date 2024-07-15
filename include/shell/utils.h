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
void getinput(char *input, size_t size);

/**
 * @brief Get number of shell command arguments. 
 * 
 * @param [in] args - given shell arguments list.
 * @return number of arguments.
 */
int32_t getargc(char **args);

#endif /* _SHELL_UTILS_H_ */