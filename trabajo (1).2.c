#include <stdio.h>
#include <string.h>

#define PRODUCTOS 5
#define INV 5
    char nombres[PRODUCTOS][20];
    float tiempo[PRODUCTOS];
    float recursos[PRODUCTOS];
    int demanda[PRODUCTOS];
    int TotalProductos = 0;
    int opc;
    char nomI [INV][50];
    float cantI[INV];
    int Inv = 0;
    float Consumo [PRODUCTOS][INV];
    

void Ingreso_inv (char nomI [][50],float cantI[],int *Inv);
void CalcularInv (char nomI[][50], float cantI[], int Inv);
float tiempoDemanda(int demanda[], float tiempo[], int TotalProductos);
void CantidadRecursos(float recurso[], int demanda[], int TotalProductos,float Consumo[][INV],int Inv, float InR[]);
void validacion_demanda(float tiempo[],  float tiempo_D , int TotalProductos, int demanda[],float Consumo [][INV], char nomI [][50],int Inv,float cantI[]);
void IngresoProductos(char nombres[][20], float tiempo[], float recursos[], int demanda[], int *TotalProductos,char nomI[][50],int Inv,float Consumo[][INV]);
void modificarVariables(char nombres[][20], float tiempo[],float Consumo[][INV], int demanda[], int TotalProductos,char nomI[][50],int Inv);
void EliminarProducto(char nombres[][20], float tiempo[], float Consumo[][INV], int demanda[], int *TotalProductos, char nomI[][50], int Inv);
void mostrarProductos(char nombres[][20], float tiempo[], float Consumo[][INV], int demanda[], int TotalProductos, char nomI[][50], int Inv);


void Ingreso_inv(char nomI[][50], float cantI[], int *Inv) {
    do {
        printf("Cuantos insumos se va a manejar ; max:%d\n", INV);
        scanf("%d", Inv);
        while (getchar() != '\n');
        if (*Inv < 0 || *Inv > INV) {
            printf("Error:max:%d\n", INV);
        }
    } while (*Inv < 0 || *Inv > INV);

    for (int i = 0; i < *Inv; i++) {
        printf("Ingrese el nombre del Insumo ,%d\n", i + 1);
        scanf("%49s", nomI[i]);
        while (getchar() != '\n');

        do {
            printf("Ingrese la cantidad de ese insumo\n");
            scanf("%f", &cantI[i]);
            while (getchar() != '\n');
            if (cantI[i] < 0) {
                printf("Error,numeros mayores a 0\n");
            }
        } while (cantI[i] < 0);
    }

    printf("\n\n#\t\tInsumo\t\tCantidad\n");
    for (int i = 0; i < *Inv; i++) {
        printf("%d\t\t%-19s\t%.2f\n", i + 1, nomI[i], cantI[i]);
    }
}
void CalcularInv (char nomI[][50], float cantI[], int Inv){
char buscar [20];
float Agregado=0;
int encontrado=-1;

    if (Inv == 0)
    {
       printf("No se ha registrado ningun recurso\n");
       return ;
    }
    
    printf("/////////INVENTARIO DISPONIBLE//////// \n");
    printf("\n #\t\tNombres\t\tStock\n");
    for (int j = 0; j < Inv; j++)
    {
       printf("%d\t\t%s\t\t%.2f\n",j+1,nomI[j],cantI[j]);
    }
    
    printf("Que recurso quieres reponer?\n");
    scanf("%19s",buscar);
    while(getchar()!='\n');

    for (int i = 0; i < Inv; i++)
    {
        if (strcmp(buscar,nomI[i])==0)
        {
            encontrado= i;
            break;
        }
    }
    
    if (encontrado == -1)
    {
        printf("NO EXISTE EN EL INVENTARIO\n");
        return;
    }

    do
    {
        printf("Cuanto agregas a :%s",nomI[encontrado]);
        scanf("%f",&Agregado);
        
        if (Agregado <= 0)
        {
            printf("Error : Valor mayor que cero\n");
            
        }
    } while (Agregado <= 0);
    while (getchar() != '\n');

    cantI[encontrado]+= Agregado;
    printf(" %s ahora tiene %.2f unidades.\n", nomI[encontrado], cantI[encontrado]);
}

void IngresoProductos(char nombres[][20], float tiempo[], float recursos[], int demanda[], int *TotalProductos,char nomI[][50],int Inv,float Consumo[][INV]) {
    if (*TotalProductos >= PRODUCTOS) {
        printf("\n Error: Limite de productos alcanzado (Maximo %d).\n", PRODUCTOS);
        return;
    }

    int i = *TotalProductos;
    printf("\n--- INGRESAR PRODUCTO [%d/%d] ---\n", i + 1, PRODUCTOS);
    printf("Ingrese el nombre del producto (sin espacios): ");
    scanf("%19s", nombres[i]);
    printf("Ingrese la demanda (cantidad): ");
    scanf("%d", &demanda[i]);
    printf("Ingrese el tiempo en fabricarse una unidad (horas): ");
    scanf("%f", &tiempo[i]);
    
    for (int j = 0; j < Inv; j++)
    {
       do
       {
        printf("Ingresar el consumo de: %s por unidad",nomI[j]);
        scanf("%f",&Consumo[i][j]);
        if (Consumo[i][j] < 0 )
        {
            printf("No numeros negagtivos");
        }
        
       } while (Consumo[i][j] < 0 );
       
    }
    

    while (getchar() != '\n');

    (*TotalProductos)++;
    
}

