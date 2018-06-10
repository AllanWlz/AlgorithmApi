/*****************************************************************************
*  OpenST Basic tool library                                                 *
*  Copyright (C) 2017 Allan.Wang  allan.wanglz@qq.com.                       *
*                                                                            *
*  This file is part of OST.                                                 *
*                                                                            *
*  This program is free software; you can redistribute it and/or modify      *
*  it under the terms of the GNU General Public License version 3 as         *
*  published by the Free Software Foundation.                                *
*                                                                            *
*  You should have received a copy of the GNU General Public License         *
*  along with OST. If not, see <http://www.gnu.org/licenses/>.               *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*  @file     cppstd.h                                                        *
*  @brief    A Self-made Data Sturcture and Algorithm library for c++        *
*  			                                                                 *
*                                                                            *
*  @author   Allan.Wang                                                      *
*  @email    allan.wanglz@qq.com                                             *
*  @version  1.0.0.1		                                                 *
*  @date     allan.wanglz@qq.com                                             *
*  @license  GNU General Public License (GPL)                                *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : Description                                              *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2018/03/09 | 1.0.0.1   | Allan.Wang      | Create file                     *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#include <stdlib.h>

#include <stdarg.h>

#ifndef __CPPSTD_H__

#define __CPPSTD_H__


/*******************************************
 * @name	countones()
 * @brief 	统计一个整数中二进制位1的个数
 * @param   _uint32 n 正整数n 
 * @return   返回说明
 *        -<int> n 
********************************************/
#define POW(c) (1 << (c)) //2^c

#define MASK(c) (((unsigned long) - 1) / (POW(POW(c)) + 1))

//MASK(0) = 5555555(h)
//MASK(1) = 3333333(h)
//MASK(2) = 0f0f0f0f(h)
//MASK(3) = 00ff00ff(h)
//MASK(4) = 0000ffff(h)

//输入：n 的二进制展开中，以2^c位为单位分组，各组数值已经分别等于原先这2^c位中1的数目
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))
//运算优先级：先右移，再位与
//过程：以2^c位为单位分组，相邻的组两两捉对累加，累加值用原2^(c + 1)位就地记录
//输出：n的二进制展开中，以2^(c+1)位为单位分组，各组数值分别等于这原先2^(c+1)位中1的数目

int countones( unsigned int n);


/*******************************************
 * @name	Vector
 * @brief 	向量标准模板
********************************************/
typedef int Rank;

#define DEFAULT_CAPACITY 3

template <typename T> class Vector{

protected:

	Rank _size;int _capacity;T* _elem;//规模、容量、数据区

	void copyFrom(T const* A, Rank lo, Rank hi);//复制数组区间A[lo,hi]

	void expand(); //空间不足时扩容

	void shrink(); //装填因子过小时压缩

	bool bubble(Rank lo, Rank hi); //扫描交换

	void bubbleSort(Rank lo, Rank hi); //起泡交换排序

	Rank max(Rank lo, Rank hi);  //选取较大元素

	void selectionSort(Rank lo, Rank hi);//选择排序算法

	void merge(Rank lo,Rank mi,Rank hi);//归并算法

	void mergeSort(Rank lo, Rank hi);//归并排序算法

	Rank partition(Rank lo, Rank hi);//轴点构造算法

	void quickSort(Rank lo, Rank hi);//快速排序算法

	void heapSort(Rank lo, Rank hi); //堆排序

public:

//构造函数

	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量为c，规模为s，所有元素初始为v
	{
		_elem = new T[_capacity = c]; 

		for(_size = 0;_size <s;_elem[_size++] = v);
	}	

	Vector(T const* A, Rank n){copyFrom(A,0,n);}   //数组整体复制

	Vector(T const* A, Rank lo, Rank hi){copyFrom(A,lo,hi);}//数组局部复制

	Vector(Vector<T> const &V){copyFrom(V._elem,0,V._size);} //向量整体复制

	Vector(Vector<T> const &V, Rank lo, Rank hi){copyFrom(V._elem,lo,hi);}//区间

//析构函数

	~Vector(){delete []_elem;}

//只读访问

	Rank size() const {return _size;};

	bool empty() const {return !_size;}

	int disordered() const; //判断向量是否已排序

	Rank find(T const & e) const {return find(e,0,_size);}

	Rank find(T const & e, Rank lo, Rank hi) const;//无序向量区间查找

	Rank search(T const & e) const //有序向量整体查找
	{

		return(0 >= _size)? -1:search(e, 0, _size);

	}

	Rank search (T const & e, Rank lo, Rank hi) const; //有序向量区间查找

//可写访问接口

	T & operator[] (Rank r) const; //重载下标操作符

	Vector<T> & operator=(Vector<T> const &); //重载赋值操作符，直接克隆向量

	T remove(Rank r); //删除秩为r的元素

	int remove(Rank	lo, Rank hi); //删除秩在lo hi 之间的元素

	Rank insert(Rank r, T const & e); //插入元素

	Rank insert(T const & e){return insert(_size, e);} //作为末元素加入

	void sort(int method, Rank lo, Rank hi); //对 lo hi 元素排序

	void sort(){sort(0,0,_size);} //整体排序

	void unsort(Rank lo, Rank hi);//对lo hi置乱

	void unsort(){unsort(0,_size);}//整体置乱

	int deduplicate(); //无序去重

	int uniquify();    //有序去重

//遍历

	void traverse(void (*) (T&)); //遍历（使用函数指针，只读或局部性修改

	template <typename VST> void traverse (VST &); //遍历（使用函数对象，可全局性修改
};


