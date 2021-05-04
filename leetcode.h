#pragma once
#ifndef LEETCODE_H
#define LEETCODE_H

#include <queue>
#include <string>
#include <vector>
#include <memory>
/**
 * 
 * Tree(string) ： return root of Tree
 * 
 * LinkedListNode(string) : return head of LinkedListNode
 * 
 * 
*/

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
 * some functions
 *
*/
namespace leetcode
{
    bool isDigitalOrCharacter(const char &ch)
    {
        return ('0' <= ch && '9' >= ch) || ('a' <= ch && 'z' >= ch) || ch == '-';
    }

    bool isSplitCondition(const char &ch)
    {
        return ch == ',' || ch == ']';
    }

    template <typename T>
    void eraseQueue(std::queue<T> &q)
    {
        while (!q.empty())
            q.pop();
    }

    std::vector<std::shared_ptr<int>> parseString(std::string &s)
    {
        std::queue<char> cache;
        std::vector<std::shared_ptr<int>> res;
        auto &begin = s.begin();
        auto &end = s.end() - 1;
        while (*begin != '[')
            ++begin;
        while (*end != ']')
            --end;
        ++begin;
        for (; begin != end + 1; ++begin)
        {
            if (isSplitCondition(*begin))
            {
                int realNum = 0;
                int positive = 1;
                if (cache.empty())
                    return {};
                if (cache.front() == '-')
                {
                    positive = -1;
                    cache.pop();
                }
                while (!cache.empty())
                {
                    realNum = realNum * 10 + static_cast<int>(cache.front() - '0');
                    cache.pop();
                }
                if (realNum == 69560) // null
                    res.push_back(nullptr);
                else
                    res.push_back(std::make_shared<int>(realNum * positive));
            }
            else if (isDigitalOrCharacter(*begin))
            {
                cache.push(*begin);
            }
        }
        return res;
    }
}
/**
 *
 * Conversion functions
 *
*/
namespace leetcode
{
    leetcode::TreeNode *Tree(std::string e)
    {
        std::queue<leetcode::TreeNode *> q;
        auto nodes = parseString(e);
        leetcode::TreeNode *root = nullptr;
        bool leftNotIn = true;
        for (const auto &node : nodes)
        {
            if (q.empty())
                q.push(root = new leetcode::TreeNode(*node));
            else
            {
                auto curNode = q.front();
                if (!curNode->left && leftNotIn)
                {
                    if (node)
                        q.push(curNode->left = new leetcode::TreeNode(*node));
                    else
                        curNode->left = nullptr;
                    leftNotIn = false;
                }
                else if (!curNode->right)
                {
                    if (node)
                        q.push(curNode->right = new leetcode::TreeNode(*node));
                    else
                        curNode->right = nullptr;
                    q.pop();
                    leftNotIn = true;
                }
            }
        }
        return root;
    }
    leetcode::ListNode *LinkedList(std::string e)
    {
        leetcode::ListNode *head = new ListNode();
        leetcode::ListNode *pseudoHead = head;
        auto nodes = parseString(e);
        for (const auto &node : nodes)
        {
            if (node)
            {
                head->next = new ListNode(*node);
                head = head->next;
            }
            else
                return nullptr;
        }
        auto res = pseudoHead->next;
        delete pseudoHead;
        return res;
    }
}
#endif
