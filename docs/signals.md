# Implementación de señales en minishell.

## Comandos bash a tener en cuenta:

```Bash
cascaribash$ ps #muestra procesos
  PID TTY           TIME CMD
 3580 ttys000    0:00.03 -zsh
 3751 ttys002    0:00.01 ./minishell
76071 ttys002    0:00.03 /bin/zsh -il
10376 ttys003    0:00.02 -zsh
#------------------------------------#
cascaribash$ ps | grep minishell #muestra procesos y los filtra por nombre, ojo mostrará tb el grep. Salida-> 
3751 ttys002    0:00.01 ./minishell
10416 ttys003    0:00.00 grep minishell
#------------------------------------#
cascaribash$ ps | grep minishell | grep -v grep #nos oculta la linea del proceso de grep
3751 ttys002    0:00.01 ./minishell
#------------------------------------#
cascaribash$ ps | grep minishell | grep -v grep | awk '{print $1}' #imprime solo el primer arg de la linea, el PID
3751
```

### Que es lo que tengo que hacer con las señales
Si se presiona **Ctrl+C=SIGINT** podemos decir que hay que mostrar un salto de linea y muestre el prompt. Para ello hay que hacer uso de la función rl_on_new_line();rl_replace_line("", 0); y rl_redisplay();

Si se presiona **CTRL+ D** no es una señal sino un caracter de control que representa el EOF. Cuando se presiona en un terminal quiere decir que no hay mas entrada por lo que se desencadena la salida. Al no ser una señal no se puede capturar por lo que para manejarla el copiloto nos sugiere que comprobemos si readline devuelve null, lo que indica que se ha alcanzado el final de entrada del archivo,(esto no me queda claro).

**CTRL+'\'** seria la señal **SIGQUIT** no se puede lanzar desde el teclado directamente pero es equivalente a hacer un kill PID al proceso y machacarlo. Hay que ignorar la señal SIGQUIT.
