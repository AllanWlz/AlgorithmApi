#include <stdlib.h>
#include "cppstd.h"


template <typename T> void swap(T & a,T & b){
	
	T c = a;

	a = b;

	b = c;

	return;
}


/*******************************************
 * @name	countones()
 * @brief 	统计一个整数中二进制位1的个数
 * @param   _uint32 n 正整数n 
 * @return   返回说明
 *        -<int> n 
********************************************/
int countones( unsigned int n){

	n = ROUND( n , 0 );

	n = ROUND( n , 1 );

	n = ROUND( n , 2 );

	n = ROUND( n , 3 );

	n = ROUND( n , 4 );
	
	return n;
}
/*******************************************
 * @name	Vector Algriothm
 * @brief 	向量标准算法
********************************************/
template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
{

	while(lo < hi){

		Rank mi = (lo + hi) >> 1;

		(e < A[mi])? hi = mi: lo = mi + 1;

	}

	return --lo;

}

/*******************************************
 * @name	Vector
 * @brief 	向量标准模板
********************************************/
template <typename T>

void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){

	_elem = new T[_capacity = 2 * (hi - lo)]; _size =0;

	while(lo<hi) _elem[_size++] = A[lo++];

}//区间复制

template <typename T>

Vector<T>& Vector<T>::operator= (Vector<T> const & V) //重载赋值操作符，直接克隆向量
{

	if (_elem) delete [] _elem; //释放原有空间

	copyFrom(V._elem, 0, V.size()); //整体复制

	return *this; //返回当前对象的引用，以便链式复制

}

template <typename T> void Vector<T>::expand() //扩容算法
{

	if(_size < _capacity) return; //尚未满员时，不必扩容

	if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //不低于最小容量

	T* oldElem = _elem; _elem = new T[_capacity <<= 1]; //容量加倍

	for (int i = 0; i < _size; ++i)
	{
		_elem[i] = oldElem[i];
	}
	delete [] oldElem;

}

template <typename T> void Vector<T>::shrink() //缩容算法
{

	if(_capacity < DEFAULT_CAPACITY<<1) return;

	if(_size << 2 >_capacity) return;

	T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //容量减半

	for (int i = 0; i < _size; ++i)
	{
		_elem[i] = oldElem[i];
	}
	delete [] oldElem;
}

template <typename T> T& Vector<T>::operator[] (Rank r) const //重载运算符
{
	return _elem[r];
}

template <typename T> void Vector<T>::unsort(Rank lo, Rank hi){//等概率随机置乱区间 lo hi
	
	T* V = _elem + lo;

	for (Rank i = hi - lo; i > 0 ; i--)
	{
		/* code */
		swap(V[i-1],V[rand()%i]);
	
	}

}

template <typename T> 
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const{ //注意lo < hi-- 判定完后 hi-- 接着判定 _elem[hi]

	while((lo < hi--) && e!=_elem[hi]);

	return hi;

}

template <typename T>
Rank Vector<T>::insert(Rank r, T const & e){//关键是从后往前移动

	expand();

	for(int i = _size; i > r; i--) _elem[i] = _elem[i-1];

	_elem[r] = e;

	_size++;

	return r;

}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)//从前往后
{

	if(lo == hi) return 0;

	while(hi < _size) _elem[lo++] = _elem[hi++];

	_size = lo;

	shrink();

	return	hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r){

	T e = _elem[r];

	remove(r,r + 1);

	return e;

}

template <typename T>
int Vector<T>::deduplicate(){//注意find 左闭右开的特性

	int oldsize = _size;

	Rank i = 1;

	while(i<_size){
		
		(find(_elem[i],0,i) < 0)?i++:remove(i);

	}

	return oldsize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit) (T&))
{

	for (int i = 0; i < _size; ++i)
	{
		/* code */
		visit(_elem[i]);
	}

}

template <typename T> template <typename VST> //元素类型 操作器
void Vector<T>::traverse(VST & visit)//函数对象机制
{
	for (int i = 0; i < _size; ++i)
	{
		/* code */

		visit(_elem[i]);
	}
}