float tiempoDemanda(int demanda[], float tiempo[], int TotalProductos) {
    float TiempoTacumulado = 0.0;
    for (int i = 0; i < TotalProductos; i++) {
        float TotalTiempo = demanda[i] * tiempo[i];
        TiempoTacumulado += TotalTiempo;
    }
    return TiempoTacumulado;
}

void CantidadRecursos(float recurso[], int demanda[], int TotalProductos,float Consumo[][INV],int Inv, float InR[]) {
    
    for (int j = 0; j < Inv; j++)
    {
      InR[j] = 0.0;    
    }
    
    for (int i = 0; i < TotalProductos; i++) {
       for (int j = 0; j < Inv; j++)
       {
        
       InR[j] += Consumo[i][j] * demanda[i];
       }
    }
}

void validacion_demanda(float tiempo[],  float tiempo_D , int TotalProductos, int demanda[],float Consumo [][INV], char nomI [][50],int Inv,float cantI[]) {
    float tiempo_R = tiempoDemanda(demanda, tiempo, TotalProductos);
    float InR[INV];
    CantidadRecursos(recursos, demanda, TotalProductos, Consumo, Inv, InR);
    
    int Icheck = 1;

    printf("Tiempo requerido: %.2f hrs | Tiempo disponible: %.2f hrs\n", tiempo_R, tiempo_D);
    if (tiempo_R > tiempo_D ) {
        printf("Falta tiempo: %.2f horas\n", tiempo_R - tiempo_D);
    }
    
    printf("Validacion Insumos \n");
    for (int j = 0; j < Inv ; j++)
    {
        printf("%s = requiere: %.2f ; Disponible=%.2f\n",nomI[j],InR[j],cantI[j]);
        if (InR[j] > cantI[j])
        {
            Icheck =0;
            printf("Faltan : %.2f de %s\n",InR[j] -cantI[j] ,nomI[j] );
        }
    }
    
if (tiempo_R <= tiempo_D && Icheck )
{
    for (int j = 0; j < Inv; j++)
    {
        cantI[j] -= InR[j];
    }
    printf("Se cumple la demanda \n");
}else{

    printf("No se cumple la demanda\n");
}


    
    


    
}

void mostrarProductos(char nombres[][20], float tiempo[], float Consumo[][INV], int demanda[], int TotalProductos, char nomI[][50], int Inv) {
    if (TotalProductos == 0) {
        printf("\n[!] No hay productos registrados.\n");
        return;
    }

    printf("\n#\tProducto\tTiempo/U\tDemanda\t\tConsumo por unidad\n");
    for (int i = 0; i < TotalProductos; i++) {
        printf("%d\t%-12s\t%.2f\t\t%d\t\t", i + 1, nombres[i], tiempo[i], demanda[i]);
        for (int j = 0; j < Inv; j++) {
            printf("%s: %.2f  ", nomI[j], Consumo[i][j]);
        }
        printf("\n");
    }
}
void modificarVariables(char nombres[][20], float tiempo[],float Consumo[][INV], int demanda[], int TotalProductos,char nomI[][50],int Inv) {
    if (TotalProductos == 0) {
        printf("\n[!] No hay productos registrados para modificar.\n");
        return;
    }

    mostrarProductos(nombres, tiempo,Consumo, demanda, TotalProductos,nomI,Inv);

    char buscar[20];
    int pos = -1;
    

    printf("\nIngrese el nombre exacto del producto a modificar: ");
    scanf("%19s", buscar);
    while (getchar() != '\n');

    for (int i = 0; i < TotalProductos; i++) {
        if (strcmp(buscar, nombres[i]) == 0) {
           pos = i;
            
            break;
        }
    }

    if (pos != -1) {
        printf("\nProducto encontrado. Ingrese los nuevos datos:\n");
        printf("Nuevo nombre: ");
        scanf("%19s", nombres[pos]);
        printf("Nuevo tiempo por unidad: ");
        scanf("%f", &tiempo[pos]);
        printf("Nueva demanda: ");
        scanf("%d", &demanda[pos]);
        for (int j = 0; j < Inv; j++)
            {
                do
                {
                    printf("Consumo de %s, por unidad",nomI[j]);
                    scanf("%f",&Consumo[pos][j]);
                    if (Consumo [pos][j] < 0)
                    {
                        printf("Ingrese un valor positivo (Puede ser cero)\n");
                    }
                    
                } while (Consumo [pos][j] < 0);
            }
        while (getchar() != '\n');
        printf("\n Datos del producto actualizados correctamente.\n");
    } else {
        printf("\n Producto no encontrado.\n");
    }
}

