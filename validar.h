/**
 *  @file validar.h
*
*     @brief Este archivo funciona como el motor del programa entero de Laboratorio.c, ya que se encuentran todas las funciones
*            que controlan los botones, asi como la interaccion con la base de datos, validar ciertos comando y sacar las
             ventanas emergetes de error y la inicializacion de mysql
*
*     @author Juan Castillo Carrillo, Ana Regina Morfin Marquez, y David Emmanuel Perez Avila
*     @date 03/12/2020
*/
#ifndef validar_h
#define validar_h
#include "Param.h"
/*
 *Esta funcion inicializa el mysql con la base a la que nos vamos a conectar
 */
void iniciar_mysql(nodo *data)
{
    mysql_init(&data->mysql); // Prepara la conexion al servidor de bases de datos
     // Se conecta al servidor de base de datos y verifica que no haya error
    if(!mysql_real_connect(&data->mysql, "localhost", "ic19amm", "216200","ic19amm", 0, NULL, 0)){
      exit(1);
    }
    if( mysql_select_db(&data->mysql,"ic19amm") ){
        exit(1);
    }
}
/*
 * Esta funcion genera una ventana emergente, ya sea de error o para informar al usuario
 */

void error_emergente (nodo *lista)
{
	GtkWidget *window, *box, *label;

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),"Mensaje");
  gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
  gtk_container_border_width(GTK_CONTAINER(window),30);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_widget_destroy),window);

	box = gtk_vbox_new(TRUE, 0);

	label = gtk_label_new(lista->error);
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);
	label = gtk_button_new_with_label("OK");
	g_signal_connect_swapped(GTK_OBJECT(label),"clicked",GTK_SIGNAL_FUNC(gtk_widget_destroy), window);
	gtk_box_pack_start(GTK_BOX(box),label,FALSE,FALSE,0);

	gtk_container_add(GTK_CONTAINER(window),box);
	gtk_widget_show_all(window);
}
/**
 *Esta funcion valida si el usuario y la contrasena y e tipo estan en la base de datos
 */

int validar_cuenta_pass(char cuenta[], char passw[], char tip[],nodo *data)
{
	int i,cant=0;
	char linea[1024];
	strcat(tip,"U");
	if(strcmp(cuenta,"")==0)
	  strcat(cuenta,"-1");
	if(strcmp(passw,"")==0)
	  strcat(passw,"a");
	sprintf(linea,"Select NoCuenta from PF_usuarios where NoCuenta='%s' AND Passw='%s' AND Tipo='%c'", cuenta, passw, tip[0]);
   	if( mysql_query(&data->mysql,linea) ){
        	return -1;
	}
    // Obtiene el query
    if( !(data->res = mysql_store_result(&data->mysql)) ){
	return -1;
    }
    while( (data->row = mysql_fetch_row(data->res)) ){
        i = 0;

        for( i=0 ; i < mysql_num_fields(data->res); i++ )
	cant++;
}
	if(cant==0)
	return -1;
	mysql_free_result(data->res);
	return 0;
}
/**
 * Esta funcion sirve para sacar un dato especifico de la base de datos de los usuarios
 */
void sacar_dato(char dato[], char tabla[], nodo*data)
{
	char linea[256];
	sprintf(linea,"Select %s from %s where NoCuenta=%s",dato, tabla, data->no_cuenta);
	mysql_query(&data->mysql,linea);
	data->res = mysql_store_result(&data->mysql);
	data->row = mysql_fetch_row(data->res);
	mysql_free_result(data->res);
}
/**
 * Esta funcion es del boton de Usuario_prestamo  donde se conceta a la base y hace "el prestamo"
 */
