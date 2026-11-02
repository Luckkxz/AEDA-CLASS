#include <iostream>
#include <set>
#include <array>
#include <vector>
#include <string>
#include <format>
#include <algorithm>
#include <numbers>
#include "../01_Buildingblocks/helpers.h"

// ============================================================================
// SEMANA 7: CONTENEDORES ASOCIATIVOS ORDENADOS I - std::set y std::multiset
// ============================================================================

// ============================================================================
// LECCION 22: Arquitectura de Memoria (Árboles Rojo-Negro / Balanceados)
// ¿Por qué O(log n)? ¿Por qué los elementos son const a través de iteradores?
// ============================================================================
void leccion_22_arquitectura_arbol() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 22: Arquitectura Interna de std::set" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * DIFERENCIA CLAVE DE ORGANIZACION:
     * - Contenedores Secuenciales (vector, deque, list):
     *   Organizan los datos por POSICION o momento de llegada (indice 0, 1, 2...).
     * - Contenedores Asociativos (set, multiset, map, multimap):
     *   Organizan los datos sobre la base de CLAVES (Keys) ordenadas,
     *   INDEPENDIENTEMENTE de quien fue insertado primero o despues.
     *
     * ESTRUCTURA SUBYACENTE:
     * En la STL de C++, los asociativos ordenados se implementan sobre
     * ARBOLES DE BUSQUEDA BINARIA AUTO-BALANCEADOS (Self-balancing BST, Red-Black Trees):
     *
     *                     [ Nodo Raiz: 50 ]
     *                        /         \
     *           [ Hijo Izq: 20 ]     [ Hijo Der: 80 ]
     *               /       \            /       \
     *           [ 10 ]     [ 30 ]     [ 70 ]    [ 90 ]
     *
     * PUNTOS CLAVE DE EXAMEN (¡Enfasis textual del profesor!):
     * 1. ¿Cuando se logra O(log n)?
     *    UNICAMENTE SI EL ARBOL ESTA BALANCEADO.
     *    Si el arbol se desbalanceara (degenerara), tendria altura N y la
     *    busqueda caeria a lineal O(N) como una lista enlazada simple.
     *    Los Red-Black Trees garantizan altura O(log n) mediante rotaciones.
     *
     * 2. ¿Por que los elementos NO se pueden modificar por iterador?
     *    Si pudieras hacer `*it = 999;`, cambiarias el valor sin reorganizar el arbol,
     *    destruyendo el invariante de orden binario. Por eso, el iterador desreferencia
     *    como `const T&`. Para cambiar un valor, debes BORRAR e INSERTAR el nuevo.
     *
     * 3. Criterio de orden por defecto:
     *    Utiliza el functor std::less<T> (operador <).
     *
     * 4. Claves unicas:
     *    std::set NO admite elementos repetidos.
     */

    std::set<int> s{50, 20, 80, 10, 30, 70, 90};

    std::cout << "set tras insertar en orden desordenado (se auto-ordena): ";
    for (int x : s) std::cout << x << " ";
    std::cout << std::endl;

    auto it = s.begin();
    std::cout << "Primer elemento (*s.begin()): " << *it << " (el menor)" << std::endl;

    // ERROR DE COMPILACION DE EXAMEN:
    // *it = 100; // ¡ERROR! El valor es 'const int&'. No se puede modificar in-place.
}

// ============================================================================
// LECCION 23: Inserción y Retorno de std::pair<iterator, bool>
// ============================================================================
void leccion_23_insercion_pair() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 23: Retorno de insert() y emplace()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * std::set::insert(valor) RETORNA UN std::pair:
     *   pair.first  -> Iterador que apunta al elemento en el arbol.
     *   pair.second -> Booleano:
     *                  true  = La insercion tuvo exito (el elemento era nuevo).
     *                  false = La insercion fallo (el elemento ya existia).
     */
    std::set<int> s{10, 20, 30};

    // 1. Insercion de un elemento nuevo:
    auto [it1, exito1] = s.insert(40);
    std::cout << std::format("Insertar 40 -> Valor: {}, Exito: {}", *it1, exito1) << std::endl;

    // 2. Intento de insercion de un duplicado:
    auto [it2, exito2] = s.insert(20);
    std::cout << std::format("Insertar 20 (repetido) -> Valor apuntado: {}, Exito: {}", *it2, exito2) << std::endl;

    // 3. emplace(): Construccion in-situ
    auto [it3, exito3] = s.emplace(50);
    std::cout << std::format("Emplace 50 -> Valor: {}, Exito: {}", *it3, exito3) << std::endl;

    // 4. Insercion por rangos (de arrays, vectores, etc.):
    std::array<int, 3> extra{25, 30, 35};
    s.insert(extra.begin(), extra.end()); // El 30 se ignora silenciosamente

    print_container("set tras todas las inserciones: ", s);
}

