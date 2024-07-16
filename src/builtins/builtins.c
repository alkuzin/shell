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

#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <pwd.h>

#include <shell/builtins.h>
#include <shell/utils.h>
#include <shell/shell.h>

/**
 * @brief Get number of builtin commands.
 * 
 * @return total number of builtin commands.
 */
static size_t shell_builtins_size(void);

/** @brief List of shell builtin commands functions pointers. */
static void (*shell_builtins[]) = {
    &shell_echo,
    &shell_pwd,
    &shell_export,
    &shell_exit
};

/** @brief List of shell builtin commands names. */
static char *shell_builtins_names[] = {
    "echo",
    "pwd",
    "export",
    "exit"
};


static size_t shell_builtins_size(void)
{
    return (sizeof(shell_builtins_names) / sizeof(char *));
}

int32_t shell_is_builtin(char *cmd)
{
    char *builtin;

    for (size_t i = 0; i < shell_builtins_size(); i++) {
        builtin = shell_builtins_names[i];
        
        if (strncmp(builtin, cmd, strlen(builtin)) == 0)
            return i;
    }

    return -1;
}

void shell_exec_builtin(int32_t id, char **args)
{
    void (*builtin) (char **);

    builtin = shell_builtins[id];
    builtin(args);
}
