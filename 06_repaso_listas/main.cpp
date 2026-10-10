#include <iostream>
#include <list>
#include <array>
#include <string>
#include <format>
#include <algorithm>
#include <iterator> // Para std::advance

// ============================================================================
// SEMANA 6: LISTAS DOBLEMENTE ENLAZADAS (std::list)
// ============================================================================

// ============================================================================
// LECCION 17: Arquitectura de Memoria de std::list (Nodos Doblemente Enlazados)
// ¿Por que NO tiene operator[] ni .at()?
// ============================================================================
void leccion_17_arquitectura_nodos() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 17: Arquitectura de Nodos de std::list" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * COMPARATIVA DEFINITIVA DE MEMORIA:
     *
     * 1. std::vector: [ 10 | 20 | 30 | 40 ] (1 solo bloque contiguo)
     * 2. std::deque:  Mapa de punteros -> Varios bloques contiguos
     * 3. std::list:   NADA ES CONTIGUO. Cada elemento vive en su propio "Nodo"
     *                 en una direccion de memoria completamente aleatoria del Heap:
     *
     *   Nodo 1:                 Nodo 2:                 Nodo 3:
     *   [ prev = nullptr ]      [ prev = ptr_nodo1 ]    [ prev = ptr_nodo2 ]
     *   [ dato = 10      ] <--> [ dato = 20        ] <--> [ dato = 30        ]
     *   [ next = ptr_nodo2 ]    [ next = ptr_nodo3 ]    [ next = nullptr   ]
     *
     * CONSECUENCIAS FIJAS DE EXAMEN:
     * 1. NO TIENE operator[] ni .at():
     *    Como los nodos estan regados por la RAM, el procesador NO puede calcular
     *    la direccion del indice 5 sumando un offset. Tienes que viajar de nodo en nodo.
     * 2. NO TIENE .data(): No existe memoria contigua.
     * 3. NO TIENE .capacity() ni .reserve(): Cada nodo se pide individualmente con new.
     * 4. SOBRECARGA DE MEMORIA: Cada nodo gasta el dato + 2 punteros (16 bytes extra en 64 bits).
     */

    std::list<int> l1{10, 20, 30};
    std::cout << "l1.size():  " << l1.size() << std::endl;
    std::cout << "l1.front(): " << l1.front() << std::endl;
    std::cout << "l1.back():  " << l1.back() << std::endl;

    // l1[0];    // ERROR DE COMPILACION (No existe [])
    // l1.at(0); // ERROR DE COMPILACION (No existe .at)
}

// ============================================================================
// LECCION 18: Navegacion e Iteradores Bidireccionales (std::advance)
// ============================================================================
void leccion_18_navegacion_advance() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 18: Iteradores Bidireccionales y std::advance" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::list<int> l1{10, 20, 30, 40, 50, 60, 70};

    auto it = l1.begin();
    // it + 3; // ERROR DE COMPILACION: Los iteradores de list son Bidirectional,
               // no permiten saltos directos (RandomAccess).

    // Para moverte N posiciones se usa std::advance(it, n):
    // Salta paso a paso (O(N)) siguiendo los punteros 'next':
    std::advance(it, 3); // Nos movemos 3 posiciones adelante
    std::cout << "Elemento tras std::advance(it, 3): " << *it << " (El 40)" << std::endl;

    // Tambien puede retroceder porque es doblemente enlazada:
    std::advance(it, -1);
    std::cout << "Elemento tras std::advance(it, -1): " << *it << " (Retrocedio al 30)" << std::endl;
}

