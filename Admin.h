/**
*     @file Admin.h
*
*     @brief Contiene las ventanas y vinculos con el programa principal para
             administradores. Se puede: visualizar usuarios,modificar y registrar
						 usuarios,histrial de búsquedas de los usuarios, buscar por nombre/tipo
						 o por criterio, solicitar material a almacén, y desplegar información
						 de queries determinados.
*
*     @author Juan Castillo Carrillo, Ana Regina Morfin Marquez, y David Emmanuel Perez Avila
*     @date 03/12/2020
*/

#ifndef Admin_h
#define Admin_h
#include "Param.h"
#include "validar.h"

/*
*     Esta funcion sirve para solicitar material al almacén, se debe de ingresar
*			el materialid(material) y la cantidad a solicitar. La función prestamo_admin
*			se conecta con validar.h para realizar la solicitud.
*/
void admin_pedir_material (GtkWidget *p,gpointer data)
{
	nodo *lista =(nodo *)data;
	GtkWidget *window, *label, *box, *box2, *boton;
	GdkColor color;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),320,200);
	gtk_container_border_width(GTK_CONTAINER(window),20);
	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

	box = gtk_vbox_new(TRUE,0);
	box2= gtk_hbox_new(TRUE,0);

	label = gtk_label_new("MATERIAL ID :");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	label = gtk_label_new("CANTIDAD :");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

	box2= gtk_hbox_new(TRUE,0);

	lista->entrylog[0] =  gtk_combo_box_text_new();
	combo_llenar_lista(lista);
	gtk_box_pack_start(GTK_BOX(box2),lista->entrylog[0],FALSE,FALSE,0);

	lista->entrylog[1] = gtk_entry_new();
 	gtk_entry_set_alignment(GTK_ENTRY(lista->entrylog[1]),0);
  gtk_entry_set_max_length(GTK_ENTRY(lista->entrylog[1]),5);
	gtk_box_pack_start(GTK_BOX(box2),lista->entrylog[1],FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,0);

	boton = gtk_button_new_with_label("SOLICITAR");
	gdk_color_parse("#f98305", &color);
	gtk_widget_modify_bg(GTK_WIDGET(boton),GTK_STATE_NORMAL, &color);
	gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(prestamo_admin), lista);
	gtk_box_pack_start(GTK_BOX(box),boton,FALSE,FALSE,0);

	gdk_color_parse("#2a9ebc", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_container_add(GTK_CONTAINER(window),box);
	gtk_widget_show_all(window);
}

/*
*     Esta funcion sirve para visualizar a todos los usuarios de la base de datos.
*			Despliega los datos de los campos siguientes: NoCuenta,AP,AM,Nombre,Carrera,
*			Semestre, FechaNac, Correo,Adeudo y Tipo.
*/
void visualizar_usuarios (GtkWidget *p,gpointer data)
{
	nodo *lista=(nodo *)data;
	GtkWidget *window, *label, *box2;
	GtkWidget *columna[10];
	GdkColor color;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"LISTA DE USUARIOS");
  gtk_container_border_width(GTK_CONTAINER(window),10);
	box2 = gtk_hbox_new(FALSE,0);
	int i;

	for(i=0; i<10; i++)
	columna[i] = gtk_vbox_new(FALSE,0);

	label = gtk_label_new("NO_CUENTA");
	gtk_box_pack_start(GTK_BOX(columna[0]),label,FALSE,FALSE,10);
	label = gtk_label_new("AP_PATERNO");
	gtk_box_pack_start(GTK_BOX(columna[1]),label,FALSE,FALSE,10);
	label = gtk_label_new("AP_MATERNO");
	gtk_box_pack_start(GTK_BOX(columna[2]),label,FALSE,FALSE,10);
	label = gtk_label_new("NOMBRE");
	gtk_box_pack_start(GTK_BOX(columna[3]),label,FALSE,FALSE,10);
	label = gtk_label_new("CARRERA");
	gtk_box_pack_start(GTK_BOX(columna[4]),label,FALSE,FALSE,10);
	label = gtk_label_new("SEMESTRE");
	gtk_box_pack_start(GTK_BOX(columna[5]),label,FALSE,FALSE,10);
	label = gtk_label_new("FECHA NACIMIENTO");
	gtk_box_pack_start(GTK_BOX(columna[6]),label,FALSE,FALSE,10);
	label = gtk_label_new("CORREO");
	gtk_box_pack_start(GTK_BOX(columna[7]),label,FALSE,FALSE,10);
	label = gtk_label_new("ADEUDO");
	gtk_box_pack_start(GTK_BOX(columna[8]),label,FALSE,FALSE,10);
	label = gtk_label_new("TIPO DE CUENTA");
	gtk_box_pack_start(GTK_BOX(columna[9]),label,FALSE,FALSE,10);
	// Ejecuta el query
	if( mysql_query(&lista->mysql,"SELECT * FROM PF_usuarios") ){
		//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
		//exit(1);
	}

	// Obtiene el query
	if( !(lista->res = mysql_store_result(&lista->mysql)) ){
		//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
		//exit(1);
	}

	// Despliega el resultado del query
	while( (lista->row = mysql_fetch_row(lista->res)) )
	{
		i = 0;
		for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
			if(lista->row[i] != NULL){
				if(i!=10)
				{
					label = gtk_label_new(lista->row[i]);
					gtk_box_pack_start(GTK_BOX(columna[i]),label,FALSE,FALSE,10);
				}
			}
		}
	}
	for(i=0;i<10;i++)
	gtk_box_pack_start(GTK_BOX(box2),columna[i],FALSE,FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),box2);
	mysql_free_result(lista->res);

	gdk_color_parse("#2a9ebc", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_widget_show_all(window);
}

