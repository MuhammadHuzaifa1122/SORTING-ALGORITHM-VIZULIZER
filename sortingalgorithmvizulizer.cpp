#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;

void printHeader();
void loader();
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int RED = 4;
int GREEN = 10;
int YELLOW = 6;
int BLUE = 9;
int CYAN = 11;
int WHITE = 7;
bool VISUALIZE = false;
long long SWAPS = 0;
long long COMPARISONS = 0;
void setConsoleColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int sortingAlgorithms();
int dataShape();
void bubbleSort(int arr[], int size);
void bubbleSortPure(int arr[], int size);
void selectionSort(int arr[], int size);
void scenario(int option);
void mergeSortWrapper(int arr[], int size);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void quickSort(int arr[], int low, int high);
int division(int arr[], int low, int high);
void quickSortWrapper(int arr[], int size);
void printArray(int arr[], int size, int changeIndex = -1);
void selectionSortPure(int arr[], int size);
void mergePure(int arr[], int l, int m, int r);
void mergeSortPure(int arr[], int l, int r);
int partitionPure(int arr[], int low, int high);
void quickSortPure(int arr[], int low, int high);
void printComparisonTable(int arr[], int size);
void showTimeComplexities();

int main()
{
    double timeTakenInSelectionSort, timeTakenInBubbleSort, timeTakenInMergeSort, timeTakenInQuickSort;
    system("cls");
    loader();
    system("cls");
    printHeader();
    srand(time(0));
    while (true)
    {
        int max = 100000, size;
        setConsoleColor(CYAN);
        cout << "Enter the size of the array: ";
        setConsoleColor(WHITE);
        cin >> size;
        if (size > max)
        {
            setConsoleColor(RED);
            cout << "Max size is " << max << endl;
            setConsoleColor(WHITE);
            continue;
        }

        int arr[max];
        while (true)
        {
            int option = dataShape();
            system("cls");
            printHeader();
            if (option == 1)
            {
                for (int i = 0; i < size; i++)
                {
                    arr[i] = rand() % 100;
                }
                setConsoleColor(YELLOW);
                cout << "Average Case: Random Array" << endl;
                setConsoleColor(WHITE);
                cout << "Press any key to continue..." << endl;
                getch();
            }
            else if (option == 2)
            {
                for (int i = 0; i < size; i++)
                {
                    arr[i] = i + 1;
                }
                setConsoleColor(GREEN);
                cout << "Best Case: Sorted Array" << endl;
                setConsoleColor(WHITE);
                cout << "Press any key to continue..." << endl;
                getch();
            }
            else if (option == 3)
            {
                for (int i = 0; i < size; i++)
                {
                    arr[i] = i + 1;
                }
                for (int i = 0; i < size / 5; i++)
                {
                    int x = rand() % size;
                    int y = rand() % size;
                    swap(arr[x], arr[y]);
                }
                setConsoleColor(YELLOW);
                cout << "Nearly Sorted Array (Approx. Average Case)" << endl;
                setConsoleColor(WHITE);
                cout << "Press any key to continue..." << endl;
                getch();
            }
            else if (option == 4)
            {
                for (int i = 0; i < size; i++)
                {
                    arr[i] = size - i;
                }
                setConsoleColor(RED);
                cout << "Worst Case: Reverse Array" << endl;
                setConsoleColor(WHITE);
                cout << "Press any key to continue..." << endl;
                getch();
            }
            else if (option == 5)
            {
                setConsoleColor(YELLOW);
                cout << "Enter " << size << " elements of the array separated by space: ";
                setConsoleColor(WHITE);
                for (int i = 0; i < size; i++)
                    cin >> arr[i];
                setConsoleColor(GREEN);
                cout << "Custom array received!" << endl;
                setConsoleColor(WHITE);
                cout << "Press any key to continue..." << endl;
                getch();
            }
            else if (option == 6)
            {
                int minVal, maxVal;
                setConsoleColor(CYAN);
                cout << "Enter minimum value: ";
                setConsoleColor(WHITE);
                cin >> minVal;
                setConsoleColor(CYAN);
                cout << "Enter maximum value: ";
                setConsoleColor(WHITE);
                cin >> maxVal;

                for (int i = 0; i < size; i++)
                {
                    arr[i] = minVal + rand() % (maxVal - minVal + 1);
                }
                setConsoleColor(YELLOW);
                cout << "Random array generated with range [" << minVal << ", " << maxVal << "]" << endl;
                setConsoleColor(WHITE);
                cout << "Press any key to continue..." << endl;
                getch();
            }

            else if (option == 7)
            {
                return 0;
            }
            else
            {
                setConsoleColor(RED);
                cout << "Invalid Option!" << endl;
                cout << "Press any key to continue..." << endl;
                getch();
                setConsoleColor(WHITE);
                continue;
            }
            int option1;
            while (true)
            {
                option1 = sortingAlgorithms();
                system("cls");
                printHeader();
                if (option1 == 1)
                {
                    int *temp = new int[size];
                    for (int i = 0; i < size; i++)
                        temp[i] = arr[i];

                    scenario(option);

                    int runs = (size > 1000) ? 1 : 100;
                    clock_t start = clock();
                    for (int i = 0; i < runs; i++)
                    {
                        for (int j = 0; j < size; j++)
                            temp[j] = arr[j];

                        selectionSortPure(temp, size);
                    }
                    clock_t end = clock();
                    delete[] temp;
                    timeTakenInSelectionSort = double(end - start) / CLOCKS_PER_SEC / runs;

                    setConsoleColor(GREEN);
                    cout << fixed << setprecision(6) << "Time taken by Selection Sort: " << timeTakenInSelectionSort << " seconds" << endl;
                    setConsoleColor(WHITE);

                    cout << "Press any key to continue..." << endl;
                    getch();

                    cout << "Enable visualization? (1 = Yes, 0 = No): ";
                    cin >> VISUALIZE;

                    if (VISUALIZE && size <= 100)
                    {
                        SWAPS = 0;
                        COMPARISONS = 0;
                        selectionSort(arr, size);
                        setConsoleColor(CYAN);
                        cout << "Total Comparisons: " << COMPARISONS << endl;
                        cout << "Total Swaps: " << SWAPS << endl;
                        setConsoleColor(WHITE);
                        getch();
                    }
                    else if (VISUALIZE)
                    {
                        cout << "Size too big for vizulization!" << endl;
                        cout << "Press any key to continue..." << endl;
                        getch();
                    }
                }

                else if (option1 == 2)
                {
                    int *temp = new int[size];
                    for (int i = 0; i < size; i++)
                        temp[i] = arr[i];

                    scenario(option);
                    int runs = (size > 1000) ? 1 : 2000;

                    clock_t start = clock();
                    for (int i = 0; i < runs; i++)
                    {

                        for (int j = 0; j < size; j++)
                            temp[j] = arr[j];

                        bubbleSortPure(temp, size);
                    }
                    clock_t end = clock();

                    delete[] temp;

                    timeTakenInBubbleSort = double(end - start) / CLOCKS_PER_SEC / runs;

                    setConsoleColor(GREEN);
                    cout << fixed << setprecision(6)
                         << "Time taken by Bubble Sort: " << timeTakenInBubbleSort << " seconds" << endl;
                    setConsoleColor(WHITE);

                    cout << "Press any key to continue..." << endl;
                    getch();

                    cout << "Enable visualization? (1 = Yes, 0 = No): ";
                    cin >> VISUALIZE;

                    if (VISUALIZE && size <= 100)
                    {
                        SWAPS = 0;
                        COMPARISONS = 0;
                        bubbleSort(arr, size);
                        setConsoleColor(CYAN);
                        cout << "Total Comparisons: " << COMPARISONS << endl;
                        cout << "Total Swaps: " << SWAPS << endl;
                        setConsoleColor(WHITE);
                        getch();
                    }
                    else if (VISUALIZE)
                    {

                        cout << "Size too big for visualization!" << endl;
                        cout << "Press any key to continue..." << endl;
                        getch();
                    }
                }

                else if (option1 == 3)
                {
                    int *temp = new int[size];
                    for (int i = 0; i < size; i++)
                        temp[i] = arr[i];

                    scenario(option);
                    int runs = 100;
                    clock_t start = clock();
                    for (int i = 0; i < runs; i++)
                        mergeSortPure(temp, 0, size - 1);
                    clock_t end = clock();
                    delete[] temp;
                    timeTakenInMergeSort = double(end - start) / CLOCKS_PER_SEC / runs;
                    setConsoleColor(GREEN);
                    cout << fixed << setprecision(6) << "Time taken by Merge Sort: " << timeTakenInMergeSort << " seconds" << endl;
                    setConsoleColor(WHITE);
                    cout << "Press any key to continue..." << endl;
                    getch();
                    cout << "Enable visualization? (1 = Yes, 0 = No): ";
                    cin >> VISUALIZE;
                    if (VISUALIZE && size <= 100)
                    {
                        SWAPS = 0;
                        COMPARISONS = 0;
                        mergeSortWrapper(arr, size);
                        setConsoleColor(CYAN);
                        cout << "Total Comparisons: " << COMPARISONS << endl;
                        cout << "Total Swaps: " << SWAPS << endl;
                        setConsoleColor(WHITE);
                        getch();
                    }
                    else if (VISUALIZE)
                    {
                        cout << "Size too big for visualization!" << endl;
                        cout << "Press any key to continue..." << endl;
                        getch();
                    }
                }
                else if (option1 == 4)
                {
                    int *temp = new int[size];
                    for (int i = 0; i < size; i++)
                        temp[i] = arr[i];
                    scenario(option);
                    int runs = (size > 1000) ? 1 : 2000;
                    clock_t start = clock();
                    for (int i = 0; i < runs; i++)
                    {
                        for (int j = 0; j < size; j++)
                            temp[j] = arr[j];

                        quickSortPure(temp, 0, size - 1);
                    }
                    clock_t end = clock();
                    double timeTakenInQuickSort = double(end - start) / CLOCKS_PER_SEC / runs;

                    delete[] temp;
                    setConsoleColor(GREEN);
                    cout << fixed << setprecision(6) << "Time taken by Quick Sort: " << timeTakenInQuickSort << " seconds" << endl;
                    setConsoleColor(WHITE);
                    cout << "Press any key to continue..." << endl;
                    getch();
                    cout << "Enable visualization? (1 = Yes, 0 = No): ";
                    cin >> VISUALIZE;
                    if (VISUALIZE && size <= 100)
                    {
                        quickSortWrapper(arr, size);
                        getch();
                    }
                    else if (VISUALIZE)
                    {
                        SWAPS = 0;
                        COMPARISONS = 0;
                        quickSortWrapper(arr, size);
                        setConsoleColor(CYAN);
                        cout << "Total Comparisons: " << COMPARISONS << endl;
                        cout << "Total Swaps: " << SWAPS << endl;
                        setConsoleColor(WHITE);
                        getch();
                    }
                }
                else if (option1 == 5)
                {
                    if (size > 10000)
                    {
                        setConsoleColor(RED);
                        cout << "Array too large for comparison table using O(n^2) sorts. Reduce size." << endl;
                        setConsoleColor(WHITE);
                        cout << "Press any key to continue..." << endl;
                        getch();
                    }
                    else
                    {
                        printComparisonTable(arr, size);
                        cout << "Press any key to continue..." << endl;
                        getch();
                    }
                }
                else if (option1 == 6)
                {
                    showTimeComplexities();
                }

                else if (option1 == 7)
                {
                    break;
                }
                else
                {
                    setConsoleColor(RED);
                    cout << "Invalid Option!" << endl;
                    cout << "Press any key to continue..." << endl;
                    getch();
                    setConsoleColor(WHITE);
                    continue;
                }
            }

            system("cls");
        }
    }
}

