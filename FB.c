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

#include "TreeView/buildTree.h"

#define MAX_PATH 1024

int main(int argc, char **argv) {
    gtk_init (&argc, &argv);
    GtkTreeStore *store = gtk_tree_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
    char *working_dir = getenv("HOME");
    if (working_dir != NULL) {
        printf("Home dir in enviroment ");
        printf("%s\n", working_dir);
    }
    else {
        working_dir = pwd();
        if(working_dir != NULL){
            printf("Failed to find Home using current directory ");
        }
        else{
            printf("Directory error terminate");
            exit(0);
        }
    }
    
    GtkTreeIter iter_p;
    if(list_dir(store, working_dir, iter_p, 0) != 0){
        printf ("Error building tree");
        return 1;
    }
    
    GtkWidget *treeview = gtk_tree_view_new ();
    build_treeview(treeview);
    
    GtkTreeSelection *selection;
    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(treeview));
    g_signal_connect (G_OBJECT(selection), "changed", 
                      G_CALLBACK(item_selected), NULL);
        
    gtk_tree_view_set_model (GTK_TREE_VIEW (treeview), GTK_TREE_MODEL (store));

    g_object_unref (store);
    
    display (treeview);
    
    gtk_main ();
    return 0;
}



