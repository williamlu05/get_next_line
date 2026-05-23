*Este proyecto ha sido creado como parte del currículo de 42 por wlu-bjor*

# Get Next Line

## Descripción

`get_next_line` implementa una función que devuelve una línea completa cada vez que se llama con un descriptor de archivo (`fd`).

Objetivo del proyecto:
- Leer de forma incremental desde un `fd` sin cargar todo el archivo en memoria.
- Devolver cada línea incluyendo `\n` cuando exista.
- Mantener el estado entre llamadas para continuar desde el punto exacto de lectura anterior.

La función funciona tanto con archivos regulares como con la entrada estándar.

## Instrucciones

### Compilación

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c
```

También se puede compilar sin definir `BUFFER_SIZE`; en ese caso se usa el valor por defecto definido en el header.

### Uso básico

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Para leer de entrada estándar, usa `get_next_line(0)`. En caso de que quieras comprobar la parte bonus, se sustituye el header a la versión bonus.

## Algoritmo y Justificación Técnica

La implementación se apoya en una variable estática para conservar los bytes pendientes entre llamadas. El flujo es:

1. Leer bloques de tamaño `BUFFER_SIZE` y concatenarlos a un buffer persistente.
2. Detener la lectura en cuanto aparezca `\n` o `read()` devuelva fin de archivo.
3. Extraer y devolver la primera línea disponible del buffer persistente.
4. Guardar el resto para la siguiente llamada.

Justificación de esta estrategia:
- Cumple el requisito de lectura incremental: no procesa el archivo completo por adelantado.
- Minimiza lecturas innecesarias: al detectar `\n`, corta la lectura en esa llamada.
- Es robusta para líneas largas y tamaños de buffer muy distintos (`1`, `42`, `9999`, etc.).
- Respeta el comportamiento esperado en EOF:
  - Si queda texto sin `\n`, devuelve esa última línea.
  - Si no queda nada más que leer, devuelve `NULL`.

En bonus, se amplía la idea usando almacenamiento estático por descriptor para soportar múltiples `fd` en alternancia sin mezclar estados.

## Recursos

Referencias técnicas clásicas:
- Manual de `read(2)`: https://man7.org/linux/man-pages/man2/read.2.html
- Manual de `open(2)`: https://man7.org/linux/man-pages/man2/open.2.html
- Manual de `malloc(3)`: https://man7.org/linux/man-pages/man3/malloc.3.html
- Documentación POSIX (descriptor de archivo y E/S): https://pubs.opengroup.org/onlinepubs/9699919799/

Uso de IA en este proyecto:
- Se utilizó para revisar redacción y detectar casos límite a probar.
- No se usó para sustituir el proceso de diseño principal del algoritmo ni la comprensión de la lógica de lectura incremental.
- El código final se revisó manualmente para asegurar coherencia con las restricciones del enunciado.
