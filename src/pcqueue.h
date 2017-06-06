/**
 * pcqueue.h - Header for a single producer, single consumer lock-free queue
 */
#pragma once

#include <atomic>
#include <algorithm>

template<typename Element, size_t Size>
class ProducerConsumerQueue
{
public:
	enum { Capacity = Size+1 } ;

	ProducerConsumerQueue()	: m_Tail(0), m_Head(0) {}
	~ProducerConsumerQueue() {}

	bool push(const Element& item)
	{
		const auto tail = m_Tail.load(std::memory_order_relaxed) ;
		const auto next_tail = increment(tail) ;

		// first check to see if we are at the end
		if( next_tail == m_Head.load(std::memory_order_acquire) )
			return false ;

		// still room... store the item and increment the tail
		m_Elements[tail] = std::move(item) ;
		m_Tail.store(next_tail, std::memory_order_release) ;

		return true ;	// Success!
	}

	bool pop(Element& refItem)
	{
		const auto head = m_Head.load(std::memory_order_relaxed) ;

		// are there any items left in the queue?
		if( head == m_Tail.load(std::memory_order_acquire) )
			return false ;

		// still have some items
		refItem = std::move(m_Elements[head]) ;
		m_Head.store(increment(head), std::memory_order_release) ;

		return true ;	// Success!
	}

	bool wasEmpty() const
	{
		return m_Head.load() == m_Tail.load() ;
	}

	bool wasFull() const
	{
		const auto next_tail = increment(m_Tail.load()) ;
		return next_tail == m_Head.load() ;
	}
	bool isLockFree() const
	{
		return m_Head.is_lock_free() && m_Tail.is_lock_free() ;
	}

private:
	size_t increment(size_t index) const
	{
		return (index + 1) % Capacity ;
	}

	// For better Multi-CPU cache sync performance,
	// keep the variables ordered this way Tail - Array - Head
	// Putting the tail and head next to each other in memory
	// can cause the CPU to thrash the L1 cash of another core
	std::atomic<size_t> 	m_Tail ;
	Element					m_Elements[Capacity] ;
	std::atomic<size_t>		m_Head ;
} ;
