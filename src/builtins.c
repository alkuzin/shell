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
    &shell_export
};

/** @brief List of shell builtin commands names. */
static char *shell_builtins_names[] = {
    "echo",
    "pwd",
    "export"
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

void shell_pwd(char **args)
{
    char cwd[1024];
    (void) args;

    if (getcwd(cwd, sizeof(cwd)))
        puts(cwd);
    else {
        perror("shell: pwd");
        exit(EXIT_FAILURE);
    }
}

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