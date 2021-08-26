//
// Created by chenda on 2021/3/12.
//
//#include <iostream>
//#include <vector>
//#include <assert.h>
//#include <string.h>
//#include <queue>
#include <bits/stdc++.h>


//#define build_all

using namespace std;


struct ListNode {
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {
        std::cout << "the constructor of struct, with val is: " << val << '\n';
    }
    ListNode() : val(0), next(nullptr) {}
    ~ListNode() {
        std::cout << "the deconstruction of struct, with val is: " << val << '\n';
    }
};

class BinaryTreeNode {
public:
    int val;
    BinaryTreeNode* pParent;
    BinaryTreeNode* pRight;
    BinaryTreeNode* pLeft;
};

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
};

ListNode* CreateList(std::vector<int>& vals) {
    if (vals.size() == 0) return nullptr;
    int vals_size = vals.size();
    ListNode* head = new ListNode(vals[0]);
    ListNode* tmp = head;
    for (int i = 1; i < vals_size; ++i) {
        tmp->next = new ListNode(vals[i]);
        tmp = tmp->next;
    }
    return head;
}

void DeleteList(ListNode* head) {
    if (!head) return;
    while(head) {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

void ShowList(ListNode* head) {
    if (!head) return;
    while (head) {
        std::cout << head->val << " -> ";
        head = head->next;
    }
    std::cout << "null" << "\n";
}

//此方法未指定null节点特殊值，用来建立完全二叉树
TreeNode* CreateBinaryTree(std::vector<int>& vec) {
    if (vec.empty()) return nullptr;
    int index = 0;
    TreeNode* root = new TreeNode(vec[index]);
    std::queue<TreeNode*> myQueue;
    myQueue.emplace(root);
    while (index < vec.size() - 1) {
        TreeNode* pNode = myQueue.front();
        myQueue.pop();
        pNode->left = new TreeNode(vec[++index]);
        myQueue.emplace(pNode->left);
        pNode->right = new TreeNode(vec[++index]);
        myQueue.emplace(pNode->right);
    }
    return root;
}

//如果指定所有节点值均大于等于0, 而负值表示空节点
TreeNode* CreateBinaryTree_1(std::vector<int>& vec) {
    if (vec.empty() || vec[0] < 0) return nullptr;
    int index = 0;
    TreeNode* root = new TreeNode(vec[index]);
    std::queue<TreeNode*> myQueue;
    myQueue.emplace(root);
    while (index < vec.size() - 1) {//感觉这里应该是-2
        TreeNode* pNode = myQueue.front();
        myQueue.pop();
        if (vec[++index] >= 0) {
            pNode->left = new TreeNode(vec[index]);
            myQueue.emplace(pNode->left);
        }
        if (vec[++index] >= 0) {
            pNode->right = new TreeNode(vec[index]);
            myQueue.emplace(pNode->right);
        }
    }
    return root;
}

//使用递归的方法建立二叉树，指定负值为空节点
TreeNode* CreateTreeRecursion(std::vector<int>& vec, int& index) {
    if (vec.empty() || index >= vec.size() || vec[index] < 0) return nullptr;
    TreeNode* root = new TreeNode(vec[index]);
    ++index;
    root->left = CreateTreeRecursion(vec, index);
    ++index;
    root->right = CreateTreeRecursion(vec, index);
    return root;
}


void DeleteTree(TreeNode* root) {
    if (!root) return;
    std::queue<TreeNode*> myQueue;
    myQueue.emplace(root);
    while (!myQueue.empty()) {
        TreeNode* pNode = myQueue.front();
        myQueue.pop();
        if (pNode->left) myQueue.emplace(pNode->left);
        if (pNode->right) myQueue.emplace(pNode->right);
        std::cout << "delete TreeNode : " << pNode->val << '\n';
        delete pNode;
        pNode = nullptr;
    }
}

void dfsTree(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << '\t';
    dfsTree(root->left);
    dfsTree(root->right);
}

void bfsTree(TreeNode* root) {
    if (!root) return;
    std::queue<TreeNode*> myQueue;
    myQueue.emplace(root);
    while (!myQueue.empty()) {
        TreeNode* pNode = myQueue.front();
        myQueue.pop();
        std::cout << pNode->val << '\t';
        if (pNode->left) myQueue.emplace(pNode->left);
        if (pNode->right) myQueue.emplace(pNode->right);
    }
    std::cout << '\n';
}



//----众多函数----
#ifdef build_all

//---------------------------------------------------字符串测试-------------------------------
void string_addr_test() {
    char arr1[] = "hello";
    char arr2[] = "hello";
    const char *str1 = "hello";
    const char *str2 = "hello";
    std::cout << (int*)arr1 << " " << (int*)arr2 << " "<< sizeof(arr1) <<std::endl;//不一样
    std::cout << (int*)str1 << " " << (int*)str2 << std::endl;//一样-----指向的应该都是字符串常量存储的内存地址
}
//-------------------------------------------------------------二维数组查找--------------------
bool find(int* matrix, int raws, int cols, int number) {
    if (!matrix || raws <= 0 || cols <= 0) return false;
    int raw = 0;
    int col = cols - 1;
    while (raw < raws && col >= 0) {
        int num = matrix[raw * raws + col];
        if (num == number) {
            return true;
        } else if (num > number) {
            --col;
        } else {
            ++raw;
        }
    }
    return false;
}

//---------------------------------------------------------------------链表插入删除--------------
//向链表尾部插入节点，注意传入的函数参数是指向指针的指针，
// 主要应对的情形就是传入空链表时的情况（形参实参相关）
void AddToTail(ListNode** pHead, int value) {
    ListNode* pNew = new ListNode();
    pNew->val = value;
    pNew->next = nullptr;
    if (*pHead == nullptr) {
        *pHead = pNew;
        return;
    } else {
        ListNode* pTmp = *pHead;
        while (pTmp->next != nullptr) {
            pTmp = pTmp->next;
        }
        pTmp->next = pNew;
    }
}

//删除链表节点（有很多细节）
void RemoveNode(ListNode** pHead, int value) {
    if (pHead == nullptr || *pHead == nullptr) return;
    ListNode* pDelete = nullptr;
    if ((*pHead)->val == value) {
        pDelete = *pHead;
        *pHead = (*pHead)->next;
    } else {
        ListNode* pTmp = *pHead;
//        while (pTmp->next != nullptr && pTmp->next->val != value) {
//            pTmp = pTmp->next;
//        }
//        if (pTmp->next != nullptr) {
//            pDelete = pTmp->next;
//            pTmp->next = pTmp->next->next;
//        }
        while (pTmp->next != nullptr) {
            if (pTmp->next->val == value) {
                pDelete = pTmp->next;
                pTmp->next = pTmp->next->next;
                break;
            } else {
                pTmp = pTmp->next;
            }
        }
    }
    if (pDelete != nullptr) {
        delete pDelete;
        pDelete = nullptr;
    }
}

//---------------------------------------根据前序中序遍历--------重建二叉树----------------
BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder) {
    //前序遍历序列的第一个数字是根节点的值
    int rootval = startPreorder[0];
    BinaryTreeNode* root = new BinaryTreeNode();
    root->pLeft = nullptr;
    root->pRight = nullptr;
     if (startPreorder == endPreorder) {
         if (startInorder == endInorder && *startPreorder == *startInorder) {
             return root;
         } else {
             std::cout << "wrong input----" << '\n';
             assert(false);
         }
     }
     //在中序遍历中找到根节点的值
     int* rootInorder = startInorder;
     while (rootInorder <= endInorder && *rootInorder != rootval) {
         ++rootInorder;
     }
     if (rootInorder == endInorder && *rootInorder != rootval) {
         std::cout << "wrong input----" << '\n';
         assert(false);
     }

     int leftLength = rootInorder - startInorder;
     int* leftPreorderEnd = startPreorder + leftLength;
     if (leftLength > 0) {
         root->pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd,
                                     startInorder, rootInorder - 1);
     }
     if (leftLength < endPreorder - startPreorder) {
         root->pRight = ConstructCore(leftPreorderEnd + 1, endPreorder,
                                      rootInorder + 1, endInorder);
     }

     return root;
}

