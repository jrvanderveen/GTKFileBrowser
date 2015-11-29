/*
lsitView.h
functions for list view
 
 */
void dir_selected (GtkWidget *selection, gpointer data);
//void display (GtkWidget *treeview);
void build_listview (GtkWidget *treeview);
int build_list (GtkTreeStore* store, char* dir_name);