int dataShape()
{
    system("cls");
    printHeader();
    int option;
    setConsoleColor(CYAN);
    cout << "Select one of the following data shape." << endl;
    cout << "1. Random " << endl;
    cout << "2. Sorted " << endl;
    cout << "3. Nearly Sorted " << endl;
    cout << "4. Reverse " << endl;
    cout << "5. Custom Array (manual input)" << endl;
    cout << "6. Random Array with custom range" << endl;
    cout << "7. Exit " << endl;
    cout << "Enter Option: ";
    setConsoleColor(WHITE);
    cin >> option;
    return option;
}

int sortingAlgorithms()
{
    system("cls");
    printHeader();
    int option;
    setConsoleColor(CYAN);
    cout << "Select one of the following algorithms." << endl;
    cout << "1. Selection Sort " << endl;
    cout << "2. Bubble Sort " << endl;
    cout << "3. Merge Sort " << endl;
    cout << "4. Quick Sort " << endl;
    cout << "5. Comaparion table for above mentioned for different sorting algorithms" << endl;
    cout << "6. Show Time Complexity of Sorting Algorithms" << endl;
    cout << "7. Exit " << endl;
    cout << "Enter Option (1-7): ";
    setConsoleColor(WHITE);
    cin >> option;
    return option;
}

