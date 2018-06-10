#include <stdlib.h>
#include "cppstd.h"

#ifndef __LONGINT_H__

#define __LONGINT_H__

#define positive 1    //宏定义正负符号
#define negative -1

//长正数类，继承自cppstd中的双向链表标准模板
class longint: public List<int>{

public:

//member
	int sign;  //长整数的正负符号


//method

	longint(char* str);   //以字符串str构造长整数

	longint();			//空的长整数构造函数，默认值为0

	longint operator+(longint b); // 重载加法运算符

	longint operator=(longint b); // 重载等号运算符

	bool isabslt(longint b)		//比较绝对值是否比b大
}


#endif