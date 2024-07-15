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
#include <stdlib.h>
#include <stdio.h>

#include <shell/builtins.h>
#include <shell/utils.h>
#include <shell/shell.h>


void shell_export(char **args)
{
    char    **env, **env_sorted, *ptr;
    int32_t count;
    (void)  args;

    env   = environ;
    count = 0;

    while (*env) {
        count++;
        env++;
    }

    env_sorted = (char **)malloc(count * sizeof(char *));

    if (!env_sorted) {
        perror("shell: export: allocation error");
        exit(EXIT_FAILURE);
    }

    env = environ;

    for (int32_t i = 0; i < count; i++) {
        env_sorted[i] = *env;
        env++;
    }

    qsort(env_sorted, count, sizeof(char *), shell_cmpstr);

    for (int32_t i = 0; i < count; i++) {
        ptr = strchr(env_sorted[i], '=');

        if (ptr) {
            *ptr = '\0';
            printf("declare -x %s=\"%s\"\n", env_sorted[i], ptr + 1);
        }
    }

    free(env_sorted);
}