/*
*     Esta funcion sirve para visualizar el perfil de un usuario y modificar
* 		cualquiera de los campos con excepción del NoCuenta. El administrador
*			puede cambiar también si hay Adeudos.
*/
void admin_modificar (GtkWidget *d, gpointer gp)
{
 nodo *lista=(nodo *)gp;
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *entrybox;
  GtkWidget *vbox, *hbox, *box, *boxG;
  GtkWidget *button;
  GtkWidget *abajobox;
  GdkColor color;

  lista->ban=1;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"MODIFICAR USUARIOS");
	gtk_container_border_width(GTK_CONTAINER(window),20);
	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

  box=gtk_vbox_new(FALSE,5);
	boxG=gtk_hbox_new(FALSE,5);

	lista->entrylog[0] =  gtk_combo_box_text_new();
	combo_llenar_lista_U(lista);
	gtk_box_pack_start(GTK_BOX(box),lista->entrylog[0],FALSE,FALSE,0);
	button= gtk_button_new_with_label("Ver");
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Llenar_modificar),lista);

	gtk_box_pack_start(GTK_BOX(boxG),box,FALSE,FALSE,0);
	box=gtk_vbox_new(FALSE,5);

	//Inicio No.cuenta
	hbox=gtk_hbox_new(FALSE,5);
	label=gtk_label_new("No.Cuenta: ");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
	label=gtk_label_new(lista->no_cuenta);
	lista->label_cuenta=label;
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),hbox,FALSE,FALSE,0);

	hbox=gtk_hbox_new(FALSE,5);
	//Tabla izquierda
	vbox=gtk_vbox_new(FALSE, 5);

	label=gtk_label_new("Nombre: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[0]=entrybox;
	sacar_dato("Nombre", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label=gtk_label_new("Apellido Paterno:");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[1]=entrybox;
	sacar_dato("AP", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label=gtk_label_new("Apellido Materno:");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[2]=entrybox;
	sacar_dato("AM", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label=gtk_label_new("Carrera: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[3]=entrybox;
	sacar_dato("Carrera", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label=gtk_label_new("Semestre: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[4]=entrybox;
	sacar_dato("Semestre", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,0);
	//Tabla derecha
	vbox=gtk_vbox_new(FALSE, 5);

	label=gtk_label_new("Fecha Nacimiento: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[5]=entrybox;
	sacar_dato("FechaNac", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label=gtk_label_new("Correo: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[6]=entrybox;
	sacar_dato("Correo", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label=gtk_label_new("Contrasena: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	entrybox = gtk_entry_new();
	lista->entryper[7]=entrybox;
	sacar_dato("Passw", "PF_usuarios", lista);
	gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
	gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

	label= gtk_label_new("Adeudo:");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);


	label= gtk_check_button_new_with_label("Adeudo");
	//gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);

	sacar_dato("Adeudo", "PF_usuarios", lista);
	if(strcmp(lista->row[0], "0")==0)
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(label), FALSE);
	else
	  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(label), TRUE);
	lista->entryper[8]=label;
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);

	label=gtk_label_new("Tipo: ");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);

	label = gtk_label_new("Administrador");
	lista->entryper[9]=label;
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);

	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,0);

  //botones
  abajobox = gtk_hbox_new(FALSE,5);

  button= gtk_button_new_with_label("Guardar");
  gtk_box_pack_start(GTK_BOX(abajobox),button,FALSE,TRUE,0);
  gdk_color_parse("#fdb70d", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(guardar_datos),lista);
  gtk_widget_show(button);

  button= gtk_button_new_with_label("Cancelar");
  gtk_box_pack_start(GTK_BOX(abajobox),button,FALSE,TRUE,0);
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
	g_signal_connect_swapped(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy), window);
  gtk_widget_show(button);

	gtk_box_pack_start(GTK_BOX(box),hbox,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(box),abajobox,FALSE,FALSE,0); //new

	gtk_box_pack_start(GTK_BOX(boxG),box,FALSE,FALSE,0);

	gdk_color_parse("#90cae6", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_container_add(GTK_CONTAINER(window),boxG);
	gtk_widget_show_all(window);

}

/*
*     Esta funcion sirve para visualizar el perfil de un usuario y modificar
* 		cualquiera de los campos con excepción del NoCuenta. El administrador
*			puede cambiar también si hay Adeudos.
*/
void registro_usuario (GtkWidget *p, gpointer data)
{
	nodo *lista =(nodo *)data;
	GtkWidget *window, *label, *boxmain, *box, *box2, *auxbox, *boton;
	GdkColor  color;
	int i;
	char linea[16];

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_border_width(GTK_CONTAINER(window),10);
  gtk_window_set_title(GTK_WINDOW(window),"REGISTRO DE NUEVO USUARIO");
	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

	boxmain = gtk_vbox_new(FALSE,0);
	box = gtk_hbox_new(TRUE,0);
	box2 = gtk_vbox_new(TRUE,0);
	auxbox = gtk_hbox_new(TRUE,0);

	label = gtk_label_new("REGISTRO");
	gtk_box_pack_start(GTK_BOX(boxmain),label,FALSE,FALSE,5);

	label = gtk_label_new("NOMBRE");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[0] = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[0]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[0],FALSE,FALSE,0);
	label = gtk_label_new("AP_PATERNO");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[1] = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[1]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[1],FALSE,FALSE,0);
	label = gtk_label_new("AP_MATERNO");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[2] = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[2]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[2],FALSE,FALSE,0);
	label = gtk_label_new("CARRERA");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[3] = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[3]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[3],FALSE,FALSE,0);
	label = gtk_label_new("SEMESTRE");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[4] = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[4]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[4],FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);

	box2 = gtk_vbox_new(TRUE,0);

	label = gtk_label_new("FECHA DE NACIMIENTO");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);

	lista->altausu[5] = gtk_combo_box_text_new();
	for(i=2002; i>1950; i--)
	{
		sprintf(linea,"%d",i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->altausu[5]), linea);
	}
	gtk_box_pack_start(GTK_BOX(auxbox),lista->altausu[5],FALSE,FALSE,0);

	lista->altausu[6] = gtk_combo_box_text_new();
	for(i=1; i<13; i++)
	{
		sprintf(linea,"%d",i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->altausu[6]), linea);
	}
	gtk_box_pack_start(GTK_BOX(auxbox),lista->altausu[6],FALSE,FALSE,0);

	lista->altausu[7] = gtk_combo_box_text_new();
	for(i=1; i<32; i++)
	{
		sprintf(linea,"%d",i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->altausu[7]), linea);
	}
	gtk_box_pack_start(GTK_BOX(auxbox),lista->altausu[7],FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box2),auxbox,FALSE,FALSE,0);


	label = gtk_label_new("CORREO");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[8] = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[8]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[8],FALSE,FALSE,0);
	label = gtk_label_new("CONTRASENA");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[9] = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(lista->altausu[9]),20);
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[9],FALSE,FALSE,0);
	label = gtk_label_new("TIPO DE CUENTA");
	gtk_box_pack_start(GTK_BOX(box2),label,FALSE,FALSE,0);
	lista->altausu[10] = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->altausu[10]), "USUARIO");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->altausu[10]), "ADMINISTRADOR");
	gtk_box_pack_start(GTK_BOX(box2),lista->altausu[10],FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),box2,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(boxmain),box,FALSE,FALSE,5);

	auxbox = gtk_hbox_new(TRUE,0);
	label = gtk_label_new(" ");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,5);
	boton = gtk_button_new_with_label("GUARDAR");
	gdk_color_parse("#fdb70d", &color);
	gtk_widget_modify_bg(GTK_WIDGET(boton),GTK_STATE_NORMAL, &color);
	gtk_signal_connect(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(admin_alta_usuario), lista);
	gtk_box_pack_start(GTK_BOX(auxbox),boton,FALSE,FALSE,5);
	boton = gtk_button_new_with_label("CANCELAR");
	gdk_color_parse("#f98305", &color);
	gtk_widget_modify_bg(GTK_WIDGET(boton),GTK_STATE_NORMAL, &color);
	g_signal_connect_swapped(GTK_OBJECT(boton),"clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy), window);
	gtk_box_pack_start(GTK_BOX(auxbox),boton,FALSE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(boxmain),auxbox,FALSE,FALSE,0);

	gtk_container_add(GTK_CONTAINER(window),boxmain);

	gdk_color_parse("#90cae6", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_widget_show_all(window);

}

/*
*     Esta funcion sirve para visualizar todas las búsquedas realizadas por todos
* 		los usuarios con el fin de conocer que materiales son los más buscados.
*/
void historial_de_busqueda (GtkWidget *p, gpointer data)
{
	nodo *lista=(nodo *)data;
	GtkWidget *window, *label, *box2;
	GtkWidget *columna[6];
	GdkColor color;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"LISTA DE USUARIOS");
  gtk_container_border_width(GTK_CONTAINER(window),10);
	box2 = gtk_hbox_new(FALSE,0);
	int i;

	for(i=0; i<7; i++)
	columna[i] = gtk_vbox_new(FALSE,0);

	label = gtk_label_new("ID_BUSQUEDA");
	gtk_box_pack_start(GTK_BOX(columna[0]),label,FALSE,FALSE,10);
	label = gtk_label_new("FECHA_BUSQUEDA");
	gtk_box_pack_start(GTK_BOX(columna[1]),label,FALSE,FALSE,10);
	label = gtk_label_new("NO_CUENTA");
	gtk_box_pack_start(GTK_BOX(columna[2]),label,FALSE,FALSE,10);
	label = gtk_label_new("USUARIO");
	gtk_box_pack_start(GTK_BOX(columna[3]),label,FALSE,FALSE,10);
	label = gtk_label_new("MATERIALID");
	gtk_box_pack_start(GTK_BOX(columna[4]),label,FALSE,FALSE,10);
	label = gtk_label_new("MATERIAL");
	gtk_box_pack_start(GTK_BOX(columna[5]),label,FALSE,FALSE,10);
	// Ejecuta el query
	if( mysql_query(&lista->mysql,"SELECT Busquedaid, FHBusqueda, NoCuenta, CONCAT(u.Nombre,' ',AP,' ',AM)AS Usuario, Materialid, m.Nombre AS Material FROM PF_busquedas LEFT JOIN PF_usuarios u USING (NoCuenta) LEFT JOIN PF_inventario m USING(Materialid)") ){
		//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
		//exit(1);
	}
	// Obtiene el query
	if( !(lista->res = mysql_store_result(&lista->mysql)) ){
		//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
		//exit(1);
	}

	// Despliega el resultado del query
	while( (lista->row = mysql_fetch_row(lista->res)) )
	{
		i = 0;
		for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
			if(lista->row[i] != NULL){
					label = gtk_label_new(lista->row[i]);
					gtk_box_pack_start(GTK_BOX(columna[i]),label,FALSE,FALSE,10);
			}
		}
	}
	for(i=0;i<7;i++)
	gtk_box_pack_start(GTK_BOX(box2),columna[i],FALSE,FALSE,10);
	gtk_container_add(GTK_CONTAINER(window),box2);
	mysql_free_result(lista->res);
	gtk_widget_show_all(window);

	gdk_color_parse("#90cae6", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);
}

