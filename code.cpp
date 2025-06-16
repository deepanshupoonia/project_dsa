//MULTIMEDIA CONTENT LIBRARY
//The project is about creating a multimedia content library that allows users to add, search, and delete multimedia content based on a spatial bounding box.
//The project uses an R-Tree data structure to store multimedia content and perform spatial queries. 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <unordered_map>
//including the unordered map library
#include <sstream>
//including the sstream library
#include <algorithm>
//defining the maximum number of children
#define MAX_CHILDREN 4


//defining the namespace
using namespace std;


// Structure representing a spatial bounding box
struct BoundingBox {
    float xmin, ymin, xmax, ymax;

    BoundingBox(float x_min = 0, float y_min = 0, float x_max = 0, float y_max = 0)
        : xmin(x_min), ymin(y_min), xmax(x_max), ymax(y_max) {}

// Method to check if the bounding box intersects with another bounding box
    void expandToInclude(const BoundingBox& other) {
        // Expand the bounding box to include another bounding box
        xmin = min(xmin, other.xmin);
        //finding the minimum of the x coordinates
        ymin = min(ymin, other.ymin);
        //finding the minimum of the y coordinates
        xmax = max(xmax, other.xmax);
        //finding the maximum of the x coordinates
        ymax = max(ymax, other.ymax);
    }
};

// Structure for each multimedia item
struct MultimediaContent {
    int id;
    string title;
    string tags;
    BoundingBox box;

    MultimediaContent(int content_id, const string& content_title, const string& content_tags, BoundingBox content_box)
        : id(content_id), title(content_title), tags(content_tags), box(content_box) {}
};

// Structure for an R-Tree node
struct RTreeNode {
    bool is_leaf;
    //defining the bounding box
    BoundingBox box;
    //defining the vector of multimedia content
    vector<MultimediaContent*> contents;
    vector<RTreeNode*> children;
    // Constructor for the R-Tree node
// Constructor for the R-Tree node
    RTreeNode(bool leaf, BoundingBox bounding_box)
        : is_leaf(leaf), box(bounding_box) {}

// Destructor for the R-Tree node
    ~RTreeNode() {
        for (auto content : contents) {
            delete content;
        }
        // Delete children recursively
        for (auto child : children) {
            delete child;
        }
    }

// Method to add content to the node

    void addContent(MultimediaContent* content) {
        contents.push_back(content);
        // Update bounding box after adding content
        box.expandToInclude(content->box);
    }

    bool needsSplit() const {
        // Check if the node needs to be split based on the number of children
        return contents.size() > MAX_CHILDREN;
    }

    // Method to delete content based on bounding box
    void deleteContent(const BoundingBox& query_box) {
        if (is_leaf) {
            // Delete content that intersects with the query bounding box
            auto it = contents.begin();
            // Iterate through the contents and delete the content that intersects with the query bounding box
            while (it != contents.end()) {
                if (intersects((*it)->box, query_box)) {
                    delete *it; // Delete the content
                    it = contents.erase(it); // Remove from the vector
                } else {
                    ++it;
                }
            }
            // Update bounding box after deletion
            box = BoundingBox();
            for (auto* content : contents) {
                // Update bounding box after deletion
                box.expandToInclude(content->box);
            }
        } else {
            for (auto* child : children) {
                // Recursively delete content from the child nodes
                child->deleteContent(query_box);
            }
            // Update bounding box after deletion
            box = BoundingBox();
            for (auto* child : children) {
                // Update bounding box after deletion
                box.expandToInclude(child->box);
            }
        }
    }

    bool intersects(const BoundingBox& box1, const BoundingBox& box2) {
        // Check if the bounding box intersects with another bounding box
        return (box1.xmin <= box2.xmax && box1.xmax >= box2.xmin &&
        // Check if the bounding box intersects with another bounding box
                box1.ymin <= box2.ymax && box1.ymax >= box2.ymin);
    }
};

// Class for the R-Tree
class RTree {
public:
// Constructor for the R-Tree
    RTree() {
        root = new RTreeNode(true, BoundingBox(0, 0, 1000, 1000));
    }
// Destructor for the R-Tree
    ~RTree() {
        delete root;
    }
// Method to insert content into the R-Tree
    void insert(MultimediaContent* content) {
        insert(root, content);
        // Check if the root node needs to be split
        if (root->needsSplit()) {
            splitRoot();
        }
    }
    // Method to search for content based on bounding box

    void search(const BoundingBox& query_box, ofstream& output_file) {
        // Search for content based on the query bounding box
        searchNode(root, query_box, output_file);//searching the node
    }

    void deleteContent(const BoundingBox& query_box) {
        // Delete content based on the query bounding box
        root->deleteContent(query_box);
    }

