/**
 * runloop_mgr.h - Run loop management interface
 */
#pragma once

#include "runloop.h"
#include <map>
#include <thread>
#include <mutex>

namespace yart {

	class RunLoopManager
	{
	public:
		RunLoopManager() ;
		~RunLoopManager() ;

		bool CreateRunLoop() ;

		RunLoop* GetCurrentRunLoop() const ;
		RunLoop* GetRunLoopForThread(std::thread::id id) const ;

	private:
		mutable std::mutex m_loopMutex ;
		std::map<std::thread::id, RunLoop*> m_mapLoops ;
	} ;
}