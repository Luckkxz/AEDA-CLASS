#include <iostream>
#include <map>
#include <string>
#include <format>
#include <vector>
#include <stdexcept>
#include "../01_Buildingblocks/helpers.h"

// ============================================================================
// SEMANA 7: CONTENEDORES ASOCIATIVOS ORDENADOS II - std::map y std::multimap
// ============================================================================

// ============================================================================
// LECCION 28: Arquitectura de std::map y la estructura std::pair
// ¿Cómo se almacena la pareja Clave-Valor en el árbol?
// ============================================================================
void leccion_28_arquitectura_map_pair() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 28: Arquitectura de std::map y std::pair" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ARQUITECTURA DE std::map:
     * Al igual que std::set, se implementa sobre un ÁRBOL ROJO-NEGRO (Red-Black Tree).
     * Pero cada nodo del árbol no guarda un solo dato, sino un:
     *
     *            std::pair<const Key, Value>
     *
     *       [ Nodo: .first = "DNI_100" (const) | .second = "Juan" ]
     *                  /                               \
     *   [ .first = "DNI_050" | "Ana" ]    [ .first = "DNI_150" | "Pedro" ]
     *
     * PUNTOS CLAVE DE EXAMEN:
     * 1. ¿En función de qué componente se ordena el árbol?
     *    UNICAMENTE en base a la CLAVE (.first) usando std::less<Key>.
     *    El valor (.second) es solo "carga útil" (payload); no interviene en el orden.
     *
     * 2. ¿Por qué la clave es `const Key`?
     *    Si cambiaras la clave de un nodo existente, romperías la posición ordenada
     *    del árbol.
     *
     * 3. Structured Binding (C++17/20):
     *    Permite desempaquetar limpiamente:
     *    for (const auto& [clave, valor] : mapa) { ... }
     */

    std::map<int, std::string> codigos{
        {101, "Sistemas"},
        {105, "Industrial"},
        {102, "Software"}
    };

    // Imprime ordenado automáticamente por clave ascendente (101, 102, 105):
    std::cout << "Map recorrido con structured binding (ordenado por clave):" << std::endl;
    for (const auto& [cod, carrera] : codigos) {
        std::cout << std::format("  Clave: {:3d} -> Carrera: {:s}", cod, carrera) << std::endl;
    }

    auto it = codigos.begin();
    // it->first = 999;       // ¡ERROR DE COMPILACION! .first es 'const int'
    it->second = "Computacion"; // SI ES VALIDO: el valor asociado (.second) es modificable.
    std::cout << "Valor modificado en la clave 101: " << it->second << std::endl;
}

// ============================================================================
// LECCION 29: operator[] vs at() (¡LA PREGUNTA FIJA DE EXAMEN!)
// ============================================================================
void leccion_29_operator_corchetes_vs_at() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 29: operator[] vs at() (Comportamiento Crucial)" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * DIFERENCIA VITAL ENTRE m[k] y m.at(k):
     *
     * 1. operator[k]:
     *    - Si la clave 'k' EXISTE: Devuelve una referencia mutable a su valor asociado.
     *    - Si la clave 'k' NO EXISTE:
     *      ¡INSERTA AUTOMÁTICAMENTE una nueva pareja con la clave 'k' y el valor
     *      inicializado por defecto (ej: 0 para enteros, "" para strings)!
     *    - CONSECUENCIA DIRECTA: operator[] NUNCA puede usarse sobre un mapa const.
     *
     * 2. at(k):
     *    - Si la clave 'k' EXISTE: Devuelve la referencia al valor asociado.
     *    - Si la clave 'k' NO EXISTE:
     *      LANZA UNA EXCEPCIÓN capturable de tipo `std::out_of_range`.
     *      NUNCA altera ni inserta elementos en el mapa.
     *    - SI puede usarse sobre mapas const.
     */

    std::map<std::string, int> notas{
        {"Elias", 18},
        {"Carlos", 15}
    };

    // 1. operator[] para modificar existente:
    notas["Elias"] = 20;
    std::cout << "notas[\"Elias\"] modificada a: " << notas["Elias"] << std::endl;

    // 2. operator[] con clave inexistente:
    std::cout << "Tamano de notas ANTES de consultar clave inexistente: " << notas.size() << std::endl;
    int nota_fantasma = notas["AlumnoNuevo"]; // ¡LO INSERTA CON NOTA 0 AUTOMÁTICAMENTE!
    std::cout << "notas[\"AlumnoNuevo\"]: " << nota_fantasma << " (auto-insertado con 0)" << std::endl;
    std::cout << "Tamano de notas DESPUES de operator[]: " << notas.size() << " (aumento a 3!)" << std::endl;

    // 3. at() seguro con comprobación y excepciones:
    std::cout << "\nAcceso seguro con at():" << std::endl;
    try {
        std::cout << "notas.at(\"Carlos\"): " << notas.at("Carlos") << std::endl;
        std::cout << "Intentando notas.at(\"Inexistente\")..." << std::endl;
        std::cout << notas.at("Inexistente") << std::endl; // Lanza std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cout << "-> Excepcion capturada correctamente: std::out_of_range ("
                  << e.what() << ")" << std::endl;
        std::cout << "Tamano de notas tras fallo de at(): " << notas.size()
                  << " (NO se modifico el mapa)" << std::endl;
    }
}

