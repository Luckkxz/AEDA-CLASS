#include <iostream>
#include <deque>
#include <vector>
#include <array>
#include <string>
#include <format>
#include <algorithm>
#include <ranges>

// ============================================================================
// SEMANA 5: DOUBLE ENDED QUEUE (std::deque) - DEQUES STL
// ============================================================================

// ============================================================================
// LECCION 13: Arquitectura Interna de Memoria (Fragmented Contiguous Blocks)
// ¿Por que std::deque NO es un solo bloque contiguo como vector?
// ============================================================================
void leccion_13_arquitectura_memoria() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 13: Arquitectura Interna de Memoria del Deque" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * VECTOR (Memoria Contigua Unica):
     * [ Bloque Unico Gigante en Heap: 1 | 2 | 3 | 4 | 5 ]
     * - Si metes algo al frente: O(N) (debe mover todos a la derecha).
     * - Si se llena: debe pedir otro bloque mas grande y copiar todo.
     *
     * DEQUE (Fragmented Contiguous Blocks - Bloques Fragmentados):
     * Tiene un "MAPA CENTRAL" (Array de Punteros) que apunta a varios "CHUNKS" (bloques fijos):
     *
     *   Mapa Central:
     *   [ ptr_bloque_0 ] ------> [ Bloque 0: casillas fijas... ]
     *   [ ptr_bloque_1 ] ------> [ Bloque 1: casillas fijas... ]
     *   [ ptr_bloque_2 ] ------> [ Bloque 2: casillas fijas... ]
     *
     * CONSECUENCIAS DIRECTAS DE EXAMEN:
     * 1. Insercion y borrado en AMBOS extremos (frente y final) en O(1) amortizado.
     * 2. NO tiene .capacity() ni .reserve() (¡PREGUNTA FIJA!).
     *    ¿Por que? Porque no necesita reservar un solo buffer contiguo; asigna
     *    bloques nuevos segun se requiera.
     * 3. SI tiene .shrink_to_fit() (libera bloques que quedaron vacios).
     * 4. Acceso por indice dq[i] es ligeramente mas lento que vector por doble indireccion:
     *    (1ro busca el bloque en el mapa central, 2do busca el elemento en el bloque).
     */

    std::deque<int> dq{10, 20, 30, 40, 50};

    std::cout << "Tamano dq.size(): " << dq.size() << std::endl;
    std::cout << "dq.empty():       " << (dq.empty() ? "SI" : "NO") << std::endl;
    std::cout << "dq.max_size():    " << dq.max_size() << std::endl;

    // NO EXISTEN:
    // dq.capacity(); // ERROR DE COMPILACION
    // dq.reserve(100); // ERROR DE COMPILACION

    // SI EXISTE:
    dq.shrink_to_fit();
    std::cout << "shrink_to_fit() ejecutado correctamente (libera bloques no usados)." << std::endl;
}

// ============================================================================
// LECCION 14: Operaciones en Ambos Extremos (push_front, push_back, pop_*)
// ============================================================================
void leccion_14_operaciones_duales() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 14: Operaciones Duales O(1) en Ambos Extremos" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::deque<int> dq;

    // 1. Inserciones al final: push_back y emplace_back
    dq.push_back(50);
    dq.push_back(60);
    dq.emplace_back(70); // in-place
    std::cout << "Tras push_back/emplace_back (50, 60, 70): ";
    for (int x : dq) std::cout << x << " ";
    std::cout << std::endl;

    // 2. Inserciones al frente: push_front y emplace_front (¡O(1) instantaneo!)
    // En std::vector esto requeriria O(N) movimientos; en deque es O(1)
    dq.push_front(40);
    dq.push_front(30);
    dq.emplace_front(20);
    std::cout << "Tras push_front/emplace_front (40, 30, 20): ";
    for (int x : dq) std::cout << x << " ";
    std::cout << std::endl;

    // 3. Inspeccionar extremos:
    std::cout << "Primer elemento dq.front(): " << dq.front() << std::endl;
    std::cout << "Ultimo elemento dq.back():   " << dq.back() << std::endl;

    // 4. Eliminar por ambos extremos:
    dq.pop_front(); // Quita el 20
    dq.pop_back();  // Quita el 70
    std::cout << "Tras pop_front() y pop_back(): ";
    for (int x : dq) std::cout << x << " ";
    std::cout << std::endl;
}

