#ifndef TASKSIVAN_H
#define TASKSIVAN_H

#include <cmath>
#include <list>
#include <unordered_map>
#include <exception>

#include <chrono>

#include <iostream>

/* Дано:
 *   массив int base[N]
 *   массив int* A[M], состоящий из int a_m[N]
 *   функция предикат funct(int, int)
 *
 *   Алгоритм проходит последовательно k : M раз по элементам base[i] и A[k][i], если
 *      funct(base[i], A[k][i]) == true, то erase base[i]
 *      funct(base[i], A[k][i]) == false, то erase A[k][i]
 *   Выше описанные действия повторяются i : N раз
 */


bool myPredicate(int lhs, int rhs){ return lhs < rhs;}

typedef  bool(*myPredicateType)(int lhs, int rhs);

// N - кол-во элементов в массивах A и Base (наименования взяты из условия задачи)
// M - кол-во массивов A

void taskIvan(std::list<std::unordered_map<int, int>>& listMapsA, std::unordered_map<int, int>& mapBase, myPredicateType funct){

    // Тут можно рассмотреть исключительные ситуации и выкидывать ошибку при нарушении условий задачи.

    auto iterBase = mapBase.begin();        // O(1) - T1;

    while (iterBase != mapBase.end()){      // Повторяется N раз
        bool statusDeleteBase = true;       // O(1) - T2;
        for ( auto& currentMap : listMapsA) // Повторояется M раз
        {
            if (funct(iterBase->second, currentMap[iterBase->first])){ // O(1) - T3;
                auto iterTemp = iterBase;   // O(1) - T4; Это необходимо, так как erase() удаляет элемент следовательно и итератор становиться не актуальным
                iterBase++;                 // O(1) - T5;
                mapBase.erase(iterTemp);    // O(1) - T6; erase() с итератором выполняется за const в среднем, в худешем случаи O(n);
                statusDeleteBase = false;   // O(1) - T7;
                break;                      // O(1) - T8;
            }
            else{
                currentMap.erase(iterBase->first); // O(1) - T9;
                    // В среднем выполняется как T(count(key)), худшем случаи: T(size()) = O(n);
                    // T(count(key)) = O(1) в среднем, в худешем O(n);
            }
        }

        if (statusDeleteBase) iterBase++;   // O(1) - T10;
                // От этого if не уйти, так как необходимо что бы iterBase увеличивался один раз внутри цикла while,
                // не красиво, согласен. Но выхода не вижу;
    }
}
/*
 * Прошу посмотри данные рассуждения, я возможно ошибся.
 *
 * ** T3 + T4 + T5 + T7 + T8 = O(1), T2 + T10 = O(1);
 * Рассмотрим случай при котором T6 = O(N) и T9 = O(N), тогда:
 * 1) T(taskIvan) = T1 + N*T2 + N*M*(T3 + T4 + T5 + T6 + T7 + T8) + N*T10 = N*M*( O(N) + O(1) ) + N*(O(1)) + O(1) ==
 *    == N*M*O(N) + N*M*O(1) + N*(O(1)) + O(1);
 *    допустим P = max(N, M), тогда:
 *    N*M*O(N) + N*M*O(1) + N*(O(1)) + O(1) = P*P*O(P) + O(P^2) + O(P) + O(1) = O(P^3) - done!
 *
 * 2) T(taskIvan) = T1 + N*T2 + N*M*(T9) + N*T10 = N*M*(O(N)) + N*(O(1)) + O(1)
 *    допустим P = max(N, M), тогда:
 *    P*P*O(P) + O(P) + O(1) = O(P^3) - done!
 */

void printListMaps(std::list<std::unordered_map<int, int>>& input){
    int count = 0;
    for(auto& map : input){
        std::cout << std::endl << "A[" << count << "]" << std::endl;
        for(auto& pair : map){
            std::cout << pair.first << " : " << pair.second <<std::endl;
        }
        count++;
    }
}

void printMap(std::unordered_map<int, int>& input){

    std::cout << std::endl << "B" << std::endl;
    for(auto& pair : input){
        std::cout << pair.first << " : " << pair.second <<std::endl;
    }
}

// Функция для тестирования taskIvan(), возвращает наносекунды.
std::atomic_int64_t test1(std::list<std::unordered_map<int, int>>& listMapsA, std::unordered_map<int, int>& mapBase, myPredicateType funct){

    auto begin = std::chrono::steady_clock::now();
    taskIvan(listMapsA, mapBase, funct);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    return elapsed_ns.count();
}
#endif // TASKSIVAN_H
