#pragma once

#include "common.h"

template <class Type>
class UniqueList
{
public:

    UniqueList() :
        m_delete_duplicates(true)
    {

    }

    Type add(Type item)
    {
        if(contains(item))
        {
            Type existing_item = getItem(item);

            /*
            if(m_delete_duplicates)
            {
                DeleteAObject(item);
            }
            */

            return existing_item;
        }

        m_items.push_back(item);

        return item;
    }

    void remove(Type item)
    {
        for(auto it = m_items.begin(); it != m_items.end(); ++it)
        {
            if(*it.equals(item))
            {
                m_items.erase(it);
                break;
            }
        }
    }

    Type getItem(Type item)
    {
        for(Type current_item : m_items)
        {
            if(current_item->equals(item))
            {
                return current_item;
            }
        }

        return nullptr;
    }

    bool contains(Type item)
    {
        for(Type current_item : m_items)
        {
            if(current_item->equals(item))
            {
                return true;
            }
        }

        return false;
    }

    void clear()
    {
        m_items.clear();
    }

    const std::vector<Type>& getItems() const
    {
        return m_items;
    }

    void setDeleteDuplicates(bool delete_duplicates)
    {
        m_delete_duplicates = delete_duplicates;
    }

    bool getDeleteDuplicates() const
    {
        return m_delete_duplicates;
    }

protected:

    std::vector<Type> m_items;

    bool m_delete_duplicates;

};
