/*
 main functions for grid
 
 check_state(GtkWidget* widget, data);
 build_infoview(grid, file_path);
 handel_permision_set(file_path, grid, perm_toggle, statbuf);
 set_checkbox_perm(file_path, perm_toggle, grid, p, O, C, R, S, X);
 permision_usr_grp_oth(grid, label);
 permision_label(grid, label);
 owner_group_value (grid, label, statbuf);
 size_path_grid(grid, label, file_path, statbuf);
 start_fb(grid, label);
 */
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>

#include "buildInfoView.h"
#include "../Utils/utils.h"

#define LEN 20
#define MAX_PATH 1024

/*
 set_checkbox_perm(file_path, perm_toggle, grid, p, O, C, R, S, X);
 callback function for selecting a check box 
 if button is set, set the selected permision and if unset, unset selected permision
 */
void check_state(GtkWidget* widget, char *data){
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))){
        set_permision(data);
        g_print("\nSET: %s", data);
    }
    else {
        unset_permision(data);
        g_print("\nUNSET: %s", data);
    }
}
/*
 build_infoview(grid, file_path);
 main function for grid view 
 set initial atributes
 if the file_path is NULL aka only when starting the fb the call start_fb
 otherwise call functions that set and store information in the grid
 */
void build_infoview(GtkWidget *grid, char *file_path){
        GtkWidget *perm_toggle = gtk_check_button_new(); 
        GtkWidget *label = gtk_label_new("");
        //grid------------------------------
        //gtk_grid_set_column_spacing (GTK_GRID(grid),5);
        gtk_grid_set_row_spacing (GTK_GRID(grid),1);
        gtk_grid_set_column_homogeneous(GTK_GRID (grid),TRUE);
        gtk_grid_set_row_homogeneous(GTK_GRID (grid),TRUE);
        
        if(file_path == NULL){
            start_fb(grid, label);
        }
        else{
            struct stat statbuf;
            if (stat(file_path, &statbuf) == 0){
                size_path_grid(grid, label, file_path, statbuf);
                owner_group_value(grid, label, statbuf);
                permision_label(grid, label);
                permision_usr_grp_oth(grid, label);
                handel_permision_set(file_path, grid, perm_toggle, statbuf);
            }
        }
}
/*
  handel_permision_set(file_path, grid, perm_toggle, statbuf);
  each if/else statement checks a specific file permision
  call set_checkbox_perm with the location in the grid for the permision box and toggel state
 */