BinaryTreeNode* Construct(int* preorder, int* inorder, int length) {
    if (preorder == nullptr || inorder == nullptr || length <= 0) return nullptr;

    return ConstructCore(preorder, preorder + length - 1,
                         inorder, inorder + length - 1);
}


//--------------------------------------------------------二叉树中序遍历的下一个节点--------------------------------
BinaryTreeNode* GetNext(BinaryTreeNode* pNode) {
    if (!pNode) return nullptr;
    BinaryTreeNode* pNext = pNode->pRight;
    if (pNext != nullptr) {
        while (pNext->pLeft != nullptr) {
            pNext = pNext->pLeft;
        }
    } else if (pNode->pParent != nullptr) {
        BinaryTreeNode* pParent_tmp = pNode->pParent;
        BinaryTreeNode* pCurrent = pNode;
        while (pParent_tmp != nullptr && pCurrent == pParent_tmp->pRight) {
            pCurrent = pParent_tmp;
            pParent_tmp = pParent_tmp->pParent;
        }
        pNext = pParent_tmp;
    }
    return pNext;
}

BinaryTreeNode* GetNext_1(BinaryTreeNode* node) {
    if (!node) return nullptr;
    BinaryTreeNode* pNext = nullptr;
    if (node->pRight != nullptr) {
        BinaryTreeNode* pRight = node->pRight;
        while (pRight->pLeft != nullptr) {
            pRight = pRight->pLeft;
        }
        pNext = pRight;
    } else if (node->pParent != nullptr) {
        BinaryTreeNode* pParent = node->pParent;
        BinaryTreeNode* pCurrent = node;
        while (pParent != nullptr && pParent->pLeft != pCurrent) {
            pCurrent = pParent;
            pParent = pParent->pParent;
        }
        pNext = pParent;
    } else {
        pNext = nullptr;
    }
    return pNext;
}

