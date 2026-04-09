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
  return &it.current->val[it.s];
}

template <class T, size_t K> BTree<T, K> *minimum(BTree<T, K> *root)
{
  if (!root)
  {
    return {0, root};
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
  BTree<T, K> next = it.current;
  size_t ind = it.s;
  size_t size = K;

  if (!next)
  {
    return it;
  }
  if (ind < size)
  {
    if (next.children[ind + 1])
    {
      next = minimum(next.children[ind + 1]);
      ind = 0;
    }
    else
    {
      ++ind;
    }
  }
  else
  {
    BTree<T, K> *parent = next.parent;
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
      parent = next.parent;
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
