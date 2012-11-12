#ifndef __AVL_TREE_H__
# define __AVL_TREE_H__

template <typename T>
class AVLTree {

public:

  class Node {
  public:
    Node(T value, Node* parent = 0, Node* left = 0, Node* right = 0, int height = 0) :
      _value(value), _parent(0), _left(left), _right(right), _height(0) {
    }

    const Node*		parent() const { return this->_parent; }
    Node*		parent() { return this->_parent; }
    void       		parent(Node* parent) { this->_parent = parent; }

    const Node*		left() const { return this->_left; }
    Node*		left() { return this->_left; }
    void       		left(Node* left) { this->_left = left; }

    const Node*		right() const { return this->_right; }
    Node*		right() { return this->_right; }
    void       		right(Node* right) { this->_right = right; }

    T&			value() { return this->_value; }
    void		value(const T& value) { this->_value = value; }

    T&			height() { return this->_height; }
    void		height(const T& value) {
      Node* tmp = this;
      int i = value;
      for (; tmp != 0; tmp = tmp->parent(), ++i) {
	if (tmp->height() < i)	tmp->_height = i;
      }
    }

  private:
    T		_value;
    Node*	_parent;
    Node*	_left;
    Node*	_right;
    int		_height;
  };

  AVLTree() :
    _root(0) {
  }

  void	push(const T& value) {
    Node*	newNode = new Node(value);

    if (this->_root == 0) {
      this->_root = newNode;
    } else {
      Node* t = this->__iterate<&AVLTree<T>::__canGoLeft, &AVLTree<T>::__canGoRight>(this->_root, value);
      if (t->value() < value) {
	std::cout << "Add To :" << t->value() << " on Right" << std::endl;
	t->right(newNode);
      }
      else {
	std::cout << "Add To :" << t->value() << "on Left" << std::endl;
	t->left(newNode);
      }
      newNode->parent(t);
      newNode->height(0);
      t = this->__getNode< &AVLTree<T>::__isNotBalanced>((*this)._root);
      if (t != 0) {
	std::cout << "Desequilibre" << std::endl;
	if (this->__zigZigRight(t) == true ||
	    this->__zigZagRight(t) == true ||
	    this->__zigZigLeft(t) == true ||
	    this->__zigZagLeft(t) == true)
	  return ;
	/*std::cout << "NODE non equilibre : " << t->value() << " ZigZigDroit : " << this->__zigZigRight(t) << 
	  " ZigZagDroit : " << this->__zigZagRight(t) << " ZigZigGauche : " << this->__zigZigLeft(t) <<
	  " ZigZagGauche : " << this->__zigZagLeft(t) << std::endl;
	  exit(0);*/
      }
    }
  }

  void	applyToTree(void (*func)(T&), Node* current = 0) {
    if (this->_root == 0) return ;
    else if (current == 0) this->applyToTree(func, this->_root);
    else {
      func(current->value());
      if (current->left() != 0) {
	std::cout << "Left" << std::endl;
	this->applyToTree(func, current->left());
      }
      if (current->right() != 0) {
	std::cout << "Right" << std::endl;
	this->applyToTree(func, current->right());
      }
    }
  }

private:

template <bool (AVLTree<T>::*canGoLeft)(Node*, const T&),
	  bool (AVLTree<T>::*canGoRight)(Node*, const T&)>
Node*	__iterate(Node* current, const T& value) {
  if ((this->*canGoLeft)(current, value) == true) {
    std::cout << "Go Left" << std::endl;
      return this->__iterate<canGoLeft, canGoRight>(current->left(), value);
    }
    else {
      if ((this->*canGoRight)(current, value) == true) {
	std::cout << "Go Right" << std::endl;
	return this->__iterate<canGoLeft, canGoRight>(current->right(), value);
      }
      return current;
    }
    return 0;
  }

  bool	__canGoLeft(Node* node, const T& value) {
    if (node->left() == 0) return false;
    if (value > node->value()) return false;
    return true;
  }

  bool	__canGoRight(Node* node, const T& value) {
    if (node->right() == 0) return false;
    if (value < node->value()) return false;
    return true;
  }

