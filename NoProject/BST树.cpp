#include <iostream>

using namespace std;

#define MAX_LENGTH 100

typedef int ElementType;
typedef struct BinTreeNode{
	ElementType data;
	struct BinTreeNode* left, * right, *parent;
}TNode, *Tree;

typedef struct Queue {
	TNode **data_queue;
	int size;
	int max_length;
} TQueue;

void print_array(ElementType*, int);
bool add_node(TNode*,TNode*, ElementType);
bool add_node(Tree*, ElementType);
TNode* create_TNode(TNode*, ElementType);
void create_BST(Tree* T, ElementType* arr, int size);
void InOrder_visit_node(TNode* node);
void InOrderTraverse(Tree* T);
void levelTraverse(Tree* T);
void qpush(TQueue*, TNode*);
TNode* qpop(TQueue*);
ostream& operator<<(ostream& os, TNode* node);

TQueue* create_Queue() {
	TQueue* Tq = new TQueue;
	Tq->max_length = MAX_LENGTH;
	Tq->data_queue = new TNode*[Tq->max_length];
	Tq->size = 0;
	return Tq;
}

void qpush(TQueue* Tq, TNode* node) {
	if (Tq->size >= Tq->max_length) exit(1);
	else {
		Tq->data_queue[Tq->size] = node;
		Tq->size++;
	}
}

TNode* qpop(TQueue* Tq) {
	TNode* ret = Tq->data_queue[0];
	for (int i = 1; i < Tq->size; i++) {
		Tq->data_queue[i - 1] = Tq->data_queue[i];
	}
	Tq->size--;
	return ret;
}

void print_array(ElementType* arr, int size) {
	cout << " { ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << "}" << endl;
}

bool add_node(TNode *node, TNode* _parent, ElementType data) {
	if (!node) return false;
	if (node->data == data) return false;
	if (data < node->data) {
		if (!node->left) {
			node->left = create_TNode(node, data);
			node->left->parent = node;
			return true;
		}
		if (add_node(node->left, node, data)) return true;
	}
	if (data > node->data) {
		if (!node->right) {
			node->right = create_TNode(node, data);
			node->right->parent = node;
			return true;
		}
		if (add_node(node->right, node, data)) return true;
	}
	return false;
}

bool add_node(Tree *tree, ElementType data) {
	if (!*tree) { *tree = create_TNode(*tree, data); return true; }
	return add_node(*tree, *tree, data);
}

TNode* create_TNode(TNode* _parent, ElementType input) {
	TNode* node = new TNode;
	node->parent = _parent;
	node->data = input;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void create_BST(Tree* T, ElementType *arr, int size) {
	for (int i = 1; i < size; i++) {
		add_node(*T, *T, arr[i]);
		cout << arr[i] << " has been added!" << endl;
	}
}

// 中序遍历
void InOrder_visit_node(TNode *node) {
	//cout << "Root " << node->data << endl;
	cout << "{ ";
	if (node->left) {
		//cout << node->data << " left start" << endl;
		InOrder_visit_node(node->left);
		//cout << node->data << " left finished" << endl;
	}
	cout << node << " ";
	if (node->right) {
		//cout << node->data << " right start" << endl;
		InOrder_visit_node(node->right);
		//cout << node->data << " right finished" << endl;
	}
	cout << "} ";
}

void InOrderTraverse(Tree* T) {
	if (!*T) return;
	InOrder_visit_node(*T);
	cout << endl;
}

void levelNodeVisit(TNode* node, TQueue* Tq) {
	if (!node) return;
	qpush(Tq, node);
	while (Tq->size != 0) {
		cout << qpop(Tq) << " ";
		if (node->left) { qpush(Tq, node->left); }
		if (node->right) { qpush(Tq, node->right); }
		node = Tq->data_queue[0];
	}
	cout << endl;
}

void levelTraverse(Tree* T) {
	TQueue* Tq = create_Queue();
	levelNodeVisit(*T, Tq);
}

bool find(Tree* T, ElementType target) {
	TNode* node = *T;
	while (node) {
		if (target == node->data) return true;
		else {
			if (target < node->data) node = node->left;
			else node = node->right;
		}
	}
	return false;
}

ostream& operator<<(ostream& os, TNode* node) {
	os << node->data;
	return os;
}

void show_choose() {
	cout << "1.Insert\n2.In Order Traverse\n3.Level Traverse\n4.Find\n5.Quit\nEnter Code:";
}

void insert_array(Tree* T,ElementType* arr, int size, int test) {
	for (int i = 0; i < size; i++) {
		if (test) {
			if (add_node(T, arr[i])) cout << ">>" << arr[i] << " add Finished!\n";
			else { cout << ">> Input Error!\n"; size--; }
		}
		else { if (!add_node(T, arr[i])) { size--; } }
	}
}

int node_size(TNode* node, int *count) {
	if (!node) return 0;
	if (node->left) {
		*count = 1 + node_size(node->left, count);
	}
	if (node->right) {
		*count = 1 + node_size(node->right, count);
	}
	return *count;
}

int get_tree_size(Tree* T) {
	int *count = new int;
	*count = 1;
	int result = node_size(*T, count);
	return result;
}

int node_height(TNode* node, int *count) {
	if (!node) return 0;
	return *count + max(node_height(node->left, count), node_height(node->right, count));
}

int get_tree_height(Tree* T) {
	int result = 1;
	return node_height(*T, &result);
}

int main() {
	// 建立BST
	Tree* tree = new Tree;
	*tree = NULL;
	int ElementArrSize = 100000;
	ElementType* arr = new ElementType[ElementArrSize];
	/*while(1) {
		int input = 0;
		show_choose();
		cin >> input;
		if (input == 1) {
			int n = 0;
			cout << "Insert Number of Elements:"; cin >> n;
			while (n--) {
				cout << "Enter Element:"; cin >> input;
				if (add_node(tree, input)) cout << input << " was added!\n";
				else {
					cout << input << " has been added!\n";
				}
			}
		}
		else if (input == 2) {
			InOrderTraverse(tree);
		}
		else if (input == 3) {
			levelTraverse(tree);
		}
		else if (input == 4) {
			cout << "Enter Data to Find:"; cin >> input;
			if (find(tree, input)) cout << "\n>> Found!\n";
			else cout << "\n>> Not in Tree!\n";
		}
		else if (input == 5) {
			cout << "Quit!\n";
			return 0;
		}
		else cout << "Check Out Code Entered!\n";
		cout << "-----------\n\n";
	}*/
	srand(time(NULL));
	for (int i = 0; i < ElementArrSize; i++) {
		arr[i] = rand() % 100000 + 1;
	}
	insert_array(tree, arr, ElementArrSize, 0);
	//int tree_size = get_tree_size(tree);
	int tree_height = get_tree_height(tree);
	//InOrderTraverse(tree);
	cout << "Tree Height:" << tree_height << endl;
	return 0;
}