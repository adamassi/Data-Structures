//
// Created by admin on 25/11/2022.
//

#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdlib.h>



#include "Node.h"




using namespace std;

template<class T, class Comp, class Equal>
class AVLtree {
public:
    
    Node<T> *max_node; /// it was named max, i changed it to max_node
    int num_nodes;
    Node<T>* root;
    Comp compare;
    Equal equal;

    AVLtree() : max_node(nullptr), num_nodes(0), root(nullptr) {};

    AVLtree(Node<T>* max_node, int num_nodes, Node<T>* root) : max_node(max_node), num_nodes(num_nodes), root(root) {};

    ~AVLtree() {
        clear(root);
    }

    AVLtree(T arr[], int size) {
        root = sortedArrayToAVL(arr, 0, size - 1);
        max_node = maximumNode(root);
        num_nodes = size;
    }
    
    Node<T>* getRoot() const
    {
        if (this==nullptr)
        {
            return nullptr;
        }
        return root;
    }

    void connectSubTreeToTree(Node<T>* originalRoot, Node<T>* newRoot) {
        if (originalRoot->parent == NULL) {
            root = newRoot;
        }
        //nf7s: else if ola bs if
        if (originalRoot->isLeftSon()) {
            originalRoot->parent->left_son = newRoot;
        }

        if (originalRoot->isRightSon()) {
            originalRoot->parent->right_son = newRoot;
        }

        newRoot->parent = originalRoot->parent;
        originalRoot->parent = newRoot;
    }

    void rollLeftLeft(Node<T>* currRoot) {
        Node<T>* originalRoot = currRoot;
        Node<T>* originalRootLeftTree = currRoot->left_son;
        Node<T>* originalRootLeftTreeRightSon = originalRootLeftTree->right_son;

        connectSubTreeToTree(originalRoot, originalRootLeftTree);
        currRoot = originalRootLeftTree;
        currRoot->right_son = originalRoot;
        currRoot->right_son->left_son = originalRootLeftTreeRightSon;
        if (currRoot->right_son->left_son != NULL) {
            currRoot->right_son->left_son->parent = currRoot->right_son;
        }

        currRoot->right_son->updateHeight();
        currRoot->right_son->calcBF();

        currRoot->updateHeight();
        currRoot->calcBF();

    }

    void rollLeftRight(Node<T>* currRoot) {
        Node<T>* originalRoot = currRoot;
        Node<T>* originalRootLeftTree = currRoot->left_son;
        Node<T>* originalRootLeftTreeRightSon = originalRootLeftTree->right_son;
        Node<T>* originalRootLeftTreeRightSonLeftSon = originalRootLeftTreeRightSon->left_son;
        Node<T>* originalRootLeftTreeRightSonRightSon = originalRootLeftTreeRightSon->right_son;

        connectSubTreeToTree(originalRoot, originalRootLeftTreeRightSon);
        currRoot = originalRootLeftTreeRightSon;
        currRoot->right_son = originalRoot;
        currRoot->right_son->left_son = originalRootLeftTreeRightSonRightSon;
        if (currRoot->right_son->left_son != NULL) {
            currRoot->right_son->left_son->parent = currRoot->right_son;
        }
        currRoot->left_son = originalRootLeftTree;
        if (currRoot->left_son != NULL) {
            currRoot->left_son->parent = currRoot;
        }
        currRoot->left_son->right_son = originalRootLeftTreeRightSonLeftSon;
        if (currRoot->left_son->right_son != NULL) {
            currRoot->left_son->right_son->parent = currRoot->left_son;
        }

        currRoot->right_son->updateHeight();
        currRoot->right_son->calcBF();

        currRoot->left_son->updateHeight();
        currRoot->left_son->calcBF();
        currRoot->updateHeight();
        currRoot->calcBF();
    }

    void rollRightRight(Node<T>* currRoot) {
        Node<T>* originalRoot = currRoot;
        Node<T>* originalRootRightTree = currRoot->right_son;
        Node<T>* originalRootRightTreeLeftSon = originalRootRightTree->left_son;

        connectSubTreeToTree(originalRoot, originalRootRightTree);
        currRoot = originalRootRightTree;
        currRoot->left_son = originalRoot;
        currRoot->left_son->right_son = originalRootRightTreeLeftSon;
        if (currRoot->left_son->right_son != NULL) {
            currRoot->left_son->right_son->parent = currRoot->left_son;
        }

        currRoot->left_son->updateHeight();
        currRoot->left_son->calcBF();
        currRoot->updateHeight();
        currRoot->calcBF();
    }

