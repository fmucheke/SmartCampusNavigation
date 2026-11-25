#ifndef DEPARTMENT_TREE_H
#define DEPARTMENT_TREE_H

// Samriddi Upreti
// This file is for DepartmentNode and DepartmentTree.
// It stores the departments and their hierarchy from departments.txt.

#include <string>
#include <vector>

// This stores each department with its parent and children.
struct DepartmentNode {
    std::string name;
    DepartmentNode* parent;                 // null if its root
    std::vector<DepartmentNode*> children;  // stores all the child departments

    explicit DepartmentNode(const std::string& deptName,
                            DepartmentNode* parentNode = nullptr)
        : name(deptName), parent(parentNode) {}
};

// This class is used to manage all the departments in tree.
class DepartmentTree {
public:
    DepartmentTree();
    ~DepartmentTree();

    // Stops copying the tree because it uses pointers.
    DepartmentTree(const DepartmentTree&) = delete;
    DepartmentTree& operator=(const DepartmentTree&) = delete;

    // tree2 Reads departments from file and counts accepted and rejected.
    void loadFromFile(const std::string& path,
                      const std::string& displayName,
                      int& accepted, int& rejected);

    // tree 3 Adds department to the tree.
    // If tree is empty, first department will be the root.
    bool addDepartment(const std::string& name,
                       const std::string& parentName,
                       std::string& errorReason);

    bool isEmpty() const;

    // Finds department by name without checking uppercase or lowercase.
    DepartmentNode* findDepartment(const std::string& name) const;

    // Gets how deep the department is from root.
    int getDepth(const DepartmentNode* node) const;

    // tree 4  Searches department and shows its information.
    void searchAndDisplay(const std::string& name) const;

    // tree 5  Shows departments in hierarchy with 4 spaces for each level.
    void displayHierarchy() const;

    // tree 6  Gets the departments in preorder.
    std::vector<std::string> preorder() const;

// tree 7 gets the departments in postorder children and then parent 
std::vector<std::string> postorder() const;

    // tree 7 gets department in level order usinf queue
    std::vector<std::string> levelOrder() const;

    // tree 8 shows total deartment , leafc counts nad trees height
    void displayStatistics() const;

    // Prints the preorder departments without spaces for levels.
    void printSequence(const std::string& title,
                       const std::vector<std::string>& sequence) const;

private:
    DepartmentNode* root;
    int nodeCount;

    // Deletes all the nodes from tree.
    void destroySubtree(DepartmentNode* node);

    void displayHelper(const DepartmentNode* node, int depth) const;
    void preorderHelper(const DepartmentNode* node,
                        std::vector<std::string>& out) const;
//  helper functions for postorder and statistics
    void postorderHelper(const DepartmentNode* node,
                         std::vector<std::string>& out) const;
    int countLeaves(const DepartmentNode* node) const;
    int heightHelper(const DepartmentNode* node) const;

 //added helper for maximum children
    int maxChildren(const DepartmentNode* node) const;

};

#endif
