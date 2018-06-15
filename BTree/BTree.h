#include <BTreeNode.h>

namespace btree
{
    template <typename TK, typename TV, int M>
    class BTree
    {
        using NodeType = BTreeNode<TK, TV, M>;
        using NodeIndex = BTreeNode<TK, TV, M>::NodeIndex;
    public:
        BTree()
        {
            root = createNode();
        }
        BTree(const BTree& other)=delete;
        BTree(BTree&& other)=delete;
        BTree& operator=(const BTree& other)=delete;
        BTree& operator=(BTree&& r)=delete;
        ~BTree()
        {
            releaseNode(root);
        }

        std::pair<NodeType, int>* find(const TK &key)
        {
            NodeIndex cur = root;
            NodeIndex parent = nullptr;
            while (cur)
            {
                size_t i = 0;
                while (i < cur->size)
                {
                    if (cur->keys[i] < key)
                    {
                        i++;
                    }
                    else if (cur->keys[i] > key)
                    {
                        cur = cur->sub[i];
                        parent = cur;
                        break;
                    }
                    else
                    {
                        return std::make_pair(cur, i);
                    }
                }

                if (cur != nullptr && i == cur->size)
                {
                    cur = cur->sub[i];
                    parent = cur;
                }
            }

            return std::make_pair(nullptr, 0);
        }

        bool insert(const TK &key)
        {
            NodeType* cur = root;
            NodeType* parent = nullptr;
            while(cur)
            {
                std::size_t i = 0;
                while(i < cur->size)
                {
                    if(key < cur->keys[i])
                    {

                    }
                    else if(key > cur->keys[i])
                    {

                    }
                    else
                    {
                        return 
                    }
                }
            }
        }
    private:
        NodeType *root;
    };
}