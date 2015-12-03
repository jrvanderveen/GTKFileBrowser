/*
 buildInfoView.h
 */
#define MAX_PATH 1024
struct stat;
void set_checkbox_perm(char *file_path, GtkWidget *perm_toggle, GtkWidget *grid, char *p, int O, int C, int R, int S, int X);
void handel_permision_set(char *file_path, GtkWidget *grid, GtkWidget *perm_toggle, struct stat statbuf);
void permision_usr_grp_oth(GtkWidget *grid, GtkWidget *label);
void permision_label(GtkWidget *grid, GtkWidget *label);
void owner_group_value (GtkWidget *grid, GtkWidget *label, struct stat statbuf);
void build_infoview(GtkWidget *grid, char *file_path);
void check_state(GtkWidget* widget, char *data);
void size_path_grid(GtkWidget *grid, GtkWidget *label, char *file_path, struct stat statbuf);
void start_fb(GtkWidget *grid, GtkWidget *label);



//void permision_set_usr(GtkWidget *grid, GtkWidget *label, GtkWidget *perm_toggle, struct stat statbuf, char *change_perm);
//void permision_set_grp(GtkWidget *grid, GtkWidget *label, GtkWidget *perm_toggle, struct stat statbuf, char *change_perm);
//void permision_set_oth(GtkWidget *grid, GtkWidget *label, GtkWidget *perm_toggle, struct stat statbuf, char *change_perm);