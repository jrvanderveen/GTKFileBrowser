/*
 main functions for listview
 
 build_list (store, dir_name)            
 build_listview (GtkWidget *listview)
 gint sort_file_names (model, a,b, data)
 
 each element of the listview consists of
                        
                        FILE_NAME, 
                        FILE_SIZE,
                        FILE_DATE,
                        DIR_NAME,
                        PATH_NAME,
                        IMAGE,
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
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


/*
 This functions basically handels everything didnt have enough time to clean it up when i do i asume it will look a lot like buildtree.c
 find all the files in the directory name given and store information about them in store
 for the image i have a folder of images with names like "c" "deb" "h" ect math the extension to the icon and use it as image
 for each file create a stat for it to find all the information needed
 */
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
    char f_date[MAX_PATH];
    char f_time[MAX_PATH];
    unsigned int f_size;
    struct tm *tm;
    GError *error = NULL;
    GdkPixbuf* image;
    char *file_type;

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
            if (entry->d_type & DT_REG || entry->d_type & DT_DIR) {
                if (strlen(f_name) >= PATH_MAX) {
                    fprintf (stderr, "File length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                //determine image
                char *image_path = (char*) malloc(50*sizeof(char));
                file_type = strrchr(f_name, '.');
                
                if(file_type != NULL){
                    file_type++;
                    strcpy(image_path, "ListView/icons/16px/");
                    strcat(image_path, file_type);
                    image = gdk_pixbuf_new_from_file(image_path, &error);
                    if(error != NULL){
                        error = NULL;
                        printf("\nextension '%s' not found default set: ListView/icons/16px/_blank", file_type);
                        image = gdk_pixbuf_new_from_file("ListView/icons/16px/_blank", &error);
                    }
                    else{
                        printf("\nimage_path: %s", image_path);
                    }
                }
                else{
                    if(entry->d_type & DT_DIR){
                        printf("\nimage_path: TreeView/icons/folder");
                        image = gdk_pixbuf_new_from_file("TreeView/icons/folder", &error);
                    }
                    else{
                        printf("\nimage_path: ListView/icons/16px/exe");
                        image = gdk_pixbuf_new_from_file("ListView/icons/16px/exe", &error);
                    }
                    
                }
                //file path 
                char *full_path = (char*) malloc(MAX_PATH*sizeof(char));
                strcpy(full_path, dir_name);
                strcat(full_path, "/");
                strcat(full_path, f_name);
                if (stat(full_path, &statbuf) == 0){
                    f_size = statbuf.st_size;
                    tm = localtime(&statbuf.st_mtime);
                    strftime(f_date, sizeof(f_date), nl_langinfo(D_FMT), tm);
                    strftime(f_time, sizeof(f_time), nl_langinfo(T_FMT), tm);
                    strcat(f_date, " ");
                    strcat(f_date, f_time);
                    //save file_name into list store

                    printf("\nf_name: %s , f_date: %s , f_size: %d", f_name, f_date, f_size);
                    
                    gtk_tree_store_append(store, &iter, NULL);
                    gtk_tree_store_set(store, &iter, 
                                    FILE_NAME, f_name,
                                    FILE_SIZE, f_size,
                                    FILE_DATE, f_date,
                                    DIR_NAME, "",
                                    PATH_NAME, dir_name,
                                    IMAGE, image,
                                    -1);
                }
                free(full_path);
                free(image_path);
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
/*
 build_listview (listview)
 create the graphical view for the list
 columns include Name Size and Date(last modification)
 make all columns sortable aswell
 */
void build_listview (GtkWidget *listview) {
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    //
    // add name to the listview
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_text_new();
    //resizable
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_min_width(column,100); 
    
    gtk_tree_view_column_pack_start(column, renderer, FALSE);
    gtk_tree_view_column_set_attributes (
                column, renderer, "text", FILE_NAME,
                NULL); 
    
    renderer = gtk_cell_renderer_pixbuf_new();
    gtk_tree_view_column_pack_start(column, renderer, FALSE);
    gtk_tree_view_column_set_attributes(
                column, renderer, "pixbuf", IMAGE, 
                NULL);
            
    gtk_tree_view_column_set_title(column, "Name");
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);
    //sort name
    gtk_tree_view_column_set_sort_column_id(column, FILE_NAME);
    gtk_tree_view_column_set_sort_indicator(column, TRUE);
    
    //
    // add size to the listview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Size (b)", renderer, "text", FILE_SIZE,
                NULL); 
    //resizable
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_min_width(column,30); 
    
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);
    //sort size
    gtk_tree_view_column_set_sort_column_id(column, FILE_SIZE);
    gtk_tree_view_column_set_sort_indicator(column, TRUE);
    //
    // date to the listview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Date", renderer, "text", FILE_DATE,
                NULL); 
    //resizable
    gtk_tree_view_column_set_resizable(column,TRUE);
    gtk_tree_view_column_set_min_width(column,30); 
    
    
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);
    //sort date
    gtk_tree_view_column_set_sort_column_id(column, FILE_DATE);
    gtk_tree_view_column_set_sort_indicator(column, TRUE);
}
/*
 sort_file_names(model, a, b, data)
 callback function for selecting a column to sort
 sort column based on strcmp
 */
gint sort_file_names (GtkTreeModel *model,
                      GtkTreeIter *a, GtkTreeIter *b,
                      gpointer data) {
    
    gchar *name1, *name2;
    gtk_tree_model_get (model, a, FILE_NAME, &name1, -1);
    gtk_tree_model_get (model, b, FILE_NAME, &name2, -1);
    
    int order = strcmp(name1, name2);
    g_free(name1);
    g_free(name2);
    
    return -order;
}