void printArray(int arr[], int size, int changeIndex)
{
    for (int i = 0; i < size; i++)
    {
        if (i == changeIndex)
        {
            setConsoleColor(RED);
            cout << arr[i] << " ";
        }
        else
        {
            setConsoleColor(WHITE);
            cout << arr[i] << " ";
        }
        Sleep(50);
    }
    setConsoleColor(WHITE);
    cout << endl;
}

void bubbleSort(int arr[], int size)
{
    setConsoleColor(YELLOW);
    cout << "Array before sorting" << endl;
    setConsoleColor(WHITE);
    printArray(arr, size);
    Sleep(500);

    clock_t sortStart = clock();
    for (int i = 0; i < size - 1; i++)
    {
        setConsoleColor(YELLOW);
        cout << "\n========== PASS " << i + 1 << " ==========" << endl;
        setConsoleColor(WHITE);
        Sleep(200);

        for (int j = 0; j < size - i - 1; j++)
        {
            system("cls");
            printHeader();
            setConsoleColor(YELLOW);
            cout << "Pass " << i + 1 << " | Comparing index " << j << " and " << j + 1 << endl;
            cout << "Values: " << arr[j] << " and " << arr[j + 1] << endl;
            setConsoleColor(WHITE);

            for (int k = 0; k < size; k++)
            {
                if (k == j || k == j + 1)
                {
                    setConsoleColor(RED);
                }
                cout << arr[k] << " ";
                setConsoleColor(WHITE);
                Sleep(40);
            }
            cout << endl;

            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                SWAPS++;
                setConsoleColor(GREEN);
                cout << "SWAPPED!" << endl;
                setConsoleColor(WHITE);
                Sleep(300);
            }
            else
            {
                setConsoleColor(CYAN);
                cout << "No swap needed" << endl;
                setConsoleColor(WHITE);
                Sleep(200);
            }
            COMPARISONS++;
        }
    }
    clock_t sortEnd = clock();
    double sortTime = double(sortEnd - sortStart) / CLOCKS_PER_SEC;

    system("cls");
    printHeader();
    setConsoleColor(YELLOW);
    cout << "Array after sorting:" << endl;
    setConsoleColor(GREEN);
    printArray(arr, size);
    setConsoleColor(CYAN);
    cout << "Actual Sorting Time (including visualization): " << sortTime << " seconds" << endl;
    setConsoleColor(WHITE);
    Sleep(500);
}

