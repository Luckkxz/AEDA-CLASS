#include <iostream>
#include <array>
#include <vector>
#include <format>
#include <ranges>
#include <string>
#include <algorithm>

// ============================================================================
// LECCION 1: Puntero crudo subyacente (.data())
// Ambos garantizan memoria contigua (casilleros pegados uno tras otro en RAM).
// ============================================================================
void leccion_01_punteros_y_data() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 1: .data() y Memoria Contigua" << std::endl;
    std::cout << "==================================================" << std::endl;

    // ARRAY: Los 5 enteros viven juntos en el Stack
    std::array<int, 5> arr{10, 20, 30, 40, 50};
    int* ptr_arr = arr.data(); // Apunta al casillero 0 (&arr[0])

    std::cout << "[std::array] Direccion base: " << ptr_arr << std::endl;
    std::cout << "[std::array] Primer valor (*ptr): " << *ptr_arr << std::endl;
    std::cout << "[std::array] Segundo valor (*(ptr+1)): " << *(ptr_arr + 1) << std::endl;

    // VECTOR: Los enteros viven juntos en el Heap (memoria dinamica)
    std::vector<int> vec{10, 20, 30, 40, 50};
    int* ptr_vec = vec.data(); // Apunta al casillero 0 en el Heap

    std::cout << "[std::vector] Direccion base en Heap: " << ptr_vec << std::endl;
    std::cout << "[std::vector] Primer valor (*ptr): " << *ptr_vec << std::endl;
    std::cout << "[std::vector] Segundo valor (*(ptr+1)): " << *(ptr_vec + 1) << std::endl;
}

// ============================================================================
// LECCION 2: .fill() vs .assign() (PREGUNTA 2 DE TU PC1)
// ¿Por que fill() NO existe en vector?
// ============================================================================
void leccion_02_fill_vs_assign() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 2: fill() vs assign() (Pregunta de PC1)" << std::endl;
    std::cout << "==================================================" << std::endl;

    // std::array TIENE el metodo .fill() porque su tamano ya esta fijo:
    std::array<int, 4> arr;
    arr.fill(77); // Rellena sus 4 casillas con el numero 77
    std::cout << "[std::array despues de .fill(77)]: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;

    // std::vector NO TIENE .fill(). (vec.fill(77) da ERROR de compilacion).
    // En vector se usa .assign(cantidad, valor) o el algoritmo std::fill():
    std::vector<int> vec;
    vec.assign(4, 77); // Crea 4 casillas con el valor 77
    std::cout << "[std::vector despues de .assign(4, 77)]: ";
    for (int x : vec) std::cout << x << " ";
    std::cout << std::endl;
}

// ============================================================================
// LECCION 3: Diferencias de tamano: sizeof vs .size() vs .max_size()
// ============================================================================
void leccion_03_sizes_y_sizeof() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 3: sizeof vs .size() vs .max_size()" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::array<int, 5> arr{1, 2, 3, 4, 5};
    std::vector<int> vec{1, 2, 3, 4, 5};

    // sizeof: Mide BYTES totales que ocupa el objeto
    // int = 4 bytes -> 5 ints = 20 bytes
    std::cout << "sizeof(arr): " << sizeof(arr) << " bytes (5 ints x 4 bytes)" << std::endl;
    // Un vector solo guarda 3 punteros de control (en 64 bits = 24 bytes)
    std::cout << "sizeof(vec): " << sizeof(vec) << " bytes (solo guarda punteros de control)" << std::endl;

    // .size(): Mide la CANTIDAD de elementos guardados
    std::cout << "arr.size(): " << arr.size() << " elementos" << std::endl;
    std::cout << "vec.size(): " << vec.size() << " elementos" << std::endl;

    // .max_size(): Limite teorico
    std::cout << "arr.max_size(): " << arr.max_size() << " (fijo e igual a N)" << std::endl;
    std::cout << "vec.max_size(): " << vec.max_size() << " (casi infinito en RAM)" << std::endl;
}
void push_and_pop(){
    std::vector<int> v;          // vector vacío de enteros

    v.push_back(10);        // agrega al final -> [10]
    v.push_back(20);        // -> [10, 20]
    v.push_back(30);        // -> [10, 20, 30]

    std::cout << v.size() << std::endl;   // 3 (cantidad de elementos)
    std::cout << v[0] << std::endl;       // 10 (acceso por índice, como un arreglo)
    std::cout << v.back() << std::endl;   // 30 (último elemento)

    v.pop_back();               // elimina el último -> [10, 20]
    std::cout << v.empty() << std::endl;  // 0 (false, no está vacío)
}