template <typename T>
int Vector<T>::disordered() const{

	int n = 0;

	for (int i = 0; i < _size; ++i)
	{
		if(_elem[i-1] > _elem[i]) n++;
	}

	return n;
}

template <typename T> int Vector<T>::uniquify(){ //去重并返回被删除元素总数
	
	Rank i = 0, j = 0;

	while(++j < _size){

		if (_elem[i] != _elem[j])
		{
			/* code */
			_elem[++i] = _elem[j];

		}

	}

	_size = ++i;

	shrink();

	return j - i;

}

template <typename T>
Rank Vector<T>::search(T const& e,  Rank lo ,Rank hi) const{

	//return (rand() % 2) > binSearch(_elem, e , lo, hi):fibSearch(_elem, e, lo, hi);

	return binSearch(_elem, e , lo, hi);

}

template <typename T>
void Vector<T>::sort(int method, Rank lo, Rank hi){

	switch(method)
	{

		case 1: bubbleSort(lo, hi); break;

		case 2: selectionSort(lo, hi); break;

		case 3: mergeSort(lo, hi); break;

		case 4: heapSort(lo, hi); break;

		default: quickSort(lo, hi); break;

	}

}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{

	while(!bubble(lo, hi--));

}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi){

	bool sorted = true;

	while(++lo < hi)
	{

		if( _elem[lo - 1] > _elem[lo])
		{

			sorted = false;

			swap(_elem[lo - 1], _elem[lo]);

		}

	} 

	return sorted;

}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi){

	T e;

	Rank r;

	while(++lo < hi)
	{

		e = _elem[lo - 1];

		r = lo - 1;

		for (int i = lo; i < hi; ++i)
		{
			/* code */

			if(_elem[i] < e)
			{
				e = _elem[i];

				r = i;
			}

		}

		swap(_elem[lo - 1], _elem[r]);

	}

}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi){

	if ( hi - lo < 2) return;

	Rank mi = (lo + hi) >> 1;

	mergeSort(lo , mi);

	mergeSort(mi, hi);

	merge(lo, mi, hi);

}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{

	T* A = _elem + lo;

	Rank lb = mi - lo;

	T* B = new T[lb];

	for (Rank i = 0; i < lb; B[i] = A[i++])
	{
		/* code */
	}

	Rank lc = hi - mi;

	T* C = _elem + mi;

	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
	{
		/* code */

		if((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];

		if((k < lc) && (!(j < lb) || (C[k] <= B[j]))) A[i++] = C[k++];

	}

	delete [] B;

}

template <typename T>
void List<T>::init()//列表初始化
{

	header = new ListNode<T>;

	trailer = new ListNode<T>;

	header -> succ = trailer;

	header -> pred = NULL;

	trailer -> pred = header;

	trailer -> succ = NULL;

	_size = 0;

}

template <typename T>
T & List<T>::operator[](Rank r) const{

	ListNodePosi(T) p = first();

	while(0 < r--) p = p -> succ;

	return	p -> data;

}

template <typename T>
ListNodePosi(T) List<T>::find(T const & e, int n, ListNodePosi(T) p) const
{

	while(0 < n--) 

		if(e == (p = p -> pred) -> data) return p;

	return NULL;

}

template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const & e)
{

	_size++;

	return header -> insertAsSucc(e);//e当作首节点插入

}

template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const & e)
{

	_size++;

	return trailer -> insertAsPred(e);

}

template <typename T>ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)//e当作p的后继插入
{

	_size++;

	return p->insertAsSucc(e);

}

template <typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{

	_size++;

	return p->insertAsPred(e);

}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{

	ListNodePosi(T) x =new ListNode(e, pred, this);

	pred -> succ = x;

	this -> pred = x;

	return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const & e)
{

	ListNodePosi(T) x = new ListNode(e,this,succ);

	succ -> pred = x;

	succ = x;

	return x;

}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{

	init();

	while(n--){insertAsLast(p -> data); p = p->succ;}

}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n)
{

	copyNodes(p,n);

}