void solicitar_usuario(GtkWidget *v, gpointer gp)
{
  nodo *data=(nodo *)gp;
  const char *mat, *cantidad;
  char text[8];//Este es la cantidad
  int t=-1, dispo=0, cant=0;//Este es el id
  int ban=0;
  char linea[256];
  mat = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]));
  if(mat!=NULL)
    sscanf(mat,"%d",&t);
  else
    t=-1;
  cantidad = gtk_entry_get_text(GTK_ENTRY(data->entrylog[1]));
  strcpy(text,cantidad);
  //Verifica
  sacar_dato("Adeudo","PF_usuarios",data);
  if(strcmp(data->row[0],"0")==0)
  {
    if(t==-1)
      {
        strcpy(data->error,"Seleccione un material");
        error_emergente(data);
      }
    else
      {
        //Verificar si hay disponibilidad
        sprintf(linea, "Select PF_disponibilidad(%d)", t);
        if(mysql_query(&data->mysql,linea))
    g_print("Hubo error al ejecutar query");
        if(!(data->res = mysql_store_result(&data->mysql)))
    g_print("Hubo error al sacar el query");
        data->row = mysql_fetch_row(data->res);

        sscanf(data->row[0],"%d", &dispo);
        sscanf(cantidad, "%d", &cant);
        if(cant==0)
    ban++;
        if((dispo-cant)<0)
    {
      strcpy(data->error,"No se puede esa cantidad\nConsulte Disp[onibilidad");
      error_emergente(data);
    }
        else
    {
      mysql_query(&data->mysql,"START TRANSACTION");
      sprintf(linea,"INSERT INTO PF_prestamos (Inicio, Limite,NoCuenta) VALUES (CURDATE(),ADDDATE(CURDATE(), INTERVAL 5 DAY), %s)", data->no_cuenta);
      if(mysql_query(&data->mysql,linea))
        ban++;

      sprintf(linea,"SELECT Prestamoid from PF_prestamos order by Prestamoid desc Limit 1");
      if(mysql_query(&data->mysql,linea))
        g_print("Hubo error al ejecutar query");
      if(!(data->res = mysql_store_result(&data->mysql)))
        g_print("Hubo error al sacar el query");
      data->row = mysql_fetch_row(data->res);

      sprintf(linea,"INSERT INTO PF_prestamos_inventario (Prestamoid, Materialid, CantidadP) VALUES (%s,%d, %d)",data->row[0],t, cant);
      if(mysql_query(&data->mysql,linea))
        ban++;
      if(ban>0)
        {
          mysql_query(&data->mysql,"ROLLBACK");
          strcpy(data->error,"Hubo un error al solicitar material\nVerifique cantidad");
          error_emergente(data);
        }
      else
        {
          mysql_query(&data->mysql,"COMMIT");
          strcpy(data->error,"Material solicitado\nRegrese sui material el dia indicado");
          error_emergente(data);
        }
    }

      }
  }
  else
  {
    strcpy(data->error,"USTED TIENE UN ADEUDO\nCONTACTE AL ADMINISTRADOR");
    error_emergente(data);
  }

}
/*
 * Esta funcion proveniente de Admin.h actualiza la base para aumentar la cantidad de materiales que hay
 */
void prestamo_admin (GtkWidget *p, gpointer data)
{
  nodo *lista=(nodo *)data;
  const char *mat, *cantidad;
  char text[8];//Este es la cantidad
  int t;//Este es el id
  char linea[256];
  mat = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(lista->entrylog[0]));
  cantidad = gtk_entry_get_text(GTK_ENTRY(lista->entrylog[1]));

  sscanf(mat,"%d",&t);
  strcpy(text, cantidad);

  sprintf(linea, "CALL PF_Pedir_Admin(%d, %s)", t, text);
  mysql_query(&lista->mysql,linea);

    strcpy(lista->error,"PROCEDIMIENTO\nCOMPLETADO");

    error_emergente(lista);

}
/*
 * ESta funcion llena un combo?box con el materialid y el nombre de todos los materiales que hay en la base
 * Se usa en todas las funciones que lo necesite una combo_box con los materiales
 */

