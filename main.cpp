//Neel Madala
//3/22/2024
//This code takes in list of integers from either the file or console and adds them to a binary search tree and the user is able to search for and delete user specified integers from the tree as well as print out the tree.

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include "node.h"

void ADD(Node*& root, Node* newNode, Node* tree);
void print(Node* tree, int count);
bool search(Node* tree, int s);
Node* deleteInt(Node* &root, int value);
int main(){
  cout << "Welcome to BST" << endl << endl;
  bool looping = true;
  bool adding = true;
  char command[10];
  char input[3200];
  int value = -1;
  Node* tree = nullptr;
  while(looping == true) {
    cout <<"ADD, REMOVE, SEARCH, PRINT, or QUIT?" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(command, "ADD") == 0) {//Add to BST
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
	    Node* temp = new Node();
	    temp->setData(value);
	    ADD(tree, temp, tree);
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
	  Node* temp = new Node();
	  temp->setData(value);
	  ADD(tree, temp, tree);
	  numdone++;
	}
      }
      else {
	cout << "Invalid input" << endl;
      }
    }
    else if(strcmp(command, "SEARCH") == 0) {//Search through BST for a integer
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
    else if(strcmp(command, "PRINT") == 0) {//PRINT out tree
      print(tree, 0);
    }
    else if(strcmp(command, "REMOVE") == 0) {//Delete from tree
      cout << "Enter the numbe you are deleteing" << endl;
      int deleteInteger;
      cin >> deleteInteger;
      cin.clear();
      cin.ignore(10000, '\n');
      tree = deleteInt(tree, deleteInteger);
      cout << "Done deleteing" << endl;
    }
    else if(strcmp(command, "QUIT") == 0) {//quits
      looping = false;
      cout << "Thanks for utilizing this code" << endl;
    }
  }
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
scp        else {
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
scp        else {
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
scp        else {
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


void print(Node* tree, int count) {//print out tree
  if(tree->getRight() != nullptr) {//get to the right child
    print(tree->getRight(), count+1);
  }
  for(int i = 0; i < count; i++) {//tabs over
    cout << '\t';
  }
  cout << tree->getData() << endl;//print out value
  //left side
  if(tree->getLeft() != nullptr) {//get to the left child
    print(tree->getLeft(), count+1);
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

Node* deleteInt(Node* &root, int value) { //Courtesy of Nathan Zou: Delete function, deletes a node from the tree
  Node* left = root->getLeft();
  Node* right = root->getRight();
  if (root == nullptr) {
    return root;
  }
  else if (value < root->getData()) {
    root->setLeft(deleteInt(left, value));
  }
  else if (value > root->getData()) {
    root->setRight(deleteInt(right, value));
  }
  else { //If the root node is to be delete
    if (root->getRight() == nullptr && root->getLeft() == nullptr) { //If there is no child nodes
      root->~Node();
      root = nullptr;
      return root;
    }
    //If there is one child node that exists
    else if (root->getLeft() == nullptr) { //The right child node exists
      Node* temp = root;
      root = root->getRight();
      temp->~Node();
      return root;
    }
    else if (root->getRight() == nullptr) { //The left child node exists
      Node* temp = root;
      root = root->getLeft();
      temp->~Node();
      return root;
    }
    else { //If there are two child nodes that exists
      //Find the minimum on the right
      Node* temp = root->getRight();
      while (temp->getLeft() != nullptr) {
	temp = temp->getLeft();
      }
      //Delete/replacement
      root->setData(temp->getData());
      Node* r = root->getRight();
      root->setRight(deleteInt(r, temp->getData()));
    }
  }
  return root;
}
