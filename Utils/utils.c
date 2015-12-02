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

#include "../FileInfoView/buildInfoView.h"
#include "../ListView/buildList.h"
#include "../enum.h"

#define MAX_PATH 1024

void dir_selected (GtkWidget *selection, GtkTreeStore *store) {
    
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(selection), 
        &model, &iter)) {
        
        gtk_tree_store_clear(store);
        gchar *path_name;
    
        gtk_tree_model_get (model, &iter, PATH_NAME, &path_name, -1);
        printf("\n\n");
        g_message("selected %s", path_name);
        
        if (build_list(store, (char *)path_name) != 0) {
            printf("\nError building list from data");
            exit(0);
        }
    }
}
void file_selected (GtkWidget *selection, GtkWidget *grid) {
    
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(selection), 
        &model, &iter)) {
        gchar *path_name, *file_name;
        char full_name[MAX_PATH];
        
        gtk_tree_model_get (model, &iter, PATH_NAME, &path_name, -1);
        gtk_tree_model_get (model, &iter, FILE_NAME, &file_name, -1);
        
        printf("\n\n");
        g_message("selected %s/%s", path_name,file_name);
        
        strcpy(full_name, path_name);
        strcat(full_name, "/");
        strcat(full_name, file_name);
        
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        
        build_infoview(grid, full_name);
    }
}

void display (GtkWidget *treeview, GtkWidget *listview, GtkWidget *grid) {
    
    // create the window
    GtkWidget *window, *hpaned, *vpaned, *scroller; 
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "File Browser");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 1000, 500);
    g_signal_connect (window, "delete_event", gtk_main_quit, NULL);
    
    // create a scrolled windowc
    scroller = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroller),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    // create v-pane
    vpaned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
    gtk_paned_pack1 (GTK_PANED (vpaned), listview, TRUE, FALSE);
    gtk_paned_pack2 (GTK_PANED (vpaned), grid, TRUE, FALSE);
    
    // create h-pane
    hpaned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_pack1 (GTK_PANED (hpaned), treeview, TRUE, FALSE);
    gtk_paned_pack2 (GTK_PANED (hpaned), vpaned, TRUE, FALSE);

    gtk_container_add (GTK_CONTAINER (scroller), hpaned);
    gtk_container_add (GTK_CONTAINER (window), scroller);
    gtk_widget_show_all (window);
}

char *pwd () {
   char cwd[MAX_PATH];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
    }
   else
       perror("error directory not found");
   return cwd;
}