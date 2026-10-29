# Algoritmos y Estructura de Datos Avanzadas — CC232 / SW305

**Universidad Nacional de Ingeniería (UNI) — Facultad de Ingeniería Industrial y de Sistemas (FIIS)**  
**Semestre:** 2026-II  
**Profesor:** Ing. Ronald Ricardo Martinez Chunga  

Repositorio de estudio y código de clase para el curso de Algoritmia y Estructura de Datos Avanzadas.

---

## Estructura de Módulos del Proyecto

| Carpeta | Tema / Contenido | Conceptos Clave Evaluados |
| :--- | :--- | :--- |
| `00_recursos` | Recursos transversales y utilidades | `auto`, templates genéricos, `std::format`, idioms de C++20 |
| `01_Buildingblocks` | Bloques fundamentales & Helpers | `Helpers.h` (`print_container`, `print_map`, `print_multimap`), `Swap`, templates de función |
| `02_Array` | Arreglos de tamaño estático (`std::array`) | Acceso seguro `.at()`, iteradores directos y reversos (`rbegin`/`rend`), cálculo con `std::numbers::pi`, ordenamiento `std::sort` y comparaciones |
| `03_vectors` | Arreglos dinámicos en Heap (`std::vector`) | Constructores `() ` vs `{}`, `front()`/`back()`, inserciones y borrado de rangos, `std::ranges::copy` con `back_inserter`, `emplace_back`, patrón **Erase-Remove** vs `std::erase` |
| `04_DEQUES` | Colas de doble extremo (`std::deque`) | Memoria por bloques fragmentados (*chunks*), inserción en extremos $O(1)$ (`push_front`/`push_back`), ordenamiento lexicográfico, `ranges::sort` con `std::greater`, Erase-Remove |
| `06_Lists` | Listas doblemente enlazadas (`std::list`) | Nodos dispersos en Heap, `push_front`/`push_back`, inserción con `std::advance`, `remove` por valor vs `remove_if` con predicado lambda, `splice()` $O(1)$ sin copia, `.sort()` propio, `merge()` y `reverse()` |
| `06_Set` | Conjuntos ordenados (`std::set`, `std::multiset`) | Árboles balanceados (Red-Black), claves únicas vs duplicadas, inserción retornando `pair<iterator, bool>`, orden descendente con `std::greater`, `contains()` (C++20), `find()` y `erase()`, `merge()` de sets, `count()` en multiset |
| `07_Map` | Diccionarios asociativos ordenados (`std::map`) | Parejas clave-valor (`std::pair`), `operator[]` (lectura, modificación e inserción automática), `.at()` con lanzamiento de `std::out_of_range`, eliminación con `.erase(key)` y `.clear()` |

---

## Módulos de Repaso Personal y Simulacros
- `03_repaso`: Prácticas y ejercicios de refuerzo de vectores.
- `04_repaso_deques`: Ejercicios de repaso para deques.
- `06_repaso_listas`: Ejercicios de repaso para listas enlazadas.
- `PPTS/`: Contiene los simulacros de examen (30 y 100 preguntas) y el compendio teórico de ADT en PDF.
