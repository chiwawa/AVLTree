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
  std::cout << "ajout de -1" << std::endl;
  t.push(-1);

  std::cout << "ajout de -10" << std::endl;
  t.push(-10);

  std::cout << "ajout de -5" << std::endl;
  t.push(-5);

  std::cout << "ajout de -6" << std::endl;
  t.push(-6);

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
    -1	      15
	    /   \
	  10	21
	         \
		 23
*/
