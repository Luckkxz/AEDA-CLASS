#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <array>
#include <format>
#include <vector>
#include <stdexcept>
#include "../01_Buildingblocks/helpers.h"

// ============================================================================
// SEMANA 7: CONTENEDORES ASOCIATIVOS ORDENADOS II - std::map y std::multimap
// ============================================================================

// ============================================================================
// LECCION 28: Arquitectura de std::map y la estructura std::pair
// ¿Como se almacena la pareja Clave-Valor en el arbol?
// ============================================================================
void leccion_28_arquitectura_map_pair() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 28: Arquitectura de std::map y std::pair" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ARQUITECTURA DE std::map:
     * Al igual que std::set, se implementa sobre un ARBOL ROJO-NEGRO (Red-Black Tree).
     * Pero cada nodo del arbol no guarda un solo dato, sino un:
     *
     *            std::pair<const Key, Value>
     *
     *       [ Nodo: .first = "DNI_100" (const) | .second = "Juan" ]
     *                  /                               \
     *   [ .first = "DNI_050" | "Ana" ]    [ .first = "DNI_150" | "Pedro" ]
     *
     * PUNTOS CLAVE DE EXAMEN:
     * 1. ¿En funcion de que componente se ordena el arbol?
     *    UNICAMENTE en base a la CLAVE (.first) usando std::less<Key>.
     *    El valor (.second) es solo "carga util" (payload); no interviene en el orden.
     *
     * 2. ¿Por que la clave es `const Key`?
     *    Si cambiaras la clave de un nodo existente, romperias la posicion ordenada
     *    del arbol.
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

    // Imprime ordenado automaticamente por clave ascendente (101, 102, 105):
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
     *      ¡INSERTA AUTOMATICAMENTE una nueva pareja con la clave 'k' y el valor
     *      inicializado por defecto (ej: 0 para enteros, "" para strings)!
     *    - CONSECUENCIA DIRECTA: operator[] NUNCA puede usarse sobre un mapa const.
     *
     * 2. at(k):
     *    - Si la clave 'k' EXISTE: Devuelve la referencia al valor asociado.
     *    - Si la clave 'k' NO EXISTE:
     *      LANZA UNA EXCEPCION capturable de tipo `std::out_of_range`.
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
    int nota_fantasma = notas["AlumnoNuevo"]; // ¡LO INSERTA CON NOTA 0 AUTOMATICAMENTE!
    std::cout << "notas[\"AlumnoNuevo\"]: " << nota_fantasma << " (auto-insertado con 0)" << std::endl;
    std::cout << "Tamano de notas DESPUES de operator[]: " << notas.size() << " (aumento a 3!)" << std::endl;

    // 3. at() seguro con comprobacion y excepciones:
    std::cout << "\nAcceso seguro con at():" << std::endl;
    try {
        std::cout << "Nota de Carlos: " << notas.at("Carlos") << std::endl;
        std::cout << "Consultando 'Desconocido': " << notas.at("Desconocido") << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "¡Excepcion capturada con exito! Mensaje: " << e.what() << std::endl;
        std::cout << "El mapa no fue alterado por at(). Tamano sigue siendo: " << notas.size() << std::endl;
    }
}

// ============================================================================
// LECCION 30: Insercion Controlada: insert() vs insert_or_assign()
// ============================================================================
void leccion_30_insercion_controlada() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 30: Control de Insercion: insert() vs insert_or_assign()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * RETORNO DE m.insert({k, v}):
     * Devuelve `std::pair<iterator, bool>`:
     * - iterador: apunta al elemento (nuevo o ya existente).
     * - bool: true si se inserto exitosamente, false si la clave YA EXISTIA.
     *
     * Si la clave ya existia, insert() NO SOBREESCRIBE EL VALOR.
     *
     * insert_or_assign() (C++17):
     * Si existe, actualiza el valor (.second).
     * Si no existe, lo inserta nuevo.
     * Devuelve tambien std::pair<iterator, bool> donde bool indica si fue insercion nueva (true)
     * o solo asignacion/actualizacion (false).
     */

    std::map<std::string, double> precios;

    // Primer intento: insercion exitosa
    auto [it1, ok1] = precios.insert({"Manzana", 2.50});
    std::cout << std::format("Insert 'Manzana': {} (precio: {:.2f})", ok1 ? "EXITO" : "FALLO", it1->second) << std::endl;

    // Segundo intento con misma clave pero distinto precio:
    auto [it2, ok2] = precios.insert({"Manzana", 4.00});
    std::cout << std::format("Insert 'Manzana' con 4.00: {} (precio retenido: {:.2f})",
                             ok2 ? "EXITO" : "FALLO (ya existia)", it2->second) << std::endl;

    // Con insert_or_assign():
    auto [it3, ok3] = precios.insert_or_assign("Manzana", 4.50);
    std::cout << std::format("insert_or_assign 'Manzana' con 4.50: Nuevo={} (precio actual: {:.2f})",
                             ok3 ? "SI (nueva clave)" : "NO (actualizado)", it3->second) << std::endl;
}

