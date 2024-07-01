#include <stdio.h>
#include <mysql.h>

//Datos de conexión a la base de datos
#define HOST "localhost"
#define PORT 3306
#define USERNAME "root"
#define PASSWORD "Lore44"
#define DATABASE "cursoc"

int main(){
	
	int error;
	MYSQL conexion;
	
	error = conectar(&conexion); 
	
	return 0;
}

int conectar(MYSQL *conexion){
	int error;
	
	conexion = mysql_init(NULL); //devuelve una referencia a MYSQL. Se inicializa el puntero para preparar la conexión
	
	if(mysql_real_connect(conexion, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) != NULL){ //Si se logró realizar la conexión...
		printf("Se establecio la conexion con la base de datos\n");
		error = 0;
	}else{
		printf("Error con la conexion con la base de datos\n");
		error = 1;
	}
	
	return error;
}
