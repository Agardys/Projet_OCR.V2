#include <stdlib.h>
#include <gtk/gtk.h>
#include "GUI.h"

#define DEFAULT_FILE "main.c"

static void open_file (const gchar *file_name, GtkTextView *p_text_view)
{
  g_return_if_fail (file_name && p_text_view);
  {
    gchar *contents = NULL;

    if (g_file_get_contents (file_name, &contents, NULL, NULL))
    {
      /* Copie de contents dans le GtkTextView */

      gchar *utf8 = NULL;
      GtkTextIter iter;
      GtkTextBuffer *p_text_buffer = NULL;

      p_text_buffer = gtk_text_view_get_buffer (p_text_view);
      gtk_text_buffer_get_iter_at_line (p_text_buffer, &iter, 0);
      utf8 = g_locale_to_utf8 (contents, -1, NULL, NULL, NULL);
      g_free (contents), contents = NULL;
      gtk_text_buffer_insert (p_text_buffer, &iter, utf8, -1);
      g_free (utf8), utf8 = NULL;
    }
    else
    {
      printf ("Impossible d'ouvrir le fichier %s\n", file_name);
    }
  }
}

void open(GtkWidget *widget, gpointer user_data)
{

  GtkWidget *p_dialog = gtk_file_chooser_dialog_new ("Ouvrir un fichier", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *file_name = NULL;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    open_file (file_name, GTK_TEXT_VIEW (user_data));
    g_free (file_name), file_name = NULL;  
  }

  gtk_widget_destroy (p_dialog);

  (void)widget;
}


int main (int argc, char **argv)
{
  
  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);

  /* Creation de la fenetre principale de l'application */
  GtkWidget *p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GtkWidget *open = gtk_button_new_from_stock (GTK_STOCK_OPEN);
  GtkWidget *submit = gtk_button_new_with_label ("Submit");
  GtkWidget *box = gtk_box_new (TRUE, 0);
  GtkWidget *text = gtk_text_view_new();


  gtk_container_add (GTK_CONTAINER(p_window), box);
  gtk_box_pack_start (GTK_BOX(box), text, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX(box), open, FALSE, FALSE, 0);
  gtk_box_pack_start (GTK_BOX(box), submit, FALSE, FALSE, 0);

  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT (open), "clicked", G_CALLBACK (open_file), text);

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);

  /* Lancement de la boucle principale */
  gtk_main();
  return EXIT_SUCCESS;
}