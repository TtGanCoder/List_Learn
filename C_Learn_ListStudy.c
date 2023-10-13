#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>


//今天自学了一手链表，接下来我将设置一个程序，来实现
// 1.创建一个5个节点的链表
// 2.在头部删除一个节点并增加一个新节点
// 3.在尾部删除节点并增加一个新的节点
// 4.在链表中间增加节点
// 5.在链表中间删除节点
//

struct List {         //首先，要想创建一个链表，我们需要创建一个个的节点才能形成链表，要创造节点，我们需要创造他的骨架结构
	int date;         //就正如这个结构体List是形成节点的重要条件（1.数据类型\数据2.指向下一个节点的指针）
	struct List* next;
};


struct List* CreateNewNode(int newdate) {
	struct List* NewNode = (struct List*)malloc(sizeof(struct List));//通过malloc函数分配一个struct List结构体大小的内存，分配一个节点的内存
	if (NewNode == NULL) {                                           //通常malloc函数分配内存时，分配成功会返回一个void*通用类型的指针，
		printf("内存分配失败\n");                                    //但是这个指针并不能直接与我们的struct List直接赋值操作，虽然可以
		return 1;//0表示运行成功，1表示失败                          //因为编译器会强制转换void*的指针类型，但是为了一个良好的编译习惯
	}                                                                //我们通常会先转换指针类型，好处就是便于理解代码
	NewNode->date = newdate;                                         //malloc函数分配空间失败时会返回NULL
	NewNode->next = NULL;
	return NewNode;
}

void PrintList(struct List*head) {//打印链表的函数
	struct List* Current = head;
	if (head == NULL) {
		printf("链表为空");
		return;
	}
	while (Current != NULL) {
		if (Current->next == NULL) {
			printf("%d", Current->date);
		}else
		printf("%d->", Current->date);//创造一个新指针从头指针开始循环遍历链表并打印每一个节点
		Current = Current->next;
	}
	printf("\n");
	return;
}

//删除头结点的函数
void Delete_Head(struct List**head) {//**一个很重要的知识点，，函数传参时想改变main里的值时要用指针来传参，通过创建一个指向main里的值的地址的
	if (*head == NULL) {             //指针，来实际上改变我们想要改变的这个值，如果直接传值的话，则会导致在函数内部重新创建一个相等的值
		printf("链表为空");          //来改变函数内部的这个值，并不会对main的值做出改变
	}                                //还有一个重要的理解（我个人的理解）函数的调用和传参实际上是a=b；这么说吧，假设我在main上面创建了一个新的
	struct List* Current = *head;    //函数，void hanshu（a）{}参数设置成a，当我在main调用他的时候hanshu(b);给他传参b，实际上就是a=b；
	*head = (*head)->next;           //把b的值赋予a，调用指针时是*a=&b
	free(Current);                   
	return;                          
	                                
}                                   

void Insert_In_Head(int newdate,struct List**head) {//在头结点插入新节点的函数
	struct List* NewNode = CreateNewNode(newdate);
	NewNode->next = *head;//将第一个节点的地址赋予当前节点的next
	*head = NewNode;//更新当前节点为头节点
	return;
}

void Delete_End(struct List** head) {//删除最后一个节点的函数
	struct List* Current = *head;
	while (Current->next->next != NULL) {
		Current = Current->next;
	}
	struct List* Temp = Current->next->next;
	Current->next = NULL;
	free(Temp);
	return;
}

void Insert_In_End(int newdate,struct List** head) {//在最后一个节点添加新节点的函数
	struct List* NewNode = CreateNewNode(newdate);
	struct List* Current = *head;
	while (Current->next != NULL) {
		Current = Current->next;
	}
	Current->next = NewNode;
	return;
}

void Insert_After_Targetvalue(int Targetvalue,int Newdate,struct List** head) {//在期望节点后增加新节点的函数，能力有限，想实现一个互动判断
	struct List* Current = *head;                                              //判断当前节点是否是期望插入节点的节点，输入Y执行插入，
	struct List* NewNode = CreateNewNode(Newdate);                             //输入N则继续遍历下一个重复节点的值继续判断，从而实现
	while (Current != NULL) {                                                  //面对重复节点时的应对措施，但是又需要设置一个新的打印循环
		if(Current->date== Targetvalue){                                       //还涉及到putchar函数等等，有点麻烦，下次学习的时候再设计                                                          
			NewNode->next = Current->next;                                     //针对有重复节点时的链表插入
			Current->next = NewNode;
			return;
		}
		Current = Current->next;
	}
	printf("找不到目标节点，插入失败");
	return;
}

void Delete_After_Targetvalue(int Targetvalue,struct List** head) {//实现删除目标节点后一位节点的函数
	struct List* Current = *head;
	while (Current != NULL) {
		if (Current->date == Targetvalue) {
			struct List* temp = Current->next;
			Current->next = Current->next->next;
			free(temp);
			return;
		}
		Current = Current->next;
	}
	printf("未找到目标节点，删除失败");
	return;
}

int main(){
	struct List* head = CreateNewNode(4);//这里创造一个头指针指向第一个数据，头指针在对链表进行各种操作时有着很重要的意义
	head->next = CreateNewNode(8);
	head->next->next = CreateNewNode(8);
	head->next->next->next= CreateNewNode(2);
	head->next->next->next->next = CreateNewNode(1);//创造了一个5个节点的链表48821
	printf("创建了一个链表：");
	PrintList(head);//验证一下我们的链表是否成功创建
	                                                      //问题1解决
	Delete_Head(&head);//删除第一个节点
	printf("删除了头节点，当前链表为：");
	PrintList(head);//验证一下是否删除成功
	Insert_In_Head(1,&head);//在头部插入一个数据1
	printf("在头部插入了一个数据1，当前链表为：");
	PrintList(head);//验证一下是否插入成功
	                                                     //问题2解决
	Delete_End(&head);//删除最后一个节点
	printf("删除了最后一个节点，当前链表为：");
	PrintList(head);//验证一下是否删除成功
	Insert_In_End(6,&head);//在最后一个节点插入6；
	printf("在最后一个节点插入了6，当前链表为：");
	PrintList(head);//验证一下是否插入成功
	                                                     //问题3解决
	Insert_After_Targetvalue(8,6,&head);//在链表中8和8之间插入一个6,目前精力有限只能实现没有重复数时（第一个重复数后）的链表节点插入
	printf("在8和8中插入一个6，当前链表为：");
	PrintList(head);//验证一下是否插入成功
	                                                     //问题4解决
	Delete_After_Targetvalue(1,&head);//删除第一个8
	printf("删除第一个8，当前链表为：");
	PrintList(head);//验证一下是删除成功
	                                                     //问题5解决
	return 0;
}