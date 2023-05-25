#include <iostream>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <chrono>
#include <string>
#include <Windows.h>
#include <fstream>

using namespace std;
using namespace chrono;
const int MAX_STUDENTS = 50;

struct Student {
    string name;
    char gender;
    int group_number;
    int list_number;
    int grades[8];
};

void create_student(Student* students, int& count) {
    if (count >= MAX_STUDENTS) {
        cout << "Maximum number of students reached." << endl;
        return;
    }
    Student new_student;
    cout << "Enter student name: ";
    getline(cin, new_student.name);
    cout << "Enter student gender (M/W): ";
    cin >> new_student.gender;
    cout << "Enter student group number: ";
    cin >> new_student.group_number;
    cout << "Enter student list number: ";
    cin >> new_student.list_number;
    cout << "Enter student grades for 3 exams and 5 differentiated credits: ";
    for (int i = 0; i < 8; i++) {
        cin >> new_student.grades[i];
    }
    students[count] = new_student;
    count++;
}

void edit_student(Student* students, int count) {
    cout << "Enter the index of the student you want to edit (0-" << count - 1 << "): ";
    int index;
    cin >> index;
    if (index < 0 || index >= count) {
        cout << "Invalid index." << endl;
        return;
    }
    cout << "Enter new student name: ";
    cin.ignore();
    getline(cin, students[index].name);
    cout << "Enter new student gender (M/W): ";
    cin >> students[index].gender;
    cout << "Enter new student group number: ";
    cin >> students[index].group_number;
    cout << "Enter new student list number: ";
    cin >> students[index].list_number;
    cout << "Enter new student grades for 3 exams and 5 differentiated credits: ";
    for (int i = 0; i < 8; i++) {
        cin >> students[index].grades[i];
    }
}

void print_students(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        cout << "Student #" << i + 1 << endl;
        cout << "Name: " << students[i].name << endl;
        cout << "Gender: " << students[i].gender << endl;
        cout << "Group number: " << students[i].group_number << endl;
        cout << "List number: " << students[i].list_number << endl;
        cout << "Grades:";
        for (int j = 0; j < 8; j++) {
            cout << " " << students[i].grades[j];
        }
        cout << endl;
    }
}

void print_students_by_group(Student* students, int numStudents, int groupNumber) {
    cout << "Students in group " << groupNumber << ":" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].group_number == groupNumber) {
            cout << "Student #" << i + 1 << ":" << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "Group number: " << students[i].group_number << endl;
            cout << "List number: " << students[i].list_number << endl;
            cout << "Grades:";
            for (int j = 0; j < 8; j++) {
                cout << " " << students[i].grades[j];
            }
            cout << endl;
        }
    }
}

float get_average_score(const Student& student) {
    float sum = 0;
    for (int i = 0; i < 8; i++) {
        sum += student.grades[i];
    }
    return sum / 8;
}

void print_average_scores(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            float score1 = get_average_score(students[i]);
            float score2 = get_average_score(students[j]);
            if (score1 < score2) {
                swap(students[i], students[j]);
            }
        }
    }
    for (int i = 0; i < count; i++) {
        float score = get_average_score(students[i]);
        cout << students[i].name << " - " << score << endl;
    }
}

void print_gender_count(Student* students, int count) {
    int man_count = 0;
    int women_count = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].gender == 'M') {
            man_count++;
        }
        else if (students[i].gender == 'W') {
            women_count++;
        }
    }
    cout << "Man students: " << man_count << endl;
    cout << "Women students: " << women_count << endl;
}