// ============================================================================
// LECCION 24: Búsqueda Eficiente: find() vs std::find(), count() y contains()
// ============================================================================
void leccion_24_busqueda_logaritmica() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 24: Busqueda Logaritmica: s.find(), count() y contains()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ¡TRAMPA MORTAL DE EXAMEN!
     * 1. std::find(s.begin(), s.end(), val):
     *    Es el algoritmo generico. Recorre nodo por nodo secuencialmente.
     *    Costo: O(N) LINEAL. ¡Desperdicia la estructura de arbol!
     *
     * 2. s.find(val):
     *    Es el metodo miembro nativo de std::set.
     *    Baja por las ramas izquierda/derecha comparando claves.
     *    Costo: O(log n) LOGARITMICO. ¡Esta es la opcion correcta!
     */
    std::set<std::string> ciudades{"Lima", "Cusco", "Arequipa", "Trujillo", "Piura"};

    // 1. Busqueda con find() nativo:
    auto it = ciudades.find("Cusco");
    if (it != ciudades.end()) {
        std::cout << "ciudades.find(\"Cusco\"): ENCONTRADO -> " << *it << std::endl;
    } else {
        std::cout << "ciudades.find(\"Cusco\"): NO encontrado" << std::endl;
    }

    // 2. contains() - Metodo moderno introducido en C++20:
    // Retorna directamente true o false en O(log n) sin lidiar con iteradores:
    bool tiene_lima = ciudades.contains("Lima");
    bool tiene_iquitos = ciudades.contains("Iquitos");
    std::cout << std::format("ciudades.contains(\"Lima\"): {}", tiene_lima) << std::endl;
    std::cout << std::format("ciudades.contains(\"Iquitos\"): {}", tiene_iquitos) << std::endl;

    // 3. count() en std::set:
    // Como las claves son unicas, count() solo puede devolver 1 (si esta) o 0 (si no esta):
    std::cout << "ciudades.count(\"Arequipa\"): " << ciudades.count("Arequipa") << std::endl;
    std::cout << "ciudades.count(\"Tacna\"):    " << ciudades.count("Tacna") << std::endl;
}

// ============================================================================
// LECCION 25: Borrado y Límites de Rango (lower_bound, upper_bound)
// ============================================================================
void leccion_25_borrado_limites() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 25: erase(), lower_bound() y upper_bound()" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::set<int> s{10, 20, 30, 40, 50, 60, 70};

    // 1. Borrado por clave exacta: s.erase(clave)
    // Retorna el numero de elementos borrados (1 o 0 en set) en O(log n):
    size_t eliminados = s.erase(30);
    std::cout << "s.erase(30) -> Elementos borrados: " << eliminados << std::endl;

    size_t eliminados_inexistente = s.erase(999);
    std::cout << "s.erase(999) -> Elementos borrados: " << eliminados_inexistente << std::endl;

    // 2. lower_bound(k): Primer elemento >= k
    // 3. upper_bound(k): Primer elemento > k
    std::cout << "\n--- Limites de rango sobre {10, 20, 40, 50, 60, 70} ---" << std::endl;
    auto lb = s.lower_bound(35); // Primer elemento >= 35 (es el 40)
    auto ub = s.upper_bound(50); // Primer elemento > 50 (es el 60)

    std::cout << "lower_bound(35): " << *lb << " (primer elemento >= 35)" << std::endl;
    std::cout << "upper_bound(50): " << *ub << " (primer elemento > 50)" << std::endl;

    // Borrar un subrango [lb, ub): borra 40 y 50
    s.erase(lb, ub);
    print_container("set tras borrar rango [lower_bound(35), upper_bound(50)): ", s);
}

