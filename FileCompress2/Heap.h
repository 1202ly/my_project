#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#if 1
template<class T>
class Less
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};
template<class T>
class Greator
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template < class T, class Compare = Less<T>>
class Heap
{
public:
	Heap()
	{}
	Heap(const T* array, size_t size)
	{
		//将数组中的元素存起来（完全二叉树）
		_array.reserve(size);
		for (size_t i = 0; i < size; i++)
		{
			_array.push_back(array[i]);
		}
		//调整
		//2.找完全二叉树中倒数第一个非叶子节点
		int pRoot = (size - 1 - 1) >> 1;//（最后一个元素的下标-1）/2
		for (; pRoot >= 0; --pRoot)
		{
			_AdjustDown(pRoot);//向下调整
		}
	}
	void Push(const T& data)
	{
		_array.push_back(data);
		if (_array.size() > 1)
		{
			_AdjustUp(_array.size() - 1);
		}
	}
	void Pop()
	{
		size_t size = _array.size() - 1;//最后一个元素的下标
		//空堆，直接返回
		if (Empty())
		{
			return;
		}
		//只有一个元素，直接删除
		else if (_array.size() == 1)
		{
			_array.pop_back();
		}
		//如果有多个元素，删除堆顶元素
		else
		{
			swap(_array[0], _array[size]);
			_array.pop_back();
			if (_array.size() > 1)
			{
				_AdjustDown(0);
			}
		}
	}
	T Top()const
	{
		return _array[0];
	}
	bool Empty()const
	{
		return _array.empty();
	}
	size_t Size()const
	{
		return _array.size();
	}

private:
	void _AdjustDown(size_t parent)
	{
		Compare com;
		//标记左右孩子中最小的孩子（默认左孩子最小）
		size_t child = parent * 2 + 1;
		size_t size = _array.size();
		while (child<size)
		{
			//找左右孩子中最小的孩子
			if (child + 1 < size && com(_array[child + 1], _array[child]))
			{
				child = child + 1;//最小的更改为右孩子
			}
			//判断双亲和孩子是否需要交换调整
			if (com(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}
	void _AdjustUp(size_t child)//此时child为下标
	{
		Compare com;
		size_t parent = (child - 1) >> 1;
		while (child > 0)
		{
			if (com(_array[child], _array[parent]))
			{
				swap(_array[parent], _array[child]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
				break;
		}
	}
private:
	std::vector<T> _array;
};
#endif
///////////////////////////////////单元测试///////////////////////////////
//void TestHeap()
//{
//	int array[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
//	Heap<int>hp(array, sizeof(array) / sizeof(array[0]));
//	cout << "hp.Top()=" << hp.Top() << endl;
//	cout << "hp.Size()=" << hp.Size() << endl;
//	hp.Push(5);
//	cout << "hp.Top()=" << hp.Top() << endl;
//	cout << "hp.Size()=" << hp.Size() << endl;
//	hp.Pop();
//	cout << "hp.Top()=" << hp.Top() << endl;
//	cout << "hp.Size()=" << hp.Size() << endl;
//	if (hp.Empty())
//	{
//		cout << "为空" << endl;
//	}
//	else
//	{
//		cout << "非空" << endl;
//	}
//}
