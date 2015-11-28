/*
buildTree.h
initilize functions for build tree
*/
enum {
    DIRNAME,
    PATH_NAME,
    COLUMNS
};
char *pwd ();
void build_treeview (GtkWidget *treeview);
void display (GtkWidget *treeview);
int list_dir (GtkTreeStore* store, const char * dir_name, GtkTreeIter iter_p, int state);
void item_selected (GtkWidget *selection, gpointer data);

