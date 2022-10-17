#include <iostream>
using namespace std;

// 双向链表简单实现
typedef struct ListNode {
	int val;
	struct ListNode* prev, * next;
} ListNode;

ListNode* create_list_node(ListNode* _prev, ListNode* _next) {
	ListNode* node = new ListNode;
	node->prev = _prev;
	node->next = _next;
	_prev->next = node;
	_next->prev = node;
	cout << "Enter value : "; cin >> node->val;
	return node;
}

ListNode* create_list() {
	ListNode* list = new ListNode;
	int input = 0;
	cout << "Head node >> ";
	cout << "Enter value : "; cin >> list->val;
	list->next = list;
	list->prev = list;
	cout << "Enter node 1.yes, 0.no :"; cin >> input;
	ListNode* prev = list, *next = list;
	while (input) {
		ListNode* new_node = create_list_node(prev, next);
		cout << "Enter node 1.yes, 0.no :"; cin >> input;
		prev = new_node;
	}
	return list;
}

void output_list_orderly(ListNode* head) {
	ListNode* temp = head;
	while (temp->next != head) {
		cout << temp->val << " -> ";
		temp = temp->next;
	}
	cout << temp->val << endl;
}

void output_list_in_reverse_order(ListNode* head) {
	ListNode* temp = head->prev;
	while (temp != head) {
		cout << temp->val << " <- ";
		temp = temp->prev;
	}
	cout << temp->val << endl;
}

ListNode* add_one_node_at_last(ListNode* head) {
	cout << "Add one node at last >> ";
	return create_list_node(head->prev, head);
}

ListNode* add_one_node_at_first(ListNode* head) {
	cout << "Add one node at first >> ";
	return create_list_node(head->prev, head);
}

int main() {
	ListNode* list = create_list();
	output_list_orderly(list);
	output_list_in_reverse_order(list);

	add_one_node_at_last(list);
	output_list_orderly(list);
	output_list_in_reverse_order(list);

	list = add_one_node_at_first(list);

	output_list_orderly(list);
	output_list_in_reverse_order(list);
	return 0;
}