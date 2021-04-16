/*================================================================
*   Copyright (C) 2020 Renleilei. All rights reserved.
*   
*   文件名称：001_helloWorld.go
*   创 建 者：Renleilei (renleilei1992@foxmail.com)
*   创建日期：2020年09月05日
*   描    述：
*   版    本: Version 1.00
================================================================*/

package main

// import "fmt"

import (
"fmt"
"./package/myMath"
)

func main() {
	/* 这是我的第一个简单的golang程序 */
	fmt.Println("Hello World! Hi Golang!")
	fmt.Println(mathClass.Add(99,100))
	testDataStruct()
	fmt.Println("--------------split---------------")
	testString()
}

/* 基础数据结构 */
func testDataStruct() {
	/* bool */
	var bVal bool = true
	/* int */
	var iVal int = 10
	/* float */
	var iVal1 float32 = 10.1
	var iVal2 float64 = 10.2

	fmt.Println(bVal)
	fmt.Println(iVal)
	fmt.Println(iVal1)
	fmt.Println(iVal2)
}

/* 字符串使用 */
func testString() {
	text1 := "\"Hello GoLang\", I said1"
	text2 := `"Hello GoLang", I said2`
	fmt.Println(text1)
	fmt.Println(text2)

	text3 := "Hello" + " GoLang"
	text3 += " C++"
	fmt.Println(text3)

	text4 := "abcdefg"
	fmt.Println(text4[3])		// 获取字符串索引位置为3的原始字节, 比如a为97, 此处c为100
	fmt.Println(text4[3:5])		// 获取字符串索引位置 3 - 5 的字符串, 此处为 de
	fmt.Println(text4[3:])		// 截取得字符串索引位置为 3 到len(s)-1的字符串, 此处为 defg
	fmt.Println(text4[:5])		// 截取得字符串索引位置为 0 到 5 的字符串, 此处为 abcde
	fmt.Println(len(text4))		// 获取字符串的字节数?, 此处为 7
//	fmt.Println(utf8.RuneCountInString(text4))		// 获取字符串字符的个数
	fmt.Println([]rune(text4))	// 将字符串的每一个字节转化为ASCII码值, 此处为 [97 98 99 100 101 102 103]
	fmt.Println(string(text4[4]))	// 获取字符串索引位置的字符的字符值

	// 遍历字符串
	text5 := "ABCDEFG"
	for index,char := range text5 {
		fmt.Printf("%d %U %c \n", index, char, char)
	}

	// 字符串索引与切片
	text6 := "aAbBcCdDeEfFgG"
	chars := []rune(text6)		// 先把字符串转为rune切片, 虽然可以通过 string(text[3]) 索引为3的字符,但是不一定可靠, 有些字符可能有多个字节
	for _,char := range chars {
		fmt.Println(string(char))
	}
}
