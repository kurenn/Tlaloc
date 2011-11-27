Tláloc - Lenguaje de programación estructurado
====================

Tláloc es un lenguaje de programación estructurado con fines educativos, con léxico generado en Flex, sintáxis en Bison, estructura semántica en C, y máquina virtual en Ruby. 

El objetivo de Tláloc como lenguaje de propósito específico es servir de medio a docentes y profesores para enseñar de manera clara, sencilla y concisa las estructuras básicas de todo lenguaje de programación estructurado mediante una sintaxis estandarizada, basada en palabras genéricas como las típicamente utilizadas en pseudocódigo. Así mismo, ser el punto de partida para estudiantes de nivel primaria y secundaria con la finalidad de comprender la lógica de programación, más que el lenguaje mismo. 

Características del lenguaje
---------------------

Algunas de las ventajas que el lenguaje brindará a los estudiantes serán las siguientes:

* Trasladar el conocimiento adquirido en Tláloc a otros lenguajes de programación.
* Tiempos de desarrollo reducidos por la sintaxis/semántica provista por el lenguaje.
* Código entendible y legible que facilite su propio mantenimiento.
* Compatible por la generación de código interpretado por medio de una máquina virtual. 
* Lenguaje como herramienta de aprendizaje que facilitará el reconocimiento de estructuras básicas en todo lenguaje de programación estructurado.  
* Mismos estatutos a los utilizados en los lenguajes más populares hoy en día en el mundo. 


Los atributos de calidad como producto de software del mismo lenguaje serán:

* Compatibilidad
* Aprendibilidad	
* Readability
* Writability

Elementos disponibles
---------------------

El lenguaje en toda su extensión contará con los siguientes elementos:

* Declaración y asignación de variables locales y globales.
* Generación de expresiones.
* Estatutos de ciclo.
* Estatutos condicionales.
* Estatutos de lectura y escritura.
* Funciones matemáticas aplicadas a expresiones.
* Declaración y llamado de múltiples funciones.
* Llamados recursivos de las mismas funciones. 
* Declaración y manipúlación de Arreglos (unidimensionales y bidimensionales).

Estructura técnica
---------------------

Licencia
---------------------

Compilador y Máquina Virtual para el lenguaje de programación Tláloc, como proyecto académico. 

Copyright (C) 2011 Eduardo López & Abraham Kuri

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/gpl.html.


Manual de usuario
====================

Para empezar a usar Tláloc, es necesario definir un nombre para el programa, en este caso test. Todo programa debe llamar una función main() del tipo void la cual no recibirá parámetros, e insertar el bloque de código a ejecutar.
    
    program test:

        method void main():
            printline("Hello World!").
        end method

    end program


Ejemplo de elementos disponibles
---------------------

Toda instrucción en Tláloc debe tener un inicio y un fin, es decir:

program test:
	.
	.
	.
end program

Así mismo con los métodos y estatutos, ejemplos de los cuales se muestran a continuación:

    method void main():
        ...
        ...
    end method

    if(a < b):
        ...
        ...
    end if

    for 0 to 10 step 1:
        ...
        ...
    end for

    while(a < b):
        ...
        ...
    end while

Lo anterior con la finalidad de concientizar al programador sobre el inicio y el fin de los estatutos.


Tipos de dato
---------------------

Los tipos de dato con los que el programador cuenta son:

* Integer (Entero)
* Decimal (Flotante)
* Boolean (Variable con valor True o False)
* String (Conjunto de carácteres)

Estos tipos se utilizan para la definición de variables, tal y como se muestra a continuación:

    define variable as integer.
    define palabras as string.

También para el tipo de retorno de un método o función como el siguiente ejemplo:

    method string palabra(integer a, string b):
        define variable as integer = a.
        ...
        ...
        return variable.
    end method

Definición y asignación de variables
---------------------

La definición de variables en Tláloc se lleva a cabo de la siguiente manera:
	
    define var as integer.

	Del estatuto anterior se puede fácilmente identificar que con la palabra reservada "define" se indica al programa que será una variable, posteriormente sigue el identificador de la variable y finalmente su tipo de dato.

Para variables globales, solo es cuestión de definirlas después de la inicialización del programa:

    program test:
        define a as integer.
        define var2 as integer.

        method void main():
            ...
            ...

	Para la asignación de una variable en su definición, se haría de la siguiente manera:

	define var as integer = 1.

