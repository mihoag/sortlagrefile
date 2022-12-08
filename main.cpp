#include"Sort.h"
int main()
{
    clock_t start, end;
    start = clock();
    int num_ways = 100; // Số file cần chia
    int run_size = 30001; // Số dòng cần đọc ở mỗi file

    char inputFile[] = "Books_rating.csv";
    char outputFile[] = "sorted_books_rating.csv";

    FileSorting(inputFile, outputFile, num_ways, run_size);
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << fixed << setprecision(5) << time_taken << endl;
    return 0;
}