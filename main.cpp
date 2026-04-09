#include <iostream>

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

template <class T, size_t K> BTree<T, K> *maximum(BTree<T, K> *root)
{
  if (!root)
  {
    return root;
  }
  while (root->children[K])
  {
    root = root->children[K];
  }
  return root;
}

template <class T, size_t K> BTreeIt<T, K> begin(BTree<T, K> *tree)
{
  return {0, minimum(tree)};
}

template <class T, size_t K> BTreeIt<T, K> rbegin(BTree<T, K> *tree)
{
  return {K - 1, maximum(tree)};
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
      if (parent->children[size] != next)
      {
        size_t i = 0;
        for (; i < size && parent->children[i] != next; ++i)
        {
        }
        if (i < size)
        {
          ind = i;
          break;
        }
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
  BTree<T, K> *prev = it.current;
  size_t ind = it.s;
  size_t size = K;

  if (!prev)
  {
    return it;
  }
  if (prev->children[ind])
  {
    prev = maximum<T, K>(prev->children[ind]);
    ind = size - 1;
  }
  else if (ind > 0)
  {
    --ind;
  }
  else
  {
    BTree<T, K> *parent = prev->parent;
    while (parent)
    {
      if (parent->children[0] != prev)
      {
        size_t i = size;
        for (; i > 0 && parent->children[i] != prev; --i)
        {
        }
        if (i > 0)
        {
          ind = i - 1;
          break;
        }
      }
      prev = parent;
      parent = prev->parent;
    }
    prev = parent;
  }
  return {ind, prev};
}
template <class T, size_t K> bool hasNext(BTreeIt<T, K> it)
{
  return next(it).current; // Сделал по аналогии с классной работой
}

template <class T, size_t K> bool hasPrev(BTreeIt<T, K> it)
{
  return prev(it).current; // Сделал по аналогии с классной работой
}

template <class T, size_t K> void clear(BTree<T, K> *root)
{
  if (!root)
  {
    return;
  }
  for (size_t i = 0; i < K + 1; ++i)
  {
    clear(root->children[i]);
  }
  delete root;
}

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
  std::cout << "--- Тест последовательного обхода 4-дерева ---\n";

  while (hasNext(it))
  {
    std::cout << value(it) << " ";
    it = next(it);
  }

  std::cout << value(it);

  std::cout << "\n--- Тест завершен ---\n";

  std::cout << "--- Тест обратного обхода 4-дерева ---\n";

  auto r_it = rbegin(root);
  while (hasPrev(r_it))
  {
    std::cout << value(r_it) << " ";
    r_it = prev(r_it);
  }

  std::cout << value(r_it);

  std::cout << "\n--- Тест завершен ---\n";

  clear<int, 3>(root);

  BTree<int, 1> *root2 = new BTree<int, 1>{{}, {}, nullptr};
  root2->val[0] = 10;
  root2->parent = nullptr;

  BTree<int, 1> *leftChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftChild2->val[0] = 5;
  leftChild2->parent = root2;

  root2->children[0] = leftChild2;

  BTree<int, 1> *leftleftChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftleftChild2->val[0] = 3;
  leftleftChild2->parent = leftChild2;

  leftChild2->children[0] = leftleftChild2;

  BTree<int, 1> *leftleftleftChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftleftleftChild2->val[0] = 2;
  leftleftleftChild2->parent = leftleftChild2;

  leftleftChild2->children[0] = leftleftleftChild2;

  BTree<int, 1> *leftleftleftleftChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftleftleftleftChild2->val[0] = 1;
  leftleftleftleftChild2->parent = leftleftleftChild2;

  leftleftleftChild2->children[0] = leftleftleftleftChild2;

  BTree<int, 1> *leftleftleftrightChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftleftleftrightChild2->val[0] = 4;
  leftleftleftrightChild2->parent = leftleftChild2;

  leftleftChild2->children[1] = leftleftleftrightChild2;

  BTree<int, 1> *leftrightChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftrightChild2->val[0] = 8;
  leftrightChild2->parent = leftChild2;

  leftChild2->children[1] = leftrightChild2;

  BTree<int, 1> *leftrightleftChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftrightleftChild2->val[0] = 6;
  leftrightleftChild2->parent = leftrightChild2;

  leftrightChild2->children[0] = leftrightleftChild2;

  BTree<int, 1> *leftrightleftrightChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftrightleftrightChild2->val[0] = 7;
  leftrightleftrightChild2->parent = leftrightleftChild2;

  leftrightleftChild2->children[1] = leftrightleftrightChild2;

  BTree<int, 1> *leftrightrightChild2 = new BTree<int, 1>{{}, {}, nullptr};
  leftrightrightChild2->val[0] = 9;
  leftrightrightChild2->parent = leftrightChild2;

  leftrightChild2->children[1] = leftrightrightChild2;

  BTree<int, 1> *rightChild2 = new BTree<int, 1>{{}, {}, nullptr};
  rightChild2->val[0] = 15;
  rightChild2->parent = root2;

  root2->children[1] = rightChild2;

  BTree<int, 1> *rightrightChild2 = new BTree<int, 1>{{}, {}, nullptr};
  rightrightChild2->val[0] = 18;
  rightrightChild2->parent = rightChild2;

  rightChild2->children[1] = rightrightChild2;

  BTree<int, 1> *rightrightleftChild2 = new BTree<int, 1>{{}, {}, nullptr};
  rightrightleftChild2->val[0] = 17;
  rightrightleftChild2->parent = rightrightChild2;

  rightrightChild2->children[0] = rightrightleftChild2;

  auto it2 = begin(root2);
  std::cout << "--- Тест последовательного обхода 2-дерева ---\n";

  while (hasNext(it2))
  {
    std::cout << value(it2) << " ";
    it2 = next(it2);
  }

  std::cout << value(it2);

  std::cout << "\n--- Тест завершен ---\n";

  std::cout << "--- Тест обратного обхода 2-дерева ---\n";

  auto r_it2 = rbegin(root2);
  while (hasPrev(r_it2))
  {
    std::cout << value(r_it2) << " ";
    r_it2 = prev(r_it2);
  }

  std::cout << value(r_it2);

  std::cout << "\n--- Тест завершен ---\n";

  clear<int, 1>(root2);

  return 0;
}
