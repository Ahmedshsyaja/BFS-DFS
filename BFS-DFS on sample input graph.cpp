
#include<iostream>
using namespace std;
struct node
{
	int data;
	struct node* next;
	struct node* prev;
}*start;
struct double_llist
{
private:
	node* temp = NULL;
	node* head = NULL;
	node* current_ptr = NULL;
	int count;
public:
	node* insert_at_begin(int value) {
		if (head == NULL) {
			temp = new node;
			temp->data = value;
			head = temp;
			current_ptr = temp;
			temp->next = NULL;
			temp->prev = NULL;
		}
		else {
			current_ptr = temp;
			temp = new node;
			temp->data = value;
			current_ptr->next = temp;
			temp->prev = current_ptr;
			temp->next = NULL;
		}
		return temp;
	}
	void insert_after(int value, int position) {
		node* Temp = head;
		int counter = 0;
		node* temp2 = NULL;
		node* temp1 = new node;
		while (Temp != NULL) {
			if (position == 0) {
				temp1->data = value;
				temp1->prev = Temp;
				temp2 = Temp;
				temp2 = temp2->next;
				temp1->next = temp2;
				Temp->next = temp1;
				break;
			}
			if (counter == position) {
				temp1->prev = Temp;
				temp2 = Temp;
				temp2 = temp2->next;
				temp1->data = value;
				temp1->next = temp2;
				Temp->next = temp1;
				break;
			}
			Temp = Temp->next;
			counter = counter + 1;
		}
	}
	node* insert_at_end(int value){
		node* temp = new node;
		temp->data = value;
		this->temp->next = temp;
		temp->prev = this->temp;
		temp->next = NULL;
		if (head == NULL) {
			this->head = this->temp;
			this->current_ptr = this->temp;
		}
		else {
			this->current_ptr = this->temp;
		}
		return temp;
	};
	void delete_at_begin() {
		node* temp = head;
		if (temp == NULL) {
			delete temp;
		}
		temp = temp->next;
		delete head;
		if (temp == NULL) {
			head = NULL;
			return;
		}
		head = temp;
		temp->prev = NULL;
	};
	void delete_before(int value) {
		node* Temp = head;
		node* temp2 = NULL;
		node* temp3 = NULL;
		while (Temp != NULL) {
			if (Temp->data == value) {
				temp3 = Temp;
				temp2 = Temp;
				temp2 = Temp->prev;
				temp3 = Temp->next;
				if (temp3 == NULL) {
					break;
				}
				delete Temp;
				temp3->prev = temp2;
				temp2->next = temp3;
				Temp = temp3;
			}
			Temp = Temp->next;
		}
	};
	int Search(int data) {
		node* Temp = head;
		int count = 0;
		while (Temp != NULL) {
			if (data == Temp->data) {
				return count;
			}
			else {
				Temp = Temp->next;
				count = count + 1;
			}
		}
	}
	node* delete_at_end(node* NODE) {
		node* temp = NODE;
		if (temp == NULL) {
			head = NULL;
			return head;
		}
		temp = temp->prev;
		delete NODE;
		if (temp == NULL) {
			head = NULL;
			return head;
		}
		if (temp->prev == NULL) {
			head = temp;
		}
		temp->next = NULL;
		return temp;
	};
	int Return_At_F() {
		return head->data;
	}
	int return_At_L() {
		node* Temp = head;
		int data = 0;
		while (Temp != NULL) {
			data=Temp->data;
			Temp = Temp->next;
		}
		return data;
	}
	void display_dlist() {
		node* Temp = head;
		while (Temp != NULL) {
			cout << Temp->data << " ";
			Temp = Temp->next;
		}
		cout << endl;
	}
	bool is_empty() {
		if (head == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	node* R_Front() {
		return head;
	}
	double_llist()
	{
		head = NULL;
		current_ptr = NULL; //constructor for my class
		count = 0;
	}
	~double_llist() {
		current_ptr = head;
		while (current_ptr != NULL)
		{
			node* next = current_ptr->next;
			delete current_ptr;
			current_ptr = next;
		}
	}
};
class Graph {
	node* Node = NULL;
	double_llist** a = NULL;
	double_llist* list = NULL;
	int vertex = 0;
public:
	Graph(int vertex) {
		this->vertex = vertex;
		a = new double_llist * [vertex];
		for (int i = 0; i < vertex; i++) {
			a[i] = NULL;
		}
	}
	void AddEdge(int u, int v) {
		if (a[u] == NULL) {
			list = new double_llist;
			list->insert_at_begin(v);
			a[u] = list;
			if (a[v] == NULL) {
				list = new double_llist;
				list->insert_at_begin(u);
				a[v] = list;
				a[v]->insert_at_begin(u);
			}
			else {
				a[v]->insert_at_begin(u);
			}
		}
		else {
			a[u]->insert_at_begin(v);
			if (a[v] == NULL) {
				list = new double_llist;
				list->insert_at_begin(u);
				a[v] = list;
			}
			else {
				a[v]->insert_at_begin(u);
			}
		}
	}
	void Display() {
		for (int i = 0; i < vertex; i++) {
			if (a[i] != NULL) {
				cout << " Vertex " << i << " --->";
				a[i]->display_dlist();
			}
		}
	}
	void B_F_S(int n,int search) {
		bool* visited = new bool[this->vertex];
		double_llist queue;
		visited[n] = true;
		for (int i = 0; i < this->vertex; i++) {
			visited[i] = false;
		}
		queue.insert_at_begin(n);
		while (queue.is_empty() != true) {
			int index = queue.Return_At_F();
			if (visited[index] != true) {
				cout << " " << index;
				if (index == search) {
					return;
				}
				visited[index] = true;
			}
			queue.delete_at_begin();
			node* temp = NULL;
			if (a[index] != NULL) {
				temp = a[index]->R_Front();
			}
			while (temp != NULL) {
				int data = temp->data;
				if (visited[data] != true) {
					queue.insert_at_begin(data);
					cout << " " << data;
					if (data == search) {
						return;
					}
					visited[data] = true;
				}
				temp = temp->next;
			}
		}
	}
	int D_F_S(int n,int search) {
		bool* visited = new bool[this->vertex];
		double_llist stack;
		visited[n] = true;
		for (int i = 0; i < this->vertex; i++) {
			visited[i] = false;
		}
		node* nd = NULL;
		node* temp = NULL;
		int index = 0;
		nd=stack.insert_at_begin(n);
		index = stack.return_At_L();
		while (stack.is_empty() != true) {
			if (a[index] != NULL) {
				if (visited[index] != true) {
					cout << " " << index;
					if (index == search) {
						return 0;
					}
					visited[index] = true;
				}
				temp = a[index]->R_Front();
			}
			if (temp != NULL) {
				if (visited[temp->data] == true || visited[temp->data] != true) {
					while (visited[temp->data] == true|| visited[temp->data] != true) {
						if (visited[temp->data] != true) {
							cout << temp->data << " ";
							if (index == temp->data) {
								return 0;
							}
							visited[temp->data] = true;
							nd = stack.insert_at_begin(temp->data);
							index = temp->data;
							break;
						}
						else if(visited[temp->data] == true) {
							node* No = NULL;
							node* Nd = NULL;
							Nd = a[index]->R_Front();
							int data = 0;
							while (visited[Nd->data] == true) {
								
								Nd = Nd->next;
								if(Nd!=NULL)
								data = Nd->data;
								if (Nd == NULL) {
									data = 0;
									break;
								}
							}
							if (data == 0) {
								nd=stack.delete_at_end(nd);
								index = stack.return_At_L();
							}
							else {
								index = data;
								nd = stack.insert_at_begin(index);
							}
							break;
						}
					}
				}
			}
			else {
				return 0;
			}
			
		}
	}
	int matrix(int  array[][2], int Vertices, int Edges) {
		int** arr = new int* [Vertices];
		for (int i = 0; i < Vertices; i++) {
			arr[i] = new int[Edges];
		}
		for (int i = 0; i < Vertices; i++) {
			for (int j = 0; j < Edges; j++) {
				arr[i][j] = 0;
			}
		}
		int val[2];
		int a = 0;
		int b = 0;
		for (int i = 0; i < 7; i++) {
			for (int k = 0; k < 2; k++) {
				val[k] = array[i][k];
			}
			for (int k = 0; k < 2; k++) {
				for (int l = k + 1; l < 2; l++) {
					if (val[l] != -1) {
						a = val[k];
						b = val[l];
						arr[a][b] = 1;
						arr[b][a] = 1;
						swap(a, b);
						arr[a][b] = 1;
						arr[b][a] = 1;
					}
				}
				break;
			}

		}
		cout << "\n";
		for (int i = 1; i < Vertices; i++) {
			for (int j = 1; j < Edges; j++) {
				cout << arr[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}
	void Path() {
		cout << " B_F_S" << "\n";
		cout << "-------\n";
		B_F_S(1, 4);
		cout << "\n D_F_S" << "\n";
		cout << "-------\n";
		D_F_S(1, 4);
	}
};
int main() {
	Graph a(14);
    a.AddEdge(1,2);
	a.AddEdge(2, 4);
	a.AddEdge(2, 5);
	a.AddEdge(5, 9);
	a.AddEdge(9, 13);
	a.AddEdge(4, 8);
	a.AddEdge(4, 7);
	a.AddEdge(7, 11);
	a.AddEdge(7, 12);
	a.AddEdge(1, 3);
	a.AddEdge(3, 6);
	a.AddEdge(6, 10);
	a.Display();
	a.Path();
}