    void rollRightLeft(Node<T>* currRoot) {
        Node<T>* originalRoot = currRoot;
        Node<T>* originalRootRightTree = currRoot->right_son;
        Node<T>* originalRootRightTreeLeftSon = originalRootRightTree->left_son;
        Node<T>* originalRootRightTreeLeftSonRightSon = originalRootRightTreeLeftSon->right_son;
        Node<T>* originalRootRightTreeLeftSonLeftSon = originalRootRightTreeLeftSon->left_son;

        connectSubTreeToTree(originalRoot, originalRootRightTreeLeftSon);
        currRoot = originalRootRightTreeLeftSon;
        currRoot->left_son = originalRoot;
        currRoot->left_son->right_son = originalRootRightTreeLeftSonLeftSon;
        if (currRoot->left_son->right_son != NULL) {
            currRoot->left_son->right_son->parent = currRoot->left_son;
        }
        currRoot->right_son = originalRootRightTree;
        if (currRoot->right_son) {
            currRoot->right_son->parent = currRoot;
        }
        currRoot->right_son->left_son = originalRootRightTreeLeftSonRightSon;
        if (currRoot->right_son->left_son != NULL) {
            currRoot->right_son->left_son->parent = currRoot->right_son;
        }

        currRoot->right_son->updateHeight();
        currRoot->right_son->calcBF();
        currRoot->left_son->updateHeight();
        currRoot->left_son->calcBF();
        currRoot->updateHeight();
        currRoot->calcBF();
    }

    void roll(Node<T>* node) {
        if(node==nullptr){
            return;
        }
        if (node->bf == 2) {
            if ((node->left_son)->bf >= 0)
                rollLeftLeft(node);
            else if (node->left_son->bf == -1)
                rollLeftRight(node);
        } else if (node->bf == -2) {
            if (node->right_son->bf <= 0)
                rollRightRight(node);
            else if (node->right_son->bf == 1)
                rollRightLeft(node);
        }
    }

    void clear(Node<T>* &root) {
        if (root == nullptr){
            return;
        }
        if (root != nullptr)
        {
        clear(root->left_son);
        clear(root->right_son);
        delete root;
        }
        
        max_node = nullptr;
        root = nullptr;
        num_nodes = 0;
    }

    void clear_pointer(Node<T>* &root) {
        if (root == NULL) {
            return;
        }
        if (root->left_son) {
            clear_pointer(root->left_son);
        }
        if (root->right_son) {
            clear_pointer(root->right_son);
        }
        delete root;
        max_node = NULL;
        root = NULL;
        num_nodes = 0;
    }

    T *findData(const T &data) {
        if (findNode(data) == nullptr) {
            return nullptr;
        }
        return findNode(data)->value;
    }

    Node<T>* findNode(const T& data) {
        return findNodeHelper(this->root, data);
    }

    Node<T>* findNodeHelper(Node<T>* node, const T &data){
        if (node == nullptr || node->value == nullptr)
            return nullptr;
        if (equal(*(node->value), data)) {
            return node;
        } 
        else{
            if(compare(*(node->value), data)) {
                return findNodeHelper(node->right_son, data);
            }
            else{
                return findNodeHelper(node->left_son, data);
            } 
        }
        return nullptr; // won't reach here 
    }

    void insert(T data) {
        if (&data == nullptr) {
            return;
        }

        if (findNode(data) != nullptr) {
            throw Failure(); // node already exist 
            return;
        }
        Node<T>* node=nullptr ;
        node = node->createNode(data);
        insertHelper(node, root);
        node->updateHeight();
        node->calcBF();
        max_node = maximumNode(root);
        num_nodes++;
    }

