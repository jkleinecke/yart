/**
 * refcounted.h
 */
#pragma once

#include <atomic>

namespace yart {

	class RefCounted
	{
	protected:
		RefCounted() : m_nRefCount(1) {}
		virtual ~RefCounted() {}

	public:
		void Retain() const
		{
			std::atomic_fetch_add_explicit(&m_nRefCount, 1u, std::memory_order_relaxed) ;
		}
		void Release() const
		{
			if( std::atomic_fetch_sub_explicit(&m_nRefCount, 1u, std::memory_order_release) == 1)
			{
				std::atomic_thread_fence(std::memory_order_acquire) ;
				delete this ;
			}
		}

	private:
		mutable std::atomic<unsigned> m_nRefCount ;
	} ;
}