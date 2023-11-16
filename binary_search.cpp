#include <iostream>
#include <vector>

using namespace std;

int binary_search(const vector<int> arr, int x, int low, int high) {
    if ( low > high ) {
        return -1;
    }
    
    int mid = static_cast<int>((low + high) / 2);
    
    if (arr[mid] == x) {
        return mid;
    }
    
    if (arr[mid] > x) {
        return binary_search(arr, x, low, mid - 1);
    } else {
        return binary_search(arr, x, mid + 1, high);
    }
}

int main()
{
    std::cout << "data of array:" << std::endl;
    const vector<int> arr{ 1, 5, 7, 11, 12, 19, 22, 37, 42, 51, 56, 58, 64, 89, 1111 };
    for(auto& i: arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "data you want to search:" << std::endl;
    int x;
    std::cin >> x;
    int index = binary_search(arr, x, 0, arr.size() - 1);
    std::cout << "element is at the index of " << index << " of the array." << std::endl;

    return 0;
}
