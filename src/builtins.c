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

#include <string.h>
#include <stdio.h>

#include <shell/builtins.h>
#include <shell/utils.h>

static void (*shell_builtins[]) = {
    &shell_echo
};


int32_t shell_is_builtin(char *cmd)
{
    if (strncmp("echo", cmd, 4))
        return 0;
    
    return -1;
}

void shell_exec_builtin(int32_t id, char **args)
{
    void (*builtin) (char **);

    builtin = shell_builtins[id];
    builtin(args);
}

void shell_echo(char **args)
{
    int32_t argc, is_n_opt;

    argc     = getargc(args);
    is_n_opt = 0;

    if (argc > 1) {
        if (args[1] && strncmp(args[1], "-n", 2))
            is_n_opt = 1;
        
        for (int32_t i = 0; i < argc - 1; i++)
            printf("%s ", args[i]);
        
        if (!is_n_opt)
            putchar('\n');
    }
}