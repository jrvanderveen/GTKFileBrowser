/*
 main functions for list view
 
 build_listview:    main function for listview.  find information about all files in directory and store them in store
 build_list:        create the graphical view for list
 sort_file_names:   sort the column given
 */

void build_listview (GtkWidget *treeview);
int build_list (GtkTreeStore* store, char* dir_name);

gint sort_file_names (GtkTreeModel *model,
                      GtkTreeIter *a, GtkTreeIter *b,
                      gpointer data);