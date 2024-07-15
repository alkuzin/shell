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

#include <shell/utils.h>


void shell_getinput(char *input, size_t size)
{
	uint32_t i;

    i = 0;
	fgets(input, size, stdin);

	if (input) {
        
		while (input[i] != '\n' && input[i] != '\0')
			i++;
        
		if (input[i] == '\n')
            input[i] = '\0';
		else {
            while (getchar() != '\n')
                continue;
        }
    }
}

int32_t shell_getargc(char **args)
{
	int32_t i;

	i = 0;
	
	while (args[i])
		i++;
	
	return i;
}

int32_t shell_cmpstr(const void *p1, const void *p2)
{
    char *s1, *s2;

    s1 = *(char **)p1;
    s2 = *(char **)p2;
    
    return strcmp(s1, s2);
}