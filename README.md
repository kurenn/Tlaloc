Tláloc - Lenguaje de programación estructurado
====================

Forma de ejecución
---------------------

* Situarse en la carpeta donde estan los archivos fuente
* Ejecutar el siguiente comando en la terminal
    make && ./tlaloc < nombre_archivo_a_probar.txt
* Una vez que el programa alla compilado correctamente, se debe de correr la maquina virtual a traves del siguiente comando:
    $ ruby VMTlaloc/init.ruby

Cabe mencionar que el comando anterior solo funciona para maquinas con arquitectura UNIX y con las dependencias necesarias para la ejecucion, en este caso ruby en la version 1.9.2 y gcc en la version 4.1 o superior
