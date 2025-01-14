#include "prueba.h" // Incluir el archivo de encabezado necesario

int main() {

    const char *filename = FILE_PATH;
    FILE*file = fopen(FILE_PATH, "r");


    if (file != NULL)
    {
        fclose(file);
    } else {
        fclose(file);
        
        file= fopen(filename, "a");
        if (file == NULL)
        {
            perror("Error al crear el archivo");
            return 1;
        }
        fprintf(file, "%-20s %-10s %-10s %-10s\n", "Nombre", "Cantidad", "Código", "Precio");
        printf("El archivo '%s' ha sido creado.\n", filename);
        fclose(file);
        


    }

    struct Producto productos[MaxProduc]; 
    int productoacount = cargarProductos(productos); // Cargar productos desde el archivo
    int eleccion;

    do {
        // Menú principal para seleccionar acciones
        printf("----------------------------\n");
        printf("¿Qué acción desea realizar sobre los productos?\n");
        printf("1. Ingresar\n2. Editar\n3. Eliminar\n4. Listado de Productos\n5. Salir\n");
        printf("Acción: ");
        while (1) {
          if (scanf("%d", &eleccion) == 1) {
            getchar();
              break; // Si la lectura fue exitosa, salimos del bucle
          } else {
              // Si no fue un número entero, mostramos un mensaje de error y limpiamos el buffer
              printf("No es un numero de la eleccion: ");
              while (getchar() != '\n'); // Limpiar el buffer de entrada
          }
        }


        if (eleccion<0 || eleccion >4
        // Realizar la acción correspondiente según la elección
        switch (eleccion) {
            case 1:
                IngresarProducto(productos, &productoacount);
                break;
            case 2:
                editarProducto(productos, productoacount);
                break;
            case 3:
                EliminarProducto(productos, &productoacount);
                break;
            case 4:
                listaProductos(productos, productoacount);
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Acción no válida. Intente nuevamente.\n");
        }
    } while (eleccion != 5); // Repetir hasta que el usuario elija salir

    return 0;
}