// ============================================================================
// LECCION 4: .empty() en array vs en vector
// ============================================================================
void leccion_04_empty_diferencia() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 4: empty() en array vs vector" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::array<int, 3> arr{0, 0, 0};
    // Aunque tenga ceros, sus 3 casillas existen en memoria:
    std::cout << "arr (tamano 3) esta vacio? arr.empty(): "
              << (arr.empty() ? "SI" : "NO") << std::endl;

    std::array<int, 0> arr_vacio;
    // Solo si N == 0 un array es empty:
    std::cout << "arr_vacio (tamano 0) esta vacio? arr_vacio.empty(): "
              << (arr_vacio.empty() ? "SI" : "NO") << std::endl;

    std::vector<int> vec;
    // Empieza vacio (size == 0):
    std::cout << "vec al crearse esta vacio? vec.empty(): "
              << (vec.empty() ? "SI" : "NO") << std::endl;

    vec.push_back(100);
    std::cout << "vec despues de push_back(100) esta vacio? vec.empty(): "
              << (vec.empty() ? "SI" : "NO") << std::endl;
}

// ============================================================================
// LECCION 5: Acceso seguro .at() vs operator[] vs front() / back()
// ============================================================================
void leccion_05_acceso_y_seguridad() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 5: Acceso Seguro (.at) vs Inseguro ([])" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::vector<int> v{10, 20, 30};

    std::cout << "Primer elemento v.front(): " << v.front() << std::endl;
    std::cout << "Ultimo elemento v.back():   " << v.back() << std::endl;

    // Acceso directo por indice:
    std::cout << "v[1]:    " << v[1] << std::endl;
    std::cout << "v.at(1): " << v.at(1) << std::endl;

    // Si nos pasamos del indice:
    try {
        std::cout << "Intentando v.at(99)..." << std::endl;
        std::cout << v.at(99) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "--> ATRAPADO POR .at(): Indice fuera de rango!" << std::endl;
    }
}

// ============================================================================
// LECCION 6: swap() - Diferencia de Complejidad O(N) vs O(1)
// ============================================================================
void leccion_06_swap_memoria_y_complejidad() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 6: swap() (O(N) en array vs O(1) en vector)" << std::endl;
    std::cout << "==================================================" << std::endl;

    // En std::vector: solo intercambia sus punteros internos (O(1))
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{99, 88, 77};

    std::cout << "Puntero original de v1: " << (void*)v1.data() << std::endl;
    std::cout << "Puntero original de v2: " << (void*)v2.data() << std::endl;

    //Nota: el (void*) solo se pone para obligar a std::cout a mostrar el código hexadecimal de la dirección de memoria

    v1.swap(v2); // O(1) solo intercambia las direcciones

    std::cout << "\nDespues de v1.swap(v2):" << std::endl;
    std::cout << "Nuevo puntero de v1 (ahora apunta a los datos de v2): " << (void*)v1.data() << std::endl;
    std::cout << "Nuevo puntero de v2 (ahora apunta a los datos de v1): " << (void*)v2.data() << std::endl;
    std::cout << "Primer valor de v1 ahora (*v1.data()): " << *v1.data() << std::endl;
    std::cout << "Primer valor de v2 ahora (*v2.data()): " << *v2.data() << std::endl;
}

