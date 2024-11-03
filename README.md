Multimedia Content Library

Team Members

Lavudya Sai Mani Chaitanya - 2023CSB1133,
Deepanshu Poonia - 2023CSB1117,
Aman Sinam - 2023CSB1098,
Mentoring TA-Deepu Yadav.
This project is a C++ implementation of a multimedia content library that enables users to store, search, and delete multimedia content items based on spatial bounding boxes. The library uses an R-Tree data structure to efficiently handle spatial queries, making it suitable for applications involving geospatial data or multimedia with spatial coordinates.

Table of Contents

Features,
Project Structure,
Requirements,
Getting Started,
Usage,
Adding Content,
Searching Content,
Deleting Content,
Expected Outputs,
File Structure,
Notes,
Features.

R-Tree Data Structure: Efficient storage and querying of multimedia content based on spatial bounding boxes.
CSV Persistence: Stores multimedia content in a CSV file, enabling content persistence across sessions.
Add, Search, and Delete Functionality: Supports adding new content, searching by bounding box, and deleting content.
Project Structure

This project has the following core components:

R-Tree Implementation: Provides efficient handling of spatial bounding boxes for multimedia items.
Multimedia Content Library: Core library for managing multimedia items, including adding, searching, and deleting content.
CSV Data Storage: Handles loading and saving data to a CSV file to ensure data persistence across sessions.
Requirements

C++ compiler (supporting C++11 or higher)
Standard C++ libraries
CSV file (for data persistence)
Getting Started

Clone the repository:
bash
Copy code
git clone https://github.com/your-username/multimedia-content-library.git
Compile the code:
bash
Copy code
g++ main.cpp -o multimedia_library
Run the executable:
bash
Copy code
./multimedia_library
Usage

Adding Content
Input: Specify the content's ID, name, type, and bounding box coordinates.
Expected Result: The content item will be added to the R-Tree structure and saved in the CSV file.
Searching Content
Input: Enter bounding box coordinates to search within.
Expected Result: Returns a list of content items that intersect with the specified bounding box.
Deleting Content
Input: Provide the ID of the content you wish to delete.
Expected Result: The content item is removed from both the R-Tree structure and the CSV file.
Expected Outputs

Add Content: Confirmation message showing that the item has been added.
Search Content: List of content items within the search area.
Delete Content: Confirmation message that the item has been deleted.
File Structure

main.cpp - The main executable file.
rtree.h - R-Tree implementation header file.
content_library.cpp - Contains functions for adding, searching, and deleting content.
content.csv - CSV file used for storing content data.
Notes

Make sure the content.csv file exists in the same directory as the executable.
Proper error handling is included, but ensure valid inputs for optimal functionality.
This README provides a comprehensive overview of the Multimedia Content Library, including setup, usage, and expected results.