void print_students_without_scholarship(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        bool has_scholarship = true;
        bool has_low_grade = false;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] < 4) {
                has_scholarship = false;
                if (students[i].grades[j] == 3) {
                    has_low_grade = true;
                }
            }
        }
        if (has_scholarship || !has_low_grade) {
            continue;
        }
        cout << students[i].name << "(" << students[i].group_number << ")" << ", grades: ";
        for (int j = 0; j < 8; j++) {
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

void print_students_with_good_and_excellent_grades(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        bool has_bad_grade = false;
        bool has_excellent_grade = false;
        bool has_grade_3 = false;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] < 4) {
                has_bad_grade = true;
            }
            else if (students[i].grades[j] == 4) {
                has_excellent_grade = true;
            }
            else if (students[i].grades[j] == 3) {
                has_grade_3 = true;
            }
        }
        if (has_bad_grade || !has_excellent_grade || (!has_grade_3 && !has_excellent_grade)) {
            continue;
        }
        bool all_5_grades = true;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] != 5) {
                all_5_grades = false;
                break;
            }
        }
        if (all_5_grades) {
            continue;
        }
        cout << students[i].name << "(" << students[i].group_number << ")" << ", grades: ";
        for (int j = 0; j < 8; j++) {
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

void print_students_with_excellent_grades(Student* students, int count) {
    for (int i = 0; i < count; i++) {
        bool has_bad_grade = false;
        for (int j = 0; j < 8; j++) {
            if (students[i].grades[j] != 5) {
                has_bad_grade = true;
                break;
            }
        }
        if (has_bad_grade) {
            continue;
        }
        cout << students[i].name << "(" << students[i].group_number << ")" << ", grades: ";
        for (int j = 0; j < 8; j++) {
            cout << students[i].grades[j] << " ";
        }
        cout << endl;
    }
}

void print_students_by_list_number(Student* students, int numStudents, int listNumber) {
    cout << "Students in list " << listNumber << ":" << endl;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].list_number == listNumber) {
            cout << "Student #" << i + 1 << ":" << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Gender: " << students[i].gender << endl;
            cout << "Group number: " << students[i].group_number << endl;
            cout << "List number: " << students[i].list_number << endl;
            cout << "Grades:";
            for (int j = 0; j < 8; j++) {
                cout << " " << students[i].grades[j];
            }
            cout << endl;
        }
    }
}

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int data) {

    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void printList(Node* head) {
    cout << "List: " << endl;
    Node* current = head;
    while (current != NULL) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

Node* createList() {
    cout << "Enter numbers of elements: ";
    auto start_time = chrono::high_resolution_clock::now();
    int n;
    Node* head = NULL;
    Node* tail = NULL;
    cin >> n;
    cout << endl;
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int value = rand() % 100;
        Node* newNode = createNode(value);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    cout << endl;
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
    return head;
}

Node* createListFromInput() {
    auto start_time = chrono::high_resolution_clock::now();
    Node* head = NULL;
    Node* tail = NULL;
    int n = 0;
    cout << "Enter the elements of the list: " << endl;
    string line;
    getline(cin, line);
    stringstream ss(line);
    int value;
    while (ss >> value) {
        n++;
        Node* newNode = createNode(value);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
    cout << "Entered " << n << " elements." << endl;
    return head;
}

void insertNode(Node** headRef, int index, int value) {
    auto start_time = chrono::high_resolution_clock::now();
    Node* newNode = createNode(value);
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    if (index == 0) {
        newNode->next = *headRef;
        (*headRef)->prev = newNode;
        *headRef = newNode;
        return;
    }
    Node* current = *headRef;
    int i = 0;
    while (i < index && current != NULL) {
        current = current->next;
        i++;
    }
    if (current == NULL) {
        Node* tail = *headRef;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newNode;
        newNode->prev = tail;
        return;
    }
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
}

void deleteByIndex(Node** head, int index) {
    auto start_time = chrono::high_resolution_clock::now();
    if (*head == NULL) {
        return;
    }
    Node* current = *head;
    if (index == 0) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        delete current;
        return;
    }
    for (int i = 0; current != NULL && i < index - 1; i++) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        return;
    }
    Node* next = current->next->next;
    delete current->next;
    current->next = next;
    if (next != NULL) {
        next->prev = current;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
}

void deleteByValue(Node** head, int data) {
    auto start_time = chrono::high_resolution_clock::now();
    if (*head == NULL) {
        return;
    }
    Node* current = *head;
    if (current->data == data) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        delete current;
        return;
    }
    while (current != NULL && current->data != data) {
        current = current->next;
    }
    if (current == NULL) {
        return;
    }
    Node* prev = current->prev;
    Node* next = current->next;
    delete current;
    if (prev != NULL) {
        prev->next = next;
    }
    if (next != NULL) {
        next->prev = prev;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
}

void swapNodes(Node** head, int data1, int data2) {
    if (data1 == data2) {
        return;
    }
    Node* current = *head;
    Node* node1 = NULL;
    Node* node2 = NULL;
    while (current != NULL) {
        if (current->data == data1) {
            node1 = current;
        }
        else if (current->data == data2) {
            node2 = current;
        }
        current = current->next;
    }
    if (node1 == NULL || node2 == NULL) {
        return;
    }
    if (node1->prev != NULL) {
        node1->prev->next = node2;
    }
    else {
        *head = node2;
    }
    if (node2->prev != NULL) {
        node2->prev->next = node1;
    }
    else {
        *head = node1;
    }
    Node* temp = node1->prev;
    node1->prev = node2->prev;
    node2->prev = temp;
    temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
}

void swapNodesByIndex(Node** head, int index1, int index2) {
    if (index1 == index2) {
        return;
    }
    Node* current = *head;
    Node* node1 = NULL;
    Node* node2 = NULL;
    int i = 0;
    while (current != NULL) {
        if (i == index1) {
            node1 = current;
        }
        else if (i == index2) {
            node2 = current;
        }
        current = current->next;
        i++;
    }
    if (node1 == NULL || node2 == NULL) {
        return;
    }
    if (node1->prev != NULL) {
        node1->prev->next = node2;
    }
    else {
        *head = node2;
    }
    if (node2->prev != NULL) {
        node2->prev->next = node1;
    }
    else {
        *head = node1;
    }
    Node* temp = node1->prev;
    node1->prev = node2->prev;
    node2->prev = temp;
    temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
}

Node* findNodeByIndex(Node* head, int index) {
    auto start_time = chrono::high_resolution_clock::now();
    Node* current = head;
    int i = 0;
    while (current != NULL) {
        if (i == index) {
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
            cout << "Elepsed time: " << duration << " ns" << endl;
            return current;
        }
        current = current->next;
        i++;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
    return NULL;
}

int findNodeIndexByValue(Node* head, int value) {
    auto start_time = chrono::high_resolution_clock::now();
    Node* current = head;
    int index = 0;
    while (current != NULL) {
        if (current->data == value) {
            auto end_time = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
            cout << "Elepsed time: " << duration << " ns" << endl;
            return index;
        }
        current = current->next;
        index++;
    }
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();
    cout << "Elepsed time: " << duration << " ns" << endl;
    return -1;
}

struct stack {
    char data;
    stack* tail;
};

stack* push(stack* str, char c) {
    stack* next = new stack;
    next->data = c;
    next->tail = str;
    return next;
}

bool empty(stack* str) {
    if (!str) return 1;
    else return 0;
}

stack* pop(stack* str) {
    stack* prev = str->tail;
    delete str;
    str = prev;
    return str;
}

char top(stack* str) {
    return str->data;
}

struct stack_i {
    double data;
    stack_i* tail;
};

stack_i* push(stack_i* s, double num) {
    stack_i* next = new stack_i;
    next->data = num;
    next->tail = s;
    return next;
}

bool empty(stack_i* str) {
    if (!str) return 1;
    else return 0;
}

stack_i* pop(stack_i* str) {
    stack_i* prev = str->tail;
    delete str;
    str = prev;
    return str;
}

double top(stack_i* str) {
    return str->data;
}

int _switch(char c) {
    switch (c) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    default: return -1;
    }
}

void output_stack(stack* s) {
    while (!empty(s)) {
        cout << s->data << ' ';
        s = s->tail;
    }
}

bool correction(string& s) {
    stack* par = NULL;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i] == ' ' && _switch(s[i - 1]) == -1 && _switch(s[i + 1]) == -1) return 0;
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') s.erase(i, 1);
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') par = push(par, s[i]);
        else if (s[i] == ')')
            if (!empty(par)) par = pop(par);
            else return 0;
    }
    if (!empty(par)) return 0;
    for (int i = 1; i < s.length() - 1; i++) {
        if (s[i] == '(' && (_switch(s[i - 1]) == -1 || s[i - 1] == ')')) {
            s.insert(i, "*");
        }
        else if (s[i] == ')' && (_switch(s[i + 1]) == -1 || s[i + 1] == '(')) {
            s.insert(i + 1, "*");
        }
    }
    for (int i = 1; i < s.length(); i++) {
        if (s[i - 1] == '+' && s[i] == '-') s.erase(i - 1, 1);
        else if (s[i - 1] == '-' && s[i] == '-') {
            s.insert(i - 1, "+");
            s.erase(i, 2);
        }
        else if (_switch(s[i - 1]) > 0 && _switch(s[i]) > 0 && s[i] != '-') return 0;
    }
    for (int i = 0, k = 0; i < s.length(); i++) {
        if (_switch(s[i]) > 0) k++;
        if (i == 1 && s[i - 1] != '-' && _switch(s[i - 1]) > 0) return 0;
        else if (i == s.length() - 1 && _switch(s[i]) > 0 || i == s.length() - 1 && !k) return 0;
    }
    return 1;
}

