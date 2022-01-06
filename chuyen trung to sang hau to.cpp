#include <iostream>
#include <string>
using namespace std;

struct NODE {
	char key;
	NODE* next;
};

NODE* createNode(char key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->next = NULL;
	return newNode;
}

void insertHead(NODE*& pHead, char key) {
	if (pHead == NULL) {
		pHead = createNode(key);
		return;
	}

	else {
		NODE *newNode = createNode(key);
		newNode->next = pHead;
		pHead = newNode;
		return;
	}
	return;
}

void removeHead(NODE*& pHead) {
	if (pHead == NULL)
		return;
	else {
		NODE* old_pHead = pHead;
		pHead = pHead->next;
		delete old_pHead;
		return;
	}
	return;
}

NODE* stack;

void push(char key) {
	insertHead(stack, key);
}

void pop() {
	removeHead(stack);
}

int doUuTien(char toan_tu) {
	if (toan_tu == '+' || toan_tu == '-')
		return 1;
	else if (toan_tu == '*' || toan_tu == '/')
		return 2;
	else if (toan_tu == '^')
		return 3;
	return 0;
}

string convert(string bieuthuctrungto) {
	int dem=0;						//đếm chỉ số duyệt qua biểu thức để biết bao giờ đã duyệt qua hết
	char x=bieuthuctrungto[0];		//dùng để duyệt từng phần tử của biểu thức
	string bieuthuchauto;			//kết quả sẽ được lưu vào chuỗi này
	
	push('(');
	bieuthuctrungto=bieuthuctrungto + ')';

	while (dem != bieuthuctrungto.length()) {
		x = bieuthuctrungto[dem];
		//nếu x là toán hạng
		if ('0'<=x  && x<='9') {		
			bieuthuchauto = bieuthuchauto + x;
		}
		//nếu x là dấu ngoặc mở
		else if (x == '(')
			push(x);
		//nếu x là toán tử
		else if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^') {
			//nếu phần tử đỉnh stack có độ ưu tiên lớn hơn x
			while (doUuTien(stack->key)>=doUuTien(x)){
				char w = stack->key;
				pop();
				bieuthuchauto = bieuthuchauto + w;
			}
			push(x);
		}
		//nếu x là dấu ngoặc đóng
		else if (x == ')') {
			while (stack->key != '(') {
				char w = stack->key;
				pop();
				bieuthuchauto = bieuthuchauto + w;
			}
			pop();	//đẩy ngoặc mở ra khỏi stack
		}
		else {
			bieuthuctrungto.erase(dem, 0);
		}
		dem = dem + 1;
	}

	return bieuthuchauto;
}

void deleteStack() {
	while (stack != NULL)
		pop();
}

int main() {
	string bieuthuctrungto = "3+5^(12/6+1)-7*15/3+6";
	cout << convert(bieuthuctrungto);
	deleteStack();
	return 0;
}


