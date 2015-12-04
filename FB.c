/*
 Main function for GTK file browser
 This program searches recursivly through your computer starting at HOME directory
 building a treeview of all directories and subdirectories
 when a directory is selected everything contained in it is displayed on a side pannel in a list view
 when an item is selected the bottom pannel displays informnation about that file
 also allowing the user to change permisions.
 */

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

#include "ListView/buildList.h"
#include "TreeView/buildTree.h"
#include "Utils/utils.h"
#include "enum.h"
#include "FileInfoView/buildInfoView.h"

#define MAX_PATH 1024

int main(int argc, char **argv) {
    gtk_init (&argc, &argv);
    //create place to store information about directories and files
    GtkTreeStore *store_tree = gtk_tree_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    GtkTreeStore *store_list = gtk_tree_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    
    //create sortable columns for list view
    GtkTreeSortable *sortable = GTK_TREE_SORTABLE (store_list);
    gtk_tree_sortable_set_sort_func (sortable, FILE_NAME, sort_file_names, 
                                     GINT_TO_POINTER (FILE_NAME), NULL);
    gtk_tree_sortable_set_sort_column_id (sortable, FILE_NAME,
                                          GTK_SORT_ASCENDING);
    gtk_tree_sortable_set_sort_column_id (sortable, FILE_SIZE,
                                          GTK_SORT_ASCENDING);
    gtk_tree_sortable_set_sort_column_id (sortable, FILE_DATE,
                                          GTK_SORT_ASCENDING);
    //find HOME directory
    //if not found use current directory
    char *working_dir = getenv("HOME");
    if (working_dir != NULL) {
        printf("Home dir in enviroment ");
        printf("%s\n", working_dir);
    }
    else {
        working_dir = pwd();
        if(working_dir != NULL){
            printf("Failed to find Home using current directory %s\n", working_dir);
        }
        else{
            printf("Directory error terminate");
            exit(0);
        }
    }
    //store infromation for treeview
    GtkTreeIter iter_p;
    if(list_dir(store_tree, working_dir, iter_p, 0) != 0){
        printf ("Error building tree");
        return 1;
    }
    //store information for listview
    if(build_list(store_list, working_dir) != 0){
        printf ("Error building tree");
        return 1;
    }
    //Initialize view for the three pannels
    GtkWidget *treeview = gtk_tree_view_new ();
    GtkWidget *listview = gtk_tree_view_new ();
    GtkWidget *grid = gtk_grid_new();
    //build initial view for the file browser
    //treeview and store_tree only used once on initial set up
    build_fb_input(treeview, listview, grid, store_tree, store_list);

    g_object_unref (store_tree);
    g_object_unref (store_list);
    
    //display three panes
    display (treeview, listview, grid);
    
    gtk_main ();
    return 0;
}


