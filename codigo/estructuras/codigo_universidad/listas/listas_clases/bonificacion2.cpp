#include <iostream>
#include <vector>

/*
LeetCode 83 — Remove Duplicates from Sorted List (Easy)

Enunciado:
Dada la cabeza (head) de una lista enlazada ordenada, elimina todos los
duplicados de forma que cada elemento aparezca solo una vez.
Devuelve la lista, tambien ordenada.

Ejemplo 1:
  Entrada: head = [1,1,2]
  Salida:  [1,2]

Ejemplo 2:
  Entrada: head = [1,1,2,3,3]
  Salida:  [1,2,3]

Restricciones:
  - La cantidad de nodos esta en [0, 300]
  - -100 <= Node.val <= 100
  - La lista ya viene ordenada de menor a mayor
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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == nullptr) {
            // lista vacia
            return head;
        }

        ListNode* auxiliar = head;

        while(auxiliar->next != nullptr) {
            ListNode* siguiente = auxiliar->next;
            if(auxiliar->val == siguiente->val) {
                auxiliar->next = siguiente->next;
                delete siguiente;
                // dejamos auxiliar donde esta para comprobar el mismo valor hasta que pueda avanzar
            } else {
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
        {1, 1, 2},        // esperado: [1,2]
        {1, 1, 2, 3, 3},  // esperado: [1,2,3]
        {},               // esperado: []
        {1},              // esperado: [1]
    };

    for (const auto& caso : casos) {
        ListNode* resultado = Solution().deleteDuplicates(crearLista(caso));
        std::cout << "Resultado: ";
        imprimirLista(resultado);
        std::cout << "\n";
    }

    return 0;
}