void mergeSortWrapper(int arr[], int size)
{
    setConsoleColor(YELLOW);
    cout << "Array before sorting:" << endl;
    setConsoleColor(WHITE);
    printArray(arr, size);
    Sleep(500);

    clock_t sortStart = clock();
    mergeSort(arr, 0, size - 1);
    clock_t sortEnd = clock();
    double sortTime = double(sortEnd - sortStart) / CLOCKS_PER_SEC;

    system("cls");
    printHeader();
    setConsoleColor(YELLOW);
    cout << "Array after sorting:" << endl;
    setConsoleColor(GREEN);
    printArray(arr, size);
    setConsoleColor(CYAN);
    cout << "Actual Sorting Time (including visualization): " << sortTime << " seconds" << endl;
    setConsoleColor(WHITE);
    Sleep(500);
}

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        COMPARISONS++;

        system("cls");
        printHeader();
        setConsoleColor(YELLOW);
        cout << "Merging indices [" << left << " - " << right << "]\n\n";

        for (int x = 0; x < right + 1; x++)
        {
            if (x == k)
                setConsoleColor(RED);
            else
                setConsoleColor(WHITE);

            cout << arr[x] << " ";
        }
        cout << endl;

        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];

        SWAPS++;
        Sleep(200);
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void selectionSort(int arr[], int size)
{
    setConsoleColor(YELLOW);
    cout << "Array before sorting" << endl;
    setConsoleColor(WHITE);
    printArray(arr, size);
    Sleep(500);

    clock_t sortStart = clock();
    for (int i = 0; i < size - 1; i++)
    {
        setConsoleColor(YELLOW);
        cout << "\n========== PASS " << i + 1 << " ==========" << endl;
        cout << "Finding minimum from index " << i << " to " << size - 1 << endl;
        setConsoleColor(WHITE);
        Sleep(200);

        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            COMPARISONS++;
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        system("cls");
        printHeader();
        setConsoleColor(YELLOW);
        cout << "Pass " << i + 1 << " | Min value " << arr[minIndex] << " at index " << minIndex << endl;
        cout << "Swapping index " << i << " (" << arr[i] << ") with index " << minIndex << " (" << arr[minIndex] << ")" << endl;
        setConsoleColor(WHITE);

        for (int k = 0; k < size; k++)
        {
            if (k == i || k == minIndex)
            {
                setConsoleColor(RED);
            }
            cout << arr[k] << " ";
            setConsoleColor(WHITE);
            Sleep(40);
        }
        cout << endl;

        swap(arr[i], arr[minIndex]);
        SWAPS++;
        setConsoleColor(GREEN);
        cout << "SWAPPED!" << endl;
        setConsoleColor(WHITE);
        Sleep(300);
    }
    clock_t sortEnd = clock();
    double sortTime = double(sortEnd - sortStart) / CLOCKS_PER_SEC;

    system("cls");
    printHeader();
    setConsoleColor(YELLOW);
    cout << "Array after sorting:" << endl;
    setConsoleColor(GREEN);
    printArray(arr, size);
    setConsoleColor(CYAN);
    cout << "Actual Sorting Time (including visualization): " << sortTime << " seconds" << endl;
    setConsoleColor(WHITE);
    Sleep(500);
}