    void insertHelper(Node<T>* nodeToAdd, Node<T>* currRoot) {
        //the tree is empty
        if (currRoot == nullptr) {
            nodeToAdd->parent=nullptr;
            root = nodeToAdd;
            root->height=0;
            return;
        }

        //add the node to the left sub-tree if data is smaller
        //returns true if the first is smaller
        if (compare(*(nodeToAdd->value), *(currRoot->value))) {
            if (currRoot->left_son != nullptr) {
              //  std::cout << " INSERT HELPER : left son of 3 is : " << currRoot->left_son->value.; << std::endl;
                insertHelper(nodeToAdd, currRoot->left_son);
            } else {
                currRoot->left_son=nodeToAdd;
                nodeToAdd->parent=currRoot;
            }
        }

            //add the node to the right sub-tree if data is bigger
        else {
            if (currRoot->right_son != nullptr) {
                insertHelper(nodeToAdd, currRoot->right_son);
            } else {
                currRoot->right_son=nodeToAdd;
                nodeToAdd->parent=currRoot;
            }
        }
        currRoot->updateHeight();
        currRoot->calcBF();
        if (!currRoot->isValidBF()) {
            roll(currRoot);
        }
    }

    void remove(const T &data) {
        if (&data == nullptr )
            return;

        // if (num_nodes == 0)
        //     return;
        Node<T>* node = findNode(data);
        if (node == nullptr) {
            throw Failure(); // node mosh  exist
            return;
        }
        removeHelper(node, root);
        num_nodes--;
        if (num_nodes != 0) {
            max_node = maximumNode(root);
        } else {
            max_node = nullptr;
        }
    }

    void removeHelper(Node<T> *node_to_delete, Node<T> *currNode) {
        if(node_to_delete == nullptr || currNode==nullptr)
            return;
        if (equal(*(node_to_delete->value), *(currNode->value) )) {
            if ((currNode->left_son == nullptr) && (currNode->right_son == nullptr)) {
                Node<T>* to_remove = currNode;
                currNode = currNode->parent;
                if (to_remove->isLeftSon()) {
                    currNode->left_son=nullptr;
                }
                if (to_remove->isRightSon()) {
                    currNode->right_son=nullptr;
                }
                delete to_remove;
                if (num_nodes == 1) {
                    this->root = nullptr;
                }
            }

                // the root has only left son
            else if (currNode->left_son && currNode->right_son == nullptr) {
                Node<T>* left = currNode->left_son;
                delete currNode->value;
                currNode->value = new T(*(left->value));
                
                currNode->left_son=left->left_son;
                currNode->left_son=left->right_son;
                delete left;
            }

                // the root has only right son
            else if (currNode->left_son == nullptr && currNode->right_son) {
                Node<T>* right = currNode->right_son;
                delete currNode->value;
                currNode->value=new T(*(right->value));
                currNode->left_son=right->left_son;
                currNode->right_son=right->right_son;
                delete right;
            } else {
                // left and right exists
                Node<T>* min_node = getMinNode(currNode->right_son);
                delete currNode->value;
                currNode->value=new T(*(min_node->value));
                removeHelper(min_node, currNode->right_son);

            }
        } else if (compare(*(node_to_delete->value), *(currNode->value))) {

            removeHelper(node_to_delete, currNode->left_son);
        } else {
            removeHelper(node_to_delete, currNode->right_son);
        }
        /*if (num_nodes - 1 != 0) {
            currNode->updateHeight();
            if (!currNode->isValidBF()) {
                roll(currNode);
            }
        }*/
        currNode->updateHeight();
        currNode->calcBF();
        if (!currNode->isValidBF()) {
            roll(currNode);
        }
    }

    Node<T> *maximumNode(Node<T>* node) {
        if (node == NULL) {
            return NULL;
        }
        if (node->right_son == NULL) {
            return node;
        }
        return maximumNode(node->right_son);
    }

    Node<T>* getMinNode(Node<T>* node) const{
        if (node == NULL) {
            return NULL;
        }
        if (node->left_son == NULL) {
            return node;
        }
        return getMinNode(node->left_son);
    }

    void preorder(Node<T>* root) {
        if (root != nullptr) {
            cout << *(root->getValue()) << " ";
            preorder(root->left_son);
            preorder(root->right_son);
        }
    }


    void postorder(Node<T>* root) {
        if (root != nullptr) {
            postorder(root->left_son);
            postorder(root->right_son);
            std::cout << *(root->getValue()) << " ";
        }
    }

    T* maxData() {
        if (max_node == nullptr) {
            return nullptr;
        }

        return (max_node->value);
    }

