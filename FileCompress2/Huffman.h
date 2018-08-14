#define _CRT_SECURE_NO_WARNINGS 1
#pragma once;
template<class W>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const W& weight)
	:_pleft(NULL)
	, _pright(NULL)
	, _parent(NULL)
	, _weight(weight)
	{}
	HuffmanTreeNode<W>* _pleft;
	HuffmanTreeNode<W>* _pright;
	HuffmanTreeNode<W>* _parent;
	W _weight;//权值
};

template<class W>
class HuffmanTree
{
	typedef HuffmanTreeNode<W> node;
	typedef node* pnode;
public:
	HuffmanTree()
		:_proot(NULL)
	{}
	HuffmanTree(W* array, size_t size, const W& index)
	{
		CreateTree(array, size, index);
	}
	~HuffmanTree()
	{
		Destroy(_proot);
	}
	pnode Getroot()
	{
		return _proot;
	}
private:
	void CreateTree(W* array, size_t size, const W& index)//index无效值
	{
		struct LESS
		{
			bool operator()(pnode pLeft, pnode pRight)
			{
				return pLeft->_weight < pRight->_weight;
			}
		};
		Heap<pnode, LESS> hp;
		for (size_t i = 0; i < size; i++)
		{
			if (array[i] != index)
				hp.Push(new node(array[i]));
		}
		if (hp.Empty())
		{
			_proot = NULL;
		}
		while (hp.Size()>1)
		{
			pnode pLeft = hp.Top();
			hp.Pop();
			pnode pRight = hp.Top();
			hp.Pop();

			pnode pParent = new node(pLeft->_weight + pRight->_weight);
			pParent->_pleft = pLeft;
			pLeft->_parent = pParent;

			pParent->_pright = pRight;
			pRight->_parent = pParent;
			hp.Push(pParent);
		}
		_proot = hp.Top();
	}
	void Destroy(pnode& pRoot)
	{
		if (pRoot)
		{
			Destroy(pRoot->_pleft);
			Destroy(pRoot->_pright);
			delete pRoot;
			pRoot = NULL;
		}
	}
private:
	pnode _proot;
};
