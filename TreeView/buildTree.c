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
    DIRNAME,
    PATH_NAME,
    COLUMNS
};*/

char *pwd () {
   char cwd[MAX_PATH];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
    }
   else
       perror("error directory not found");
   return cwd;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void build_treeview (GtkWidget *treeview) {
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    // add the Position to the treeview
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes (
                "Name", renderer, "text", DIR_NAME,
                NULL);    
    gtk_tree_view_append_column (GTK_TREE_VIEW (treeview), column);
}

void display (GtkWidget *treeview, GtkWidget *listview) {
    
    // create the window
    GtkWidget *window, *hpaned, *scroller; 
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "WWU Org Chart");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 200, 200);
    g_signal_connect (window, "delete_event", gtk_main_quit, NULL);
    
    // create a scrolled window
    scroller = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroller),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    // create pane
    hpaned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
    
    // pack the containers
    gtk_paned_pack1 (GTK_PANED (hpaned), treeview, TRUE, FALSE);
    gtk_paned_pack2 (GTK_PANED (hpaned), listview, TRUE, FALSE);
    gtk_container_add (GTK_CONTAINER (scroller), hpaned);
    gtk_container_add (GTK_CONTAINER (window), scroller);
    gtk_widget_show_all (window);
}
  
int list_dir (GtkTreeStore* store, const char * dir_name, GtkTreeIter iter_p, int state)
{
    DIR * d;

    /* Open the directory specified by "dir_name". */

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
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
                            DIR_NAME, start_name,
                            PATH_NAME, dir_name,
                            -1);  
        list_dir (store, dir_name, iter_p, 1);
    }
    else{
        GtkTreeIter iter_ch;
        while (1) {
            struct dirent * entry;
            const char * d_name;

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
                        int path_length;
                        char path[PATH_MAX];
        
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
                                            FILE_NAME, " ",
                                            DIR_NAME, d_name,
                                            PATH_NAME, path,
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