void handel_permision_set(char *file_path, GtkWidget *grid, GtkWidget *perm_toggle, struct stat statbuf){    
    //user read
    if((statbuf.st_mode & S_IRUSR) == S_IRUSR){
        set_checkbox_perm(file_path, perm_toggle, grid, " /u-r", 1, 0, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /u-r", 0, 0, 4, 2, 1);
    }
    //user write
    if((statbuf.st_mode & S_IWUSR) == S_IWUSR){
        set_checkbox_perm(file_path, perm_toggle, grid, " /u-w", 1, 2, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /u-w", 0, 2, 4, 2, 1);
    }
    //user execute
    if((statbuf.st_mode & S_IXUSR) == S_IXUSR){
        set_checkbox_perm(file_path, perm_toggle, grid, " /u-x", 1, 4, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /u-x", 0, 4, 4, 2, 1);
    }
    //group read
    if((statbuf.st_mode & S_IRGRP) == S_IRGRP){
        set_checkbox_perm(file_path, perm_toggle, grid, " /g-r", 1, 6, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /g-r", 0, 6, 4, 2, 1);
    }
    //group write
    if((statbuf.st_mode & S_IWGRP) == S_IWGRP){
        set_checkbox_perm(file_path, perm_toggle, grid, " /g-w", 1, 8, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /g-w", 0, 8, 4, 2, 1);
    }
    //group execute
    if((statbuf.st_mode & S_IXGRP) == S_IXGRP){
        set_checkbox_perm(file_path, perm_toggle, grid, " /g-x", 1, 10, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /g-x", 0, 10, 4, 2, 1);
    }
    //other read
    if((statbuf.st_mode & S_IROTH) == S_IROTH){
        set_checkbox_perm(file_path, perm_toggle, grid, " /o-r", 1, 12, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /o-r", 0, 12, 4, 2, 1);
    }
    //other write
    if((statbuf.st_mode & S_IWOTH) == S_IWOTH){
        set_checkbox_perm(file_path, perm_toggle, grid, " /o-w", 1, 14, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /o-w", 0, 14, 4, 2, 1);
    }
    //other execute
    if((statbuf.st_mode & S_IXOTH) == S_IXOTH){
        set_checkbox_perm(file_path, perm_toggle, grid, " /o-x", 1, 16, 4, 2, 1);
    }
    else {
        set_checkbox_perm(file_path, perm_toggle, grid, " /o-x", 0, 16, 4, 2, 1);
    }
}
/*
  set_checkbox_perm(file_path, perm_toggle, grid, p, O, C, R, S, X);
  create a string that is file_path + permision
  permision is " /ugo-rwx"  the / is used later because no file can have a / in its name
  create label with p[4] aka permision
  attack box to grid with toggel state given previously
  the call back functions data will be the file_path + permision string
 */
void set_checkbox_perm(char *file_path, GtkWidget *perm_toggle, GtkWidget *grid, char *p, int O, int C, int R, int S, int X){    //read
    char *change_perm;
    change_perm = (char *) malloc(MAX_PATH);
    int i = 0;
    while(file_path[i] != '\0'){
        change_perm[i] = file_path[i];
        i++;
    }
    int x = 0;
    while(p[x] != '\0'){
        change_perm[i] = p[x];
        i++;
        x++;
    }
    change_perm[i] = '\0';
    if(p != NULL){
        if(p[4] == 'r'){perm_toggle = gtk_check_button_new_with_mnemonic("r");}
        else if(p[4]=='w'){perm_toggle = gtk_check_button_new_with_mnemonic("w");}
        else {perm_toggle = gtk_check_button_new_with_mnemonic("x");}
    }
    else{
        printf("/nError permision not found");
    }
    gtk_grid_attach (GTK_GRID (grid), perm_toggle, C, R, S, X);
    g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), change_perm);
    if(O == 1){gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(perm_toggle), TRUE);}
    else{
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(perm_toggle), FALSE);
    }
    gtk_widget_show(perm_toggle);
    
    
}
/*
  permision_usr_grp_oth(grid, label);
  set label for user group and other
 */
void permision_usr_grp_oth(GtkWidget *grid, GtkWidget *label){
    //owner/group/other            
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Owner", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 0, 3, 6, 1);
    gtk_widget_show(label);
    
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Group", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 6, 3, 6, 1);
    gtk_widget_show(label);
    
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Other", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 12, 3, 6, 1);
    gtk_widget_show(label);    
}
/*
 permision_label(grid, label);
 set label for Permision
 */
void permision_label(GtkWidget *grid, GtkWidget *label){
    //permision label            
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Permisions", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 6, 2, 5, 1);
    gtk_widget_show(label);    
}
/*
 owner_group_value (grid, label, statbuf);
 find the owner and group of a file
 create a group label and user, then labels right next to them with the values found
 */
void owner_group_value (GtkWidget *grid, GtkWidget *label, struct stat statbuf){
    struct group *grp;
    struct passwd *pwd;
    ////owner
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Owner: ", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 10, 1, 1, 1);
    gtk_widget_show(label);
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL){
        printf("\nSuccess Owner name found");
        label = gtk_widget_new(GTK_TYPE_LABEL, "label", pwd->pw_name, NULL);
    }
    else{
        printf("\nOwner name not found. Display udi Number.");
        label = gtk_widget_new(GTK_TYPE_LABEL, "label", statbuf.st_uid, NULL);
    }
    gtk_grid_attach (GTK_GRID (grid), label, 11, 1, 2, 1);
    gtk_widget_show(label);
    
    ////group
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Group: ", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 1, 1, 1);
    gtk_widget_show(label);
    if ((grp = getgrgid(statbuf.st_gid)) != NULL){
        printf("\nSuccess group name found");
        label = gtk_widget_new(GTK_TYPE_LABEL, "label", grp->gr_name, NULL);
    }
    else{
        printf("\nGroup name not found. Display git Number.");
        label = gtk_widget_new(GTK_TYPE_LABEL, "label", statbuf.st_gid, NULL);
    }
    gtk_grid_attach (GTK_GRID (grid), label, 2, 1, 2, 1);
    gtk_widget_show(label);
    
}
/*
 size_path_grid(grid, label, file_path, statbuf);
 find size and path and create labels for them
 */
void size_path_grid(GtkWidget *grid, GtkWidget *label, char *file_path, struct stat statbuf){
    int f_size = statbuf.st_size;
    char description[MAX_PATH];

    strcpy(description, "Path: ");
    strcat(description, file_path);
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", description, NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 0, 10, 1);
    gtk_widget_show(label);
    
    //size
    char str_size[LEN];
    snprintf(str_size, LEN, "%d", f_size);
    strcpy(description, "Size: ");
    strcat(description, str_size);
    
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", description, NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 12, 0, 3, 1);
    gtk_widget_show(label);
}
/*
 start_fb(grid, label);
 if the fb is just created disply the labels with no values
 */
void start_fb(GtkWidget *grid, GtkWidget *label){
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Path/Size", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 0, 4, 1);
    gtk_widget_show(label);
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Owner/Group", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 1, 4, 1);
    gtk_widget_show(label);
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Set/Display Permisions", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 2, 4, 1);
    gtk_widget_show(label);
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Permsions: Owner/Group/Other", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 3, 4, 1);
    gtk_widget_show(label);
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Permision details", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 1, 4, 4, 1);
    gtk_widget_show(label);    
}












