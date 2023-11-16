#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int partition(vector<int> & arr, int low, int high) {
    int i = (low - 1);      // index of smaller element
    int pivot = arr[high];  // pivot element
    std::cout << "low:" << low << ", high:" << high;
    
    for(int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i += 1;         // increase index of smaller element
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            std::cout << ", arr[" << j << "] <===> arr[" << i << "]";
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    std::cout << ", arr[" << (i+1) << "] <===> arr[" << high << "], pivot_index:" << (i+1);
    std::cout << std::endl;
    return (i+1);
}

void quick_sort(vector<int> & arr, int low, int high) {
    if ( arr.size() <= 1 || low >= high) {
        return;
    }
    
    std::cout << std::endl;
    for(auto& i: arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    int pivot_index = partition(arr, low, high);
    for(auto& i: arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;
    quick_sort(arr, low, pivot_index - 1);
    quick_sort(arr, pivot_index + 1, high);
}

int main()
{
    std::cout << "Before sorting:" << std::endl;
    vector<int> arr{ 37, 42, 15, 86, 57, 69, 21, 49, 88, 64, 98, 72, 2, 8, 6, 7, 1, 3 };
    for(auto& i: arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    quick_sort(arr, 0, arr.size() - 1);
    
    std::cout << "After sorting:" << std::endl;
    for(auto& i: arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
