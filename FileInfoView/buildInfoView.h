/*
 buildInfoView.h
 */
struct stat;
void permision_set_usr(GtkWidget *grid, GtkWidget *label, GtkWidget *perm_toggle, struct stat statbuf);
void permision_set_grp(GtkWidget *grid, GtkWidget *label, GtkWidget *perm_toggle, struct stat statbuf);
void permision_set_oth(GtkWidget *grid, GtkWidget *label, GtkWidget *perm_toggle, struct stat statbuf);
void permision_usr_grp_oth(GtkWidget *grid, GtkWidget *label);
void permision_label(GtkWidget *grid, GtkWidget *label);
void owner_group_value (GtkWidget *grid, GtkWidget *label, struct stat statbuf);
void build_infoview(GtkWidget *grid, char *file_path);
void check_state(GtkWidget* widget, gpointer data);
void size_path_grid(GtkWidget *grid, GtkWidget *label, char *file_path, struct stat statbuf);
void start_fb(GtkWidget *grid, GtkWidget *label);