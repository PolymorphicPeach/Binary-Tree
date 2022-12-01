/* Author: Matthew Peach
 * Program Status: Complete
 * 
 * Description:
 *     The program loads a Binary Search Tree with some initial values, then allows the user to interact
 *   with the tree (search, display, add, delete, and delete all). Options are displayed by mainMenu(), which
 *   returns an integer that controls the switch-statement in main().
 * 
 *      Deleting from the tree was more complicated than I thought it would be. I also declare "traversalPtr"
 *   a lot in the BinaryTree methods. Next time I may try to simply keep traversalPtr as a node pointer
 *   data member of BinaryTree and reset it to nullptr at the end of each method it's needed. 
 */
#include <iostream>
#include <vector>
#include "BinaryTree.h"
#include "BinaryTree.cpp"
#include "Node.h"
#include "Node.cpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

int mainMenu();
bool integerConvertable(string userInput);

int main(){
    bool quitProgram {false};
    vector <int> testID {6702, 1255, 1071, 2390, 1558, 7406, 7562, 3004, 4922, 8483};
    vector <string> testName {"James B W Bevis", "Romney Wordsworth", "Revis Jacara",
                              "Clegg Forbes", "Kalin Tros", "Archibald Beechcroft", 
                              "Penthor Mul", "Bartlet Finchley", "Latham Bine",
                              "Jeff Myrtlebank"};

    BinaryTree* employeeTree = new BinaryTree();
    
    for(size_t i {0}; i < testID.size(); ++i){
        employeeTree->addNode(testID[i], testName[i]);
    }
    
    cout << "NOTE: The binary tree has been populated with sample values." << endl << endl;

    while(!quitProgram){    
        switch(mainMenu()){
            
        // --- Search ---
        case 1:{
            string userInputID {"Unset"};
            cout << "Enter an employeeID to search for: ";
            getline(cin, userInputID);
            cin.clear();
            cout << endl;
            
            if(integerConvertable(userInputID)){
                int inputAsInt {0};
                inputAsInt = std::stoi(userInputID);
                if(!employeeTree->searchTree(inputAsInt)){
                    cout << "Employee not found." << endl;
                }
            }
            else{
                cout << "ERROR: Invalid employeeID search query." << endl;
            }
            
            break;
        }
        
        // --- Display Tree ---
        case 2:{
            employeeTree->displayTree();
            break;
        }
        
        // --- Add Node ---
        case 3:{
            string userInputID {"Unset"};
            cout << "Enter new employee ID: ";
            getline(cin, userInputID);
            cin.clear();
            cout << endl;
            
            if(integerConvertable(userInputID)){
                string userInput {"Unset"};
                int newID = std::stoi(userInputID);
                cout << "Enter the employee's name: ";
                getline(cin, userInput);
                cin.clear();
                cout << endl;
                
                if(!employeeTree->addNode(newID, userInput)){
                    cout << "ERROR: Employee ID: " << newID << " is already in use." << endl;
                }
            }
            else{
                cout << "ERROR: Invalid employeeID entry." << endl;
            }
            break;
        }
        
        // --- Delete Node ---
        case 4:{
            string userInputID {"Unset"};
            cout << "Enter the employee ID of the employee to remove: ";
            getline(cin, userInputID);
            cin.clear();
            cout << endl;
            
            if(integerConvertable(userInputID)){
                int deleteID = std::stoi(userInputID);
                
                if(employeeTree->deleteNode(deleteID)){
                    cout << "Employee deleted." << endl;
                }
                else{
                    cout << "No employee with ID: " << deleteID << " found." << endl;
                }
            }
            else{
                cout << "ERROR: Invalid employeeID entry." << endl;
            }
            break;
        }
        
        // --- Clear Tree ---
        case 5:{
            employeeTree->clearTree();
            cout << "All employees removed from tree." << endl;
            break;
        }
        
        // --- Quit ---
        case 6:{
            quitProgram = true;
            break;
        }
        
        default:
            cout << "ERROR: Please enter a valid selection." << endl;
        }
        
        cout << endl << endl;
    }   
    
    cout << " --- End Program --- " << endl
         << "Thanks, I feel like I learned a lot this semester!" << endl << endl;
    
    delete employeeTree;
    employeeTree = nullptr;
    
    return 0;
}

// Function: mainMenu()
//
// Parameters: N/A
//
// Returns: int
//
// Purpose:
//   This function returns an integer that controls the switch statement in main, 
// allowing the user to interact with the Binary Search Tree.

