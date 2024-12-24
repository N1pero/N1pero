#include <iostream>
#include <limits>
#include <algorithm>
#include "Group.h"
#include "Exceptions.h"
#include "TextProcessor.h"


using namespace std;

void createGroup(Group**& groups, int& groupCount, int& groupCapacity);
void deleteGroup(Group**& groups, int& groupCount);
void addStudentToGroup(Group** groups, int groupCount);
void editGroup(Group** groups, int groupCount);
void editStudentInGroup(Group** groups, int groupCount);
void deleteStudentFromGroup(Group** groups, int groupCount);
void addGroupAtPosition(Group**& groups, int& groupCount, int& groupCapacity);
void addStudentAtPosition(Group** groups, int groupCount);
void showGroups(Group** groups, int groupCount);
void showHighAchievers(Group** groups, int groupCount);

int main() {
    setlocale(LC_ALL, "Rus");

    int groupCapacity = 2;
    int groupCount = 0;
    Group** groups = new Group * [groupCapacity];
    TextProcessor processor;
    const char* inputFile = "Text.txt";

    while (true) {
        cout << "Main menu:\n";
        cout << "1. Task 1: Work with groups and students\n";
        cout << "2. Task 2: Processing text from a file\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            cout << "Exit program.\n";
            break;
        }
        else if (choice == 1) {
            while (true) {
                cout << "Task menu 1:\n";
                cout << "1. Create a group\n";
                cout << "2. Delete a group\n";
                cout << "3. Add a student to a group\n";
                cout << "4. Edit a group\n";
                cout << "5. Edit a student in a group\n";
                cout << "6. Remove a student from a group\n";
                cout << "7. Add a student to a specific position in a group\n";
                cout << "8. Show all groups\n";
                cout << "9. Show students with score > 4.0\n";
                cout << "0. Back to main menu\n";
                cout << "Your choice: ";
                int subChoice;
                cin >> subChoice;
                cin.ignore();

                if (subChoice == 0) {
                    break;
                }

                try {
                    switch (subChoice) {
                    case 1:
                        createGroup(groups, groupCount, groupCapacity);
                        break;
                    case 2:
                        deleteGroup(groups, groupCount);
                        break;
                    case 3:
                        addStudentToGroup(groups, groupCount);
                        break;
                    case 4:
                        editGroup(groups, groupCount);
                        break;
                    case 5:
                        editStudentInGroup(groups, groupCount);
                        break;
                    case 6:
                        deleteStudentFromGroup(groups, groupCount);
                        break;
                    case 7:
                        addStudentAtPosition(groups, groupCount);
                        break;
                    case 8:
                        showGroups(groups, groupCount);
                        break;
                    case 9:
                        showHighAchievers(groups, groupCount);
                        break;
                    default:
                        cout << "Error: invalid selection.\n";
                    }
                }
                catch (const exception& e) {
                    cout << "Error: " << e.what() << "\n";
                }
            }
        }
        else if (choice == 2) {
            while (true) {
                cout << "\nMenu:\n";
                cout << "1. Output text from file\n";
                cout << "2. Output text with word order changed\n";
                cout << "0. Exit\n";
                cout << "Choose an action: ";
                int subChoice; cin >> subChoice;

                if (subChoice == 0) {
                    cout << "Return to main menu.\n";
                    break;
                }

                switch (subChoice) {
                case 1:
                    processor.display(inputFile);
                    break;
                case 2:
                    processor.processFile(inputFile);
                    break;
                default:
                    cout << "Incorrect input. Try again.\n";
                }
            }
        }
    }

    for (int i = 0; i < groupCount; ++i) {
        delete groups[i];
    }
    delete[] groups;

    return 0;
}
void createGroup(Group**& groups, int& groupCount, int& groupCapacity) {
    if (groupCount == groupCapacity) {
        groupCapacity *= 2;
        Group** newGroups = new Group * [groupCapacity];
        for (int i = 0; i < groupCount; ++i) {
            newGroups[i] = groups[i];
        }
        delete[] groups;
        groups = newGroups;
    }
    int groupNumber;
    cout << "Enter group number: ";
    cin >> groupNumber;


    groups[groupCount++] = new Group(groupNumber);
    cout << "Group created successfully.\n";

    // Sort groups by ascending group number
    sort(groups, groups + groupCount, [](Group* a, Group* b)
        { return a->getGroupNumber() < b->getGroupNumber();
        });
    cout << " Groups are sorted by number ascending.\n";
}
void deleteGroup(Group**& groups, int& groupCount) {
    if (groupCount == 0) {
        throw GroupException("Group list is empty. There is nothing to delete.");
    }

    cout << "Enter the group number to delete: ";
    int groupNumber;
    cin >> groupNumber;

    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            delete groups[i];
            for (int j = i; j < groupCount - 1; ++j) {
                groups[j] = groups[j + 1];
            }
            --groupCount;
            cout << "Group successfully deleted.\n";

            return;
        }
    }

    throw GroupException("Group with the specified number was not found.");
}

