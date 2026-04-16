// name: zeinab salami
// date: 4/16/2026
// This program implements an address book using a binary search tree (BST).

#include <iostream>
#include <string>

using namespace std;

// =======================
// TreeNode CLASS
// Represents one contact in the BST
// =======================
class TreeNode {
public:
    string name;
    string phoneNumber;
    string emailaddress;
    string homeaddress;

    TreeNode* left;
    TreeNode* right;

    // Constructor initializes a contact node
    TreeNode(string name, string phoneNumber, string emailaddress, string homeaddress)
        : name(name), phoneNumber(phoneNumber), emailaddress(emailaddress),
        homeaddress(homeaddress), left(nullptr), right(nullptr) {
    }
};

// =======================
// ADDRESS BOOK CLASS
// Manages BST operations (insert, delete, search, display)
// =======================
class AddressBook {

private:
    TreeNode* root = nullptr; // Root of BST

    // Insert a new contact into BST (sorted by name)
    TreeNode* insert(TreeNode* node, string name, string phoneNumber,
        string emailaddress, string homeaddress) {

        if (!node)
            return new TreeNode(name, phoneNumber, emailaddress, homeaddress);

        if (name < node->name)
            node->left = insert(node->left, name, phoneNumber, emailaddress, homeaddress);
        else if (name > node->name)
            node->right = insert(node->right, name, phoneNumber, emailaddress, homeaddress);

        return node;
    }

    // Find smallest node in right subtree (used in deletion)
    TreeNode* findMin(TreeNode* node) {
        while (node->left)
            node = node->left;
        return node;
    }

    // Delete a contact from BST
    TreeNode* deleteContact(TreeNode* node, string name) {
        if (!node) return node;

        if (name < node->name)
            node->left = deleteContact(node->left, name);
        else if (name > node->name)
            node->right = deleteContact(node->right, name);
        else {
            // Case 1: no left child
            if (!node->left) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2: no right child
            else if (!node->right) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: two children
            TreeNode* temp = findMin(node->right);

            node->name = temp->name;
            node->phoneNumber = temp->phoneNumber;
            node->emailaddress = temp->emailaddress;
            node->homeaddress = temp->homeaddress;

            node->right = deleteContact(node->right, temp->name);
        }
        return node;
    }

    // Search for a contact by name
    TreeNode* search(TreeNode* node, string name) {
        if (!node || node->name == name)
            return node;

        if (name < node->name)
            return search(node->left, name);

        return search(node->right, name);
    }

    // Inorder traversal (prints contacts in alphabetical order)
    void inOrderTraversal(TreeNode* node) {
        if (!node) return;

        inOrderTraversal(node->left);

        cout << "Name: " << node->name << endl;
        cout << "Phone: " << node->phoneNumber << endl;
        cout << "Email: " << node->emailaddress << endl;
        cout << "Address: " << node->homeaddress << endl;
        cout << endl;

        inOrderTraversal(node->right);
    }

    // Count total contacts in BST
    int countContacts(TreeNode* node) {
        if (!node) return 0;
        return 1 + countContacts(node->left) + countContacts(node->right);
    }

public:

    // Add contact (wrapper function)
    void addContact(string name, string phoneNumber, string emailaddress, string homeaddress) {
        root = insert(root, name, phoneNumber, emailaddress, homeaddress);
    }

    // Remove contact by name
    void remove(string name) {
        root = deleteContact(root, name);
    }

    // Find and display a contact
    void findContact(string name) {
        TreeNode* result = search(root, name);

        if (result) {
            cout << "Contact found:" << endl;
            cout << "Name: " << result->name << endl;
            cout << "Phone: " << result->phoneNumber << endl;
            cout << "Email: " << result->emailaddress << endl;
            cout << "Address: " << result->homeaddress << endl;
        }
        else {
            cout << "Contact not found." << endl;
        }
    }

    // Display all contacts in alphabetical order
    void inOrder() {
        inOrderTraversal(root);
    }

    // Return total number of contacts
    int count() {
        return countContacts(root);
    }
};

// =======================
// MAIN FUNCTION (USER INTERFACE)
// =======================
int main() {

    AddressBook addressBook;

    int choice;
    string name, phone, email, address;

    // Menu loop
    while (true) {

        cout << " ==========Address Book Menu==========" << endl;
        cout << " 1. Add Contact" << endl;
        cout << " 2. Remove Contact" << endl;
        cout << " 3. Find Contact" << endl;
        cout << " 4. Display Contacts" << endl;
        cout << " 5. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        cout << "----------------------------------------" << endl;

        switch (choice) {

        case 1:
            // Add new contact
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone number: ";
            getline(cin, phone);
            cout << "Enter email address: ";
            getline(cin, email);
            cout << "Enter home address: ";
            getline(cin, address);

            addressBook.addContact(name, phone, email, address);

            cout << "Contact added successfully." << endl;
            cout << "\nTotal number of contacts: " << addressBook.count() << endl;
            break;

        case 2:
            // Remove contact
            cout << "Enter name to remove: ";
            getline(cin, name);

            addressBook.remove(name);

            cout << "Contact removed successfully." << endl;
            cout << "\nTotal number of contacts: " << addressBook.count() << endl;
            break;

        case 3:
            // Find contact
            cout << "Enter name to find: ";
            getline(cin, name);

            addressBook.findContact(name);
            break;

        case 4:
            // Display all contacts
            cout << "-------------------" << endl;
            cout << "Contacts:" << endl;

            addressBook.inOrder();

            cout << "\nTotal number of contacts: " << addressBook.count() << endl;
            break;

        case 5:
            // Exit program
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
