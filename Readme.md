Este repositorio permite resolver ecuaciones diferenciales parciales hiperbólicas dada la forma de la ecuación, unas condiciones iniciales y unas condiciones de frontera. Adicionalmente permite graficar las soluciones y compararlas con una solución exacta en caso de que se provea.

# Dependencias
Para la compilación se utiliza el flag -I/usr/include/python3.9 -lpython3.9. Este flag es necesario para la graficación ya que se hace uso indirectamente de python3 para graficar. Si tiene una versión diferente de Python, reemplace por su versión. Si aún cambiando la versión hay un problema de compilación que indica que no se pudo encontrar Python.h debe instalar el paquete python3.x-dev (reemplace x por su versión). Tenga en cuenta que debe tener instalados los módulos de Numpy y matplotlib. 

# Compilación
Para compilar uno de los archivos de ejemplo que se encuentra en la carpeta examples ingrese al makefile y asigne a la variable EXAMPLE_FILE el nombre del archivo a compilar (sin extensión). Luego ejecute make en la terminal.