// ============================================================================
// LECCION 30: Inserción Controlada: insert() vs insert_or_assign()
// ============================================================================
void leccion_30_insercion_controlada() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 30: Control de Insercion: insert() vs insert_or_assign()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * DIFERENCIA DE SOBREESCRITURA:
     * - m.insert({k, v}):
     *   Si la clave ya existe, NO LA SOBREESCRIBE (conserva el valor anterior)
     *   y retorna pair<it, false>.
     * - m.insert_or_assign(k, v) (C++17):
     *   Si no existe la inserta; si existe, ACTUALIZA su valor explícitamente.
     */

    std::map<int, std::string> inventario{
        {1, "Teclado"},
        {2, "Mouse"}
    };

    // 1. Intento de insert con clave existente:
    auto [it1, exito1] = inventario.insert({1, "Teclado Mecanico RGB"});
    std::cout << std::format("insert clave 1 repetida -> Exito: {}, Valor en mapa: {}",
                             exito1, it1->second) << " (NO SOBREESCRIBIO)" << std::endl;

    // 2. Uso de insert_or_assign (C++17):
    auto [it2, exito2] = inventario.insert_or_assign(1, "Teclado Mecanico RGB");
    std::cout << std::format("insert_or_assign clave 1 -> Fue nueva insercion: {}, Valor en mapa: {}",
                             exito2, it2->second) << " (SI SOBREESCRIBIO)" << std::endl;
}

// ============================================================================
// LECCION 31: Búsqueda Logarítmica y Borrado
// ============================================================================
void leccion_31_busqueda_borrado() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 31: Busqueda O(log n) con find(), contains() y erase()" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::map<std::string, double> precios{
        {"Manzana", 2.50},
        {"Platano", 1.80},
        {"Naranja", 3.20},
        {"Fresa", 5.00}
    };

    // 1. find(clave): O(log n)
    auto it = precios.find("Platano");
    if (it != precios.end()) {
        std::cout << std::format("find(\"Platano\") -> Clave: {}, Precio: S/. {:.2f}",
                                 it->first, it->second) << std::endl;
    }

    // 2. contains(clave) (C++20):
    std::cout << "precios.contains(\"Fresa\"): " << precios.contains("Fresa") << std::endl;
    std::cout << "precios.contains(\"Mango\"): " << precios.contains("Mango") << std::endl;

    // 3. erase(clave): Borra la pareja y retorna 1 si existía o 0 si no existía:
    size_t borrados = precios.erase("Naranja");
    std::cout << "precios.erase(\"Naranja\") -> Eliminados: " << borrados << std::endl;

    // 4. clear(): Vacia todo el arbol liberando todos los nodos:
    precios.clear();
    std::cout << "Tras precios.clear() -> size = " << precios.size()
              << ", empty = " << (precios.empty() ? "true" : "false") << std::endl;
}

