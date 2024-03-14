#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
方法一：自顶向下归并排序
对链表自顶向下归并排序的过程如下。

1.
找到链表的中点，以中点为分界，将链表拆分成两个子链表。寻找链表的中点可以使用快慢指针的做法，快指针每次移动
222 步，慢指针每次移动 111
步，当快指针到达链表末尾时，慢指针指向的链表节点即为链表的中点。

2. 对两个子链表分别排序。

3. 将两个排序后的子链表合并，得到完整的排序后的链表。可以使用「21.
合并两个有序链表」的做法，将两个有序的子链表进行合并。

上述过程可以通过递归实现。递归的终止条件是链表的节点个数小于或等于
111，即当链表为空或者链表只包含 111 个节点时，不需要对链表进行拆分和排序。

 */

ListNode *merge(ListNode *head1, ListNode *head2) {
  ListNode *dummyHead = new ListNode(0);
  ListNode *temp = dummyHead, *temp1 = head1, *temp2 = head2;
  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->val <= temp2->val) {
      temp->next = temp1;
      temp1 = temp1->next;
    } else {
      temp->next = temp2;
      temp2 = temp2->next;
    }
    temp = temp->next;
  }
  if (temp1 != nullptr) {
    temp->next = temp1;
  } else if (temp2 != nullptr) {
    temp->next = temp2;
  }
  return dummyHead->next;
}

ListNode *sortList(ListNode *head, ListNode *tail) {
  if (head == nullptr) {
    return head;
  }
  if (head->next == tail) {
    head->next = nullptr;
    return head;
  }
  ListNode *slow = head, *fast = head;
  while (fast != tail) {
    slow = slow->next;
    fast = fast->next;
    if (fast != tail) {
      fast = fast->next;
    }
  }
  ListNode *mid = slow;
  return merge(sortList(head, mid), sortList(mid, tail));
}

ListNode *sortList(ListNode *head) { return sortList(head, nullptr); }

void print_list(ListNode *l) {
  while (l) {
    std::cout << l->val << " ";
    l = l->next;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]) {
  ListNode l3(3);
  ListNode l2(5, &l3);
  ListNode l1(6, &l2);
  ListNode l0(0, &l1);
  print_list(&l0);

  auto result = sortList(&l0);
  print_list(&l0);

  return 0;
}
