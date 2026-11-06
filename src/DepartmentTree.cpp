

 // Samriddi Upreti
 // This file has the functions for department tree.
 // It loads departments, adds them, searches and displays the tree.

#include "DepartmentTree.h"
#include "FileUtils.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Makes a empty department tree.
DepartmentTree::DepartmentTree() {
    root = nullptr;
    nodeCount = 0;
}

// Deletes the tree when its not used anymore.
DepartmentTree::~DepartmentTree() {
    destroySubtree(root);
}

// Deletes the child nodes first and then the parent.
void DepartmentTree::destroySubtree(DepartmentNode* node) {
    if (node == nullptr) {
        return;
    }

    for (DepartmentNode* child : node->children) {
        destroySubtree(child);
    }

    delete node;
}

// Checks if there is any department in tree.
bool DepartmentTree::isEmpty() const {
    return root == nullptr;
}

// Finds a department by checking its name.
DepartmentNode* DepartmentTree::findDepartment(
    const std::string& name) const {

    std::string target = StandardizeName(name);

    if (target.empty()) {
        return nullptr;
    }

    // Uses preorder to search the tree.
    std::vector<DepartmentNode*> pending;

    if (root != nullptr) {
        pending.push_back(root);
    }

    while (!pending.empty()) {
        DepartmentNode* current = pending.back();
        pending.pop_back();

        if (StandardizeName(current->name) == target) {
            return current;
        }

        // Adds childrens in reverse so first child gets checked first.
        for (int i = static_cast<int>(current->children.size()) - 1;
             i >= 0; --i) {
            pending.push_back(current->children[i]);
        }
    }

    return nullptr;
}

// Adds a department if its name and parent are valid.
bool DepartmentTree::addDepartment(
    const std::string& name,
    const std::string& parentName,
    std::string& errorReason) {

    errorReason.clear();

    std::string cleanName = name;
    std::string cleanParent = parentName;

    // Remove spaces from start and end but keep original letters.
    const std::string spaces = " \t\n\r\f\v";

    size_t first = cleanName.find_first_not_of(spaces);
    if (first == std::string::npos) {
        errorReason = "Department name cannot be empty";
        return false;
    }
    size_t last = cleanName.find_last_not_of(spaces);
    cleanName = cleanName.substr(first, last - first + 1);

    first = cleanParent.find_first_not_of(spaces);
    if (first == std::string::npos) {
        cleanParent = "";
    } else {
        last = cleanParent.find_last_not_of(spaces);
        cleanParent = cleanParent.substr(first, last - first + 1);
    }

    // Checks if same department is already there.
    if (findDepartment(cleanName) != nullptr) {
        errorReason = "Duplicate department: " + cleanName;
        return false;
    }

    // First department becomes root.
    if (isEmpty()) {
        root = new DepartmentNode(cleanName);
        nodeCount++;
        return true;
    }

    if (cleanParent.empty()) {
        errorReason = "Parent name cannot be empty";
        return false;
    }

    DepartmentNode* parentNode = findDepartment(cleanParent);

    if (parentNode == nullptr) {
        errorReason = "Unknown parent: " + cleanParent;
        return false;
    }

    // Adds new department under the parent.
    DepartmentNode* newNode =
        new DepartmentNode(cleanName, parentNode);

    parentNode->children.push_back(newNode);
    nodeCount++;

    return true;
}

