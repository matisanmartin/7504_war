 * Siguen apareciendo referencias a soldados dentro de la lista. Recuerden que no está bueno acoplar esas dos cosas que nada tienen que ver una con la otra.
 
 Mail enviado a lucio consultando, esperando respuesta.

  * El código de estrategia.hpp se hace difícil de leer... sería bueno separar la declaración de las clases de la implementación de los métodos, en primer lugar. Y además de eso, ver si se puede modularizar los métodos largos en términos de otros métodos más chicos y con nombres más declarativos.
  
  Por ahora lo único que hice fue dividirlo en distintos archivos para que no queden todas las clases juntas. Se puede mejorar.
 
 * Me está tirando segmentation fault cuando lo ejecuto con -n (sin -o, o poniendo -o después de -n)
 
 	Consultado también por mail. Por lo pronto "solucione" el segmentation fault muy brutamente con un if, pero la solucion no es del todo correcta... si el -o no esta vaya y pase, si el -o esta, va a mandar el nombre igual por cout. El problema esta, creo yo, en que oss todavia no esta asignado a la hora de usar opt_name en los casos que dice lucio, ya que el opt_output que se ocupa de asignar oss, se ejecuta despues. Todavia no se me ocurre como hacerlo andar sin modificar algo del cmdline (cosa que no tengo ganas ni entiendo mucho) o sin hacer una especie de parseo casero inicial, buscando el -o y asignar oss.
 
 * También parece haber código repetido entre los Ejecutar de las distintas estrategias. Se podría evitar sacando factor común, subiendo esto a la superclase y luego redefiniendo la parte variable de código en cada subclase (se entiende?)
 
 	Si, se entiende, pero ni ganas ahora.
 
 * En la línea de lo anterior, la lista sigue exponiendo hacia afuera el concepto de nodo. No está bien hacer pública la implementación. 
 
 	Esto supongo que esta relacionado con armar el iterador.
