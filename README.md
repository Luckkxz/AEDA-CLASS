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
| `01_Buildingblocks` | Bloques fundamentales & Helpers | `helpers.h` (`print_container`, `print_map`, `print_multimap`), `Swap`, templates de función |
| `02_Array` | Arreglos de tamaño estático (`std::array`) | Acceso seguro `.at()`, iteradores directos y reversos (`rbegin`/`rend`), cálculo con `std::numbers::pi`, ordenamiento `std::sort` y comparaciones |
| `03_vectors` | Arreglos dinámicos en Heap (`std::vector`) | Constructores `()` vs `{}`, `front()`/`back()`, inserciones y borrado de rangos, `std::ranges::copy` con `back_inserter`, `emplace_back`, patrón **Erase-Remove** vs `std::erase` |
| `04_DEQUES` | Colas de doble extremo (`std::deque`) | Memoria por bloques fragmentados (*chunks*), inserción en extremos $O(1)$ (`push_front`/`push_back`), ordenamiento lexicográfico, `ranges::sort` con `std::greater`, Erase-Remove |
| `06_Lists` | Listas doblemente enlazadas (`std::list`) | Nodos dispersos en Heap, `push_front`/`push_back`, inserción con `std::advance`, `remove` por valor vs `remove_if` con predicado lambda, `splice()` $O(1)$ sin copia, `.sort()` propio, `merge()` y `reverse()` |
| `06_Set` | Conjuntos ordenados (`std::set`, `std::multiset`) | Árboles balanceados (Red-Black), claves únicas vs duplicadas, inserción retornando `pair<iterator, bool>`, orden descendente con `std::greater`, `contains()` (C++20), `find()` y `erase()`, `merge()` de sets, `count()` en multiset |
| `07_Map` | Diccionarios asociativos ordenados (`std::map`, `std::multimap`) | Parejas clave-valor (`std::pair`), `operator[]` vs `.at()`, `try_emplace()` vs `emplace()`, claves `string_view`, `std::multimap` (mapeo uno a muchos), `equal_range()`, `count()`, `contains()` |
| `08_Unordered_Set` | Contenedores asociativos Hash (`std::unordered_set`) | Tablas hash con encadenamiento separado, inspección de cubos (`bucket_count`, `bucket_size`, `load_factor`), iteradores locales, `insert_range`, `merge()`, `contains()`, `extract()` con manipulación de Node Handles |

---

## Módulos de Repaso Didáctico Personal y Simulacros
- `03_repaso`: Prácticas y lecciones de refuerzo de `std::vector` (Lecciones 1 a 12).
- `04_repaso_deques`: Lecciones y ejercicios de `std::deque` (Lecciones 13 a 16).
- `06_repaso_listas`: Lecciones y ejercicios de `std::list` (Lecciones 17 a 21).
- `06_repaso_set`: Lecciones y trampas de examen de `std::set` y `std::multiset` (Lecciones 22 a 27).
- `07_repaso_map`: Lecciones y trampas de examen de `std::map`, `std::multimap`, `try_emplace()`, `equal_range()` y `string_view` (Lecciones 28 a 35).
- `08_repaso_unordered`: Lecciones 36 a 42:
  - **Semana 10 PPT**: Teoría de Árboles (altura, nivel, profundidad), BST y degeneración a $O(n)$, Árboles Balanceados AVL ($BF = h_L - h_R \in \{-1,0,+1\}$), rotaciones LL, RR, LR, RL y algoritmos, Red-Black Trees en C++ STL.
  - **Tablas Hash STL**: De $O(\log n)$ a $O(1)$ promedio, arquitectura de buckets, colisiones, factor de carga y rehashing, `extract()` con Node Handles (modificación segura de claves), y gran matriz comparativa de examen `std::set` vs `std::unordered_set`.
- `PPTS/`: Contiene los simulacros de examen (30 y 100 preguntas) y el compendio teórico de ADT en PDF.
