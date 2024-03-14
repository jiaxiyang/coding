#include <iostream>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {}

void print_list(ListNode *l) {
  while (l) {
    std::cout << l->val << " ";
    l = l->next;
  }
  std::cout << std::endl;
}

// 链表反转: 往新的链表中插入
ListNode *reverseList(ListNode *head) {
  ListNode *prev = NULL, *tmp, *cur = head;
  while (cur) {
    tmp = cur->next;
    cur->next = prev;
    prev = cur;
    cur = tmp;
  }
  return prev;
}

// 链表排序：

int main(int argc, char *argv[]) {
  ListNode l3(3);
  ListNode l2(2, &l3);
  ListNode l1(1, &l2);
  ListNode l0(0, &l1);
  print_list(&l0);
  auto result = reverseList(&l0);
  print_list(result);

  return 0;
}
