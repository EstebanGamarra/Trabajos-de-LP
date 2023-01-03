/*
 * JuegoVida.c
 *
 *  Created on: 18 may. 2020
 *      Author: Daniel Barboza
 */


#include<time.h>
#include<stdlib.h>
#include<curses.h>
#include <gtk/gtk.h>

GObject *window1;
GtkBuilder *builder;
GObject *boton_empezar;
GObject *entry_tamano;
GtkWidget *window2;
GtkWidget *grid;
GtkWidget *button[3000];
GtkWidget *window3;

void clicked_boton_empezar(GtkWidget *widget, gpointer data);
void click_tablero(GtkWidget *widget, gpointer data);
void clicked_boton_go(GtkWidget *widget, gpointer data);
void clicked_boton_stop(GtkWidget *widget, gpointer data);
void clicked_boton_continue(GtkWidget *widget, gpointer data);
void visual_gtk1();
void visual_gtk2();
void EstadoInicial();
void AnalizarN();
void ImprimirN();
void ImprimirM();
void AnalizarM();
int juego_vida();
int z,x,i,j,tam, count=0,stop=0;
int **n = NULL;
int **m = NULL;

struct lugares {
	int x;
	int y;
};

void clicked_boton_go(GtkWidget *widget, gpointer data) {  //
	gtk_widget_show_all((GtkWidget *) window2);
	g_timeout_add_seconds(1, juego_vida, NULL);
	stop = 1;
}

void clicked_boton_stop(GtkWidget *widget, gpointer data) {
	stop = 0;
}

void clicked_boton_continue(GtkWidget *widget, gpointer data) {
	stop = 1;
}

static void
	activate (GtkApplication *app,
	          gpointer        user_data)
	{
	  GtkWidget *grid;
	  GtkWidget *button;

	  window3 = gtk_application_window_new (app);
	  gtk_window_set_title (GTK_WINDOW (window3), "Consola");
	  gtk_container_set_border_width (GTK_CONTAINER (window3), 10);

	  grid = gtk_grid_new ();

	  gtk_container_add (GTK_CONTAINER (window3), grid);

	  button = gtk_button_new_with_label ("Continue");
	  g_signal_connect (button, "clicked", G_CALLBACK (clicked_boton_continue), NULL);

	  gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

	  button = gtk_button_new_with_label ("Stop");
	  g_signal_connect (button, "clicked", G_CALLBACK (clicked_boton_stop), NULL);

	  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

	  button = gtk_button_new_with_label ("Go");
	  g_signal_connect_swapped (button, "clicked", G_CALLBACK (clicked_boton_go), NULL);

	  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);
	  g_signal_connect(window3, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}

int main (int argc, char *argv[]){
	guint ret;
	GError *error = NULL;
	gtk_init(&argc, &argv);
	builder = gtk_builder_new();
	ret = gtk_builder_add_from_file(builder, "juego_de_la_vida.glade", &error);
	if (ret == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s",
				error->message);
		return 1;
	}
	g_free(error);

	window1 = gtk_builder_get_object(builder, "window1");
	g_signal_connect(window1, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	boton_empezar = gtk_builder_get_object(builder, "boton_empezar");
	g_signal_connect(boton_empezar, "clicked",
			G_CALLBACK (clicked_boton_empezar), NULL);
	entry_tamano = gtk_builder_get_object(builder, "entry_tamano");
	gtk_widget_show_all((GtkWidget *) window1);

	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.JuegoVida", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	gtk_main();
	return status;
}

void genesis() {
	int i, j;
	struct lugares *lugares = NULL;
	lugares = (struct lugares*) malloc(tam * tam * sizeof(struct lugares));
	window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window2), "juego de la vida");
	gtk_container_set_border_width(GTK_CONTAINER(window2), 20);
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window2), grid);
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			if (n[i][j] == 1){
				button[j + (tam * i)] = gtk_button_new_with_label(" ");
			}
			else {
				button[j + (tam * i)] = gtk_button_new_with_label("0");
			}
			lugares[j + (tam * i)].x = i;
			lugares[j + (tam * i)].y = j;
			g_signal_connect(button[j + (tam * i)], "clicked",
					G_CALLBACK (click_tablero), &lugares[j + (tam * i)]);
			gtk_grid_attach(GTK_GRID(grid), button[j + (tam * i)], j, i, 1, 1);
		}
	}
	g_signal_connect(window2, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}
int juego_vida(){
	z=1;
	if(count%2 == 0 && count > 0){
		AnalizarM();
	}
	if(count%2 == 1){
		AnalizarN();
	}
	if (stop == 0) {
		return (TRUE);
	}
	if (stop == 1){
		if (z == 1){
			if(count%2 == 0){
				count++;
				ImprimirN();
				visual_gtk1();
				return (TRUE);
			}
			else if(count%2 == 1){
				count++;
				ImprimirM();
				visual_gtk2();
				return (TRUE);
			}
		}
		else {
			return (FALSE);
		}
	}
	return 0;
}

