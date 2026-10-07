#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <format> // C++20 para std::format

// ============================================================================
// 00 RECURSOS: FUNDAMENTOS Y HERRAMIENTAS QUE APARECEN EN TU CODIGO DE CLASE
// ============================================================================

// ----------------------------------------------------------------------------
// TEMA 1: TEMPLATES (template<typename T>)
// ¿Que significa y por que tu profesor lo pone en Swap y en print_container?
// ----------------------------------------------------------------------------
/*
 * Un TEMPLATE es una PLANTILLA o MOLDE.
 * En C normal, si querias intercambiar dos enteros tenias que hacer SwapInt(int&, int&),
 * si querias doubles SwapDouble(double&, double&), etc.
 * Con template<typename T>, la letra "T" representa CUALQUIER tipo que le pases:
 * int, double, string, vector, etc.
 * C++ genera automaticamente la funcion correcta en tiempo de compilacion.
 */
template<typename T>
void mi_swap(T& a, T& b) {
    T temporal = a;
    a = b;
    b = temporal;
}

// Template para imprimir cualquier contenedor (como helpers.h de tu profesor):
template<typename T>
void imprimir_cualquier_cosa(const char* titulo, const T& contenedor) {
    std::cout << titulo << ": ";
    for (const auto& elemento : contenedor) {
        std::cout << elemento << " ";
    }
    std::cout << std::endl;
}

void leccion_01_templates() {
    std::cout << "\n--- RECURSO 1: Templates (template<typename T>) ---" << std::endl;

    int x = 5, y = 10;
    std::cout << "Antes de mi_swap (enteros): x = " << x << ", y = " << y << std::endl;
    mi_swap(x, y); // C++ deduce que T = int
    std::cout << "Despues de mi_swap:         x = " << x << ", y = " << y << std::endl;

    std::string s1 = "Hola", s2 = "Mundo";
    std::cout << "\nAntes de mi_swap (strings): s1 = " << s1 << ", s2 = " << s2 << std::endl;
    mi_swap(s1, s2); // C++ deduce que T = std::string
    std::cout << "Despues de mi_swap:         s1 = " << s1 << ", s2 = " << s2 << std::endl;

    std::vector<int> v{1, 2, 3};
    imprimir_cualquier_cosa("Probando template con vector", v);
}

// ----------------------------------------------------------------------------
// TEMA 2: PASO DE PARAMETROS (Valor vs Referencia vs Referencia Constante)
// ----------------------------------------------------------------------------
/*
 * 1. Por Valor: void foo(int a)
 *    Saca una FOTOCOPIA del dato. Si modificas "a", el original no cambia.
 *    En cosas pesadas (como vectores) gasta mucha memoria y tiempo copiando.
 *
 * 2. Por Referencia: void foo(int& a)  (El ampersand &)
 *    Pasa el OBJETO REAL (un alias o puntero oculto).
 *    Si modificas "a", modificas el original. Ideal para Swap o para modificar.
 *
 * 3. Por Referencia Constante: void foo(const std::vector<int>& v)
 *    NO saca fotocopia (super rapido), pero la palabra "const" PROTEGE el dato:
 *    el compilador no deja que la funcion modifique el vector original.
 */
void duplicar_por_referencia(int& numero) {
    numero *= 2; // Modifica la variable original
}

void leccion_02_paso_parametros() {
    std::cout << "\n--- RECURSO 2: Paso por Referencia (&) vs Valor ---" << std::endl;
    int nota = 10;
    std::cout << "Nota original: " << nota << std::endl;
    duplicar_por_referencia(nota);
    std::cout << "Nota tras duplicar_por_referencia(nota): " << nota << " (Modificada con exito!)" << std::endl;
}

// ----------------------------------------------------------------------------
// TEMA 3: auto vs auto& vs const auto& (En bucles for)
// ----------------------------------------------------------------------------
/*
 * - for (auto x : vec)        -> Saca una COPIA de cada elemento en cada vuelta.
 * - for (auto& x : vec)       -> Lee la casilla real (permite modificar elementos).
 * - for (const auto& x : vec) -> Lee directamente SIN copiar y SIN riesgo de modificar.
 *                                (Es el mas eficiente y el estandar en C++ moderno).
 */
