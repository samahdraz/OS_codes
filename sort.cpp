#include <iostream>
#include <vector>
#include <thread>

using namespace std;

vector <int> arr;

void readInput()
{
    FILE* input;
    input = freopen("Input1.txt","r",stdin);
    int arraySize,temp;

    cin >> arraySize;

    for(int i = 0; i < arraySize; i++){
        cin >> temp;
        arr.push_back(temp);
    }

    fclose(input);
}

void merge(int l, int m, int r)
{
    vector<int> temp;
    int i = l, j = m + 1;

    while(i <= m && j <= r)
        arr[i] < arr[j] ? temp.push_back(arr[i++]) : temp.push_back(arr[j++]);

    while(i <= m)
        temp.push_back(arr[i++]);

    while(j <= r)
        temp.push_back(arr[j++]);

    for(int i = 0; i < temp.size(); i++)
        arr[l + i] = temp[i];
}

void mergeSort(int l, int r)
{
    if(l < r)
    {
        int m = l + ( r - l ) / 2;

        thread t1{[&](){mergeSort(l, m);}};
        thread t2{[&](){mergeSort(m + 1, r);}};

        t1.join();
        t2.join();

        merge(l, m, r);
    }
}

void printArray()
{
    for(int num : arr)
        cout << num << " ";
}

int main()
{
    readInput();
    mergeSort(0, arr.size()-1);
    /*auto start = chrono::steady_clock::now();
    mergeSort(0, arr.size()-1);
    auto end = chrono::steady_clock::now();
    auto time = end - start;
    auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(time);
    std::cout << "Time taken: " << seconds.count() << " seconds" << std::endl;*/

    cout << "Sorted array:";
    printArray();

    

    return 0;
}
