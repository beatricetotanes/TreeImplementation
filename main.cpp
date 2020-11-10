//
//  main.cpp
//  TOTANES_VELASCO_05
//

#include <iostream>

using namespace std;

typedef struct node {
    int data;
    int count;
    struct node *left;
    struct node *right;
}node ;

typedef struct tree {
    struct node *top;
}tree;

struct node* NEWNODE (int data);
void INSERT(int data, node **root);
node *SEARCH(node **root, int data);
node *DELETE(node **root, int data);
node *MINIMUM(node *root);
node *MAXIMUM(node *root);
void DISPLAY(node *root);
void PREORDER(node *root);
void INORDER(node *root);
void POSTORDER(node *root);
node *inOrderSuccessor(node *root);
node *inOrderPre(node *root);
void CASE1(node **root);
void CASE2(node **root);
void CASE3(node **root);
void CASE4(node *root);
void CASE5(node *root);

int main() {
    node *root = NULL;
    int c = 0;
    int choice;
    
    while (c == 0) {
        //Menu
        cout << "\n\nBinary Search Tree\n";
        cout << "[1] Insert Item\n";
        cout << "[2] Delete Item\n";
        cout << "[3] Search Item\n";
        cout << "[4] Find Maximum\n";
        cout << "[5] Find Minimum\n";
        cout << "[6] Find Successor\n";
        cout << "[7] Find Predecessor\n";
        cout << "[8] Display Tree\n";
        cout << "[0] Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 0:
                c = 1;
                break;
            case 1:
                CASE1(&root);
                c = 0;
                break;
            case 2:
                CASE2(&root);
                c = 0;
                break;
            case 3:
                CASE3(&root);
                c = 0;
                break;
            case 4:
                CASE4(root);
                c = 0;
                break;
            case 5:
                CASE5(root);
                c = 0;
                break;
            case 6:
                inOrderSuccessor(root);
                c = 0;
                break;
            case 7:
                inOrderPre(root);
                c = 0;
                break;
            case 8:
                DISPLAY(root);
                c = 0;
                break;
            default:
                c = 0;
                cout << "Invalid input.\n"; //Prints message if user inputs a value other than 0 to 4
        }
        
    }
    
    return 0;
}

//HELPER
struct node* NEWNODE (int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node)); //allocating memory for the new node
    
    newnode->data = data;
    newnode->count = 1;
    newnode->left = NULL;
    newnode->right = NULL;
    
    return newnode; //returns new node
}

//CASES---------------------------------

void CASE1(node **root){
    int num;
    cout << "Enter number: ";
    cin >> num;
    INSERT(num, &(*root));
}

void CASE2(node **root){
    int num;
    node *temp;
    cout << "Enter number: ";
    cin >> num;
    temp = SEARCH(&(*root), num);
    if (temp != NULL) {
        if (temp->count > 1) {
            cout << "Count of [" << num << ": " << temp->count - 1 << "]\n";
        }else cout << "The number [" << temp->data << "] is deleted.\n";
        DELETE(&(*root), num);
    }else cout << "The item does not exist in the tree.\n";
}

void CASE3(node **root){
    int num;
    node *temp;
    cout << "Enter number: ";
    cin >> num;
    temp = SEARCH(&(*root), num);
    if (temp != NULL) {
        cout << "\nThe no. [" << num << "] has the count of [" << temp->count << "].\n";
    }else cout << "The number that you're looking for does not exist.";
}

void CASE4(node *root){
    node *temp;
    temp = MAXIMUM(root);
    if (temp != NULL) {
        cout << "Maximum number in the tree: " << temp->data << "\n";
    }
}

void CASE5(node *root){
    node *temp;
    temp = MINIMUM(root);
    if (temp != NULL) {
        cout << "Minimum number in the tree: " << temp->data << "\n";
    }
}

//MAIN FUNCTIONS TO USE-----------------------
void INSERT(int data, node **root) {
    node *tempNode = NEWNODE(data);
    node *current;
    node *parent;
    node *duplicate;
    
    //if tree is empty
    if(*root == NULL) {
        *root = tempNode;
        //cout << "Current Item: " << data << endl;
    } else {
        duplicate = SEARCH(root, data);
        if (duplicate != NULL) {
            duplicate->count++;
            cout << "Count: " << duplicate->count << endl;
            return;
        }
        
        current = *root;
        parent = NULL;
        
        while(1) {
            parent = current;
            //cout << "Current Item: " << current->data << endl;
            //go to left of the tree
            if(data < parent->data) {
                current = current->left;
                //insert to the left
                
                if(current == NULL) {
                    parent->left = tempNode;
                    return;
                }
            }  //go to right of the tree
            else {
                current = current->right;
                
                //insert to the right
                if(current == NULL) {
                    parent->right = tempNode;
                    return;
                }
            }
        }
    }
}

node *SEARCH(node **root, int data){
    if ((*root) == NULL) return NULL;
    else if ((*root)->data == data) return *root;
    else if(data < (*root)->data) return SEARCH(&(*root)->left, data);
    else return SEARCH(&(*root)->right, data);
}

