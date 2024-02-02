# Paluegos y to_do
* [] $$, *** debe mostrar syntax error ***
* [] $?
* [] $1 no muestra nada, $123 muestra 23
* [x] No detecta rl_replace_line
* []Implementar las señales
	* [x]SIGINT 
	* [x]SIGQUIT
	* [x]CTRL + D
	* [ ]Al hacer Ctrl C durante un heredoc no se comporta como bash **importante**hace salto de linea y deberia salir de heredoc
	* [ ]Al hacer ctrl D durante un heredoc **importante** en ft_heredoc no se comporta como bash ***La manera de solucionar estas movidas seria con la variable global dandole valor 1 en ft_handler, 2 al entrar a heredoc y 3 cuando se	este ejecutando el ultimo comando(cat) esto no lo entiendo muy bien y añadiendo if(sig == A SIGINT && global == 2) por ej***

* []con heredoc sale un leak de memoria al hacer el CTRL D
* []Quitar invalid read en ft_count_quotes
* [] Comprender perfect como funciona nuestra minishell **urgente e importante**
* [] Ejecutar una minishell dentro de otra y que se vayan acumulando (no se cierren)
* [] Ir ejecutando segun correccion
* [] Echo "\$<" & '$>' debe dar bad syntax error
* [] expandir variables en heredoc
* [X] echo "holaamigo"" no da error por comillas cerradas
* []cuando las comillas estan abiertas imprime error pero deberia de imprimirlo y volver a inicio(gestion de errores)