A diferencia de muchos otros lenguajes de programación que existen actualmente en el mercado, que marcan la terminación de un enunciado con el símbolo “;” en Tláloc se maneja de forma distinta utilizando el punto.

Asimismo se presenta la estructura para la definición de variables dimensionadas:
	
	define arreglo as integer[10].
	define matriz as integer[1,10].

Para las asignaciones de este tipo de variables, es necesario asignar el valor uno a uno;

	arreglo[0] = 0.
	arreglo[1] = 1.
	...
	matriz[0,0] = 0.
	matriz[0,1] = 1.

Es necesario considerar que todas las definiciones deben de hacerse al principio de un bloque. Si se trata de definir variables después de la definición de variables general, el compilador no reconocerá las nuevas variables. 


Definición de estatutos tradicionales
---------------------

#### Estatuto 'if' en Tláloc

	Para definir un estatuto de tipo condicional en Tláloc, se maneja la siguiente sintaxis:
	
	if(a < b):
		printline(“a es menor que b”).
	else:
		printline(“a es mayor que b”).
	end if

	Es necesario marcar el inicio del condicional, con los dos puntos como símbolo y se cierra con las palabras clave end y el estatuto en cuestión en este caso if.

#### Estatuto 'for' en Tláloc

La estructura sintáctica para construir un estatuto for es la siguiente:

	for i = 0 to 9 step 1:
		printline(i).
	end for

En el ejemplo anterior, se sigue el mismo orden para la declaración de estatutos, facilitando así el desarrollo de enunciados dentro del código.

#### Estatuto 'while' en Tláloc

La construcción el estatuto while dentro de Tláloc es la siguiente:

	while(i < 10):
		a = a + 3.
		i = i + 1.
	end while


#### Estatutos de lectura y escritura

Los estatutos de lectura y escritura son sencillos de usar.

Para la impresión en pantalla de valores, es necesario utilizar la función print() o printline(). Print imprimirá lo que reciba como parámetro en una sola línea sin dar el salto de línea típico utilizado en lenguajes de programación.

	define a as integer = 10.
	print(a).

Generando la salida de 10

Para la impresión con salto de línea, se utiliza la función printline:

	printline(a).

Generando la salida de 10\n

Para la escritura se tienen dos funciones para evitar errores en ejecución.

	define a as integer.
	readint(a).

En caso de querer leer un string, se puede utilizar la función readline.
	define palabra as string.
	readline(palabra).


Definición de métodos o funciones en Tláloc
---------------------

Tláloc cuenta con funciones matemáticas predefinidas (abs, log, sin, cos, sqrt), sin embargo y de ser necesario el programador puede definir tantas funciones requiera, que tengan un fin especifico.

	method integer uno(integer a):
		printline(a).
	end method

	method void main():
		uno(5).
	end method

Funciones matemáticas incluidas
---------------------

Como valor agregado al lenguaje, se incluyen funciones matemáticas que pueden recibir una expresión, y devolver su resultado. 

Para el valor absoluto:

	a = abs(-347).

Para el coseno: 

	b = cos(180).

Para el seno:

	c = sin(360).

Para obtener el logaritmo base 10:

	d = log(10).

Para la tangente:

	e = tan(90).

Para obtener la raíz cuadrada:

	f = sqrt(100).

Es necesario tener una variable a la cual se le asignará el valor, ya que cada una de las funciones devuelve una variable del tipo decimal. Los valores que devuelve son en radianes para los casos en los que aplique. 
	

Puntos importantes a considerar
---------------------

1. Tláloc es un lenguaje estructurado de alto nivel, que permite la manipulación de arreglos unidimensionales y bidimensionales.
2. Cuenta con funciones matemáticas predefinidas para facilitar los cálculos.
3. Todas las definiciones deben de hacerse al principio de un bloque



Descripción de los posibles errores
---------------------

Forma de ejecución
---------------------

1. Situarse en la carpeta donde estan los archivos fuente
2. Ejecutar el siguiente comando en la terminal:
    
        make && ./tlaloc < nombre_archivo_a_compilar.txt

3. Una vez que el programa haya compilado correctamente, se debe de correr la maquina virtual a traves del siguiente comando:
    
        $ ruby VMTlaloc/init.ruby

Cabe mencionar que el comando anterior solo funciona para maquinas con arquitectura UNIX y con las dependencias necesarias para la ejecucion, en este caso ruby en la version 1.9.2 y gcc en la version 4.1 o superior.