void scenario(int option)
{
    system("cls");
    printHeader();
    if (option == 2)
    {
        setConsoleColor(GREEN);
        cout << "Best Case: Sorted Array" << endl;
    }
    if (option == 1)
    {
        setConsoleColor(YELLOW);
        cout << "Average Case: Random Array" << endl;
    }
    if (option == 4)
    {
        setConsoleColor(RED);
        cout << "Worst Case: Reverse Array" << endl;
    }
    if (option == 3)
    {
        setConsoleColor(YELLOW);
        cout << "Nearly Sorted Array (Approx. Average Case)" << endl;
    }
    setConsoleColor(WHITE);
    Sleep(500);
}

void quickSortWrapper(int arr[], int size)
{
    setConsoleColor(YELLOW);
    cout << "Array before sorting" << endl;
    setConsoleColor(WHITE);
    printArray(arr, size);
    Sleep(500);

    clock_t sortStart = clock();
    quickSort(arr, 0, size - 1);
    clock_t sortEnd = clock();
    double sortTime = double(sortEnd - sortStart) / CLOCKS_PER_SEC;

    system("cls");
    printHeader();
    setConsoleColor(YELLOW);
    cout << "Array after sorting" << endl;
    setConsoleColor(GREEN);
    printArray(arr, size);
    setConsoleColor(CYAN);
    cout << "Actual Sorting Time (including visualization): " << sortTime << " seconds" << endl;
    setConsoleColor(WHITE);
    Sleep(500);
}

int division(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        COMPARISONS++;

        system("cls");
        printHeader();
        setConsoleColor(YELLOW);
        cout << "Pivot: " << pivot << " (index " << high << ")\n\n";

        for (int x = 0; x <= high; x++)
        {
            if (x == j)
                setConsoleColor(CYAN);     
            else if (x == high)
                setConsoleColor(RED);      
            else
                setConsoleColor(WHITE);

            cout << arr[x] << " ";
        }
        cout << endl;

        Sleep(150);

        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
            SWAPS++;
        }
    }

    swap(arr[i + 1], arr[high]);
    SWAPS++;

    return i + 1;
}


