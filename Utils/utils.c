/*
 This file contains funtions used through program any utility this is needed should be found here
 
 dir_selected (selection, store);
 display (treeview, listview, grid); 
 file_selected (selection, grid);
 set_permision(p_info);
 unset_permision(p_info);
 build_fb_input(treeview, listview, grid, store_tree, store_list);
 pwd ();
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

#include "../FileInfoView/buildInfoView.h"
#include "../ListView/buildList.h"
#include "../TreeView/buildTree.h"
#include "../enum.h"

#define MAX_PATH 1024

/*
 set_permision(p_info)
 When a change in a permision togel box is detected if it is toggeled on call set_permision
 dtermine the file location and create a stat for it
 set mode the the files current mode
 determine the permision to be set and XOR it with the current mode
 chmod mode
 */
void set_permision(char *p_info){
    char *p;
    p = strrchr(p_info, '/' );
    p_info[strlen(p_info)-5] = '\0';
    
    struct stat statbuf;
    mode_t mode;
    printf("\nfile_name: %s", p_info);
    if (stat(p_info, &statbuf) == 0){
        printf("\nSuccess: settign premesions");
        
        mode = statbuf.st_mode & 07777;
        if(strcmp(p, "/u-r") == 0){
            mode |= S_IRUSR;   
        }
        else if(strcmp(p, "/u-w") == 0){
            mode |= S_IWUSR;
        }
        else if(strcmp(p, "/u-x") == 0){
            mode |= S_IXUSR;
        }
        else if(strcmp(p, "/g-r") == 0){
            mode |= S_IRGRP;
        }
        else if(strcmp(p, "/g-w") == 0){
            mode |= S_IWGRP;
        }
        else if(strcmp(p, "/g-x") == 0){
            mode |= S_IXGRP;
        }
        else if(strcmp(p, "/o-r") == 0){
            mode |= S_IROTH;
        }
        else if(strcmp(p, "/o-w") == 0){
            mode |= S_IWOTH;
        }
        else{
            mode |= S_IXOTH;
        }
        chmod(p_info, mode);
    }
    else{
        printf("\nError opening File %s", p_info);
    }
    p_info[strlen(p_info)] = ' ';
}
/*
 unset_permision(p_info)
 When a change in a permision togel box is detected if it is toggeled off call unset_permision
 dtermine the file location and create a stat for it
 set mode the the files current mode
 determine the permision to be set and unset that permision in mode
 chmod mode
 */
void unset_permision(char *p_info){
    
    char *p;
    p = strrchr(p_info, '/' );
    p_info[strlen(p_info)-5] = '\0';
    
    struct stat statbuf;
    mode_t mode;
    if (stat(p_info, &statbuf) == 0){
        printf("\nSuccess: unssetting premesions");
        
        mode = statbuf.st_mode & 07777;
        if(strcmp(p, "/u-r") == 0){
            mode &= ~(S_IRUSR);   
        }
        else if(strcmp(p, "/u-w") == 0){
            mode &= ~(S_IWUSR);
        }
        else if(strcmp(p, "/u-x") == 0){
            mode &= ~(S_IXUSR);
        }
        else if(strcmp(p, "/g-r") == 0){
            mode &= ~(S_IRGRP);
        }
        else if(strcmp(p, "/g-w") == 0){
            mode &= ~(S_IWGRP);
        }
        else if(strcmp(p, "/g-x") == 0){
            mode &= ~(S_IXGRP);
        }
        else if(strcmp(p, "/o-r") == 0){
            mode &= ~(S_IROTH);
        }
        else if(strcmp(p, "/o-w") == 0){
            mode &= ~(S_IWOTH);
        }
        else{
            mode &= ~(S_IXOTH);
        }
        chmod(p_info, mode);
    }
    else{
        printf("\nError opening File %s", p_info);
    }
    p_info[strlen(p_info)] = ' ';
}

/*
dir_selected (selection, store)
if a directory form treeview is selected find the path of that directiory form selection
call build_list to creat a new list of everything in the directory selected
 */
void dir_selected (GtkWidget *selection, GtkTreeStore *store) {
    
    GtkTreeModel *model;
    GtkTreeIter iter;
    if (gtk_tree_selection_get_selected (GTK_TREE_SELECTION(selection), 
        &model, &iter)) {
        
        gtk_tree_store_clear(store);
        gchar *path_name;
    
        gtk_tree_model_get (model, &iter, PATH_NAME, &path_name, -1);
        printf("\n\n");
        g_message("Directory selected %s", path_name);
        
        if (build_list(store, (char *)path_name) != 0) {
            printf("\nError building list from data");
            exit(0);
        }
    }
}
/*
 file_selected(selection, grid)
 if an item is selected from the list view find the path to that item
 destroy any information in the current file information panel
 call build list to create a new grid of file information
 */
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
        g_message("FIle selected %s/%s", path_name,file_name);
        
        strcpy(full_name, path_name);
        strcat(full_name, "/");
        strcat(full_name, file_name);
        
        //remove rows from current grid
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        gtk_grid_remove_row (GTK_GRID(grid),0);
        
        build_infoview(grid, full_name);
    }
}

/*
 display(treeview, listview, grid)
 create the main window and its properties
 The three pannels initilized will be passed in 
 this function creates 3 scroll able widgets 
 it places listview and grid in a verticle pane
 and that verticle pane in a horizontal pane with treeview
 */
void display (GtkWidget *treeview, GtkWidget *listview, GtkWidget *grid) {
    
    // create the window
    GtkWidget *window, *hpaned, *vpaned, *scrollerT, *scrollerL, *scrollerG; 
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "File Browser");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (window, 1000, 500);
    g_signal_connect (window, "delete_event", gtk_main_quit, NULL);
    
    // create a scrolled windowc
    scrollerT = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollerT),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    scrollerL = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollerL),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);
    scrollerG = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollerG),
                                    GTK_POLICY_AUTOMATIC,
                                    GTK_POLICY_AUTOMATIC);    
    // create v-pane
    gtk_container_add (GTK_CONTAINER (scrollerL), listview);
    gtk_container_add (GTK_CONTAINER (scrollerG), grid);
    
    vpaned = gtk_paned_new (GTK_ORIENTATION_VERTICAL);
    gtk_paned_pack1 (GTK_PANED (vpaned), scrollerL, TRUE, FALSE);
    gtk_paned_pack2 (GTK_PANED (vpaned), scrollerG, TRUE, FALSE);
    
    // create h-pane
    gtk_container_add (GTK_CONTAINER (scrollerT), treeview);
    hpaned = gtk_paned_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_pack1 (GTK_PANED (hpaned), scrollerT, TRUE, FALSE);
    gtk_paned_pack2 (GTK_PANED (hpaned), vpaned, TRUE, FALSE);
    
    gtk_paned_set_position(GTK_PANED(vpaned), 300);
    gtk_paned_set_position(GTK_PANED(hpaned), 200);
    
    gtk_container_add (GTK_CONTAINER (window), hpaned);
    gtk_widget_show_all (window);
}
/*
 build_fb_input(treeview, listview, grid, store_tree, store_list);
 take widgets treeview listview and grid and call functions that create their graphical aspects
 set up the signal for selecting a directory and item from the listviwew
 using store_tree and store_list fill the tree/list views
 */

void build_fb_input(GtkWidget *treeview, GtkWidget *listview, GtkWidget *grid, GtkTreeStore *store_tree, GtkTreeStore *store_list){
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
}
/*
 pwd()
 create new current working directory string
 */

char *pwd () {
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        printf("\n\n %s \n", cwd);
    }
    else{
        perror("error directory not found");
    }
    return cwd;
}