//--------------------------------------------------快速排序--------------------------------
//实现快速排序算法的关键在于先在数组中选择一个数字，接下来将数组分为两部分，左小右大
int RandomIndexRange(int start, int end) {
    if (start < 0 || end < 0) return 0;
    return (int)(start + end) / 2;
}
void Swap(int* data1, int* data2) {
    int tmp = *data1;
    *data1 = *data2;
    *data2 = tmp;
}
//end最大 == length - 1
//int (&data)[]是错误的
int Partition(int *data, int length, int start, int end) {
    if (data == nullptr || length < 0 || start < 0 || end < start || end >= length) return -1;
    int index = RandomIndexRange(start, end);
    Swap(&data[index], &data[end]);
    int small = start - 1;
    for (int i = start; i < end; ++i) {
        if (data[i] < data[end]) {
            ++small;
            Swap(&data[small], &data[i]);
        }
    }
    ++small;
    Swap(&data[small], &data[end]);
    return small;
}
//使用递归重复上述过程
void QuickSort(int *data, int length, int start, int end) {
    if (data == nullptr || start >= end || start < 0 || end >= length) return;
    int index = Partition(data, length, start, end);
    if (index > start)
        QuickSort(data, length, start, index - 1);
    if (index < end)
        QuickSort(data, length, index + 1, end);
}

//不同的排序算法适用的场景也不相同----例子：公司员工年龄排序
void SortAges(int *ages, int length) {
    if (ages == nullptr || length <= 0) return;
    const int oldestAge = 99;
    int timesOfAge[oldestAge + 1];
    for (int i = 0; i <= oldestAge; ++i) {
        timesOfAge[i] = 0;
    }
    for (int i = 0; i < length; ++i) {
        int age = ages[i];
        if (age < 0 || age > oldestAge) {
            printf("wrong");
        }
        ++timesOfAge[age];
    }
    int idx = 0;
    for (int i = 0; i <= oldestAge; ++i) {
        for (int j = 0; j < timesOfAge[i]; ++i) {
            ages[idx] = i;
            ++idx;
        }
    }
}

//-----------------旋转数组的最小数字----加一个无关紧要的条件： > 0
int minArray(std::vector<int>& numbers) {
    if (numbers.size() == 0) return 0;
    int start = 0;
    int end = numbers.size() - 1;
    int mid = start;
    while (numbers[start] >= numbers[end]) {
        if (end - start == 1) {
            mid = end;
            break;
        }
        mid = (start + end) / 2;
        //对于此种特殊情况需要遍历进行
        if (numbers[start] == numbers[end] && numbers[start] == numbers[mid]) {
            int res = numbers[start];
            for (int i = start + 1; i < end; ++i) {
                if (res > numbers[i]) res = numbers[i];
            }
            return res;
        }
        if (numbers[mid] >= numbers[start])
            start = mid;
        else
            end = mid;
    }
    return numbers[mid];
}




//----------------反转链表------------
void ReverseListNode(ListNode** head) {
    if (head == nullptr || *head == nullptr) return;
    ListNode* pPre = nullptr;
    ListNode* pCurr = *head;
    while(pCurr) {
        ListNode* pNext = pCurr->next;
        pCurr->next = pPre;
        pPre = pCurr;
        pCurr = pNext;
    }
    *head = pPre;
}

void ReverseListNode_1(ListNode*& head) {
    if (head == nullptr) return;
    ListNode* pPre = nullptr;
    ListNode* pCurr = head;
    while(pCurr) {
        ListNode* pNext = pCurr->next;
        pCurr->next = pPre;
        pPre = pCurr;
        pCurr = pNext;
    }
    head = pPre;
}

