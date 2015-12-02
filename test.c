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

int main(void) {
    struct stat statbuf;
    struct group *grp;
    struct passwd *pwd;
    
    if (stat("/media/jrvanderveen/WindowsPartition/programing/CS352/GTK/GTKFileBrowser", &statbuf) == 0){
        if ((grp = getgrgid(statbuf.st_gid)) != NULL)
            printf("\n %-8.8s", grp->gr_name);
        else
            printf("\n %-8d", statbuf.st_gid);
        
        if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
            printf("\n %-8.8s \n", pwd->pw_name);
        else
            printf("\n %-8d \n", statbuf.st_uid);
    }
    if(statbuf.st_mode & S_IRUSR == S_IRUSR){
        printf("r ");
    }
    else{
        printf("- ");
    }
    printf( (statbuf.st_mode & S_IWUSR) ? "w " : "-");
    printf( (statbuf.st_mode & S_IXUSR) ? "x \n" : "-");
}