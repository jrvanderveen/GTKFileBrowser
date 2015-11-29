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

#include "../ListView/buildList.h"
#include "../enum.h"

#define MAX_PATH 1024

void item_selected (GtkWidget *selection, GtkTreeStore *store) {
    
    GtkTreeModel *model;
    GtkTreeIter iter;
    
    if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(selection), 
        &model, &iter)) {
        
        gtk_tree_store_clear(store);
        gchar *path_name;
    
        gtk_tree_model_get (model, &iter, PATH_NAME, &path_name, -1);
        g_message("selected %s\n", path_name);
        
        if (build_list(store, (char *)path_name) != 0) {
            printf("Error building list from data\n");
            exit(0);
        }
    }
}
