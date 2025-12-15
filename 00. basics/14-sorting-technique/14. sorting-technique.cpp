#include <bits/stdc++.h>
using namespace std;

/* ------------------------------
   1. SELECTION SORT
   ------------------------------

   INTUITION
   ------------------------------
   - Think of the array as divided into two parts:
       1) Sorted part (begins empty)
       2) Unsorted part
   - In every step, you SELECT the smallest value from the
     unsorted part and put it in its correct position in the
     sorted part.
   - Sorted region grows from the left side.

   WHY THIS WORKS:
   - Smallest element MUST be placed at index 0.
   - Second smallest MUST be at index 1.
   - Continue this until array is sorted.

   ALGORITHM (Step-by-Step)
   -------------------------
   For i = 0 to n-2:
       1) minIndex = i
       2) Scan j = i+1 to n-1:
             if arr[j] < arr[minIndex]
                 minIndex = j
       3) Swap arr[i] with arr[minIndex]

   TIME COMPLEXITY:
   - Always O(N^2)

   SPACE COMPLEXITY:
   - O(1) in-place

   STABILITY:
   - Not stable (swap may break equal-order)
*/

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }

        swap(arr[i], arr[minIndex]);
    }
}

/*
DRY RUN
Array = [13, 46, 24, 52, 20, 9]

i=0 → minIndex after full scan = 5  
Swap arr[0], arr[5]  
→ [9,46,24,52,20,13]

i=1 → minIndex = 5  
→ [9,13,24,52,20,46]

i=2 → minIndex = 4  
→ [9,13,20,52,24,46]

i=3 → minIndex = 4  
→ [9,13,20,24,52,46]

i=4 → minIndex = 5  
→ [9,13,20,24,46,52]
*/



/* ------------------------------
   2. BUBBLE SORT
   ------------------------------

   INTUITION
   ----------
   - Adjacent values are compared.
   - Larger values "bubble up" toward the right end.
   - After each full pass, the largest unsorted value is settled.

   WHY THIS WORKS:
   - Each pass guarantees the next largest element moves to its
     correct final position.

   ALGORITHM
   ----------
   For i = 0 to n-2:
       swapped = false
       For j = 0 to n-i-2:
           If arr[j] > arr[j+1]:
               swap and mark swapped = true
       If no swap → array already sorted → break early

   TIME COMPLEXITY:
   - Worst and average O(N^2)
   - Best O(N) when array already sorted

   SPACE COMPLEXITY:
   - O(1)

   STABILITY:
   - Stable
*/

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {

        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

/*
DRY RUN
[13, 46, 24, 52, 20, 9]

Pass 1 → bubble largest (52) to end  
Pass 2 → bubble second-largest  
Pass 3 → continue until sorted  
Final → [9,13,20,24,46,52]
*/



/* ------------------------------
   3. INSERTION SORT
   ------------------------------

   INTUITION
   ----------
   - Left part of the array is considered sorted.
   - Current element (key) is inserted at the correct position in
     the left sorted region.

   REAL ANALOGY:
   - Like sorting playing cards in your hand one-by-one.

   ALGORITHM
   ----------
   For i = 1 to n-1:
       key = arr[i]
       j = i - 1
       while j >= 0 and arr[j] > key:
           arr[j+1] = arr[j]
           j--
       arr[j+1] = key

   TIME COMPLEXITY:
   - Best: O(N)
   - Worst: O(N^2)

   SPACE COMPLEXITY:
   - O(1)

   STABILITY:
   - Stable
*/

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {

        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  
            j--;
        }
        arr[j + 1] = key;
    }
}

/*
DRY RUN  
[13,46,24,52,20,9]

Insert 46 → correct  
Insert 24 → shift 46  
Insert 52 → correct  
Insert 20 → shift 52,46,24  
Insert 9 → shift everything  
Final → [9,13,20,24,46,52]
*/



