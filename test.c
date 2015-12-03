#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <locale.h>
#include <langinfo.h>
#include <string.h>
#include <limits.h>
#include <grp.h>
#include <pwd.h>


#define CHANGEFILE "/home/jrvanderveen/Documents/CS352/calc/calc.c"
int main(void) {
    struct stat st;
    mode_t mode;
    const char *path = "test.txt";

    stat(CHANGEFILE, &st);

    mode = st.st_mode & 07777;

    // modify mode
    //mode &= ~(S_IRUSR);    /* Clear this bit */
    mode |= S_IXGRP;       /* Set this bit   */

    chmod(CHANGEFILE, mode);

    return 0;   
}
