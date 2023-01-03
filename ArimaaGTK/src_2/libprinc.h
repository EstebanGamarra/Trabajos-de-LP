#ifndef LIBPRINC_H_
#define LIBPRINC_H_

/*
										░▄▀▄▀▀▀▀▄▀▄░░░░░░░░░
										░█░░░░░░░░▀▄░░░░░░▄░
										█░░▀░░▀░░░░░▀▄▄░░█░█
										█░▄░█▀░▄░░░░░░░▀▀░░█
										█░░▀▀▀▀░░░░░░░░░░░░█
										█░░░░░░░░░░░░░░░░░░█
										█░░░░░░░░░░░░░░░░░░█
										░█░░▄▄░░▄▄▄▄░░▄▄░░█░
										░█░▄▀█░▄▀░░█░▄▀█░▄▀░
										░░▀░░░▀░░░░░▀░░░▀░░░			Programador:Esteban Gamarra
▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂
El perro de la buena suerte explicará las funciones declaradas aquí para saber sus funciones en el programa.
▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂▂▃▅▆▇▇▆▅▃▂
 */
void selectablero();
/* Se encarga de seleccionar el tipo de tablero y transferirlo a la matriz que se usará como nuestro tablero
 * principal que se usa para el resto del juego, originalmente las piezas deberían de poder elegirse a gusto pero
 * como se presentó un error, la estructura de esta función fue comentada, ya que el error podría ser un problema
 * del compilador o algun otro inconveniente que escapa del control del programador.
 * Ingresando A,B,C,D o E(opción removida y algoritmo comentado para su análisis, este sería el que permitiría
 * elegir donde poner las piezas donde uno desee), se decide el tablero a usar en el resto de la partida.
 */
void elegirjugador(int elegiremp);
/* Ingresando por teclado 1, 2 o 3, se pude elegir si empieza el jugador, la cpu o al azar mediante el comando rand()
 * el cual debe ser inicializado mediante srand (time(NULL)); una sola vez, ya que necesita un valor inicial para
 * poder utilizarse posteriormente el comando.
 */
void posjugador();
/* posjugador es básicamente la misma que "reordenarme()" sólo que con uso de variables iref,jref en imov,jmov
 * más la condición que pide que la ficha seleccionada sea la correcta, es decir, una ficha aliada (para ello el uso
 * del while en comparación a reordenarme). El switch case es para un cambio de valores en las variables (mediante el código
 * ASCII), para que estos puedan ser utilizados en las operaciones con el tablero.
 * Cabe también destacar que una vez hecha la subrutina iref y jref permanecerán costantes por el resto de la jugada o hasta
 * que se cometa un error y pida la terminal realizar todos los comandos nuevamente, incluyendo necesariamente una nueva
 * ficha a seleccionar para su posterior movimiento/empuje/estire.
 */
void poscpu();
/* la misma idea que posjugador solo que éste está determinado medinte la funcion rand(), la función se repite hasta que
 * halla conseguido una pieza válida. No espera el teclado y se ejecuta de forma automática una vez que es el turno de la
 * cpu (una de las condiciones para que se ejecute el programa continuamente en el main)
 */
void movjugador();
/* IMPORTANTE: FUNCIÓN QUE INCLUYE A LA FUNCIÓN ENCARGADA DE EMPUJAR/ESTIRAR
 * Esta función se encarga  de preguntar la posición adyascente a la posición ya elegida del jugador.
 * Esto puede ir de dos formas, se escoje un lugar vacío y se hace la jugada o
 * se selecciona una pieza enemiga y se empieza la verificación de la sub-rutina (empujejugador) la cual
 * dependiendo de lo introducido y otros parámetros como si la pieza que se quiere mover tiene menor
 * valor a la pieza que se está utilizando, entre otros.
 * De no cumplirse ninguna de las dos, se vuelve a pedir que se introduzca un comando.
 */
void movcpu();
/* Mismo funcionamiento que movjugador incluyendo también este a empujecpu, sólo que los valores
 * están hecho aleatoriamente hasta que se cumple una jugada válida.
 */
void empujejugador();
/* Donde ocurre el empuje o estire, para el empuje se pide una casilla adyascente a la pieza que se decidió
 * que ya se quiere empujar, para la función de estirar sin embargo, uno debe volver a ingresar por teclado
 * la coordenada de su pieza original que es la que realiza la función de empujar/estirar y respecto a esta,
 * elegir una casilla adyascente vacía para que se pueda realizar la función de estiramiento.
 */
void empujecpu();
/* Misma idea que empujejugador sólo que esta esta aleatoria y debe repetir todos los pasos hasta tener una
 * jugada correcta. Esta función junto en general, con el resto de las funciones de la cpu, son impresas en la terminal
 * constantemente hasta que realiza una jugada correcta, esto es para ver cómo funciona la "inteligencia artificial" y
 * cuántas pruebas hace antes de acertar.
 */
void reordenarme();
/* Función clave, transforma los comandos del tablero a comandos que pueden ser interpretados y transferidos directamente
 * a los índices de la matriz para su posterior uso.
 */
void ordernarcpu();
/* Misma idea que reordernarme pero aplicado a la cpu con rand().
 */
void trampa();
/* Función que se encarga de corroborar si la pieza es comida ya sea enemiga o aliada, se verifica despues de cada movimiento
 * dentro de un mismo turno. Además incluye parámetros para saber si las piezas adyascentes son aliadas para la ficha
 * que se encuentra en la trampa en cuestión. De esta forma si se encuentra rodeada, no puede ser comida.
 */
int ganador();
/* Verifica quien gana según si ya no hay conejos, algún conejo contrario llega al extremo del otro, o una vez terminados los
 * turnos posibles MAX (definidos al comienzo), el que posea la mayor cantidad de piezas en el tablero es el que gana
 */
/*FALTAS:
 * PRIMERO:No se pudo implementar insertar las fichas en el orden que uno desea, esto es comentado dentro del código mismo en el archivo.c
 * SEGUNDO:Así mismo también se presentaron inconvenientes al hacerlo aleatoriamente por medio de rand() (código borrado del archivo.c)
 * debido a que se utilizó un algoritmo similar al ordenamiento por teclado, estos requerían de aún más whiles(Repeticiones) por cada
 * valor randomizado debido a que uno al ingresar por teclado puede equivocarse como máximo una vez, pero la máquina puede equivocarse
 * indefinidamente. Después se quizo llegar a una forma más eficiente del código y termino saturando la memoria por lo que se concluyó quitar.
 * Por lo que al final se utilizó solamente valores predeterminado de tableros.
 * TERCERO:Corroborar si una trampa come una pieza se hizo con valores constantes por lo que los "colores" es decir, jugar desde arriba o abajo
 * no se pudo concluir. Una solución a esto sería preguntar qué color se desea y en base a eso varíar los valores de las fichas  (12 en total)
 * de dos formas, ambas opuestas según el color que se desee. El problema es que esto en la subrutina trampa() requeriría un if y whiles
 * distintos para los caso 1 y caso 2,es decir, dependiendo del color que se escogió, y el algoritmo sería el doble de largo, .
 * Esto se trató de implementar pero generaba errores a los cuales no se le encontraron solución.
 */
#endif