void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = division(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void bubbleSortPure(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}
void selectionSortPure(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
}
void mergePure(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSortPure(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortPure(arr, left, mid);
        mergeSortPure(arr, mid + 1, right);
        mergePure(arr, left, mid, right);
    }
}
int partitionPure(int arr[], int low, int high)
{
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortPure(int arr[], int low, int high)
{
    int *stack = new int[high - low + 1];
    int top = -1;
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0)
    {
        high = stack[top--];
        low = stack[top--];
        int pi = partitionPure(arr, low, high);
        if (pi - 1 - low > high - (pi + 1))
        {
            if (low < pi - 1)
            {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }
            if (pi + 1 < high)
            {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
        }
        else
        {
            if (pi + 1 < high)
            {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
            if (low < pi - 1)
            {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }
        }
    }
    delete[] stack;
}
void printComparisonTable(int arr[], int size)
{
    int temp[100000];
    double timeSelection, timeBubble, timeMerge, timeQuick;

    for (int i = 0; i < size; i++)
        temp[i] = arr[i];
    clock_t start = clock();
    selectionSortPure(temp, size);
    clock_t end = clock();
    timeSelection = double(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++)
        temp[i] = arr[i];
    start = clock();
    bubbleSortPure(temp, size);
    end = clock();
    timeBubble = double(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++)
        temp[i] = arr[i];
    start = clock();
    mergeSortPure(temp, 0, size - 1);
    end = clock();
    timeMerge = double(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++)
        temp[i] = arr[i];
    start = clock();
    quickSortPure(temp, 0, size - 1);
    end = clock();
    timeQuick = double(end - start) / CLOCKS_PER_SEC;

    setConsoleColor(CYAN);
    cout << "-----------------------------------------" << endl;
    cout << "| Algorithm       | Time (seconds)      |" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "| Selection Sort  | " << fixed << setprecision(6) << timeSelection << "            |" << endl;
    cout << "| Bubble Sort     | " << fixed << setprecision(6) << timeBubble << "            |" << endl;
    cout << "| Merge Sort      | " << fixed << setprecision(6) << timeMerge << "            |" << endl;
    cout << "| Quick Sort      | " << fixed << setprecision(6) << timeQuick << "            |" << endl;
    cout << "-----------------------------------------" << endl;
    setConsoleColor(WHITE);
}
void showTimeComplexities()
{
    system("cls");
    printHeader();
    setConsoleColor(CYAN);
    cout << "-----------------------------------------------------------------" << endl;
    cout << "| Algorithm        | Best Case | Average Case | Worst Case      |" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "| Selection Sort   | ";
    setConsoleColor(RED);
    cout << "O(n^2)";
    setConsoleColor(RED);
    cout << "       | ";
    setConsoleColor(RED);
    cout << "O(n^2)";
    setConsoleColor(RED);
    cout << "       | ";
    setConsoleColor(RED);
    cout << "O(n^2)";
    setConsoleColor(CYAN);
    cout << "       |" << endl;
    cout << "| Bubble Sort      | ";
    setConsoleColor(GREEN);
    cout << "O(n)";
    setConsoleColor(WHITE);
    cout << "         | ";
    setConsoleColor(RED);
    cout << "O(n^2)";
    setConsoleColor(RED);
    cout << "       | ";
    setConsoleColor(RED);
    cout << "O(n^2)";
    setConsoleColor(CYAN);
    cout << "       |" << endl;
    cout << "| Merge Sort       | ";
    setConsoleColor(GREEN);
    cout << "O(n log n)";
    setConsoleColor(WHITE);
    cout << "   | ";
    setConsoleColor(WHITE);
    cout << "O(n log n)";
    setConsoleColor(WHITE);
    cout << "   | ";
    setConsoleColor(WHITE);
    cout << "O(n log n)";
    setConsoleColor(CYAN);
    cout << "   |" << endl;
    cout << "| Quick Sort       | ";
    setConsoleColor(GREEN);
    cout << "O(n log n)";
    setConsoleColor(WHITE);
    cout << "   | ";
    setConsoleColor(WHITE);
    cout << "O(n log n)";
    setConsoleColor(WHITE);
    cout << "   | ";
    setConsoleColor(RED);
    cout << "O(n^2)";
    setConsoleColor(CYAN);
    cout << "       |" << endl;

    cout << "-----------------------------------------------------------------" << endl;
    setConsoleColor(WHITE);
    cout << "Press any key to return..." << endl;
    getch();
}

void printHeader()
{
    setConsoleColor(CYAN);
    SetConsoleOutputCP(CP_UTF8);
    setConsoleColor(6);
    cout << endl;
    cout << "  █████████    █████████   █████   █████" << endl;
    cout << " ███░░░░░███  ███░░░░░███ ░░███   ░░███ " << endl;
    cout << "░███    ░░░  ░███    ░███  ░███    ░███ " << endl;
    cout << "░░█████████  ░███████████  ░███    ░███ " << endl;
    cout << " ░░░░░░░░███ ░███░░░░░███  ░░███   ███  " << endl;
    cout << " ███    ░███ ░███    ░███   ░░░█████░   " << endl;
    cout << "░░█████████  █████   █████    ░░███     " << endl;
    cout << " ░░░░░░░░░  ░░░░░   ░░░░░      ░░░      " << endl
         << endl;
    cout << "==========================================" << endl;
    cout << "|      Sorting Algorithm Visualizer      |" << endl;
    cout << "==========================================" << endl
         << endl;

    setConsoleColor(7);
    setConsoleColor(WHITE);
}

void loader(){
    SetConsoleOutputCP(CP_UTF8);
    int x = 10;
    int y = 5;
    setConsoleColor(6);
    gotoxy(x, y);
    cout << "███████╗ ██████╗ ██████╗ ████████╗██╗███╗   ██╗ ██████╗                  " << endl;
    gotoxy(x, y + 1);
    cout << "██╔════╝██╔═══██╗██╔══██╗╚══██╔══╝██║████╗  ██║██╔════╝                  " << endl;
    gotoxy(x, y + 2);
    cout << "███████╗██║   ██║██████╔╝   ██║   ██║██╔██╗ ██║██║  ███╗                 " << endl;
    gotoxy(x, y + 3);
    cout << "╚════██║██║   ██║██╔══██╗   ██║   ██║██║╚██╗██║██║   ██║                 " << endl;
    gotoxy(x, y + 4);
    cout << "███████║╚██████╔╝██║  ██║   ██║   ██║██║ ╚████║╚██████╔╝                 " << endl;
    gotoxy(x, y + 5);
    cout << "╚══════╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝                  " << endl;
    gotoxy(x, y + 7);
    cout << " █████╗ ██╗      ██████╗  ██████╗ ██████╗ ██╗████████╗██╗  ██╗███╗   ███╗" << endl;
    gotoxy(x, y + 8);
    cout << "██╔══██╗██║     ██╔════╝ ██╔═══██╗██╔══██╗██║╚══██╔══╝██║  ██║████╗ ████║" << endl;
    gotoxy(x, y + 9);
    cout << "███████║██║     ██║  ███╗██║   ██║██████╔╝██║   ██║   ███████║██╔████╔██║" << endl;
    gotoxy(x, y + 10);
    cout << "██╔══██║██║     ██║   ██║██║   ██║██╔══██╗██║   ██║   ██╔══██║██║╚██╔╝██║" << endl;
    gotoxy(x, y + 11);
    cout << "██║  ██║███████╗╚██████╔╝╚██████╔╝██║  ██║██║   ██║   ██║  ██║██║ ╚═╝ ██║" << endl;
    gotoxy(x, y + 12);
    cout << "╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝     ╚═╝" << endl;
    gotoxy(x, y + 14);
    cout << "██╗   ██╗██╗███████╗██╗   ██╗ █████╗ ██╗     ██╗███████╗███████╗██████╗  " << endl;
    gotoxy(x, y + 15);
    cout << "██║   ██║██║██╔════╝██║   ██║██╔══██╗██║     ██║╚══███╔╝██╔════╝██╔══██╗ " << endl;
    gotoxy(x, y + 16);
    cout << "██║   ██║██║███████╗██║   ██║███████║██║     ██║  ███╔╝ █████╗  ██████╔╝ " << endl;
    gotoxy(x, y + 17);
    cout << "╚██╗ ██╔╝██║╚════██║██║   ██║██╔══██║██║     ██║ ███╔╝  ██╔══╝  ██╔══██╗ " << endl;
    gotoxy(x, y + 18);
    cout << " ╚████╔╝ ██║███████║╚██████╔╝██║  ██║███████╗██║███████╗███████╗██║  ██║ " << endl;
    gotoxy(x, y + 19);
    cout << "  ╚═══╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝╚══════╝╚══════╝╚═╝  ╚═╝" << endl;
    gotoxy(x, y + 21);
    setConsoleColor(7);
    cout << "Press any key to continue..." << endl;
    gotoxy(x, y + 22);
    getch();
}

