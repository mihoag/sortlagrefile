#include"Sort.h"
MinHeap::MinHeap(MinHeapNode a[], int size)
{
	heap_size = size;
	harr = a;
	int i = (heap_size - 1) / 2;
	while (i >= 0) {
		MinHeapify(i);
		i--;
	}
}
void MinHeap::MinHeapify(int i)
{
	while (i < (heap_size + 1) / 2)
	{
		int l = 2 * i + 1; // left node index
		int r = 2 * i + 2; // right node index
		int smallest = i;

		if (l < heap_size && harr[l].element.id < harr[i].element.id)
			smallest = l;

		if (r < heap_size && harr[r].element.id < harr[smallest].element.id)
			smallest = r;

		if (smallest != i) {
			swap(&harr[i], &harr[smallest]);
			i = smallest;
		}
		else
		{
			break;
		}
	}
}
void swap(MinHeapNode* x, MinHeapNode* y)
{
	MinHeapNode temp = *x;
	*x = *y;
	*y = temp;
}
LL GetFileLength(const string& filepath)
{
	LL len = -1;
	ifstream in;
	in.open(filepath, ios_base::in);
	if (in.is_open())
	{
		in.seekg(0, ios::end);
		len = in.tellg();
		in.close();
	}

	return len;
}
istream& operator>>(std::istream& input, BOOK& book)
{
	getline(input, book.id, ',');
	getline(input, book.otherData);
	return input;
}
ofstream& operator<<(std::ofstream& output, BOOK& book)
{
	stringstream ss;
	ss << book.id + "," + book.otherData + "\n";
	output << ss.str();
	return output;
}
void swap(BOOK& a, BOOK& b)
{
	BOOK temp = a;
	a = b;
	b = temp;
}
void partition(BOOK a[], int l, int r, int& begin, int& end)
{
	int mid = (l + r) / 2;
	swap(a[mid], a[r]); // Tạo tính ngẫu nhiên khi lấy phần tử cuối

	string pivotValue = a[r].id;
	int i = l, j = r - 1;

	while (true) { // tách thành |nhỏ hơn| và |lớn hơn hoặc bằng pivot value|
		while (a[i].id < pivotValue) i++;

		while (a[j].id >= pivotValue) {
			j--;
			if (j <= l) break;
		}

		if (i >= j) break;
		swap(a[i], a[j]);
	}

	swap(a[r], a[i]);

	begin = i; // index của phần tử đầu tiên trong mảng = pivot value
	i++;
	j = r;

	while (true) { // Đưa những phần tử = pivot value vào ngay sau nó
		while (a[j].id > pivotValue) {
			j--;
			if (j <= i) break;
		}
		if (j <= i) {
			j = i;
			break;
		}
		swap(a[j], a[i]);
		i++;
	}

	end = j - 1; // index của phần tử cuối cùng trong mảng = pivot value

}
void quicksort3(BOOK a[], int l, int r)
{
	int begin, end;
	partition(a, l, r, begin, end);

	if (end + 1 < r) {
		quicksort3(a, end + 1, r);
	}

	if (begin - 1 > l) {
		quicksort3(a, l, begin - 1);
	}
}
void splitBigFile(const string& filepath, const char* namefile, LL blockSize)
{
	LL ori_size = GetFileLength(filepath);
	blockSize *= 1024; //KB -> B
	if (ori_size == -1)
	{
		cout << "get file length failed." << endl;
		return;
	}
	ifstream in;
	in.open(filepath, ios_base::in | ios_base::binary);
	if (!in.is_open())
	{
		cout << "ifstream open failed" << endl;
		return;
	}

	LL read_count = 0;
	LL cur_count = 0;
	int i;
	BOOK book;
	for (i = 0; read_count < ori_size && i <= numfile; ++i)
	{
		int thisTimesRead = 0;
		string divfile = namefile + to_string(i) + ".csv";
		cout << "spliting file: " << divfile << ".." << endl;
		ofstream out;
		out.open(divfile, ios_base::out | ios_base::binary);
		if (!out.is_open())
		{
			cout << "open " << divfile << " failed." << endl;
			break;
		}

		int lines = 0;
		while (thisTimesRead < blockSize && read_count < ori_size)
		{
			if (!(in >> book))
				break;


			cur_count = book.id.length() + book.otherData.length();

			// Lần đầu tiên đọc lấy header từ trong file ra 
			if (read_count == 0)
			{
				headerbook = book;
				read_count += cur_count;
				continue;
			}

			read_count += cur_count;
			thisTimesRead += cur_count;
			out << book;
			lines++;
		}
		num_line.push_back(lines);
		sizefile.push_back(thisTimesRead);
		out.close();
	}
	in.close();
	cout << "Split " << i << " files, original file size: " << ori_size << "Bytes." << endl;
}
void mergeFiles(char* output_file, string fname, string typefile, int k)
{
	ifstream* in = new ifstream[k];

	// Mở k = num_ways files để merge 
	for (int i = 0; i < k; i++) {
		string fileName = fname + to_string(i) + typefile;
		in[i].open(fileName, ios_base::out | ios_base::binary);
	}


	// Tạo file output kết quả 
	ofstream out;
	out.open(output_file, ios_base::out | ios_base::binary);

	// Tạo mảng là cây heap lưu trữ phần tử đầu (nhỏ nhất) của mỗi files và index đại diện cho file đó
	MinHeapNode* nodeArr = new MinHeapNode[k];
	int i;
	for (i = 0; i < k; i++) {
		if (!(in[i] >> nodeArr[i].element))
			break;

		// Index đại diện của từng file
		nodeArr[i].i = i;
	}
	// Tạo cây Min Heap từ mảng trên 
	MinHeap hp(nodeArr, i);
	// Nếu header = true thực hiện đưa header lên đầu file
	if (header == true)
	{
		out << headerbook;
	}

	int count = 0;
	while (count != i) {
		// Lấy phần tử nhỏ nhất (phần tử đầu - root) trong Min Heap (phần tử đầu) và ghi vào file output
		MinHeapNode root = hp.getMin();
		out << root.element;

		// Tìm phần tử kế tiếp thuộc cùng 1 file với root và thay thế cho root
		if (!(in[root.i] >> root.element)) { // Đây là trường hợp khi file này đã đọc hết, không còn gì để đọc
			root.element.id = "{{{{{{{{{{";  // nên ta thay thế bằng 1 giá trị lớn nhất mà các node ko bao giờ đạt được
			count++;                         // để không ảnh hưởng việc lấy phần tử đầu của Min Heap
		}                                    // Vì ID lớn nhất chỉ có thể là ZZZZZZZZZZ nên ta thay bằng {{{{{{{{{{ để đảm bảo

		// Thay thế root bằng phần tử kế tiếp trong file, đồng thời Heapify lại để cây trở thành Min Heap
		hp.replaceMin(root);
	}

	// Đóng input và output files
	for (int i = 0; i < k; i++)
		in[i].close();

	out.close();

	delete[] in;
}
void SplitAndSort(char* input_file, int run_size, int num_ways)
{
	// Đọc file input là Book-rating
	ifstream in;
	in.open(input_file, ios_base::out | ios_base::binary);

	// Tạo num_ways = 10 files để ghi data sau khi sort vào
	ofstream* out = new ofstream[num_ways];
	for (int i = 0; i < num_ways; i++) {
		string fileName = to_string(i);
		out[i].open(fileName, ios_base::out | ios_base::binary);
	}

	// Cấp phát bộ nhớ để đọc run_size = 3003 dòng
	BOOK* arr = new BOOK[run_size];
	bool more_input = true;
	int next_output_file = 0;
	int i;
	while (more_input) {
		for (i = 0; i < run_size; i++) {
			if (!(in >> arr[i])) {
				more_input = false;
				break;
			}
		}

		quicksort3(arr, 0, i - 1);

		// Ghi dữ liệu vừa sort được vào file
		for (int j = 0; j < i; j++) {
			out[next_output_file] << arr[j];
		}

		next_output_file++;
	}

	// Đóng input và output files
	for (int i = 0; i < num_ways; i++)
		out[i].close();

	in.close();

	delete[] out;
}
void FileSorting(char* input_file, string fname, string typefile, char* output_file, int num_ways, int run_size)
{
	SplitAndSort(input_file, run_size, num_ways);
	mergeFiles(output_file, fname, typefile, num_ways);
}