/*
*     Esta funcion despliega los queries siguientes:  Préstamos activos y
*			que material, materiales que más tardan en regresar, material más
* 		solicitado, préstamos vencidos, usuarios que deban material.
*/
void mas_informacion (GtkWidget *p, gpointer data)
{
	nodo *lista = (nodo *)data;
	GtkWidget *window, *boxmain, *boxh, *boxv, *label, *auxbox;
	GdkColor color;
	int i, j;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window),320,200);
	gtk_container_border_width(GTK_CONTAINER(window),10);
	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

	boxmain = gtk_vbox_new(FALSE,5);
	boxh = gtk_hbox_new(FALSE,5);
	boxv = gtk_vbox_new(TRUE,5);
	auxbox = gtk_hbox_new(TRUE,0);

	label = gtk_label_new("PRESTAMOS ACTIVOS\nY MATERIAL");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(boxh),label,FALSE,FALSE,0);

	label = gtk_label_new("PRESTAMO_ID");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("LIMITE");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("NO_CUENTA");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("USUARIO");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("MATERIAL_ID");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("NOMBRE");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv),auxbox,FALSE,FALSE,0);
	auxbox = gtk_hbox_new(TRUE,0);

	// Ejecuta el query
	if( mysql_query(&lista->mysql,"SELECT Prestamoid, Limite, NoCuenta,CONCAT(u.Nombre,' ', AP,' ',AM)AS Usuario, Materialid,m.Nombre FROM PF_prestamos LEFT JOIN PF_prestamos_inventario using(Prestamoid) LEFT JOIN PF_inventario m USING(Materialid)LEFT JOIN PF_usuarios u USING(NoCuenta) WHERE Fin IS NULL") ){
		//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
		//exit(1);
	}

	// Obtiene el query
	if( !(lista->res = mysql_store_result(&lista->mysql)) ){
		//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
		//exit(1);
	}

	// Despliega el resultado del query
	while( (lista->row = mysql_fetch_row(lista->res)) )
	{
		i = 0;
		j = 0;
		for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
			if(lista->row[i] != NULL){
					label = gtk_label_new(lista->row[i]);
					gdk_color_parse("#043047", &color);
					gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
					gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
					if(j==5)
					{
						gtk_box_pack_start(GTK_BOX(boxv),auxbox,FALSE,FALSE,0);
						auxbox = gtk_hbox_new(TRUE,0);
						j=0;
					}
					j++;
			}
		}
	}
	mysql_free_result(lista->res);
	gtk_box_pack_start(GTK_BOX(boxh),boxv,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxmain),boxh,FALSE,FALSE,0);

	boxh = gtk_hbox_new(FALSE,5);
	auxbox = gtk_hbox_new(TRUE,0);
	label = gtk_label_new("MATERIAL QUE\nQUE MAS TARDAN\nEN REGRESAR");
	gdk_color_parse("#2a9ebc", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(boxh),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);

	// Ejecuta el query
	if( mysql_query(&lista->mysql,"SELECT Nombre FROM PF_prestamos LEFT JOIN PF_prestamos_inventario USING(Prestamoid) LEFT JOIN PF_inventario USING(Materialid) WHERE (DATEDIFF(Fin,Inicio))=(SELECT DATEDIFF(Fin, Inicio)AS Dias FROM PF_prestamos LEFT JOIN PF_prestamos_inventario USING(Prestamoid) LEFT JOIN PF_inventario USING(Materialid)ORDER BY Dias DESC LIMIT 1)") ){
		//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
		//exit(1);
	}

	// Obtiene el query
	if( !(lista->res = mysql_store_result(&lista->mysql)) ){
		//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
		//exit(1);
	}

	// Despliega el resultado del query
	while( (lista->row = mysql_fetch_row(lista->res)) )
	{
		i = 0;
		for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
			if(lista->row[i] != NULL){
					label = gtk_label_new(lista->row[i]);
					gdk_color_parse("#2a9ebc", &color);
					gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
					gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
			}
		}
	}
	mysql_free_result(lista->res);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxh),auxbox,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxmain),boxh,FALSE,FALSE,0);


	boxh = gtk_hbox_new(FALSE,5);
	auxbox = gtk_hbox_new(TRUE,0);
	label = gtk_label_new("MATERIAL MAS \nSOLICITADO");
	gdk_color_parse("#f98305", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(boxh),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);

	// Ejecuta el query
	if( mysql_query(&lista->mysql,"SELECT Nombre FROM PF_inventario LEFT JOIN PF_prestamos_inventario USING(Materialid)GROUP BY Materialid HAVING COUNT(Materialid)= (SELECT COUNT(Materialid) FROM PF_prestamos_inventario GROUP BY Materialid ORDER BY COUNT(Materialid) DESC LIMIT 1)") ){
		//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
		//exit(1);
	}

	// Obtiene el query
	if( !(lista->res = mysql_store_result(&lista->mysql)) ){
		//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
		//exit(1);
	}

	// Despliega el resultado del query
	while( (lista->row = mysql_fetch_row(lista->res)) )
	{
		i = 0;
		for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
			if(lista->row[i] != NULL){
					label = gtk_label_new(lista->row[i]);
					gdk_color_parse("#f98305", &color);
					gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
					gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
			}
		}
	}
	mysql_free_result(lista->res);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxh),auxbox,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxmain),boxh,FALSE,FALSE,0);

	boxh = gtk_hbox_new(FALSE,5);
	boxv = gtk_vbox_new(TRUE,5);
	auxbox = gtk_hbox_new(TRUE,0);

	label = gtk_label_new("PRESTAMOS VENCIDOS\nY MATERIAL");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(boxh),label,FALSE,FALSE,0);

	label = gtk_label_new("PRESTAMO_ID");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("LIMITE");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("NO_CUENTA");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("USUARIO");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("MATERIAL_ID");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	label = gtk_label_new("NOMBRE");
	gdk_color_parse("#043047", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
	gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxv),auxbox,FALSE,FALSE,0);
	auxbox = gtk_hbox_new(TRUE,0);

	// Ejecuta el query
	if( mysql_query(&lista->mysql,"SELECT Prestamoid, Limite, NoCuenta,CONCAT(u.Nombre,' ', AP,' ',AM)AS Usuario, Materialid,m.Nombre FROM PF_prestamos LEFT JOIN PF_prestamos_inventario using(Prestamoid) LEFT JOIN PF_inventario m USING(Materialid)LEFT JOIN PF_usuarios u USING(NoCuenta) WHERE (Fin IS NULL) AND (NOW()>=Limite)") ){
		//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
		//exit(1);
	}

	// Obtiene el query
	if( !(lista->res = mysql_store_result(&lista->mysql)) ){
		//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
		//exit(1);
	}

	// Despliega el resultado del query
	while( (lista->row = mysql_fetch_row(lista->res)) )
	{
		i = 0;
		j = 0;
		for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
			if(lista->row[i] != NULL){
					label = gtk_label_new(lista->row[i]);
					gdk_color_parse("#043047", &color);
					gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
					gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
					if(j==5)
					{
						gtk_box_pack_start(GTK_BOX(boxv),auxbox,FALSE,FALSE,0);
						auxbox = gtk_hbox_new(TRUE,0);
						j=0;
					}
					j++;
			}
		}
	}
	mysql_free_result(lista->res);
	gtk_box_pack_start(GTK_BOX(boxh),boxv,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(boxmain),boxh,FALSE,FALSE,0);

		boxh = gtk_hbox_new(FALSE,5);
		boxv = gtk_vbox_new(TRUE,5);
		auxbox = gtk_hbox_new(TRUE,0);

		label = gtk_label_new("USUARIOS QUE DEBEN\nMATERIAL");
		gdk_color_parse("#2a9ebc", &color);
		gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
		gtk_box_pack_start(GTK_BOX(boxh),label,FALSE,FALSE,0);

		label = gtk_label_new("NOMBRE");
		gdk_color_parse("#2a9ebc", &color);
		gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
		gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
		label = gtk_label_new("AP_PATERNO");
		gdk_color_parse("#2a9ebc", &color);
		gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
		gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
		label = gtk_label_new("AP_MATERNO");
		gdk_color_parse("#2a9ebc", &color);
		gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
		gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
		gtk_box_pack_start(GTK_BOX(boxv),auxbox,FALSE,FALSE,0);
		auxbox = gtk_hbox_new(TRUE,0);

		// Ejecuta el query
		if( mysql_query(&lista->mysql,"SELECT u.Nombre, AP AS APATERNO, AM AS APEMATERNO FROM PF_prestamos LEFT JOIN PF_prestamos_inventario using(Prestamoid) LEFT JOIN PF_inventario USING(Materialid)LEFT JOIN PF_usuarios u USING(NoCuenta) WHERE (Fin IS NULL)GROUP BY NoCuenta") ){
			//fprintf(stderr,"Error processing query \"%s\" Error: %s\n",buffer,mysql_error(&mysql));
			//exit(1);
		}

		// Obtiene el query
		if( !(lista->res = mysql_store_result(&lista->mysql)) ){
			//	fprintf(stderr,"Error storing results Error: %s\n",mysql_error(&data->mysql));
			//exit(1);
		}

		// Despliega el resultado del query
		while( (lista->row = mysql_fetch_row(lista->res)) )
		{
			i = 0;
			j = 0;
			for( i=0 ; i < mysql_num_fields(lista->res); i++ ){
				if(lista->row[i] != NULL){
						label = gtk_label_new(lista->row[i]);
						gdk_color_parse("#2a9ebc", &color);
						gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
						gtk_box_pack_start(GTK_BOX(auxbox),label,FALSE,FALSE,0);
						if(j==2)
						{
							gtk_box_pack_start(GTK_BOX(boxv),auxbox,FALSE,FALSE,0);
							auxbox = gtk_hbox_new(TRUE,0);
							j=0;
						}
						j++;
				}
			}
		}
		mysql_free_result(lista->res);
		gtk_box_pack_start(GTK_BOX(boxh),boxv,FALSE,FALSE,0);
		gtk_box_pack_start(GTK_BOX(boxmain),boxh,FALSE,FALSE,0);

	gdk_color_parse("#c1e4f5", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_container_add(GTK_CONTAINER(window),boxmain);
	gtk_widget_show_all(window);
}