string reverse_notation(string str) {
    cout << "Adjusted expression: " << str << '\n' << "Translate in OPN:\n";
    string n;
    stack* stack = NULL;
    string num = "";
    int k = 1;
    for (int i = 0, flag; i < str.length(); i++) {
        if (str[i] == '-') {
            if (i == 0 && _switch(str[i + 1]) == -1) {
                n += str[i];
                continue;
            }
            else if (_switch(str[i - 1]) > 1 && _switch(str[i + 1]) == -1) {
                n += str[i];
                continue;
            }
        }
        flag = _switch(str[i]);
        if (flag == 0) {
            if (str[i] == '(') {
                if (num != "") {
                    n += num;
                    n += ' ';
                    num = "";
                    cout << k << ". Stack: ";
                    output_stack(stack);
                    cout << "\t\toutput string: " << n << "\n";
                    k++;
                }
                stack = push(stack, str[i]);
                cout << k << ". Stack: ";
                output_stack(stack);
                cout << "\t\toutput string: " << n << "\n";
                k++;
            }
            else {
                if (num != "") {
                    n += num;
                    n += ' ';
                    num = "";
                    cout << k << ". Stack: ";
                    output_stack(stack);
                    cout << "\t\toutput string: " << n << "\n";
                    k++;
                }
                while (!empty(stack)) {
                    if (top(stack) != '(') {
                        n += top(stack);
                        stack = pop(stack);
                        n += ' ';
                    }
                    else {
                        stack = pop(stack);
                        break;
                    }
                }
                cout << k << ". Stack: ";
                output_stack(stack);
                cout << "\t\toutput string: " << n << "\n";
                k++;
            }
        }
        else if (flag == 1) {
            if (num != "") {
                n += num;
                n += ' ';
                num = "";
                cout << k << ". Stack: ";
                output_stack(stack);
                cout << "\t\toutput string: " << n << "\n";
                k++;
            }
            if (empty(stack) || _switch(top(stack)) < flag) {
                stack = push(stack, str[i]);
            }
            else {
                while (!empty(stack) && _switch(top(stack)) >= flag) {
                    n += top(stack);
                    stack = pop(stack);
                    n += ' ';
                }
                stack = push(stack, str[i]);
            }
            cout << k << ". Stack: ";
            output_stack(stack);
            cout << "\t\toutput string: " << n << "\n";
            k++;
        }
        else if (flag == 2) {
            if (num != "") {
                n += num;
                n += ' ';
                num = "";
                cout << k << ". Stack: ";
                output_stack(stack);
                cout << "\t\toutput string: " << n << "\n";
                k++;
            }
            if (empty(stack) || _switch(top(stack)) < flag) {
                stack = push(stack, str[i]);
            }
            else {
                while (!empty(stack) && _switch(top(stack)) >= flag) {
                    n += top(stack);
                    stack = pop(stack);
                    n += ' ';
                }
                stack = push(stack, str[i]);
            }
            cout << k << ". Stack: ";
            output_stack(stack);
            cout << "\t\toutput string: " << n << "\n";
            k++;
        }
        else num += str[i];
    }
    if (num != "") {
        n += num;
        n += ' ';
        cout << k << ". Stack: ";
        output_stack(stack);
        cout << "\t\toutput string: " << n << "\n";
        k++;
    }
    while (!empty(stack)) {
        n += top(stack);
        stack = pop(stack);
        n += ' ';
    }
    cout << k << ". Stack: ";
    output_stack(stack);
    cout << "\t\toutput string: " << n << "\n";
    return n;
}

