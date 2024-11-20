#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class for tasks
class Task {
protected:
    int id;
    string description;
    bool completed;

public:
    Task(int id, string description) : id(id), description(description), completed(false) {}

    virtual void display() {
        cout << "ID: " << id << " | Description: " << description
             << " | Status: " << (completed ? "Completed" : "Pending") << endl;
    }

    void markComplete() {
        completed = true;
    }

    int getId() const {
        return id;
    }

    virtual ~Task() {}
};

// Derived class for high-priority tasks
class HighPriorityTask : public Task {
private:
    string deadline;

public:
    HighPriorityTask(int id, string description, string deadline)
        : Task(id, description), deadline(deadline) {}

    void display() override {
        cout << "ID: " << id << " | Description: " << description
             << " | Status: " << (completed ? "Completed" : "Pending")
             << " | Deadline: " << deadline << endl;
    }
};

// Class to manage the To-Do List
class ToDoList {
private:
    vector<Task*> tasks;
    int taskCounter;

public:
    ToDoList() : taskCounter(0) {}

    void addTask(const string& description, const string& deadline = "") {
        if (deadline.empty()) {
            tasks.push_back(new Task(++taskCounter, description));
        } else {
            tasks.push_back(new HighPriorityTask(++taskCounter, description, deadline));
        }
    }

    void markTaskComplete(int id) {
        for (auto& task : tasks) {
            if (task->getId() == id) {
                task->markComplete();
                cout << "Task " << id << " marked as completed." << endl;
                return;
            }
        }
        cout << "Task with ID " << id << " not found." << endl;
    }

    void displayTasks() {
        if (tasks.empty()) {
            cout << "No tasks available!" << endl;
            return;
        }
        cout << "To-Do List:\n";
        for (auto& task : tasks) {
            task->display();
        }
    }

    ~ToDoList() {
        for (auto& task : tasks) {
            delete task;
        }
    }
};

// Main function
int main() {
    ToDoList toDoList;
    int choice;

    do {
        cout << "\n==== To-Do List Menu ====\n";
        cout << "1. Add Task\n";
        cout << "2. Add High-Priority Task\n";
        cout << "3. Mark Task Complete\n";
        cout << "4. Display Tasks\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cin.ignore(); // To clear the input buffer
            string description;
            cout << "Enter task description: ";
            getline(cin, description);
            toDoList.addTask(description);
            break;
        }
        case 2: {
            cin.ignore();
            string description, deadline;
            cout << "Enter task description: ";
            getline(cin, description);
            cout << "Enter deadline: ";
            getline(cin, deadline);
            toDoList.addTask(description, deadline);
            break;
        }
        case 3: {
            int id;
            cout << "Enter task ID to mark as complete: ";
            cin >> id;
            toDoList.markTaskComplete(id);
            break;
        }
        case 4:
            toDoList.displayTasks();
            break;
        case 5:
            cout << "Exiting To-Do List application." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
