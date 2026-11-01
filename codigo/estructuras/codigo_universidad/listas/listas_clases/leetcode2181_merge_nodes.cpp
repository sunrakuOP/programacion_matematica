#include <iostream>
#include <vector>

/*
LeetCode 2181 — Merge Nodes in Between Zeros (Medium)

Enunciado:
Te dan la cabeza (head) de una lista enlazada que contiene una serie de
enteros separados por ceros. El inicio y el final de la lista tienen
Node.val == 0.

Por cada dos ceros consecutivos, fusiona todos los nodos que estan entre
ellos en un solo nodo cuyo valor es la suma de los nodos fusionados.
La lista modificada no debe contener ceros.

Devuelve la cabeza de la lista modificada.

Ejemplo 1:
  Entrada: head = [0,3,1,0,4,5,2,0]
  Salida:  [4,11]
  Explicacion: 3 + 1 = 4 y 4 + 5 + 2 = 11

Ejemplo 2:
  Entrada: head = [0,1,0,3,0,2,2,0]
  Salida:  [1,3,4]

Restricciones:
  - El inicio y el final de la lista tienen Node.val == 0
  - 0 <= Node.val <= 1000
  - Hay al menos 3 nodos
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        ListNode* auxiliar = head;
        ListNode* anterior = nullptr;
        int suma = 0;

        while (auxiliar != nullptr) {
            ListNode* siguiente = auxiliar->next;
            if (auxiliar->val != 0) {
                suma += auxiliar->val;
                if (siguiente->val != 0) {
                    if (anterior == nullptr) {
                        head = siguiente;
                    } else {
                        anterior->next = siguiente;
                    }
                    delete auxiliar;
                    auxiliar = siguiente;
                } else {
                    auxiliar->val = suma;
                    suma = 0;
                    anterior = auxiliar;
                    auxiliar = siguiente;
                }
            } else {
                if (anterior == nullptr) {
                    head = siguiente;
                } else {
                    anterior->next = siguiente;
                }
                delete auxiliar;
                auxiliar = siguiente;
            }
        }
        return head;
    }
};













// ---------- Helpers para probar (no tocar) ----------

// Convierte un vector en una lista enlazada y devuelve su cabeza
ListNode* crearLista(const std::vector<int>& valores) {
    ListNode* cabeza = nullptr;
    for (int i = static_cast<int>(valores.size()) - 1; i >= 0; --i) {
        cabeza = new ListNode(valores[i], cabeza);
    }
    return cabeza;
}

// Imprime la lista con formato [a,b,c]
void imprimirLista(ListNode* cabeza) {
    std::cout << "[";
    for (ListNode* actual = cabeza; actual != nullptr; actual = actual->next) {
        std::cout << actual->val;
        if (actual->next != nullptr) std::cout << ",";
    }
    std::cout << "]";
}

int main() {
    std::vector<std::vector<int>> casos = {
        {0, 3, 1, 0, 4, 5, 2, 0},  // esperado: [4,11]
        {0, 1, 0, 3, 0, 2, 2, 0},  // esperado: [1,3,4]
        {0, 5, 0},                 // esperado: [5]
    };

    for (const auto& caso : casos) {
        ListNode* resultado = Solution().mergeNodes(crearLista(caso));
        std::cout << "Resultado: ";
        imprimirLista(resultado);
        std::cout << "\n";
    }

    return 0;
}
