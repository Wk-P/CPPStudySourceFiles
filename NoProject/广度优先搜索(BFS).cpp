/*
* 对于二叉树广度优先搜索
* 实际就是层序遍历
* 借用队列实现
*/
#include <queue>
#include <iostream>
using namespace std;

typedef struct TreeNode{
	int val;
	struct TreeNode* left, * right;
} TreeNode, *Tree;

TreeNode* createTreeNode() {
	int val; cin >> val;
	if (!val) return NULL;
	TreeNode* node = new TreeNode;
	node->val = val;
	node->left = createTreeNode();
	node->right = createTreeNode();
	return node;
}

Tree* createTree() {
	Tree* tree = new Tree;
	*tree = createTreeNode();
	return tree;
}

void levelTraverse(Tree* tree) {
	queue<TreeNode*> NodeQ;
	NodeQ.push(*tree);
	while (!NodeQ.empty()) {
		cout << NodeQ.front()->val << " ";
		if (NodeQ.front()->left) NodeQ.push(NodeQ.front()->left);
		else cout << "X" << " ";
		if (NodeQ.front()->right) NodeQ.push(NodeQ.front()->right);
		else cout << "X" << " ";
		NodeQ.pop();
	}
}

string levelTraverse2(Tree* tree) {
	string ret = "";
	queue<TreeNode*> NodeQ;
	NodeQ.push(*tree);
	ret += (*tree)->val + '0';
	while (!NodeQ.empty()) {
		if (NodeQ.front()->left) {
			NodeQ.push(NodeQ.front()->left);
			ret += NodeQ.front()->left->val + '0';
		}
		else ret += "X";
		if (NodeQ.front()->right) {
			NodeQ.push(NodeQ.front()->right);
			ret += NodeQ.front()->right->val + '0';
		}
		else ret += "X";
		NodeQ.pop();
	}
	return ret;
}

int main() {
	cout << "Enter value of tree1 elements : ";
	Tree* tree1 = createTree();
	cout << "Enter value of tree2 elements : ";
	Tree* tree2 = createTree();
	string str1 = levelTraverse2(tree1);
	string str2 = levelTraverse2(tree2);
	cout << "str1 = '" << str1 << "'" << endl;
	cout << "str2 = '" << str2 << "'" << endl;
	if (!str1.compare(str2)) cout << "These two trees are Same!" << endl;
	else cout << "These two trees are not Same!" << endl;
	return 0;
}