    Node<T>* getSmallestDescendant(Node<T>* node) {
    if (node!=nullptr &&  node->left_son == nullptr) {
        return node;
    }
        return getSmallestDescendant(node->left_son);
}

T getNextInInorder(Node<T>* node) {
    if(!node){
        return nullptr;
    }
    
    if(node->right_son){
        if (!(getSmallestDescendant(node->right_son)->value))
        {
            return nullptr;
        }
        return  *(getSmallestDescendant(node->right_son)->value);
    }
    if(node->isLeftSon()){
        if(node->parent){
            return *(node->parent->value);
        }
    }
    if(node->isRightSon()){
        for( ; node->parent!=nullptr; node=node->parent){
            if(node->parent->isLeftSon()){
                return *(node->parent->parent->value);
            }
        }       
    }
    return nullptr;
}

T getPreviousInInorder(Node<T>* node) {
    if(!node){
        return nullptr;
    }
    if(node->left_son){
        if(!(maximumNode(node->left_son)->value)) return nullptr;
        return *(maximumNode(node->left_son)->value);
    }
    if(node->isRightSon()){
        if(node->parent){
            return *(node->parent->value);
        }
    }
    if(node->isLeftSon()){
        for( ; node->parent!=nullptr; node=node->parent){
            if(node->parent->isRightSon()){
                return *(node->parent->parent->value);
            }
        }       
    }
    return nullptr;
}




    /*
    void storeInOrderToArray(T in_order[]) {
        int i = 0;
        storeInOrderNodes(root, in_order, &i);
    }
    */

    /*void storeInOrderNodes(Node<T>* node, T in_order[], int *index) {
        if (node == nullptr)
            return;
        storeInOrderNodes(node->left_son, in_order, index);
        in_order[*index] = *(node->getValue());
        (*index)++;
        storeInOrderNodes(node->right_son, in_order, index);
    }

    void storeInOrderToArray2(T in_order[], int size) {
        int i = 0;
        storeInOrderNodes2(root, in_order, &i, size);
    }

    void storeInOrderNodes2(Node<T>* node, T in_order[], int *index, int size) {
        if (node == nullptr)
            return;
        storeInOrderNodes2(node->left_son, in_order, index, size);
        if (*index < size) {
            in_order[*index] = *(node->getValue());
            (*index)++;
        }
        storeInOrderNodes2(node->right_son, in_order, index, size);
    }
    */

   /* Node<T>* sortedArrayToAVL(T arr[], int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node<T>* node = nullptr;
        node = node->createNode(arr[mid]);

        node->left_son = sortedArrayToAVL(arr, start, mid - 1);
        node->right_son = sortedArrayToAVL(arr, mid + 1, end);
        if (node->left_son != nullptr)
            node->left_son->parent = node;
        if (node->right_son != nullptr)
            node->right_son->parent = node;
        node->updateHeight();
        node->calcBF();
        return node;
    }*/


    void avlToSortedArrayBackwards(T in_order[], int size) {
        int i = size;
        avlToSortedArrayBackwardsHelper(root, in_order, &i);
    }

    void avlToSortedArrayBackwardsHelper(Node<T>* currRoot, T arr[], int *index) {
        if (currRoot != nullptr) {
            avlToSortedArrayBackwardsHelper(currRoot->left_son, arr, index);
            arr[*index] = (currRoot->getValue());
            (*index)--;
            avlToSortedArrayBackwardsHelper(currRoot->right_son, arr, index);
        }
    }

    int getNodesNumInRange(Node<T>* root, const T &low, const T &high) {
        // Base case
        if (!root) return 0;

        if (equal(*root->value, high) && Equal(*root->value, low))
            return 1;

        if (!compare(high, *(root->value)) && !compare(*(root->value), low))
            return 1 + getNodesNumInRange(root->left_son, low, high) +
                   getNodesNumInRange(root->right_son, low, high);


        else if (Comp(*(root->getValue()), low))
            return getNodesNumInRange(root->right_son, low, high);

        else return getNodesNumInRange(root->left_son, low, high);
    }


