template <typename TItemType>
LinkedList<TItemType>::LinkedList() :
    count_(0),
    head_(NULL),
    tail_(NULL)
{

}

template <typename TItemType>
LinkedList<TItemType>::~LinkedList() 
{
    clear();
}

template <typename TItemType>
size_t LinkedList<TItemType>::add(const TItemType item)
{
    ListNode* newNode = createNode();
    newNode->value = item;

    if(head_ != NULL)
    {
        tail_->next = newNode;
        tail_ = newNode;    
    } 
    else 
    {
        head_ = tail_ = newNode;
    }

    ++count_;
    return count_;
}

template <typename TItemType>
void LinkedList<TItemType>::addRange(const TItemType* array, size_t count)
{
    for(int i = 0; i < count; i++)
    {
        add(array[i]);
    }
}

template <typename TItemType>
void LinkedList<TItemType>::insert(size_t index, const TItemType item)
{
    BOUNDS_CHECK(count_ + 1, index);

    if(index == count_)
    {
        add(item);
        return;   
    }

    ListNode* newNode = createNode();
    newNode->value = item;

    if (index == 0)
    {
        newNode->next = head_;
        head_ = newNode;
    }
    else 
    {
        ListNode* prevNode = nodeAt(index - 1);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }

    ++count_;
}

template <typename TItemType>
void LinkedList<TItemType>::remove(size_t index)
{
    BOUNDS_CHECK(count_, index);

    if(index > 0)
    {
        ListNode* prev = nodeAt(index - 1);
        ListNode* next = prev->next->next;
        
        if(tail_ == prev->next)
        {
            tail_ = prev;
        }

        freeNode(prev->next);
        prev->next = next;        
    }
    else 
    {
        ListNode* next = head_->next;
        
        if(tail_ == head_)
        {
            tail_ = NULL;
        }

        freeNode(head_);
        head_ = next;
    }

    --count_;
}

template <typename TItemType>
void LinkedList<TItemType>::set(size_t index, const TItemType item)
{
    BOUNDS_CHECK(count_, index);

    nodeAt(index)->value = item;
}

template <typename TItemType>
TItemType LinkedList<TItemType>::get(size_t index) const
{
    BOUNDS_CHECK(count_, index);

    return nodeAt(index)->value;
}

template <typename TItemType>
TItemType& LinkedList<TItemType>::operator[](const size_t index)
{
    return nodeAt(index)->value;
}

template <typename TItemType>
void LinkedList<TItemType>::clear()
{
    while(count_ > 0)
        remove(0);
}

template <typename TItemType>       
size_t LinkedList<TItemType>::count() const
{
    return count_;
}

template <typename TItemType>       
typename LinkedList<TItemType>::ListNode* LinkedList<TItemType>::nodeAt(size_t index) const
{
    BOUNDS_CHECK(count_, index);

    LinkedList<TItemType>::ListNode* cursor = head_;

    for(int i = 0; i < index; i++)
        cursor = cursor->next;

    return cursor;
}

template <typename TItemType>       
typename LinkedList<TItemType>::ListNode* LinkedList<TItemType>::createNode()
{
    LinkedList<TItemType>::ListNode* node = reinterpret_cast<LinkedList<TItemType>::ListNode* >(Memory::allocate(sizeof(LinkedList<TItemType>::ListNode)));
    node->next = NULL;
    return node;
}

template <typename TItemType>
void LinkedList<TItemType>::freeNode(LinkedList<TItemType>::ListNode*  node)
{
    Memory::free(node);
}

template <typename TItemType>
TItemType LinkedList<TItemType>::read(ptr_t state) const
{
    return reinterpret_cast<LinkedList<TItemType>::ListNode*>(state)->value;
}

template <typename TItemType>
bool_t LinkedList<TItemType>::next(ptr_t* state) const
{
    if(*state == NULL)
    {
        return (*state = head_) != NULL;
    }

    return *state != NULL && 
        (*state = reinterpret_cast<LinkedList<TItemType>::ListNode*>(*state)->next) != NULL; 
}