// ============================================================================
// LECCION 7: Iteradores a Fondo (Normales, Rangos y Reversos)
// ============================================================================
void leccion_07_iteradores() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 7: Iteradores Normales, Sub-rangos y Reversos" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::array<int, 5> x_vals{17, 23, 7, 11, 31};

    // -------------------------------------------------------------
    // PARTE A: Recorrido Normal Completo (begin hasta end)
    // -------------------------------------------------------------
    std::cout << "A) Recorrido normal (hacia adelante):\n";
    // - begin(): casilla 0 (el 17)
    // - end():   casilla 5 (UN PASO DESPUES DEL 31, no tocar con *)
    // - ++it:    avanza a la derecha
    for (auto it = x_vals.begin(); it != x_vals.end(); ++it) {
        std::cout << std::format("{:5d} ", *it);
    }
    std::cout << std::endl;
    //• "{:<5d}" -> Alinea el número a la izquierda ocupando 5 espacios (10   ).
    //• "{:^5d}" -> Centra el número en esos 5 espacios ( 10)

    // -------------------------------------------------------------
    // PARTE B: Elegir donde empezar y donde acabar (Sub-rango)
    // Supongamos que solo queremos imprimir desde el indice 1 al 3: {23, 7, 11}
    // -------------------------------------------------------------
    std::cout << "\nB) Sub-rango (desde el indice 1 hasta antes del 4):\n";
    auto inicio = x_vals.begin() + 1; // Apunta al indice 1 (valor 23)
    auto fin    = x_vals.begin() + 4; // Apunta al indice 4 (limite de parada)

    for (auto it = inicio; it != fin; ++it) {
        std::cout << std::format("{:5d} ", *it);
    }
    std::cout << std::endl;

    // -------------------------------------------------------------
    // PARTE C: Recorrido Reverso (rbegin hasta rend) - PREGUNTA DE TU PC1
    // -------------------------------------------------------------
    std::cout << "\nC) Recorrido reverso (hacia atras):\n";
    // - rbegin(): apunta al ultimo elemento real (el 31)
    // - rend():   apunta UN PASO ANTES del primer elemento (muro de parada)
    // - ++it:     ¡REGLA DE ORO! ++ avanza hacia la izquierda en reversos
    for (auto it = x_vals.rbegin(); it != x_vals.rend(); ++it) {
        std::cout << std::format("{:5d} ", *it);
    }
    std::cout << std::endl;
}

