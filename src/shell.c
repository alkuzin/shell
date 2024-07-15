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

#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>

#include <shell/builtins.h>
#include <shell/shell.h>
#include <shell/utils.h>

static char shell_prompt[SHELL_PROMPT_BUFSIZE];
static char shell_cwd[PATH_MAX];


static void shell_set_prompt(void)
{
    char    hostname[HOST_NAME_MAX];
    char    home_dir[PATH_MAX];
    char    cwd[PATH_MAX];
    char    *home_user, *username;
    struct  passwd *pw;
    int32_t status;
    uid_t   uid;

    uid      = getuid();
    pw       = getpwuid(uid);
    username = pw->pw_name;
    status   = gethostname(hostname, HOST_NAME_MAX);

    if (status != 0) {
        perror("shell: gethostname");
        exit(EXIT_FAILURE);
    }

    if (!getcwd(cwd, sizeof(cwd))) {
        perror("shell: getcwd");
        exit(EXIT_FAILURE);
    }

    snprintf(home_dir, sizeof(home_dir), "/home/%s/", username);
    home_user = strstr(cwd, home_dir);

    /* print '~' instead of '/home/<username>/...' */
    if (home_user) {
        strncpy(shell_cwd, "~", PATH_MAX);
        strncat(shell_cwd, home_user + strlen(home_dir) - 1, PATH_MAX - 1);
    }
    else
        strncpy(shell_cwd, cwd, PATH_MAX);
    
    snprintf(shell_prompt, SHELL_PROMPT_BUFSIZE, "[%s-%s]", username, hostname);
}

void shell_init(void)
{
    char    buffer[SHELL_INPUT_BUFSIZE];
    char    **args;
    int32_t status;

    shell_set_prompt();

    do {
        printf("%s:%s> ", shell_prompt, shell_cwd);
        getinput(buffer, SHELL_INPUT_BUFSIZE);

        args = shell_split(buffer);

        if (!args[0])
            continue; 

        status = shell_exec(args);

        free(args);

    } while (status);
}

char **shell_split(char *buffer)
{
    char    **tokens, *token;
    int32_t size, pos;

    size   = SHELL_TOK_BUFSIZE;
    pos    = 0;
    tokens = (char **)malloc(size * sizeof(char *));
    
    if (!tokens) {
        perror("malloc error");
        exit(EXIT_FAILURE);
    }
    
    token = strtok(buffer, SHELL_TOK_DELIM);

    while (token != NULL) {
        tokens[pos] = token;
        pos++;
        
        if (pos >= size) {
            size += SHELL_TOK_BUFSIZE;
            tokens = (char **)realloc(tokens, size * sizeof(char *));
            
            if (!tokens) {
                perror("malloc error");
                exit(EXIT_FAILURE);
            }    
        }
        
        token = strtok(NULL, SHELL_TOK_DELIM);
    }
    
    tokens[pos] = NULL;
    return tokens;
}

int32_t shell_exec(char **args)
{
    char    path[SHELL_TOK_BUFSIZE];
    int32_t status, ret;
    pid_t   pid, wpid;

    pid = fork();

    if (pid == 0) {
        ret = shell_is_builtin(args[0]);
        
        /* child process */
        if (ret != -1)
            shell_exec_builtin(ret, args);
        else {
            strncpy(path, "/usr/bin/", 10);
            strncat(path, args[0], strlen(args[0]));

            ret = execve(path, args, NULL);

            if (ret == -1)
                printf("shell: %s: command not found\n", args[0]);    
        }

        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        /* fork error */
        perror("shell");
    }
    else {
        /* parent process */
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        
        (void)wpid;
    }

    return 1;
}