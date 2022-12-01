#include"Sort.h"

int main()
{
	int i = 0;
	clock_t time_req = clock();
	splitBigFile("Books_rating.csv", "file",27925);
	for (int i = 0; i <= numfile; i++)
	{
		string in = "file" + to_string(i) + ".csv";
		char* input = new char[in.length() + 1];
		strcpy(input, in.c_str());
		string out = "output" + to_string(i) + ".csv";
		char* output = new char[out.length() + 1];
		strcpy(output, out.c_str());
		string fname = "";
		string typefile = "";
		cout << "number of lines in file " << i << ": " << num_line[i] << endl;
		FileSorting(input, fname, typefile, output, 10, num_line[i] / 10 + 1);
	}
	// Thuc hien merge 100 FILE output lai voi nhau
	string fname = "output";
	string typefile = ".csv";
	char outputFile[] = "output.csv";
	header = true;
	mergeFiles(outputFile, fname, typefile, 100);
	time_req = clock() - time_req;
	cout << "Total time : " << (float)time_req / CLOCKS_PER_SEC << " seconds" << endl;
	num_line.clear();
}