// Reads the department file and checks the records.
void DepartmentTree::loadFromFile(
    const std::string& path,
    const std::string& displayName,
    int& accepted,
    int& rejected) {

    accepted = 0;
    rejected = 0;

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Error: Cannot open " << path << "\n";
        return;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        // Skips blank lines and comments.
        if (StandardizeName(line).empty()) {
            continue;
        }

        size_t start = line.find_first_not_of(" \t\r\n");
        if (start != std::string::npos && line[start] == '#') {
            continue;
        }

        // Each line should have only one |.
        size_t separator = line.find('|');

        if (separator == std::string::npos ||
            line.find('|', separator + 1) != std::string::npos) {

            rejected++;
            std::cout << "Warning: " << displayName
                      << " line " << lineNumber
                      << ": Wrong number of fields\n";
            continue;
        }

        std::string name = line.substr(0, separator);
        std::string parent = line.substr(separator + 1);

        if (StandardizeName(name).empty() ||
            StandardizeName(parent).empty()) {

            rejected++;
            std::cout << "Warning: " << displayName
                      << " line " << lineNumber
                      << ": Empty department or parent name\n";
            continue;
        }

        // First accepted department must have NONE as parent.
        if (isEmpty() && StandardizeName(parent) != "NONE") {
            rejected++;
            std::cout << "Warning: " << displayName
                      << " line " << lineNumber
                      << ": Root must have parent NONE\n";
            continue;
        }

        // There can only be one root.
        if (!isEmpty() && StandardizeName(parent) == "NONE") {
            rejected++;
            std::cout << "Warning: " << displayName
                      << " line " << lineNumber
                      << ": Another root is not allowed\n";
            continue;
        }

        std::string errorReason;

        if (addDepartment(name, parent, errorReason)) {
            accepted++;
        } else {
            rejected++;
            std::cout << "Warning: " << displayName
                      << " line " << lineNumber
                      << ": " << errorReason << "\n";
        }
    }

    file.close();
}

// Finds how many levels a department is below root.
int DepartmentTree::getDepth(const DepartmentNode* node) const {
    if (node == nullptr) {
        return -1;
    }

    int depth = 0;

    while (node->parent != nullptr) {
        depth++;
        node = node->parent;
    }

    return depth;
}

// Searches for a department and shows its information.
void DepartmentTree::searchAndDisplay(
    const std::string& name) const {

    if (StandardizeName(name).empty()) {
        std::cout << "Error: Department name cannot be empty\n";
        return;
    }

    DepartmentNode* department = findDepartment(name);

    if (department == nullptr) {
        std::cout << "Department not found: " << name << "\n";
        return;
    }

    std::cout << "Department: " << department->name << "\n";

    if (department->parent == nullptr) {
        std::cout << "Parent: None\n";
    } else {
        std::cout << "Parent: "
                  << department->parent->name << "\n";
    }

    std::cout << "Direct children: "
              << department->children.size() << "\n";

    std::cout << "Depth: " << getDepth(department) << "\n";
}

// Prints the department and then its childrens.
void DepartmentTree::displayHelper(
    const DepartmentNode* node,
    int depth) const {

    if (node == nullptr) {
        return;
    }

    std::cout << std::string(depth * 4, ' ')
              << node->name << "\n";

    for (const DepartmentNode* child : node->children) {
        displayHelper(child, depth + 1);
    }
}

// Shows the department hierarchy.
void DepartmentTree::displayHierarchy() const {
    if (isEmpty()) {
        std::cout << "No departments are loaded.\n";
        return;
    }

    displayHelper(root, 0);
}

// Visits the parent first and then all its childrens.
void DepartmentTree::preorderHelper(
    const DepartmentNode* node,
    std::vector<std::string>& out) const {

    if (node == nullptr) {
        return;
    }

    out.push_back(node->name);

    for (const DepartmentNode* child : node->children) {
        preorderHelper(child, out);
    }
}

// Gets the department names in preorder.
std::vector<std::string> DepartmentTree::preorder() const {
    std::vector<std::string> result;
    preorderHelper(root, result);
    return result;
}

// Prints the traversal as a sequence without indentation.
void DepartmentTree::printSequence(
    const std::string& title,
    const std::vector<std::string>& sequence) const {

    std::cout << title << "\n";

    if (sequence.empty()) {
        std::cout << "No departments are loaded.\n";
        return;
    }

    for (size_t i = 0; i < sequence.size(); i++) {
        if (i > 0) {
            std::cout << " -> ";
        }
        std::cout << sequence[i];
    }

    std::cout << "\n";
}
