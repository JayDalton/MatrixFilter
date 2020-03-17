﻿#pragma once

#include <boost/circular_buffer.hpp>

template<typename Type>
struct BufferedQueue
{
   BufferedQueue(std::size_t capacity, std::size_t lineSize = 1)
      : m_capacity(capacity * lineSize), m_lineSize(lineSize)
      , m_source(capacity), m_target(capacity)
   {
   }

   void append(const Type& value)
   {
      m_sourceCounter = std::min(m_sourceCounter + 1, getCapacity());
      m_source.push_back(value);
   }

   void append(Type&& value)
   {
      m_sourceCounter = std::min(m_sourceCounter + 1, getCapacity());
      m_source.push_back(std::move(value));
   }

   const std::size_t getCapacity() const
   {
      return m_capacity;
   }

   const std::size_t getLineSize() const
   {
      return m_lineSize;
   }

   const std::size_t getStoredItemSize() const
   {
      return m_target.size();
   }

   const std::size_t getStoredLineSize() const
   {
      const std::size_t needless = getStoredItemSize();
      return needless ? ((needless - 1) / m_lineSize) + 1 : 0u;
   }

   bool isEmpty() const
   {
      return m_target.empty();
   }

   const Type& getElement(int index) const
   {
      return m_target.at(index);
   }

   void clear()
   {
      m_target.clear();
   }

   const std::size_t getAvailableItemSize() const
   {
      const std::size_t freeSize = m_target.reserve();
      const std::size_t tailSize = getBufferedItemSize();
      return (freeSize < tailSize) ? (tailSize - freeSize) : 0u;
   }

   void removeNeedlessHead()
   {
      const std::size_t needless = getAvailableItemSize();
      m_target.erase(m_target.begin(), m_target.begin() + needless);
   }

   const std::size_t getBufferedItemSize() const
   {
      return std::clamp(m_sourceCounter, 0u, m_source.capacity());
   }

   void appendBufferedTail()
   {
      if (const auto tailSize = getBufferedItemSize())
      {
         std::copy(
            std::make_move_iterator(m_source.end() - tailSize),
            std::make_move_iterator(m_source.end()),
            std::back_inserter(m_target)
         );
      }
      m_sourceCounter = 0;
   }

private:
   const std::size_t m_capacity;
   const std::size_t m_lineSize;
   std::size_t m_sourceCounter{0};
   boost::circular_buffer<Type> m_source;
   boost::circular_buffer<Type> m_target;
};


// Codepage: UTF-8 (ÜüÖöÄäẞß)
