/**
*     @file Usuario.h
*
*     @brief Contiene las ventanas y vinculos con el programa principal para
             usuarios. Se puede: solicitar material, regresar material, realizar
             búsquedas y ver su propio perfil, así como realizar modificaciones.
*
*     @author Juan Castillo Carrillo, Ana Regina Morfin Marquez, y David Emmanuel Perez Avila
*     @date 03/12/2020
*/

//Incluir librerías
#ifndef usuario_h
#define usuario_h
#include "Param.h"
#include "validar.h"

/*
*     Esta funcion sirve para cargar el perfil del usuario de la base de SQL
*     y mostrarlo de forma gráfica al usuario. Se pueden observar los datos,
*     así como realizar modificaciones.
*/
void usuario_perfil(GtkWidget *d, gpointer gp)
{
  //Declaraciones
  nodo *lista=(nodo *)gp;
  lista->ban=0;

  //Widgets a utilizar
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *entrybox;
  GtkWidget *vbox, *hbox, *box;
  GtkWidget *button;
  GtkWidget *abajobox;
  GdkColor color;

  //Creación de la ventana
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),20);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

  box=gtk_vbox_new(FALSE,5);

  //Inicio No.cuenta
  hbox=gtk_hbox_new(FALSE,5);
  label=gtk_label_new("No.Cuenta: ");
  gdk_color_parse("#f98305", &color); //Se asigna el color a utilizar a "color"
  gtk_widget_modify_bg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color); //Se incluye el color
  gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0); //Se empaqueta el label en la caja
  label=gtk_label_new(lista->no_cuenta);
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
  gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box),hbox,FALSE,FALSE,0);

  hbox=gtk_hbox_new(FALSE,5);
  //Tabla izquierda
  vbox=gtk_vbox_new(FALSE, 5);

  //Despliega los campos de información del perfil de usuario
  label=gtk_label_new("Nombre: ");
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[0]=entrybox;
  sacar_dato("Nombre", "PF_usuarios", lista); //Esta función obtiene la información de la base de datos y la despliega en la ventana
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Apellido Paterno:");
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[1]=entrybox;
  sacar_dato("AP", "PF_usuarios", lista); //Obtiene el apellido paterno de la base de datos del usuario
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Apellido Materno:"); //Obtiene el apellido materno de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[2]=entrybox;
  sacar_dato("AM", "PF_usuarios", lista);
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Carrera: "); //Obtiene la carrera de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[3]=entrybox;
  sacar_dato("Carrera", "PF_usuarios", lista);
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Semestre: ");  //Obtiene el semestre de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[4]=entrybox;
  sacar_dato("Semestre", "PF_usuarios", lista);
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,0);
  //Tabla derecha
  vbox=gtk_vbox_new(FALSE, 5);

  label=gtk_label_new("Fecha Nacimiento: ");  //Obtiene la fecha de nacimiento de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[5]=entrybox;
  sacar_dato("FechaNac", "PF_usuarios", lista);
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Correo: ");  //Obtiene el correo de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[6]=entrybox;
  sacar_dato("Correo", "PF_usuarios", lista);
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Contrasena: ");  //Obtiene la contraseña de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_entry_new();
  lista->entryper[7]=entrybox;
  sacar_dato("Passw", "PF_usuarios", lista);
  gtk_entry_set_text(GTK_ENTRY(entrybox), lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Adeudo: ");    //Obtiene adeudo de la base de datos del usuario
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  sacar_dato("Adeudo", "PF_usuarios", lista);
  if(strcmp(lista->row[0], "0")==0)
    entrybox = gtk_label_new("Sin adeudo"); //Como adeudo es booleano, 0 es que no hay adeudo
  else
    entrybox = gtk_label_new("Con adeudo, vaya con el admin"); //Si tiene adeudo, solo el administrador lo puede modificar
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);

  label=gtk_label_new("Tipo: "); //Obtiene el Tipo de la base de datos. Puede ser Usuario o Administrador
  gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
  entrybox = gtk_label_new("Usuario");
  gtk_box_pack_start(GTK_BOX(vbox),entrybox,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,0);

  //botones
  abajobox = gtk_hbox_new(TRUE,5); //Caja que incluye botones de Guardar y Cancelar

  button= gtk_button_new_with_label("Guardar");
  gtk_box_pack_start(GTK_BOX(abajobox),button,FALSE,TRUE,0);
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(guardar_datos),lista); //Registra los datos en la base de datos
  gtk_widget_show(button);

  label = gtk_label_new(" "); //Para un espacio
  gtk_box_pack_start(GTK_BOX(abajobox),label,FALSE,TRUE,0);

  button= gtk_button_new_with_label("Cancelar");
  gtk_box_pack_start(GTK_BOX(abajobox),button,FALSE,TRUE,0);
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  g_signal_connect_swapped(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy), window); //Cierra la ventana y no se registran los cambios.
  gtk_widget_show(button);

  //Empaqueta las cajas de datos y botones
  gtk_box_pack_start(GTK_BOX(box),hbox,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box),abajobox,FALSE,FALSE,0);

  //Color de la ventana
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

  //Empaqueta caja en la ventana y la hace visible
  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_widget_show_all(window);

}