void EliminarProducto(char nombres[][20], float tiempo[], float Consumo[][INV], int demanda[], int *TotalProductos, char nomI[][50], int Inv) {
    if (*TotalProductos == 0) {
        printf("\n[!] No hay productos registrados para eliminar.\n");
        return;
    }

    mostrarProductos(nombres, tiempo,Consumo, demanda, *TotalProductos,nomI,Inv);
    char buscar[20];
    int pos = -1;

    printf("\nIngrese el nombre del producto que desea eliminar: ");
    scanf("%19s", buscar);
    while (getchar() != '\n');

    for (int i = 0; i < *TotalProductos; i++) {
        if (strcmp(buscar, nombres[i]) == 0) {
           pos= i;
            break;
        }
    }

    if (pos != -1) {
        for (int i = pos; i < *TotalProductos - 1; i++) {
            strcpy(nombres[i], nombres[i + 1]);
            tiempo[i] = tiempo[i + 1];
            demanda[i] = demanda[i + 1];
            for (int j = 0; j < Inv; j++)
            {
                Consumo[i][j]= Consumo[i + 1][j]; 
            }
            


        }
        (*TotalProductos)--;
        printf("\n Producto eliminado correctamente.\n");
    } else {
        printf("\n Producto no encontrado.\n");
    }
}




int main(int argc, char const *argv[]) {
    do {
        printf("\n========================================\n");
        printf("      SISTEMA DE GESTION - FABRICA      \n");
        printf("========================================\n");
        printf("1. Ingresar inventario inicial\n");
        printf("2. Reabastecer / actualizar inventario\n");
        printf("3. Ingresar nuevo producto\n");
        printf("4. Mostrar productos registrados\n");
        printf("5. Calcular tiempo total de fabricacion requerido\n");
        printf("6. Calcular recursos necesarios totales\n");
        printf("7. Verificar si es posible cumplir con la demanda\n");
        printf("8. Editar datos de un producto\n");
        printf("9. Eliminar un producto\n");
        printf("10. Salir\n");
        printf("----------------------------------------\n");
        printf("Escoja una opcion (1-10): ");

        if (scanf("%d", &opc) != 1) {
            printf("Error: Ingrese un numero valido.\n");
            while (getchar() != '\n');
            opc = 0;
            continue;
        }
        while (getchar() != '\n');

        switch (opc) {
            case 1:
                Ingreso_inv(nomI, cantI, &Inv);
                break;

            case 2:
                CalcularInv(nomI, cantI, Inv);
                break;

            case 3:
                if (Inv == 0) {
                    printf("\n Primero ingrese el inventario .\n");
                } else {
                    IngresoProductos(nombres, tiempo, recursos, demanda, &TotalProductos, nomI, Inv, Consumo);
                }
                break;

            case 4:
                mostrarProductos(nombres, tiempo, Consumo, demanda, TotalProductos, nomI, Inv);
                break;

            case 5:
                if (TotalProductos == 0) {
                    printf("\n No hay productos registrados aun.\n");
                } else {
                    float totalT = tiempoDemanda(demanda, tiempo, TotalProductos);
                    printf("\n--> Tiempo total de fabricacion requerido: %.2f horas\n", totalT);
                }
                break;

            case 6:
                if (TotalProductos == 0) {
                    printf("\n No hay productos registrados aun.\n");
                } else {
                    float InR[INV];
                    CantidadRecursos(recursos, demanda, TotalProductos, Consumo, Inv, InR);
                    printf("\nRecursos requeridos para la demanda:\n");
                    for (int j = 0; j < Inv; j++) {
                        printf("# %s = requiere %.2f ; Disponible %.2f\n", nomI[j], InR[j], cantI[j]);
                    }
                }
                break;

            case 7:
                if (TotalProductos == 0) {
                    printf("\n[!] No hay productos registrados aun.\n");
                } else {
                    float tiempo_D;
                    printf("\nIngrese el tiempo limite disponible en la fabrica (horas): ");
                    scanf("%f", &tiempo_D);
                    while (getchar() != '\n');

                    validacion_demanda(tiempo, tiempo_D, TotalProductos, demanda, Consumo, nomI, Inv, cantI);
                }
                break;

            case 8:
                modificarVariables(nombres, tiempo, Consumo, demanda, TotalProductos, nomI, Inv);
                break;

            case 9:
                EliminarProducto(nombres, tiempo, Consumo, demanda, &TotalProductos, nomI, Inv);
                break;

            case 10:
                printf("\nSaliendo del sistema. ¡Hasta luego!\n");
                return 0;

            default:
                printf("\n[X] Opcion invalida, intente otra vez.\n");
                break;
        }

        if (opc != 10) {
            int seguir = 0;
            printf("\n¿Desea realizar otra operacion? (Si: 1 / No: 0): ");
            scanf("%d", &seguir);
            while (getchar() != '\n');
            if (seguir != 1) {
                printf("\nSaliendo del sistema. ¡Hasta luego!\n");
                break;
            }
        }

    } while (1);

    return 0;
}


