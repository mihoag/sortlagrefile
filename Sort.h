#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <Windows.h>
#include<vector>
#include<sstream>

using namespace std;
typedef unsigned long long LL;
#define numfile 99
static vector<long long> sizefile;
static vector<int> num_line;

struct BOOK 
{
	string id, otherData;
};

struct MinHeapNode 
{

	BOOK element;
	int i; // index đại diện của từng chunk file
};

class MinHeap
{

	MinHeapNode* harr;

	int heap_size; // kích thước của MinHeap

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

// Overloading toán tử >>
istream& operator>>(std::istream& input, BOOK& book);

// Overloading toán tử <<
ofstream& operator<<(std::ofstream& output, BOOK& book);

void swap(MinHeapNode* x, MinHeapNode* y);

LL GetFileLength(const string& filepath);

void swap(BOOK& a, BOOK& b);

void partition(BOOK a[], int l, int r, int& begin, int& end);

void quicksort3(BOOK a[], int l, int r);

void splitBigFile(const string& filepath, const char* namefile, LL blockSize);

// Merge num_ways = 10 file lại
void mergeFiles(char* output_file, string fname, string typefile, int k);

// Cắt và sort từng file
void SplitAndSort(char* input_file, int run_size, int num_ways);

void FileSorting(char* input_file, string fname, string typefile, char* output_file, int num_ways, int run_size);