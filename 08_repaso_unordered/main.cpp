#include <iostream>
#include <unordered_set>
#include <set>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <format>
#include <algorithm>
#include <cctype>
#include "../01_Buildingblocks/helpers.h"

// ============================================================================
// SEMANA 10 / AEDA: DE ARBOLES BALANCEADOS A CONTENEDORES HASH EN C++ STL
// REPASO INTEGRAL: ARBOLES, BST, AVL, RED-BLACK Y std::unordered_set
// ============================================================================

// Helper para convertir strings a mayusculas de forma 100% segura (evita UB con signed chars)
static std::string safe_to_upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return s;
}

// ============================================================================
// LECCION 36: Jerarquia de Arboles, Propiedad BST y Degradacion
// (TEORIA FUNDAMENTAL DE LA PPT DE CLASE - SEMANA 10)
// ============================================================================
void leccion_36_teoria_arboles_y_bst() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 36: Jerarquia de Arboles y Degradacion BST" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * CONCEPTOS CLAVE DE ARBOLES (PPT DIAPOSITIVA 2 Y 3):
     * - NODE: Cada elemento en un arbol.
     * - ROOT: Nodo raiz, el nodo superior del arbol.
     * - PARENT / CHILD: Nodo padre y nodos hijos derivados.
     * - LEAF (Hoja): Nodo sin hijos.
     * - EDGE (Arista): Conexion dirigida entre dos nodos.
     * - HEIGHT (Altura, h): Longitud del camino mas largo desde la raiz a una hoja.
     * - DEPTH (Profundidad): Distancia de un nodo desde la raiz (numero de aristas).
     * - LEVEL (Nivel): Distancia desde la raiz. Nivel = Profundidad + 1 (o Profundidad si raiz=0).
     * - SUBTREE (Subarbol): Arbol formado por un nodo y todos sus descendientes.
     *
     * ARBOL BINARIO DE BUSQUEDA (BST - Binary Search Tree):
     * Cada nodo tiene a lo sumo dos hijos (izquierdo y derecho) ordenados:
     *      Para todo nodo con clave 'k':
     *      ∀ x ∈ T_izquierdo: x < k
     *      ∀ y ∈ T_derecho:   y > k
     *
     * VENTAJA TEORICA:
     * En un arbol perfectamente lleno:
     *      n = 2^(h+1) - 1   ===>   h = O(log n)
     *      T_search(n) = O(h) = O(log n)
     *
     * ¡PREGUNTA FIJA DE EXAMEN!: ¿PUEDE UN BST PERDER SU EFICIENCIA?
     * SI. Si insertamos datos ya ordenados (ej: 1, 2, 3, 4, 5, ..., n):
     *      (1)
     *        \
     *        (2)
     *          \
     *          (3)
     *            \
     *            (4)  ===> ¡EL ARBOL DEGENERA EN UNA LISTA ENLAZADA!
     * Altura resultante: h = n - 1
     * Complejidad de busqueda en arbol degenerado: T_search(n) = O(n) (LINEAL).
     */

    std::cout << "Terminologia de Arboles:" << std::endl;
    std::cout << "  - Altura (h): Camino mas largo desde la raiz hasta una hoja." << std::endl;
    std::cout << "  - Nivel = Profundidad + 1" << std::endl;
    std::cout << "  - Busqueda en BST depende de la altura: T(n) = O(h)" << std::endl;
    std::cout << "  - Arbol Perfectamente Lleno: n = 2^(h+1) - 1  -> h = O(log n)" << std::endl;
    std::cout << "  - Arbol Degenerado (datos ordenados): h = n - 1 -> Busqueda degenera a O(n)!" << std::endl;
}

