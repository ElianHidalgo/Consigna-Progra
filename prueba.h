
#include <stdio.h>
#include <string.h>

// Definición de constantes
#define MaxProduc 100                                // Máximo número de productos permitidos
#define IVA 0.12                                     // Valor del IVA
#define FILE_PATH "C:\\Users\\Pc\\Desktop\\CONSIGNA ENTREGA\\inventario.txt" // Ruta del archivo de inventario

// Estructura que representa un producto en el inventario
struct Producto {
    char nombre[50]; // Nombre del producto
    char codigo[20]; // Código único del producto (ahora es una cadena)
    float precio;    // Precio del producto
    int cantidad;    // Cantidad disponible en inventario
};

// Función para cargar los productos desde el archivo
int cargarProductos(struct Producto productos[]) {
    FILE *file = fopen(FILE_PATH, "r"); // Abrir archivo en modo lectura
    int count = 0;

    if (file == NULL) {
        // Si el archivo no existe, se crea uno vacío
        printf("El archivo no existe. Se creará uno nuevo.\n");
        file = fopen(FILE_PATH, "a"); // Crear archivo nuevo
        if (file == NULL) {
            printf("Error al crear el archivo.\n");
            return 0;
        }
        fclose(file);
        return 0; // Retorna 0 porque el archivo se ha creado vacío
    }

    // Leer productos del archivo hasta el final
    while (fscanf(file, "%49s %19s %f %d\n", productos[count].nombre, productos[count].codigo, &productos[count].precio, &productos[count].cantidad) == 4) {
        count++;
    }

    fclose(file); // Cerrar archivo
    return count; // Retornar la cantidad de productos cargados
}

// Función para guardar los productos en el archivo
void guardarProductos(struct Producto productos[], int count) {
    FILE *file = fopen(FILE_PATH, "a"); // Abrir archivo en modo escritura

    if (file == NULL) {
        printf("Error al guardar los productos.\n");
        return;
    }


    // Escribir todos los productos en el archivo
    for (int i = 0; i < count; i++) {
        fprintf(file, "%-20s %-10d %-10s %-10.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].codigo, productos[i].precio);
    }

    fclose(file); // Cerrar archivo
}

// Función para ingresar un nuevo producto al inventario
void IngresarProducto(struct Producto productos[], int *productoacount) {
    if (*productoacount >= MaxProduc) {
        // Verificar si se ha alcanzado el máximo de productos
        printf("Productos del Inventario completos.\n");
        return;
    }

    // Solicitar los datos del nuevo producto al usuario
    printf("Ingrese el nombre del producto: ");
    fgets(productos[*productoacount].nombre, 50, stdin);
    productos[*productoacount].nombre[strcspn(productos[*productoacount].nombre, "\n")] = 0; // Eliminar salto de línea

    printf("Ingrese la cantidad del producto: ");
    scanf("%d", &productos[*productoacount].cantidad);
    getchar();

    printf("Ingrese el código del producto (alfanumérico): ");
    fgets(productos[*productoacount].codigo, 20, stdin);
    productos[*productoacount].codigo[strcspn(productos[*productoacount].codigo, "\n")] = 0; // Eliminar salto de línea

    printf("Ingrese el precio del producto: ");
    scanf("%f", &productos[*productoacount].precio);
    getchar();

    // Incrementar el contador de productos y guardar en el archivo
    (*productoacount)++;
    guardarProductos(productos, *productoacount);
    printf("Producto ingresado correctamente.\n");
}

// Función para editar un producto en el inventario
void editarProducto(struct Producto productos[], int productoacount) {
    char nombre[50];
    printf("Ingrese el nombre del producto que desea editar: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // Eliminar salto de línea

    // Buscar el producto por su nombre
    for (int i = 0; i < productoacount; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            int cambio;
            printf("¿Qué desea cambiar del producto?\n");
            printf("1. Nombre\n2. Cantidad\n3. Precio\n4. Código\n");
            scanf("%d", &cambio);
            getchar();

            // Cambiar el atributo seleccionado
            switch (cambio) {
            case 1:
                printf("Nuevo nombre: ");
                fgets(productos[i].nombre, 50, stdin);
                productos[i].nombre[strcspn(productos[i].nombre, "\n")] = 0;
                break;
            case 2:
                printf("Nueva cantidad: ");
                scanf("%d", &productos[i].cantidad);
                getchar();
                break;
            case 3:
                printf("Nuevo precio: ");
                scanf("%f", &productos[i].precio);
                getchar();
                break;
            case 4:
                printf("Nuevo código (alfanumérico): ");
                fgets(productos[i].codigo, 20, stdin);
                productos[i].codigo[strcspn(productos[i].codigo, "\n")] = 0;
                break;
            default:
                printf("Opción no válida.\n");
                break;
            }

            guardarProductos(productos, productoacount);
            printf("Producto actualizado.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

// Función para eliminar un producto del inventario
void EliminarProducto(struct Producto productos[], int *productoacount) {
    char nombre[50];
    printf("Ingrese el nombre del producto a eliminar: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = 0; // Eliminar salto de línea

    // Buscar y eliminar el producto
    for (int i = 0; i < *productoacount; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            for (int j = i; j < *productoacount - 1; j++) {
                productos[j] = productos[j + 1];
            }

            (*productoacount)--;
            guardarProductos(productos, *productoacount);
            printf("Producto eliminado.\n");
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

// Función para listar todos los productos en el inventario
void listaProductos(struct Producto productos[], int productoacount) {
    if (productoacount == 0) {
        // Verificar si no hay productos
        printf("No hay productos en el inventario.\n");
        return;
    }

    // Imprimir encabezado de la tabla
    printf("\n%-20s %-10s %-10s %-10s\n", "Nombre", "Cantidad", "Código", "Precio");
    printf("--------------------------------------------------\n");

    // Imprimir los productos en el inventario
    for (int i = 0; i < productoacount; i++) {
        printf("%-20s %-10d %-10s %-10.2f\n", productos[i].nombre, productos[i].cantidad, productos[i].codigo, productos[i].precio);
    }
}