void combo_llenar_lista(nodo *data)
{
  char linea[256];
  sprintf(linea,"Select Materialid,Nombre from PF_inventario");
  if(mysql_query(&data->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(data->res = mysql_store_result(&data->mysql)))
    g_print("Hubo error al sacar el query");

  while( (data->row = mysql_fetch_row(data->res)) )
  {
    int	i = 0;
    strcpy(linea, "");
    for( i=0 ; i < mysql_num_fields(data->res); i++){
      if(data->row[i] != NULL){
	strcat(linea,data->row[i]);
	if(i==0)
	strcat(linea,"_");
      }
    }
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]), linea);
  }
  mysql_free_result(data->res);
}
/*
 * Esta funcion llena un combo?box con el Numero de Cuenta y el nombre de todos los usuarios que hay en la base
 * Se usa en todas las funciones que lo necesite una combo_box con los usuarios
 */
void combo_llenar_lista_U(nodo *data)
{
  char linea[256];
  sprintf(linea,"Select NoCuenta,Nombre from PF_usuarios");
  if(mysql_query(&data->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(data->res = mysql_store_result(&data->mysql)))
    g_print("Hubo error al sacar el query");

  while( (data->row = mysql_fetch_row(data->res)) )
  {
    int	i = 0;
    strcpy(linea, "");
    for( i=0 ; i < mysql_num_fields(data->res); i++){
      if(data->row[i] != NULL){
	strcat(linea,data->row[i]);
	if(i==0)
	strcat(linea,"_");
      }
    }
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]), linea);
  }
  mysql_free_result(data->res);
}
/*
ESta funcion llena un combo?box con el el numero del prestamo de y el nombre del material
todos los prestamos no regresados que hay en la base
 * Se usa en todas las funciones que lo necesite una combo_box con los prestamos
 */
void combo_llenar_lista_prestamos_vigentes(nodo *data)
{
  char linea[256];
  sprintf(linea,"SELECT Prestamoid, Nombre FROM PF_prestamos LEFT JOIN PF_prestamos_inventario USING(Prestamoid) LEFT JOIN PF_inventario USING(Materialid) WHERE NoCuenta=%s AND Fin IS NULL", data->no_cuenta);
  if(mysql_query(&data->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(data->res = mysql_store_result(&data->mysql)))
    g_print("Hubo error al sacar el query");

  while( (data->row = mysql_fetch_row(data->res)) )
  {
    int	i = 0;
    strcpy(linea, "");
    for( i=0 ; i < mysql_num_fields(data->res); i++){
      if(data->row[i] != NULL){
	strcat(linea,data->row[i]);
	if(i==0)
	strcat(linea,"_");
      }
    }
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]), linea);
  }
  mysql_free_result(data->res);
}
/*
 * Llena la informacion de Admin_modificar en todas las entrys
 */
void Llenar_modificar(GtkWidget *b, gpointer gp)
{
  nodo *data=(nodo *)gp;
  const char *mat;
  char linea[256];
  int t;
  mat = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]));
  if(mat!=NULL)
  {
  sscanf(mat,"%d",&t);
  sprintf(linea, "%d", t);

  gtk_label_set_text(GTK_LABEL(data->label_cuenta), linea);
  strcpy(data->no_cuenta, linea);

	sacar_dato("Nombre", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[0]), data->row[0]);
	sacar_dato("AP", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[1]), data->row[0]);
	sacar_dato("AM", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[2]), data->row[0]);
	sacar_dato("Carrera", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[3]), data->row[0]);
	sacar_dato("Semestre", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[4]), data->row[0]);
	sacar_dato("FechaNac", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[5]), data->row[0]);
	sacar_dato("Correo", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[6]), data->row[0]);
	sacar_dato("Passw", "PF_usuarios", data);
	gtk_entry_set_text(GTK_ENTRY(data->entryper[7]), data->row[0]);
	if(data->ban==1)
	  {
	    sacar_dato("Tipo", "PF_usuarios", data);
	    if(strcmp(data->row[0],"U")==0)
	    gtk_label_set_text(GTK_LABEL(data->entryper[9]),"Usuario");
	    else
	     gtk_label_set_text(GTK_LABEL(data->entryper[9]),"Administrador");
	    sacar_dato("Adeudo", "PF_usuarios", data);
	    if(strcmp(data->row[0],"0")==0)
	      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->entryper[8]), FALSE);
	    else
	      gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->entryper[8]), TRUE);
	  }
  }

}
/*
 * Esta funcion guarda los datos en la base de datos
 */