// ============================================================================
// LECCION 31: Busqueda Logaritmica y Borrado
// ============================================================================
void leccion_31_busqueda_borrado() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 31: Busqueda O(log n) con find(), contains() y erase()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * METODOS DE BUSQUEDA EN std::map:
     *
     * 1. m.find(clave) -> O(log n)
     *    Devuelve iterador al nodo si existe; si no, devuelve m.end().
     *    ¡NUNCA uses std::find(m.begin(), m.end(), ...) porque seria O(n)!
     *
     * 2. m.contains(clave) -> O(log n) [Desde C++20]
     *    Devuelve simplemente bool (true/false).
     *
     * 3. m.count(clave) -> O(log n)
     *    En std::map solo puede ser 0 o 1 (porque las claves son unicas).
     */

    std::map<int, std::string> servidores{
        {80, "HTTP"},
        {443, "HTTPS"},
        {22, "SSH"},
        {21, "FTP"}
    };

    // Busqueda moderna con contains():
    if (servidores.contains(443)) {
        std::cout << "Puerto 443 disponible: " << servidores[443] << std::endl;
    }

    // Busqueda tradicional con find():
    auto it = servidores.find(22);
    if (it != servidores.end()) {
        std::cout << std::format("find(): Servidor encontrado -> Puerto {} : {}", it->first, it->second) << std::endl;
    }

    // Borrado por clave: erase(clave) devuelve el numero de elementos borrados (0 o 1)
    size_t eliminados = servidores.erase(21);
    std::cout << std::format("erase(21): {} elemento(s) eliminado(s)", eliminados) << std::endl;
    std::cout << "contains(21) tras borrado: " << (servidores.contains(21) ? "true" : "false") << std::endl;
}

// ============================================================================
// LECCION 32: std::multimap (Mapeo Uno-a-Muchos)
// ¿Por que std::multimap NO TIENE operator[] ni at()?
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

    std::cout << "RECORDATORIO DE AUDIO DEL PROFESOR:" << std::endl;
    std::cout << "-> ¿Cuando NO usar asociativos (set/map)? Cuando necesites preservar" << std::endl;
    std::cout << "   estrictamente el orden cronologico de llegada de los datos." << std::endl;
    std::cout << "-> ¿Cual tiene mejor localidad de cache espacial? std::vector (por contiguidad)." << std::endl;
    std::cout << "-> ¿Cual no invalida iteradores al insertar/borrar nodos? std::list." << std::endl;
}

// ============================================================================
// LECCION 34: Insercion de Alto Rendimiento: try_emplace() vs emplace()
// (¡OPTIMIZACION CLAVE C++17/20 VISTA EN EL EJEMPLO 2 DE CLASE!)
// ============================================================================
void leccion_34_try_emplace_vs_emplace() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 34: try_emplace() vs emplace() (Optimizacion Clave)" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * ¿CUAL ES LA DIFERENCIA ENTRE emplace() Y try_emplace()?
     *
     * 1. m.emplace(k, v) / m.emplace(pair):
     *    - Intenta insertar la pareja.
     *    - ¡PROBLEMA POTENCIAL!: Si la clave ya existe, la insercion se rechaza,
     *      pero los argumentos temporales pasados a emplace() PUEDEN HABER SIDO
     *      CONSTRUIDOS O MOVIDOS innecesariamente antes de verificar la clave.
     *
     * 2. m.try_emplace(key, args_for_value...):
     *    - Evalua PRIMERO si la clave 'key' ya existe en el arbol.
     *    - Si la clave YA EXISTE: ¡NO HACE NADA! No construye el valor ni mueve
     *      ningun argumento pasado. Cero coste de construccion/movimiento.
     *    - Si la clave NO EXISTE: Construye el valor in-place pasando 'args_for_value...'
     *      directamente al constructor del tipo Value.
     *    - Retorna: std::pair<iterator, bool> (igual que insert y emplace).
     *
     * 3. CLAVES std::string_view:
     *    - std::string_view es una vista no propietaria de una cadena (puntero + longitud).
     *    - Ideal para claves de busqueda o literales estaticos: ¡CERO COPIAS EN EL HEAP!
     */

    std::map<std::string_view, std::string> aeropuertos{
        {"ORD", "O'Hare International (Chicago)"},
        {"LHR", "Heathrow Airport (London)"},
        {"LIM", "Jorge Chavez International (Lima)"}
    };

    std::cout << "Aeropuertos iniciales: " << aeropuertos.size() << std::endl;

    // Intento 1 con try_emplace (clave NUEVA):
    auto [it1, ok1] = aeropuertos.try_emplace("DXB", "Dubai International Airport");
    std::cout << std::format("try_emplace('DXB'): Exito={} -> [{}, {}]",
                             ok1 ? "SI" : "NO", it1->first, it1->second) << std::endl;

    // Intento 2 con try_emplace (clave YA EXISTENTE):
    // La cadena "Nuevo Lima" NUNCA se asigna ni altera el valor existente:
    auto [it2, ok2] = aeropuertos.try_emplace("LIM", "Nuevo Lima Internacional");
    std::cout << std::format("try_emplace('LIM' duplicado): Exito={} -> Retenido: [{}]",
                             ok2 ? "SI" : "NO (Rechazado sin construir)", it2->second) << std::endl;

    std::cout << "Total aeropuertos despues de try_emplace: " << aeropuertos.size() << std::endl;
}

