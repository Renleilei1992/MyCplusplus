/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：126_quickSort.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年05月07日
*   描    述：看到MIT的算法导论公开课关于快速排序的讲解之后尝试自己写快排
*   版    本: Version 1.00
*   公开  课: http://open.163.com/movie/2010/12/S/4/M6UTT5U0I_M6V2T7IS4.html
================================================================*/
#include <iostream>

using namespace std;

void quickSort(int arr[], int start, int end);
int partition(int arr[], int start, int end);

static const auto io_sync_off = []()
{
    // turn off sync
    std::ios::sync_with_stdio(false);
    // untie in/out streams
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
	// int arr[8] = {6, 10, 13, 5, 8, 3, 2, 11};
	int arr[100] = {884688278,387052570,77481420,537616843,659978110,215386675,604354651,
	64838842,830623614,544526209,292446044,570872277,946770900,411203381,445747969,480363996,
	31693639,303753633,261627544,884642435,978672815,427529125,111935818,109686701,714012242,
	691252458,230964510,340316511,917959651,544069623,193715454,631219735,219297819,151485185,
	986263711,805374069,915272981,493886311,970466103,819959858,733048764,393354006,631784130,
	70309112,513023688,17092337,698504118,937296273,54807658,353487181,82447697,177571868,830140516,
	536343860,453463919,998857732,280992325,13701823,728999048,764532283,693597252,433183457,157540946,
	427514727,768122842,782703840,965184299,586696306,256184773,984427390,695760794,738644784,784607555,
	433518449,440403918,281397572,546931356,995773975,738026287,861262547,119093579,521612397,306242389,
	84356804,42607214,462370265,294497342,241316335,158982405,970050582,740856884,784337461,885254231,
	633020080,641532230,421701576,298738196,918973856,472147510,169670404};
	//partition(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);

	quickSort(arr, 0, sizeof(arr)/sizeof(arr[0]) - 1);

	// print result
	for(int k = 0; k < sizeof(arr)/sizeof(arr[0]); k++) {
		cout << arr[k] << ",";
	}
	cout << endl;



	return 0;
}


void quickSort(int arr[], int start, int end)
{
	cout << "quickSort(): start: " << start << " end: " << end << endl;
	if (start < end) {
		int index = partition(arr, start, end);
		quickSort(arr, start, index - 1);
		quickSort(arr, index + 1, end);
	}
}

// 快速排序算法基础版
// 6  10 13 5  8  3  2  11
// i  j
// 6  5  13 10 8  3  2  11
//    i        j
// 6  5  3  10 8  13 2  11
//       i           j   
// 6  5  3  2  8  13 10 11
//          i           j->(loop end)
// 2  5  3  6  8  13 10 11
//          ^
// 此时6作为主元被交换到i所在的位置(第一次划分使用了6作为划分数组的主元)
// 接下来就将6的下标 r 返回,并初始化两个排序 quickSort(arr, p, r-1) 和 quickSort(arr, r+1, q)
// 初始调用 quickSort(arr, 1, n)
int partition(int arr[], int start, int end)
{
	cout << "partition(): start: " << start << " end: " << end << endl;
	// print array begin 
	cout << "partition() begin: ";
	for(int k = start; k <= end; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;

	int pos = start - 1;
	int base = arr[start];
	int tmp = 0;

	for(int i = start; i <= end; i++) {
		cout << "base: [" << base << "] ";
		if(arr[i] <= base) {
			pos++;
			tmp = arr[pos];
			arr[pos] = arr[i];
			arr[i] = tmp;
		}

		for(int k = start; k <= end; k++) {
  	        cout << arr[k] << " ";
   	    }
        cout << endl;
	}

	tmp = arr[pos];
	arr[pos] = arr[start];
	arr[start] = tmp;

	// print result
	cout << "partition() complete: ";
	for(int k = start; k <= end; k++) {
		cout << arr[k] << " ";
	}
	cout << endl;

	return pos;
}
