/*
utils.h
*/

void dir_selected (GtkWidget *selection, GtkTreeStore *store);
void display (GtkWidget *treeview, GtkWidget *listview, GtkWidget *grid); 
char *pwd ();
void file_selected (GtkWidget *selection, GtkWidget *grid);
void set_permision(char *p_info);
void unset_permision(char *p_info);