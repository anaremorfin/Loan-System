/**
*     @file Login.h
*
*     @brief En este programa se hace una division para saber si la cuenta colocada
*			es de un usuario o un administrador y asi mismo despliega las ventanas principales
*     de estos mismos.
*
*     @author Juan Castillo Carrillo, Ana Regina Morfin Marquez, y David Emmanuel Perez Avila
*     @date 03/12/2020
*/

#ifndef Login_h
#define Login_h
#include"Param.h"
#include "Usuario.h"
#include "Admin.h"

/*
*     Funcion para destruir una ventana emergente y
*			toma el numero de cuenta colocandolo en un temporal
*     para que no se destruya.
*
*/
void destruir (GtkWidget *d,gpointer data)
{
  nodo *lista=(nodo *)data;
  strcpy(lista->no_cuenta ,lista->no_temp);
  gtk_widget_destroy(d);
}

/*
*     Despliega la ventana de opciones para el administrador
*			en las cuales se incluyen visualizar usuarios, modificar
*     usuarios, registrar nuevo usuario, historial de busqueda,
*     modos de busqueda y acceso al inventario del laboratorio.
*
*/
void login_admin (nodo *data)
{
  GtkWidget *window, *button, *box, *box2;
  GdkColor color;
  char titulo[] = "VENTANA DEL ADMINISTRADOR: ";
  strcat(titulo,data->no_cuenta);
  box = gtk_vbox_new(TRUE,0);
  box2 = gtk_hbox_new(TRUE,0);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,400);
  gtk_container_border_width(GTK_CONTAINER(window),10);
  gtk_window_set_title(GTK_WINDOW(window),titulo);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(destruir),data);

  button = gtk_button_new_with_label("VISUALIZAR\nUSUARIOS");
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(visualizar_usuarios), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  button = gtk_button_new_with_label("MODIFICAR\nUSUARIOS");
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(admin_modificar), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

  box2 = gtk_hbox_new(TRUE,0);
  button = gtk_button_new_with_label("REGISTRAR\nUSUARIO");
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(registro_usuario), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  button = gtk_button_new_with_label("HISTORIAL DE\nBUSQUEDAS");
  gdk_color_parse("#fdb70d", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(historial_de_busqueda), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

  box2 = gtk_hbox_new(TRUE,0);
  button = gtk_button_new_with_label("BUSCAR POR\nNOMBRE/TIPO");
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(buscar_nombre), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  button = gtk_button_new_with_label("BUSCAR POR\nCRITERIO");
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(buscar_criterio), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

  box2 = gtk_hbox_new(TRUE,0);
  button = gtk_button_new_with_label("SOLICITAR\nMATERIAL");
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(admin_pedir_material), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  button = gtk_button_new_with_label("MÁS\nINFORMACIÓN");
  gdk_color_parse("#fdb70d", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(mas_informacion), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_widget_show_all(window);
}

/*
*     Despliega la ventana de opciones para el usuario
*			en las cuales se incluyen solicitar material, devolver material,
*     ver disponibilidad de material y modificar nuestro perfil.
*
*/
void login_usuario (nodo *data)
{
  GtkWidget *window, *button, *box, *box2;
  GdkColor color;
  char titulo[] = "VENTANA DEL USUARIO: ";
  strcat(titulo,data->no_cuenta);
  box = gtk_vbox_new(TRUE,0);
  box2 = gtk_hbox_new(TRUE,0);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),320,200);
  gtk_container_border_width(GTK_CONTAINER(window),10);
	gtk_window_set_title(GTK_WINDOW(window),titulo);
	gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(destruir),data);

  button = gtk_button_new_with_label("SOLICITAR\nMATERIAL");
  gdk_color_parse("#f98305", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(usuario_solicitar), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  button = gtk_button_new_with_label("REGRESAR\nMATERIAL");
  gdk_color_parse("#2a9ebc", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(usuario_regresar), data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

  box2 = gtk_hbox_new(TRUE,0);
  button = gtk_button_new_with_label("BUSQUEDA");
  gdk_color_parse("#90cae6", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(usuario_busqueda),data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  button = gtk_button_new_with_label("PERFIL");
  gdk_color_parse("#fdb70d", &color);
  gtk_widget_modify_bg(GTK_WIDGET(button),GTK_STATE_NORMAL, &color);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(usuario_perfil),data);
  gtk_box_pack_start(GTK_BOX(box2),button,FALSE,TRUE,0);
  gtk_box_pack_start(GTK_BOX(box),box2,FALSE,TRUE,0);

  gtk_container_add(GTK_CONTAINER(window),box);
  gtk_widget_show_all(window);
}

#endif
