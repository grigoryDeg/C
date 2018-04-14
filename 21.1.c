void push(struct node* head, int data) {
	struct node* newNode =(struct node*) malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = NULL;
	head = newNode;
}
void push_test() {
	List head = build();
	push(head, 1);
}