/*
*     Esta funcion sirve para que el usuario haga busquedas de materiales,
*     las búsquedas se registran en PF_busquedas en la base de datos. Al
*     hacer búsquedas, se muestra la disponibilidad del material consultado.
*     Se tiene que elegir un material a buscar de las opciones.
*/

void usuario_busqueda(GtkWidget *p, gpointer gp)
{
  //Declaraciones
  nodo *lista=(nodo *)gp;
  //Widgets a utilizar
  GtkWidget *window;
  GtkWidget *label;
  //GtkWidget *entrybox;
  GtkWidget *box;
  GtkWidget *button;
  //GtkWidget *abajobox;
  GdkColor color;

  //Se crea la ventana
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),20);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

  //Caja donde se muestran opciones de material y disponibilidad
  box=gtk_vbox_new(TRUE, 5);
  label=gtk_label_new("Seleccione Material");
  gdk_color_parse("#043047", &color);
  gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
  gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);

  //Se cargan los materiales a la combo box
  lista->entrylog[0] =  gtk_combo_box_text_new();
  combo_llenar_lista(lista); //Función que carga los materiales de la base de datos
  gtk_box_pack_start(GTK_BOX(box),lista->entrylog[0],FALSE,FALSE,0);

  //Botón para ejercer la búsqueda, es necesario activarlo.
  button=gtk_button_new_with_label("Ok");
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  //Cambiar el connect por la funcion que cargue
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(busqueda_material),lista); //Realiza la búsqueda

  //Disponibilidad
  label=gtk_label_new("Disponibilidad:");
  gdk_color_parse("#043047", &color);
  gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
  gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);

  //Label donde se muestra la cantidad disponible del material seleccionado
  label=gtk_label_new("N/A"); //Por default
  gdk_color_parse("#043047", &color);
  gtk_widget_modify_fg(GTK_WIDGET(label),GTK_STATE_NORMAL, &color);
  lista->label_cuenta=label;
  gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);

  //Color azul claro de la ventana
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

  //Empaqueta y muestra todo
  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_widget_show_all(window);

}

/*
*     Esta funcion sirve para solicitar préstamos de material, el usuario
*     debe de indicar el material que desea y la cantidad del mismo. El
*     número de cuenta esta guardado por default y es el del usuario. La
*     fecha de inicio y limite no se pueden modificar.
*/
void usuario_solicitar(GtkWidget *p, gpointer gp)
{
  //Declaraciones
  nodo *lista=(nodo *)gp;
  GtkWidget *window;
  GtkWidget *label;
  //Widgets
  GtkWidget *box;
  GtkWidget *vbox1;
  GtkWidget *vbox2;
  GtkWidget *caja;
  GtkWidget *button;
  GdkColor color;
  char linea[256];

  //Creación de ventana
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),20);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

  //Creación de cajas
  box=gtk_vbox_new(TRUE, 5); //Caja principal
  vbox1=gtk_vbox_new(TRUE, 5);  //Caja vertical 1
  vbox2=gtk_vbox_new(TRUE, 5);  //Caja vertical 2
  caja=gtk_hbox_new(TRUE, 5);   //Caja de abajo
  ;

  //Etiquetas con los titulos de informacion
  label=gtk_label_new("No Cuenta");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Inicio");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Limite");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Material");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Cantidad");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);

  //Cargar información de la base y mostrarla
  label=gtk_label_new(lista->no_cuenta);
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);

  sprintf(linea,"Select CURDATE()"); //Fecha actual
  if(mysql_query(&lista->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(lista->res = mysql_store_result(&lista->mysql)))
    g_print("Hubo error al sacar el query"); //Si no coinciden
  lista->row = mysql_fetch_row(lista->res); //Igualar a lista->row la informacion obtenida
  label=gtk_label_new(lista->row[0]); //Introducir informacion en un label
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0); //Empaquetar

  //Fecha Limite
  sprintf(linea,"Select ADDDATE(CURDATE(), INTERVAL 5 DAY)"); //Por default se asignan 5 días, pero puede haber excepciones desde la base de datos
  if(mysql_query(&lista->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(lista->res = mysql_store_result(&lista->mysql)))
    g_print("Hubo error al sacar el query");
  lista->row = mysql_fetch_row(lista->res);
  label=gtk_label_new(lista->row[0]);
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);

  //Combo box que despliega los materiales
  lista->entrylog[0] =  gtk_combo_box_text_new();
	combo_llenar_lista(lista);
	gtk_box_pack_start(GTK_BOX(vbox2),lista->entrylog[0],FALSE,FALSE,0);

  //Se introduce la cantidad del material seleccionado que se desea tomar prestada
	lista->entrylog[1] = gtk_entry_new();
 	gtk_entry_set_alignment(GTK_ENTRY(lista->entrylog[1]),0);
  gtk_entry_set_max_length(GTK_ENTRY(lista->entrylog[1]),5);
	gtk_box_pack_start(GTK_BOX(vbox2),lista->entrylog[1],FALSE,FALSE,0);

  //Empaquetar cajas
  gtk_box_pack_start(GTK_BOX(caja),vbox1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(caja),vbox2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box),caja,FALSE,FALSE,0);

  //Botón de solicitar, manda llamar a la función solicitar_usuario en validar.h
  button=gtk_button_new_with_label("Solicitar");
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  //Cambiar el connect por la funcion que cargue
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(solicitar_usuario),lista);

  //COLOR amarillo
  gdk_color_parse("#fdb70d", &color);
  gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

  //Empaquetar y mostrar
  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_widget_show_all(window);

}

