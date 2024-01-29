# Corrección Minishell

### Compile
* **make -n** para comprobar que se ejecutan las flags *-Wall -Werror -Wextra*.
* Compila sin errores.
* El makefile no relink.

### Comandos simples y variables globales
* []Ejecutar un comando simple con un un path absoluto como  [**/bin/ls**] ---->  				**muestra command not found**
* []Explicar porque usamos una global ----------------------------------------->  				**aun no uso la global**
* [X]Probar entrada vacia ->**da un salto de linea OK**
* []Probar solo espacios o tabs ->**espacio muestra \n y tabs autocompleta**

### Argumentos
* []Ejecutar comando simple con path absoluto como [**/bin/ls**] con opciones y sin comillas -> **muestra command not found**
* []Repetir multiples veces con comandos y args 

### echo
* []Ejecutar echo, echo + args y echo -n
* []Probar diferentes args
### exit
* []exit con y sin args
* []Probar diferentes args

### Retornar valor de un proceso
* []**echo $?**
	Ejecutar comando simple con path absoluto como [**/bin/ls**] con opciones y sin comillas y luego $?
* []Chequear el valor impreso y comprobar que es igual que en bash.
* []Repetir varias veces con diferentes comandos y argumentos. Probar con **'/bin/ls filethatdoesntexist'**
* []Probar $? + $?

### Signals
* []^C en un promt