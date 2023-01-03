/*
 ============================================================================
 Name        : Animaagkt.c
 Author      : Esteban
 Copyright   : Croqueta con comino.Inc
 ============================================================================
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
struct Grillette {
	GtkWidget *button;
	char tipo;
	int banderota; //0 jugador, 1 cpu, 2 espacio vacio, 3 trampa-indices(A-B-1-2-etc), 4 ficha seleccionada
	int posiciones[2];
} tablero[9][9];
char matriz [9][9]= { //ORDENADO FICHAS FUERTES DELANTE
	{'-','A','B','C','D','E','F','G','H'},
    {'8','I','L','I','I','I','I','I','I'},
    {'7','K','I','J','N','M','K','J','L'},
	{'6','-','-','=','-','-','=','-','-'},
	{'5','-','-','-','-','-','-','-','-'},
	{'4','-','-','-','-','-','-','-','-'},
	{'3','-','-','=','-','-','=','-','-'},
	{'2','Z','W','V','Z','Y','W','V','X'},
	{'1','U','U','U','U','U','U','U','U'}
};
GtkWidget *btn_pasart, *btn_reiniciar, *btn_empezar, *btn_aiuda, *lbl_movimiento_gral;
GtkWidget *btn_aumentar, *btn_disminuir, *btn_cpu, *btn_jugador, *btn_ok, *btn_masinfo, *btn_monitoreo;
GdkPixbuf *gatod,*gatop,*perrod,*perrop,*conejod,*conejop,*camellod;
GdkPixbuf *camellop,*caballod,*caballop,*elefanted,*elefantep;
GdkPixbuf *img_1,*img_2,*img_3,*img_4,*img_5,*img_6,*img_7,*img_8;
GdkPixbuf *img_A,*img_B,*img_C,*img_D,*img_E,*img_F,*img_G,*img_H;
GdkPixbuf *img_trampa,*img_libre;
GtkWidget *win_tablero,*win_opciones, *win_contador, *win_masinfo, *win_aiuda, *lbl_movimientos_gral;
GtkWidget *btn_trnmax, *btn_trnmin, *btn_predet, *btn_manual, *btn_plateadas, *btn_doradas, *lbl_turnminmax;
GtkWidget *tablamasinfo, *grilla; //externos al glade
GtkWidget *lbl_piezas_amigas, *lbl_piezas_enemigas, *lbl_turno, *lbl_movimiento_cpu, *lbl_movimiento_jugador; //labels de la ventana contador
int contconeju=0, contconecpu=0, contperroju=0, contperrocpu=0, contgatoju=0, contgatocpu=0; //1 al 6
int contcabju=0, contcabcpu=0, contcameju=0, contcamecpu=0, contelefju=0, contelefcpu=0; //7 al 13
int turnjugador=0, turncpu=0, turnglob=0, jugadasglobales=0, counturnjugador=0, counturncpu=0, limiteturn=0;
int okflag=0, empezarflag=0, arribajo=0, i, j ,iref, jref, imov, jmov;
char var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12;
//correspondiente a window_masinfo, aka, tabla con informacion de las piezas individuales
GtkWidget *lbl_cont1, *lbl_cont2, *lbl_cont3, *lbl_cont4, *lbl_cont5, *lbl_cont6; //lbl contadores conejo a elefante jugador
GtkWidget *lbl_cont7, *lbl_cont8, *lbl_cont9, *lbl_cont10, *lbl_cont11, *lbl_cont12; //IDEM pero CPU
GtkWidget *lbl_conejo, *lbl_perro, *lbl_gato, *lbl_caballo, *lbl_camello, *lbl_elefante; //indices en la tabla
GtkWidget *lbl_jugador, *lbl_cpu; //indices en la tabla (títulos)

int ganador(){
	int i=0, j=0;
	int contjug=0, contcpu=0;
	int finalj=0, finalcpu=0;
	for (i=0;i<9;i++){
		for(j=0;j<9;j++){
			if (matriz[i][j]==var7){
				contcpu++;
			}
			else if (matriz[i][j]==var1){
				contjug++;
			}
			else if (matriz[1][j]==var7){
				return 1;
			}
			else if (matriz[8][j]==var7){
				return 2;
			}
		}
	}
	if (contjug==0){
		return 2;
	}
	else if(contcpu==0){
		return 1;
	}
	else{
		return 0;
	}
	if(jugadasglobales==turnglob){
		for (i=0;i<9;i++){
			for(j=0;j<9;j++){
				if (matriz[i][j]==var7||matriz[i][j]==var8||matriz[i][j]==var9||
						matriz[i][j]==var10||matriz[i][j]==var11||matriz[i][j]==var12){
					finalcpu++;
				}
				else if(matriz[i][j]==var1||matriz[i][j]==var2||matriz[i][j]==var3||
						matriz[i][j]==var4||matriz[i][j]==var5||matriz[i][j]==var6){
						finalj++;
				}
			}
		}
		if (finalcpu>finalj){
			return 2;
		}
		else{
			return 1;
		}
	}
}
/*void main_loop(){
	while(ganador()!=1||ganador()!=2){
	}
}*/
void on_contador_destroyed(){
	gtk_widget_set_sensitive (btn_monitoreo, TRUE);
	gtk_widget_hide(win_contador);
}
void on_tablero_check1(GtkWidget *button, gpointer *data){ //IMPORTANTE!!!!!!
	int *dataref = data; //i y j, con aritmética de punteros podemos conseguir estos datos apretando cualquier parte del tablero
	//g_print("Fila: %d",*dataref);
	//g_print("Columna. %d", *(dataref+1));
	imov = *dataref;
	jmov = *dataref+1;
	//Si efectivamente es una ficha del jugador
	if (tablero[imov][jmov].banderota==0&&tablero[imov+1][jmov].banderota!=5&&tablero[imov-1][jmov].banderota!=5&&
			tablero[imov][jmov+1].banderota!=5&&tablero[imov][jmov-1].banderota!=5){//OBSERVAMOS SI ES NUESTRA FICHA Y EN LA INMEDIATEZ NO HAY FICHAS YA ELEGIDAS
		tablero[imov][jmov].banderota=5; //indica el primer click de selección de la pieza
	}else if(tablero[imov][jmov].banderota==5){
		iref = *dataref;
		jref = *dataref+1;
		if (tablero[iref][jref].banderota==2){ //movimiento base, el lugar donde apunta es un lugar - disponible
			if(tablero[iref][jref].tipo==var1){
				if(arribajo==1){
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(conejod));
				}else{
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(conejop));
				}
			}
			else if(tablero[iref][jref].tipo==var2){
				if(arribajo==1){
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(gatod));
				}else{
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(gatop));
				}
			}
			else if(tablero[iref][jref].tipo==var3){
				if(arribajo==1){
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(perrod));
				}else{
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(perrop));
				}
			}
			else if(tablero[iref][jref].tipo==var4){
				if(arribajo==1){
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(caballod));
				}else{
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(caballop));
				}
			}
			else if(tablero[iref][jref].tipo==var5){
				if(arribajo==1){
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(camellod));
				}else{
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(camellop));
				}
			}
			else if(tablero[iref][jref].tipo==var6){
				if(arribajo==1){
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(elefanted));
				}else{
				gtk_button_set_image(GTK_BUTTON(tablero[iref][jref].button),gtk_image_new_from_pixbuf(elefantep));
				}
			}
		}
		else{
			imov=0;
			jmov=0;
			iref=0;
			jref=0;
		}
	}
	else{
		jmov=0;
		imov=0;
	}
}
void on_btn_trnmax_clicked(){
	char str_count[10]={0};
	if (turnglob==200){ //si es mayor a 200
		turnglob=200;
	}
	else{
	turnglob=turnglob+10;
	}
	sprintf(str_count, "%d", turnglob);
	gtk_label_set_text(GTK_LABEL(lbl_turnminmax), str_count);
}
void on_btn_trnmin_clicked(){
	char str_count[10]={0};
	if (turnglob==0){ // si es menor a 0
		turnglob=0;
	}
	else{
	turnglob=turnglob-1;
	}
	sprintf(str_count, "%d", turnglob);
	gtk_label_set_text(GTK_LABEL(lbl_turnminmax), str_count);
}
void on_btn_doradas_clicked(int arribajo){
	gtk_widget_set_sensitive (btn_doradas, FALSE);
	gtk_widget_set_sensitive (btn_plateadas, TRUE);
	arribajo = 1; //variable local indica piezas plateadas o doradas elegidas
	var1 = 'U';
	var2 = 'V';
	var3 = 'W';
	var4 = 'X';
	var5= 'Y';
	var6= 'Z';
	var7 = 'I';
	var8 = 'J';
	var9 = 'K';
	var10 = 'L';
	var11= 'M';
	var12= 'N';
}
void on_btn_plateadas_clicked(int arribajo){ //predeterminado al comienzo del juego si no se especifica
	gtk_widget_set_sensitive (btn_doradas, TRUE);
	gtk_widget_set_sensitive (btn_plateadas, FALSE);
	arribajo = 0;
	var1 = 'I';
	var2 = 'J';
	var3 = 'K';
	var4 = 'L';
	var5= 'M';
	var6= 'N';
	var7 = 'U';
	var8 = 'V';
	var9 = 'W';
	var10 = 'X';
	var11= 'Y';
	var12= 'Z';
}
void on_btn_predet_clicked(int pospiezas){
	gtk_widget_set_sensitive (btn_predet, FALSE);
	gtk_widget_set_sensitive (btn_manual, TRUE);
	pospiezas = 1;
}
void on_btn_manual_clicked(int pospiezas){
	gtk_widget_set_sensitive (btn_predet, TRUE);
	gtk_widget_set_sensitive (btn_manual, FALSE);
	pospiezas = 0;
}
void on_btn_aumentar_clicked(){
	char str_count[10]={0};
	if (turnglob==10){ // si es 10
		limiteturn=10;
	}
	else{
	limiteturn=limiteturn+1;
	}
	sprintf(str_count, "%d", limiteturn);
	gtk_label_set_text(GTK_LABEL(lbl_movimientos_gral), str_count);
}
void on_btn_disminuir_clicked(){
	char str_count[10]={0};
	if (limiteturn==0){ // si es menor a 0
		limiteturn=0;
	}
	else{
	limiteturn=limiteturn-1;
	}
	sprintf(str_count, "%d", limiteturn);
	gtk_label_set_text(GTK_LABEL(lbl_movimientos_gral), str_count);
}
void on_btn_pasart_clicked(){ //ponemos a nuestro contador de cpu en 0 y contador turno jugador al máximo
	turnjugador=0;
	turncpu=1;
	counturnjugador=limiteturn;
	gtk_widget_set_sensitive (btn_pasart, FALSE);
}
void on_btn_cpu_clicked(){
	gtk_widget_set_sensitive (btn_jugador, TRUE);
	gtk_widget_set_sensitive (btn_cpu, FALSE);
	gtk_widget_set_sensitive (btn_ok, TRUE);
	turnjugador = 0;
	turncpu= 1;
}
void on_btn_jugador_clicked(){
	gtk_widget_set_sensitive (btn_jugador, FALSE);
	gtk_widget_set_sensitive (btn_cpu, TRUE);
	gtk_widget_set_sensitive (btn_ok, TRUE);
	turnjugador = 1;
	turncpu= 0;
}
void on_btn_ok_clicked(){
	gtk_widget_set_sensitive (btn_ok, FALSE);
	gtk_widget_set_sensitive (btn_disminuir, FALSE);
	gtk_widget_set_sensitive (btn_aumentar, FALSE);
	gtk_widget_set_sensitive (btn_empezar,TRUE);
	gtk_widget_set_sensitive (btn_doradas, FALSE);
	gtk_widget_set_sensitive (btn_plateadas, FALSE);
	gtk_widget_set_sensitive (btn_predet, FALSE);
	gtk_widget_set_sensitive (btn_manual, FALSE);
	gtk_widget_set_sensitive (btn_trnmin, FALSE);
	gtk_widget_set_sensitive (btn_trnmax, FALSE);
	gtk_widget_set_sensitive (btn_jugador, FALSE);
	gtk_widget_set_sensitive (btn_cpu, FALSE);
	gtk_widget_show_all (win_tablero);
	okflag = 1;
}
void on_btn_empezar_clicked(){
	gtk_widget_set_sensitive (btn_ok, FALSE);
	gtk_widget_set_sensitive (btn_disminuir, FALSE);
	gtk_widget_set_sensitive (btn_aumentar, FALSE);
	gtk_widget_set_sensitive (btn_empezar,FALSE);
	gtk_widget_set_sensitive (btn_pasart, TRUE);
	gtk_widget_set_sensitive (btn_reiniciar, TRUE);
	gtk_widget_set_sensitive (btn_doradas, FALSE);
	gtk_widget_set_sensitive (btn_plateadas, FALSE);
	gtk_widget_set_sensitive (btn_predet, FALSE);
	gtk_widget_set_sensitive (btn_manual, FALSE);
	gtk_widget_set_sensitive (btn_trnmin, FALSE);
	gtk_widget_set_sensitive (btn_trnmax, FALSE);
	gtk_widget_set_sensitive (btn_jugador, FALSE);
	gtk_widget_set_sensitive (btn_cpu, FALSE);
	empezarflag = 1;
}
void inicializar_opciones(){
	gtk_window_set_title (GTK_WINDOW (win_opciones), "Menú Principal");
	g_signal_connect(win_opciones, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_set_sensitive (btn_aiuda, TRUE);
	gtk_widget_set_sensitive (btn_pasart, FALSE);
	gtk_widget_set_sensitive (btn_reiniciar, FALSE);
	gtk_widget_set_sensitive (btn_cpu, TRUE);
	gtk_widget_set_sensitive (btn_jugador, TRUE);
	gtk_widget_set_sensitive (btn_ok, FALSE);
	gtk_widget_set_sensitive (btn_disminuir, TRUE);
	gtk_widget_set_sensitive (btn_aumentar, TRUE);
	gtk_widget_set_sensitive (btn_doradas, TRUE);
	gtk_widget_set_sensitive (btn_plateadas, TRUE);
	gtk_widget_set_sensitive (btn_predet, TRUE);
	gtk_widget_set_sensitive (btn_manual, TRUE);
	gtk_widget_set_sensitive (btn_trnmin, TRUE);
	gtk_widget_set_sensitive (btn_trnmax, TRUE);
	gtk_widget_set_sensitive (btn_empezar,FALSE);
	gtk_widget_show_all (win_opciones);
}
void inicializar_contador(){
	char amig[10]={0}, enemig[10]={0}, trn_cpu[10]={0}, trn_jug[10]={0}, turno[10]={0};
	int amigo, enemigo, cpu, jug, turn;
	amigo = contconeju + contperroju + contgatoju + contcabju + contcameju + contelefju;
	enemigo = contconecpu + contperrocpu + contgatocpu + contcabcpu + contcamecpu + contelefcpu;
	cpu = counturncpu;
	jug = counturnjugador;
	turn = turnglob;
	gtk_window_set_title (GTK_WINDOW (win_contador), "Monitoreo");
	g_signal_connect(win_contador, "destroy", G_CALLBACK(gtk_window_close), NULL);
	sprintf(amig, "%d", amigo);
	gtk_label_set_text(GTK_LABEL(lbl_piezas_amigas), amig);
	sprintf(enemig, "%d", enemigo);
	gtk_label_set_text(GTK_LABEL(lbl_piezas_enemigas), enemig);
	sprintf(trn_cpu, "%d", cpu);
	gtk_label_set_text(GTK_LABEL(lbl_movimiento_cpu), trn_cpu);
	sprintf(trn_jug, "%d", jug);
	gtk_label_set_text(GTK_LABEL(lbl_movimiento_jugador), trn_jug);
	sprintf(turno, "%d", turn);
	gtk_label_set_text(GTK_LABEL(lbl_turno), turno);
	gtk_widget_set_sensitive (btn_masinfo,TRUE);
	//gtk_widget_show_all(win_contador);
}
void actualizar_contador(){
	char amig[10]={0}, enemig[10]={0}, trn_cpu[10]={0}, trn_jug[10]={0}, turno[10]={0};
	int amigo, enemigo, cpu, jug, turn;
	amigo = contconeju + contperroju + contgatoju + contcabju + contcameju + contelefju;
	enemigo = contconecpu + contperrocpu + contgatocpu + contcabcpu + contcamecpu + contelefcpu;
	cpu = counturncpu;
	jug = counturnjugador;
	turn = turnglob;
	sprintf(amig, "%d", amigo);
	gtk_label_set_text(GTK_LABEL(lbl_piezas_amigas), amig);
	sprintf(enemig, "%d", enemigo);
	gtk_label_set_text(GTK_LABEL(lbl_piezas_enemigas), enemig);
	sprintf(trn_cpu, "%d", cpu);
	gtk_label_set_text(GTK_LABEL(lbl_movimiento_cpu), trn_cpu);
	sprintf(trn_jug, "%d", jug);
	gtk_label_set_text(GTK_LABEL(lbl_movimiento_jugador), trn_jug);
	sprintf(turno, "%d", turn);
	gtk_label_set_text(GTK_LABEL(lbl_turno), turno);
	gtk_widget_show_all(win_contador);
}
void on_btn_monitoreo_clicked(){
	gtk_widget_set_sensitive (btn_monitoreo, FALSE);
	actualizar_contador();
}
void inicializar_tablero(){
//---------- SETEAR PIEZAS EN EL TABLERO POR PRIMERA VEZ (pasar a subrutina)
    grilla = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(win_tablero), grilla);
	int i,j;
	for (i=0;i<9;i++){
			for (j=0;j<9;j++){
				tablero[i][j].button = gtk_button_new();
				if (matriz[i][j]=='U'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(conejod));
					tablero[i][j].tipo = 'U';
					if (arribajo==0){
						tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 1;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='V'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(gatod));
					tablero[i][j].tipo = 'V';
					if (arribajo==0){
						tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 1;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='W'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(perrod));
					tablero[i][j].tipo = 'W';
					if (arribajo==0){
						tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 1;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='X'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(caballod));
					tablero[i][j].tipo = 'X';
					if (arribajo==0){
						tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 1;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='Y'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(camellod));
					tablero[i][j].tipo = 'Y';
					if (arribajo==0){
						tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 1;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='Z'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(elefanted));
					tablero[i][j].tipo = 'Z';
					if (arribajo==0){
						tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 1;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='I'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(conejop));
					tablero[i][j].tipo = 'I';
					if (arribajo==0){
						tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 0;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='J'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(gatop));
					tablero[i][j].tipo = 'J';
					if (arribajo==0){
						tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 0;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='K'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(perrop));
					tablero[i][j].tipo = 'K';
					if (arribajo==0){
						tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 0;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='L'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(caballop));
					tablero[i][j].tipo = 'L';
					if (arribajo==0){
						tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 0;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='M'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(camellop));
					tablero[i][j].tipo = 'M';
					if (arribajo==0){
						tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 0;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='N'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(elefantep));
					tablero[i][j].tipo = 'N';
					if (arribajo==0){
						tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
					}
					else{
						tablero[i][j].banderota = 0;
					}
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='-'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_libre));
					tablero[i][j].tipo = '-';
					tablero[i][j].banderota = 2; //banderota 2 simboliza un espacio vacío
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='='){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_trampa));
					tablero[i][j].tipo = '=';
					tablero[i][j].banderota = 3; //banderota 3 simboliza un espacio trampa
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='1'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_1));
					tablero[i][j].tipo = '1';
					tablero[i][j].banderota = 4; //banderota 3 simboliza índice (lugar prohibido)
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='2'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_2));
					tablero[i][j].tipo = '2';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='3'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_3));
					tablero[i][j].tipo = '3';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='4'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_4));
					tablero[i][j].tipo = '4';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='5'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_5));
					tablero[i][j].tipo = '5';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='6'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_6));
					tablero[i][j].tipo = '6';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='7'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_7));
					tablero[i][j].tipo = '7';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='8'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_8));
					tablero[i][j].tipo = '8';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='A'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_A));
					tablero[i][j].tipo = 'A';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='B'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_B));
					tablero[i][j].tipo = 'B';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='C'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_C));
					tablero[i][j].tipo = 'C';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='D'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_D));
					tablero[i][j].tipo = 'D';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='E'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_E));
					tablero[i][j].tipo = 'E';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='F'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_F));
					tablero[i][j].tipo = 'F';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='G'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_G));
					tablero[i][j].tipo = 'G';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
				else if (matriz[i][j]=='H'){
					gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_H));
					tablero[i][j].tipo = 'H';
					tablero[i][j].banderota = 4;
					tablero[i][j].posiciones[0]=i;
					tablero[i][j].posiciones[1]=j;
					g_signal_connect(tablero[i][j].button, "clicked", G_CALLBACK(on_tablero_check1), &tablero[i][j].posiciones);
				}
	    		gtk_grid_attach (GTK_GRID(grilla), tablero[i][j].button, j, i, 1, 1);
	    	}
	    }
	    gtk_window_set_title (GTK_WINDOW (win_tablero), "Arimaa");
	    g_signal_connect(win_tablero, "destroy", G_CALLBACK(gtk_window_close), NULL);
	   // gtk_widget_show_all (win_tablero);
}
void inicializar_masinfo(){
	gtk_window_set_title (GTK_WINDOW(win_masinfo), "REG");
	tablamasinfo = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER(win_masinfo), tablamasinfo);
	lbl_conejo = gtk_label_new ("Conejos:");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_conejo,0,1,1,1);
	lbl_gato = gtk_label_new ("Gatos:");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_gato,0,2,1,1);
	lbl_perro = gtk_label_new ("Perros:");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_perro,0,3,1,1);
	lbl_caballo = gtk_label_new ("Caballos:");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_caballo,0,4,1,1);
	lbl_camello = gtk_label_new ("Camellos:");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_camello,0,5,1,1);
	lbl_elefante = gtk_label_new ("Elefantes:");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_elefante,0,6,1,1);
	lbl_jugador = gtk_label_new ("Jugador");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_jugador,1,0,1,1);
	lbl_cpu = gtk_label_new ("CPU");
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cpu,2,0,1,1);
	//CONTADORES
	//JUGADOR
	lbl_cont1 = gtk_label_new ("8"); //conejo
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont1,1,1,1,1);
	lbl_cont2 = gtk_label_new ("2"); //gato
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont2,1,2,1,1);
	lbl_cont3 = gtk_label_new ("2"); //perro
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont3,1,3,1,1);
	lbl_cont4 = gtk_label_new ("2"); //caballo
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont4,1,4,1,1);
	lbl_cont5 = gtk_label_new ("1"); //camello
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont5,1,5,1,1);
	lbl_cont6 = gtk_label_new ("1"); //elefante
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont6,1,6,1,1);
	//CPU
	lbl_cont7 = gtk_label_new ("8"); //conejo
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont7,2,1,1,1);
	lbl_cont8 = gtk_label_new ("2"); //gato
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont8,2,2,1,1);
	lbl_cont9 = gtk_label_new ("2"); //perro
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont9,2,3,1,1);
	lbl_cont10 = gtk_label_new ("2"); //caballo
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont10,2,4,1,1);
	lbl_cont11 = gtk_label_new ("1"); //camello
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont11,2,5,1,1);
	lbl_cont12 = gtk_label_new ("1"); //elefante
	gtk_grid_attach (GTK_GRID(tablamasinfo),lbl_cont12,2,6,1,1);
}
void actualizar_masinfo(){ //actualizar a cada rato masinfo (mostrar)
	char ccontconeju[10], ccontconecpu[10], ccontperroju[10], ccontperrocpu[10], ccontgatoju[10], ccontgatocpu[10];
	char ccontcaballoju[10], ccontcaballocpu[10], ccontcamelloju[10], ccontcamellocpu[10], ccontelefju[10], ccontelefcpu[10];
	sprintf(ccontconeju, "%d", contconeju);
	gtk_label_set_text(GTK_LABEL(lbl_cont1), ccontconeju);
	sprintf(ccontconecpu, "%d", contconecpu);
	gtk_label_set_text(GTK_LABEL(lbl_cont7), ccontconecpu);
	sprintf(ccontgatoju, "%d", contgatoju);
	gtk_label_set_text(GTK_LABEL(lbl_cont2), ccontgatoju);
	sprintf(ccontgatocpu, "%d", contgatocpu);
	gtk_label_set_text(GTK_LABEL(lbl_cont8), ccontgatocpu);
	sprintf(ccontperroju, "%d", contperroju);
	gtk_label_set_text(GTK_LABEL(lbl_cont3), ccontperroju);
	sprintf(ccontperrocpu, "%d", contperrocpu);
	gtk_label_set_text(GTK_LABEL(lbl_cont9), ccontperrocpu);
	sprintf(ccontcaballoju, "%d", contcabju);
	gtk_label_set_text(GTK_LABEL(lbl_cont4), ccontcaballoju);
	sprintf(ccontcaballocpu, "%d", contcabcpu);
	gtk_label_set_text(GTK_LABEL(lbl_cont10), ccontcaballocpu);
	sprintf(ccontcamelloju, "%d", contcameju);
	gtk_label_set_text(GTK_LABEL(lbl_cont5), ccontcamelloju);
	sprintf(ccontcamellocpu, "%d", contcamecpu);
	gtk_label_set_text(GTK_LABEL(lbl_cont11), ccontcamellocpu);
	sprintf(ccontelefju, "%d", contelefju);
	gtk_label_set_text(GTK_LABEL(lbl_cont6), ccontelefju);
	sprintf(ccontelefcpu, "%d", contelefcpu);
	gtk_label_set_text(GTK_LABEL(lbl_cont12), ccontelefcpu);
}
void on_btn_masinfo_clicked(){ // click masinfo
	gtk_widget_set_sensitive(btn_masinfo, FALSE);
	actualizar_masinfo(); //actualiza un vez para mostrar la ventana
	gtk_widget_show_all(win_masinfo);
}
/*void on_masinfo_destroyed(){ //X masinfo
	gtk_widget_set_sensitive (btn_masinfo, TRUE); //volvemos a activar el botón de ver la info
	gtk_widget_hide (win_masinfo); //cerrar sólo la ventana, no el gtk
}*/
void reiniciar_tablero(){
	int i,j;
	//Reinicio de la matriz
	matriz [0][0]='-';
	matriz [0][1]='A';
	matriz [0][2]='B';
    matriz [0][3]='C';
	matriz [0][4]='D';
	matriz [0][5]='E';
	matriz [0][6]='F';
	matriz [0][7]='G';
	matriz [0][8]='H';
	matriz [1][0]='8';
	matriz [2][0]='7';
	matriz [3][0]='6';
	matriz [4][0]='5';
	matriz [5][0]='4';
	matriz [6][0]='3';
	matriz [7][0]='2';
	matriz [8][0]='1';
	for (i=1;i<9;i++){
		for (j=1;j<9;j++){
				matriz[i][j]='-';
		}
	}
	matriz [3][3]='=';
	matriz [3][6]='=';
	matriz [6][6]='=';
	matriz [6][3]='=';
	//--------------------
	for (i=0;i<9;i++){
		for (j=0;j<9;j++){
			if (matriz[i][j]=='U'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(conejod));
				tablero[i][j].tipo = 'U';
				if (arribajo==0){
					tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 1;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='V'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(gatod));
				tablero[i][j].tipo = 'V';
				if (arribajo==0){
					tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 1;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='W'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(perrod));
				tablero[i][j].tipo = 'W';
				if (arribajo==0){
					tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 1;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='X'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(caballod));
				tablero[i][j].tipo = 'X';
				if (arribajo==0){
					tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 1;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='Y'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(camellod));
				tablero[i][j].tipo = 'Y';
				if (arribajo==0){
					tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 1;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='Z'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(elefanted));
				tablero[i][j].tipo = 'Z';
				if (arribajo==0){
					tablero[i][j].banderota = 0; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 1;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='I'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(conejop));
				tablero[i][j].tipo = 'I';
				if (arribajo==0){
					tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 0;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='J'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(gatop));
				tablero[i][j].tipo = 'J';
				if (arribajo==0){
					tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 0;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='K'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(perrop));
				tablero[i][j].tipo = 'K';
				if (arribajo==0){
					tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 0;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='L'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(caballop));
				tablero[i][j].tipo = 'L';
				if (arribajo==0){
					tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 0;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='M'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(camellop));
				tablero[i][j].tipo = 'M';
				if (arribajo==0){
					tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 0;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='N'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(elefantep));
				tablero[i][j].tipo = 'N';
				if (arribajo==0){
					tablero[i][j].banderota = 1; //banderota 0 para jugador 1 para enemigo
				}
				else{
					tablero[i][j].banderota = 0;
				}
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='-'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_libre));
				tablero[i][j].tipo = '-';
				tablero[i][j].banderota = 2; //banderota 2 simboliza un espacio vacío
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='='){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_trampa));
				tablero[i][j].tipo = '=';
				tablero[i][j].banderota = 3; //banderota 3 simboliza un espacio trampa
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='1'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_1));
				tablero[i][j].tipo = '1';
				tablero[i][j].banderota = 4; //banderota 3 simboliza índice (lugar prohibido)
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='2'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_2));
				tablero[i][j].tipo = '2';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='3'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_3));
				tablero[i][j].tipo = '3';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='4'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_4));
				tablero[i][j].tipo = '4';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='5'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_5));
				tablero[i][j].tipo = '5';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='6'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_6));
				tablero[i][j].tipo = '6';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='7'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_7));
				tablero[i][j].tipo = '7';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='8'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_8));
				tablero[i][j].tipo = '8';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='A'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_A));
				tablero[i][j].tipo = 'A';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='B'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_B));
				tablero[i][j].tipo = 'B';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='C'){
				tablero[i][j].tipo = 'C';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='D'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_D));
				tablero[i][j].tipo = 'D';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='E'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_E));
				tablero[i][j].tipo = 'E';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='F'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_F));
				tablero[i][j].tipo = 'F';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='G'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_G));
				tablero[i][j].tipo = 'G';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
			else if (matriz[i][j]=='H'){
				gtk_button_set_image(GTK_BUTTON(tablero[i][j].button),gtk_image_new_from_pixbuf(img_H));
				tablero[i][j].tipo = 'H';
				tablero[i][j].banderota = 4;
				tablero[i][j].posiciones[0]=i;
				tablero[i][j].posiciones[1]=j;
			}
		}
	}
}
void on_btn_reiniciar_clicked(){
	reiniciar_tablero();
	//REINICIO MI CONTADOR TAMBIEN OJO
	char amig[10]={0}, enemig[10]={0}, trn_cpu[10]={0}, trn_jug[10]={0}, turno[10]={0};
	int amigo, enemigo, cpu, jug, turn;
	amigo = contconeju + contperroju + contgatoju + contcabju + contcameju + contelefju;
	enemigo = contconecpu + contperrocpu + contgatocpu + contcabcpu + contcamecpu + contelefcpu;
	cpu = counturncpu;
	jug = counturnjugador;
	turn = turnglob;
	sprintf(amig, "%d", amigo);
	gtk_label_set_text(GTK_LABEL(lbl_piezas_amigas), amig);
	sprintf(enemig, "%d", enemigo);
	gtk_label_set_text(GTK_LABEL(lbl_piezas_enemigas), enemig);
	sprintf(trn_cpu, "%d", cpu);
	gtk_label_set_text(GTK_LABEL(lbl_movimiento_cpu), trn_cpu);
	sprintf(trn_jug, "%d", jug);
	gtk_label_set_text(GTK_LABEL(lbl_movimiento_jugador), trn_jug);
	sprintf(turno, "%d", turn);
	gtk_label_set_text(GTK_LABEL(lbl_turno), turno);
	//---------------------------------------------------------
	gtk_widget_set_sensitive (btn_masinfo,TRUE);
	gtk_widget_set_sensitive (btn_pasart, FALSE);
	gtk_widget_set_sensitive (btn_reiniciar, FALSE);
	gtk_widget_set_sensitive (btn_cpu, TRUE);
	gtk_widget_set_sensitive (btn_jugador, TRUE);
	gtk_widget_set_sensitive (btn_ok, FALSE);
	gtk_widget_set_sensitive (btn_disminuir, TRUE);
	gtk_widget_set_sensitive (btn_aumentar, TRUE);
	gtk_widget_set_sensitive (btn_empezar,FALSE);
	gtk_widget_set_sensitive (btn_doradas, TRUE);
	gtk_widget_set_sensitive (btn_plateadas, TRUE);
	gtk_widget_set_sensitive (btn_predet, TRUE);
	gtk_widget_set_sensitive (btn_manual, TRUE);
	gtk_widget_set_sensitive (btn_trnmin, TRUE);
	gtk_widget_set_sensitive (btn_trnmax, TRUE);
	gtk_widget_hide (win_tablero);
	gtk_widget_hide (win_masinfo);
	gtk_widget_hide (win_contador);
	contconeju=8;
	contconecpu=2;
	contperroju=2;
	contperrocpu=2;
	contgatoju=2;
	contgatocpu=2;
	contcabju=2;
	contcabcpu=2;
	contcameju=1;
	contcamecpu=1;
	contelefju=1;
	contelefcpu=1;
	turnjugador=0;
	turncpu=0;
	turnglob=0;
	jugadasglobales=0;
	counturnjugador=0;
	counturncpu=0;
	limiteturn=0;
	okflag=0;
	empezarflag=0;
	//además actualizo masinfo, en este caso, reiniciado
	actualizar_masinfo();
	actualizar_contador();
}
void on_btn_aiuda_clicked(){
	gtk_widget_set_sensitive (btn_aiuda, FALSE);
	gtk_widget_show_all(win_aiuda);
}
void on_aiuda_destroyed(){
	gtk_widget_set_sensitive (btn_aiuda, TRUE);
	gtk_widget_hide(win_aiuda);
}
void inicializar_aiuda(){
	gtk_window_set_title (GTK_WINDOW (win_aiuda), "Ayuda");
	g_signal_connect(win_aiuda, "destroy", G_CALLBACK(on_aiuda_destroyed), NULL);
}
int main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkBuilder *builder;
    //Ventanas ajenas al glade (creadas por línea de códigos)
	builder = gtk_builder_new_from_file("/home/lp1-2019/eclipse-workspace/ArimaaGTK/arimaa_gtk.glade");
    win_masinfo = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    win_tablero = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //IMAGENES
    gatod = gdk_pixbuf_new_from_file ("GD.jpg", NULL);
    gatop = gdk_pixbuf_new_from_file ("GP.jpg", NULL);
    perrod = gdk_pixbuf_new_from_file ("PD.jpg", NULL);
    perrop = gdk_pixbuf_new_from_file ("PP.jpg", NULL);
    conejod = gdk_pixbuf_new_from_file ("COD.jpg", NULL);
    conejop = gdk_pixbuf_new_from_file ("COP.jpg", NULL);
    camellod = gdk_pixbuf_new_from_file ("CAD.png", NULL);
    camellop = gdk_pixbuf_new_from_file ("CAP.png", NULL);
    caballod = gdk_pixbuf_new_from_file ("CD.jpg", NULL);
    caballop = gdk_pixbuf_new_from_file ("CP.jpg", NULL);
    elefanted = gdk_pixbuf_new_from_file ("ED.jpg", NULL);
    elefantep = gdk_pixbuf_new_from_file ("EP.jpg", NULL);
    img_1 = gdk_pixbuf_new_from_file ("1.png", NULL);
    img_2 = gdk_pixbuf_new_from_file ("2.png", NULL);
    img_3 = gdk_pixbuf_new_from_file ("3.png", NULL);
    img_4 = gdk_pixbuf_new_from_file ("4.png", NULL);
    img_5 = gdk_pixbuf_new_from_file ("5.png", NULL);
    img_6 = gdk_pixbuf_new_from_file ("6.png", NULL);
    img_7 = gdk_pixbuf_new_from_file ("7.png", NULL);
    img_8 = gdk_pixbuf_new_from_file ("8.png", NULL);
    img_A = gdk_pixbuf_new_from_file ("A.jpg", NULL);
    img_B = gdk_pixbuf_new_from_file ("B.jpeg", NULL);
    img_C = gdk_pixbuf_new_from_file ("C.jpg", NULL);
    img_D = gdk_pixbuf_new_from_file ("D.jpg", NULL);
    img_E = gdk_pixbuf_new_from_file ("E.jpg", NULL);
    img_F = gdk_pixbuf_new_from_file ("F.jpg", NULL);
    img_G = gdk_pixbuf_new_from_file ("G.jpg", NULL);
    img_H = gdk_pixbuf_new_from_file ("H.jpg", NULL);
    img_trampa = gdk_pixbuf_new_from_file ("Trampa.jpg", NULL);
    img_libre = gdk_pixbuf_new_from_file ("Libre.jpg", NULL);
    //------------CONEXION DE LAS SEÑALES AL GTK
    win_contador = GTK_WIDGET (gtk_builder_get_object(builder, "win_contador"));
    win_opciones = GTK_WIDGET (gtk_builder_get_object(builder, "win_opciones"));
    win_aiuda = GTK_WIDGET (gtk_builder_get_object(builder, "win_aiuda"));
    //Ventana CPU
    btn_pasart = GTK_WIDGET(gtk_builder_get_object(builder, "btn_pasart"));
    btn_reiniciar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_reiniciar"));
    btn_empezar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_empezar"));
	btn_aiuda = GTK_WIDGET(gtk_builder_get_object(builder, "btn_aiuda"));
	btn_cpu = GTK_WIDGET(gtk_builder_get_object(builder, "btn_cpu"));
	btn_jugador = GTK_WIDGET(gtk_builder_get_object(builder, "btn_jugador"));
	btn_ok = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ok"));
	lbl_turno = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_turno"));
	btn_aumentar = GTK_WIDGET(gtk_builder_get_object(builder, "btn_aumentar"));
	btn_disminuir = GTK_WIDGET(gtk_builder_get_object(builder, "btn_disminuir"));
	btn_doradas = GTK_WIDGET(gtk_builder_get_object(builder, "btn_doradas"));
	btn_plateadas = GTK_WIDGET(gtk_builder_get_object(builder, "btn_plateadas"));
	btn_trnmax = GTK_WIDGET(gtk_builder_get_object(builder, "btn_turnmax"));
	btn_trnmin = GTK_WIDGET(gtk_builder_get_object(builder, "btn_turnmin"));
	btn_manual = GTK_WIDGET(gtk_builder_get_object(builder, "btn_manual"));
	btn_predet = GTK_WIDGET(gtk_builder_get_object(builder, "btn_rand"));
	lbl_turnminmax = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_turnminmax"));
	lbl_movimientos_gral = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_movimientos_gral"));
	btn_monitoreo = GTK_WIDGET(gtk_builder_get_object(builder, "btn_monitoreo"));
	//Ventana Contador
	btn_masinfo = GTK_WIDGET(gtk_builder_get_object(builder, "btn_masinfo"));
	lbl_movimiento_cpu = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_movimiento_cpu"));
	lbl_movimiento_jugador = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_movimiento_jugador"));
	lbl_piezas_amigas = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_piezas_amigas"));
	lbl_piezas_enemigas = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_piezas_enemigas"));
	//-----------------CONEXION---SEÑALES CALLBACKS
	g_signal_connect (win_masinfo, "destroy", G_CALLBACK (gtk_window_close), NULL);
	g_signal_connect(win_contador, "destroy", G_CALLBACK(gtk_window_close), NULL);
	//Botones
	g_signal_connect (btn_pasart, "clicked", G_CALLBACK(on_btn_pasart_clicked), NULL);
	g_signal_connect (btn_reiniciar, "clicked", G_CALLBACK(on_btn_reiniciar_clicked), NULL);
	g_signal_connect (btn_empezar, "clicked", G_CALLBACK(on_btn_empezar_clicked), NULL);
	g_signal_connect (btn_aiuda, "clicked", G_CALLBACK(on_btn_aiuda_clicked), NULL);
	g_signal_connect (btn_cpu, "clicked", G_CALLBACK(on_btn_cpu_clicked), NULL);
	g_signal_connect (btn_jugador, "clicked", G_CALLBACK(on_btn_jugador_clicked), NULL);
	g_signal_connect (btn_ok, "clicked", G_CALLBACK(on_btn_ok_clicked), NULL);
	g_signal_connect (btn_aumentar, "clicked", G_CALLBACK(on_btn_aumentar_clicked), NULL);
	g_signal_connect (btn_disminuir, "clicked", G_CALLBACK(on_btn_disminuir_clicked), NULL);
	g_signal_connect (btn_doradas, "clicked", G_CALLBACK(on_btn_doradas_clicked), NULL);
	g_signal_connect (btn_plateadas, "clicked", G_CALLBACK(on_btn_plateadas_clicked), NULL);
	g_signal_connect (btn_trnmax, "clicked", G_CALLBACK(on_btn_trnmax_clicked), NULL);
	g_signal_connect (btn_trnmin, "clicked", G_CALLBACK(on_btn_trnmin_clicked), NULL);
	g_signal_connect (btn_manual, "clicked", G_CALLBACK(on_btn_manual_clicked), NULL);
	g_signal_connect (btn_predet, "clicked", G_CALLBACK(on_btn_predet_clicked), NULL);
	g_signal_connect (btn_monitoreo, "clicked", G_CALLBACK(on_btn_monitoreo_clicked), NULL);
	//--------------------------
	inicializar_opciones();
	inicializar_tablero();
	inicializar_masinfo();
	inicializar_contador();
	inicializar_aiuda();
	//----------------------
	gtk_widget_show_all(win_masinfo);
    gtk_main ();
    //---------------------------
    return 1;
}