//------------------------------------------打印从1到最大的n位数-----------
//Increment 实现的是字符串数字的逐1增加
bool Increment(char* number) {
    bool isOverflow = false;
    int nTakeOver = 0;
    int nLength = strlen(number);
    for (int i = nLength - 1; i >= 0; --i) {
        int nSum = number[i] - '0' + nTakeOver;
        if (i == nLength - 1) {
            ++nSum;
        }
        if (nSum >= 10) {
            if (i == 0) {
                isOverflow = true;
            } else {
                nSum -= 10;
                nTakeOver = 1;
                number[i] = '0' + nSum;
            }
        } else {
            number[i] = '0' + nSum;
            break;
        }
    }
    return isOverflow;
}
//注意--只有遇到第一个非0字符才开始打印
void PrintfNumber(char* number){
    bool isBeginning0 = true;
    int nLength = strlen(number);

    for (int i = 0; i < nLength; ++i) {
        if (isBeginning0 && number[i] != '0') isBeginning0 = false;
        if (!isBeginning0) {
            printf("%c", number[i]);
        }
    }
    printf("\t");
}
//
void Print1ToMaxOfNDigits(int n) {
    if (n <= 0) return;
    char* number = new char[n + 1];
    memset(number, '0', n);
    number[n] = '\0';

    while (!Increment(number)) {
        PrintfNumber(number);
    }
    delete[] number;
}

//------------------------打印数字---考虑到大数---数字排列的方法，使用递归使代码更整洁-----
//----------TODO:下面这个递归实现很有dfs的味道---从最低位放射全排列到最高位----
void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index) {
    if (index == length - 1) {
        PrintfNumber(number);
        return;
    }
    for (int i = 0; i < 10; ++i) {
        number[index + 1] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
    }
}

void Print1ToMaxOfNDigits_1(int n) {
    if (n <= 0) return;
    char* number = new char[n + 1];
    memset(number, '0', n);
    number[n] = '\0';

    for (int i = 0; i < 10; ++i) {
        number[0] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, n, 0);
    }
    delete[] number;
}


//------------------------------使用O(1)时间复杂度删除链表的节点-------
//----假设待删除的节点肯定在链表当中----
ListNode* DeleteNode_1(ListNode** pListHead, ListNode* pToBeDeleted) {
    if (!pListHead) return nullptr;
    if (!pToBeDeleted) return *pListHead;

    //要删除的节点不是尾节点，包括要删除头节点
    if (pToBeDeleted->next != nullptr) {
        ListNode* pNext = pToBeDeleted->next;
        pToBeDeleted->val = pNext->val;
        pToBeDeleted->next = pNext->next;
        delete pNext;
        pNext = nullptr;
        return *pListHead;
    } else if (pToBeDeleted == *pListHead) {//要删除的即是尾节点也是头节点，也就是链表只有一个节点
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        *pListHead = nullptr;
        return nullptr;
    } else {//要删除的节点是尾节点，需要把待删除节点的父节点的子节点设置成nullptr--必须遍历一遍了
        ListNode* pNode = *pListHead;
        while (pNode->next != pToBeDeleted) {
            pNode = pNode->next;
        }
        pNode->next = nullptr;
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        return *pListHead;
    }
}

//----------------------------------删除链表中重复的节点--此处指定重复的节点是连续的------
void DeleteDuplication(ListNode** pHead) {
    if (pHead == nullptr || *pHead == nullptr) return;
    ListNode* pPreNode = nullptr;
    ListNode* pNode = *pHead;
    while (pNode) {
        ListNode* pNext = pNode->next;
        bool needDelete = false;
        if (pNext && pNode->val == pNext->val) needDelete = true;
        if (!needDelete) {
            pPreNode = pNode;
            pNode = pNode->next;
        } else {
            int value = pNode->val;
            ListNode* pToBeDelete = pNode;
            while (pToBeDelete && pToBeDelete->val == value) {
                pNext = pToBeDelete->next;
                delete pToBeDelete;
                pToBeDelete = nullptr;
                pToBeDelete = pNext;
            }

            if (pPreNode) {
                pPreNode->next = pNext;
            } else {
                *pHead = pNext;
            }
            pNode = pNext;
        }
    }
}