// ============================================================================
// LECCION 26: Orden Personalizado (std::greater) y Fusión con merge()
// ============================================================================
void leccion_26_orden_descendente_merge() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 26: std::greater y s1.merge(s2)" << std::endl;
    std::cout << "==================================================" << std::endl;

    // 1. Orden descendente usando std::greater:
    std::set<int, std::greater<int>> s_desc{30, 10, 50, 20, 40};
    std::cout << "Set ordenado con std::greater (mayor a menor): ";
    for (int x : s_desc) std::cout << x << " ";
    std::cout << std::endl;

    // 2. Fusión con merge() (C++17):
    // Transfiere los nodos de s2 a s1 en O(N log(size + N)).
    // ¡Los elementos repetidos SE QUEDAN en s2 porque set no admite duplicados!
    std::set<int> a{1, 3, 5, 7};
    std::set<int> b{2, 3, 4, 7, 8};

    std::cout << "\nAntes de a.merge(b):" << std::endl;
    print_container("a: ", a);
    print_container("b: ", b);

    a.merge(b);

    std::cout << "Despues de a.merge(b):" << std::endl;
    print_container("a (absorbio nodos nuevos): ", a);
    print_container("b (conservo los duplicados 3 y 7): ", b);
}

// ============================================================================
// LECCION 27: std::multiset (Duplicados Permitidos)
// ============================================================================
void leccion_27_multiset_duplicados() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 27: std::multiset (Manejo de Duplicados)" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * std::multiset:
     * - Almacena elementos ordenados en un Red-Black Tree.
     * - PERMITE MULTIPLES ELEMENTOS CON EL MISMO VALOR.
     * - insert(val) NO retorna pair<it, bool>, sino solo `iterator`
     *   (porque la insercion NUNCA falla por duplicidad).
     *
     * ¡PELIGRO DE EXAMEN EN ms.erase(val)!
     * - ms.erase(val) borra TODAS las copias del valor que existan en el arbol.
     * - Si solo deseas borrar UNA copia, debes usar ms.erase(ms.find(val)).
     */

    std::multiset<int> ms{10, 20, 20, 20, 30, 40, 40, 50};
    print_container("multiset inicial con duplicados: ", ms);

    // 1. count() cuenta todas las apariciones en O(log n + count):
    std::cout << "ms.count(20): " << ms.count(20) << " apariciones" << std::endl;
    std::cout << "ms.count(40): " << ms.count(40) << " apariciones" << std::endl;

    // 2. Insercion de duplicado:
    ms.insert(20);
    std::cout << "Tras ms.insert(20) adicional -> count(20): " << ms.count(20) << std::endl;

    // 3. Borrar SOLO UNA copia de 20:
    auto it_uno = ms.find(20);
    if (it_uno != ms.end()) {
        ms.erase(it_uno); // Borra solo el nodo apuntado
        std::cout << "Tras borrar UNA sola copia con ms.erase(find(20)): ";
        for (int x : ms) std::cout << x << " ";
        std::cout << std::endl;
    }

    // 4. Borrar TODAS las copias de 40 de golpe:
    size_t total_borrados = ms.erase(40);
    std::cout << std::format("ms.erase(40) borro TODAS las {} copias.", total_borrados) << std::endl;
    print_container("multiset final: ", ms);
}

int main() {
    std::cout << "===========================================================" << std::endl;
    std::cout << "   REPASO AEDA - SEMANA 7: STD::SET Y STD::MULTISET        " << std::endl;
    std::cout << "===========================================================" << std::endl;

    leccion_22_arquitectura_arbol();
    leccion_23_insercion_pair();
    leccion_24_busqueda_logaritmica();
    leccion_25_borrado_limites();
    leccion_26_orden_descendente_merge();
    leccion_27_multiset_duplicados();

    return 0;
}