int mainMenu(){
    
    string userInputRaw {"Unset"};
    int userInput {0};
    
    cout << "=========================================================================" << endl
         << "Select one of the following options by entering the corresponding number." << endl
         << "-------------------------------------------------------------------------" << endl
         << "1.) Search employee ID." << endl
         << "2.) Display all tree contents in order." << endl
         << "3.) Add new employee." << endl
         << "4.) Remove an employee." << endl
         << "5.) Fire all employees." << endl
         << "6.) Exit program." << endl
         << "-------------------------------------------------------------------------" << endl
         << "Enter Selection: ";
    
    getline(cin, userInputRaw);
    cin.clear();
    
    cout << endl;
    
    if(userInputRaw == "1"){
        userInput = 1;
    }
    else if(userInputRaw == "2"){
        userInput = 2;
    }
    else if(userInputRaw == "3"){
        userInput = 3;
    }
    else if(userInputRaw == "4"){
        userInput = 4;
    }
    else if(userInputRaw == "5"){
        userInput = 5;
    }
    else if(userInputRaw == "6"){
        userInput = 6;
    }
    
    return userInput;
}


//                   (======= NOTE: Same function I used in Lab1 ========)
// Function: integerConvertable
//
// Parameters: std::string (User input that should, hopefully, be convertable to an int)
//
// Returns: bool (true means that std::stoi can be used on the 
//                  argument without crashing the program.
//                false means that std::stoi can crash the program
//                 if used on the argument.)
// Purpose:
//   This function uses various checks on the string parameter to see if it can be
// converted into a string without causing the program to crash. The specifics are commented
// in the function body. In summary this function makes the string: is not longer
// than an integer allows, only contains digits or a negative sign in the
// 0 index and digits.
//   If the input seems to actually be a number, it is converted into a signed long long int
//  to make sure that it's still in the range of the integer data-type.

bool integerConvertable(string userInput){
    // Valid integer range: -2147483648 to 2147483647
    
    bool validInteger {true}; // The goal is to have this remain true
        
    //=================================================================================================
    // Summary of if/else-ifs to determine if there are too many characters or if they are not numbers:
    //
    // 1.) The user didn't put in anything.
    // 2.) The user input a negative sign followed by more than 10 characters.
    // 3.) The user input more than 10 characters without the first character being a negative sign.
    // 4.) The user input a negative sign followed by less than 10 characters, 
    //     but there is one or more non-digit characters (excluding the negative sign).
    // 5.) The user input less than 10 characters, but there is one or more non-digit characters
    //=================================================================================================
        
    if(userInput.empty()){
        cout << "ERROR: Please enter something." << endl;
        validInteger = false;
    }
    else if(userInput.length() > 11 && userInput[0] == '-'){
        cout << "ERROR: Your number is too long. Please only enter integers in the range -2147483648 to 2147483647." << endl;
        validInteger = false;
    }
    else if(userInput.length() > 10){
        cout << "ERROR: Your number is too long. Please only enter integers in the range -2147483648 to 2147483647." << endl;
        validInteger = false;
    }
    else if(userInput[0] == '-'){ // If it's a negative number
        for(int i = 1; i < userInput.length(); ++i){
            if( !isdigit(userInput[i]) ){ // If a non-digit is encountered
                cout << "ERROR: " << userInput[i] << " is not a number. Please enter only digits or a \" - \" if negative." << endl;
                validInteger = false;
            }
        }
    }
    else{ // This is kind of the "standard" case: The input isn't empty, there is no negative sign
        for(int i = 0; i < userInput.length(); ++i){ // If it's a positive number
            if( !isdigit(userInput[i]) ){ // All characters must be digits
                cout << "ERROR: " << userInput[i] << " is not a number. Please enter only digits or a \" - \" if negative." << endl;
                validInteger = false;
            }
        }
    }
    //================================================================================
    // To trigger this if-statement, the entry is either a negative sign (-) followed
    // by 10 numeric characters, or just 10 numeric characters.
    //
    // The string still cannot be simply converted to an integer though.
    // -2147483649 and 2147483648 are "valid" at this point and trying to convert them
    // would result in an error. This if-statement will check for those cases.
    //================================================================================
    if(validInteger){
        // Convert the user input (string) to a long long integer
        long long userInputLL = std::stoll(userInput);
        if(userInputLL < -2147483648 || userInputLL > 2147483647){ // Make sure it's in range
            cout << "ERROR: Your entry should be between -2147483648 and 2147483647." << endl;
            validInteger = false;
        }
    }
    // Will have remain true if all checks are passed
    return validInteger; 
}