void guardar_datos(GtkWidget *b, gpointer gp)
{
  nodo *data=(nodo *)gp;
  const gchar *text[8];
  int i;
  int ban=0;
  char linea[256];
  char dato[32];
  char campo[32];

  mysql_query(&data->mysql,"START TRANSACTION");
  for (i=0;i<8;i++)
    {
      text[i]=gtk_entry_get_text(GTK_ENTRY(data->entryper[i]));
      if(text[i]==NULL)
	strcpy(dato,"N/I");
      else
	strcpy(dato, text[i]);
      switch(i){
      case 0:
	strcpy(campo, "Nombre");
	break;
      case 1:
	strcpy(campo, "AP");
	break;
      case 2:
	strcpy(campo, "AM");
	break;
      case 3:
	strcpy(campo, "Carrera");
	break;
      case 4:
	strcpy(campo, "Semestre");
	break;
      case 5:
	strcpy(campo, "FechaNac");
	break;
      case 6:
	strcpy(campo, "Correo");
	break;
      case 7:
	strcpy(campo, "Passw");
	break;
      case 8:
	strcpy(campo,"Adeudo");
	break;
      }

      sprintf(linea,"UPDATE PF_usuarios SET %s='%s' where NoCuenta=%s", campo, dato, data->no_cuenta);
      if(mysql_query(&data->mysql,linea))
	{
	  ban++;
	}

    }
  if(data->ban==1)
    {
  if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->entryper[8])))
    {
sprintf(linea,"UPDATE PF_usuarios SET Adeudo=1 where NoCuenta=%s", data->no_cuenta);
      if(mysql_query(&data->mysql,linea))
	{
	  ban++;
	}
    }
  else
    {
sprintf(linea,"UPDATE PF_usuarios SET Adeudo=0 where NoCuenta=%s", data->no_cuenta);
      if(mysql_query(&data->mysql,linea))
	{
	  ban++;
	}
    }
    }
  if(ban>0)
    {
      mysql_query(&data->mysql,"ROLLBACK");
      strcpy(data->error,"Hubo un error en la Matrix");
    error_emergente(data);
    }
  else
    {
      mysql_query(&data->mysql,"COMMIT");
      strcpy(data->error,"Datos actualizados");
    error_emergente(data);
    }
}

/*
 * Esta funcion hace el proceso de busqueda de la disponibilidad de los materiales
 */
void busqueda_material(GtkWidget *p, gpointer gp)
{
  nodo *data=(nodo *)gp;
  char linea[512];
  const char *mat;
  int t;
  mat = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]));
  sscanf(mat,"%d",&t);
  sprintf(linea,"Select PF_disponibilidad(%d)", t);

  if(mysql_query(&data->mysql,linea))
    g_print("Hubo error al ejecutar query");
  if(!(data->res = mysql_store_result(&data->mysql)))
    g_print("Hubo error al sacar el query");

  data->row = mysql_fetch_row(data->res);
  gtk_label_set_text(GTK_LABEL(data->label_cuenta),data->row[0]);
  sprintf(linea," INSERT INTO PF_busquedas (FHBusqueda, NoCuenta, Materialid) VALUES (NOW() ,%s,%d)",data->no_cuenta,t);
  mysql_query(&data->mysql,linea);

  mysql_free_result(data->res);


}
/*
 * Esta funcion recibe los entrybox de la ventana y los datos los mete a la base
 */