/*
*     Esta función permite buscar usuarios por nombre o por tipo. Si hay un
*			nombre escrito, hace caso al nombre. Para buscar por tipo, se debe de
* 		vaciar el campo de nombre. Despliega todos los datos, menos la clave.
*/
void buscar_nombre (GtkWidget *p, gpointer data)
{
	nodo *lista = (nodo *)data;

	GtkWidget *window, *label, *box, *vbox1, *vbox2, *entrybox, *boxmain, *button;
	GdkColor color;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"BUSCAR POR NOMBRE/TIPO");
  gtk_container_border_width(GTK_CONTAINER(window),10);

	boxmain = gtk_vbox_new(FALSE,0);
	box = gtk_hbox_new(FALSE,0);
	vbox1 = gtk_vbox_new(FALSE,0);
	vbox2 = gtk_vbox_new(FALSE,0);

	label = gtk_label_new("NOMBRE: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,10);
	label = gtk_label_new("TIPO: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,10);

	entrybox = gtk_entry_new();
	gtk_box_pack_start(GTK_BOX(vbox2),entrybox,FALSE,FALSE,10);
	lista->entrylog[0] = entrybox;
	entrybox = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrybox), "");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrybox), "USUARIO");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(entrybox), "ADMINISTRADOR");
	gtk_box_pack_start(GTK_BOX(vbox2),entrybox,FALSE,FALSE,10);
	lista->entrylog[1] =entrybox;

	gtk_box_pack_start(GTK_BOX(box),vbox1,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(box),vbox2,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(boxmain),box,FALSE,FALSE,10);

	button= gtk_button_new_with_label("BUSCAR");
  gtk_box_pack_start(GTK_BOX(boxmain),button,FALSE,TRUE,0);
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(admin_buscar_tipo),lista);
  gtk_widget_show(button);

	label = gtk_label_new("MOSTRAR INFO: ");
	gtk_box_pack_start(GTK_BOX(boxmain),label,FALSE,FALSE,10);

	gdk_color_parse("#90cae6", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_container_add(GTK_CONTAINER(window),boxmain);
	gtk_widget_show_all(window);
}