// ============================================================================
// LECCION 19: Insercion O(1), remove() y remove_if() propios de lista
// ============================================================================
void leccion_19_modificadores_propios() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 19: insert O(1), list::remove y list::remove_if" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::list<int> l1{20, 30, 40, 50, 60};

    // 1. Insercion en el medio con iterador: ¡ES O(1) REAL!
    // En vector moveria memoria contigua; en list solo reengancha 2 punteros.
    auto it = l1.begin();
    std::advance(it, 2); // Estamos en el 40
    l1.insert(it, 999);  // Inserta antes del 40 en O(1)
    
    std::cout << "Tras insertar 999: ";
    for (int x : l1) std::cout << x << " ";
    std::cout << std::endl;

    // 2. list::remove(valor): METODO MIEMBRO PROPIO
    // ¡OJO DE EXAMEN! En vector se usa std::erase o Erase-Remove.
    // En std::list NO necesitas eso: l1.remove(valor) busca los nodos, los destruye
    // de la RAM y reengancha los vecinos automaticamente.
    l1.remove(999);
    std::cout << "Tras l1.remove(999): ";
    for (int x : l1) std::cout << x << " ";
    std::cout << std::endl;

    // 3. list::remove_if(predicado_lambda):
    // Borra bajo condicion (ej: todos los multiplos de 20):
    l1.remove_if([](int x) { return x % 20 == 0; });
    std::cout << "Tras remove_if (multiplos de 20): ";
    for (int x : l1) std::cout << x << " ";
    std::cout << std::endl;
}

// ============================================================================
// LECCION 20: La magia de splice() (Transferencia de Nodos O(1))
// ============================================================================
void leccion_20_splice_magia() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 20: splice() (Mover nodos en O(1) sin copiar)" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * splice() es exclusivo de std::list.
     * Toma los nodos de l2 y los "injerta" dentro de l1.
     * CERO copias de memoria en el Heap: solo desengancha los punteros de l2
     * y los engancha en l1. ¡Costo O(1)!
     */
    std::list<std::string> l1{"Ene", "Feb", "Mar", "Abr", "Sep", "Oct"};
    std::list<std::string> l2{"May", "Jun", "Jul", "Ago"};

    // Queremos meter l2 justo antes de "Sep":
    auto it = l1.begin();
    std::advance(it, 4); // Apunta a "Sep"

    l1.splice(it, l2); // l2 transfiere todos sus nodos a l1

    std::cout << "l1 tras splice: ";
    for (const auto& s : l1) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "l2 tras splice (QUEDA VACIA!): size = " << l2.size() << std::endl;
}

// ============================================================================
// LECCION 21: Operaciones Propias: sort(), merge() y reverse()
// ============================================================================
void leccion_21_sort_merge_reverse() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 21: list::sort(), list::merge() y list::reverse()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ¿Por que no se usa std::sort(l1.begin(), l1.end())?
     * std::sort requiere acceso aleatorio (acceder al medio en O(1)).
     * Como las listas no tienen eso, std::sort DA ERROR DE COMPILACION.
     * Por eso std::list tiene su propio metodo miembro: l1.sort();
     */
    std::list<int> l1{50, 10, 30};
    std::list<int> l2{40, 20, 60};

    // 1. sort() propio de la lista:
    l1.sort();
    l2.sort();
    std::cout << "l1 ordenada: ";
    for (int x : l1) std::cout << x << " ";
    std::cout << "\nl2 ordenada: ";
    for (int x : l2) std::cout << x << " ";
    std::cout << std::endl;

    // 2. merge(): Fusiona dos listas QUE YA DEBEN ESTAR ORDENADAS
    // Une los nodos en orden y deja l2 vacia:
    l1.merge(l2);
    std::cout << "Tras l1.merge(l2): ";
    for (int x : l1) std::cout << x << " ";
    std::cout << "\nl2 tras merge queda vacia: size = " << l2.size() << std::endl;

    // 3. reverse(): Invierte la lista reorientando punteros:
    l1.reverse();
    std::cout << "Tras l1.reverse(): ";
    for (int x : l1) std::cout << x << " ";
    std::cout << std::endl;
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "   REPASO AEDA - SEMANA 6: STD::LIST STL       " << std::endl;
    std::cout << "===============================================" << std::endl;

    leccion_17_arquitectura_nodos();
    leccion_18_navegacion_advance();
    leccion_19_modificadores_propios();
    leccion_20_splice_magia();
    leccion_21_sort_merge_reverse();

    return 0;
}