void admin_alta_usuario (GtkWidget *p,gpointer data)
{
  nodo *lista = (nodo *)data;
  const char* text[11];
  char datos[11][64];
  char linea[1024],aux1[512], aux2[512], fech[32];
  int i;
  for(i=0; i<11; i++)
    {
      if(i==5||i==6||i==7||i==10)
	{
	  text[i] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(lista->altausu[i]));
	  if(text[i]==NULL)
	    strcpy(datos[i],"U");
	  else
	    strcpy(datos[i],text[i]);

	}
      else
	{
	  text[i] = gtk_entry_get_text(GTK_ENTRY(lista->altausu[i]));
	  strcpy(datos[i],text[i]);
	}
    }

  sprintf(fech, "%s-%s-%s",datos[5], datos[6], datos[7]);
  sprintf(aux1,"INSERT INTO PF_usuarios (Nombre,AP, AM, Carrera,Semestre, FechaNac, Correo, Passw, Tipo) VALUES ('%s','%s', '%s','%s', %s,",datos[0],datos[1],datos[2],datos[3],datos[4]);
  sprintf(aux2,"'%s', '%s', '%s','%c')", fech, datos[8], datos[9], datos[10][0]);
  strcpy(linea,aux1);
  strcat(linea, aux2);

  if(mysql_query(&lista->mysql,linea))
    {
      strcpy(lista->error,"Hubo un falla en la Matrix\nCheque los datos a ingresar");
      error_emergente(lista);
    }
  else
    {
      sprintf(linea,"SELECT NoCuenta from PF_usuarios order by NoCuenta desc Limit 1");
	  if(mysql_query(&lista->mysql,linea))
	    g_print("Hubo error al ejecutar query");
	  if(!(lista->res = mysql_store_result(&lista->mysql)))
	    g_print("Hubo error al sacar el query");
	  lista->row = mysql_fetch_row(lista->res);
	  sprintf(lista->error,"Nuevo usuario registrado\nNO.CUENTA: %s", lista->row[0]);
	  error_emergente(lista);
    }
}
/*
 * Esta funcion llena los labels de los campos conforme al prestamo seleccionado
 */
void Llenar_regresar(GtkWidget *x, gpointer gp)
{
  nodo *data=(nodo *)gp;
  const char *tex;
  char linea[256];
  int idp;
  tex=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]));
  if(tex==NULL)
    {
      sprintf(data->error,"NO hay campo seleccionado");
      error_emergente(data);
    }
  else
    {
      sscanf(tex,"%d",&idp);
      sprintf(linea,"SELECT Inicio, Limite,CantidadP from PF_prestamos left join PF_prestamos_inventario using(Prestamoid) where Prestamoid=%d", idp);
	  if(mysql_query(&data->mysql,linea))
	    g_print("Hubo error al ejecutar query");
	  if(!(data->res = mysql_store_result(&data->mysql)))
	    g_print("Hubo error al sacar el query");
	  data->row = mysql_fetch_row(data->res);
	  mysql_free_result(data->res);

      gtk_label_set_text(GTK_LABEL(data->entryregre[0]),data->row[0]);
      gtk_label_set_text(GTK_LABEL(data->entryregre[1]),data->row[1]);
      gtk_label_set_text(GTK_LABEL(data->entryregre[2]),data->row[2]);
    }
}
/*
 *Esta funcion hace update del prestamo para que salga que ya lo realizao
 */
void usuario_regresar_material(GtkWidget *m, gpointer gp)
{
  nodo *data=(nodo *)gp;
  const char *tex, *com;
  char linea[256];
  int idp, ban=0, day;
    tex=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->entrylog[0]));
    com=gtk_entry_get_text(GTK_ENTRY(data->entryregre[3]));
  if(tex==NULL)
    {
      sprintf(data->error,"No hay prestamo seleccionado");
      error_emergente(data);
    }
  else
    {
      sscanf(tex,"%d",&idp);
      sprintf(linea,"START TRANSACTION");
      mysql_query(&data->mysql,linea);

      sprintf(linea,"UPDATE PF_prestamos SET FIN=CURDATE() where Prestamoid=%d",idp);
      if(mysql_query(&data->mysql,linea))
	ban++;
      sprintf(linea,"UPDATE PF_prestamos SET Comentarios='%s' where Prestamoid=%d",com,idp);
      if(mysql_query(&data->mysql,linea))
	ban ++;
      //Hacer precedimiento
      sprintf(linea,"SELECT DATEDIFF(Limite, CURDATE()) from PF_prestamos where Prestamoid=%d", idp);
      if(mysql_query(&data->mysql,linea))
	ban ++;
      if(!(data->res = mysql_store_result(&data->mysql)))
	g_print("Hubo error al sacar el query");
      data->row = mysql_fetch_row(data->res);
      mysql_free_result(data->res);
      sscanf(data->row[0], "%d", &day);
      if(day<0)
	{
	  sprintf(linea,"UPDATE PF_usuarios SET Adeudo=1 where NoCuenta=%s",data->no_cuenta);
	  if(mysql_query(&data->mysql,linea))
	    ban++;
	}
      if(ban>0)
	{
	  sprintf(linea,"ROLLBACK");
	  mysql_query(&data->mysql,linea);
	  sprintf(data->error,"Hubo un error en la matrix");
	  error_emergente(data);
	}
      else
	{
	  sprintf(linea,"COMMIT");
	  mysql_query(&data->mysql,linea);
	  sprintf(data->error,"Su material ha sido regresado con exito");
	  error_emergente(data);
	}
    }
}
/*
 *Crea una ventana donde conforme al query que llega despliega el resultado
 */
