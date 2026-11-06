
#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

// Samriddi Upreti
// This file is for DepartmentNode and DepartmentTree.
// It stores the departments and their hierarchy from departments.txt.

#include <string>
#include <vector>

// This stores each department with its parent and childrens.
struct DepartmentNode {
    std::string name;                       
    DepartmentNode* parent;                 // null if its root
    std::vector<DepartmentNode*> children;  // stores all the child departments

    // This creates a department node.
    explicit DepartmentNodconst std::string& deptName,
                            DepartmentNode* parentNode = nullptr)
   : name(deptName), parent(parentNode) {}
};

// This class is used to manage all the departments in tree.
class DepartmentTree {
public:
    // Creates a empty tree.
    DepartmentTree();

    
    ~DepartmentTree();

    // Stops copying the tree because it uses pointers.
 DepartmentTree(const DepartmentTree&) = delete;  
    DepartmentTree& operator=(const DepartmentTree&) = delete;


    // TREE-2: Reads departments from file and counts accepted and rejected.
    void loadFromFile(const std::string& path,
            const std::string& displayName,
            int& accepted, int& rejected);

    // TREE-3: Adds department to the tree.
    // If tree is empty, first department will be the root.
 bool addDepartment(const std::string& name,
              const std::string& parentName,
      std::string& errorReason);

    // Checks if tree is empty or not.
bool isEmpty() const;

    // Finds department by name without checking uppercase or lowercase.
DepartmentNode* findDepartment(const std::string& name) const;

    // Gets how deep the department is from root.
  int getDepth(const DepartmentNode* node) const;

    // TREE-4: Searches department and shows its information.
    void searchAndDisplay(const std::string& name) const;

    // TREE-5: Shows departments in hierarchy with 4 spaces for each level.
 void displayHierarchy() const;

    // TREE-6: Gets the departments in preorder.
    std::vector<std::string> preorder() const;

    // Prints the preorder departments without spaces for levels.
    void printSequence(
     const std::string& title,
    const std::vector<std::string>& sequence) const;

private:
    DepartmentNode* root;
    int nodeCount;

    // Deletes all the nodes from tree.
void destroySubtree(DepartmentNode* node);

  
void displayHelper(const DepartmentNode* node,
                       int depth) const;

 void preorderHelper(
  const DepartmentNode* node,
 std::vector<std::string>& out) const;
};

#endif 