    vector<MultimediaContent*> getAllContents() {
        // Get all contents in the R-Tree
        vector<MultimediaContent*> all_contents;
        // Gather all contents in the R-Tree
        gatherContents(root, all_contents);
        // Return all contents
        return all_contents;
    }

private:
    RTreeNode* root;
// Method to gather all contents in the R-Tree
    void gatherContents(RTreeNode* node, vector<MultimediaContent*>& all_contents) {
        if (node->is_leaf) {
            all_contents.insert(all_contents.end(), node->contents.begin(), node->contents.end());
        } else {
            // Recursively gather contents from the child nodes
            for (auto* child : node->children) {
                gatherContents(child, all_contents);
            }
        }
    }
// Method to check if the bounding box intersects with another bounding box
    bool intersects(const BoundingBox& box1, const BoundingBox& box2) {
        return (box1.xmin <= box2.xmax && box1.xmax >= box2.xmin &&
        // Check if the bounding box intersects with another bounding box
                box1.ymin <= box2.ymax && box1.ymax >= box2.ymin);
    }
// Method to search for content based on bounding box
    void searchNode(RTreeNode* node, const BoundingBox& query_box, ofstream& output_file) {
        if (intersects(node->box, query_box)) {
            if (node->is_leaf) {
                for (auto* content : node->contents) {
                    // Check for exact match with the query bounding box
                    if (content->box.xmin == query_box.xmin &&
                    // Check for exact match with the query bounding box
                        content->box.ymin == query_box.ymin &&
                        // Check for exact match with the query bounding box
                        content->box.xmax == query_box.xmax &&
                        // Check for exact match with the query bounding box
                        content->box.ymax == query_box.ymax) {
                            // Print the content details
                        printContent(content, output_file);
                    }
                }
            } else {
                // Recursively search in the child nodes
                for (auto* child : node->children) {
                    // Recursively search in the child nodes
                    searchNode(child, query_box, output_file);
                    // Recursively search in the child nodes
                }
            }
        }
    }

    void printContent(const MultimediaContent* content, ofstream& output_file) {
        // Print the content details
        output_file << "ID: " << content->id << ", Title: " << content->title
        
                    << ", Tags: " << content->tags
                    // Print the content details
                    << ", Bounding Box: [" << content->box.xmin << ", "
                    << content->box.ymin << ", " << content->box.xmax << ", "
                    // Print the content details
                    << content->box.ymax << "]\n";
    }
// Method to insert content into the R-Tree
    void insert(RTreeNode* node, MultimediaContent* content) {
        if (node->is_leaf) {
            node->addContent(content);
        } else {
            // Add content to the child whose bounding box needs the least expansion
            RTreeNode* best_child = nullptr;
            for (auto* child : node->children) {
                // Add content to the child whose bounding box needs the least expansion
                if (!best_child || areaExpansion(child->box, content->box) < areaExpansion(best_child->box, content->box)) {
                    best_child = child;
                }
            }
            insert(best_child, content);
            node->box.expandToInclude(best_child->box);
        }
    }
// Method to split the root node
    void splitRoot() {
        RTreeNode* new_root = new RTreeNode(false, root->box);
        new_root->children.push_back(root);
        root = new_root;

        // Perform split of the old root
        splitNode(root->children[0]);
    }
// Method to split a node
    void splitNode(RTreeNode* node) {
        if (!node->needsSplit()) return;

        // Split node into two by distributing contents into two groups
        RTreeNode* new_node = new RTreeNode(node->is_leaf, BoundingBox());
        // Assign half of the contents to new_node
        for (size_t i = MAX_CHILDREN / 2; i < node->contents.size(); ++i) {
            // Assign half of the contents to new_node
            new_node->addContent(node->contents[i]);
        }
        // Remove the assigned contents from the original node
        node->contents.resize(MAX_CHILDREN / 2);
        // Update bounding boxes of the nodes
        node->box = BoundingBox();
        // Update bounding boxes of the nodes
        for (auto* content : node->contents) {
            node->box.expandToInclude(content->box);
        }
    }

    float areaExpansion(const BoundingBox& box, const BoundingBox& new_box) {
        float expanded_xmin = min(box.xmin, new_box.xmin);
        //finding the minimum of the x coordinates
        float expanded_ymin = min(box.ymin, new_box.ymin);
        //finding the minimum of the y coordinates
        float expanded_xmax = max(box.xmax, new_box.xmax);
        //finding the maximum of the x coordinates
        float expanded_ymax = max(box.ymax, new_box.ymax);
        //finding the maximum of the y coordinates
        return (expanded_xmax - expanded_xmin) * (expanded_ymax - expanded_ymin) - 
               (box.xmax - box.xmin) * (box.ymax - box.ymin);
    }
};

// Function to load users and their content from a CSV file
unordered_map<string, RTree*> loadUsersFromCSV(const string& filename) {
    unordered_map<string, RTree*> users;
    // Open the CSV file
    ifstream user_file(filename);
    
    if (!user_file) return users;
    // Read the CSV file line by line

    string line;
    while (getline(user_file, line)) {
        stringstream ss(line);
        string username, title, tags;
        int id;
        float xmin, ymin, xmax, ymax;

        // Read the line components
        getline(ss, username, ',');
        ss >> id;
        ss.ignore(); // ignore comma
        getline(ss, title, ',');
        getline(ss, tags, ',');
        ss >> xmin;
        ss.ignore(); // ignore comma
        ss >> ymin;
        ss.ignore(); // ignore comma
        ss >> xmax;
        ss.ignore(); // ignore comma
        ss >> ymax;

        // Create or retrieve the user's RTree
        if (users.find(username) == users.end()) {
            users[username] = new RTree();
        }

        // Create multimedia content and insert it into the user's RTree
        BoundingBox box(xmin, ymin, xmax, ymax);
        MultimediaContent* content = new MultimediaContent(id, title, tags, box);
        users[username]->insert(content);
    }
    user_file.close();
    return users;
}

