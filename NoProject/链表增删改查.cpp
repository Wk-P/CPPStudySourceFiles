#include <iostream>
using namespace std;
typedef struct _Student {
	char ID[20];
	char name[30];
	int score;
	struct _Student *next;
} _Student;

void print_student(_Student* student) {
	cout << "-8-8-8-8-8-8-8-" << endl;
	cout << "ID:" << student->ID << endl;
	cout << "Name:" << student->name << endl;
	cout << "Score:" << student->score << endl;
	cout << "***************" << endl;
}

void input_information(_Student *s) {
	cout << "ID:"; cin >> s->ID;
	cout << "Name:"; cin >> s->name;
	cout << "Score"; cin >> s->score;
}

// 头插法
void insert_to_head(_Student** head) {
	if (!head) { cout << "列表不存在" << endl; return; }
	_Student* insert_student = new _Student;
	input_information(insert_student);
	if (*head == NULL) {
		*head = insert_student;
		(*head)->next = NULL;
	}
	else {
		_Student* temp = (*head)->next;
		*head = insert_student;
		(*head)->next = temp;
	}
}

void search_student(_Student**head, char* name) {
	if (!head) { cout << "列表不存在" << endl; return; }
	if (!(*head)) { cout << "空列表!"; return; }
	_Student* temp = *head;
	while (!temp) {
		if (temp->name == name) {
			cout << "已找到学生:" << endl;
			print_student(temp);
		}
		temp = temp->next;
	}
	cout << "查无此人!" << endl;
}

void search_student(_Student** head, char* ID) {
	if (!head) { cout << "列表不存在" << endl; return; }
	if (!(*head)) { cout << "空列表!" << endl; return; }
	_Student* temp = *head;
	while (!temp) {
		if (temp->ID == ID) {
			cout << "已找到学生:" << endl;
			print_student(temp);
		}
		temp = temp->next;
	}
	cout << "查无此人!" << endl;
}

void search_student(_Student** head, int score) {
	if (!head) { cout << "列表不存在" << endl; return; }
	if (!(*head)) { cout << "空列表!" << endl; return; }
	_Student* temp = *head;
	while (!temp) {
		if (temp->score == score) {
			cout << "已找到学生:" << endl;
			print_student(temp);
		}
		temp = temp->next;
	}
	cout << "查无此人!" << endl;
}

_Student* search_student(_Student** head, char* name, char *ID) {
	if (!head) { cout << "列表不存在" << endl; return; }
	if (!(*head)) { cout << "空列表!" << endl; return; }
	_Student* temp = *head;
	_Student* prev = NULL;
	while (!temp) {
		if (temp->ID == ID && temp->name == name) {
			cout << "已找到学生:" << endl;
			print_student(temp);
			return prev;
		}
		prev = temp;
		temp = temp->next;
	}
	cout << "查无此人!" << endl;
	return NULL;
}

void delete_student(_Student** head) {
	char name[50], ID[20];
	cout << "输入需要删除的学生信息" << endl;
	cout << "ID:" << endl;
	cout << "Name" << endl;
	_Student *result = search_student(head, name, ID);
	if (result) {
		_Student* del_student = result->next;
		result->next = del_student->next;
		delete del_student;
		cout << "删除成功!" << endl;
	}
	return;
}
	
int main() {

}