/*
*     Esta función sirve para regresar préstamos de materiales. Se despliegan
*     los préstamos que tiene el usuario en la combo box en caso de existir.
*     Se debe de seleccionar el préstamo que desea regresar y presionar "Ver". El
*     número de cuenta esta guardado por default y es el del usuario. La
*     fecha de inicio y limite, el material, la cantidad y fecha fin no se
*     pueden modificar. Los comentarios son opcionales. Al presionar "Regresar
*     material" se conecta a una función que modifica la base de datos.
*/
void usuario_regresar(GtkWidget *p, gpointer gp)
{
  //Lista
  nodo *lista=(nodo *)gp;
  //Widgets
  GtkWidget *window;
  GtkWidget *label;
  GtkWidget *entrybox;
  GtkWidget *box;
  GtkWidget *vbox1;
  GtkWidget *vbox2;
  GtkWidget *caja;
  GtkWidget *top;
  GtkWidget *button;
  GdkColor color;
  //caracteres
  char linea[256];
  //Creación de ventana
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),20);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

  //Cajas
  box=gtk_vbox_new(FALSE, 5); //caja principal
  vbox1=gtk_vbox_new(FALSE, 5); //vertical 1
  vbox2=gtk_vbox_new(FALSE, 5); //vertical 2
  caja=gtk_hbox_new(FALSE, 5); //contiene vertical 1 y vertical 2
  top=gtk_vbox_new(FALSE, 5); //caja para label titulo

  //Titulo
  label=gtk_label_new("Prestamos vigentes");
  gtk_box_pack_start(GTK_BOX(top),label,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box),top,FALSE,FALSE,0);

  //Combo box con prestamos actuales del usuario
  lista->entrylog[0] =  gtk_combo_box_text_new();
  combo_llenar_lista_prestamos_vigentes(lista); //Pero llenar con prestamos
  gtk_box_pack_start(GTK_BOX(box),lista->entrylog[0],FALSE,FALSE,0);

  //Al activar el botón "Ver" se carga la información de dicho préstamo
  button= gtk_button_new_with_label("Ver");
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(Llenar_regresar),lista); //Llama a la función que carga el préstamo

  //Labels de la información a mostrar
  label=gtk_label_new("No Cuenta");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Inicio");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Limite");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Cantidad");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Fin");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);
  label=gtk_label_new("Comentarios");
  gtk_box_pack_start(GTK_BOX(vbox1),label,FALSE,FALSE,0);

  //Cargar el número de cuenta del usuario
  label=gtk_label_new(lista->no_cuenta);
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);

  //Por default está en "N/I", carga fecha de inicio
  label=gtk_label_new("N/I");
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);
  lista->entryregre[0]=label; //entryregre[0] guarda Inicio

  //Por default está en "N/I", carga fecha limite
  label=gtk_label_new("N/I");
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);
  lista->entryregre[1]=label; //entryregre[1] guarda Limite

  //Por default está en "N/I", carga cantidad
  label=gtk_label_new("N/I");
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);
  lista->entryregre[2]=label; //entryregre[2] guarda Cantidad

  //Selecciona la fecha actual para Fin
  sprintf(linea,"Select CURDATE()");
  if(mysql_query(&lista->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(lista->res = mysql_store_result(&lista->mysql)))
    g_print("Hubo error al sacar el query");
  lista->row = mysql_fetch_row(lista->res);
  mysql_free_result(lista->res);
  label=gtk_label_new(lista->row[0]); //Fin en Label
  gtk_box_pack_start(GTK_BOX(vbox2),label,FALSE,FALSE,0);

  //COMENTARIOS
  entrybox = gtk_entry_new (); //entrybox para comentarios
  gtk_box_pack_start(GTK_BOX(vbox2),entrybox,FALSE,FALSE,0);

  lista->entryregre[3]=entrybox;

  //Empaquetar cajas
  gtk_box_pack_start(GTK_BOX(caja),vbox1,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(caja),vbox2,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(box),caja,FALSE,FALSE,0);

  //Manda llamar función usuario_regresar_material
  button=gtk_button_new_with_label("Regresar material");
  gtk_box_pack_start(GTK_BOX(box),button,FALSE,TRUE,0);
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  //Cambiar el connect por la funcion que cargue
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(usuario_regresar_material),lista); //Esta función modifica PF_prestamos en la base de datos

  //Color ventana naranja
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL, &color);

  //Empaqueta y muestra
  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_widget_show_all(window);

}

#endif
