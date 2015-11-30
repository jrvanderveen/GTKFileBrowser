#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <locale.h>
#include <langinfo.h>
#include <string.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

#include "buildList.h"
#include "../enum.h"

#define MAX_PATH 512



int build_list (GtkTreeStore* store, char* dir_name) {
    DIR * d;
    /* Open the directory specified by "dir_name". */
    d = opendir (dir_name);
    
    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
        
    GtkTreeIter iter;
    struct stat statbuf;
    
    // until directory has been searched
    struct dirent * entry;
    char * f_name;
    char f_date[512];
    unsigned int f_size;
    struct tm *tm;
    while (1) {
        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
             *        out of the while loop. */
            break;
        }
        f_name = entry->d_name;
        if(f_name[0] != '.'){
            if (entry->d_type & DT_REG) {
                if (strlen(f_name) >= PATH_MAX) {
                    fprintf (stderr, "File length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                //determine image
                char *file_type = (char*) malloc(10*sizeof(char)); 
                strch()
                
                //file path 
                char *full_path = (char*) malloc(MAX_PATH*sizeof(char));
                strcpy(full_path, dir_name);
                strcat(full_path, "/");
                strcat(full_path, f_name);
                if (stat(full_path, &statbuf) == 0){
                                            printf("\n f_name1: %s", entry->d_name);
                    f_size = statbuf.st_size;
                    tm = localtime(&statbuf.st_mtime);
                    strftime(f_date, sizeof(f_date), nl_langinfo(D_FMT), tm);
                    //save file_name into list store

                    printf("\n f_name: %s , f_date: %s , f_size: %d\n", f_name, f_date, f_size);
                    
                    gtk_tree_store_append(store, &iter, NULL);
                    gtk_tree_store_set(store, &iter, 
                                    FILE_NAME, f_name,
                                    FILE_SIZE, f_size,
                                    FILE_DATE, f_date,
                                    DIR_NAME, "",
                                    PATH_NAME, dir_name,
                                    IMAGE, NULL,
                                    -1);
                    
                }
                free(full_path);
                free(file_type);
            }
        }
    }
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    return 0;
    
}

void build_listview (GtkWidget *listview) {
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    // add name to the listview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Name", renderer, "text", FILE_NAME,
                NULL); 
    
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);
    
    // add size to the listview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Size (b)", renderer, "text", FILE_SIZE,
                NULL); 
    
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);
    
    // date to the listview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Date", renderer, "text", FILE_DATE,
                NULL); 
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);
}
