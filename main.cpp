//Neel Madala
//5/3/2024
//This code creates a red black search tree which automatically balances itself in order to optimize search time where any leaf of the tree can only be one additional level deeper than every other leaf. If not it balances itself with rotation to make it so

//Assistance from Nathan Zou, Lucas Johnson, Roger Li, Noam Yaffe


#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include "node.h"

//Colors
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m"

using namespace std;

struct Trunk { //Used for printing
    Trunk* previous;
    char* str;

    Trunk(Trunk* previous, char* str) {
        this->previous = previous;
        this->str = str;
    }
};

void showTrunks(Trunk* p) {
    if (p == NULL)
        return;

    showTrunks(p->previous);

    cout << p->str;
}

//Prototypes
void ADD(Node*& head, Node*& current, Node*& previous, int value);
void PRINT(Node* root, Trunk* previous, bool isLeft);
bool search(Node* tree, int s);
void DELETE(Node* &head, Node* &x);

void BALANCE(Node*& head, Node*& current);
void rotateLeft(Node*& head, Node*& current);
void rotateRight(Node*& head, Node*& current);

Node* getSibling(Node* &x);
Node* successor(Node* &x);
Node* replaceNode(Node* &x);
bool hasRedChild(Node* &x);
void fixDoubleBlack(Node* &head, Node* &x);
void swapNodeValues(Node* &u, Node* &x);


int main(){
  cout << "Welcome to BST" << endl << endl;
  bool looping = true;
  bool adding = true;
  char command[10];
  char input[3200];
  int value = -1;
  Node* tree = nullptr;
  while(looping == true) {
    cout <<"ADD, SEARCH, PRINT, or QUIT?" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(command, "ADD") == 0) {//Add to Red black tree
      adding = true;
      cout << "Are you adding by console or file? (c/f)" << endl;//console or file
      cin.get(command, 2);
      cin.clear();
      cin.ignore(10000, '\n');
      if(strcmp(command, "c") == 0) {
	cout << "Enter you input of numbers seperated by spaces and put a -1 at end of the list" << endl;
	while(adding == true) {
	  cin >> value;
	  if(value == -1) {
	    adding = false;
	  }
	  else {
	    Node* current = tree;
	    Node* previous = NULL;
	    ADD(tree, current, previous, value);
	  }
	}
	cin.clear();
	cin.ignore(10000, '\n');
      }
      else if(strcmp(command, "f") == 0) {//adds by file max being 10 in the file I am testing with add another file call it number.txt and it can be any max
	int inputNum;
	cout << "How many numbers are you gonna input?" << endl;
	cin >> inputNum;
	cin.clear();
	cin.ignore(1000, '\n');
        
	ifstream numbers("numbers.txt");
	int numdone = 0;
	while(numbers >> value && numdone < inputNum) {//go through the file and add to BST and then go to the next int until it adds how many the user wanted
	  Node* current = tree;
	  Node* previous = NULL;
	  ADD(tree, current, previous, value);
	  numdone++;
	}
      }
      else {
	cout << "Invalid input" << endl;
      }
    }
    else if(strcmp(command, "SEARCH") == 0) {//Search through Red-Black Tree for a integer
      cout << "Enter the number you are searching " << endl;
      int searchInt;
      cin >> searchInt;
      cin.clear();
      cin.ignore(10000, '\n');
      bool inTree = search(tree, searchInt);
      if(inTree == true) {
	cout << "That number is in the tree" << endl;
      }
      else {
	cout << "That number isn't in the tree" << endl;
      }
    }
    else if(strcmp(command, "REMOVE") == 0) {//Delete from tree
      cout << "Enter the number you are deleteing" << endl;
      int deleteInteger;
      cin >> deleteInteger;
      cin.clear();
      cin.ignore(10000, '\n');
      bool checkValue = search(tree, deleteInteger);
      if(checkValue == 0) {
	cout << "Value no found in tree, cannot delete." << endl << endl;
      }
      else {
	Node* v = tree;
	while(v->getData() != value) {//not the right node
	  if(value < v->getData()) {//less than the current node
	    v = v->getLeft();
	  }
	  else  if (value > v->getData()) {//greater than the current node
	    v = v->getRight();
	  }
	}
	DELETE(tree, v);
	cout << "Done deleteing" << endl;
    }
    else if(strcmp(command, "PRINT") == 0) {//PRINT out tree
      PRINT(tree, NULL, false);
    }
    else if(strcmp(command, "QUIT") == 0) {//quits
      looping = false;
      cout << "Thanks for utilizing this code" << endl;
    }
  }
}

bool search(Node* tree, int s) {//searches for int s in search tree
  if(tree == nullptr) {//reach the end of the tree and havent found number than not in tree
    return false;
  }
  else {
    int treeD = tree->getData();
    if(treeD == s) {//if equal found the number
      return true;
    }
    else if(treeD > s) {//go down left child if smaller than parent
      return search(tree->getLeft(), s);
    }
    else if(treeD < s) {//go down right child if larger than parent
      return search(tree->getRight(), s);
    }
  }
  return false;
}

