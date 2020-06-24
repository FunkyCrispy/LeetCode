

// 20ms, 9.3MB, 97.07%, 100%
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (!l1 && !l2) return new ListNode(0);
        ListNode *rst = new ListNode(0);
        ListNode *p = rst;
        int c = 0;
        while (l1 || l2)
        {
            if (l1)
            {
                c += l1->val;
                l1 = l1->next;
            }
            if (l2)
            {
                c += l2->val;
                l2 = l2->next;
            }
            p->next = new ListNode(c % 10);
            c = c / 10;
            p = p->next;
        }
        if (c > 0)
            p->next = new ListNode(c);
        return rst->next;
    }