// ============================================================================
// LECCION 37: Arboles Balanceados: Familia AVL y Rotaciones vs Red-Black
// (PPT DIAPOSITIVAS 6 A 14)
// ============================================================================
void leccion_37_arboles_balanceados_avl_rotaciones() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 37: Arboles Balanceados, AVL y Rotaciones" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ¡TRAMPA CONCEPTUAL DE EXAMEN! (PPT Diapositiva 7):
     * "¿AVL es sinonimo de arbol de busqueda equilibrada?"
     * RESPUESTA: ¡NO! AVL ⊂ Arboles de Busqueda Equilibrados.
     * - AVL es una estrategia concreta que controla la ALTURA estricta (|BF| <= 1).
     * - Red-Black (Rojo-Negro) es OTRA estrategia que equilibra mediante PROPIEDADES DE COLOR.
     *
     * CONDICION DE BALANCE AVL:
     * Factor de Balance: BF(v) = h_L - h_R   (altura subarbol izq - altura subarbol der)
     * Condicion AVL: |BF(v)| <= 1  ===>  BF(v) ∈ {-1, 0, +1}
     *
     * TIPOS DE DESEQUILIBRIO Y SUS SOLUCIONES (PPT Diapositiva 11 y 12):
     * 1. Caso LL (Izquierda -> Izquierda):
     *    Crecimiento en el hijo izquierdo del hijo izquierdo.
     *    SOLUCION: ROTACION SIMPLE DERECHA (Rotate-Right).
     *
     * 2. Caso RR (Derecha -> Derecha):
     *    Crecimiento en el hijo derecho del hijo derecho.
     *    SOLUCION: ROTACION SIMPLE IZQUIERDA (Rotate-Left).
     *
     * 3. Caso LR (Izquierda -> Derecha):
     *    SOLUCION: DOBLE ROTACION (Rotate-Left en hijo, Rotate-Right en nodo).
     *
     * 4. Caso RL (Derecha -> Izquierda):
     *    SOLUCION: DOBLE ROTACION (Rotate-Right en hijo, Rotate-Left en nodo).
     *
     * PROPIEDAD FUNDAMENTAL DE LAS ROTACIONES:
     * ¡La rotacion cambia la forma/estructura del arbol pero PRESERVA EL ORDEN IN-ORDER!
     *
     * ¿QUE IMPLEMENTA LA BIBLIOTECA ESTANDAR C++ (STL)? (PPT Diapositiva 13):
     * Las estructuras asociativas ordenadas (std::set, std::map, std::multiset, std::multimap)
     * PREDOMINANTEMENTE UTILIZAN ARBOLES ROJO-NEGRO (Red-Black Trees).
     * Razon: El arbol Rojo-Negro tolera un arbol ligeramente menos estricto (altura <= 2*log(n+1)),
     * pero a cambio realiza MUCHAS MENOS ROTACIONES en inserciones y borrados frecuentes.
     */

    std::cout << "Resumen de Rotaciones AVL:" << std::endl;
    std::cout << "  - Caso LL (Crecimiento Izquierda-Izquierda) -> Solucion: Rotacion Derecha" << std::endl;
    std::cout << "  - Caso RR (Crecimiento Derecha-Derecha)     -> Solucion: Rotacion Izquierda" << std::endl;
    std::cout << "  - Caso LR (Crecimiento Izquierda-Derecha)   -> Solucion: Doble Rotacion (Izq luego Der)" << std::endl;
    std::cout << "  - Caso RL (Crecimiento Derecha-Izquierda)   -> Solucion: Doble Rotacion (Der luego Izq)" << std::endl;
    std::cout << "\nComplejidad AVL: Busqueda O(log n), Insercion O(log n), Eliminacion O(log n)" << std::endl;
    std::cout << "Implementacion STL C++: Predominantemente Red-Black Tree para std::set y std::map." << std::endl;
}

// ============================================================================
// LECCION 38: De Arboles a Tablas Hash: Arquitectura de std::unordered_set
// (EL SALTO CUANTICO DE O(log n) A O(1) AMORTIZADO)
// ============================================================================
void leccion_38_de_arboles_a_hash() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 38: De O(log n) a O(1): Tablas Hash" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * MOTIVACION:
     * Aunque un arbol Rojo-Negro ofrece O(log n) garantizado, para millones de elementos
     * O(log n) requiere 20-30 comparaciones y saltos de punteros en memoria dispersa.
     * ¿Podemos buscar en O(1)?
     * ¡SI! Utilizando una TABLA HASH (Hash Table).
     *
     * ARQUITECTURA INTERNA DE std::unordered_set:
     * 1. Vector de Cubos (Buckets Array):
     *    Un arreglo continuo de punteros a cabezas de listas.
     * 2. Hash Function (std::hash<Key>):
     *    Convierte cualquier tipo de clave a un entero 'size_t':
     *    indice_cubo = hash(clave) % numero_de_cubos
     * 3. Colisiones y Encadenamiento Separado (Separate Chaining):
     *    Si dos claves distintas tienen el mismo indice de cubo, se encadenan
     *    en una lista simplemente enlazada dentro de ese bucket.
     *
     *       [Bucket 0] -> nullptr
     *       [Bucket 1] -> ["Mar Negro"] -> ["Mar Rojo"] -> nullptr  (Colision!)
     *       [Bucket 2] -> ["Mar Baltico"] -> nullptr
     *       [Bucket 3] -> nullptr
     *
     * REQUISITOS DE LOS TIPOS:
     * - Para std::set<T>: Se requiere que T soporte operador '<' (std::less<T>).
     * - Para std::unordered_set<T>: Se requiere `std::hash<T>` Y `operator==`.
     *   (¡NO NECESITA operator<!).
     */

    std::hash<std::string> hasher;
    std::string s1 = "Mar Rojo";
    std::string s2 = "Mar Negro";

    std::cout << "Demostracion de Funcion Hash:" << std::endl;
    std::cout << std::format("  hash('{}') = {}", s1, hasher(s1)) << std::endl;
    std::cout << std::format("  hash('{}') = {}", s2, hasher(s2)) << std::endl;

    size_t num_buckets = 11;
    std::cout << std::format("  Indice para '{}' con 11 buckets: {}", s1, hasher(s1) % num_buckets) << std::endl;
    std::cout << std::format("  Indice para '{}' con 11 buckets: {}", s2, hasher(s2) % num_buckets) << std::endl;
}