void ADD(Node*& head, Node*& current, Node*& previous, int value) { //Add function, manually add in a node
    if (head == NULL) {
        head = new Node();
        current = head;
        head->setData(value);
        head->setColor(0); //Head is always black
    }
    else {
        if (value < current->getData()) {
            previous = current;
            current = current->getLeft();
            if (current == NULL) {
                current = new Node();
                current->setData(value);
                previous->setLeft(current);
                current->setParent(previous);
                BALANCE(head, current);
                return;
            }
            else {
                ADD(head, current, previous, value);
            }
        }
        else {
            previous = current;
            current = current->getRight();
            if (current == NULL) {
                current = new Node();
                current->setData(value);
                previous->setRight(current);
                current->setParent(previous);
                BALANCE(head, current);
                return;
            }
            else {
                ADD(head, current, previous, value);
            }
        }
    }
}
void BALANCE(Node*& head, Node*& current) { //Balance function, for Red-Black Tree properties
    Node* parent = NULL;
    Node* grandParent = NULL;
    while ((current != head) && (current->getColor() != 0) && ((current->getParent())->getColor() == 1)) {
        parent = current->getParent();
        grandParent = parent->getParent();
        //Case A: Parent = left child of grandparent
        if (parent == grandParent->getLeft()) {
            Node* uncle = grandParent->getRight();
            //Case 1A: Uncle = red, only recolor
            if (uncle != NULL && uncle->getColor() != 0) {
                grandParent->setColor(1); //Red
                parent->setColor(0); //Black
                uncle->setColor(0); //Black
                current = grandParent;
            }
            else {
                //Case 2A: Current = right child of parent, rotate left
                if (current == parent->getRight()) {
                    rotateLeft(head, parent);
                    current = parent;
                    parent = current->getParent();
                }
                //Case 3A: Current = left child of parent, rotate right
                rotateRight(head, grandParent);
                //swap colors of parent and grandparent
                int tempCol = parent->getColor();
                parent->setColor(grandParent->getColor());
                grandParent->setColor(tempCol);
                current = parent;
            }
        }
        //Case B: Parent = right child of grandparent
        else {
            Node* uncle = grandParent->getLeft();
            //Case 1B: Uncle = red, only recolor
            if (uncle != NULL && uncle->getColor() != 0) {
                grandParent->setColor(1); //Red
                parent->setColor(0); //Black
                uncle->setColor(0); //Black
                current = grandParent;
            }
            else {
                //Case 2B: Current = left child of parent, rotate right
                if (current == parent->getLeft()) {
                    rotateRight(head, parent);
                    current = parent;
                    parent = current->getParent();
                }
                //Case 3B: Current = right child of parent, rotate left
                rotateLeft(head, grandParent);
                //swap color of parent and grandparent
                int tempCol = parent->getColor();
                parent->setColor(grandParent->getColor());
                grandParent->setColor(tempCol);
                current = parent;
            }
        }
    }
    head->setColor(0); //head is black
}
void rotateLeft(Node*& head, Node*& current) { //Rotate Left
    Node* rightPointer = current->getRight();
    //begin rotation
    current->setRight(rightPointer->getLeft());
    if (current->getRight() != NULL) {
        (current->getRight())->setParent(current);
    }
    rightPointer->setParent(current->getParent());
    //if working with head
    if (current->getParent() == NULL) {
        head = rightPointer;
    }
    else if (current == (current->getParent())->getLeft()) {
        (current->getParent())->setLeft(rightPointer);
    }
    else {
        (current->getParent())->setRight(rightPointer);
    }
    rightPointer->setLeft(current);
    current->setParent(rightPointer);
}