/* ------------------------------
   4. MERGE SORT
   ------------------------------

   INTUITION
   ----------
   - Divide array into two halves recursively.
   - Sort each half.
   - Merge the two sorted halves using two-pointer technique.

   THE KEY INSIGHT:
   - Small sorted pieces can be merged efficiently.
   - Entire sorting comes from merging.

   ALGORITHM
   ----------
   mergeSort(arr, low, high):
       if low >= high: return
       mid = (low + high) / 2
       mergeSort(arr, low, mid)
       mergeSort(arr, mid+1, high)
       merge(arr, low, mid, high)

   merge(arr, low, mid, high):
       create temp[]
       left = low
       right = mid+1
       while left ≤ mid and right ≤ high:
           push smaller of arr[left], arr[right]
       push remaining left elements
       push remaining right elements
       copy temp back to arr

   TIME COMPLEXITY:
   - Always O(N log N)

   SPACE COMPLEXITY:
   - O(N) extra array

   STABILITY:
   - Stable
*/

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
        else temp.push_back(arr[right++]);
    }

    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = (low + high) / 2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}

/*
DRY RUN
Split → [13,46,24] and [52,20,9]
Sort left → [13,24,46]
Sort right → [9,20,52]
Merge → [9,13,20,24,46,52]
*/



/* ------------------------------
   5. QUICK SORT
   ------------------------------

   INTUITION
   ----------
   - Choose a pivot.
   - Partition array: elements smaller than pivot go left,
     greater go right.
   - Recursively sort left and right parts.

   WHY IT WORKS:
   - Partition ensures pivot is at its correct final position.

   ALGORITHM
   ----------
   partition(arr, low, high):
       pivot = arr[high]
       i = low-1
       for j = low to high-1:
           if arr[j] < pivot:
               i++
               swap arr[i], arr[j]
       swap arr[i+1], arr[high]
       return i+1

   quickSort(arr, low, high):
       if low < high:
           p = partition(arr, low, high)
           quickSort(arr, low, p-1)
           quickSort(arr, p+1, high)

   TIME COMPLEXITY:
   - Best/Average: O(N log N)
   - Worst: O(N^2) when pivot is poor

   SPACE COMPLEXITY:
   - O(log N) recursion stack

   STABILITY:
   - Not stable
*/

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

/*
DRY RUN  
Pivot = last element

Initial: [13,46,24,52,20,9]
Place pivot 9 at position 0 → [9,46,24,52,20,13]
Sort right side similarly
Final sorted array → [9,13,20,24,46,52]
*/



/* ------------------------------
   MAIN DRIVER FUNCTION
   ------------------------------
*/

int main() {
    int arr1[] = {13, 46, 24, 52, 20, 9};
    int n = sizeof(arr1) / sizeof(arr1[0]);

    cout << "Before Sorting: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";

    selection_sort(arr1, n);
    cout << "After Selection Sort: ";
    for (int x : arr1) cout << x << " ";
    cout << "\n\n";

    int arr2[] = {13, 46, 24, 52, 20, 9};
    bubble_sort(arr2, n);
    cout << "After Bubble Sort: ";
    for (int x : arr2) cout << x << " ";
    cout << "\n\n";

    int arr3[] = {13, 46, 24, 52, 20, 9};
    insertion_sort(arr3, n);
    cout << "After Insertion Sort: ";
    for (int x : arr3) cout << x << " ";
    cout << "\n\n";

    vector<int> arr4 = {13, 46, 24, 52, 20, 9};
    mergeSort(arr4, 0, n - 1);
    cout << "After Merge Sort: ";
    for (int x : arr4) cout << x << " ";
    cout << "\n\n";

    vector<int> arr5 = {13, 46, 24, 52, 20, 9};
    quickSort(arr5, 0, n - 1);
    cout << "After Quick Sort: ";
    for (int x : arr5) cout << x << " ";
    cout << "\n";

    return 0;
}
