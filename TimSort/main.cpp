#include <iostream>
#include "dl_list.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

class TimsortList : public List {
public:
    static const int MIN_MERGE = 64;
    static const int GALLOP_PARAM = 7;

    //Поиск minrun
    static int calculateMinRun(int n) {
        int r = 0;
        while (n >= MIN_MERGE) {
            r |= (n & 1);
            n >>= 1;
        }
        return n + r;
    }

    //Сортировка вставками
    static void insertionSort(TimsortList& arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i]->value;
            int j = i - 1;

            while (j >= left && arr[j]->value > key) {
                arr.swap(j + 1, j);
                j--;
            }
            arr[j + 1]->value = key;
        }
    }


    //Слияние подмассивов с ипользованием галопа
    static void merge(TimsortList& arr, int l, int m, int r) {
        int len1 = m - l + 1, len2 = r - m;
        TimsortList left, right;

        for (int i = 0; i < len1; i++) {
            left.append(arr[l + i]->value);
        }
        for (int j = 0; j < len2; j++) {
            right.append(arr[m + 1 + j]->value);
        }

        int i = 0, j = 0, k = l;

        // Добавляем режим галопа
        int gallopCount = 0;
        while (i < len1 && j < len2) {
            if (gallopCount == GALLOP_PARAM) {
                if (left[i]->value <= right[j]->value) {
                    arr[k++]->value = left[i++]->value;
                    if (i < len1) arr[k++]->value = left[i++]->value;
                }
                else {
                    i -= 2;
                    k -= 2;
                    gallopCount = 0;
                }
            }
            else if (left[i]->value <= right[j]->value) {
                arr[k++]->value = left[i++]->value;
                gallopCount++;
            }
            else {
                arr[k++]->value = right[j++]->value;
                gallopCount = 0;
            }
        }

        while (i < len1) {
            arr[k]->value = left[i]->value;
            i++;
            k++;
        }

        while (j < len2) {
            arr[k]->value = right[j]->value;
            j++;
            k++;
        }

    }

    //Сортировка расческой
    static void combSort(TimsortList& arr) {
        int n = arr.getSize();
        int gap = n;
        bool swapped = true;

        while (gap > 1 || swapped) {
            // Вычисляем новый размер шага
            gap = (gap * 10) / 13;
            if (gap < 1) {
                gap = 1;
            }

            swapped = false;

            for (int i = 0; i < n - gap; ++i) {
                if (arr[i]->value > arr[i + gap]->value) {
                    arr.swap(i, i + gap);
                    swapped = true;
                }
            }
        }
    }

    //TimSort
    static void timSort(TimsortList& arr, int n) {
        int minRun = calculateMinRun(MIN_MERGE);

        //Сортировка вставкой для маленьких подсписков (minrun)
        for (int i = 0; i < n; i += minRun) {
            insertionSort(arr, i, std::min(i + minRun - 1, n - 1));
        }
        //Слияние отсортированных подсписков
        for (int size = minRun; size < n; size = 2 * size) {
            for (int left = 0; left < n; left += 2 * size) {
                int mid = std::min(left + size - 1, n - 1);
                int right = std::min(left + 2 * size - 1, n - 1);
                merge(arr, left, mid, right);
            }
        }
    }
};


int main() {

    TimsortList list;
    srand(time(nullptr)); // инициализация генератора случайных чисел


    bool innerLoop = true;
    while (innerLoop) {
        std::system("cls");
        std::cout << "Menu:" << std::endl;
        std::cout <<
            "(1) - TimSort\n"
            "(2) - CombSort\n"
            "(0) - Quit\n\n";
        std::cout << "Action >> ";
        char choice;
        std::cin >> choice;
        switch (choice) {
        case '0': {
            innerLoop = false;
            break;
        }
        case '1': {
            system("cls");
            list.clear(); // Очищаем список
            for (int i = 0; i < 500; ++i) {
                list.append(rand() % 1000 - 500); // добавление случайного числа от -500 до 500
            }
            std::cout << "Original list: \n" << list << std::endl;

            auto startTime = std::chrono::high_resolution_clock::now();
            TimsortList::timSort(list, list.getSize());
            auto endTime = std::chrono::high_resolution_clock::now(); // Замер времени окончания
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime); // Разница во времени в миллисекундах

            std::cout << "\n_______________________________________________________\n";

            std::cout << "\nSorted list (Timsort with Galloping Mode): \n" << list << "\n\n";

            std::cout << "_______________________________________________________\n";

            std::cout << "Time =\t" << duration.count() << " milliseconds" << "\n\n";
            break;
        }
        case '2': {
            system("cls");
            list.clear(); // Очищаем список
            for (int i = 0; i < 500; ++i) {
                list.append(rand() % 1000 - 500); // добавление случайного числа от -500 до 500
            }
            std::cout << "Original list: " << list << std::endl;

            // Сортировка с помощью Comb Sort
            auto startTime1 = std::chrono::high_resolution_clock::now();
            TimsortList::combSort(list);
            auto endTime1 = std::chrono::high_resolution_clock::now(); // Замер времени окончания
            auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(endTime1 - startTime1); // Разница во времени в миллисекундах

            std::cout << "\n_______________________________________________________\n";

            std::cout << "\nSorted list (Comb Sort): \n" << list << "\n\n";

            std::cout << "_______________________________________________________\n";

            std::cout << "Time =\t" << duration1.count() << " milliseconds" << "\n\n";
            break;
        }
        default:
            std::cout << "\nCommand with number " << choice << " does not exist.\n\n";
            break;
        }
        system("pause");
    }
}