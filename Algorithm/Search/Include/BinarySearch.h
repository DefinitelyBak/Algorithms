#pragma once

#include "Precompile.h"


namespace Algorithm::Search
{
    /*
    Алгоритм:

    Идея поиска заключается в том, чтобы брать элемент посередине,
    между границами, и сравнивать его с искомым.
    Если искомое больше(в случае правостороннего — не меньше), чем элемент сравнения,
    то сужаем область поиска так, чтобы новая левая граница была равна индексу середины предыдущей области.
    В противном случае присваиваем это значение правой границе.
    Проделываем эту процедуру до тех пор,
    пока правая граница больше левой более чем на 1. 
     */
}