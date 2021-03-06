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
  /*  std::cout << std::endl << std::endl << "ajout de -10" << std::endl;
  t.push(-10);

  std::cout << std::endl << std::endl << "ajout de -11" << std::endl;
  t.push(-9);
  */
  /*std::cout << "ajout de -12" << std::endl;
  t.push(-12);
  */
  /*std::cout << "ajout de -13" << std::endl;
    t.push(-13);*/

  std::cout << "ajout de 15" << std::endl;
  t.push(15);
  std::cout << "ajout de 10" << std::endl;
  t.push(10);

  /*
    std::cout << "ajout de 21" << std::endl;
    t.push(21);
    std::cout << "ajout de 23" << std::endl;
    t.push(23);
  */
  //t.push(1);
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

	 1
	   \
	   15
	  /
	 10

       1
        \
	 10
	   \
	    15

	    10
	  /   \
	  1    15
 
	 [1 : NULL : 15];
	 [15 : 10 : NULL]
	 [10 : NULL : NULL]


	 Swap : NULL
	 [1 : NULL : 15];
	 [15 : 10 : NULL]
	 [10 : NULL : 15]

	 Swap : NULL
	 [1 : NULL : 10];
	 [15 : 10 : NULL]
	 [10 : NULL : 15]

	 Swap : NULL
	 [1 : NULL : 10];
	 [15 : 10 : NULL]
	 [10 : Swap : 15]

	 Swap : NULL
	 [1 : NULL : 10];
	 [15 : 10 : NULL]
	 [10 : 1 : 15]

*/
