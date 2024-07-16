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
 * @file  builtins.h
 * @brief Provides shell builtin commands. 
 * 
 * @author Alexander Kuzin (<a href="https://github.com/alkuzin">alkuzin</a>)
 * @date   15.07.2024
 */

#ifndef _SHELL_BUILTINS_H_
#define _SHELL_BUILTINS_H_

#include <stdint.h>

/**
 * @brief Check command is builtin.
 * 
 * @param [in] cmd - given command.
 * @return builtin command ID - if @a cmd is builtin.
 * @return -1 - otherwise.
 */
int32_t shell_is_builtin(char *cmd);

/**
 * @brief Execute shell builtin command.
 * 
 * @param [in] cmd - given builtin command ID.
 * @param [in] args -given list of arguments.
 */
void shell_exec_builtin(int32_t id, char **args);

/**
 * @brief Shell echo builtin commands. 
 * 
 * @param [in] args - given command arguments list.
 */
void shell_echo(char **args);

/**
 * @brief Shell print current working directory.
 * 
 * @param [in] args - given command arguments list.
 */
void shell_pwd(char **args);

/**
 * @brief Shell print enviroment variables.
 * 
 * @param [in] args - given command arguments list.
 */
void shell_export(char **args);

/**
 * @brief Exit shell.
 * 
 * @param [in] args - given command arguments list.
 */
void shell_exit(char **args);

#endif /* _SHELL_BUILTINS_H_ */