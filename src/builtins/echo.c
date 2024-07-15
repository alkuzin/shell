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


void shell_echo(char **args)
{
    int32_t argc, is_n_opt, i;

    argc     = shell_getargc(args);
    is_n_opt = 0;
    i        = 1;

    if (argc > 1) {
        if ((args[1] && strncmp(args[1], "-n", 2) == 0)) {
            is_n_opt = 1;
            i        = 2;
        }
        
        for (; i < argc - 1; i++)
            printf("%s ", args[i]);
        
        printf("%s", args[i]);
        
        if (!is_n_opt)
            putchar('\n');
    }
}