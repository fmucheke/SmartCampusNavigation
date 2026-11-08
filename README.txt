# Smart Campus Navigation and Facility Analytics System

## About the Project

This is a C++ project that helps users find facilities and buildings on a college campus. It also shows how different buildings are connected and how departments are organized.

We made this project to practice using data structures like hash tables, graphs, and trees.

## What the Program Does

The program can:

- Show all the facilities on campus.
- Search for a facility using its ID.
- Show campus buildings and their connections.
- Count the buildings, connections, and neighbors.
- Find buildings that can be reached from another building using BFS.
- Add a new department.
- Search for a department by its name.
- Display the department hierarchy.
- Show departments in preorder traversal.

## How the Project Works

The program reads information from four text files inside the `data` folder.

- `buildings.txt` contains the names of campus buildings.
- `connections.txt` contains the connections between buildings.
- `facilities.txt` contains facility IDs, names, buildings, and categories.
- `departments.txt` contains departments and their parent departments.

We used a hash table to search for facilities by ID, a graph to store building connections, and a general tree to organize departments.

## Project Files

- `include/` – Contains the header files.
- `src/` – Contains the C++ code.
- `data/` – Contains the four campus data files.
- `testdata/` – Contains extra files for testing.
- `README.txt` – Explains the project and how to run it.
- `CONTRIBUTIONS.txt` – Shows what each team member worked on.
- `design_document.txt` – Explains how we designed the program.
- `test_results.txt` – Contains the results of our tests.

## How to Run the Program

1. Download the project from GitHub.
2. Extract the ZIP file.
3. Open the project folder in VS Code or another C++ development environment.
4. Open the terminal in the main project folder.
5. Compile the C++ files using a C++ compiler.
6. Run the program.
7. Choose an option from the menu.

The program normally reads the files from the `data` folder. You can also give it another folder name to test different data files.

## Milestone 1

For Milestone 1, we worked on loading the data files, creating the hash table, building the campus graph, using BFS, and creating the department tree.

We also added a menu so users can choose what they want to do.

## Teamwork

This project was completed by three team members. Each member worked on a different part of the program, and we used GitHub to share our code and combine our work.

More information about each member's work is in `CONTRIBUTIONS.txt`.
