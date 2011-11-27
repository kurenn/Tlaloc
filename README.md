Tláloc - Lenguaje de programación estructurado
====================

Forma de ejecución
---------------------

1. Situarse en la carpeta donde estan los archivos fuente
2. Ejecutar el siguiente comando en la terminal:
    
        make && ./tlaloc < nombre_archivo_a_probar.txt

3. Una vez que el programa alla compilado correctamente, se debe de correr la maquina virtual a traves del siguiente comando:
    
        $ ruby VMTlaloc/init.ruby

Cabe mencionar que el comando anterior solo funciona para maquinas con arquitectura UNIX y con las dependencias necesarias para la ejecucion, en este caso ruby en la version 1.9.2 y gcc en la version 4.1 o superior


Licencia
---------------------

Compilador y Máquina Virtual para el lenguaje de programación Tláloc, como proyecto académico. 

Copyright (C) 2011 Eduardo López & Abraham Kuri

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see (http://www.gnu.org/licenses/gpl.html).
