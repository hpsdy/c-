#include<cstdio>
#include<stdexcept>
//http://www.cnblogs.com/skywang12345/p/3561803.html
template<typename T>
class dnode{
	public:
	T value;
	dnode *pre;
	dnode *next;
	dnode(){};
	dnode(T v, dnode *p, dnode *n):value(v), pre(p), next(n) {
	}
};

template<typename T>
class doublelink{
	public:
	typedef dnode<T> dnode_c;
	doublelink():count(0) {
		head = new dnode_c();
		head->pre = head;
		head->next = head;
	}	
	~doublelink() {
		dnode_c *tnext = head->next;
		while(tnext != head) {
			dnode_c *tmp = tnext->next;
			delete tnext;
			tnext = tmp;
		}		
		delete head;
	}
	T &get_node_by_index(int index) {
		if (index < 0 || index >= count) {
			throw new std::runtime_error("index error");
		}
		int i = 0;
		if (index < count/2) {
			dnode_c * tnext = head->next;
			for (i = 0; i < index; ++i) {
				tnext = tnext->next;
			}
			return tnext->value;
		}
		dnode_c *tpre = head->pre;
		for (i = 0; i < (count - 1 - index); ++i){
			tpre = tpre->pre;
		}
		return tpre->value;
	}
	int size() {
		return count;
	}
	bool is_empty(){
		return count == 0;
	}
	bool insert(T val, int index) {
		if (index >= count || index < 0) {
			return false;
		}			
		dnode_c *tnode = get_node_by_index(index);
		dnode_c *node = new dnode_c(val, tnode->pre, tnode); 
		dnode_c *tpre = tnode->pre;
		tnode->pre = node;
		tpre->next = node;
		++count;
		return true;
	}
	bool insert_last(T val) {
		dnode_c *last = head->pre;
		dnode_c *node = new dnode_c(val, last, head);
		last->next = node;
		head->pre = node;
		++count;
		return true;
	}
	bool insert_first(T val) {
		return insert(val, 0);
	}
	void del(int index) {
		dnode_c *dlnode = get_node_by_index(index);
		dnode_c *pnode = dlnode->pre;
		dnode_c *nnode = dlnode->next;
		pnode->next = nnode;
		nnode->pre = pnode;
		delete dlnode;
		--count;
	}
	private:
	dnode<T> *head;
	int count;
};

int main(){
	doublelink<int> link;
	link.insert_last(10);
	link.insert_last(20);
	link.insert_last(30);
	int size = link.size();
	for (int i = 0; i < size; ++i) {
		int tmp = link.get_node_by_index(i);
		printf("%d\n", tmp);
	}
	link.get_node_by_index(10);
	return 0;
}
