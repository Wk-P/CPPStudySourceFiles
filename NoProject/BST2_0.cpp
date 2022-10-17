#include <iostream>
#include <queue>
using namespace std;

typedef struct TreeNode {
	int val;
	struct TreeNode* left, * right;
} TreeNode, *Tree;
typedef queue<int> IntQueue;
typedef queue<TreeNode*> NodeQueue;


TreeNode* init_node(int);
IntQueue& random_create_queue(int);
Tree* random_create_tree();
bool add_node(Tree*, int);
void create_tree(Tree*, IntQueue&, bool);
void show_queue(IntQueue&);
void show_tree_level_traverse(Tree*);

TreeNode* init_node(int val) {
	TreeNode* node = new TreeNode;
	node->val = val;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

IntQueue& random_create_queue(int size) {
	/* 默认生成（1, size)范围内的随机数据 */
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
	IntQueue que = random_create_queue(size);
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

int main() {
	Tree* BST = random_create_tree();
	show_tree_level_traverse(BST);
	return 0;
}