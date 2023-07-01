***Link de GitHub***
https://github.com/EduardoPerezMir/Proyecto-SuperStore.git

***Ejecución***
Para ejecutar nuestro proyecto, primero compilamos el codigo, para que se cree un archivo ejecutable que es el programa. Al ejecutarlo se mostrara un menu con opciones y se debe escribir por teclado el numero que señale esa opcion y por consiguiente el enter.

***Aclaraciones***
1. Para una mejor visualización ejecute el programa con la consola en pantalla completa.
2. Evitar hacer uso de caracteres extraños, simbolos y cadenas que superen una cantidad de 30 caracteres al ser ingresador por teclado.
3. Como administrador, evite añadir elementos a la base de datos con la letra 'ñ' o letras con algún tipo de acento gráfico.
4. Al ingresar opciones que muestren toda la oferta ya sea de productos, supermercados o categorias y no hay elementos en estas, se mostrara un mensaje señalando esto.
5. Para las opciones 3 y 4 del menú del usuario (opciones de búsqueda), en caso de no haber coincidencias, se mostrará un mensaje que lo indique.
6. Para la opciones 5 y 6 del menú del usuario (opciones de búsqueda), en caso de no haber coincidencias en la búsqueda de supermercados o categorías, se mostrará un mensaje que lo indique. En caso de no haber productos asociados al supermercado o categoría encontrada, se mostrará un mensaje que lo indique.
7. Para la base de datos de productos:
    - Se debe ingresar un producto, con primera letra mayúscula. En caso de que el producto sea de más de una palabra, únicamente, se debe aplicar mayúscula a la primera letra de la primera palabra.
8. Para la base de datos de supermercados:
   - Se debe ingresar un supermercado, con primera letra mayúscula. En caso de que el supermercado sea de más de una palabra, se debe usar mayúscula para cada primera letra de cada palabra.
9. Para la base de datos de categorias:
    - Se debe ingresar una categoría, con primera letra mayúscula. En caso de que la categoría sea de más de una palabra, únicamente, se debe aplicar mayúscula a la primera letra de la primera palabra.
10. El final de las bases de datos debe ser de un salto de línea o ninguno (NO más de un salto de línea).

***Menú principal***
El menú principal contiene las siguientes opciones :
1. Armar canasta con productos que desea comprar.
  - La aplicación desplegará un submenu donde podra elegir entre 4 opciones (revisar menú de armado de canasta).
    
2. Mostrar toda la oferta de productos.
  - La aplicación mostrará toda la oferta de productos a nivel nacional.
    
3. Buscar productos por su nombre.
  - La aplicacion muestra todos los productos disponibles a nivel nacional en los diferentes supermercados, seguido a esto debe ingresar el nombre del producto que se encuentre en la lista mostrada.
    
4. Buscar productos según su precio.
  - El usuario debe ingresar como input dos precios, uno menor y uno mayor. De esta manera, la aplicación mostrará todos los productos en ese rango de precios.
    
5. Buscar productos según supermercados.
  - La aplicacion muestra todos los supermercados a nivel nacional, seguido a esto debe ingresar el nombre del supermercado que desea ver toda su oferta de productos.
    
6. Buscar productos según su categoría.
  - La aplicación muestra todas las categorías de productos a nivel nacional, seguido a esto, el usuario debe ingresar el nombre de la categoría que desea ver todos sus productos asociados.
    
7. Inicio de sesión como administrador.
  - Para iniciar sesion se espera que el usuario ingrese el rut y contraseña, podrá ingresar el 0 para salir.
    
0. Salir.
  - La aplicación se cierra.


***Menú de armado de canasta***
El menú de armado de canasta contiene las siguientes opciones:
1. Ver todos los productos de la canasta.
  - Se mostrara todos los productos que han sido agregados a la canasta.

2. Agregar productos a la canasta.
  - La aplicación muestra la oferta de productos a nivel nacional y se pide al usuario que ingrese la información del producto a agregar.
    
3. Eliminar productos de la canasta.
  - La aplicacion muestra todos los productos que se encuentran en la canasta, se espera que el usuario ingrese el nombre del producto a eliminar.
    
0. Salir.
  - El usuario ingresa 0 para salir al menú principal (menú del usuario).


***Menú del administrador***
El menú del administrador contiene las siguientes opciones:
1. Agregar productos.
  - El usuario debe ingresar la información de un producto que desea ingresar a la base de datos.
    
2. Agregar supermercados.
  - El usuario debe ingresar el supermercado que desea ingresar a la base de datos de supermercados.
    
3. Agregar categoría.
  - El usuario debe ingresar la categoría que desea ingresar a la base de datos de categorias.
    
4. Quitar productos.
  - El usuario debe ingresar el nombre del producto que desea eliminar de la base de datos de productos.
    
0. Salir.
  - El usuario ingresa 0 para salir al menú principal (menú del usuario).
