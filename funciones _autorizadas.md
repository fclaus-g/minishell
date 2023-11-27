# FUNCIONES AUTORIZADAS MINISHELL

***getcwd->** (std) Se usa para obtener el directorio de trabajo actual.
```C
#include <unistd.h>
#include <stdio.h>
//prototipo
char *getcwd(char *buf, size_t size);
//ejemplo de uso
void imprimir_directorio_actual(void)
{
    char directorio_actual[1024];
    if (getcwd(directorio_actual, sizeof(directorio_actual)) != NULL)
    {
        printf("Directorio actual: %s\n", directorio_actual);
    }
    else
    {
        perror("Error obteniendo el directorio actual");
    }
}
```
En este código se almacena el retorno de getcwd en la variable directorio actual.

