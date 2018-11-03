#include<cstdio>
#include<stdexcept>
#include<cstring>
template<typename T>
class arrStack{
	public:
	arrStack();
	~arrStack();
	void push(T);
	T pop();
	T& top();
	size_t size() {
		return count;
	}
	bool is_empty() {
		return count == 0;
	}
	bool reserve() {
		if ((count+1) > capacity) {
			T *tmp = new(std::nothrow) T[capacity * 2 + 1]();
			if (tmp == nullptr) {
				return false;
			} 
			memcpy(tmp, arr, (sizeof(T) * count));
			delete[] arr;
			arr = tmp;
			capacity = capacity * 2 + 1;
			return true;
		} else {
			return true;
		}
	}
	private:
	T *arr;
	size_t capacity;
	size_t count;
};

template<typename T>
arrStack<T>::arrStack():capacity(0) {
	arr = new(std::nothrow) T[2]();
	if (arr == nullptr){
		throw new std::runtime_error("new fail");
	}
	count=0;
	capacity = 2;
}
template<typename T>
arrStack<T>::~arrStack() {
	if (arr != nullptr){
		delete[] arr;
	}
}
template<typename T>
void arrStack<T>::push(T v) {
	bool ret = reserve();
	if (ret) {
		arr[count++] = v;
	}	
}
template<typename T>
T arrStack<T>::pop() {
	T tmp = arr[count - 1];
	arr[count - 1] = T();
	--count;
	return tmp;
}
template<typename T>
T& arrStack<T>::top() {
	return arr[count - 1];
}

int main(){
	arrStack<int> arr;
	arr.push(10);
	arr.push(20);
	arr.push(30);
	arr.push(40);
	arr.push(50);
	arr.push(60);
	size_t size = arr.size();
	for (int i = 0; i < size; ++i) {
		arr.top() += 100;
		printf("%d\n", arr.pop());
	} 
	return 0;
}

