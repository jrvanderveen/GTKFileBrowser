/*
buildTree.h
initilize functions for build tree
*/
char *pwd ();
void build_treeview (GtkWidget *treeview);
void display (GtkWidget *treeview, GtkWidget *listview);
int list_dir (GtkTreeStore* store, const char * dir_name, GtkTreeIter iter_p, int state);
void item_selected (GtkWidget *selection, GtkTreeStore *store);