// ============================================================================
// LECCION 15: Modificadores y Algoritmos en Deque
// ============================================================================
void leccion_15_modificadores_y_algoritmos() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 15: insert, erase, sort descendente y std::erase" << std::endl;
    std::cout << "==================================================" << std::endl;

    // Meses (como hizo tu profesor en deque_example_3):
    std::deque<std::string> meses{"Ene", "Feb", "Mar", "Abr", "May", "Jun"};
    std::array<std::string, 3> extra{"Jul", "Ago", "Sep"};

    // Insertar un rango de iteradores al final:
    meses.insert(meses.end(), extra.begin(), extra.end());
    std::cout << "Meses tras insertar array al final: ";
    for (const auto& m : meses) std::cout << m << " ";
    std::cout << std::endl;

    // Ordenar de Menor a Mayor (Ascendente):
    std::ranges::sort(meses);
    std::cout << "Orden alfabetico ascendente:  ";
    for (const auto& m : meses) std::cout << m << " ";
    std::cout << std::endl;

    // Ordenar de Mayor a Menor (Descendente con std::greater):
    std::ranges::sort(meses, std::greater<>());
    std::cout << "Orden alfabetico descendente: ";
    for (const auto& m : meses) std::cout << m << " ";
    std::cout << std::endl;

    // Borrado moderno en C++20 con std::erase y std::erase_if:
    std::deque<int> numeros{10, -1, 20, -1, 30, -1, 40};
    std::cout << "\nNumeros con valores invalidos (-1): ";
    for (int n : numeros) std::cout << n << " ";
    std::cout << std::endl;

    // std::erase: borra todos los que coincidan con -1:
    auto eliminados = std::erase(numeros, -1);
    std::cout << "Eliminados con std::erase: " << eliminados << std::endl;
    std::cout << "Numeros limpios: ";
    for (int n : numeros) std::cout << n << " ";
    std::cout << std::endl;

    // std::erase_if (C++20): borra segun una condicion (predicado):
    // Borremos los numeros mayores a 25:
    std::erase_if(numeros, [](int n) { return n > 25; });
    std::cout << "Tras std::erase_if (> 25): ";
    for (int n : numeros) std::cout << n << " ";
    std::cout << std::endl;
}

// ============================================================================
// LECCION 16: Tipos Teoricos y Aplicaciones (PREGUNTAS FIJAS DE TEORIA DE EXAMEN)
// ============================================================================
void leccion_16_tipos_teoricos_y_aplicaciones() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 16: Tipos Teoricos de Deque y Aplicaciones" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * En la diapositiva 3 y 4 de la Semana 5 tu profesor puso:
     *
     * 1. TIPOS DE DEQUE (Variantes restringidas):
     *    - INPUT-RESTRICTED DEQUE (Restriccion de Entrada):
     *      * Insercion permitida por UN SOLO EXTREMO.
     *      * Eliminacion permitida por AMBOS EXTREMOS.
     *
     *    - OUTPUT-RESTRICTED DEQUE (Restriccion de Salida):
     *      * Insercion permitida por AMBOS EXTREMOS.
     *      * Eliminacion permitida por UN SOLO EXTREMO.
     *
     * 2. APLICACIONES TIPICAS:
     *    - Operaciones Deshacer / Rehacer (Undo / Redo):
     *      Guardas las acciones en un extremo y puedes descartar las mas viejas
     *      por el otro extremo cuando se llena el historial.
     *    - Problemas de Ventana Deslizante (Sliding Window Maximum):
     *      Para mantener los elementos maximos dentro de una ventana fija en tiempo O(N).
     *    - Colas FIFO (First-In, First-Out) y Pilas LIFO (Last-In, First-Out).
     */

    std::cout << "Conceptos teoricos aprendidos: Input/Output restricted, Undo/Redo, Sliding Window." << std::endl;
}

int main() {
    std::cout << "===============================================" << std::endl;
    std::cout << "   REPASO AEDA - SEMANA 5: STD::DEQUE STL      " << std::endl;
    std::cout << "===============================================" << std::endl;

    leccion_13_arquitectura_memoria();
    leccion_14_operaciones_duales();
    leccion_15_modificadores_y_algoritmos();
    leccion_16_tipos_teoricos_y_aplicaciones();

    return 0;
}
