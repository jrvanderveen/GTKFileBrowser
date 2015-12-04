/*
buildTree.h
initilize functions for build tree

build_treeview:     set up the graphical ascept of the tree
build_start_state:  set the head of the tree
build_full_tree:    find and store all directoies in given dir
list_dir:           recursivly open directories
*/
void build_treeview (GtkWidget *treeview);
void build_start_state(DIR *d, GdkPixbuf *image, char *dir_name,  GtkTreeStore *store, GtkTreeIter iter_p);
void build_full_tree(DIR *d, GdkPixbuf *image, char *dir_name, GtkTreeStore *store, GtkTreeIter iter_p);
int list_dir (GtkTreeStore* store, char * dir_name, GtkTreeIter iter_p, int state);