void AnalizarN(){
	int perimetro=0;
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			if(n[i][j] == 1){
				if ((j + 1) < tam) {
					if (n[i][j + 1] == 1) {
						perimetro++;
					}
				}
				if ((j - 1) >= 0) {
					if (n[i][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i + 1) < tam) {
					if (n[i + 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j + 1) < tam)) {
					if (n[i + 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j - 1) >= 0)) {
					if (n[i + 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i - 1) >= 0) {
					if (n[i - 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j + 1) < tam)) {
					if (n[i - 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j - 1) >= 0)) {
					if (n[i - 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if(perimetro != 3 && perimetro!= 2){
					m[i][j] = 0;
				}
				if (perimetro == 3 || perimetro == 2) {
					m[i][j] = 1;
				}
				perimetro = 0;
			}
			else if (n[i][j] == 0) {
				if ((j + 1) < tam) {
					if (n[i][j + 1] == 1) {
						perimetro++;
					}
				}
				if ((j - 1) >= 0) {
					if (n[i][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i + 1) < tam) {
					if (n[i + 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j + 1) < tam)) {
					if (n[i + 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j - 1) >= 0)) {
					if (n[i + 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i - 1) >= 0) {
					if (n[i - 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j + 1) < tam)) {
					if (n[i - 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j - 1) >= 0)) {
					if (n[i - 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if(perimetro == 3){
					m[i][j] = 1;
				}
				if (perimetro != 3) {
					m[i][j] = 0;
				}
				perimetro = 0;
			}
		}
	}
}

void AnalizarM(){
	int perimetro=0;
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			if(m[i][j] == 1){
				if ((j + 1) < tam) {
					if (m[i][j + 1] == 1) {
						perimetro++;
					}
				}
				if ((j - 1) >= 0) {
					if (m[i][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i + 1) < tam) {
					if (m[i + 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j + 1) < tam)) {
					if (m[i + 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j - 1) >= 0)) {
					if (m[i + 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i - 1) >= 0) {
					if (m[i - 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j + 1) < tam)) {
					if (m[i - 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j - 1) >= 0)) {
					if (m[i - 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if(perimetro != 3 && perimetro!= 2){
					n[i][j] = 0;
				}
				if (perimetro == 3 || perimetro == 2) {
					n[i][j] = 1;
				}
				perimetro = 0;
			}
			else if (m[i][j] == 0) {
				if ((j + 1) < tam) {
					if (m[i][j + 1] == 1) {
						perimetro++;
					}
				}
				if ((j - 1) >= 0) {
					if (m[i][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i + 1) < tam) {
					if (m[i + 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j + 1) < tam)) {
					if (m[i + 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i + 1) < tam) && ((j - 1) >= 0)) {
					if (m[i + 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if ((i - 1) >= 0) {
					if (m[i - 1][j] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j + 1) < tam)) {
					if (m[i - 1][j + 1] == 1) {
						perimetro++;
					}
				}
				if (((i - 1) >= 0) && ((j - 1) >= 0)) {
					if (m[i - 1][j - 1] == 1) {
						perimetro++;
					}
				}
				if(perimetro == 3){
					n[i][j] = 1;
				}
				if (perimetro != 3) {
					n[i][j] = 0;
				}
				perimetro = 0;
			}
		}
	}
}

void EstadoInicial(){					//numeros aleatorios
	srand(time(NULL));
	for (int i=0;i<tam;i++){
		for (int j=0;j<tam;j++){
			n[i][j]=0 + rand()%(2);
		}
	}
}

void ImprimirN(){
	for (int i=0;i<tam;i++){
		for (int j=0;j<tam;j++){
			if (n[i][j]==1){
				printf("0");
			}
			else if (n[i][j]==0){
				printf(" ");
			}
		}
		printf("\n");
	}
}

void ImprimirM(){
	for (int i=0;i<tam;i++){
		for (int j=0;j<tam;j++){
			if (m[i][j]==1){
				printf("0");
			}
			else if (m[i][j]==0){
				printf(" ");
			}
		}
		printf("\n");
	}
}

void clicked_boton_empezar(GtkWidget *widget, gpointer data) {
	gtk_widget_hide((GtkWidget *) window1);
	char cad[20];
	int i;
	strcpy(cad, gtk_entry_get_text((GtkEntry *) entry_tamano));
	tam = atoi(cad);
	n = malloc(tam * sizeof(int *));
	m = malloc(tam * sizeof(int *));
	for (i = 0; i < tam; i++) {
		n[i] = malloc(tam * sizeof(int *));
		m[i] = malloc(tam * sizeof(int *));
	}
	EstadoInicial();
	genesis();
	gtk_widget_show_all (window3);
}

void visual_gtk1() {
	int i, j;
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			if (n[i][j] == 0) {
				gtk_button_set_label(GTK_BUTTON(button[j + tam * i]), "0");
			} else
				gtk_button_set_label(GTK_BUTTON(button[j + tam * i]), " ");

		}
	}
}

void visual_gtk2() {
	int i, j;
	for (i = 0; i < tam; i++) {
		for (j = 0; j < tam; j++) {
			if (m[i][j] == 0) {
				gtk_button_set_label(GTK_BUTTON(button[j + tam * i]), "0");
			} else
				gtk_button_set_label(GTK_BUTTON(button[j + tam * i]), " ");

		}
	}
}

void click_tablero(GtkWidget *widget, gpointer data) {
	struct lugares *pos = data;
	g_print("coordenadas x %d y %d\n", pos->x, pos->y);
	if (n[pos->x][pos->y] == 1) {
		n[pos->x][pos->y] = 0;
		m[pos->x][pos->y] = 0;
		gtk_button_set_label(GTK_BUTTON(widget), "0");
	} else {
		n[pos->x][pos->y] = 1;
		m[pos->x][pos->y] = 1;
		gtk_button_set_label(GTK_BUTTON(widget), " ");
	}
}