//-----------------链表中环的入口节点------
//先判断是否包含环，再求得环中节点个数，再使用快慢指针得到环的入口节点
//MeetingNode用于找到快慢指针在存在环的前提下找到相遇的节点
ListNode* MeetingNode(ListNode* pHead) {
    if (!pHead) return nullptr;
    ListNode* pSlow = pHead->next;
    if (!pSlow) return nullptr;
    ListNode* pFast = pSlow->next;
    while (pFast && pSlow) {
        if (pFast == pSlow) return pFast;
        pSlow = pSlow->next;
        pFast = pFast->next;
        if (pFast) pFast = pFast->next;
    }
    return nullptr;
}
//在找到环中任意一个节点之后就能得出环中节点数目，并找到环的入口节点
ListNode* EntryNodeOfLoop(ListNode* pHead) {
    ListNode* meetingNode = MeetingNode(pHead);
    if (!meetingNode) return nullptr;
    //得到环节点中的节点数目
    int nodesInLoop = 1;
    ListNode* pNode1 = meetingNode;
    while (pNode1->next != meetingNode) {
        ++nodesInLoop;
        pNode1 = pNode1->next;
    }
    //接下来就是、快慢指针相关
    pNode1 = pHead;
    for (int i = 0; i < nodesInLoop; ++i) pNode1 = pNode1->next;
    ListNode* pNode2 = pHead;
    while (pNode1 != pNode2) {
        pNode1 = pNode1->next;
        pNode2 = pNode2->next;
    }
    return pNode1;
}

#endif

/*包含min函数的栈*/
/*主要讲一下思路，利用辅助栈存储最小值，此处需要注意的思路是：
 * 每次新来一个数据的时候，如果此数据大于当前的最小值，那么辅助栈此时存入
 * 一个当前最小值的值，也就保证了辅助栈和数据栈尺寸相同，二辅助栈中包含多个连续相同的值，
 * 作为每个阶段的最小值*/


//三数之和
vector<vector<int>> threesum(vector<int>& nums, int target) {
    if (nums.size() < 3) return {};
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int len = nums.size();
    for (int i = 0; i < len; ++i) {
        if (nums[i] >= target) break;
        if (i > 0 && nums[i] == nums[i - 1]) continue;//去重
        int L = i + 1, R = len - 1;
        while (L < R) {
            int sum = nums[i] + nums[L] + nums[R];
            if (sum == target) {
                res.emplace_back(vector<int>{nums[i], nums[L], nums[R]});
                while (L < R && nums[L] == nums[L + 1]) ++L;//去重
                while (L < R && nums[R] == nums[R - 1]) --R;
            } else if (sum > target) {
                --R;
            } else {
                ++L;
            }
        }
    }
}




int main() {
    int myints[] = {1, 2, 3, 4, 5, 6};
    std::vector<int> vls(myints, myints + sizeof(myints) / sizeof(int));
    ListNode* head = CreateList(vls);
    ShowList(head);
    ListNode* pNode = head->next;
    delete head;
    ShowList(pNode);
    DeleteList(pNode);

    //std::vector<std::vector<int>> res = {};

    /*int i = 0;
    int* ptr = nullptr;
    std::cout << &i << " " << &ptr << std::endl;*/

    std::string s = "chen";
    int idx = s.size();
    if (s[idx] == '\0') {
        std::cout << "s[idx] is reachable" << std::endl;
    }



/*    //反转链表test
    int myints[] = {1, 2, 3, 4, 5, 6};
    std::vector<int> vls(myints, myints + sizeof(myints) / sizeof(int));
    ListNode* head = CreateList(vls);
*//*    const int s = vls.size();
    int array[4][s];
    int (*ptr_tmp)[s] = (int(*)[s])array;*//*
    ReverseListNode(&head);
    ReverseListNode_1(head);
    DeleteList(head);*/

/*  int x = 100;
    int tmp = x >> 1;
    std::cout << x << " " << tmp << '\n';//x >> 1不会更改x的值本身
*/

/*
    int y = INT32_MIN;
    int res = y & 0x1;
    std::cout << y << " " << -y << " " << res << '\n';//INT_MIN需定义成 -INT_MAX - 1, 因为-2147483648无法表示, 无法对2147483648取反
*/

/*
    int a = 1;
    int b = 2;
    char* ptr = reinterpret_cast<char*>(&a);
    std::cout << (int)*ptr << '\n';
    std::cout << &a << " " << (int*)ptr << " " << &b << '\n';
*/

/*
    std::vector<int> vec{1, 2, 4, -1, 6, -1, -1, -1, 3, -1, 5, 7, -1, -1, -1};
    int index = 0;
    TreeNode* root = CreateTreeRecursion(vec, index);
    std::cout << "bfs res: ";
    bfsTree(root);
    std::cout << '\n';
    std::cout << "dfs res: ";
    dfsTree(root);
    std::cout << '\n';
    DeleteTree(root);
*/


    /*bool flag = true;
    flag != flag;
    std::cout << flag << '\n';*/



    return 0;
}

