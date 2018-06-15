#include <memory>
#include <cstddef>
#include <cstring>

namespace btree
{
    template <typename TK,typename TV, int M>
    struct BTreeNode
    {
        using NodeType = BTreeNode<TK, TV, M>;
        using NodeIndex = BTreeNode<TK, TV, M> *;
        TK keys[M];
        TV values[M];
        NodeIndex sub[M];
        NodeIndex parent;
        NodeIndex next;
        std::size_t size;
        BTreeNode()
            :parent(nullptr), size(0)
        {
            memset(sub, M * sizeof(NodeType *), 0);
        }
    };

    template <typename TK,typename TV, int M>
    BTreeNode<TK, TV, M> readNode(BTreeNode<TK, TV, M>::NodeIndex idx)
    {
        return *idx;
    }

    template <typename TK,typename TV, int M>
    BTreeNode<TK, TV, M>::NodeIndex createNode()
    {
        return new BTreeNode();
    }

    template <typename TK,typename TV, int M>
    void releaseNode(BTreeNode<TK, TV, M>::NodeIndex idx)
    {
        delete idx;
    }
}