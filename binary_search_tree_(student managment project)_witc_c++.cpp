// FINDING MIN AND MAX with BST
/*
                    NAME                     ID
            1. BILILIGN YIBGETA


                                                                                submision. date : 10-2-2023

*/
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;
// to handl student information  interms of structure
fstream student;
struct Student
{
    // Student *right and Student *left we need both for traversing to thr right and left of the three in the entire code
    Student *left;
    Student *right;
    int id;
    string name;
    int age;
    char gender;
    double year;
};

// first creat the root node or just a node
Student *create(int id, string name, int age, char gender, double year)
{
    Student *temp = new Student();
    temp->id = id;
    temp->name = name;
    temp->age = age;
    temp->gender = gender;
    temp->year = year;
    temp->right = temp->left = NULL;
    return temp;
}

// register new student;
void add(Student *&root, int id, string name, int age, char gender, double year)
{
    if (root == NULL)
    {
        root = create(id, name, age, gender, year);
    }

    else if (root->id > id)
    {
        add(root->left, id, name, age, gender, year);
    }

    else
    {
        add(root->right, id, name, age, gender, year);
    }
}
void write(Student *&root)
{
    if (root != NULL)
    {
        if (student.is_open())
        {
            if (root->left != NULL)
            {
                write(root->left);
            }
            student << "ID:" << root->id << endl;
            student << "Name:" << root->name << endl;
            student << "Age:" << root->age << endl;
            student << "gender:" << root->gender << endl;
            student << "Payment:" << root->year << endl;
            student << endl;
            if (root->right != NULL)
            {
                write(root->right);
            }
        }
    }
    student.close();
}
// finding the minimum id student
int minId(Student *root)
{
    // checking if the tree is empty
    if (root == NULL)
    {
        cout << "no student registered" << endl;
        return 0;
    }
    else
    {
        int leftMin, rightMin;
        int min = root->id;
        if (root->left != NULL)
        {
            leftMin = minId(root->left);
            min = (min > leftMin) ? leftMin : min;
        }
        return min;
    }
}
// RETRIVE INTERMS OF  Post Order
void displayPostOrder(Student *root)
{

    if (root != NULL)
    {
        displayPostOrder(root->left);
        displayPostOrder(root->right);
        cout << root->id << "\t";
    }
}

// retrive interms of in order
void inorder(Student *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->id << "\t";
        inorder(root->right);
    }
}

// retrive interms of  Pre order
void Preorder(Student *root)
{
    if (root != NULL)
    {
        // root->left->right
        cout << root->id << "\t";
        Preorder(root->left);
        Preorder(root->right);
    }
}

// Display maximum id from the tree
int maxId(Student *root)
{
    // checking if the tree is empty
    int max, rightMax;
    if (root == NULL)
    {
        cout << "null list" << endl;
        return 0;
    }
    max = root->id;

    // check the largest elemt from the right side
    if (root->right != NULL)
    {
        rightMax = maxId(root->right);
        if (rightMax > max)
        {
            max = rightMax;
        }
    }

    return max;
}

// count total number of Student
int countStudent(Student *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + countStudent(root->left) + countStudent(root->right);
    }
}

// read from file to screen
void read()
{
    string listData[5];
    student.open("studentList.txt", ios::in);
    int i = 0;
    if (student.is_open())
    {
        string line;
        while (getline(student, line))
        {
            cout << line << endl;
        }
    }
}

// search noded
Student *search(Student *root, int key)
{
    if (root != NULL)
    {
        if (root->id = key)
        {
            return root;
        }

        if (root->id < key)
        {
            return search(root->right, key);
        }

        return search(root->left, key);
    }
    else
    {
        cout << "you can not search in null list" << endl;
        return NULL;
    }
}

