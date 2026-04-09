#include <iostream>

template <class T> struct BiTree
{
  T val;
  BiTree<T> *lt, *rt;
  BiTree<T> *parent;
};

template <class T, class F> F traverse(BiTree<T> *root, F f)
{
  if (!root)
  {
    return f;
  }

  BiTree<T> *next = minimum(root);
  while (next)
  {
    f(next->val);
    if (next->rt)
    {
      next = next->rt;
      next = minimum(next);
    }
    else
    {
      BiTree<T> *parent = next->parent;
      while (parent && parent->lt != next)
      {
        next = parent;
        parent = parent->parent;
      }
      next = parent;
    }
  }
  return f;
}

template <class T> BiTree<T> *minimum(BiTree<T> *root)
{
  if (!root)
  {
    return root;
  }
  while (root->lt)
  {
    root = root->lt;
  }
  return root;
}

template <class T> struct BiTreeIt
{
  BiTree<T> *curr;
};

template <class T> T &value(BiTreeIt<T> it)
{
  return it.curr->val;
}

template <class T> BiTreeIt<T> next(BiTreeIt<T> it)
{
  BiTree<T> next = it.curr;
  if (next->rt)
  {
    next = next->rt;
    next = minimum(next);
  }
  else
  {
    BiTree<T> *parent = next->parent;
    while (parent && parent->lt != next)
    {
      next = parent;
      parent = parent->parent;
    }
    next = parent;
  }
  return {next};
}

template <class T> BiTreeIt<T> prev(BiTreeIt<T> it)
{
  BiTree<T> next = it.curr;
  if (next->lt)
  {
    next = next->lt;
    while (next->rt)
    {
      next = next->rt;
    }
  }
  else
  {
    BiTree<T> *parent = next->parent;
    while (parent && parent->rt != next)
    {
      next = parent;
      parent = parent->parent;
    }
    next = parent;
  }
  return {next};
}

template <class T> BiTreeIt<T> hasNext(BiTreeIt<T> it)
{
  return next(it).curr;
}

template <class T> BiTree<T> hasPrev(BiTreeIt<T> it)
{
  return prev(it).curr;
}

template <class T> struct TriTree
{
  T val0, val1;
  TriTree<T> *lt, *rt, *mid, *parent;
};

template <class T> struct TriTreeIt
{
  size_t s;
  TriTree<T> *curr;
};

template <class T> TriTree<T> *minimum(TriTree<T> *root)
{
  if (!root)
  {
    return root;
  }
  while (root->lt)
  {
    root = root->lt;
  }
  return root;
}

