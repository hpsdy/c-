#include<cstdio>
#include<iostream>
#include<stack>
#include<queue>
#include<utility>
#include<stdexcept>
//http://www.cnblogs.com/skywang12345/p/3576373.html

template<typename T>
class t_node{
	public:
	T key;
	t_node<T> *left = nullptr;
	t_node<T> *right = nullptr;
	t_node<T> *parent = nullptr;
	t_node(T k) : key(k),  left(nullptr), right(nullptr), parent(nullptr) {}
	t_node(T k, t_node<T> *l, t_node<T> *r, t_node<T> *p) :
		key(k),
		left(nullptr),
		right(nullptr),
		parent(nullptr) 
	{	
		left = l;
		right = r;
		parent = p;
	}
	~t_node(){
	}
};


template<typename T>
class binarytree{
	public:
	binarytree();
	~binarytree();
	void preorder();
	void midorder();
	void afterorder();
	t_node<T> *search(T key);
	t_node<T> *iterativesearch(T key);
	T min();
	T max();
	t_node<T> *successor(t_node<T> *x);
	t_node<T> *predecessor(t_node<T> *x);
	void insert(T key);
	void remove(T key);
	void destroy();
	void print();
	private:
	void preorder(t_node<T> *tree) const;
	void midorder(t_node<T> *tree) const;
	void afterorder(t_node<T> *tree) const;
	t_node<T> *search(t_node<T> *tree, T key) const;
	t_node<T> *iterativesearch(t_node<T> *tree, T key) const;
	t_node<T> *min(t_node<T> *tree) const;
	t_node<T> *max(t_node<T> *tree) const;
	void insert(t_node<T> *&tree, t_node<T> *p);
	void remove(t_node<T> *&tree, t_node<T> *p);
	void destroy(t_node<T> *&tree);
	void print(t_node<T> *tree) const;
	t_node<T> *root;
	size_t count;
};

template<typename T>
binarytree<T>::binarytree():count(0),root(nullptr) {
}
template<typename T>
void binarytree<T>::preorder(t_node<T> *tree) const {
	printf("no recursive:");
	std::stack<t_node<T>*> treeStack;
	t_node<T> *pnode = tree;
	while (pnode != nullptr || !treeStack.empty()) {
		while (pnode != nullptr) {
			std::cout<<(pnode->key)<<'\t';
			treeStack.push(pnode);
			pnode = pnode->left;
		}
		pnode = treeStack.top();
		treeStack.pop();
		pnode = pnode->right;
	} 
	printf("\n");
}
template<typename T>
void binarytree<T>::preorder() {
	if (root == nullptr) {
		printf("null tree\n");
		return ;
	}
	preorder(root);	
}

template<typename T>
void binarytree<T>::midorder(t_node<T> *tree) const {
	printf("no recursive:");
	std::stack<t_node<T>*> treeStack;
	t_node<T> *pnode = tree;
	while (pnode != nullptr || !treeStack.empty()) {
		while (pnode != nullptr) {
			treeStack.push(pnode);
			pnode = pnode->left;
		}
		pnode = treeStack.top();
		treeStack.pop();
		std::cout<<(pnode->key)<<'\t';
		pnode = pnode->right;
	} 
	printf("\n");
}
template<typename T>
void binarytree<T>::midorder() {
	if (root == nullptr) {
		printf("null tree\n");
		return ;
	}
	midorder(root);	
}

template<typename T>
void binarytree<T>::afterorder(t_node<T> *tree) const {
	printf("no recursive:");
	std::stack<std::pair<t_node<T>*, bool>> treeStack;
	t_node<T> *pnode = tree;
	while (pnode != nullptr || !treeStack.empty()) {
		while (pnode != nullptr) {
			treeStack.push(std::pair<t_node<T>*, bool>(pnode, false));
			pnode = pnode->left;
		}
		auto &tmp = treeStack.top();
		if (tmp.second == false) {
			tmp.second = true;
			pnode = (tmp.first)->right;
		}else{
			treeStack.pop();
			std::cout<<((tmp.first)->key)<<'\t';
		}
	} 
	printf("\n");
}
template<typename T>
void binarytree<T>::afterorder() {
	if (root == nullptr) {
		printf("null tree\n");
		return ;
	}
	afterorder(root);	
}

template<typename T>
t_node<T> *binarytree<T>::search(t_node<T> *tree, T key) const {
	if (tree == nullptr || tree->key = key) {
		return tree;
	}
	if (tree->key > key){
		tree = search(tree->left, key);
	} else {
		tree = search(tree->right, key);
	}
	return tree;
}
template<typename T>
t_node<T> *binarytree<T>::search(T key) {
	if (root == nullptr) {
		printf("null tree\n");
		return nullptr;
	}
	return search(root, key);	
}

template<typename T>
t_node<T> *binarytree<T>::iterativesearch(t_node<T> *tree, T key) const {
	while (tree != nullptr && tree->key != key) {
		if (tree->key > key) {
			tree = tree->left;	
		} else if (tree->key < key) {
			tree = tree->right;
		}	
	}
	return tree;
}
template<typename T>
t_node<T> *binarytree<T>::iterativesearch(T key) {
	if (root == nullptr) {
		printf("null tree\n");
		return nullptr;
	}
	return iterativesearch(root, key);	
}

