/*
 buildInfoView.h
 */

void build_infoview(GtkWidget *grid, char *file_path);
void check_state(GtkWidget* widget, gpointer data);
void size_path_grid(GtkWidget *grid, GtkWidget *label, char *file_path, int f_size);
void start_fb(GtkWidget *grid, GtkWidget *label);