// ============================================================================
// LECCION 32: std::multimap (Mapeo Uno-a-Muchos)
// ¿Por qué std::multimap NO TIENE operator[] ni at()?
// ============================================================================
void leccion_32_multimap() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 32: std::multimap y la Ausencia de operator[]" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * std::multimap:
     * Permite multiples parejas con la MISMA CLAVE (relacion 1 a N).
     *
     * ¡PREGUNTA FIJA DE EXAMEN!
     * ¿Por que std::multimap NO implementa operator[] ni at()?
     * RESPUESTA:
     * Si la clave "UNI" tiene 3 valores distintos ("FIIS", "FIEI", "FC"),
     * la expresion `mm["UNI"]` seria completamente AMBIGUA: ¿A cual de los 3
     * valores deberia apuntar o modificar?
     * Como la STL no permite ambiguedades, la operacion NO EXISTE.
     *
     * ¿COMO SE CONSULTA UN MULTIMAP?
     * Con mm.equal_range(clave), que devuelve un std::pair de iteradores:
     * [inicio_rango, fin_rango) abarcando todos los valores asociados a esa clave.
     */

    std::multimap<std::string, std::string> facultades;

    facultades.insert({"UNI", "FIIS"});
    facultades.insert({"UNI", "FIEI"});
    facultades.insert({"UNI", "FC"});
    facultades.insert({"UNMSM", "Medicina"});
    facultades.insert({"UNMSM", "Derecho"});

    print_multimap("Contenido de facultades (std::multimap):", facultades);

    // 1. Contar cuantas entradas tiene una clave:
    std::cout << "facultades.count(\"UNI\"): " << facultades.count("UNI") << std::endl;

    // 2. equal_range(): Obtener todos los valores de "UNI":
    std::cout << "\nValores asociados a la clave 'UNI' mediante equal_range():" << std::endl;
    auto [inicio, fin] = facultades.equal_range("UNI");
    for (auto it = inicio; it != fin; ++it) {
        std::cout << "  -> " << it->second << std::endl;
    }

    // 3. erase(clave) en multimap:
    // ¡Borra TODAS las parejas que tengan esa clave!
    size_t eliminados_uni = facultades.erase("UNI");
    std::cout << std::format("facultades.erase(\"UNI\") borro TODAS las {} parejas.", eliminados_uni) << std::endl;
    print_multimap("Tras borrar 'UNI':", facultades);
}

// ============================================================================
// LECCION 33: Gran Matriz Resumen de Contenedores STL (Semanas 3 a 7)
// ============================================================================
void leccion_33_gran_resumen_stl() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 33: Resumen Final de Contenedores STL" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::cout << R"(
+-----------------+-----------------------+---------------------+---------------------+--------------------+
| Contenedor STL  | Memoria Interna       | Acceso por Indice   | Insercion Extremos  | Insercion Medio    |
+-----------------+-----------------------+---------------------+---------------------+--------------------+
| std::array      | Stack (Contigua Fija) | O(1) directo []     | NO DINAMICO         | NO DINAMICO        |
| std::vector     | Heap (1 Bloque Cont.) | O(1) directo []     | O(1) amort. final   | O(N) desplaza RAM  |
| std::deque      | Chunks + Mapa Punteros| O(1) doble salto [] | O(1) amort. front/bk| O(N) desplaza chunk|
| std::list       | Heap (Nodos Dispersos)| NO EXISTE (solo it) | O(1) estricto       | O(1) con iterador  |
| std::set / map  | Arbol Red-Black Balan.| O(log n) (map [])   | O(log n) auto-orden | O(log n) auto-orden|
+-----------------+-----------------------+---------------------+---------------------+--------------------+
)" << std::endl;

    std::cout << "¡RECORDATORIO DE AUDIO DEL PROFESOR!" << std::endl;
    std::cout << "-> ¿Cuando NO usar asociativos (set/map)? Cuando necesites preservar" << std::endl;
    std::cout << "   estrictamente el orden cronologico de llegada de los datos." << std::endl;
    std::cout << "-> ¿Cual tiene mejor localidad de cache espacial? std::vector (por contiguidad)." << std::endl;
    std::cout << "-> ¿Cual no invalida iteradores al insertar/borrar nodos? std::list." << std::endl;
}

int main() {
    std::cout << "===========================================================" << std::endl;
    std::cout << "   REPASO AEDA - SEMANA 7: STD::MAP Y STD::MULTIMAP        " << std::endl;
    std::cout << "===========================================================" << std::endl;

    leccion_28_arquitectura_map_pair();
    leccion_29_operator_corchetes_vs_at();
    leccion_30_insercion_controlada();
    leccion_31_busqueda_borrado();
    leccion_32_multimap();
    leccion_33_gran_resumen_stl();

    return 0;
}
