/*
buildTree.h
initilize functions for build tree
*/
void build_treeview (GtkWidget *treeview);
int list_dir (GtkTreeStore* store, const char * dir_name, GtkTreeIter iter_p, int state);