void addStudentToGroup(Group** groups, int groupCount) {

    if (groupCount == 0) {
        cout << "The group list is empty. First create a group.\n ";
        return;
    }

    cout << "Enter the group number where you want to add the student: ";
    int groupNumber;
    cin >> groupNumber;

    if (cin.fail()) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
        cout << "Error: Invalid group number input.\n";
        return;
    }

    cin.ignore(); // Clear the remaining newline character

    // Search for a group by number
    Group* targetGroup = nullptr;
    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            targetGroup = groups[i];
            break;
        }
    }
    if (!targetGroup) {

        cout << " Group with the specified number was not found.\n";
        return;
    }
    // Create a new student
    Student* newStudent = new Student();
    try {
        cout << "Enter student data:\n";
        cin >> *newStudent; // Use the overloaded input operator
        targetGroup->addStudent(newStudent); // Add a student to the group
    }
    catch (const exception& e) {
        delete newStudent; // Delete the object if an error occurred
        cout << "Error: " << e.what() << "\n";
    }
}
// Edit group
void editGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        throw GroupException("Group list is empty. There is nothing to edit.");
    }

    cout << "Enter the group number to edit: ";
    int groupNumber;
    cin >> groupNumber;

    for (int i = 0; i < groupCount; ++i) {

        if (groups[i]->getGroupNumber() == groupNumber) {
            cout << "Enter new number for group #" << groupNumber << ": ";
            int newNumber;
            cin >> newNumber;
            groups[i]->setGroupNumber(newNumber);
            // Sort groups by ascending group number
            sort(groups, groups + groupCount, [](Group* a, Group* b) {
                return a->getGroupNumber() < b->getGroupNumber();
                });
            cout << "Group number successfully changed and groups sorted.\n";
            return;
        }
    }
    throw GroupException("Group with specified number not found.");
}
// Edit student in group
void editStudentInGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty. Create a group first.\n";
        return;
    }

    cout << "Enter group number: ";
    int groupNumber;

    cin >> groupNumber;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Incorrect group number input.\n"; return;
    }
    // Find a group
    Group* targetGroup = nullptr;
    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            targetGroup = groups[i];
            break;
        }
    }

    if (!targetGroup) {
        cout << "Group with the specified number was not found.\n";
        return;
    }

    cout << "Enter a student number to edit: ";
    int studentIndex;
    cin >> studentIndex;

    if (cin.fail()) {

        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Incorrect student number entered.\n";
        return;
    }

    // Make sure the index is in the allowed range
    if (studentIndex <= 0 || studentIndex > targetGroup->getStudentCount()) {
        cout << "Error: Invalid student number.\n";
        return;
    }

    Student* studentToEdit = targetGroup->getStudent(studentIndex - 1); if (!studentToEdit) {
        cout << "Error: Student not found.\n";
        return;
    }

    cout << "Editing student:\n";
    cin.ignore(); // Discard the newline character left after entering
    try {
        cin >> *studentToEdit; // Entering data for a student via the overloaded operator >>
        cout << "Student edited successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error editing student: " << e.what() << "\n";
    }
}