template<typename T>
t_node<T> *binarytree<T>::min(t_node<T> *tree) const {
	if (tree == nullptr) {
		throw new std::runtime_error("null point");
	}
	while (tree->left != nullptr) {
		tree = tree->left;
	}
	return tree;
}

template<typename T>
T binarytree<T>::min() {
	return min(root)->key;
}
template<typename T>
t_node<T> *binarytree<T>::max(t_node<T> *tree) const {
	if (tree == nullptr) {
		throw new std::runtime_error("null point");
	}
	while (tree->right != nullptr) {
		tree = tree->right;
	}
	return tree;
}
template<typename T>
T binarytree<T>::max() {
	return max(root)->key;
}

template<typename T>
t_node<T> *binarytree<T>::successor(t_node<T> *x) {
	if (x == nullptr) {
		return nullptr;
	}
	if (x->right != nullptr) {
		return min(x->right);
	} else {
		t_node<T> *y = x->parent;
		while (y != nullptr && (x == y->right)) {
			x = y;
			y = x->parent;
		}
		return y;
	}
}
template<typename T>
t_node<T> *binarytree<T>::predecessor(t_node<T> *x) {
	if (x == nullptr) {
		return nullptr;
	}
	if (x->left != nullptr) {
		return max(x->left);
	} else {
		t_node<T> *y = x->parent;
		while (y != nullptr && (x == y->left)) {
			x = y;
			y = x->parent;
		}
		return y;
	}
}

template<typename T>
void binarytree<T>::insert(t_node<T> *&tree, t_node<T> *p) {
	t_node<T> *tmp = tree;
	t_node<T> *tmpre = nullptr;
	enum dest{DEF = 0, LEFT = 1, RIGHT = 2};
	dest num = DEF;
	while (tmp != nullptr) {
		tmpre = tmp;
		num = DEF;
		if (tmp->key < p->key) {
			num = RIGHT;
			tmp  = tmp->right;
		} else if (tmp->key > p->key) {
			num = LEFT;
			tmp = tmp->left;
		} else {
			return ;
		}
	}
	p->parent = tmpre;
	if (tmpre == nullptr) {
		tree = p;
	} else {
		if (num == LEFT) {
			tmpre->left = p;
		} else {
			tmpre->right = p;

		}	
	}
	++count;
}
template<typename T>
void binarytree<T>::insert(T key) {
	t_node<T> *new_node = new t_node<T>(key);
	insert(root, new_node);
}
template<typename T>
void binarytree<T>::remove(t_node<T> *&tree, t_node<T> *p) {
	if (tree == nullptr || p == nullptr) {
		return ;
	}	
	t_node<T> *x = nullptr;
	t_node<T> *y = nullptr;
	if (p->left == nullptr || p->right == nullptr) {
		y = p;
	} else {
		y = successor(p->right);
	}
	if (y->left != nullptr) {
		x = y->left;
	} else {
		x = y->right;
	}
	if (x != nullptr) {
		x->parent = y->parent;		
	}
	if (y->parent == nullptr) {
		tree = x;
	} else if (y == y->parent->left) {
		y->parent->left = x;
	} else {
		y->parent->right = x;
	}
	if (y != p) {
		p->key = y->key;
	}
	--count;
//	return y;
}
template<typename T>
void binarytree<T>::remove(T key) {
	t_node<T> *ret = iterativesearch(root, key);
	if (ret != nullptr) {
		remove(root, ret);
	}
}
template<typename T>
void binarytree<T>::destroy(t_node<T> *&tree) {
	if (tree == nullptr) {
		return ;
	}
	if (tree->left != nullptr) {
		destroy(tree->left);
	}
	if (tree->right != nullptr) {
		destroy(tree->right);
	}
	delete tree;
	--count;
	tree = nullptr;
}
template<typename T>
void binarytree<T>::destroy() {
	if (root == nullptr) {
		return ;
	}
	destroy(root);
	count = 0;
}
template<typename T>
void binarytree<T>::print(t_node<T> *tree) const {
	size_t num_per = 1;
	size_t tmp_num = 0;
	std::queue<t_node<T>*> arr;
	arr.push(tree);
	t_node<T> *tmp = nullptr;
	while(!arr.empty()) {
		tmp_num = 0;
		for (int i = 0; i < num_per; ++i) {
			tmp = arr.front();
			std::cout<<(tmp->key)<<'\t';
			arr.pop();
			if (tmp->left != nullptr) {
				++tmp_num;
				arr.push(tmp->left);
			}
			if (tmp->right != nullptr) {
				arr.push(tmp->right);
				++tmp_num;
			}
		}
		num_per = tmp_num;
		std::cout<<'\n';
	}
}
template<typename T>
void binarytree<T>::print() {
	print(root);
}
template<typename T>
binarytree<T>::~binarytree() {
	destroy();
}

int main() {
	binarytree<int> arr;
	arr.insert(10);
	arr.insert(30);
	arr.insert(20);
	arr.insert(80);
	arr.insert(90);
	arr.insert(60);
	arr.insert(70);
	arr.print();
	arr.preorder();
	arr.midorder();
	arr.afterorder();
	std::cout<<arr.max()<<std::endl;
	std::cout<<arr.min()<<std::endl;
	arr.remove(70);
	arr.print();
	return 0;
}

