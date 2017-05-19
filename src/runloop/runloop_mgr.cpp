/**
 * runloop_mgr.cpp 
 */
#include "runtime.h"
#include "runloop_mgr.h"

using namespace yart ;

RunLoopManager::RunLoopManager()
{

}

RunLoopManager::~RunLoopManager()
{
	for(auto pair : m_mapLoops)
	{
		pair.second->Release() ;
	}

	m_mapLoops.clear() ;
}

bool RunLoopManager::CreateRunLoop()
{
	auto id = std::this_thread::get_id() ;
	RunLoop* newLoop = new RunLoop() ;

	std::lock_guard<std::mutex> guard(m_loopMutex) ;
	if(m_mapLoops.find(id) == m_mapLoops.end())	// make sure this is the only run loop on the thread
	{
		m_mapLoops[id] = newLoop ;
		return true ;
	}

	return false ;
}

RunLoop* RunLoopManager::GetCurrentRunLoop() const 
{
	return GetRunLoopForThread( std::this_thread::get_id() ) ;
}

RunLoop* RunLoopManager::GetRunLoopForThread(std::thread::id id) const 
{
	std::lock_guard<std::mutex> guard(m_loopMutex) ;
	RunLoop* ptr = nullptr ;

	auto findIt = m_mapLoops.find(id) ;
	if( findIt != m_mapLoops.end() )
	{
		ptr = findIt->second ;
	}

	return ptr ;
}