void leccion_08_formas_de_inicializar() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 8: Formas de Inicializar Vectores" << std::endl;
    std::cout << "==================================================" << std::endl;
    // Forma 1: Por lista de valores
    std::vector<int> v1{10, 20, 30, 40, 50};
    // Forma 2: Con tamano especifico (se rellenan con ceros por defecto)
    std::vector<int> v2(v1.size()); // 5 ceros
    // Forma 3: Con tamano especifico y un valor inicial
    std::vector<int> v3(v1.size(), 7); // 5 sietes

    //// Para solo leer los elementos
    //for (auto n : numeros) {
    //    std::cout << n << " ";
    //}
    // Para modificar los elementos usando referencias (&)
    //for (auto& n : numeros) {
    //    n *= 2; // Duplica cada número dentro del vector
    //}

    std::cout << "v1 (valores dados): ";
    for (int x : v1) std::cout << x << " ";
    std::cout << std::endl;
    std::cout << "v2 (tamano 5 con ceros): ";
    for (int x : v2) std::cout << x << " ";
    std::cout << std::endl;
    std::cout << "v3 (tamano 5 con sietes): ";
    for (int x : v3) std::cout << x << " ";
    std::cout << std::endl;
    // Modificar v2 multiplicando v1 por v3 (como hizo tu profesor en clase):
    for (size_t i = 0; i < v1.size(); ++i) {
        v2[i] = v1[i] * v3.at(i);
    }
    std::cout << "v2 tras v1[i] * v3.at(i): ";
    for (int x : v2) std::cout << x << " ";
    std::cout << std::endl;
}
// ============================================================================
// LECCION 9: Control de Memoria: capacity, reserve, resize y shrink_to_fit
// ============================================================================
void leccion_09_control_memoria_y_capacidad() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 9: capacity, reserve, resize y shrink_to_fit" << std::endl;
    std::cout << "==================================================" << std::endl;
    std::vector<int> v;
    std::cout << "1. Vector vacio -> size: " << v.size()
              << ", capacity: " << v.capacity() << std::endl;
    // RESERVE: Reserva espacio en el Heap para 100 elementos por adelantado
    v.reserve(100);
    std::cout << "2. Tras reserve(100) -> size: " << v.size()
              << ", capacity: " << v.capacity() << " (size NO cambia!)" << std::endl;
    // push_back y emplace_back:
    v.push_back(10);
    v.emplace_back(20);
    std::cout << "3. Tras meter 2 elementos -> size: " << v.size()
              << ", capacity: " << v.capacity() << std::endl;
    // RESIZE: Crea elementos reales
    v.resize(5, 99); // Ahora habra 5 elementos en total (los nuevos tendran 99)
    std::cout << "4. Tras resize(5, 99) -> size: " << v.size()
              << ", capacity: " << v.capacity() << std::endl;
    std::cout << "   Elementos actuales: ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;
    // POP_BACK: Quita el ultimo
    v.pop_back();
    std::cout << "5. Tras pop_back() -> size: " << v.size()
              << ", capacity: " << v.capacity() << " (capacity no se reduce sola)" << std::endl;
    // SHRINK_TO_FIT: Libera el exceso de capacidad
    v.shrink_to_fit();
    std::cout << "6. Tras shrink_to_fit() -> size: " << v.size()
              << ", capacity: " << v.capacity() << " (capacidad ajustada al tamano exacto)" << std::endl;
}
// ============================================================================
// LECCION 10: insert(), erase() y clear() (Mover memoria en el medio)
// ============================================================================
void leccion_10_insert_erase_clear() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 10: insert(), erase() y clear()" << std::endl;
    std::cout << "==================================================" << std::endl;

    std::vector<int> v{10, 20, 30, 40, 50};
    std::cout << "Vector original: ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;

    // 1. INSERTAR UN SOLO ELEMENTO en el medio:
    // v.begin() + 2 es el casillero del 30.
    // Insertamos el 99 ahi (empuja al 30, 40, 50 a la derecha)
    v.insert(v.begin() + 2, 99);
    std::cout << "Tras insertar 99 en posicion 2: ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;

    // 2. INSERTAR TODO UN RANGO DE GOLPE (Como hizo tu profesor con un array):
    std::array<int, 3> extra{1000, 2000, 3000};
    // Insertamos todo el array al inicio (en v.begin()):
    v.insert(v.begin(), extra.begin(), extra.end());
    std::cout << "Tras insertar array al inicio: ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;

    // 3. ERASE: Borrar por rango [inicio, fin)
    // Borraremos los 3 elementos que acabamos de meter al inicio:
    v.erase(v.begin(), v.begin() + 3);
    std::cout << "Tras borrar los 3 primeros elementos: ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;

    // 4. CLEAR: Vaciar todo
    std::cout << "Antes de clear: size = " << v.size() << ", capacity = " << v.capacity() << std::endl;
    v.clear();
    std::cout << "Tras v.clear(): size = " << v.size() << ", capacity = " << v.capacity()
              << " (size pasa a 0, pero capacity SE CONSERVA!)" << std::endl;
}

