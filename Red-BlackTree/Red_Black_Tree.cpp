#include <iostream>
#include "hw3.h"
using namespace std;


struct Node
{
  int data;
  int size;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};
typedef Node *NodePtr;
class Tuple{
private:
	int data;
	int size;
public:
	int getData(){
		return data;
	}
	int getSize(){
		return size;
	}
	void insert(int data,int size){
		this->data = data;
		this->size = size;
	}

};
class RedBlackTree
{
private:
  NodePtr root;
  NodePtr TNULL;
  int red_count;
  int black_count;
  int node_count;
  int minSize;
  int remain = 0;
  Tuple array_size[20];
  int array_index;

  void initializeNULLNode(NodePtr node, NodePtr parent)
  {
    node->data = 0;
    node->size = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }
  void preOrderHelper(NodePtr node)
  {
    if (node != TNULL)
    {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }
  void findMin(NodePtr node)
  {
    if (node != TNULL)
    {
      findMin(node->left);
     if(node->size < minSize)
     	minSize = node->size;
      findMin(node->right);
    }
  }
  void colorCount(NodePtr node){
  	if(node != TNULL){
  		colorCount(node->left);
  		if(node->color == 0)
  			black_count++;
  		else
  			red_count++;
  		colorCount(node->right);
  	}
  }
  void postOrderHelper(NodePtr node)
  {
    if (node != TNULL)
    {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }
  NodePtr searchTreeHelper(NodePtr node, int key)
  {
    if (node == TNULL || key == node->data)
    {
      return node;
    }
    if (key < node->data)
    {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }
  void deleteFix(NodePtr x)
  {
    NodePtr s;
    while (x != root && x->color == 0)
    {
      if (x == x->parent->left)
      {
        s = x->parent->right;
        if (s->color == 1)
        {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }
        if (s->left->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->right->color == 0)
          {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }
          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      }
      else
      {
        s = x->parent->left;
        if (s->color == 1)
        {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }
        if (s->right->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->left->color == 0)
          {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }
          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }
  void rbTransplant(NodePtr u, NodePtr v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }
  void deleteNodeHelper(NodePtr node, int key,int size)
  {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL)
    {
      if (node->data == key & node->size == size)
      {
        z = node;
      }
      if (node->data <= key)
      {
        node = node->right;
      }
      else
      {
        node = node->left;
      }
    }
    if (z == TNULL)
    {
      cout << "Key not found in the tree" << endl;
      return;
    }
    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL)
    {
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if (z->right == TNULL)
    {
      x = z->left;
      rbTransplant(z, z->left);
    }
    else
    {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z)
      {
        x->parent = y;
      }
      else
      {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }
      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0)
    {
      deleteFix(x);
    }
    if(root != NULL)
    	minSize = root->size;
    else
    	minSize = 0;
  }
  void insertFix(NodePtr k)
  {
    NodePtr u;
    while (k->parent->color == 1)
    {
      if (k->parent == k->parent->parent->right)
      {
        u = k->parent->parent->left;
        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->left)
          {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      }
      else
      {
        u = k->parent->parent->right;
        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->right)
          {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root)
      {
        break;
      }
    }
    root->color = 0;
  }
  void printHelper(NodePtr root, string indent, bool last)
  {
    if (root != TNULL)
    {
      cout << indent;
      if (last)
      {
        cout << "R----";
        indent += "   ";
      }
      else
      {
        cout << "L----";
        indent += "|  ";
      }
      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "," << root->size <<  "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }
  void smallest(Node *x, Tuple *tuple, int &index){
    	if(x == NULL)
    		return;
    	smallest(x->left,tuple,index);
    	if(x->size == minSize){
    		tuple[index].insert(x->data,x->size);
    		index++;
    	}	
    	smallest(x->right,tuple,index);		
    	
    }
    void fill_size_to_array(NodePtr x){
    	
    	if(x !=TNULL){
    		fill_size_to_array(x->left);
    		array_size[array_index].insert(x->data,x->size);
    		array_index = array_index + 1;
    		fill_size_to_array(x->right);
    	}
    }

public:
  RedBlackTree()
  {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
    
  }
  void preorder()
  {
    preOrderHelper(this->root);
  }
  void findMinHelper()
  {
    findMin(this->root);
  }
  void postorder()
  {
    postOrderHelper(this->root);
  }
  NodePtr searchTree(int k)
  {
    return searchTreeHelper(this->root, k);
  }
  NodePtr minimum(NodePtr node)
  {
    while (node->left != TNULL)
    {
      node = node->left;
    }
    return node;
  }
  NodePtr maximum(NodePtr node)
  {
    while (node->right != TNULL)
    {
      node = node->right;
    }
    return node;
  }
  NodePtr successor(NodePtr x)
  {
    if (x->right != TNULL)
    {
      return minimum(x->right);
    }
    NodePtr y = x->parent;
    while (y != TNULL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }
  NodePtr predecessor(NodePtr x)
  {
    if (x->left != TNULL)
    {
      return maximum(x->left);
    }
    NodePtr y = x->parent;
    while (y != TNULL && x == y->left)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }
  void leftRotate(NodePtr x)
  {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }
  void rightRotate(NodePtr x)
  {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }
  void insert(int key,int size)
  {
  	// make zero red and black count after each insert to recount 
  	black_count = 0;
  	red_count = 0;
  	minSize = size;
  	remain++;
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->size = size;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;
    NodePtr y = nullptr;
    NodePtr x = this->root;
    while (x != TNULL)
    {
      y = x;
      if (node->data < x->data)
      {
        x = x->left;
      }
      else
      {
        x = x->right;
      }
    }
    node->parent = y;
    if (y == nullptr)
    {
      root = node;
    }
    else if (node->data < y->data)
    {
      y->left = node;
    }
    else
    {
      y->right = node;
    }
    if (node->parent == nullptr)
    {
      node->color = 0;
      return;
    }
    if (node->parent->parent == nullptr)
    {
      return;
    }
    insertFix(node);
  }
  NodePtr getRoot()
  {
    return this->root;
  }
  void deleteNode(int data,int size)
  {
    deleteNodeHelper(this->root, data,size);
    red_count = 0;
    black_count = 0;
    remain--;
  }
  void printTree()
  {
    if (root)
    {
      printHelper(this->root, "", true);
    }
  }
  int getBlackColor(){
  	red_count = 0;
  	black_count = 0;
  	colorCount(this->root);
  	return black_count;
  }
  int getRedColor(){
  	red_count = 0;
  	black_count = 0;
  	colorCount(this->root);
  	return red_count;
  }

  void printSize(){
  	cout << "Size : " << minSize << endl;
  }
  int getRemain(){
  	return remain; 
  }
  bool isEmpty(){
  	if(root == TNULL)
  		return true;
  	else
  		return false;
  }
  Tuple findSmallest(Tuple *tuple,int &count){
  	count = 0;
  	smallest(this->root,tuple,count);
  	
  }
  Tuple findnthsmallest(int nominal){
  	array_index = 0;
  	Tuple temp;
  	fill_size_to_array(this->root);
  	for(int i = 0; i < array_index - 1 ; i++){
  		for(int j = 0; j < array_index-i-1; j++){
  			if(array_size[j].getSize() > array_size[j+1].getSize()){
  				temp.insert(array_size[j].getData(),array_size[j].getSize());
  				array_size[j].insert(array_size[j+1].getData(),array_size[j+1].getSize());
  				array_size[j+1].insert(temp.getData(),temp.getSize());
  			}
  		}
  	}
  	return array_size[nominal-1];
  }
  

};
int findSmallestNominal(Tuple *tuple,int size){
	int smallest = tuple[0].getData();
	for(int i = 1; i < size; i++){
		if(tuple[i].getData() < smallest)
			smallest = tuple[i].getData();
	}
	return smallest;
}

HW3_Result hw3(int eastWarehousePackageCount,
                 int eastWarehousePackageSizes [],
                 int eastWarehousePackageOrdinals [],
                 int westWarehousePackageCount,
                 int westWarehousePackageSizes [],
                 int westWarehousePackageOrdinals []){

	HW3_Result result;
	RedBlackTree eastWarehouse,westWarehouse;
	Tuple est,west;
	Tuple tuple_east[30];
	Tuple tuple_west[30];
	Tuple nth_smallest_east,nth_smallest_west;
	int count_east = 0,count_west = 0;
	int east_count,west_count;
	int smallest_west,smallest_east;
	bool nth_east,nth_west;
	for(int i = 0; i < eastWarehousePackageCount; i++)
		eastWarehouse.insert(eastWarehousePackageOrdinals[i],eastWarehousePackageSizes[i]);

	for(int i = 0; i < westWarehousePackageCount; i++)
		westWarehouse.insert(westWarehousePackageOrdinals[i],westWarehousePackageSizes[i]);

	eastWarehouse.findMinHelper();
	westWarehouse.findMinHelper();

	eastWarehouse.findSmallest(tuple_east,count_east);
	nth_east = false;
	//cout << count_east << endl;

	for(int i = 0; i < count_east; i++)
		eastWarehouse.deleteNode(tuple_east[i].getData(),tuple_east[i].getSize());

	while(!(westWarehouse.isEmpty() & eastWarehouse.isEmpty())){
		
		if(nth_east == false){
			smallest_west = findSmallestNominal(tuple_east,count_east);
			//cout << smallest_west;
			if(smallest_west < westWarehouse.getRemain()){
				nth_west = true;
				westWarehouse.findMinHelper();
				for(int i = 0; i < count_east; i++)
					westWarehouse.insert(tuple_east[i].getData(),tuple_east[i].getSize());
				if(eastWarehouse.getRemain() == 0)
					break;
				nth_smallest_west = westWarehouse.findnthsmallest(smallest_west);
				cout << endl;
				//cout << "Find smallest " << endl;
				//cout << nth_smallest_west.getData() << " " << nth_smallest_west.getSize() <<endl;;
				nth_west = true;
				westWarehouse.deleteNode(nth_smallest_west.getData(),nth_smallest_west.getSize());
			}
			else{
				if(eastWarehouse.getRemain() == 0)
					break;
				westWarehouse.findSmallest(tuple_west,count_west);
				nth_west = false;
				for(int i = 0; i < count_west; i++)
					westWarehouse.deleteNode(tuple_west[i].getData(),tuple_west[i].getSize());
			}	
		}
		else{
			smallest_west = nth_smallest_east.getData();
			if(smallest_west < westWarehouse.getRemain()){
				westWarehouse.findMinHelper();
				westWarehouse.insert(nth_smallest_east.getData(),nth_smallest_east.getSize());
				if(eastWarehouse.getRemain() == 0)
					break;
				nth_smallest_west = westWarehouse.findnthsmallest(smallest_west);
				nth_west = true;
			}
			else{
				if(eastWarehouse.getRemain() == 0)
					break;
				westWarehouse.findSmallest(tuple_west,count_west);
				nth_west = false;
				for(int i = 0; i < count_west; i++)
					westWarehouse.deleteNode(tuple_west[i].getData(),tuple_west[i].getSize());
			}
		}

		if(nth_west = false){
			smallest_east = findSmallestNominal(tuple_west,count_west);
			//cout << smallest_east;
			if(smallest_east < eastWarehouse.getRemain()){
				nth_east = true;
				eastWarehouse.findMinHelper();
				for(int i = 0; i < count_west; i++)
					eastWarehouse.insert(tuple_west[i].getData(),tuple_west[i].getSize());
				if(westWarehouse.getRemain() == 0)
					break;
				nth_smallest_east = eastWarehouse.findnthsmallest(smallest_east);
				nth_east = true;
				eastWarehouse.deleteNode(nth_smallest_east.getData(),nth_smallest_east.getSize());
			}
			else{
				if(westWarehouse.getRemain() == 0)
					break;
				eastWarehouse.findMinHelper();
				eastWarehouse.findSmallest(tuple_west,count_west);
				nth_east = false;
				for(int i = 0; i < count_east; i++)
					eastWarehouse.deleteNode(tuple_east[i].getData(),tuple_east[i].getSize());
			}	
		}
		else{
			smallest_east = nth_smallest_west.getData();
			if(smallest_east < eastWarehouse.getRemain()){
				eastWarehouse.findMinHelper();
				eastWarehouse.insert(nth_smallest_west.getData(),nth_smallest_west.getSize());
				if(westWarehouse.getRemain() == 0)
					break;
				nth_smallest_east = eastWarehouse.findnthsmallest(smallest_east);
				nth_east = true;
			}
			else{
				if(westWarehouse.getRemain() == 0)
					break;
				westWarehouse.findMinHelper();
				eastWarehouse.findSmallest(tuple_east,count_east);
				nth_west = false;
				for(int i = 0; i < count_east; i++)
					eastWarehouse.deleteNode(tuple_east[i].getData(),tuple_east[i].getSize());
			}
		}
	}

	if((eastWarehouse.isEmpty())){
		result.packageCount = westWarehouse.getRemain();
		result.redNodeCount = westWarehouse.getRedColor();
		result.blackNodeCount = westWarehouse.getBlackColor();
		cout << "West" << endl;
		westWarehouse.printTree();
	}
	else{
		result.packageCount = eastWarehouse.getRemain();
		result.redNodeCount = eastWarehouse.getRedColor();
		result.blackNodeCount = eastWarehouse.getBlackColor();
		cout << "East" << endl;
		eastWarehouse.printTree();
	}
	return result;
}


int main()
{
	HW3_Result result;
	int eastWarehousePackageCount = 3;
    int eastWarehousePackageSizes[] = {2,2,3};
    int eastWarehousePackageOrdinals[] = {3,4,5};
    int westWarehousePackageCount = 5;
    int westWarehousePackageSizes[] = {1,1,1,5,6};
  	int westWarehousePackageOrdinals[] = {4,5,7,1,2};
  	result = hw3(eastWarehousePackageCount,eastWarehousePackageSizes,eastWarehousePackageOrdinals,westWarehousePackageCount,westWarehousePackageSizes,westWarehousePackageOrdinals);

	cout << endl;
	cout << "Remain: " << result.packageCount << "  RedCount: " << result.redNodeCount << "  BlackCount: " << result.blackNodeCount;  

}