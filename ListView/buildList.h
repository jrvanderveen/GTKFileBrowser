/*
lsitView.h
functions for list view
 
 */
void dir_selected (GtkWidget *selection, gpointer data);
//void display (GtkWidget *treeview);
void build_listview (GtkWidget *treeview);
int build_list (GtkTreeStore* store, char* dir_name);
void size_cell_display (GtkTreeViewColumn* col, 
                       GtkCellRenderer* renderer,
                       GtkTreeModel* model,
                       GtkTreeIter* iter,
                       gpointer data );
gint sort_file_names (GtkTreeModel *model,
                      GtkTreeIter *a, GtkTreeIter *b,
                      gpointer data);