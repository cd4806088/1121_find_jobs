//
// Created by chenda on 2021/3/12.
//
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;
};
//--------------前序遍历---递归----
void PreorderTraversal_Recursion(TreeNode* node) {
    if (!node) return;
    printf("%d\n", node->val);
    PreorderTraversal_Recursion(node->left);
    PreorderTraversal_Recursion(node->right);
    return;
}

//以下两种迭代方法还是有很大不同，在序列化处理前序遍历结果时会有较大差异

//-------------前序遍历---迭代方法一-----------------------------
void PreorderTraversal_Non_Recursion(TreeNode* node) {
    if (!node) return;
    std::stack<TreeNode*> s;
    while (node || !s.empty()) {
        while (node) {
            printf("%d\n", node->val);
            s.push(node);
            node = node->left;
        }
        if (!s.empty()) {
            node = s.top();
            s.pop();
            node = node->right;
        }
    }
    return;
}

//------------前序遍历---迭代方法二-----------------------------
//既然要压入堆栈，就要先压右子节点，再压左子节点
//仔细感受一下压栈的过程
std::vector<int>& preorderTraversal(TreeNode* root, std::vector<int>& res) {
    res.clear();
    if (!root) return res;
    std::stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        res.emplace_back(node->val);
        //此处前序遍历压栈先压右节点再压左节点，来保证先访问左节点
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
    return res;
}




//--------------中序遍历---递归----
void InorderTraversal_Recursion(TreeNode* node) {
    if (!node) return;
    InorderTraversal_Recursion(node->left);
    printf("%d\n", node->val);
    InorderTraversal_Recursion(node->right);
    return;
}

//-------------中序遍历---迭代方法一-----------------------------
void InorderTravelsal_Non_Recursion(TreeNode* node) {
    if (!node) return;
    std::stack<TreeNode*> s;
    while (node || !s.empty()) {
        while (node) {
            s.push(node);
            node = node->left;
        }
        if (!s.empty()) {
            node = s.top();
            s.pop();
            printf("%d\n", node->val);
            node = node->right;
        }
    }
    return;
}

//-------------中序遍历---迭代方法二-----------------------------
std::vector<int>& inorderTraversal(TreeNode* root, std::vector<int>& res) {
    res.clear();
    if (!root) return res;
    std::stack<TreeNode*> st;
    TreeNode* curr = root;
    while (curr || !st.empty()) {
        if (curr) {
            st.push(curr);
            curr = curr->left;
        } else {
            curr = st.top();
            st.pop();
            res.emplace_back(curr->val);
            curr = curr->right;
        }
    }
    return res;
}


//--------------后序遍历---递归----
void PostTraversal_Recursion(TreeNode* node) {
    if (!node) return;
    PostTraversal_Recursion(node->left);
    PostTraversal_Recursion(node->right);
    printf("%d\n", node->val);
    return;
}

//-------------后序遍历---迭代方法一-----------------------------
void PostTravelsal_Non_Recursion(TreeNode* node) {
    if (!node) return;
    TreeNode* pre = nullptr;
    std::stack<TreeNode*> s;
    while (node || !s.empty()) {
        while (node) {
            s.push(node);
            node = node->left;
        }
        node = s.top();
        //对于所有节点都是：左右子树为空，或者右子树为上一个被遍历的点-----
        //满足以上两个条件之一当前节点将会被遍历
        if (node->right == nullptr || node->right == pre) {
            pre = node;
            printf("%d\n", node->val);
            s.pop();
            node = nullptr;
        } else {
            node = node->right;
        }
    }
    return;
}


//-------------后序遍历---迭代方法二-----------------------------
//-----前序遍历是中左右-->>调整代码压栈顺序--->>中右左---->>左右中--->>就是后序遍历的结果
std::vector<int>& postorderTraversal(TreeNode* root, std::vector<int>& res) {
    res.clear();
    if (!root) return res;
    std::stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        res.emplace_back(node->val);
        //相比于前序遍历这里更改一下入栈顺序，空节点不入栈
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
    }
    std::reverse(res.begin(), res.end());
    return res;
}


int main() {
    return 0;
}
