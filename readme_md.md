*This project has been created as part of the 42 curriculum by lbetella.*

# Get Next Line

## Description

The objective of this project is to program a function that returns a line read from a file descriptor. This project is fundamental to learning how static variables work in C, as well as to perfecting dynamic memory management, ensuring that no memory leaks occur.

Calling the `get_next_line` function repeatedly (for example, using a loop) allows reading the content of the file pointed to by the file descriptor, one line at a time, until the end of the file is reached.

## Algorithm and Justification

To solve this problem cleanly and modularly, the main algorithm of `get_next_line` has been divided into three distinct phases. This allows for more readable code, easier error handling, and makes the static variable logic safe and predictable.

The function uses a single static variable (`static char *string`) that acts as a cumulative buffer. The process is as follows:

1. **Reading and Accumulating (`ft_read`)**:
   The function reads from the file using the size specified by `BUFFER_SIZE` and concatenates the newly read content to our static variable. This loop stops as soon as a newline character (`\n`) is found or the end of the file (EOF) is reached.

2. **Extracting the line (`ft_extract`)**:
   Once we have the necessary text accumulated in our static variable, this function calculates the length up to the first newline (including it). It allocates the exact memory required, copies the characters, and returns the resulting string that will be delivered to the user.

3. **Cleaning and Updating (`ft_clean`)**:
   To prepare the function for the next call, this function takes all the text that remains *after* the first newline in the static variable, saves it in a newly allocated memory space, frees the original static pointer, and returns the remaining text. This remaining text becomes the new updated value of the static variable.

**Bonus Part**: The justification for the bonus part follows the exact same algorithm but is expanded by using an array of static pointers (`static char *string[1024]`). This allows managing multiple file descriptors simultaneously without losing the reading state of each one, by associating each index of the array to a specific file descriptor.

## Instructions

This project does not generate an executable on its own; instead, it provides a set of functions designed to be compiled alongside your future projects.

To compile the functions and integrate them into your code, you must include the source files and specify the buffer size at compile time using the `-D BUFFER_SIZE=n` flag.

**Compilation Example:**

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

To use the version that supports multiple file descriptors (Bonus):

```bash
cc -Wall -Werror -Wextra -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

**Usage in code:**

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Resources

During the development of this project, the following references were consulted:

* C documentation for the allowed functions: `man 2 read`, `man 3 malloc`, `man 3 free`.
* [Static variables in C (GeeksforGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/)
* Concepts of File Descriptors in Unix systems.

**Use of AI:**
Artificial Intelligence was used in accordance with the 42 policy, strictly as a pedagogical support tool. It was employed to clarify complex theoretical concepts (such as the behavior of file descriptors and static variables), to brainstorm potential edge cases that could cause memory leaks, and to structure and format this `README.md` file. It was not used to generate the logical code of the project.