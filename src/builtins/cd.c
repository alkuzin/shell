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
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <pwd.h>

#include <shell/builtins.h>
#include <shell/utils.h>
#include <shell/shell.h>


void shell_cd(char **args)
{
    char    path[PATH_MAX];
    int32_t ret, argc, is_home_dir;
    char    *username;
    struct  passwd *pw;
    uid_t   uid;

    argc        = shell_getargc(args);
    uid         = getuid();
    pw          = getpwuid(uid);
    username    = pw->pw_name;
    is_home_dir = 0;

    if (argc == 1)
        snprintf(path, sizeof(path), "/home/%s/", username);
    else if (argc == 2)
        strncpy(path, args[1], PATH_MAX - 1);
    else {
        puts("shell: cd: too many arguments");
        exit(EXIT_FAILURE);
    }

    if (strncmp("~", path, 2) == 0) {
        snprintf(path, sizeof(path), "/home/%s/", username);
        is_home_dir = 1;
    }
    
    ret = chdir(path);

    if (ret == -1) {
        printf("shell: cd: %s: %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (!is_home_dir) {
        if (!getcwd(path, sizeof(path))) {
            perror("shell: cd: getcwd");
            exit(EXIT_FAILURE);
        }
    }

    close(pipefd[0]);
    ret = write(pipefd[1], path, strlen(path) + 1);

    if (ret == -1) {
        perror("shell: cd");
        exit(EXIT_FAILURE);
    }

    close(pipefd[1]);
    kill(getppid(), SIGUSR2);
}