// ============================================================================
// LECCION 39: Inspeccion Interna de Buckets e Iteradores Locales
// (ANALISIS PROFUNDO DEL CODIGO DE CLASE DE BUCKETS)
// ============================================================================
void leccion_39_inspeccion_buckets() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 39: Inspeccion de Buckets e Iteradores Locales" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * API DE INSPECCION DE CUBOS (BUCKETS):
     * - us.bucket_count(): Numero total de buckets asignados actualmente en la tabla.
     * - us.bucket_size(i): Numero de elementos que cayeron en el bucket 'i'.
     * - us.bucket(clave): Indice del bucket donde reside (o residiria) la clave.
     * - Iteradores Locales:
     *   us.begin(i) y us.end(i) permiten recorrer UNICAMENTE los elementos dentro
     *   del bucket 'i'. Esto permite visualizar las colisiones reales.
     */

    std::unordered_set<std::string> mares{
        "Golfo de Alaska",
        "Mar del Caribe",
        "Mar Negro",
        "Mar Rojo",
        "Golfo de Tailandia",
        "Mar de Bering",
        "Mar Baltico",
        "Mar Mediterraneo"
    };

    std::cout << std::format("Total elementos (size): {}", mares.size()) << std::endl;
    std::cout << std::format("Total cubos (bucket_count): {}", mares.bucket_count()) << std::endl;
    std::cout << std::format("Factor de carga actual: {:.4f}", mares.load_factor()) << std::endl;

    std::cout << "\nRecorrido de buckets no vacios mediante iteradores locales:" << std::endl;
    size_t colisiones = 0;
    for (size_t b = 0; b < mares.bucket_count(); ++b) {
        size_t b_size = mares.bucket_size(b);
        if (b_size > 0) {
            std::cout << std::format("  Bucket {:2d} ({} elem): ", b, b_size);
            for (auto it = mares.begin(b); it != mares.end(b); ++it) {
                std::cout << std::format("'{}' ", *it);
            }
            std::cout << std::endl;
            if (b_size > 1) {
                colisiones += (b_size - 1);
            }
        }
    }
    std::cout << std::format("Colisiones detectadas: {}", colisiones) << std::endl;
}

