//Pool Alexander Delgado Palacio y Julian Andres Lizalda Aristizabal
#include <iostream>
#include <cstdlib>

using namespace std;

struct Cliente {
    int id;
    char nombre[30];
    int edad;
    char genero;
    char motivo[50];
    Cliente* sig;
};

Cliente* cab = NULL, *clienteActual = NULL, *ultimoCliente = NULL;
Cliente* top = NULL; // Esto es para la pila del historial
int contadorID = 1;
int contadorM = 0, contadorF = 0;

void agregarCliente() {
    clienteActual = (Cliente*)malloc(sizeof(Cliente));
    if (clienteActual == NULL) {
        cout << "Error, no se pudo asignar memoria." << endl;
        return;
    }

    clienteActual->id = contadorID++;
    cin.ignore();
    cout << "Ingrese el Nombre Completo del Cliente: ";
    cin.getline(clienteActual->nombre, 30);
    cout << "Ingrese la Edad del Cliente: ";
    cin >> clienteActual->edad;
    cout << "Ingrese el Género del Cliente (M/F): ";
    cin >> clienteActual->genero;
    cin.ignore(); //Esto es para limpiar el buffer
    cout << "Ingrese el Motivo de la Llamada: ";
    cin.getline(clienteActual->motivo, 50);

    
    if ((contadorM > contadorF + 3 && clienteActual->genero == 'M') ||
        (contadorF > contadorM + 3 && clienteActual->genero == 'F')) {
        cout << "No te puedo atender " << clienteActual->nombre 
             << " porque ocacionas un desbalance de género mayor a 4." << endl;
        free(clienteActual); // Liberar memoria si no se puede agregar
        return;
    }

    // Actualizamos los contadores de género
    if (clienteActual->genero == 'M') contadorM++;
    else if (clienteActual->genero == 'F') contadorF++;

    clienteActual->sig = NULL;
    if (cab == NULL) {
        cab = clienteActual;
    } else {
        ultimoCliente = cab;
        while (ultimoCliente->sig != NULL) {
            ultimoCliente = ultimoCliente->sig;
        }
        ultimoCliente->sig = clienteActual;
    }
}

void atenderCliente() {
    if (cab == NULL) {
        cout << "No hay clientes en espera." << endl;
        return;
    }
    
    while (cab != NULL && cab->edad < 18) {
        cout << "Cliente " << cab->nombre << " no puedes ser atendido porque eres menor de edad." << endl;
        cab = cab->sig;
    }

    if (cab == NULL) {
        cout << "No hay más clientes para atender." << endl;
        return;
    }

    clienteActual = cab;
    cab = cab->sig;

    //Actualizamos los contadores de generos una vez atendido, decrementa la cantidad de generos añadidos
    if (clienteActual->genero == 'M') contadorM--;
    else if (clienteActual->genero == 'F') contadorF--;

    cout << "Cliente " << clienteActual->nombre << " ha sido atendido."  << endl;
    
    //Mandamos al cliente atendido al historial de atenciones
    clienteActual->sig = top;
    top = clienteActual;
}

void mostrarClientes() {
    if (cab == NULL) {
        cout << "No hay clientes en espera." << endl;
        return;
    }

    clienteActual = cab;
    while (clienteActual != NULL) {
        cout << "ID: " << clienteActual->id << " | Nombre: " << clienteActual->nombre
            << " | Edad: " << clienteActual->edad << " | Género: " << clienteActual->genero
            << " | Motivo: " << clienteActual->motivo << endl;
        clienteActual = clienteActual->sig;
    }
}

void mostrarHistorial() {
    if (top == NULL) {
        cout << "No hay historial de atención." << endl;
        return;
    }

    clienteActual = top;
    while (clienteActual != NULL) {
        cout << " ID: " << clienteActual->id << " | Nombre: " << clienteActual->nombre
            << " | Edad: " << clienteActual->edad << " | Género: " << clienteActual->genero
            << " | Motivo: " << clienteActual->motivo << endl;
        clienteActual = clienteActual->sig;
    }
}

int contarClientes() {
    int count = 0;
    clienteActual = cab;
    while (clienteActual != NULL) {
        count++;
        clienteActual = clienteActual->sig;
    }
    return count;
}

void deshacerAtencion() {
    if (top == NULL) {
        cout << "No hay clientes atendidos por deshacer." << endl;
        return;
    }

    clienteActual = top;
    top = top->sig;

    // Aseguramos que el cliente se agregue al final de la cola.
    if (cab == NULL) { // Si la cola está vacía, el cliente es el primero en la cola.
        cab = clienteActual;
        clienteActual->sig = NULL;
    } else {
        ultimoCliente = cab;
        while (ultimoCliente->sig != NULL) { // Buscamos el último cliente de la cola.
            ultimoCliente = ultimoCliente->sig;
        }
        ultimoCliente->sig = clienteActual; // Lo agregamos al final.
        clienteActual->sig = NULL; // El nuevo cliente debe ser el último, por lo tanto, su siguiente será NULL.
    }

    // Actualizamos los contadores de género.
    if (clienteActual->genero == 'M') contadorM++;
    else if (clienteActual->genero == 'F') contadorF++;

    cout << "Se ha deshecho la última atención. Cliente: " << clienteActual->nombre << " ha sido devuelto a la cola." << endl;
}


int main() {
    int opc;

    do {
        cout << "\n==== MENÚ ATENCIÓN AL CLIENTE ====\n";
        cout << "1. Añadir cliente a la fila\n";
        cout << "2. Ver clientes en espera\n";
        cout << "3. Cantidad de clientes en espera\n";
        cout << "4. Atender al siguiente cliente\n";
        cout << "5. Ver el historial de atenciones\n";
        cout << "6. Deshacer atención del ultimo cliente\n";
        cout << "7. Salir del programa\n";
        cout << "Seleccione una opción: ";
        cin >> opc;

        switch (opc) {
            case 1: agregarCliente(); 
            break;
            case 2: mostrarClientes(); 
            break;
            case 3: cout << "La cantidad de clientes en espera es: " << contarClientes() << endl; 
            break;
            case 4: atenderCliente(); 
            break;
            case 5: mostrarHistorial(); 
            break;
            case 6: deshacerAtencion(); 
            break;
            case 7: cout << "Saliendo del programa..." << endl; 
            break; 
            default: cout << "Opción no válida. Intente de nuevo." << endl; 
            break;
        }
    } while (opc != 7);

return 0;
}
