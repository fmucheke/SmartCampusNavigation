# Smart Campus Navigation and Facility Analytics System

## About Our Project

This is a C++ project that helps people find facilities on a college campus. It also shows how buildings are connected and how different departments are organized.

We made this project to learn more about coding, data structures, and working together as a team.

## What Our Program Does

Our program allows users to:

1. View all campus facilities.
2. Search for a facility using its ID.
3. View campus buildings and their connections.
4. Check the number of buildings and connections.
5. Find which buildings can be reached from another building.
6. Add a new department.
7. Search for a department.
8. View the department hierarchy.
9. Display departments in preorder.
10. Exit the program.

## How Our Program Works

We used three main data structures.

**Hash Table:** Helps us find facilities using their IDs.

**Graph:** Shows how campus buildings are connected. We use BFS to find which buildings can be reached from a starting building.

**Tree:** Helps us organize departments. For example, a university has different colleges, and each college has departments under it.

## Files We Used

Our program reads four text files from the `data` folder.

- `buildings.txt` – Lists campus buildings.
- `connections.txt` – Shows which buildings are connected.
- `facilities.txt` – Lists facilities and their locations.
- `departments.txt` – Lists departments and their parent departments.

The program reads these files when it starts. If there is an incorrect record, it shows a warning and continues.

## Project Folders and Files

- `src/` – Contains our C++ code.
- `include/` – Contains our header files.
- `data/` – Contains the campus information.
- `testdata/` – Contains extra files for testing.
- `README.txt` – Explains our project.
- `CONTRIBUTIONS.txt` – Shows what each member worked on.
- `design_document.txt` – Explains how we designed the program.
- `test_results.txt` – Shows our testing results.
- `.gitignore` – Keeps unnecessary files out of GitHub.

## How to Run Our Program

We use the UNT CSE CELL machines at school to run our program.

First, we log in to a CELL machine and open the terminal. Then we go to the folder where our project is saved.

**Step 1: Compile the program**

```bash
g++ -Iinclude src/*.cpp -o campus
```

This puts our C++ files together and creates a program called `campus`.

**Step 2: Run the program**

```bash
./campus
```

This starts the program and loads the original campus information.

**Step 3: Run with test files**

We can also use different files to test our program.

To test incorrect department records:

```bash
./campus testdata/tree_bad
```

To test an empty department tree:

```bash
./campus testdata/tree_empty
```

To test a tree with only one department:

```bash
./campus testdata/tree_root_only
```

These commands help us check how our program works in different situations.

## How to Use the Program

When the program starts, a menu appears.

We enter a number to choose what we want to do. For example, entering 1 shows all facilities, entering 5 finds reachable buildings, and entering 8 displays the department hierarchy.

After each task, the menu appears again. Enter 10 to exit the program.

## Testing

We test our program to make sure it works correctly.

We check things like searching for facilities, finding connected buildings, adding departments, handling duplicate names, and entering incorrect information.

We also test what happens when a file is missing or a user enters an invalid option.

Our test results are recorded in `test_results.txt`.

## Team Contributions

There are three members working on this project.

**Member A:** Works on facilities and the hash table.

**Member B:** Works on campus buildings, connections, and BFS.

**Member C:** Works on the department tree, adding and searching for departments, and displaying the hierarchy.

We use GitHub to share our work and combine our code.

More information about each member's work is in `CONTRIBUTIONS.txt`.

## Milestone 1

For Milestone 1, we worked on the main parts of our program. We focused on loading files, searching for facilities, showing building connections, finding reachable buildings, and organizing departments.

We also added a menu so users can choose what they want to do.

We will add more features for the final project.
