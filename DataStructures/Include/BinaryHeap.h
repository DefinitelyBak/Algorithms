#pragma once

#include "Precompile.h"


namespace DataStructures
{

    class BinaryHeap
    {
        public:

            int FindExtremum();

            void Push(int);

            int ExtractExtremum();

            void DeleteExtremu();

            void increaseKey();

            void decreaseKey();

            void Merge();

            
    };

}