#include <iostream>
#include "AVLTree.hpp"

void
display(int& t) {
  std::cout << t << std::endl;
}

int
main() {
  AVLTree<int>	t;

  std::cout << "ajout de 1" << std::endl;;
  t.push(1);
  std::cout << "ajout de -10" << std::endl;
  t.push(-10);

  std::cout << "ajout de -5" << std::endl;
  t.push(-5);

  std::cout << "ajout de -4" << std::endl;
  t.push(-4);

  std::cout << "ajout de -3" << std::endl;
  t.push(-3);

  std::cout << "ajout de 15" << std::endl;
  t.push(15);
  std::cout << "ajout de 10" << std::endl;
  t.push(10);
  std::cout << "ajout de 21" << std::endl;
  t.push(21);
  std::cout << "ajout de 23" << std::endl;
  t.push(23);
  //t.push(1);*/
  t.applyToTree(display);
}
/*
	 1
      /	     \
    -10	      15
   /	    /   \
 -10	  10	21
  /               \
 -11	          23
  /
-12
*/
