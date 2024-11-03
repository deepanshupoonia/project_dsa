Multimedia Content Library

This project is a C++ implementation of a multimedia content library, enabling users to store, search, and delete multimedia content items based on spatial bounding boxes. The library uses an R-Tree data structure to efficiently handle spatial queries, making it suitable for applications involving geospatial data or multimedia with spatial coordinates.

Table of Contents

Features
Project Structure
Requirements
Getting Started
Usage
Adding Content
Searching Content
Deleting Content
Expected Outputs
File Structure
Notes
Features

R-Tree Data Structure: Efficient storage and querying of multimedia content based on spatial bounding boxes.
CSV Persistence: Stores multimedia content in a CSV file, enabling content persistence across sessions.
Add, Search, and Delete Functionality: Supports adding new content, searching by bounding box, and deleting content.
Multi-user Support: Users can log in or create accounts, with content stored separately for each user.
Project Structure

Main Code: main.cpp - Contains the R-Tree implementation and user interface logic.
Data File: users_content.csv - CSV file storing multimedia content for all users.
Requirements

Compiler: A C++ compiler that supports C++11 or later (e.g., g++).
Libraries: No external libraries are required. The project uses standard C++ libraries.
Getting Started

Clone or Download the project repository to your local machine.
Compile the Code:
bash
Copy code
g++ main.cpp -o multimedia_content_library
Run the Executable:
bash
Copy code
./multimedia_content_library
Usage

Upon running the program, you will be prompted to log in or create a new account. Follow these steps:

1. Log In or Create a New User
Enter your username. If you are a new user, type new to create an account.
If you choose new, you will be asked to enter a username. This username is used to organize content uniquely for each user.
2. Main Menu
After logging in, the main menu provides the following options:

plaintext
Copy code
Select an option:
1. Add new content
2. Search content by bounding box
3. Delete content by bounding box
4. Exit
Adding Content
Option: 1
Input Details:
ID: A unique integer identifier for the content.
Title: A string representing the title of the multimedia content.
Tags: Tags or keywords describing the content (comma-separated).
Bounding Box: Coordinates in the format xmin ymin xmax ymax (representing spatial boundaries).
Expected Output: A success message, and the content will be saved in the users_content.csv file.
Example:

plaintext
Copy code
Enter content ID: 101
Enter title: Sunset Photo
Enter tags (comma-separated): nature, sunset, beach
Enter bounding box coordinates (xmin ymin xmax ymax): 10 20 30 40
Searching Content
Option: 2
Input Details:
Bounding Box: Coordinates in the format xmin ymin xmax ymax for searching.
Expected Output: The program will create a text file named <username>_search_result.txt containing the details of all multimedia content that matches the specified bounding box.
Example:

plaintext
Copy code
Enter bounding box coordinates to search (xmin ymin xmax ymax): 10 20 30 40
Expected File Output (<username>_search_result.txt):
plaintext
Copy code
ID: 101, Title: Sunset Photo, Tags: nature, sunset, beach, Bounding Box: [10, 20, 30, 40]
Deleting Content
Option: 3
Input Details:
Bounding Box: Coordinates in the format xmin ymin xmax ymax to specify content for deletion.
Expected Output: A success message confirming deletion, and the users_content.csv file will be updated accordingly.
Example:

plaintext
Copy code
Enter bounding box coordinates to delete (xmin ymin xmax ymax): 10 20 30 40
Expected Output:
plaintext
Copy code
Content deleted successfully.
Expected Outputs

Adding Content: "Content added successfully."
Search Results: Results saved to a text file (e.g., username_search_result.txt).
Deleting Content: "Content deleted successfully."
File Structure

users_content.csv: Contains multimedia content for each user in the format:
csv
Copy code
username,id,title,tags,xmin,ymin,xmax,ymax
<username>_search_result.txt: Search results file, created per user based on search queries.
Notes

CSV Persistence: The users_content.csv file will be updated every time content is added or deleted.
Data Consistency: Ensure unique IDs for each multimedia content item within a user's account.
Bounding Box Format: Maintain consistent format xmin ymin xmax ymax for all spatial data.
This README should provide clear guidance on how to use your multimedia content library, making it easy for others to understand and utilize your project.






