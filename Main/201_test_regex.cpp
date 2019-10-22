/*================================================================
*   Copyright (C) 2019 Renleilei. All rights reserved.
*   
*   文件名称：201_test_regex.cpp
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2019年10月21日
*   描    述：简单测试C++11中引入的正则表达式库
*   版    本: Version 1.00
================================================================*/

#include <iostream>
#include <regex>
#include <cstring>

using namespace std;

void regex_match(string str);
void regex_search(string str);
void regex_replace(string str);

int main()
{

	std::string s = "Some people, when confronted with a problem, think "
					  "\"I know, I'll use regular expressions.\" "
					  "Now, they have two problems.";
	regex_search(s);
	regex_match(s);
	regex_replace(s);
	return 0;
}

void regex_match(string str)
{
	std::regex word_regex("(\\w+)");
	auto words_begin = std::sregex_iterator(str.begin(), str.end(), word_regex);
	auto words_end = std::sregex_iterator();

	std::cout << __func__ << "::Found: " << std::distance(words_begin, words_end) << " words\n";

	// 找到超过6个字符的单词
	const int N = 6;
	cout << "Words longer than " << N << " characters:\n";
	for(std::sregex_iterator iter = words_begin; iter != words_end; ++iter) {
		std::smatch match = *iter;
		std::string match_str = match.str();
		if (match_str.size() > N) {
			cout << " " << match_str << endl;
		}
	}
}

void regex_search(string str)
{
	cout << str << endl;
	std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);
	if (std::regex_search(str, self_regex)) {
		std::cout << "Text contains the phrase 'regular expressions'\n";
	}
}

void regex_replace(string str)
{
	// 超过6个字符的单词加上中括号
	std::regex long_word_regex("(\\w{7,})");
	std::string new_s = std::regex_replace(str, long_word_regex, "[$&]");
	cout << __func__ << "::" << new_s << endl;

	// 超过6个字符的单词替换为 ****
	std::regex replace_regex("(\\w{7,})");
	std::string result_str = std::regex_replace(str, replace_regex, "****");
	cout << __func__ << "::" << result_str << endl;
}
