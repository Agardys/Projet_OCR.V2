#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Matrix.h"
#include "segmentation.h"
#include "neural_network.h"

char *text;
char *filename;

GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *Submit_button;
GtkWidget *file_chooser;
GtkWidget *image1;
GtkWidget *image2;
GtkWidget *frame2;
GtkWidget *scroll_window;
GtkWidget *viewport;
GtkWidget *text_view;
GtkWidget *save_button;
GtkTextBuffer *TextBuffer;

GtkBuilder *builder;


int second_main(char* filename)
{
	FILE* fp;
    //int argc,char *argv[]
  


  //=======INITIALISATION DU RÉSEAU DE NEURONE======

  struct Vecteur *vecteur[EX];
  struct Neurone neuronEntree[NUMIN];
  struct Neurone neuronCachee[NUMHID];
  struct Neurone neuronSortie[NUMOUT];
  struct Neurone neuronBiais[NUMBIAS];
  struct Lien *lien[NB_LIENS];
  Network(neuronEntree, neuronCachee, neuronSortie, neuronBiais, lien, vecteur);


  //============== Résultat Réseau ===============


  //compteur de caractères à reconnaitre : 
  int compt = 0;

  int *size = &compt;

  //traitement de tout les caractères de l'image :
  double **Tab = segmentation(filename,size);

  struct Vecteur *lettre[compt];

  for(int i = 0;i<compt;i++)
    lettre[i] = calloc(1, sizeof(struct Vecteur));

  loadImage(lettre,Tab,compt);
  
  //interrogation du caractère pour l'OCR
  fp = fopen("RESULTAT.txt","w");
  for(int k = 0;k<compt;k++)
  {
      for(int i = 0;i<NUMIN;i++)
        neuronEntree[i].poidsSortie = lettre[k]->premier[i];

      for(int i = 0;i<NUMHID;i++)
        calculNeurones(lien, neuronCachee, i);

      int j1 = 0;
      double max1 = 0.0;
      for(int i = 0;i<NUMOUT;i++)
      {
        calculNeurones(lien, neuronSortie, i);
        if(neuronSortie[i].poidsSortie>max1)
        {
          max1 = neuronSortie[i].poidsSortie;
          j1 = i;
        }
      }


      switch((int)lettre[k]->premier[224])
      {
        case 1:
          printf("option 1\n");
          fputc(' ',fp);
          fputc(PrintResultat(j1),fp);
          break;
        case 2:
          printf("option 2\n");
          fputc('\n',fp);
          fputc(PrintResultat(j1),fp);
 	        break;
        case 0:
          printf("option 0\n");
          //fputc('\0',fp);
          fputc(PrintResultat(j1),fp);
          break;
        default:
          printf("option interouvable\n");
      }
  }


  fclose(fp);
  FreeNetwork(lien, vecteur);
  return compt;
}





int main(int argc, char *argv[])
{
  //second_main(argv[1]);
  //return 0;
  //=====================================GTK PART======================================

  gtk_init(&argc, &argv);

  builder = gtk_builder_new_from_file ("ocr.glade");

  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_builder_connect_signals(builder, NULL);

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  Submit_button = GTK_WIDGET(gtk_builder_get_object(builder, "Submit_button"));
  file_chooser = GTK_WIDGET(gtk_builder_get_object(builder, "file_chooser"));
  image2 = GTK_WIDGET(gtk_builder_get_object(builder, "image2"));
  frame2 = GTK_WIDGET(gtk_builder_get_object(builder, "frame2"));
  scroll_window = GTK_WIDGET(gtk_builder_get_object(builder, "scroll_window"));
  viewport = GTK_WIDGET(gtk_builder_get_object(builder, "viewport"));
  text_view = GTK_WIDGET(gtk_builder_get_object(builder, "text_view"));
  save_button = GTK_WIDGET(gtk_builder_get_object(builder, "save"));


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

void on_changed_text(GtkTextBuffer *TextBuffer)
{
  //gtk_widget_show(saveText);
  (void)TextBuffer;
}


void on_save_clicked(GtkButton *b)
{
	GtkWidget *dialog;
	GtkWidget *toplevel = gtk_widget_get_toplevel(GTK_WIDGET(b));
	dialog = gtk_file_chooser_dialog_new("Save", GTK_WINDOW(toplevel), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
	{
		char *filepath;
		filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		if (filepath != NULL)
		{
			char buffer[1000];
  			int i = 0;
  			int c;
  			FILE *fp = fopen("RESULTAT.txt", "r");
  			while(1) 
  			{
    			c = fgetc(fp);
    			if( feof(fp) )
    				break ;
        
    			buffer[i] = (char)c;
    			i += 1;
  				g_file_set_contents (filepath, buffer, strlen(buffer), NULL);
  			}
		}
		else
			printf("error\n");
	}
	gtk_widget_destroy(dialog);
}

void show_text(int compt)
{
  TextBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  g_signal_connect(TextBuffer, "changed", G_CALLBACK(on_changed_text), NULL);
  char buffer[compt * 2];
  int i = 0;
  int c; 
  FILE *fp = fopen("RESULTAT.txt", "r");
  while(1) 
  {
    c = fgetc(fp);
    if( feof(fp) )
    	break ;
        
    buffer[i] = (char)c;
    i += 1;
  }
  fclose(fp);
  gtk_text_buffer_set_text(TextBuffer,(const gchar *) buffer , (gint) -1);
}

void on_Submit_button_clicked (GtkButton *b)
{
  if (filename)
  {
    int compt = second_main(filename);
    show_text(compt);
    return;
  }
  (void)b;
}