class Bitmap{//位图Bitmap类
private:
	Rank* F; Rank N;//规模为N的向量F，记录[k]被标记的次序
	Rank* T; Rank top;//容量为N的栈T，记录被标记各位秩的栈，以及栈顶指针

protected:
	inline bool valid(Rank r){return (0 <= r)&&(r < top);}
	inline bool erased(Rank k)//判断[k]是否被标记过，且后来又被清除
	{
		return valid(F[k]) && !(T[F[k]] + 1 + k);
	}

public:
	Bitmap(Rank n = 8)
	{
		N = n;
		F = new Rank[n];
		T = new Rank[N];
		top = 0;
	}

	~Bitmap(){delete []F;delete []T;}//析构时释放空间

//interface
	inline void set(Rank k){//插入

		if(test (k)) return; //忽略已带标记的位
		if(!erased(k)) F[k] = top++;
		T[F[k]] = k;//若系曾经被标记后被清除，则恢复原校验环

	}

	inline void clear(Rank k)//删除
	{
		if(test(k)) T[F[k]] = - 1 - k;
	}

	inline bool test(Rank k)
	{
		return valid(F[k]) && (k == T[F[k]]);
	}
};



#define ListNodePosi(T) ListNode<T>*

template <typename T> 
struct ListNode{
	
	T data;

	ListNodePosi(T) pred;

	ListNodePosi(T) succ;

//Construct
	ListNode(){}

	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL):data(e),pred(p),succ(s){};

//Operation
	
	ListNodePosi(T) insertAsPred(T const& e);

	ListNodePosi(T) insertAsSucc(T const& e);

};

template <typename T> 
class List{

private:

	int _size; 

	ListNodePosi(T) header;

	ListNodePosi(T) trailer;

protected:

	void init();

	int clear();;

	void copyNodes(ListNodePosi(T), int); //复制列表中自位置p起的n项

	void merge(ListNodePosi(T) &, int, List<T>&, ListNodePosi(T) q, int m);

	void mergeSort(ListNodePosi(T)&, int);

	void selectionSort(ListNodePosi(T), int);

	void insertionSort(ListNodePosi(T), int);

public:

//Construction
//
	List(){init();}

	List(List<T> const& L); //整体复制列表

	List(List<T> const& L, Rank r, int n);

	List(ListNodePosi(T) p, int n);

//Restore
	~List();

//Read Only
//
	Rank size() const{return _size;};

	bool empty() const{return _size <= 0;};

	T & operator[](Rank r) const; //重载，寻秩访问

	ListNodePosi(T) first() const {return header -> succ;} //首节点位置

	ListNodePosi(T) last() const {return trailer -> pred;} //末节点位置

	bool valid(ListNodePosi(T) p)//判断位置p是否对外合法
	{

		return p && (trailer != p) && (header != p);

	}

	int disordered() const;//判断列表是否已经有序

	ListNodePosi(T) find(T const & e) const //无序列表查找
	{return find(e, _size, trailer);}

	ListNodePosi(T) find(T const & e, int n, ListNodePosi(T) p)const;//无序区间查找

	ListNodePosi(T) search(T const& e) const
	{return search(e, _size, trailer);}

	ListNodePosi(T) search(T const & e, int n, ListNodePosi(T) p) const;

	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n); //在p及其n-1个后继中选出最大者

	ListNodePosi(T) selectMax(){return selectMax(header -> succ, _size);}//整体最大者

//可读写访问接口

	ListNodePosi(T) insertAsFirst(T const & e);

	ListNodePosi(T) insertAsLast(T const & e);

	ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);//将e作为p的后继插入

	ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);//将e作为p的前驱插入

	T remove(ListNodePosi(T) p);//删除合法位置p处的节点

	void merge(List<T>& L)
	{
		merge(first(), _size, L, L.first(), L.size); //全列表归并
	}

	void sort(int method,ListNodePosi(T) p, int n);//列表区间排序

	void sort(){sort(first(), _size);} //列表整体排序

	int deduplicate(); //无序去重

	int uniquify();	//有序去重

	void reverse(); //前后倒置
//遍历

	void traverse(void (*) (T&)); //遍历，依次实施visit操作

	template <typename VST> //操作器

	void traverse(VST &); //遍历，依次实施visit操作 
};

template <typename T> class Stack:public Vector<T>{

public:

	void push(T const & e){this->insert(this->size(), e);}//入栈

	T pop(){return this->remove(this->size() - 1);}//出栈

	T &top(){return (*this)[this->size() - 1];}


};

template <typename T> class Queue:public List<T>{
	
public:

	void enqueue(T const & e){this->insertAsLast(e);}// 尾部插入

	T dequeue(){return this->remove(this->first());};//出队

	T& front(){return this->first()->data;}//队首

};




#endif