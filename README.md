
# Compilador para configuración de VMs

Este proyecto consiste en la implementación de un compilador que permite, a través de un determinado lenguaje, generar un archivo de configuración para levantar una máquina virtual (VM). Es decir, se busca resolver el problema de lidiar con complejos archivos de configuración de máquinas virtuales en XML. Esto es, a través de un lenguaje sencillo, amigable y natural al lenguaje humano.

## Tecnologías utilizadas

Construido con Flex y Bison.

## Lenguaje YSY

Las siguiente es la sintaxis del lenguaje: 

```
vm1 = create vm “[nombre de la maquina virtual]” {
    cores [cantidad de cores]
    ram [cant de RAM][G/M] (gigabytes o megabytes)
    disk [tamaño del disco][G/M] (gigabytes o megabytes)
    iso [path al archivo] 
    so [windows10/ubuntu2204/otros]
    bios [legacy/UEFI]
    net-controller {
      type [nat, bridge, macvtop]
      ip “[X.X.X.X]”
      mac “[MAC address]”
}
```

Aclaraciones: 

* Parámetros obligatorios: nombre, iso/so.
* Luego de create vm, las líneas de código sucesivas pueden estar en cualquier orden.
* Solo uno de las siguiente palabras pueden estar simultáneamente: iso o so.
* Al escribir la opción se tomará el link de descarga guardado para cada palabra clave y con el script de Bash bajará el archivo .iso con wget para configurar la máquina virtual.
* La extensión de los archivos del lenguaje, por convención, será .ysy



## Requerimientos

Para construir el compilador, se requieren las siguientes dependencias:

* [Bison v3.8.2](https://www.gnu.org/software/bison/)
* [CMake v3.24.1](https://cmake.org/)
* [Flex v2.6.4](https://github.com/westes/flex)
* [GCC v11.1.0](https://gcc.gnu.org/)
* [Make v4.3](https://www.gnu.org/software/make/)
* [Libvirt 8.0.0](https://libvirt.org/)
* [Qemo 7.2.3](https://www.qemu.org/)

Aclaración: este compilador funciona solamente para Linux, pensado para usarse con libvirt y el Virtual Machine Manager.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos:

```bash
user@machine:path/ $ chmod u+x --recursive script
user@machine:path/ $ script/build.sh
```

## Compilación

Para compilar un programa, primero cree un archivo denominado `program.ysy` (o el nombre que desee), con la sintaxis apropiada del lenguaje ysy (ver informe y casos de testeo para más información).

Luego, ejecute el compilador desde el directorio raíz del proyecto, o desde cualquier otro lugar indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
user@machine:path/ $ script/start.sh program.ysy
```

Debería obtener los archivos de configuración XML de las VMs en la carpeta `output` dentro de la raíz del proyecto.

## Ejecución

Para levantar una VM en base a su configuración, ejecute los siguientes comandos:

```bash
user@machine:path/ $ sudo virsh create config1.xml
user@machine:path/ $ qemu-img create -f qcow2 Win1k.qcow2 10G
```

## Testing de compilación

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