double calculate(string s) {
    string num = "";
    double num_1, num_2;
    stack_i* stack = NULL;
    for (int i = 0, k = 1; i < s.length(); i++) {
        if (_switch(s[i]) == -1 && s[i] != ' ') {
            while (s[i] != ' ') {
                num += s[i];
                i++;
            }
            stack = push(stack, stoi(num));
            cout << k << ". Writing to the stack " << num << '\n';
            k++;
            num = "";
        }
        else if (_switch(s[i]) == 1) {
            if (s[i] == '+') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 + num_1);
                cout << k << ". Taking it out of the stack " << num_2 << " and " << num_1 << ", we add it up and return it to the stack " << num_1 + num_2 << '\n';
                k++;
            }
            if (s[i] == '-' && i < s.length() - 1 && s[i + 1] == ' ') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 - num_1);
                cout << k << ". Taking it out of the stack " << num_2 << " and " << num_1 << ", subtract and return to the stack " << num_2 - num_1 << '\n';
                k++;
            }
            else if (s[i] == '-' && i < s.length() - 1 && _switch(s[i + 1]) == -1) {
                while (s[i] != ' ') {
                    num += s[i];
                    i++;
                }
                stack = push(stack, stoi(num));
                cout << k << ". Writing to the stack " << num << '\n';
                k++;
                num = "";
            }
        }
        else if (_switch(s[i]) == 2) {
            if (s[i] == '*') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 * num_1);
                cout << k << ". Taking it out of the stack " << num_2 << " and " << num_1 << ", multiply and return to the stack " << num_1 * num_2 << '\n';
                k++;
            }
            if (s[i] == '/') {
                num_1 = top(stack);
                stack = pop(stack);
                num_2 = top(stack);
                stack = pop(stack);
                stack = push(stack, num_2 / num_1);
                cout << k << ". Taking it out of the stack " << num_2 << " and " << num_1 << ", divide and return to the stack " << num_2 / num_1 << '\n';
                k++;
            }
        }
    }
    cout << "Returning the top element of the stack\n";
    return top(stack);
}

