/**
*     @file Laboratorio.c
*
*     @brief En este programa se encuentra la ventana principal
*			donde se inicia sesion.
*
*     @author Juan Castillo Carrillo, Ana Regina Morfin Marquez, y David Emmanuel Perez Avila
*     @date 03/12/2020
*/
#include"validar.h"
#include"Param.h"
#include"Login.h"
//----------------------------------------------------------------
//Main
void login (GtkButton *p,gpointer data);

/*
*     Esta funcion es mandada llamar cuando se cierra la
*			ventana principal y se debe liberar toda la memoria.
*
*/
void cerrar (GtkWidget *d,gpointer data)
{
	nodo *lista=(nodo *)data;
	mysql_close(&lista->mysql);
	gtk_main_quit();
}
//----------------------------------------------------------------
/*
*     Esta es la funcion principal donde se inicializa la primer
*     ventana y se le da la opcion al usuario de iniciar sesion
*			como usuario o como administrador
*
*/
gint main(gint argc, gchar *argv[])
{
	GtkWidget *window;
	GtkWidget *boton;
	GtkWidget *box1, *box2, *auxbox;
	GtkWidget *label;
	GtkWidget *entrybox;
	GdkColor color;

	nodo lista;

	gtk_init(&argc, &argv);

	iniciar_mysql(&lista);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),320,200);
	gtk_container_border_width(GTK_CONTAINER(window),20);

	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(cerrar),&lista);

	box1 = gtk_vbox_new(TRUE,5);
	box2= gtk_vbox_new(TRUE,5);
	auxbox = gtk_hbox_new(TRUE,5);

	label = gtk_label_new("NO. CUENTA :");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);

	entrybox = gtk_entry_new();
  gtk_entry_set_alignment(GTK_ENTRY(entrybox),0);
  gtk_entry_set_max_length(GTK_ENTRY(entrybox),20);
	lista.entrylog[2] = entrybox;
	gtk_box_pack_start(GTK_BOX(box2),auxbox,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box2),entrybox,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);

	box2= gtk_vbox_new(TRUE,5);
	auxbox = gtk_hbox_new(TRUE,5);

	label = gtk_label_new("PASSWORD :");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);

	entrybox = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entrybox),FALSE);
 	gtk_entry_set_alignment(GTK_ENTRY(entrybox),0);
  gtk_entry_set_max_length(GTK_ENTRY(entrybox),20);
	lista.entrylog[3] = entrybox;
	gtk_box_pack_start(GTK_BOX(box2),auxbox,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box2),entrybox,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(box1),box2,FALSE,FALSE,0);

	auxbox = gtk_hbox_new(TRUE,5);

	label = gtk_label_new("Tipo :");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);

	entrybox = gtk_combo_box_text_new();
	lista.combolog = entrybox;
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrybox), "Administrador");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrybox), "Usuario");
	//gtk_combo_box_set_active(GTK_COMBO_BOX(entrybox),-1);
	gtk_box_pack_start(GTK_BOX(auxbox),entrybox,FALSE,FALSE,5);

	boton = gtk_button_new_with_label("INICIAR SESION");
	gdk_color_parse("#2a9ebc", &color);
	gtk_widget_modify_bg(GTK_WIDGET(boton),GTK_STATE_NORMAL, &color);
	gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(login), &lista);
	gtk_box_pack_start(GTK_BOX(auxbox),boton,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box1),auxbox,FALSE,FALSE,0);

	gtk_container_add(GTK_CONTAINER(window),box1);

	gdk_color_parse("#90cae6", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

/*
*     Esta funcion recibe como parametros las dos entrys del Inicio
*			y valida si el numeor de cuenta y la contraseña son correctos
*
*/
void login (GtkButton *p, gpointer data)
{
	nodo *lista = (nodo *)data;
	const char *text1, *text2, *text3;
	char text[3][32];

	text1 = gtk_entry_get_text(GTK_ENTRY(lista->entrylog[2]));
	text2 = gtk_entry_get_text(GTK_ENTRY(lista->entrylog[3]));
	text3 = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(lista->combolog));

	strcpy(text[0], text1);
	strcpy(text[1], text2);
	if(text3==NULL)
	  strcpy(text[2],"U");
	else
	  strcpy(text[2], text3);
	if(validar_cuenta_pass(text[0],text[1],text[2],lista)==-1)
	{
		strcpy(lista->error,"EL USUARIO Y/O \nCONTRASENA SON INCORRECTOS");
		error_emergente(lista);
	}
	else
	{
		strcpy(lista->no_cuenta, text[0]);
		strcpy(lista->no_temp, text[0]);
		if(strcmp(text3,"Administrador")==0)
		login_admin(lista);
		if(strcmp(text3,"Usuario")==0)
		login_usuario(lista);
	}
}
