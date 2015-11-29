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

#include "buildList.h"
#include "../enum.h"

#define MAX_PATH 512


/*enum {
    DIRNAME,
    PATH_NAME,
    COLUMNS
};*/

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
    
    // until directory has been searched
    while (1) {
        struct dirent * entry;
        const char * f_name;
        
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
                //save file_name into list store
                gtk_tree_store_append(store, &iter, NULL);
                                printf ("f_name: %s\n", f_name);
                gtk_tree_store_set(store, &iter, 
                                   FILE_NAME, f_name, 
                                   DIR_NAME, " ",
                                   PATH_NAME, dir_name,
                                   -1);

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

    // add the first name to the listview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Name", renderer, "text", FILE_NAME,
                NULL); 
    gtk_tree_view_append_column (GTK_TREE_VIEW (listview), column);

}
/*
void dir_selected (GtkWidget *selection, gpointer data) {
    
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(selection), 
        &model, &iter)) {
        
        char *path_name;
        char *dir_name;
        
        gtk_tree_model_get (model, &iter, PATH_NAME, &path_name, DIRNAME, dir_name, -1);
        g_message("selected %s\n", path_name);
    
    
        // build the list store from dir
        

        
        if (build_list(check_dir, store) != 0) {
            printf("Error building list from data\n");
            exit(0);
        }
        
        // create the tree view of the list
        GtkWidget *listview = gtk_tree_view_new ();
        build_lreeview(listview);
        
        // add the tree model to the tree view
        gtk_tree_view_set_model (GTK_TREE_VIEW (listview), GTK_TREE_MODEL (store));
        
        // unreference the model so that it will be destroyed when the tree
        // view is destroyed
        g_object_unref (store);
        
        // display the tree view
        display (listview);
    }
    return 0;
}
*/
