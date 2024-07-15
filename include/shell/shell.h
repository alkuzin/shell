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
 * @file  shell.h
 * @brief Provides definitions & functions used in shell. 
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   14.07.2024
 */

#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdint.h>

#define SHELL_TOK_DELIM      " \n\t\r\"\'"
#define SHELL_INPUT_BUFSIZE  256
#define SHELL_TOK_BUFSIZE    64
#define SHELL_PROMPT_BUFSIZE 256

extern char **environ;

/** @brief Initialize shell. */
void shell_init(void);

/**
 * @brief Split user input. 
 * 
 * @param [in] buffer - given user input.
 * @return separated tokens list.
 */
char **shell_split(char *buffer);

/**
 * @brief Execute shell command.
 * 
 * @param [in] args - given separated tokens list.
 * @return zero in case of success.
 */
int32_t shell_exec(char **args);

/**
 * @brief Set current directory.
 * 
 * @param [in] path - given current directory to set. 
 */
void shell_set_cwd(char *path);

#endif /* _SHELL_H_ */