    /*void getNodesInRangeToArr(Node<T>* root, const T &low, const T &high, T arr[], int *index) {
        if (!root) return;

        if (Equal(*root->value, high) && Equal(*root->value, low)) {
            arr[*index] = *(root->getValue());
        }
        if (!Comp(high, *(root->value)) && !Comp(*(root->value), low)) {
            
            getNodesInRangeToArr(root->left_son, low, high, arr, index);
            arr[*index] = *(root->getValue());
            (*index)=(*index)-1;
            getNodesInRangeToArr(root->right_son, low, high, arr, index);
        } else if (Comp(*(root->getValue()), low))
            getNodesInRangeToArr(root->right_son, low, high, arr, index);
        else
            getNodesInRangeToArr(root->left_son, low, high, arr, index);
    }*/

//////////////////////////////////////////////////////////////////// 
    void  PrintInOrder(int num, T* arr) const
    {
        int index = 0;
        int left_subtree_done = 0;
        Node<T>* current = this->getRoot();
        while (current && index < num)
        {
            if (!left_subtree_done)
            {
                current= getMinNode(current);
                
            }
            arr[index] = *(current->value);
            index++;
            left_subtree_done = 1;

            if (current->right_son)
            {
                left_subtree_done = 0;
                current = current->right_son;
            }

            else if (current->parent)
            {
                while (current->parent &&
                    current == current->parent->right_son)
                    current = current->parent;
                if (!((*current).parent))
                    break;
                current = current->parent;
            }
            else break;
        }
    }


/*T* mergeSortedArr(const T* arr1, const T* arr2, int n1, int n2) const{
	T* dst = new T[n1 + n2];
	int i = 0, j = 0, k = 0;
	while (i < n1 && j < n2)
	{
		if (compare(arr1[i],arr2[j]))
			dst[k++] = arr1[i++];
		else
			dst[k++] = arr2[j++];
	}
	while (i < n1)
		dst[k++] = arr1[i++];
	while (j < n2)
		dst[k++] = arr2[j++];
	return dst;
} */

/*Node<T>* sortedArrayToTreeHelper(const T array[], int first, int last, int n) const
{    
	if (first > last)
		return nullptr;
	int mid = (first + last) / 2;
    Node<T>* node=nullptr;
    node=node->createNode(array[mid]);
	//Node<T>* root(new Node<T>(array[mid]));
	node->left_son=(this->sortedArrayToTreeHelper(array, first, mid - 1, n));

    if (node->left_son != nullptr) 
        node->left_son->parent=node;
	node->updateHeight();
    node->calcBF();
    this->sortedArrayToTreeHelper(array, mid + 1, last, n);
	if (node->right_son != nullptr) 
        node->right_son->parent=node;
	node->updateHeight();
    node->calcBF();
    //1 + getMax(root->left_son->getHeight(), root->right_son->getHeight())
	return node;
}*/

/*void mergeTrees(const AVLtree<T, Comp, Equal>* tree1, const AVLtree<T, Comp, Equal>* tree2)
{
	int size1 ,size2;
    size2 = tree2->num_nodes;
    size1 = tree1->num_nodes;
	this->num_nodes = size1 + size2;
	T* arr2 = size2 > 0 ? new T[size2]() : nullptr;
    T* arr1 = size1 > 0 ? new T[size1]() : nullptr;
	tree1->PrintInOrder(size1, arr1);
	tree2->PrintInOrder(size2, arr2);
	T* arr3 = mergeSortedArr(arr1, arr2, size1, size2);
    
	root = sortedArrayToAVL(arr3, 0, num_nodes-1);
	
	delete[] arr1;
	delete[] arr2;
    delete[] arr3;
}*/



int getMax(int a, int b)
{
    return (a >= b) ? a : b;
}
};
/*
void debugging_printTree(const std::string& prefix, const Node<T>* node, bool isLeft, std::string& str)
{
    if( node != nullptr )
    {
        str += prefix;

        str += (isLeft ? "└──" : "├──" );

        // print the value of the node
        str += std::to_string((*(node->value)).getID());
        str += "\n";

        // enter the next tree level - left and right branch
        debugging_printTree( prefix + (isLeft ? "    " : "│   "), node->right, false, str);
        debugging_printTree( prefix + (isLeft ? "    " : "│   "), node->left, true, str);
    }
}

void debugging_printTree(const Node<T>* node, std::string& str)
{
    debugging_printTree("", node, true, str);
}

std::string debugging_printTree()
{
    std::string tree = "";
    debugging_printTree(this->root, tree);
    return tree;
}


*/













#endif //WET1_DS_WINTER_AVLTREE_H
