#include <iostream>
#include <cassert>

class List
{
public:

    List() : m_head(nullptr), m_tail(nullptr) { }

    ~List()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    bool empty() const
    {
        return m_head == nullptr;
    }

    void show() const
    {
        Node* current = m_head;
        while (current != nullptr)
        {
            std::cout << current->value << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    void push_front(int val)
    {
        Node* node = new Node(val);
        if (empty())
        {
            m_head = node;
            m_tail = node;
        }
        else
        {
            node->next = m_head;
            m_head = node;
        }
    }

    void push_back(int val)
    {
        Node* node = new Node(val);
        if (empty())
        {
            m_head = node;
            m_tail = node;
        }
        else
        {
            m_tail->next = node;
            m_tail = node;
        }
    }

    void pop_front()
    {
        if (empty())
        {
            return;
        }
        Node* tmp = m_head;
        m_head = m_head->next;
        delete tmp;
        if (m_head == nullptr)
        {
            m_tail = nullptr;
        }
    }

    void pop_back() {
        if (empty())
        {
            return;
        }
        if (m_head == m_tail)
        {
            delete m_head;
            m_head = m_tail = nullptr;
            return;
        }
        Node* current = m_head;
        while (current->next != m_tail)
        {
            current = current->next;
        }
        delete m_tail;
        m_tail = current;
        m_tail->next = nullptr;
    }

    int get() const
    {
        if (empty())
        {
            return 0;
        }
        Node* slow = m_head;
        Node* fast = m_head;
        Node* prev = nullptr;
        while (fast != nullptr && fast->next != nullptr)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        return (fast == nullptr && prev != nullptr) ? prev->value : slow->value;
    }

private:
    struct Node
    {
        int value;
        Node* next;

        Node(int val) : value(val), next(nullptr) { }
    };

    Node* m_head;
    Node* m_tail;
};

int main()
{
    List list;
    assert(list.empty());

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    assert(!list.empty());
    assert(list.get() == 3); // middle element

    list.push_front(0);
    assert(list.get() == 2); // middle element after pushing front 0

    list.pop_front();
    assert(list.get() == 3); // middle element after popping front 0

    list.push_back(6);
    list.push_back(7);
    assert(list.get() == 4); // middle element after pushing back 6 and 7

    list.pop_back();
    assert(list.get() == 3); // middle element after popping back 7
}