// ============================================================================
// LECCION 35: std::multimap Avanzado: find() con bucle vs equal_range()
// (TRAMPAS Y PATRONES DEL EJEMPLO 4 DE CLASE)
// ============================================================================
void leccion_35_multimap_avanzado() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 35: multimap: find() + bucle vs equal_range()" << std::endl;
    std::cout << "==================================================" << std::endl;

    /*
     * PATRONES DE RECORRIDO DE CLAVES DUPLICADAS EN std::multimap:
     *
     * Un multimap almacena elementos con la misma clave de forma CONTIGUA en el
     * recorrido in-order del arbol. Por tanto, todas las entradas con clave K estan juntos.
     *
     * METODO A: find(k) + bucle while (como en multimap_example_4):
     *    auto iter = mm.find(k);
     *    if (iter != mm.end()) {
     *        while (iter != mm.end() && iter->first == k) {
     *            // procesar
     *            ++iter;
     *        }
     *    }
     *    ¡CUIDADO CON EL INCREMENTO!: Si llegas a mm.end(), no debes desreferenciar iter->first.
     *
     * METODO B: equal_range(k) (Forma Canonica y Mas Segura en C++):
     *    auto [primero, ultimo] = mm.equal_range(k);
     *    // Devuelve el rango semi-abierto [primero, ultimo).
     *    // Si la clave NO existe, primero == ultimo.
     *    for (auto it = primero; it != ultimo; ++it) {
     *        // procesar it->second
     *    }
     *
     * ¡TRAMPA DE EXAMEN!:
     * En multimap_example_4 del profesor, el codigo comprobaba:
     *   `if (p.first->first != key)`
     * ¡PELIGRO! Si la clave NO existe y el multimap esta vacio o p.first == mm.end(),
     * desreferenciar `p.first->first` causa UNDEFINED BEHAVIOR / CRASH.
     * La forma correcta y segura SIEMPRE es comprobar:
     *   `if (p.first == p.second)` // Rango vacio = no encontrado!
     */

    using multimap_ciudades = std::multimap<std::string_view, std::string>;

    multimap_ciudades ciudades{
        {"Peru", "Lima"},
        {"Peru", "Arequipa"},
        {"Peru", "Cusco"},
        {"Brasil", "Sao Paulo"},
        {"Brasil", "Rio de Janeiro"},
        {"Chile", "Santiago"}
    };

    std::array<std::string_view, 3> paises_buscar{"Peru", "Chile", "Argentina"};

    std::cout << "\n--- METODO 1: Bucle while con find() ---" << std::endl;
    for (const auto& pais : paises_buscar) {
        std::cout << std::format("Buscando pais '{}':", pais) << std::endl;
        if (auto it = ciudades.find(pais); it != ciudades.end()) {
            while (it != ciudades.end() && it->first == pais) {
                std::cout << std::format("  -> [{}, {}]", it->first, it->second) << std::endl;
                ++it;
            }
        } else {
            std::cout << "  -> ¡No encontrado!" << std::endl;
        }
    }

    std::cout << "\n--- METODO 2: Rango seguro con equal_range() ---" << std::endl;
    for (const auto& pais : paises_buscar) {
        std::cout << std::format("Buscando pais '{}' con equal_range():", pais) << std::endl;
        auto [primero, ultimo] = ciudades.equal_range(pais);
        if (primero == ultimo) {
            std::cout << "  -> ¡Rango vacio (No encontrado)!" << std::endl;
        } else {
            for (auto it = primero; it != ultimo; ++it) {
                std::cout << std::format("  -> Ciudad: {}", it->second) << std::endl;
            }
        }
    }
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
    leccion_34_try_emplace_vs_emplace();
    leccion_35_multimap_avanzado();

    return 0;
}