// Function to append new multimedia content for a user to the CSV file
void appendUserContentToCSV(const string& filename, const string& username, MultimediaContent* content) {
    ofstream user_file(filename, ios::app); // Open in append mode
    if (user_file) {
        user_file << username << "," << content->id << "," << content->title 
                  << "," << content->tags << "," << content->box.xmin << "," 
                  << content->box.ymin << "," << content->box.xmax << "," 
                  << content->box.ymax << "\n"; // Append the content
    }
    user_file.close();
}

// Function to rewrite the CSV file after deletion
void rewriteCSV(const string& filename, const unordered_map<string, RTree*>& users) {
    ofstream user_file(filename);
    if (user_file) {
        for (const auto& pair : users) {
            const string& username = pair.first;
            RTree* tree = pair.second;
            vector<MultimediaContent*> contents = tree->getAllContents();
            for (const auto& content : contents) {
                user_file << username << "," << content->id << "," << content->title
                          << "," << content->tags << "," << content->box.xmin << ","
                          << content->box.ymin << "," << content->box.xmax << ","
                          << content->box.ymax << "\n";
            }
        }
    }
}

// Main function to manage users, add/search content
int main() {
    // Load users and their content from the CSV file
    unordered_map<string, RTree*> users = loadUsersFromCSV("users_content.csv");

    string username;
    // Prompt for user creation or login
    cout << "Enter your username (or type 'new' to create a new user): ";
    cin >> username;
// Create a new user if the username does not exist
    if (username == "new") {
        
        cout << "Enter new username: ";//prompting for the new username
        cin >> username;
        if (users.find(username) != users.end()) {
            // Check if the username already exists
            cout << "Username already exists. Try logging in." << endl;
            return 0;
        }
        users[username] = new RTree();
    } else if (users.find(username) == users.end()) {
        // Check if the username exists
        cout << "Username not found. Please try again." << endl;
        // Check if the username exists
        return 0;
    }
// Main menu for adding/searching content
    int option;
    while (true) {
        cout << "Select an option:\n1. Add new content\n2. Search content by bounding box\n3. Delete content by bounding box\n4. Exit\n";
        cin >> option;
// Add new multimedia content
        if (option == 1) {
            int id;
            string title, tags;
            float xmin, ymin, xmax, ymax;
// Prompt for content details
            cout << "Enter content ID: ";
            cin >> id;
            cout << "Enter title: ";
            // Prompt for content details
            cin.ignore();
           
            getline(cin, title);
            
            cout << "Enter tags (comma-separated): ";
            getline(cin, tags);
            cout << "Enter bounding box coordinates (xmin ymin xmax ymax): ";
            cin >> xmin >> ymin >> xmax >> ymax;
// Create new multimedia content and insert it into the user's RTree
            MultimediaContent* new_content = new MultimediaContent(id, title, tags, BoundingBox(xmin, ymin, xmax, ymax));
            users[username]->insert(new_content);
            // Append new multimedia content to the CSV file
            appendUserContentToCSV("users_content.csv", username, new_content);
            // Prompt for content details
            cout << "Content added successfully." << endl;

        } else if (option == 2) {
            // Search for multimedia content based on bounding box
            float xmin, ymin, xmax, ymax;
            
            cout << "Enter bounding box coordinates to search (xmin ymin xmax ymax): ";
            // Prompt for content details
            cin >> xmin >> ymin >> xmax >> ymax;

            BoundingBox query_box(xmin, ymin, xmax, ymax);
            string filename = username + "_search_result.txt";
            ofstream output_file(filename);
            if (output_file) {
                users[username]->search(query_box, output_file);//searching the user
                cout << "Search results saved to '" << filename << "'." << endl;
                output_file.close();
            } else {
                cout << "Unable to open results file." << endl;
            }
// Prompt for content details
        } else if (option == 3) {
            float xmin, ymin, xmax, ymax;
            cout << "Enter bounding box coordinates to delete (xmin ymin xmax ymax): ";
            cin >> xmin >> ymin >> xmax >> ymax;
// Delete multimedia content based on bounding box
            BoundingBox delete_box(xmin, ymin, xmax, ymax);
            users[username]->deleteContent(delete_box);
            rewriteCSV("users_content.csv", users);
            cout << "Content deleted successfully." << endl;
// Exit the program
        } else if (option == 4) {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid option." << endl;
        }
    }

    // Clean up dynamically allocated trees
    for (auto& pair : users) {
        delete pair.second;
    }
    cout << "Goodbye!" << endl;

    return 0;
}