// ============================================================================
// LECCION 40: Factor de Carga, max_load_factor y Rehashing
// (¡PREGUNTA FIJA DE RENDIMIENTO EN EXAMEN!)
// ============================================================================
void leccion_40_factor_carga_y_rehashing() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 40: Factor de Carga (Load Factor) y Rehashing" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ¿QUE ES EL FACTOR DE CARGA (LOAD FACTOR)?
     *         load_factor = size() / bucket_count()
     * Representa el promedio de elementos por bucket.
     *
     * UMBRAL: max_load_factor()
     * Por defecto en C++ es 1.0f.
     * Si load_factor > max_load_factor(), el contenedor ejecuta un REHASH AUTOMATICO:
     * 1. Aloca un nuevo arreglo de buckets (usualmente el doble o siguiente numero primo).
     * 2. Recalcula el bucket para CADA uno de los 'N' elementos existentes.
     * 3. Mueve los nodos al nuevo arreglo.
     * ¡ESTA OPERACION DE REHASHING CUESTA O(N)!
     *
     * OPTIMIZACION CRITICA: reserve(n)
     * Si sabemos que insertaremos 10,000 elementos, llamamos:
     *      us.reserve(10000);
     * Esto aloca suficientes buckets de antemano para que el load_factor nunca supere
     * max_load_factor, ¡EVITANDO TODOS LOS REHASHINGS INTERMEDIOS!
     */

    std::unordered_set<int> tabla;
    std::cout << "Estado Inicial de una tabla vacia:" << std::endl;
    std::cout << std::format("  bucket_count: {}, load_factor: {:.2f}, max_load_factor: {:.2f}",
                             tabla.bucket_count(), tabla.load_factor(), tabla.max_load_factor()) << std::endl;

    std::cout << "\nInsertando elementos y observando el rehash automatico:" << std::endl;
    size_t prev_buckets = tabla.bucket_count();
    for (int i = 1; i <= 25; ++i) {
        tabla.insert(i);
        if (tabla.bucket_count() != prev_buckets) {
            std::cout << std::format("  -> ¡REHASH disparado al insertar {}! Buckets: {} -> {} (size: {}, load_factor: {:.2f})",
                                     i, prev_buckets, tabla.bucket_count(), tabla.size(), tabla.load_factor()) << std::endl;
            prev_buckets = tabla.bucket_count();
        }
    }

    std::cout << "\nUso de reserve() para pre-alocar buckets:" << std::endl;
    std::unordered_set<int> tabla_optimizada;
    tabla_optimizada.reserve(1000);
    std::cout << std::format("  Tras reserve(1000): bucket_count pre-alocado = {}", tabla_optimizada.bucket_count()) << std::endl;
}

// ============================================================================
// LECCION 41: Operaciones Avanzadas: extract() + Node Handles y merge()
// (LA UNICA FORMA LEGAL DE MODIFICAR UN ELEMENTO EN UN SET EN C++17/20)
// ============================================================================
void leccion_41_extract_node_handles_merge() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 41: extract(), Node Handles y merge()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ¡PROBLEMA FUNDAMENTAL EN std::set y std::unordered_set!:
     * Los elementos son SIEMPRE CONSTANTES (`const Key`).
     * `auto it = us.find("Mar Rojo"); *it = "MAR ROJO";` // ¡ERROR DE COMPILACION!
     * Porque si cambiaras el valor directamente en el set, romperias el bucket asignado
     * (o el orden del arbol en std::set).
     *
     * LA SOLUCION MODERNA: NODE HANDLES Y extract() (C++17):
     * 1. `auto nh = us.extract(clave);`
     *    Desvincula el nodo de la tabla hash SIN DESTRUIRLO y lo entrega como un
     *    objeto "Node Handle" que es PROPIETARIO del nodo.
     * 2. Si `!nh.empty()`, el valor queda mutable:
     *    `nh.value() = safe_to_upper(nh.value());`
     * 3. Reinsertamos el nodo:
     *    `us.insert(std::move(nh));`
     *    La tabla hash recalcula el hash del nuevo valor y lo coloca en el bucket correcto.
     * ¡VENTAJA CLAVE!: CERO alocaciones y CERO desasignaciones de memoria heap.
     *
     * FUSION EFICIENTE CON merge():
     * `s2.merge(s1);`
     * Mueve los nodos de s1 a s2 re-enlazando punteros.
     * Si un elemento de s1 YA EXISTE en s2 (duplicado), se queda en s1.
     */

    std::unordered_set<std::string> us1{"Mar Rojo", "Mar Negro", "Mar Baltico"};
    std::unordered_set<std::string> us2{"Mar Caspio", "Mar Rojo"}; // "Mar Rojo" es duplicado

    std::cout << "Antes de merge():" << std::endl;
    std::cout << std::format("  us1.size() = {}, us2.size() = {}", us1.size(), us2.size()) << std::endl;

    // merge(): Transfiere sin copiar
    us2.merge(us1);
    std::cout << "Despues de us2.merge(us1):" << std::endl;
    std::cout << std::format("  us2.size() = {} (absorbio Mar Negro y Mar Baltico)", us2.size()) << std::endl;
    std::cout << std::format("  us1.size() = {} (retuvo 'Mar Rojo' por ser duplicado)", us1.size()) << std::endl;

    // extract() y mutacion de elemento:
    std::cout << "\nModificacion segura mediante extract() + Node Handle:" << std::endl;
    std::string objetivo = "Mar Baltico";

    auto nh = us2.extract(objetivo);
    if (!nh.empty()) {
        std::cout << std::format("  Nodo extraido con exito: '{}'", nh.value()) << std::endl;
        nh.value() = safe_to_upper(nh.value()); // Modificamos el valor fuera del set!
        std::cout << std::format("  Valor transformado a: '{}'", nh.value()) << std::endl;
        us2.insert(std::move(nh)); // Reinsertamos con hash recalculado
        std::cout << "  Nodo reinsertado en us2." << std::endl;
    }

    std::cout << "Comprobacion con contains():" << std::endl;
    std::cout << std::format("  us2.contains('Mar Baltico'): {}", us2.contains("Mar Baltico")) << std::endl;
    std::cout << std::format("  us2.contains('MAR BALTICO'): {}", us2.contains("MAR BALTICO")) << std::endl;
}

