//
// Created by 1 on 15.04.2023.
//

#include "bin_search.h"

int bin_search(int *mas, int lim, int element) {
    int low = 0, mid, high = lim - 1;

    while (low <= high) {
        mid = (int) ((low + high) / 2);

        if (element == mas[mid])
            return mid;

        if (element < mas[mid])
            high = mid - 1;
        else if (element > mas[mid])
            low= mid + 1;
    }
    return -1;
}

int bin_search_rec(int *mas, int low, int high, int element) {
    int mid = (int) (low + high) / 2;
    if (element == mas[mid])
        return (low + high) / 2;

    if (element < mas[mid])
        bin_search_rec(mas, low, mid - 1, element);
    else if (element > mas[mid])
        bin_search_rec(mas, mid + 1, high, element);
}
