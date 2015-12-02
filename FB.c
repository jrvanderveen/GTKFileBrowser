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
    GtkTreeStore *store_tree = gtk_tree_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    GtkTreeStore *store_list = gtk_tree_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, GDK_TYPE_PIXBUF);
    
    //sortable 
    GtkTreeSortable *sortable = GTK_TREE_SORTABLE (store_list);
    gtk_tree_sortable_set_sort_func (sortable, FILE_NAME, sort_file_names, 
                                     GINT_TO_POINTER (FILE_NAME), NULL);
    gtk_tree_sortable_set_sort_column_id (sortable, FILE_NAME,
                                          GTK_SORT_ASCENDING);
    gtk_tree_sortable_set_sort_column_id (sortable, FILE_SIZE,
                                          GTK_SORT_ASCENDING);
    gtk_tree_sortable_set_sort_column_id (sortable, FILE_DATE,
                                          GTK_SORT_ASCENDING);
    char *working_dir = getenv("HOME");
    if (working_dir != NULL) {
        printf("Home dir in enviroment ");
        printf("%s\n", working_dir);
    }
    else {
        working_dir = pwd();
        if(working_dir != NULL){
            printf("Failed to find Home using current directory \n");
        }
        else{
            printf("Directory error terminate");
            exit(0);
        }
    }
    
    GtkTreeIter iter_p;
    if(list_dir(store_tree, working_dir, iter_p, 0) != 0){
        printf ("Error building tree");
        return 1;
    }
    if(build_list(store_list, working_dir) != 0){
        printf ("Error building tree");
        return 1;
    }
    //build first two views, tree and list.
    GtkWidget *treeview = gtk_tree_view_new ();
    GtkWidget *listview = gtk_tree_view_new ();
    GtkWidget *grid = gtk_grid_new();
    
    build_treeview(treeview);
    build_listview(listview);
    build_infoview(grid, NULL);
    
    GtkTreeSelection *selection;
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(treeview));
    g_signal_connect (G_OBJECT(selection), "changed", 
                      G_CALLBACK(dir_selected), store_list);
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(listview));
    g_signal_connect (G_OBJECT(selection), "changed", 
                      G_CALLBACK(file_selected), grid);
        
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store_tree));
    gtk_tree_view_set_model (GTK_TREE_VIEW (listview), GTK_TREE_MODEL (store_list));

    g_object_unref (store_tree);
    g_object_unref (store_list);
    
    display (treeview, listview, grid);
    
    gtk_main ();
    return 0;
}