/*
*     Esta función permite buscar usuarios por nombre o por tipo. Si hay un
*			nombre escrito, hace caso al nombre. Para buscar por tipo, se debe de
* 		vaciar el campo de nombre.
*/
void buscar_criterio (GtkWidget *p, gpointer data)
{
	nodo *lista = (nodo *)data;
	GtkWidget *window, *label, *box, *vbox1, *vbox2, *boxmain, *button, *auxbox;
	GdkColor color;
	int i;
	char linea[32];
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"BUSCAR POR CRITERIO");
  gtk_container_border_width(GTK_CONTAINER(window),10);

	boxmain = gtk_vbox_new(FALSE,0);
	box = gtk_hbox_new(FALSE,0);
	vbox1 = gtk_vbox_new(TRUE,0);
	vbox2 = gtk_vbox_new(FALSE,0);
	auxbox = gtk_hbox_new(FALSE,0);

	label = gtk_label_new("AP_PATERNO: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,5);
	label = gtk_label_new("NO_CUENTA: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,5);
	label = gtk_label_new("CARRERA: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,5);
	label = gtk_label_new("SEMESTRE: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,5);
	label = gtk_label_new("FECHA DE\nNACIMIENTO: ");
	gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,5);

	for(i=0; i<4; i++)
	{
		lista->busmix[i] = gtk_entry_new();
		gtk_box_pack_start(GTK_BOX(vbox2),lista->busmix[i],FALSE,FALSE,10);
	}

	lista->busmix[4] = gtk_combo_box_text_new();
	for(i=2002; i>1950; i--)
	{
		sprintf(linea,"%d",i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->busmix[4]), linea);
	}
	gtk_box_pack_start(GTK_BOX(auxbox),lista->busmix[4],FALSE,FALSE,0);

	lista->busmix[5] = gtk_combo_box_text_new();
	for(i=1; i<13; i++)
	{
		sprintf(linea,"%d",i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->busmix[5]), linea);
	}
	gtk_box_pack_start(GTK_BOX(auxbox),lista->busmix[5],FALSE,FALSE,0);

	lista->busmix[6] = gtk_combo_box_text_new();
	for(i=1; i<32; i++)
	{
		sprintf(linea,"%d",i);
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(lista->busmix[6]), linea);
	}
	gtk_box_pack_start(GTK_BOX(auxbox),lista->busmix[6],FALSE,FALSE,0);

	gtk_box_pack_start(GTK_BOX(vbox2),auxbox,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(box),vbox1,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(box),vbox2,FALSE,FALSE,10);
	gtk_box_pack_start(GTK_BOX(boxmain),box,FALSE,FALSE,10);

	button= gtk_button_new_with_label("BUSCAR");
  gtk_box_pack_start(GTK_BOX(boxmain),button,FALSE,TRUE,0);
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(busqueda_crit),lista);
  gtk_widget_show(button);

	label = gtk_label_new("MOSTRAR INFO: ");
	gtk_box_pack_start(GTK_BOX(boxmain),label,FALSE,FALSE,10);

	gdk_color_parse("#90cae6", &color);
	gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

	gtk_container_add(GTK_CONTAINER(window),boxmain);
	gtk_widget_show_all(window);
}
#endif