void rotateRight(Node*& head, Node*& current) { //Rotate Right
    Node* leftPointer = current->getLeft();
    //being rotation
    current->setLeft(leftPointer->getRight());
    if (current->getLeft() != NULL) {
        (current->getLeft())->setParent(current);
    }
    leftPointer->setParent(current->getParent());
    //if working with head
    if (current->getParent() == NULL) {
        head = leftPointer;
    }
    else if (current == (current->getParent())->getLeft()) {
        (current->getParent())->setLeft(leftPointer);
    }
    else {
        (current->getParent())->setRight(leftPointer);
    }
    leftPointer->setRight(current);
    current->setParent(leftPointer);
}
//Adopted from Nathan Zou
void PRINT(Node* root, Trunk* previous, bool isLeft) { //Print functions, prints out tree
    if (root == NULL) {
        return;
    }
    char* prevStr = (char*)("    ");
    Trunk* trunk = new Trunk(previous, prevStr);
    PRINT(root->getLeft(), trunk, true);
    //Formatting tree
    if (!previous) {
        trunk->str = (char*)("---");
    }
    else if (isLeft) {
        trunk->str = (char*)(".---");
        prevStr = (char*)("   |");
    }
    else {
        trunk->str = (char*)("'---");
        previous->str = prevStr;
    }
    showTrunks(trunk);
    if (root->getColor() == 0) { //if Black
        cout << BLUE << root->getData() << RESET << endl;
    }
    else { //Red
        cout << RED << root->getData() << RESET << endl;
    }
    if (previous) {
        previous->str = prevStr;
    }
    trunk->str = (char*)("   |");
    PRINT(root->getRight(), trunk, false);
}
void DELETE(Node* &head, Node* &x) {
  Node* u = replaceNode(x);
  Node* parent = x->getParent();
  //Bool to track if both are black
  bool bothBlack = ((u == NULL || u->getColor() == 0) && (x == NULL || x->getColor() == 0));

  //If x has no children
  if (u == NULL) {
    if (x == head) {
      head = NULL;
    }
    else {
      if (bothBlack) {
	fixDoubleBlack(head, x);
      }
      else {
	//One is red -> make sibling red
	if (getSibling(x) != NULL) {
	  getSibling(x)->setColor(1);
	}
      }
      //Delete x from tree
      if (x == parent->getLeft()) {
	parent->setLeft(NULL);
      }
      else {
	parent->setRight(NULL);
      }
    }
    x->~Node();
    return;
  }

  //If x has 1 child
  if (x->getRight() == NULL || x->getLeft() == NULL) {
    if (x == head) {
      //Value of u goes to x
      x->setData(u->getData());
      x->setLeft(NULL);
      x->setRight(NULL);
      //Delete u
      u->~Node();
    }
    else {
      //Detach x from tree and move u up
      if (x == parent->getLeft()) {
	parent->setLeft(u);
      }
      else {
	parent->setRight(u);
      }
      //Delete x
      x->~Node();
      u->setParent(parent);
      if (bothBlack) {
	fixDoubleBlack(head, x);
      }
      else {
	//If one is red, color u black
	u->setColor(0);
      }
    }
    return;
  }

  //if x has 2 children
  swapNodeValues(u, x);
  DELETE(head, u);
}
Node* getSibling(Node* &x) {
  if (x->getParent() == NULL) {
    return NULL;
  }
  if (x == x->getParent()->getLeft()) {
    return x->getParent()->getRight();
  }
  else {
    return x->getParent()->getLeft();
  }
}

Node* successor(Node* &x) {
  //Get the left most value of right subtree
  Node* a = x;
  while (a->getLeft() != NULL) {
    a = a->getLeft();
  }
  return a;
}

Node* replaceNode(Node* &x) {
  //If node has 2 children
  if (x->getLeft() != NULL && x->getRight() != NULL) {
    Node* right = x->getRight();
    return successor(right);
  }
  //If node has no children
  else if (x->getLeft() == NULL && x->getRight() == NULL) {
    return NULL;
  }
  //If node has 1 child
  else {
    if (x->getLeft() != NULL) {
      return x->getLeft();
    }
    else {
      return x->getRight();
    }
  }
}

void swapNodeValues(Node* &u, Node* &x) {
  //Swap the int values between the two given nodes
  int temp;
  temp = u->getData();
  u->setData(x->getData());
  x->setData(temp);
}

void fixDoubleBlack(Node* &head, Node* &x) {
  if (x == head)
    return;

  Node* sibling = getSibling(x);
  Node* parent = x->getParent();

  if (sibling == NULL) {
    //if no sibling, push doublebalck up
    fixDoubleBlack(head, parent);
  } else {
    if (sibling->getColor() == 1) {
      //silbing is red
      parent->setColor(1); //red
      sibling->setColor(0); //black
      if (sibling == parent->getLeft()) {
	rotateRight(head, parent);
      } else {
	rotateLeft(head, parent);
      }
      fixDoubleBlack(head, x);
    } else {
      //sibling is black
      if (hasRedChild(sibling)) {
	//has at least 1 red child
	if (sibling->getLeft() != NULL && sibling->getLeft()->getColor() == 1) {
	  //sibling's left child is red
	  if (sibling == parent->getLeft()) {
	    //left left
	    sibling->getLeft()->setColor(sibling->getColor());
	    sibling->setColor(parent->getColor());
	    rotateRight(head, parent);
	  } else {
	    //right left
	    sibling->getLeft()->setColor(parent->getColor());
	    rotateRight(head, sibling);
	    rotateLeft(head, parent);
	  }
	} else {
	  //sibling's right child is red
	  if (sibling == parent->getLeft()) {
	    //left right
	    sibling->getRight()->setColor(parent->getColor());
	    rotateLeft(head, sibling);
	    rotateRight(head, parent);
	  } else {
	    //right right
	    sibling->getRight()->setColor(sibling->getColor());
	    sibling->setColor(parent->getColor());
	    rotateLeft(head, parent);
	  }
	}
	parent->setColor(0); //black
      } else {
	//two black children
	sibling->setColor(1); //red
	if (parent->getColor() == 0) {
	  fixDoubleBlack(head, parent); //recursion
	} else {
	  parent->setColor(0); //black
	}
      }
    }
  }
}

bool hasRedChild(Node* &x) {
  if (x->getLeft() != NULL && x->getLeft()->getColor() == 1) {
    return true;
  } else if (x->getRight() != NULL && x->getRight()->getColor() == 1) {
    return true;
  } else {
    return false;
  }
}
 
