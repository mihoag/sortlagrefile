#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <Windows.h>
#include<vector>
#include<sstream>
#include<ctime>
#define numfile 99

using namespace std;
typedef unsigned long long LL;
static vector<long long> sizefile;
static vector<int> num_line;

struct BOOK
{
	string id, otherData;
};

static BOOK headerbook;
static bool header = false;

struct MinHeapNode {

	BOOK element;

	int i; // index đại diện của từng chunk file
};
class MinHeap {

	MinHeapNode* harr;

	int heap_size; // kích thước min heap

public:

	MinHeap(MinHeapNode a[], int size);

	void MinHeapify(int);

	MinHeapNode getMin() { return harr[0]; }

	void replaceMin(MinHeapNode x)
	{
		harr[0] = x;
		MinHeapify(0);
	}
};
// Hoán đổi hai node của MinHeap
void swap(MinHeapNode* x, MinHeapNode* y);

//Lấy kích thước của file
LL GetFileLength(const string& filepath);

// Overloading toán tử >>
istream& operator>>(std::istream& input, BOOK& book);

// Overloading toán tử <<
ofstream& operator<<(std::ofstream& output, BOOK& book);

//Hoán đổi hai dữ liệu BOOK
void swap(BOOK& a, BOOK& b);

//Chọn phần tử làm vách ngăn cho thuật toán QuickSort3
void partition(BOOK a[], int l, int r, int& begin, int& end);

//Sắp xếp các quyển sách theo ID
void quicksort3(BOOK a[], int l, int r);

//Chia file lớn thành các file nhỏ
void splitBigFile(const string& filepath, const char* namefile, LL blockSize);

// Gộp các file đã sắp xếp, file sau khi gộp lại vẫn là file đã sắp xếp
void mergeFiles(char* output_file, string fname, string typefile, int k);

// Chia file và sắp xếp từng file
void SplitAndSort(char* input_file, int run_size, int num_ways);

//Sắp xếp dữ liệu của file
void FileSorting(char* input_file, string fname, string typefile, char* output_file, int num_ways, int run_size);