void visualizar_nombre_tipo(nodo *data, char linea[])
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
	if( mysql_query(&lista->mysql,linea) ){
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
 * Sirve para ejecutar la funcion de buscar de nombre o tipo
 */
void admin_buscar_tipo(GtkWidget *t, gpointer gp)
{
  nodo *data= (nodo *)gp;
  const char *nom, *tip;
  char tipo[16], linea[256];
  tip=gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(data->entrylog[1]));
  nom=gtk_entry_get_text(GTK_ENTRY(data->entrylog[0]));
  if(tip!=NULL)
    strcpy(tipo,tip);
  strcat(tipo, "V");
  if(strcmp(nom,"")==0)
    {
      if(tip==NULL || tipo[0]=='V')
	{
	  sprintf(data->error,"Seleccione algun campo");
	  error_emergente(data);
	}
      else
	{
	  sprintf(linea, "SELECT * from PF_usuarios where Tipo='%c'", tipo[0]);
	  visualizar_nombre_tipo(data, linea);
	}
    }
  else
    {
      sprintf(linea, "SELECT * from PF_usuarios where Nombre='%s'", nom);
      visualizar_nombre_tipo(data, linea);
    }
}
/*
 *Funcion que sirve para crear el query y desplegar toda la informacion de buscar por criterios
 */
void busqueda_crit (GtkWidget *p, gpointer gp)
{
  nodo *lista = (nodo *)gp;
  const char* text[7];
  char linea[1028];
  char aux[128];
  char auxf[32];
  int i;

  for(i=0; i<7; i++)
  {
    if(i==6||i==5||i==4)
    {
      text[i] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(lista->busmix[i]));
    }
    else
    {
      text[i] = gtk_entry_get_text(GTK_ENTRY(lista->busmix[i]));
    }
  }
  sprintf(linea, "Select * from PF_usuarios where (Adeudo=0 OR Adeudo=1) ");
    if(strcmp(text[0],"")!=0)
      {
	sprintf(aux,"AND AP='%s' ", text[0]);
	strcat(linea,aux);
      }
    if(strcmp(text[1],"")!=0)
      {
	sprintf(aux,"AND NoCuenta=%s ", text[1]);
	strcat(linea,aux);
      }
    if(strcmp(text[2],"")!=0)
      {
	sprintf(aux,"AND Carrera='%s' ", text[2]);
	strcat(linea,aux);
      }
    if(strcmp(text[3],"")!=0)
      {
	sprintf(aux,"AND Semestre=%s ", text[3]);
	strcat(linea,aux);
      }

    if((text[4]!=NULL)&&(text[5]!=NULL)&&(text[6]!=NULL))
      {
	sprintf(auxf,"%s-%s-%s", text[4], text[5], text[6]);
	sprintf(aux,"AND FechaNAc='%s'", auxf);
	strcat(linea,aux);
	}

    visualizar_nombre_tipo(lista, linea);

}


#endif
