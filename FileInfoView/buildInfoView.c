#include <sys/stat.h>
#include <string.h>
#include <gtk/gtk.h>

#include "buildInfoView.h"
#define LEN 15

void check_state(GtkWidget* widget, gpointer data){
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
        {
                g_print("Toggle button activated\n");
        }else
        {
                g_print("Toggle button not activated\n");
        }
}
 
void build_infoview(GtkWidget *grid, char *file_path){
        GtkWidget *perm_toggle, *label;
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
                int f_size = statbuf.st_size;
                size_path_grid(grid, label, file_path, f_size);
            }
            ///path/size---------------------------------
            
            //owner/group            
            label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Owner: me", NULL);
            gtk_grid_attach (GTK_GRID (grid), label, 1, 1, 8, 1);
            gtk_widget_show(label);
            
            label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Group: me", NULL);
            gtk_grid_attach (GTK_GRID (grid), label, 10, 1, 3, 1);
            gtk_widget_show(label);
            //permision label            
            label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Permisions", NULL);
            gtk_grid_attach (GTK_GRID (grid), label, 6, 2, 5, 1);
            gtk_widget_show(label);
            
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

            /////////////permisions
            perm_toggle = gtk_check_button_new_with_mnemonic("r");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 0, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("w");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 2, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("x");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 4, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("r");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 6, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("w");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 8, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("x");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 10, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("r");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 12, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("w");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 14, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);
            
            perm_toggle = gtk_check_button_new_with_mnemonic("x");
            gtk_grid_attach (GTK_GRID (grid), perm_toggle, 16, 4, 2, 1);
            g_signal_connect(perm_toggle, "toggled", G_CALLBACK(check_state), NULL);
            gtk_widget_show(perm_toggle);

        }
}
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
void size_path_grid(GtkWidget *grid, GtkWidget *label, char *file_path, int f_size){
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Path: ", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 0, 0, 2, 1);
    gtk_widget_show(label);
    
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", file_path, NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 2, 0, 15, 1);
    gtk_widget_show(label);
    
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", "Size: ", NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 17, 0, 1, 1);
    gtk_widget_show(label);
    
    char str_size[LEN];
    snprintf(str_size, LEN, "%d", f_size);
    label = gtk_widget_new(GTK_TYPE_LABEL, "label", str_size, NULL);
    gtk_grid_attach (GTK_GRID (grid), label, 18, 0, 3, 1);
    gtk_widget_show(label);
}















