#include <iostream>
#include <vector>

/*
LeetCode 24 — Swap Nodes in Pairs (Medium)

Enunciado:
Dada una lista enlazada, intercambia cada par de nodos adyacentes y
devuelve su cabeza. Debes resolverlo sin modificar los valores de los
nodos: solo se pueden cambiar los nodos en si.

Ejemplo 1:
  Entrada: head = [1,2,3,4]
  Salida:  [2,1,4,3]

Ejemplo 2:
  Entrada: head = []
  Salida:  []

Ejemplo 3:
  Entrada: head = [1]
  Salida:  [1]

Restricciones:
  - La cantidad de nodos esta en [0, 100]
  - 0 <= Node.val <= 100
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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        ListNode* nuevaCabeza = head->next;
        ListNode* anterior = nullptr;
        ListNode* auxiliar = head;

        while (auxiliar != nullptr && auxiliar->next != nullptr) {
            ListNode* siguiente = auxiliar->next;
            ListNode* proximo = siguiente->next;

            if (anterior != nullptr) {
                anterior->next = siguiente;
            }
            siguiente->next = auxiliar;
            auxiliar->next = proximo;

            anterior = auxiliar;
            auxiliar = proximo;
        }
        return nuevaCabeza;
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
        {1, 2, 3, 4},  // esperado: [2,1,4,3]
        {},            // esperado: []
        {1},           // esperado: [1]
        {1, 2, 3},     // esperado: [2,1,3]
    };

    for (const auto& caso : casos) {
        ListNode* resultado = Solution().swapPairs(crearLista(caso));
        std::cout << "Resultado: ";
        imprimirLista(resultado);
        std::cout << "\n";
    }

    return 0;
}
