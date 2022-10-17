#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/* 使用栈迭代中序访问树 */

// 套用BST代码建树
typedef struct TreeNode {
	int val;
	struct TreeNode* left, *right;
}TreeNode, *Tree;
typedef queue<TreeNode*> NodeQueue;
typedef queue<int> IntQueue;
typedef stack<TreeNode*> NodeStack;

TreeNode* init_node(int);
IntQueue& random_create_queue(int, bool);
Tree* random_create_tree();
bool add_node(Tree*, int);
void create_tree(Tree*, IntQueue&, bool);
void show_queue(IntQueue&);
void show_tree_level_traverse(Tree*);
void for_tree_in_order(Tree*);

TreeNode* init_node(int val) {
	TreeNode* node = new TreeNode;
	node->val = val;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

IntQueue& random_create_queue(int size, bool reset) {
	/* 默认生成（1, size)范围内的随机数据 */
	if (reset) srand(time(NULL));
	IntQueue* que = new IntQueue;
	for (int i = 0; i < size; i++) {
		que->push(rand() % size + 1);
	}
	return *que;
}

Tree* random_create_tree() {
	Tree* T = new Tree;
	*T = NULL;
	int size = 0; cout << "Enter size of tree : "; cin >> size;
	IntQueue que = random_create_queue(size, 1);
	//show_queue(que);
	create_tree(T, que, true);
	return T;
}

bool add_node(Tree* T, int val) {
	if (!*T) {
		*T = init_node(val); return true;
	}
	TreeNode* node = *T;
	while (node) {
		if (node->val == val) return false;
		if (node->val > val) {
			if (node->left) node = node->left;
			else { node->left = init_node(val); return true; }
		}
		else {
			if (node->right) node = node->right;
			else { node->right = init_node(val); return true; }
		}
	}
	return false;
}

void create_tree(Tree* T, IntQueue& que, bool display) {
	while (!que.empty()) {
		if (add_node(T, que.front()) && display) {
			cout << que.front() << " added successfully!\n";
		}
		else if (display) {
			cout << que.front() << " failed to add!\n";
		}
		que.pop();
	}
}

void show_queue(IntQueue& que) {
	for (int i = 0; i < que.size(); i++) {
		cout << que.front() << " ";
		que.pop();
	}
}

void show_tree_level_traverse(Tree* T) {
	NodeQueue que;
	if (!T) { cout << "Empty!\n"; return; }
	que.push(*T);
	while (!
		que.empty()) {
		cout << que.front()->val << " ";
		if (que.front()->left) que.push(que.front()->left);
		if (que.front()->right) que.push(que.front()->right);
		que.pop();
	}
}

void for_tree_preorder(Tree* T) {
	if (!T) { cout << "Tree is empty!\n"; return; }
	if (!*T) { cout << "Tree is empty!\n"; return; }
	NodeStack _Stack;
	_Stack.push(*T);
	while (!_Stack.empty()) {
		TreeNode* node = _Stack.top();
		cout << node->val << " ";
		if (node->left || node->right) {
			_Stack.pop();
			if (node->right) { _Stack.push(node->right); };
			if (node->left) { _Stack.push(node->left); };
		}
		else {
			_Stack.pop();
		}
	}
}

void for_tree_inorder(Tree* T) {
	if (!T) { cout << "Tree is empty!\n"; return; }
	if (!*T) { cout << "Tree is empty!\n"; return; }
	NodeStack _Stack;
	_Stack.push(*T);
	while (!_Stack.empty()) {
		TreeNode* node = _Stack.top();
		// 入栈
		if (node->left || node->right) {
			if (node->left) {
				_Stack.push(node->left);
				node = _Stack.top();
			}
			else {
				cout << node->val << " ";
				_Stack.pop();
				_Stack.push(node->right);
			}
		}
		else {
			while (!node->right) {
				cout << node->val << " ";
				_Stack.pop();
				if (!_Stack.empty()) node = _Stack.top();
				else return;
			}
			cout << node->val << " ";
			_Stack.pop();
			_Stack.push(node->right);
		}
	}
}

int main() {
	Tree* BST = random_create_tree();
	for_tree_inorder(BST);
	//for_tree_preorder(BST);
	return 0;
}
