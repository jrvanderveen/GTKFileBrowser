#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

#include "buildTree.h"
#include "../ListView/buildList.h"
#include "../enum.h"

#define MAX_PATH 1024

/*enum {
    FILE_NAME,
    FILE_SIZE,
    FILE_DATE,
    DIR_NAME,
    PATH_NAME,
    IMAGE,
    COLUMNS
};*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void build_treeview (GtkWidget *treeview) {
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    column = gtk_tree_view_column_new();
    renderer = gtk_cell_renderer_pixbuf_new();
    gtk_tree_view_column_pack_start(column, renderer, FALSE);
    gtk_tree_view_column_set_attributes(column, renderer, "pixbuf", IMAGE, NULL);
    
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, FALSE);
    gtk_tree_view_column_set_attributes (column, renderer, "text", DIR_NAME,
                NULL); 
    
    gtk_tree_view_column_set_title(column, "Name");
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);

}
  
int list_dir (GtkTreeStore* store, const char * dir_name, GtkTreeIter iter_p, int state) {
    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    GError *error = NULL;
    GdkPixbuf* image = gdk_pixbuf_new_from_file("TreeView/icons/folder", &error);
    if(state == 0){
        char start_name[MAX_PATH];

        strcpy(start_name, strrchr(dir_name, '/') + 1);
        struct dirent * entry;
        const char * d_name;
        
        entry = readdir (d);
        
        if (! entry) {
            printf("Directory Not Found");
            exit(0);
        }
        gtk_tree_store_append (store, &iter_p, NULL);
        gtk_tree_store_set (store, &iter_p,
                            FILE_NAME, "",
                            FILE_SIZE, 0,
                            FILE_DATE, "",
                            DIR_NAME, start_name,
                            PATH_NAME, dir_name,
                            IMAGE, image,
                            -1);  
        list_dir (store, dir_name, iter_p, 1);
    }
    else{
        GtkTreeIter iter_ch;
        struct dirent * entry;
        char * d_name;
        int path_length;
        char path[PATH_MAX];

        while (1) {
            /* "Readdir" gets subsequent entries from "d". */
            entry = readdir (d);
            if (! entry) {
                /* There are no more entries in this directory, so break
                out of the while loop. */
                break;
            }
            d_name = entry->d_name;
            if(d_name[0] != '.'){
                if (entry->d_type & DT_DIR) {
                    if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) {
                        path_length = snprintf (path, PATH_MAX,
                                                "%s/%s", dir_name, d_name);
                        printf ("path: %s\n", path);
                        if (path_length >= PATH_MAX) {
                            fprintf (stderr, "Path length has got too long.\n");
                            exit (EXIT_FAILURE);
                        }
                        /* Recursively call "list_dir" with the new path. */
                        gtk_tree_store_append (store, &iter_ch, &iter_p);
                        gtk_tree_store_set (store, &iter_ch,
                                            FILE_NAME, "",
                                            FILE_SIZE, 0,
                                            FILE_DATE, "",
                                            DIR_NAME, d_name,
                                            PATH_NAME, path,
                                            IMAGE, image,
                                            -1);  
                        list_dir (store, path, iter_ch, 1);
                    }
                }
                
            }
        }
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    return 0;
}