// Delete student from group
void deleteStudentFromGroup(Group** groups, int groupCount) {
    if (groupCount == 0) {
        throw GroupException("Group list is empty. Nothing to delete.");
    }

    cout << "Enter group number: ";
    int groupNumber;
    cin >> groupNumber;

    for (int i = 0; i < groupCount; ++i) {
        if (groups[i]->getGroupNumber() == groupNumber) {
            cout << "Enter student number to delete: ";
            int studentIndex;
            cin >> studentIndex;

            groups[i]->removeStudent(studentIndex - 1);
            cout << "Student successfully removed from group #" << groupNumber << ".\n";
            return;
        }
    }

    throw GroupException("Group with the specified number was not found.");
}

void addGroupAtPosition(Group**& groups, int& groupCount, int& groupCapacity) {
    if (groupCount == groupCapacity) {

        groupCapacity *= 2;
        Group** newGroups = new Group * [groupCapacity];
        for (int i = 0; i < groupCount; ++i) {
            newGroups[i] = groups[i];
        }
        delete[] groups;
        groups = newGroups;
    }

    int position, groupNumber;
    cout << "Enter position for new group (1-" << groupCount + 1 << "): ";
    cin >> position;

    if (position < 1 || position > groupCount + 1) {
        throw InputException("Invalid position.");
    }

    cout << "Enter new group number: ";
    cin >> groupNumber;

    for (int i = groupCount; i >= position; --i) {
        groups[i] = groups[i - 1];
    }

    groups[position - 1] = new Group(groupNumber);
    ++groupCount;
    // Sort groups by ascending group number

    sort(groups, groups + groupCount, [](Group* a, Group* b) {
        return a->getGroupNumber() < b->getGroupNumber();
        });
    cout << "Group successfully added and groups sorted by ascending number.\n";
}

// Add student to specific position in group
void addStudentAtPosition(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty. Create group first.\n";
        return;
    }

    try {
        cout << "Enter group number: ";
        int groupNumber;
        cin >> groupNumber;

        if (cin.fail()) {
            throw InputException("Input error! Incorrect group number.");
        }

        // Find a group
        Group* targetGroup = nullptr;
        for (int i = 0; i < groupCount; ++i) {
            if (groups[i]->getGroupNumber() == groupNumber) {
                targetGroup = groups[i];
                break;

            }
        }

        if (!targetGroup) {
            throw GroupException("Group with the specified number was not found.");
        }

        cout << "Enter a position for a new student (1-" << targetGroup->getStudentCount() + 1 << "):";
        int position;
        cin >> position;

        if (cin.fail() || position < 1 || position > targetGroup->getStudentCount() + 1) {
            throw InputException("Input error! Invalid position for adding a student.");
        }

        Student* newStudent = new Student(); // Create a new student
        cout << "Enter student details:\n";
        cin.ignore(); // Clear remaining newline
        cin >> *newStudent; // Overloaded student input operator

        try {
            targetGroup->addStudentAtPosition(newStudent, position - 1); // Call method
            cout << "Student successfully added at position " << position << " in group #" << groupNumber << ".\n";
        }
        catch (const exception& e) {
            delete newStudent; // Delete object if error occurred throw; // Rethrow exception upstream

        }
    }
    catch (const InputException& e) {
        cout << "Input error: " << e.what() << "\n";
        cin.clear(); // Reset stream state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    }
    catch (const GroupException& e) {
        cout << "Error with group: " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

// Show groups
void showGroups(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "The group list is empty.\n";
        return;
    }

    for (int i = 0; i < groupCount; ++i) {
        groups[i]->showStudents();
        cout << " \n";
    }
}

// Show students with score greater than 4.0
void showHighAchievers(Group** groups, int groupCount) {
    if (groupCount == 0) {
        cout << "Group list is empty.\n";
        return;
    }

    for (int i = 0; i < groupCount; ++i) {
        Group* group = groups[i];
        cout << "Group #" << group->getGroupNumber() << ":\n";

        bool found = false; // Flag to check students with score > 4.0
        for (int j = 0; j < group->getStudentCount(); ++j) {
            Student* student = group->getStudent(j);
            if (student->getAverageGrade() > 4.0) {
                cout << " Student #" << (j + 1) << ": " // Print student number
                    << student->getSurname()
                    << ", Average grade: " << student->getAverageGrade() << "\n"; found = true;
            }
        }

        if (!found) {
            cout << " No students with average grade greater than 4.0.\n";
        }

        cout << " \n";
    }

}