template <class T> TriTreeIt<T> next(TriTreeIt<T> it)
{
  TriTree<T> *next = it.curr;
  size_t ind = it.s;

  if (!next)
  {
    return it;
  }

  if (ind == 0)
  {
    if (next->mid)
    {
      next = next->mid;
      next = minimum(next);
      ind = 0;
    }
    else
    {
      ind = 1;
    }
  }
  else
  {
    if (next->rt)
    {
      next = next->rt;
      next = minimum(next);
      ind = 0;
    }
    else
    {
      TriTree<T> *parent = next->parent;
      while (parent)
      {
        if (parent->lt == next)
        {
          ind = 0;
          break;
        }
        if (parent->mid == next)
        {
          ind = 1;
          break;
        }
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
  return {next, ind};
}

template <class T> TriTreeIt<T> prev(TriTreeIt<T> it)
{
  TriTree<T> *next = it.curr;
  size_t ind = it.s;

  if (!next)
  {
    return it;
  }

  if (ind == 1)
  {
    if (next->mid)
    {
      next = next->mid;
      next = maximum(next);
      ind = 1;
    }
    else
    {
      ind = 0;
    }
  }
  else
  {
    if (next->lt)
    {
      next = next->lt;
      next = maximum(next);
      ind = 1;
    }
    else
    {
      TriTree<T> *parent = next->parent;
      while (parent)
      {
        if (parent->rt == next)
        {
          ind = 1;
          break;
        }
        if (parent->mid == next)
        {
          ind = 0;
          break;
        }
        next = parent;
        parent = next->parent;
      }
      next = parent;
    }
  }
  return {next, ind};
}

template <class T> bool hasNext(TriTree<T> it)
{
  return next(it).curr;
}

template <class T> bool hasPrev(TriTree<T> it)
{
  return prev(it).curr;
}

template <class T, size_t K> struct BTree
{
  T val[K];
  BTree<T, K> *children[K + 1];
  BTree<T, K> *parent;
};

template <class T, size_t K> struct BTreeIt
{
  size_t s;
  BTree<T, K> *current;
};

template <class T, size_t K> T &value(BTreeIt<T, K> it)
{
  return it.current->val[it.s];
}

template <class T, size_t K> BTree<T, K> *minimum(BTree<T, K> *root)
{
  if (!root)
  {
    return root;
  }
  while (root->children[0])
  {
    root = root->children[0];
  }
  return root;
}

template <class T, size_t K> BTreeIt<T, K> begin(BTree<T, K> *tree)
{
  return {0, minimum(tree)};
}

template <class T, size_t K> BTreeIt<T, K> next(BTreeIt<T, K> it)
{
  BTree<T, K> *next = it.current;
  size_t ind = it.s;
  size_t size = K;

  if (!next)
  {
    return it;
  }
  if (ind < size && next->children[ind + 1])
  {
    next = minimum<T, K>(next->children[ind + 1]);
    ind = 0;
  }
  else if (ind < size - 1)
  {
    ++ind;
  }
  else
  {
    BTree<T, K> *parent = next->parent;
    while (parent)
    {
      if (parent->children[0] != next)
      {
        size_t i = 1;
        for (; i < size && parent->children[i] != next; ++i)
        {
        }
        if (i < size)
        {
          ind = i;
          break;
        }
      }
      else
      {
        ind = 0;
        break;
      }
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {ind, next};
}

template <class T, size_t K> BTreeIt<T, K> prev(BTreeIt<T, K> it)
{
}
template <class T, size_t K> bool hasNext(BTreeIt<T, K> it)
{
  return next(it).current;
}

template <class T, size_t K> bool hasPrev(BTreeIt<T, K> it);

int main()
{

  BTree<int, 3> *root = new BTree<int, 3>{{}, {}, nullptr};
  root->val[0] = 10;
  root->val[1] = 20;
  root->val[2] = 30;
  root->parent = nullptr;

  BTree<int, 3> *leftChild = new BTree<int, 3>{{}, {}, nullptr};
  leftChild->val[0] = 4;
  leftChild->val[1] = 8;
  leftChild->val[2] = 9;
  leftChild->parent = root;

  BTree<int, 3> *leftMidChild = new BTree<int, 3>{{}, {}, nullptr};
  leftMidChild->val[0] = 5;
  leftMidChild->val[1] = 6;
  leftMidChild->val[2] = 7;
  leftMidChild->parent = leftChild;

  leftChild->children[1] = leftMidChild;

  BTree<int, 3> *rootMidChild1 = new BTree<int, 3>{{}, {}, nullptr};
  rootMidChild1->val[0] = 12;
  rootMidChild1->val[1] = 15;
  rootMidChild1->val[2] = 17;
  rootMidChild1->parent = root;

  BTree<int, 3> *rootMidChild2 = new BTree<int, 3>{{}, {}, nullptr};
  rootMidChild2->val[0] = 22;
  rootMidChild2->val[1] = 23;
  rootMidChild2->val[2] = 25;
  rootMidChild2->parent = root;

  BTree<int, 3> *rootRightChild = new BTree<int, 3>{{}, {}, nullptr};
  rootRightChild->val[0] = 35;
  rootRightChild->val[1] = 40;
  rootRightChild->val[2] = 43;
  rootRightChild->parent = root;

  BTree<int, 3> *RightLeftChild = new BTree<int, 3>{{}, {}, nullptr};
  RightLeftChild->val[0] = 36;
  RightLeftChild->val[1] = 37;
  RightLeftChild->val[2] = 38;
  RightLeftChild->parent = rootRightChild;

  rootRightChild->children[1] = RightLeftChild;

  BTree<int, 3> *RightRightChild = new BTree<int, 3>{{}, {}, nullptr};
  RightRightChild->val[0] = 90;
  RightRightChild->val[1] = 95;
  RightRightChild->val[2] = 97;
  RightRightChild->parent = rootRightChild;

  rootRightChild->children[3] = RightRightChild;

  root->children[0] = leftChild;
  root->children[1] = rootMidChild1;
  root->children[2] = rootMidChild2;
  root->children[3] = rootRightChild;

  auto it = begin(root);
  std::cout << "--- Тест последовательного обхода ---\n";

  while (hasNext(it))
  {
    std::cout << value(it) << " ";
    it = next(it);
  }

  std::cout << value(it);

  std::cout << "\n--- Тест завершен ---\n";

  delete leftChild;
  delete leftMidChild;
  delete rootMidChild1;

  delete rootMidChild2;
  delete rootRightChild;
  delete RightLeftChild;

  delete RightRightChild;
  delete root;

  return 0;
}