// ============================================================================
// LECCION 42: Gran Tabla Comparativa de Examen Parcial
// std::set vs std::unordered_set (DIFERENCIAS CRUCIALES DE EXAMEN)
// ============================================================================
void leccion_42_gran_tabla_comparativa() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 42: Matriz Comparativa std::set vs std::unordered_set" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::cout << R"(
+------------------------------------+-----------------------------------+-----------------------------------+
| CRITERIO                           | std::set (Arbol Balanceado)       | std::unordered_set (Tabla Hash)   |
+------------------------------------+-----------------------------------+-----------------------------------+
| Estructura Interna                 | Arbol Rojo-Negro (Red-Black Tree) | Tabla Hash con Separate Chaining  |
| Orden de los Elementos             | SIEMPRE ORDENADO (in-order)       | SIN ORDEN GARANTIZADO             |
| Requisito de Tipo para la Clave    | operator< (o std::less<Key>)      | std::hash<Key> Y operator==       |
| Busqueda Promedio                  | O(log n)                          | O(1)                              |
| Busqueda Peor Caso (¡EXAMEN!)      | O(log n) Estricto Garantizado     | O(n) (si todos colisionan)        |
| Insercion Promedio                 | O(log n)                          | O(1)                              |
| Insercion Peor Caso                | O(log n)                          | O(n) (cuando ocurre rehashing)    |
| Borrado Promedio                   | O(log n)                          | O(1)                              |
| Categoria de Iteradores            | Bidirectional Iterator (--it, ++it| Forward Iterator (solo ++it)      |
| Consultas de Rango (lower_bound)   | SI: lower_bound(), upper_bound()  | NO EXISTEN (sin sentido de orden) |
| Sobrecarga de Memoria              | 3 punteros + color por nodo       | Arreglo buckets + punteros nodo   |
| ¿Cuando Elegirlo?                  | Cuando requieres datos ordenados  | Maxima velocidad de acceso puro   |
+------------------------------------+-----------------------------------+-----------------------------------+
)" << std::endl;

    std::cout << "PREGUNTAS TIPICAS DE EXAMEN PARCIAL:" << std::endl;
    std::cout << "1. ¿Cual es el peor caso teorico de busqueda en std::unordered_set?" << std::endl;
    std::cout << "   -> RESPUESTA: O(n), si la funcion hash es pesima y todos los elementos caen en el mismo bucket." << std::endl;
    std::cout << "2. ¿Puedo llamar a s.lower_bound(x) en un unordered_set?" << std::endl;
    std::cout << "   -> RESPUESTA: NO. Las operaciones de rango no existen en contenedores hash porque no hay orden." << std::endl;
    std::cout << "3. ¿Por que std::unordered_set usa iteradores Forward en lugar de Bidirectional?" << std::endl;
    std::cout << "   -> RESPUESTA: Porque los buckets se implementan como listas simplemente enlazadas (un solo puntero next)." << std::endl;
}

int main() {
    std::cout << "===========================================================" << std::endl;
    std::cout << "   REPASO AEDA - SEMANA 10: ARBOLES BST/AVL Y TABLAS HASH  " << std::endl;
    std::cout << "===========================================================" << std::endl;

    leccion_36_teoria_arboles_y_bst();
    leccion_37_arboles_balanceados_avl_rotaciones();
    leccion_38_de_arboles_a_hash();
    leccion_39_inspeccion_buckets();
    leccion_40_factor_carga_y_rehashing();
    leccion_41_extract_node_handles_merge();
    leccion_42_gran_tabla_comparativa();

    return 0;
}
