
#ifndef TASKEXCHANGE_H
#define TASKEXCHANGE_H

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

/*
 * Перестановки
 * Выведите число перестановок P(n).
 *
 * ФОРМАТ ВВОДА:
 * В первой строке находится одно число nn (1≤n≤7)(1≤n≤7).
 */

#include <iostream>
void task1(){
    int n, count = 1;
    std::cin >> n;
    while (n != 1){
        count *= n;
        n--;
    }
    std::cout << count;
}

/*
 * Задано nn интервалов. Требуется найти максимальное количество взаимно непересекающихся интервалов.
 * Два интервала пересекаются, если они имеют хотя бы одну общую точку.
 *
 * ФОРМАТ ВВОДА:
 * В первой строке задано одно число nn (1≤n≤100)(1≤n≤100) — количество интервалов.
 * В следующих nn строках заданы интервалы l_i,r_i,l_i​,r_i​ (1≤l_i≤r_i≤50)(1≤l_i​≤r_i​≤50).
 */

bool compare(std::pair<int, int>& lhs, std::pair<int, int>& rhs){
    return lhs.second < rhs.second;
}

void task2(){
    int n, minRline, minLline, count = 1;
    std::cin >> n;
    std::vector<std::pair<int, int>> lines(n);
    for (int i = 0; i < n; i++) std::cin >> lines[i].first >> lines[i].second;

    std::sort(lines.begin(), lines.end(), compare);

    if(n > 0){
        minLline = lines[0].first;
        minRline = lines[0].second;
    }
    for(int i = 1; i < lines.size(); i++){
        if( (minLline < lines[i].second) && (minRline < lines[i].first)){
            count++;
            minLline = lines[i].first;
            minRline = lines[i].second;
        }
    };

    std::cout << count;
}



#endif // TASKEXCHANGE_H