// ============================================================================
// LECCION 11: Algoritmos de C++20 (copy con back_inserter, find, sort, ==)
// ============================================================================
void leccion_11_algoritmos_ranges() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 11: Algoritmos Modernos con <ranges>" << std::endl;
    std::cout << "==================================================" << std::endl;

    // 1. back_inserter: Copia de un array a un vector haciendo push_back solo
    const char* planetas_arr[] = {"Mercurio", "Venus", "Tierra", "Marte"};
    std::vector<std::string> planetas;

    std::ranges::copy(planetas_arr, std::back_inserter(planetas));

    std::cout << "Vector planetas tras copy con back_inserter: ";
    for (const auto& p : planetas) std::cout << p << " ";
    std::cout << std::endl;

    // 2. find: Buscar en el vector
    auto it_tierra = std::ranges::find(planetas, "Tierra");
    if (it_tierra != planetas.end()) {
        std::cout << "--> 'Tierra' ENCONTRADA en el vector: " << *it_tierra << std::endl;
    }

    // 3. sort: Ordenar alfabéticamente
    std::vector<std::string> copia = planetas;
    std::ranges::sort(copia);
    std::cout << "Vector ordenado con ranges::sort: ";
    for (const auto& p : copia) std::cout << p << " ";
    std::cout << std::endl;

    // 4. Comparación directa (operador ==):
    std::cout << "planetas == copia? " << (planetas == copia ? "IGUALES" : "DISTINTOS") << std::endl;
}

// ============================================================================
// LECCION 12: El Patron Erase-Remove vs std::erase (C++20)
// ============================================================================
void leccion_12_erase_remove_idiom() {
    std::cout << "\n==================================================" << std::endl;
    std::cout << "LECCION 12: Patron Erase-Remove vs std::erase" << std::endl;
    std::cout << "==================================================" << std::endl;

    constexpr double BASURA = -1.0;
    std::vector<double> v1{10.0, 20.0, BASURA, 30.0, BASURA, 40.0};
    std::vector<double> v2 = v1; // Copia para probar el metodo C++20

    std::cout << "Vector original v1: ";
    for (double x : v1) std::cout << x << " ";
    std::cout << " (size: " << v1.size() << ")" << std::endl;

    // METODO CLASICO: Erase-Remove Idiom
    // Paso 1: remove solo reordena, no cambia el size!
    auto sobrantes = std::ranges::remove(v1, BASURA);
    std::cout << "Tras ranges::remove -> size sigue siendo: " << v1.size() << " (NO se redujo!)" << std::endl;

    // Paso 2: erase borra fisicamente la cola de basura
    v1.erase(sobrantes.begin(), v1.end());
    std::cout << "Tras v1.erase()     -> size final: " << v1.size() << std::endl;
    std::cout << "Elementos de v1 limpios: ";
    for (double x : v1) std::cout << x << " ";
    std::cout << std::endl;

    // METODO MODERNO C++20: std::erase hace todo en 1 linea
    std::cout << "\nMetodo C++20 (std::erase directo):" << std::endl;
    auto eliminados = std::erase(v2, BASURA);
    std::cout << "Cantidad de elementos eliminados: " << eliminados << std::endl;
    std::cout << "Elementos de v2 limpios: ";
    for (double x : v2) std::cout << x << " ";
    std::cout << " (size: " << v2.size() << ")" << std::endl;
}

int main() {
    leccion_01_punteros_y_data();
    leccion_02_fill_vs_assign();
    leccion_03_sizes_y_sizeof();
    push_and_pop();
    leccion_04_empty_diferencia();
    leccion_05_acceso_y_seguridad();
    leccion_06_swap_memoria_y_complejidad();
    leccion_07_iteradores();
    leccion_08_formas_de_inicializar();
    leccion_09_control_memoria_y_capacidad();
    leccion_10_insert_erase_clear();
    leccion_11_algoritmos_ranges();
    leccion_12_erase_remove_idiom();

    return 0;
}