/*
node* SEARCH(int data, node **root){
    node *current = *root;
    
    while(current->data != data){
        if(current != NULL) {
            
            //go to left tree
            if(current->data > data){
                current = current->left;
            }  //else go to right tree
            else {
                current = current->right;
            }
            
            //not found
            if(current == NULL){
                return current;
            }
        }
    }
    return current;
}*/


node *DELETE(node **root, int data){
    
    if (*root == NULL) return *root;
    else if(data < (*root)->data) (*root)->left = DELETE(&(*root)->left, data);
    else if(data > (*root)->data) (*root)->right = DELETE(&(*root)->right, data);
    else{
        //If there count > 1
        if ((*root)->count > 1) {
            (*root)->count--;
            cout << "Count in delete: " << (*root)->count << "\n"; //Remove after checking
            return *root;
        }
        
        //Case 1: No child
        if ((*root)->left == NULL && (*root)->right == NULL) {
            delete *root;
            *root = NULL;
        }
        
        //Case 2: One Child
        else if((*root)->left == NULL){
            node *temp = *root;
            *root = (*root)->right;
            delete temp;
        }
        else if((*root)->right == NULL){
            node *temp = *root;
            *root = (*root)->left;
            delete temp;
        }
        
        //Case 3: 2 Children
        else{
            node *temp = MINIMUM((*root)->right);
            (*root)->data = temp->data;
            (*root)->right = DELETE(&(*root)->right, temp->data);
        }
    }
    
    return *root;
}

node *MINIMUM(node *root){
    node *current = root;
    if((root) == NULL){
        cout << "Error: Tree is empty.\n";
    }else{
        while (current->left != NULL) {
            current = current->left;
        }
    }
    return current;
}

node *MAXIMUM(node *root){
    node *current = root;
    if((root) == NULL){
        cout << "Error: Tree is empty.\n";
    }else{
        while (current->right != NULL) {
            current = current->right;
        }
    }
    return current;
}

void DISPLAY(node *root){
    cout << "\nBinary Search Tree\n";
    if (root == NULL) {
        cout << "The tree is empty.\n";
    }
    cout << "[1] Preorder: ";
    PREORDER(root);
    cout << "\n[2] Inorder: ";
    INORDER(root);
    cout << "\n[3] Postorder: ";
    POSTORDER(root);
    cout << endl;
}

void PREORDER(node *root){
    if (root == NULL) return;
    cout << root->data << " ";
    PREORDER(root->left);
    PREORDER(root->right);
}

void INORDER(node *root){
    if (root == NULL) return;
    INORDER(root->left);
    cout << root->data << " ";
    INORDER(root->right);
}

void POSTORDER(node *root){
    if (root == NULL) return;
    POSTORDER(root->left);
    POSTORDER(root->right);
    cout << root->data << " ";
}

node *inOrderSuccessor(node *root){
    node *tmpRoot = root;
    node *tmpSearch;
    node *min;
    node *succ = NULL;
    int data;
    cout << "Enter number: ";
    cin >> data;
    tmpSearch = SEARCH(&root, data);
    
    // step 1 of the above algorithm
    if (tmpSearch->right != NULL) {
        min = MINIMUM(tmpSearch->right);
        cout << "The successor of [" << data << "] is [" << min->data << "].\n";
        return min;
    }
    
    // step 2 of the above algorithm

    
    // Start from root and search for
    // successor down the tree
    while (tmpRoot != NULL)
    {
        if (tmpSearch->data < tmpRoot->data)
        {
            succ = tmpRoot;
            tmpRoot = tmpRoot->left;
        }
        else if (tmpSearch->data > tmpRoot->data)
            tmpRoot = tmpRoot->right;
        else break;
    }

    if (succ == NULL) {
        cout << "There is no successor.\n";
    }else{
        cout << "The successor of [" << data << "] is [" << succ->data << "].\n";
    }
    return succ;
}

node *inOrderPre(node *root){
    node *tmpRoot = root;
    node *tmpSearch;
    node *min;
    node *pre = NULL;
    int data;
    cout << "Enter number: ";
    cin >> data;
    tmpSearch = SEARCH(&root, data);
    
    // step 1 of the above algorithm
    if (tmpSearch->left != NULL) {
        min = MAXIMUM(tmpSearch->left);
        cout << "The successor of [" << data << "] is [" << min->data << "].\n";
        return min;
    }
    
    // step 2 of the above algorithm
    
    // Start from root and search for
    // successor down the tree
    while (tmpRoot != NULL)
    {
        if (tmpSearch->data < tmpRoot->data)
        {
            tmpRoot = tmpRoot->left;
        }
        else if (tmpSearch->data > tmpRoot->data){
            pre = tmpRoot;
            tmpRoot = tmpRoot->right;
        }else break;
    }
    
    if (pre == NULL) {
        cout << "There is no predecessor.\n";
    }else{
        cout << "The predecessor of [" << data << "] is [" << pre->data << "].\n";
    }
    return pre;
}