void leccion_03_auto_en_bucles() {
    std::cout << "\n--- RECURSO 3: auto, auto& y const auto& ---" << std::endl;
    std::vector<int> nums{1, 2, 3, 4, 5};

    // Usando auto& para modificar todos sumandoles 10:
    for (auto& n : nums) {
        n += 10; // Modifica directamente en el vector
    }

    std::cout << "Vector tras for con auto&: ";
    // Usando const auto& para leer rapido sin modificar:
    for (const auto& n : nums) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

// ----------------------------------------------------------------------------
// TEMA 4: std::format (C++20) y sus especificadores
// ----------------------------------------------------------------------------
/*
 * En tu codigo el profesor usa: std::format("{:5d}", val) o std::format("{:s}", cond).
 *
 * {}       -> Formato normal por defecto.
 * {:5d}    -> Entero ('d' de decimal) ocupando un ancho minimo de 5 caracteres
 *             (rellena con espacios a la izquierda para alinear columnas).
 * {:6d}    -> Entero ocupando ancho de 6 espacios.
 * {:.2f}   -> Decimal ('f' de float/double) con exactamente 2 decimales.
 * {:s}     -> String o booleano formateado como texto.
 */
void leccion_04_formato_std_format() {
    std::cout << "\n--- RECURSO 4: std::format (C++20) ---" << std::endl;

    int id = 7;
    double precio = 19.5;
    bool aprobado = true;

    // Alinear numeros en columnas ordenadas:
    std::cout << std::format("Alineado {:5d} | {:5d} | {:5d}", 1, 23, 456) << std::endl;
    std::cout << std::format("Alineado {:5d} | {:5d} | {:5d}", 7890, 12, 3) << std::endl;

    // Formatear decimales y booleanos:
    std::cout << std::format("ID: {:04d}, Precio: ${:.2f}, Aprobado: {:s}", id, precio, aprobado) << std::endl;
}

// ----------------------------------------------------------------------------
// TEMA 5: constexpr vs const (Constantes en compilacion)
// ----------------------------------------------------------------------------
/*
 * En tu codigo el profe escribe: constexpr size_t n{10};
 *
 * - const: Variable de solo lectura. Su valor puede conocerse al ejecutar.
 * - constexpr: Expresion constante calculada en TIEMPO DE COMPILACION.
 *   El procesador ni siquiera gasta tiempo calculandolo en ejecucion;
 *   el compilador reemplaza directamente el valor en el codigo maquina.
 */
void leccion_05_constexpr() {
    std::cout << "\n--- RECURSO 5: constexpr ---" << std::endl;
    constexpr size_t TAMANO_MAX{10};
    constexpr double VALOR_INVALIDO{-1.0};

    std::cout << "Constantes en compilacion: TAMANO_MAX = " << TAMANO_MAX 
              << ", VALOR_INVALIDO = " << VALOR_INVALIDO << std::endl;
}

// ----------------------------------------------------------------------------
// TEMA 6: static en funciones de archivo
// ----------------------------------------------------------------------------
/*
 * ¿Por que tu profesor pone "static void vector_example_1()"?
 *
 * La palabra "static" fuera de una clase (a nivel de archivo) significa
 * ENLACE INTERNO (Internal Linkage).
 * Le dice al compilador: "Esta funcion SOLO existe dentro de este archivo .cpp".
 * Si en otro archivo .cpp tienes una funcion con el mismo nombre, no habra choque
 * ni error de linkeo.
 */
static void funcion_privada_del_archivo() {
    std::cout << "Funcion protegida para este archivo .cpp con 'static'." << std::endl;
}

// ----------------------------------------------------------------------------
// TEMA 7: Directivas del Preprocesador (#ifdef, #ifndef, #define, #endif)
// ----------------------------------------------------------------------------
/*
 * En 04_DEQUES el profesor puso:
 *   #ifdef __cpp_lib_containers_ranges
 *       d1.append_range(array1);
 *   #else
 *       d1.insert(d1.end(), ...);
 *   #endif
 *
 * ¿Que es? Son ordenes para el PREPROCESADOR (antes de compilar):
 * - #ifdef NOMBRE: "¿Existe esta caracteristica en el compilador?"
 *   Si existe (C++23), compila la linea con append_range.
 * - #else: Si no existe (C++20), compila la linea alternativa con insert().
 *
 * Y en helpers.h:
 *   #ifndef INC_HELPERS_H
 *   #define INC_HELPERS_H
 *   ...
 *   #endif
 * Se llaman "Include Guards": evitan que un archivo de cabecera (.h) se
 * incluya dos veces y duplique codigo.
 */

// ============================================================================
// MAIN: Ejecuta todas las herramientas
// ============================================================================
int main() {
    std::cout << "==================================================" << std::endl;
    std::cout << "   00 RECURSOS: BUILDING BLOCKS & HERRAMIENTAS   " << std::endl;
    std::cout << "==================================================" << std::endl;

    leccion_01_templates();
    leccion_02_paso_parametros();
    leccion_03_auto_en_bucles();
    leccion_04_formato_std_format();
    leccion_05_constexpr();
    funcion_privada_del_archivo();

    return 0;
}
