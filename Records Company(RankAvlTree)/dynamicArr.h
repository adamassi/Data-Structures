#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

#include <stdlib.h>

    const  int SHRINK_FACTOR = 2;
    const  int EXPAND_FACTOR = 2;
    const  int INITIAL_SIZE = 10;
    
    template <class T>
    struct DynArray
    {
        T *array;
         int size;
         int filled;
        // const  int expand_factor;

        explicit DynArray() : array(new T[INITIAL_SIZE]), size(INITIAL_SIZE), filled(0){};
        ~DynArray(){
            delete[] array; 
        }

        DynArray(const DynArray &other) : array(new T[other.size]), size(other.size),filled(other.filled){
             int i=0;
            while(i<other.filled){
                array[i] = other.array[i];
                i++;
            }
        }

        DynArray &operator=(const DynArray &other) = delete;

        T insert(const T &data){
            if (filled == size - 1)
            {
                T *new_array = new T[size * EXPAND_FACTOR];
                 int i = 0;
                while(i<filled){
                    new_array[i] = array[i]; 
                    i++;

                }
                delete[] array;
                array = new_array;
                size *= EXPAND_FACTOR;
            }
            array[filled] = data;
            filled++;
            return array[(filled-1)];
        }

        void remove_top()
    {
        delete array[filled-1];
        filled--;
        if (filled <= size / 4)
        {
            T *new_arr = new T[size / 2];
            for (int i = 0; i < filled; ++i)
                new_arr[i] = array[i];
            delete[] array;
            size = size / 2;
            array = new_arr;
        }
    }


        void clear() {
        filled = 0;
        size = INITIAL_SIZE;
        delete[] array;
        T *new_arr = new T[INITIAL_SIZE];
        array = new_arr;
    }
    };


#endif //DYNAMIC_ARR_H