Student *minValeNode(Student *node)
{
    Student *current = node;

    // find the most left leaf
    while (current && current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Delete Node
Student *
deleteNode(Student *root, int id)
{
    if (root == NULL)
    {
        return root;
    }

    if (id < root->id)
    {
        root->left = deleteNode(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = deleteNode(root->right, id);
    }
    else
    {
        // the node has no child
        if (root->left == NULL and root->right == NULL)
        {
            return NULL;
        }

        // node only one child
        else if (root->left == NULL)
        {
            Student *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Student *temp = root->left;
            free(root);
            return temp;
        }

        Student *temp = minValeNode(root->right);
        root->id = temp->id;
        root->right = deleteNode(root->right, temp->id);
    }
    return root;
}
void avl(Student *root)
{

    
    // Traverse the skewwd binary tree and stores its nodes pointers in vectors nodes[]
    void storeBSTNodes(Student* root,vector<Student*> &nodes){
        if(root==NULL){
            return;
        }
        storeBSTNodes(root->left,nodes);
        nodes.push_back(root);
        storeBSTNodes(root->right,nodes);
    }


    // Recurence Function to construct binary tree
    Student* buildTreeUtil(vector<Student*> &nodes, int start, int end){
        if(start>end){
            return NULL;
        }
        // Get middle elemnt and make it root
        int mid= (start+end)/2;
        Student* root= nodes[mid];

        // using index in Inorder Traversal construct left and right subtrees
        root->left = buildTreeUtil(nodes, start, mid-1);
        root->right= buildTreeUtil(nodes, mid+1,end);
        return root;
    }


    //Unbalanced BST using AVL Tree
    Student* buildTree(Student* root){
        // store nodes of given BST in sorted order
        vector<Student *> nodes;
        storeBSTNodes(root,nodes);

        // construct BST from nodes
        int n= nodes.size();
        return buildTreeUtil(nodes,0,n-1);
        
    cout << "the tree is balanced completly!!" << endl;
}

int main()
{
    Student *root = NULL;
    int id, age, noreg, n, key, year;
    int nostud = 0;
    string name;
    char gender;

    cout << "\n #############################################################";
    cout << "\n #####                                                   #####";
    cout << "\n #####           WELCOME TO BAHIRDAR UNIVERSITY          #####";
    cout << "\n #####                                                   #####";
    cout << "\n #############################################################" << endl;
    cout << "\n ~~~     THIS IS  BAHIRDAR UNIVERSITY STUDENT   MANEGMENT  LIST    ~~~" << endl;
    cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "\n"
         << endl;
    while (1)
    {
        if (n > 13 || n < 0)
        {
            cout << "INVALID INPUT ! please choice the correct one" << endl;
        }

        cout << "\n";
        cout << "\n                 ~~  WHAT DO YOU WANT TO DO ?  ~~" << endl;
        cout << "\n                  ################################" << endl;
        cout << "\n";
        cout << "1. TO REGISTER new student             ~~    7. HOW MANY STUDENTS are registered " << endl;
        cout << "2. VIEW the student list               ~~    8. list of students interms of in order " << endl;
        cout << "3. FIND student                        ~~    9. list of students interms of pre order" << endl;
        cout << "4. Delete student                      ~~    10.list of students interms of post order" << endl;
        cout << "5. TO Delete the minimum ID student    ~~    11.the minimum Id student" << endl;
        cout << "6. TO Delete the maximum ID  student   ~~    12.the maximum Id student" << endl;
        cout << "13. form AVL tree" << endl;
        cout << "0. TO exit" << endl;
        cin >> n;

        switch (n)
        {
        case 1:
            cout << "\n";
            cout << "How Many Student do you want TO register" << endl;
            cin >> noreg;

            if (noreg > 0)
            {
                cout << "FILL STUDENT INFORMATION CAREFULLY " << endl;
                do
                {
                    cout << "Enter Student id" << endl;
                    cin >> id;
                    cout << "Enter Student name" << endl;
                    cin >> name;
                    cout << "Enter Student age" << endl;
                    cin >> age;
                    cout << "Enter Student gender" << endl;
                    cin >> gender;
                    cout << "Enter Student year" << endl;
                    cin >> year;
                    nostud++;
                    add(root, id, name, age, gender, year);
                    student.open("studentList.txt", ios::app);
                    write(root);
                    cout << "~~~ REGISTER COMPLETE~~~~" << endl;
                    cout << "~~~ PLEASE REGISTER THE NEXT STUDENT ~~" << endl;
                } while (nostud < noreg);
            }

            break;

        case 2:
            read();
            break;
        case 3:
            cout << "Enter ID TO search" << endl;
            cin >> key;
            cout << search(root, key)->name;
            break;
        case 4:
            cout << "Enter ID TO delete" << endl;
            cin >> key;
            deleteNode(root, key);
            cout << "After Deleting Student Record" << endl;
            inorder(root);
        case 5:
            key = minId(root);
            deleteNode(root, key);
            cout << "After Deleting Minimum ID" << endl;
            inorder(root);
        case 6:
            key = maxId(root);
            deleteNode(root, key);
            cout << "After Delteing Maximum ID" << endl;
            inorder(root);
        case 7:
            cout << "There are " << countStudent(root) << "student in the list";
            break;
        case 8:
            inorder(root);
            break;

        case 9:
            Preorder(root);
            break;

        case 10:
            displayPostOrder(root);
            break;
        case 11:
            minId(root);
            break;

        case 12:
            maxId(root);
            break;

        case 13:
            avl(root);

        case 0:
            return 0;
        }
    }
    return 0;
}