int main() {
    bool d = true;
    while (d == true) {
        int task;
        cout << "Select task:\n"
            "1. First practical\n"
            "2. Second practical\n"
            "3. Third practical\n";
        cin >> task;
        if (task == 0) {
            d = false;
            break;
        }
        cout << '\n' << '\n';
        switch (task)
        {
        case 1:
        {
            Student students[MAX_STUDENTS];
            int count = 0;
            int groupNumber;
            int listNumber;
            while (true) {
                int task;
                cout << "Choose an operation:" << endl;
                cout << "1. Create new student " << endl;
                cout << "2. Edit student information" << endl;
                cout << "3. Show information" << endl;
                cout << "4. Information of group" << endl;
                cout << "5. Top student" << endl;
                cout << "6. Man and women students" << endl;
                cout << "7. Students without scholarship; good and excellent; only excellent" << endl;
                cout << "8. Students by list number" << endl;
                cout << "0. Exit" << endl;
                cin >> task;
                if (task == 0)
                {

                    break;
                }
                cout << '\n' << '\n';
                cin.ignore();
                switch (task) {
                case 1:
                    create_student(students, count);
                    break;
                case 2:
                    edit_student(students, count);
                    break;
                case 3:
                    print_students(students, count);
                    break;
                case 4:
                    cout << "Enter group number: ";
                    cin >> groupNumber;
                    print_students_by_group(students, count, groupNumber);
                    break;
                case 5:
                    cout << "Top students:" << endl;
                    print_average_scores(students, count);
                    break;
                case 6:
                    print_gender_count(students, count);
                    break;
                case 7:
                    cout << "Without scholarship:" << endl;
                    print_students_without_scholarship(students, count);
                    cout << endl;
                    cout << "Good and excellent:" << endl;
                    print_students_with_good_and_excellent_grades(students, count);
                    cout << endl;
                    cout << "Only excellent:" << endl;
                    print_students_with_excellent_grades(students, count);
                    cout << endl;
                    break;
                case 8:
                    cout << "Enter list number: ";
                    cin >> listNumber;
                    print_students_by_list_number(students, count, listNumber);
                    break;
                case 0: {
                    d = false;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 2:
        {
            Node* head = NULL;
            Node* list = NULL;
            Node* foundNode = nullptr;
            Node* currentNode = head;
            while (true) {
                int task;
                cout << "Choose an operation:" << endl;
                cout << "1. Create a list " << endl;
                cout << "2. Insert of element " << endl;
                cout << "3. Delete of element " << endl;
                cout << "4. Exchange of element " << endl;
                cout << "5. Receiving of element " << endl;
                cout << "0. Exit " << endl;
                cin >> task;
                if (task == 0)
                {

                    break;
                }
                cout << '\n' << '\n';
                cin.ignore();
                switch (task) {
                case 1:
                    while (true) {
                        int task1;
                        cout << "Choose a method: " << endl;
                        cout << "1. Random " << endl;
                        cout << "2. By you " << endl;
                        cout << "0. Back to main menu" << endl;
                        cin >> task1;
                        cin.ignore();
                        switch (task1) {
                        case 1:
                            list = createList();
                            printList(list);
                            break;
                        case 2:
                            list = createListFromInput();
                            printList(list);
                            break;
                        case 0:
                            break;
                        default:
                            break;
                        }
                        if (task1 == 0) {
                            break;
                        }
                    }
                    break;
                case 2:
                    int index, value;
                    cout << "Enter index to insert: ";
                    cin >> index;
                    cout << "Enter value to insert: ";
                    cin >> value;
                    insertNode(&list, index, value);
                    printList(list);
                    break;
                case 3:
                    while (true) {
                        int task2;
                        cout << "Choose a method: " << endl;
                        cout << "1. By index " << endl;
                        cout << "2. By value " << endl;
                        cout << "0. Back to main menu" << endl;
                        cin >> task2;
                        cin.ignore();
                        switch (task2) {
                        case 1:
                            int index;
                            cout << "Enter the index of the element to be deleted: ";
                            cin >> index;
                            deleteByIndex(&list, index);
                            printList(list);
                            break;
                        case 2:
                            int value;
                            cout << "Enter the value of the element to be deleted: ";
                            cin >> value;
                            deleteByValue(&list, value);
                            printList(list);
                            break;
                        case 0:
                            break;
                        default:
                            break;
                        }
                        if (task2 == 0) {
                            break;
                        }
                    }
                    break;
                case 4:
                    while (true) {
                        int task3;
                        cout << "Choose a method: " << endl;
                        cout << "1. By value " << endl;
                        cout << "2. By index " << endl;
                        cout << "0. Back to main menu" << endl;
                        cin >> task3;
                        cin.ignore();
                        switch (task3) {
                        case 1:
                            int data1, data2;
                            cout << "Enter the values of the nodes to be swapped: ";
                            cin >> data1 >> data2;
                            swapNodes(&list, data1, data2);
                            printList(list);
                            break;
                        case 2:
                            int index1, index2;
                            cout << "Enter index of the nodes to be swapped: ";
                            cin >> index1 >> index2;
                            swapNodesByIndex(&list, index1, index2);
                            printList(list);
                            break;
                        case 0:
                            break;
                        default:
                            break;
                        }
                        if (task3 == 0) {
                            break;
                        }
                    }
                    break;
                case 5:
                    int task5;
                    cout << "Choose a method: " << endl;
                    cout << "1. Find element by index" << endl;
                    cout << "2. Find element by value" << endl;
                    cout << "0. Back to main menu" << endl;
                    cin >> task5;
                    cin.ignore();
                    if (task5 == 1) {
                        int index;
                        cout << "Enter the index of the element: ";
                        cin >> index;
                        foundNode = findNodeByIndex(list, index);
                        if (foundNode != NULL) {
                            cout << "Found node: " << foundNode->data << endl;
                        }
                    }
                    else if (task5 == 2) {
                        int value;
                        cout << "Enter the value of the element: ";
                        cin >> value;
                        int index = findNodeIndexByValue(list, value);
                        if (index != -1) {
                            cout << "Node found at index: " << index << endl;
                        }
                    }
                    else {
                        break;
                    }
                    break;
                case 0: {
                    d = false;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }
        case 3:
        {
            string str, str_out;
            while (true) {
                int key;
                cout << "Choose operation:" << endl;
                cout << "1. OPN " << endl;
                cout << "0. Exit " << endl;
                cin >> key;
                if (key == 0)
                {

                    break;
                }
                cout << '\n' << '\n';
                
                switch (key) {
                case 1:cin.ignore();
                    cout << "Enter the expression: ";
                    getline(cin, str);
                    while (str == "" || !correction(str)) {
                        cout << "Invalid input\n\nEnter the expression: ";
                        getline(cin, str);
                    }
                    str_out = reverse_notation(str);
                    cout << "Reverse polish notation: " << str_out << '\n';
                    cout << "Calculations: \n";
                    cout << "Answer: " << calculate(str_out) << "\n\n";
                    break;
                case 0: {
                    d = false;
                }
                default:
                {
                    break;
                }
                }
            }
            break;
        }


        }
    }
}
    

