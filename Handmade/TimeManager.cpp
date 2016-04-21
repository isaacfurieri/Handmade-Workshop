#include <iomanip>
#include <iostream>
#include <SDL.h>
#include "TimeManager.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all defaults using the Reset function
//------------------------------------------------------------------------------------------------------
TimeManager::TimeManager()
{

	Reset();

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in milliseconds
//------------------------------------------------------------------------------------------------------
double TimeManager::GetElapsedTimeMilliseconds() const
{

	return m_elapsedTimeMilliseconds;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in seconds
//------------------------------------------------------------------------------------------------------
double TimeManager::GetElapsedTimeSeconds() const
{

	return m_elapsedTimeSeconds;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in minutes
//------------------------------------------------------------------------------------------------------
double TimeManager::GetElapsedTimeMinutes() const
{

	return m_elapsedTimeMinutes;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns time elapsed in hours
//------------------------------------------------------------------------------------------------------
double TimeManager::GetElapsedTimeHours() const
{

	return m_elapsedTimeHours;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in milliseconds
//------------------------------------------------------------------------------------------------------
double TimeManager::GetTotalTimeMilliseconds() const
{

	return m_totalTimeMilliseconds;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in seconds
//------------------------------------------------------------------------------------------------------
double TimeManager::GetTotalTimeSeconds() const
{

	return m_totalTimeSeconds;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in minutes
//------------------------------------------------------------------------------------------------------
double TimeManager::GetTotalTimeMinutes() const
{

	return m_totalTimeMinutes;

}
//------------------------------------------------------------------------------------------------------
//getter function that returns total time passed in hours
//------------------------------------------------------------------------------------------------------
double TimeManager::GetTotalTimeHours() const
{

	return m_totalTimeHours;

}
//------------------------------------------------------------------------------------------------------
//function that starts the timer running 
//------------------------------------------------------------------------------------------------------
void TimeManager::Start()
{

	//only if timer is not already running then start timer
	//by assigning current SDL clock ticks and timer running flag
	if (!m_isTimerRunning)
	{
		m_startTime = (double)SDL_GetTicks();
		m_lastTime = (double)SDL_GetTicks();
		m_isTimerRunning = true;
	}

}
//------------------------------------------------------------------------------------------------------
//function that pauses the timer
//------------------------------------------------------------------------------------------------------
void TimeManager::Pause()
{

	//only if timer is running and not already paused then pause it
	//by resetting all elapsed time variables and assign timer paused flag
	if (m_isTimerRunning && !m_isTimerPaused)
	{
		m_elapsedTimeMilliseconds = 0.0;
		m_elapsedTimeSeconds = 0.0;
		m_elapsedTimeMinutes = 0.0;
		m_elapsedTimeHours = 0.0;
		m_isTimerPaused = true;
	}

}
//------------------------------------------------------------------------------------------------------
//function that resumes the timer
//------------------------------------------------------------------------------------------------------
void TimeManager::Resume()
{

	//only if timer is running and paused then resume it
	//by assigning current SDL clock ticks and timer paused flag
	if (m_isTimerRunning && m_isTimerPaused)
	{
		m_lastTime = (double)SDL_GetTicks();
		m_isTimerPaused = false;
	}

}
//------------------------------------------------------------------------------------------------------
//function that stops the timer
//------------------------------------------------------------------------------------------------------
void TimeManager::Stop()
{

	//only if timer is already running then stop 
	//and reset it by using the Reset function
	if (m_isTimerRunning)
	{
		Reset();
	}

}
//------------------------------------------------------------------------------------------------------
//function that calculates the total and elapsed time
//------------------------------------------------------------------------------------------------------
void TimeManager::Update()
{

	//only if timer is running then do elapsed and total time calculations
	//if timer is NOT paused then calculate the elapsed time
	//total time calculations are done even if timer is paused as long as its running
	if (m_isTimerRunning)
	{

		if (!m_isTimerPaused)
		{
			
			//calculate time passed since last function call 
			//this uses the current SDL real time and last time recorded earlier
			double elapsedTime = (double)SDL_GetTicks() - m_lastTime;

			//convert elapsed time from milliseconds into four time formats
			m_elapsedTimeMilliseconds = elapsedTime;
			m_elapsedTimeSeconds = elapsedTime / 1000;
			m_elapsedTimeMinutes = elapsedTime / 60000;
			m_elapsedTimeHours = elapsedTime / 3600000;

			//reset variable for use in next function call
			m_lastTime = SDL_GetTicks();

		}
		
		//calculate total time passed since timer was started
		//this uses the current SDL real time and start time recorded earlier
		double totalTime = (double)SDL_GetTicks() - m_startTime;

		//convert total time from milliseconds into four time formats
		m_totalTimeMilliseconds = totalTime;
		m_totalTimeSeconds = totalTime / 1000;
		m_totalTimeMinutes = totalTime / 60000;
		m_totalTimeHours = totalTime / 3600000;

	}

}
//------------------------------------------------------------------------------------------------------
//function that displays all elapsed and total time on console window
//------------------------------------------------------------------------------------------------------
void TimeManager::Output()
{

	//clear the console window screen
	system("cls");
	std::cout << "--------------------------------------" << std::endl;

	//state if timer is running and (not) paused
	if (m_isTimerRunning)
	{
		std::cout << "Timer is RUNNING";
		std::cout << (m_isTimerPaused ? " and PAUSED" : "") << std::endl;
	}

	//state if timer is not running
	else
	{
		std::cout << "Timer is OFF" << std::endl;
	}	
	
	std::cout << "--------------------------------------" << std::endl;

	//set output text to display in floating point 
	//format with a five decimal point precision
	std::cout << std::fixed << std::setprecision(5);

	//display all elapsed time data
	std::cout << "Elapsed time (MS) : " << m_elapsedTimeMilliseconds << std::endl;
	std::cout << "Elapsed time (S)  : " << m_elapsedTimeSeconds << std::endl;
	std::cout << "Elapsed time (M)  : " << m_elapsedTimeMinutes << std::endl;
	std::cout << "Elapsed time (H)  : " << m_elapsedTimeHours << std::endl;

	std::cout << "--------------------------------------" << std::endl;

	//display all total time data
	std::cout << "Total time (MS) : " << m_totalTimeMilliseconds << std::endl;
	std::cout << "Total time (S)  : " << m_totalTimeSeconds << std::endl;
	std::cout << "Total time (M)  : " << m_totalTimeMinutes << std::endl;
	std::cout << "Total time (H)  : " << m_totalTimeHours << std::endl;

	std::cout << "--------------------------------------" << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that resets all variables to their default values
//------------------------------------------------------------------------------------------------------
void TimeManager::Reset()
{

	m_isTimerRunning = false;
	m_isTimerPaused = false;

	m_startTime = 0.0;
	m_lastTime = 0.0;

	m_elapsedTimeMilliseconds = 0.0;
	m_elapsedTimeSeconds = 0.0;
	m_elapsedTimeMinutes = 0.0;
	m_elapsedTimeHours = 0.0;

	m_totalTimeMilliseconds = 0.0;
	m_totalTimeSeconds = 0.0;
	m_totalTimeMinutes = 0.0;
	m_totalTimeHours = 0.0;

}