template <typename T>
List<T>::List(List<T> const &L)
{

	copyNodes(L.first(),L._size);

}

template <typename T>
List<T>::List(List<T> const & L, int r, int n)
{

	copyNodes(L[r], n);

}

template <typename T>T List<T>::remove(ListNodePosi(T) p)//删除合法节点p
{

	T e = p -> data;

	p -> pred -> succ = p -> succ;

	p -> succ -> pred = p -> pred;

	delete p;

	_size --;

	return e;

}

template <typename T> List<T>::~List()
{

	clear();

	delete header;

	delete trailer;

}

template <typename T> List<T>::clear(){
	
	int oldsize = _size;

	while(0 < _size) remove(header -> succ);

	return oldsize;
}

template <typename T> int List<T>::deduplicate()//始终保留最后一个出现的唯一样本
{

	if(_size < 2) return 0;

	int oldsize = _size;

	ListNodePosi(T) p = header; Rank r = 0;

	while(trailer != (p = p -> succ))
	{

		ListNodePosi(T) q = find(p -> data, r, p);

		q? remove(q): r++;

	}

	return oldsize - _size;
}

template <typename T> 
void List<T>::traverse(void (*visit) (T&))
{
	for (ListNodePosi(T) p = header ->succ;p != trailer;p = p->succ)
	{
		/* code */
		visit(p->data);

	}
}

template <typename T> template <typename VTS>//操作器
void List<T>::traverse(VTS & visit)
{
	for (ListNodePosi(T) p = header ->succ;p != trailer;p = p->succ)
	{
		/* code */
		visit(p->data);

	}
}

template <typename T> int List<T>::uniquify(){
	
	if(_size < 2) return 0;

	int oldsize = _size;

	ListNodePosi(T) p = first();

	while( p != trailer)
	{

		p = p -> succ;

		if(p->pred -> data != p -> data) remove(p -> pred);

	}

	return oldsize - _size;
}


template <typename T>
ListNodePosi(T) List<T>::search(T const & e, int n, ListNodePosi(T) p) const//在p的n个真前驱中找到不大于e的最后者
{

	while( 0 <= n--)
		
		if(((p = p -> pred)-> data )<= e) break;

	return p;

}

template <typename T> void List<T>::sort(int method, ListNodePosi(T) p, int n)
{

	switch(method)
	{

		case 1: insertionSort(p, n); break;

		case 2: selectionSort(p, n); break;

		default: mergeSort(p, n); break;

	}

}

template <typename T> 
void List<T>::insertionSort(ListNodePosi(T) p, int n)//对起始于p的n个元素排序
{

	for (int r = 0; r < n; r++)
	{
		/* code */

		insertA(search(p -> data, r, p), p -> data);

		p = p -> succ;

		remove(p -> pred);

	}

}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)//从起始于p的n个元素中选出最大者
{

	ListNodePosi(T) max = p;

	for (ListNodePosi(T) cur = p ; 1 < n; n--)
	{
		/* code */
		if (!lt((cur = cur -> succ) -> data,max -> data))
		{
			/* code */
			max = cur;
		}
	}

	return max;

}

template <typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n)
{

	ListNodePosi(T) head = p -> pred;

	ListNodePosi(T) tail = p;

	for (int i = 0; i < n; ++i)
	{
		/* code */
		tail = tail -> succ;

	}

	while(1 < n)
	{

		ListNodePosi(T) max = selectMax(head -> succ, n);

		insertB(tail, remove(max));

		tail = tail -> pred;

		n--;

	}

}

template <typename T>//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
void List<T>::merge(ListNodePosi(T) & p, int n, List<T> & L, ListNodePosi(T) q, int m)
{

	ListNodePosi(T) pp = p-> pred;

	while(0 < m)

		if((0 < n) && (p->data <= q -> data))
		{

			if( q == (p = p->succ)) break;
			
			n--;

		}
		else{

			insertB(p, L.remove((q = q-> succ) -> pred));

			m--;

		}

	p = pp->succ;
}


