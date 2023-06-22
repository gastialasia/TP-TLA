
# Compilador para configuración de VMs


Un compilador para crear archivos de configuración de máquinas virtuales a partir de un lenguaje amigable para el usuario. Construido con Flex y Bison.

## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)
* [Libvirt 8.0.0](https://libvirt.org/)

Aclaración: este compilador funciona solamente para Linux, pensado para usarse con libvirt y el Virtual Machine Manager.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos:

```bash
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/ $ script/build.sh
```

## Ejecución

Para compilar un programa, primero cree un archivo denominado `program.ysy` (o el nombre que desee), con la sintaxis apropiada del lenguaje ysy (ver informe y casos de testeo para más información).

Luego, ejecute el compilador desde el directorio raíz del proyecto, o desde cualquier otro lugar indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
user@machine:path/ $ script/start.sh program.ysy
```

Debería obtener los archivos de configuración XML de las VMs en la carpeta `output` dentro de la raíz del proyecto.

## Testing

```bash
user@machine:path/ $ script/test.sh
```

Si desea agregar nuevos casos de uso, deberá crear un archivo por cada uno, que contenga el programa a testear dentro de las carpetas `test/accept` o `test/reject` según corresponda (es decir, si el mismo debe ser aceptado o rechazado por el compilador).

Aclaración: Estos tests solo sirven para verificar la correcta compilación del lenguaje. Los archivos XML generados en output serán los que corresponden a las VMs definidas en el último test en la carpeta `test/accept`.

## Librerías externas utilizadas

 Program: Set Data Structure
 
 Description: Example of a set data structure and operations (union, subset,
 intersection, etc.) implemented in C.  See the Wikipedia article on Sets:
 https://en.wikipedia.org/wiki/Set_(mathematics)

 YouTube Lesson: https://www.youtube.com/watch?v=RVqdK6WAjUI

 Author: Kevin Browne @ https://portfoliocourses.com

 Github: https://github.com/portfoliocourses/c-example-code/blob/main/sets.c