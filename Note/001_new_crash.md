date: 2017-12-31


date: 2017-12-28

#### new 引起的程序崩溃

	- 简述: 由于类的构造函数中使用了列表初始化，string成员初始化值的时候传入了 0 ，引起程序崩溃，实际应该传入 ""

	```
	class Instance
	{
		public:
			Instance(char ch1, string str1, int num1);
			~Instance();

		private:
			char ch1;
			string str1;
			int num1;
	}

	Instance(char ch1, string str1, int num1)
		:ch1('a')
		,str1(0)	// 崩溃开始
		,num1(0)
	{
	}

	```

### STRING
	- NCString strAdd01 = _T("Hello C++");

### DECLARE_DYNAMIC
	- 在初始化一个窗口类的时候，动态创建，需要让底层知道你是cview还是cwnd
