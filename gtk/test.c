#include <stdlib.h>
#include <gtk/gtk.h>
#include "segmentation.h"


char *filename;

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *Submit_button;
GtkWidget *file_chooser;
GtkBuilder *builder;


int main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  builder = gtk_builder_new_from_file ("ocr.glade");

  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_builder_connect_signals(builder, NULL);

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  Submit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Submit_button"));
  file_chooser = GTK_WIDGET(gtk_builder_get_object(builder, "file_chooser"));


  gtk_widget_show(window);

  gtk_main();

  return EXIT_SUCCESS;
}

void on_file_chooser_file_set(GtkFileChooserButton *f)
{
  filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
  printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));
}



void on_Submit_button_clicked (GtkButton *b)
{
  segmentation("alphabet.bmp");
  (void)b;
}