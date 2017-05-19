/**
 * runloop.cpp - Implementation of RunLoop class
 */

#include "runloop.h"

using namespace yart ;

RunLoop::RunLoop()
{

}

RunLoop::~RunLoop()
{

}

/**
 * @brief Executes each worker on the run loop
 */
void RunLoop::Execute()
{
	for(auto& worker: m_aWorkers)
	{
		worker() ;
	}
}

/**
 * @brief Adds a worker to the loop
 * 
 * @param worker Function to execute for the worker
 */
void RunLoop::AddWorker(std::function<void()> worker)
{
	m_aWorkers.push_back(worker) ;	
}