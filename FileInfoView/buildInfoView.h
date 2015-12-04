/*
 initilize functions for buildInfoView.c
 
 set_checkbox_perm:         set the permision check box in specific location and set its initial toggel
 handel_permision_set:      search through all file permisions and call set_checkbox_perm with specific location and toggel information     
 permision_usr_grp_oth:     create labels for user group and other
 permision_label:           creat permision label
 owner_group_value:         create labels with owner and group values 
 build_infoview:            main grid function. set grid atributes and call functions to store and set data
 check_state:               call back function for selecting a check box
 size_path_grid:            create labels with size and path values             
 start_fb                   when fb is initialy started if there are no file selected set labels (slightly differently), with no values
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
