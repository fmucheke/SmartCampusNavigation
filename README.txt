SMART CAMPUS NAVIGATION AND FACILITY ANALYTICS SYSTEM

GitHub Repository:
https://github.com/fmucheke/SmartCampusNavigation

## About Our Project
This is a C++ project that helps people find facilities on a college campus. It also shows how buildings are connected, finds the shortest path between buildings and displays how different departments are organized.

We made this project to learn more about data structures, problem-solving and working together as a team.

## What Our Program Does

Our program has 18 menu options:

1. View all facilities
2. Search facility by ID
3. Search facility by name
4. Search facility by category
5. View campus graph
6. Display graph counts and degrees
7. Find reachable buildings (BFS)
8. Find shortest path
9. Add department
10. Search department
11. Display department hierarchy
12. Preorder traversal
13. Postorder traversal
14. Level-order traversal
15. Department statistics
16. Facility category report
17. Graph connectivity report
18. Exit

## How Our Program Works

We used three main data structures.

### Hash Table

We used a custom hash table to find facilities quickly using their IDs. Instead of searching through every facility, the program uses a hash function to find which bucket contains the facility.

We created our own hash table without using a built-in library hash table.

**Hash function:**

    h = 0
    For each character c in the facility ID:
        h = (h * 31 + c) % capacity

The final value of h is the bucket number.

Our hash table has a default capacity of 101 buckets. Facility IDs must start with the letter F followed by exactly three digits, such as F004.

The program removes extra spaces and converts IDs to uppercase before hashing, so f004 and F004 are treated as the same ID.

**Collision handling:**

Sometimes two different facility IDs end up in the same bucket. This is called a collision.

We used separate chaining to handle collisions. Each bucket contains a vector that can store multiple facilities.

For example, F001 and F039 both go into bucket 16. Both facilities can still be stored and searched.

A collision is counted when a new facility is successfully added to a bucket that already contains another facility. Duplicate IDs are rejected and do not increase the collision count.

The hash table has a fixed capacity and does not resize. However, the vectors inside the buckets can grow when needed.

Searching by ID uses the hash table, while searching by name and category uses linear search. Name and category searches ignore capitalization and display all exact matches.

### Graph

The graph shows how campus buildings are connected. Each building has a list of its neighboring buildings, which is called an adjacency list.

Connections work both ways. The program counts each connection only once and does not allow duplicate connections or connections from a building to itself.

We use Breadth-First Search (BFS) to find reachable buildings, the shortest path between two buildings and connected components.

The shortest path is based on the fewest connections between buildings, not the actual walking distance.

The graph connectivity report shows the total buildings, total connections, buildings with the highest degree, isolated buildings and number of connected components.

### Tree

We used a general tree to organize departments because each department can have multiple children.

Each department has a name, a parent and a list of its children.

The program supports three types of traversals:

- Preorder: Visits the parent before its children.
- Postorder: Visits the children before their parent.
- Level-order: Visits departments one level at a time.

The children of each department are visited in the order they were added.

The program also displays the following department statistics:

- Total number of departments.
- Number of leaf departments.
- Tree height.
- Maximum number of children.

The tree height is measured in edges. If the tree is empty, the height is displayed as N/A.

## Files We Used

Our program reads four text files from the data folder in the following order:

- buildings.txt – Lists campus buildings.
- connections.txt – Shows which buildings are connected.
- facilities.txt – Lists facilities and their locations.
- departments.txt – Lists departments and their parent departments.

The program reads these files when it starts. If there is an incorrect record, it displays a warning with the file name, line number and reason. It then continues loading the remaining records.

## Project Folders and Files

- src/ – Contains our C++ code.
- include/ – Contains our header files.
- data/ – Contains the campus information.
- testdata/ – Contains extra files for testing.
- README.txt – Explains our project and how to run it.
- CONTRIBUTIONS.txt – Shows each member's work, individual reflections and code review.
- design_document.txt – Explains how we designed the program.
- test_results.txt – Contains our testing results.
- .gitignore – Keeps unnecessary files out of GitHub.

## How to Run Our Program

The program uses C++17 and is intended to run on the UNT CSE CELL machines.

First, log in to a CELL machine and open the terminal. Go to the folder where the project is saved.

### Step 1: Compile the program

    g++ -std=c++17 -Iinclude src/*.cpp -o campus

This compiles the C++ files and creates a program called campus.

### Step 2: Run the program

    ./campus

This starts the program and loads the original campus information from the data folder.

### Step 3: Run with test files

We can also use different data folders to test the program.

To test incorrect department records:

    ./campus testdata/tree_bad

To test an empty department tree:

    ./campus testdata/tree_empty

To test a tree with only one department:

    ./campus testdata/tree_root_only

To test the maximum number of children:

    ./campus testdata/tree_max_children

To test hash table collisions:

    ./campus testdata/collision

To test shortest paths with equal numbers of connections:

    ./campus testdata/graph_tie

To test a missing data folder:

    ./campus testdata/nofolder

## How to Use the Program

When the program starts, a menu appears. Enter a number from 1 to 18 to select an option.

For example, option 2 searches for a facility by ID, option 8 finds the shortest path between buildings and option 15 displays department statistics.

After each task, the menu appears again. Enter 18 to exit the program.

Departments added through the menu are stored in memory only. They do not change the original departments.txt file.

## Testing

We tested the program using normal data, invalid records, empty files and different user inputs.

Our testing includes:

- Facility searches and hash table collisions.
- Duplicate and invalid facility IDs.
- Facility category counts and percentages.
- BFS reachability and shortest paths.
- Graph connectivity and isolated buildings.
- Department searches and traversals.
- Department statistics.
- Empty trees and root-only trees.
- Maximum number of children in different tree structures.
- Missing files and invalid menu inputs.

All completed tests passed successfully. The program handled the tested valid and invalid inputs correctly, and the tested features worked as expected.

Our expected outputs, actual outputs and individual test results are recorded in test_results.txt.

## Team Contributions

### Member A – Urisha Shrestha

Worked on facilities, the custom hash table, facility searches and the facility category report.

### Member B – Franklin Mucheke

Worked on the campus graph, graph loading, BFS reachability, shortest path and graph connectivity report.

### Member C – Samriddi Upreti

Worked on the department tree, department searches, tree traversals, department statistics and project documentation.

All members contributed to testing, debugging and combining the modules. More information about each member's work is in CONTRIBUTIONS.txt.

## Final Submission

For the Final submission, we expanded the features from Milestone 1. We added facility name and category searches, shortest path, postorder and level-order traversals, department statistics, facility category reports and graph connectivity reports.

We continued using our original three data structures: a custom hash table, an adjacency list graph and a general tree.

The updated menu combines all these features into one program.

Through this project, we learned how different data structures can work together to solve a problem and how to develop and test a program as a team.
