/**
*     @file Param.h
*
*     @brief En esta funcion se encuentran todos los parametros utilizados
*     a lo largo del programa para transportar la informacion.
*
*     @author Juan Castillo Carrillo, Ana Regina Morfin Marquez, y David Emmanuel Perez Avila
*     @date 03/12/2020
*/

#ifndef param_h
#define param_h
#include<gtk/gtk.h>
#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>

typedef struct parametros{
	//Entrys universales para varias funciones excluyendo combolog y entrylog[2] y [3] que se usan en el main
  GtkWidget *entrylog[5], *combolog;
	//-------------------------------------------------------------------
	//Widgets para dar de alta usuarios
	GtkWidget *altausu[11];
  //Widgets para busqueda mixta
  GtkWidget *busmix[7];
	//Widgets para modificacion de perifl
  GtkWidget *entryper[10];
  //Bandera para modificar
  int ban;
  //Widget para regresar material
  GtkWidget *entryregre[5];
  //Guardar numero de cuenta
  GtkWidget *label_cuenta;
  //string de nomero de cuenta y una linea para mensajes emergentes
  char no_cuenta[8], error[64];
  //variable temporal para no perder el no de cuenta actual
  char no_temp[8];
  //Variables SQL
  MYSQL mysql;
  MYSQL_RES *res;
  MYSQL_ROW row;
  MYSQL_FIELD *fields;
}nodo;

#endif