  template <bool (AVLTree<T>::*predicat)(Node*, const T&)>
  Node*	__getNode(Node* current, const T& value = 0) {
    if (current == 0) return 0;
    if ((this->*predicat)(current, value) == true) return current;

    Node* result = 0;
    if ((result = this->__getNode<predicat>(current->left(), value)) != 0) return result;
    if ((result = this->__getNode<predicat>(current->right(), value)) != 0) return result;
    return 0;
   }

  bool	__isNotBalanced(Node* current, const T&) {
    std::cout << "Eq on " << current->value() << std::endl;
    if (current->left() != 0 && current->right() != 0) {
      int res = current->left()->height() - current->right()->height();
      if (res < -1 || res > 1) return true;
    }
    else if (current->left() == 0 && current->right() && current->right()->height() >= 1) {
      return true;
    }
    else if (current->right() == 0 && current->left() && current->left()->height() >= 1) return true;
    return false;
  }

  bool	__zigZigRight(Node* node) {
    std::cout << "Zig Zig Right on "<<node->value() << std::endl;
    if (node->left() == this->__maxHeight(node->left(), node->right()))
      return false;
    if (node->right()->left() == this->__maxHeight(node->right()->left(), node->right()->right()))
      return false;
    this->__zigZigRightSwap(node);
    return true;
  }

  bool	__zigZigRightSwap(Node* node) {
    Node* swap = node->right()->left();

    node->right()->left(node);
    node = node->right();
    node->left()->right(swap);
    if (swap != 0) swap->parent(node->left());

    if (node->left()->parent() == 0) {
      node->parent(0);
      this->_root = node;
    }
    node->left()->parent(node);
  }

  bool	__zigZagRight(Node* node) {
    std::cout << "Zig Zag Right on "<<node->value() << std::endl;
    if (node->left() == this->__maxHeight(node->left(), node->right()))
      return false;
    if (node->right()->right() == this->__maxHeight(node->right()->left(), node->right()->right()))
      return false;
    this->__zigZagRightSwap(node);
    return true;
  }

  void	__zigZagRightSwap(Node* node) {
    Node* swap = node->right()->left();

    node->right()->left(node);
    node = node->right();
    node->left()->right(swap);
    swap->parent(node->left());

    if (node->left()->parent() == 0) {
      node->parent(0);
      this->_root = node;
    }
    node->left()->parent(node);
  }

  bool	__zigZigLeft(Node* node) {
    std::cout << "Zig Zig Left on "<< node->value() << std::endl;
    if (node->right() == this->__maxHeight(node->left(), node->right()))
      return false;
    if (node->left()->right() == this->__maxHeight(node->left()->left(), node->left()->right()))
      return false;
    this->__zigZigLeftSwap(node);
    return true;
  }

  void	__zigZigLeftSwap(Node* node) {
    Node* swap = node->left()->right();
    if (swap != 0) swap->parent(node);
    node->left()->right(node);
    node->left()->parent(node->parent());
    if (node->parent() == 0) this->_root = node->left();
    node->left(swap);
    node->parent(node->left());
  }

  bool	__zigZagLeft(Node* node) {
    std::cout << "Zig Zag Left on "<<node->value() << std::endl;
    if (node->right() == this->__maxHeight(node->left(), node->right()))
      return false;
    if (node->left()->left() == this->__maxHeight(node->left()->left(), node->left()->right()))
      return false;

    /*
    //SIDA
    std::cout << node->left() << std::endl;
    std::cout << "GO" << std::endl;
    Node* swap = node->left()->right()->left();
    std::cout << "0" << std::endl;
    node->left()->right()->left(node->left());

    std::cout << "1" << std::endl;
    node->left(node->left()->right());

    std::cout << "2" << std::endl;
    node->left()->left()->right(swap);
    if (swap != 0) swap->parent(node->left()->left());

    if (node->left()->right() != 0) {
      std::cout << "3" << std::endl;
      std::cout << "Value : " << node->left()->right()->value() << std::endl;
      node->left()->right()->parent(node);
    }
    std::cout << "4" << std::endl;
    node->left()->parent(node->left()->right());
    std::cout << "Zig Zag Left !!!" << std::endl;
    */
//exit(0);
    return true;
  }

  Node*	__maxHeight(Node* node1, Node* node2) {
    if (node1 == 0) return node2;
    else if (node2 == 0) return node1;

    if (node1->height() > node2->height()) return node1;
    return node2;
  }


private:
  Node*		_root;
};

#endif
