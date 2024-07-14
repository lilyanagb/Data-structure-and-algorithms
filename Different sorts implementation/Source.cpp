#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}

///////////////////////////////////////////////

void insertion_sort(vector<int>& arr) {
	for (int i = 1; i < arr.size(); i++) {
		int curValue = arr[i];

		int j = i - 1;

		while (j >= 0 && arr[j] > curValue) {
			arr[j + 1] = arr[j];
			j--;
		}

		arr[j + 1] = curValue;
	}
}

///////////////////////////////////////////////

int partition(vector<int>& arr, int l, int r) {

	int pivot = arr[r];
	int i = l;

	for (int j = l; j < r; j++) {
		if (arr[j] <= pivot) {
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[r]);
	return i;
}

void quick_sort(vector<int>& arr, int l, int r) {
	if (l < r)
	{
		int pivot = partition(arr, l, r);

		quick_sort(arr, l, pivot - 1);
		quick_sort(arr, pivot + 1, r);
	}
}

/////////////////////////////////////////

void merge(vector<int>& arr, int l, int mid, int r) {
	vector<int> left;
	vector<int> right;

	for (int i = l; i <= mid; i++) {
		left.push_back(arr[i]);
	}

	for (int i = mid + 1; i <= r; i++) {
		right.push_back(arr[i]);
	}

	int i = 0;
	int j = 0;

	int index = l;
	while (i < left.size() && j < right.size()) {
		if (left[i] < right[j]) {
			arr[index++] = left[i++];
		}
		else {
			arr[index++] = right[j++];
		}
	}

	while (i < left.size()) {
		arr[index++] = left[i++];
	}

	while (j < right.size()) {
		arr[index++] = right[j++];
	}
}

void merge1(vector<int>& vec, int start, int mid, int end) {
	int i = start, j = mid + 1;
	vector<int> temp;

	while (i <= mid && j <= end) {

		if (vec[i] <= vec[j]) {
			temp.push_back(vec[i]);
			i++;
		}
		else {
			temp.push_back(vec[j]);
			j++;
		}

	}

	while (i <= mid) {
		temp.push_back(vec[i]);
		i++;
	}

	while (j <= end) {
		temp.push_back(vec[j]);
		j++;
	}

	for (int i = start; i <= end; i++) {
		vec[i] = temp[i - start];
	}
}

void merge_sort(vector<int>& arr, int l, int r) {
	if (r - l <= 0) {
		return;
	}

	int mid = l + (r - l) / 2;

	merge_sort(arr, l, mid);
	merge_sort(arr, mid + 1, r);

	merge(arr, l, mid, r);
}

///////////////////////////////////////////////
int getMax(int array[], int size) {
	int max = array[1];
	for (int i = 2; i <= size; i++) {
		if (array[i] > max)
			max = array[i];
	}
	return max; 
}

void countingSort(vector<int>& array) {

	auto maxNumber = *max_element(array.begin(), array.end());

	int len = array.size();

	vector<int> countingArray(maxNumber + 1);

	for (int i = 0; i < maxNumber + 1; i++) {
		countingArray[i] = 0;
	}

	for (int i = 0; i < len; i++) {
		countingArray[array[i]]++;
	}

	int currentIndexOfArray = 0;
	for (int i = 0; i <= maxNumber; i++) {

		for (int j = 0; j < countingArray[i]; j++) {

			array[currentIndexOfArray++] = i;
		}

	}
}


int main() {
	int arr[8] = { 1,5,9,20,3,6,88,1 };
	vector<int> arrq = { 1,5,9,20,-2,3,6,88,-10,1 };
	vector<int> arrq1 = { 1,5,9,20,3,6,88,10,1 };
	int size = arrq.size();

	//bubbleSort(arr, 10); //O(N^2)
	//insertion_sort(arrq); //not stable  //O(N^2)
	//quick_sort(arrq, 0, size - 1); //O(NlogN)
   	// merge_sort(arrq,0,size-1); //O(NlogN)
	//countingSort(arrq1); //O(N+k) doesnt work for negative

	for (int i = 0; i < 8; i++) {

		cout << arr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < 10; i++) {

		cout << arrq1[i] << " ";
	}
	return 0;
}