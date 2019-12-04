#include <stdlib.h>
#include <gtk/gtk.h>
//#include "segmentation.h"


char *filename;

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *Submit_button;
GtkWidget *file_chooser;
GtkWidget *progress_bar;
GtkWidget *image1;
GtkWidget *image2;
GtkWidget *frame2;
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
  progress_bar = GTK_WIDGET(gtk_builder_get_object(builder, "progress_bar"));
  image2 = GTK_WIDGET(gtk_builder_get_object(builder, "image2"));
  frame2 = GTK_WIDGET(gtk_builder_get_object(builder, "frame2"));

  gtk_widget_show(window);

  image1 = NULL;

  gtk_main();

  return EXIT_SUCCESS;
}

void on_file_chooser_file_set(GtkFileChooserButton *f)
{
  filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f));
  printf("%s\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));
  printf("openned\n");

  
  if (image1)
  {
  	gtk_container_remove(GTK_CONTAINER(frame2), image1);
  	gtk_widget_hide(image1);
  	image1 = NULL;
  	image2 = gtk_image_new_from_file(filename);
  	gtk_container_add(GTK_CONTAINER(frame2), image2);
  	gtk_widget_show(image2);
  }
  else
  {
  	gtk_container_remove(GTK_CONTAINER(frame2), image2);
  	gtk_widget_hide(image2);
  	image2 = NULL;
  	image1 = gtk_image_new_from_file(filename);
  	gtk_container_add(GTK_CONTAINER(frame2), image1);
  	gtk_widget_show(image1);
  }
}



void on_Submit_button_clicked (GtkButton *b)
{
  //segmentation(filename);
  (void)b;
  printf("submit\n");
}

