*Este proyecto ha sido creado como parte del currículo de 42 por wlu-bjor*

# Get Next Line

## Descripción

Este proyecto establece la función get_next_line(fd), el cual es capaz de leer una línea completa del descriptor de archivo indicado por el parámetro. Permite leer tanto de ficheros como de la entrada de lectura del programa, y en caso de leer ficheros, leerá hasta el fin del archivo cuando carece de saltos de línea. 

El programa lee en bloques de bytes, y en caso de leer demás (pasado el fin de línea), mantendrán los bytes restantes hasta la siguiente llamada de get_next_line, para que no se pierda esos datos de lectura anteriores

## Instrucciones

Con este proyecto se proporciona la función, y en cuanto se compile tendrá abierta la variable estática que almacenará el buffer de entrada, por lo que se puede seguir llamando la función de forma continua, y el programa gestionará la lectura hasta no quedar datos que leer. 

Aquí tiene un programa que es capaz de probar cada ejecución de la función:

```
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
// #include "get_next_line_bonus.h"
int main(void)
{
	// Probar leer ficheros o de entrada, descomenta el que desees
	// int fd = open("test.txt", O_RDONLY);
	int fd = 1;

	while (1)
	{
		char *string = get_next_line(fd);
		if (*string)
			printf("%s", string);
	}
	return (0);
}
```

## Recursos

Se ha utilizado el manual de C en momentos necesarios, compañeros en caso de duda, la inteligencia artificial en búsquedas de errores, edge cases que probar, y redacción del proyecto. No se ha utilizado ningún algoritmo innovador para implementar la función, lo que sí que ha sido necesario manejar ha sido la lectura de fichero y las variables estáticas.