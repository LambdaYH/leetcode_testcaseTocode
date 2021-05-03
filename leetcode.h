#pragma once
#ifndef LEETCODE_H
#define LEETCODE_H

#include <initializer_list>
#include <queue>
/**
 * 
 * DataStruct's in leetcode
 * 
*/
namespace leetcode
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
}

/**
 * 
 * Conversion functions
 * 
*/
namespace leetcode
{
    leetcode::TreeNode *Tree(std::initializer_list<int> nodes)
    {
        std::queue<leetcode::TreeNode> q;
        leetcode::TreeNode *root = nullptr;
        for (const auto &nodeVal : nodes)
        {
            if (q.empty())
                q.push(root = new leetcode::TreeNode(nodeVal));
            else
            {
                auto curNode = q.front();
                if (!curNode->left)
                    q.push(curNode->left = new leetcode::TreeNode(nodeVal));
                else if (!curNode->right)
                {
                    q.push(curNode->right = new leetcode::TreeNode(nodeVal));
                    q.pop();
                }
            }
        }
        return root;
    }
    leetcode::ListNode *LinkedList(std::initializer_list<int> nodes)
    {
        leetcode::ListNode *head = new ListNode();
        leetcode::ListNode pseudoHead = head;
        for (const auto &nodeVal : nodes)
        {
            head->next = new ListNode(nodeVal);
            head = head->next;
        }
        auto res = pseudoHead->next;
        delete pseudoHead;
        return res;
    }
}
#endif