template <typename T>
void List<T>::mergeSort(ListNodePosi(T) &p, int n)
{

	if(n<2) return;

	int m = n>>1;

	ListNodePosi(T) q = p;

	for (int i = 0; i < m; i++)
	{
		/* code */
		q = q-> succ;
	}

	mergeSort(p,m);

	mergeSort(q, n-m);

	merge(p, m, *this, q, n-m);
}

/*******************************************
 * @name	BinNode
 * @brief 	二叉树节点标准模板
********************************************/

template <typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{return lc = new BinNode(e,this);}//将e作为当前节点的左孩子插入二叉树
template <typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{return rc = new BinNode(e,this);}//将e作为当前节点的左孩子插入二叉树

template <typename T, typename VST>
static void visitAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)> & S)
{
	while(x)
	{
		visit(x->data);
		if(x -> rc != NULL) S.push(x->rc); 
		x = x->lc;
	}
}
template <typename T> template <typename VST>
void BinNode<T>::travPre(VST& visit)	//先序遍历
{
	Stack<BinNodePosi(T)> S;
	BinNodePosi(T) x = this;
	while(true)
	{
		visitAlongLeftBranch(x, visit, S);
		if(S.empty()) break;
		x = S.pop();
	}
}

template <typename T, typename VST>
static void goAlongLeftBranch(BinNodePosi(T) x, VST& visit, Stack<BinNodePosi(T)> & S)
{
	while(x)
	{
		S.push(x);
		x = x->lc;
	}
}
template <typename T> template <typename VST>
void BinNode<T>::travIn(VST& visit)	//先序遍历
{
	Stack<BinNodePosi(T)> S;
	BinNodePosi(T) x = this;
	while(true)
	{
		goAlongLeftBranch(x, visit, S);
		if(S.empty()) break;
		x = S.pop();
		visit(x->data);
		x=x->rc;
	}
}

template <typename T> template <typename VST>
void BinNode<T>::travLevel(VST& visit)	//先序遍历
{
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);
	while(!Q.empty())
	{
		BinNodePosi(T) x=Q.dequeue();
		visit(x->data);
		if(HasLChild(*x)) Q.enqueue(x->lc);
		if(HasRChild(*x)) Q.enqueue(x->rc);
	}
}

/*******************************************
 * @name	BinTree
 * @brief 	二叉树标准模板
********************************************/
//树的高度更新
template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)
{return x->height = 1 + max(stature(x->lc), stature(x->rc));}
template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x) {updateHeight(x); x=x->parent;}
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{_size = 1; return _root = new BinNode<T>(e);} //将e当作根节点插入空的二叉树

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;} 

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{_size++; x->insertAsRC(e); updateHeightAbove(x); return x->lc;} 

template <typename T>	//将S当作节点x的左子树接入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T> * &S)	//T作为x左子树接入
{
	if(x->lc = S->_root) x->lc->parent = x;
	_size += S._size; updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	release(S);
	S = NULL;
	return x;
}

template <typename T>	//将S当作节点x的右子树接入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T> * &S)	//T作为x左子树接入
{
	if(x->rc = S->_root) x->rc->parent = x;
	_size += S._size; updateHeightAbove(x);
	S->_root = NULL;
	S->_size = 0;
	release(S);
	S = NULL;
	return x;
}

template <typename T>	//删除二叉树中位置x处的节点及其后代，返回被删除节点的数量
int BinTree<T>::remove(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x -> parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template <typename T>	//删除二叉树中位置x处的节点及其后代，返回被删除节点的数量
static int removeAt(BinNodePosi(T) x)
{
	if(!x) return 0;
	int n = 1 + removeAt(x -> lc) + removeAt(x->rc);
	release(x->data);
	release(x);
	return n;
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	BinTree<T> * S = new BinTree<T>;
	S->_root = x;
	x->parent =NULL;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}
