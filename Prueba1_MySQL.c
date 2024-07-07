#include <stdio.h>
#include <mysql.h>

//Datos de conexi�n a la base de datos
#define HOST "localhost"
#define PORT 3306
#define USERNAME "root"
#define PASSWORD "Lore44"
#define DATABASE "cursoc"

int conectar(MYSQL **conexion);
void ejecutar_consulta(MYSQL *conexion, char *consulta);

int main(){
	
	int error;
	char *consulta;
	MYSQL *conexion; //Propio de MYSQL. Permite realizar la conexi�n
	
	error = conectar(&conexion); 
	
	if(!error){
		consulta = "SELECT *FROM usuarios";
		ejecutar_consulta(conexion, consulta);
		mysql_close(conexion); //IMPORTANTE: Cerrar la sesi�n de MYSQL porque consume recursos del sistema operativo
	}
	
	return 0;
}

int conectar(MYSQL **conexion){ //Para MYSQL trabaja con punteros
	int error;
	
	*conexion = mysql_init(NULL); //devuelve una referencia a MYSQL. Se inicializa el puntero para preparar la conexi�n
	
	if(mysql_real_connect(*conexion, HOST, USERNAME, PASSWORD, DATABASE, PORT, NULL, 0) != NULL){ //Si se logr� realizar la conexi�n...
		printf("Se establecio la conexion con la base de datos\n");
		error = 0;
	}else{
		printf("Error con la conexion con la base de datos\n");
		error = 1;
	}
	
	return error;
}

void ejecutar_consulta(MYSQL *conexion, char *consulta){ //Est� recibiendo datos de la funci�n anterior y como segundo parametro recibe una cadena que tiene la instrucci�n SQL
	
	int error, filas, columnas, i, j;
	MYSQL_RES *resultado_conexion; //Se almacena en un puntero porque as� lo dice MYSQL. Almacena el resultado de la conexi�n.
	MYSQL_FIELD *campo; //Funci�n de MYSQL que va recorriendo las columnas
	MYSQL_ROW resultado_fila; //Funci�n de MYSQL que almacena el resultado de la fila
	
	error = mysql_query(conexion, consulta); //Permite ejecutar una consulta
	
	if(!error){ //Si no existe ning�n error....
		resultado_conexion = mysql_store_result(conexion); //mysql_store_result = funci�n propia de MYSQL, nos arroja el resultado de la conxi�n
		
		if(resultado_conexion){ //Si el puntero es v�lido, entonces...
			filas = mysql_num_rows(resultado_conexion); //mysql_num_rows:funci�n propia de MYSQL, almacena el n�m. de filas
			columnas = mysql_num_fields(resultado_conexion); //mysql_num_fields: Funci�n propia de MYSQL, almacena el n�m. de columnas
			
			/*----------- Damos a continuaci�n un formato de tabla como aparece en la workbeanch ---------------*/
			
			while(campo=mysql_fetch_field(resultado_conexion)){ //Mientras todo eso no sea nulo.Funci�n propia de MYSQL que obtiene el n�mero de columnas total y va recorriendo el puntero para obtener todos los n�mero de columnas
				
				printf("%15s", campo->name); //Mostrar una cadena con 15 espacios y si es m�s chica de 15 llenar con espacios en blanco y siempre ocupar 15 espacios, y se muestra el campo name
	                                         //El campo name al parecer es propio de MYSQL		
			} 	
			printf("\n");
			
			/*---------------------------------- Mostrar datos de MYSQL ---------------------------------------*/
			for(i=1; i<filas; i++){
				resultado_fila = mysql_fetch_row(resultado_conexion); //Resultado_fila es un vector no un puntero
				for(j=0; j<columnas; j++){
					printf("%15s", resultado_fila[j]);
				}
				printf("\n");
			}
		}
	}else{
		printf("Ocurrio un error al ejecutar la consulta SQL\n"); //En caso de haber un error
	}
	
}
