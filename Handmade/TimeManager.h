/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : November 2015

  -----------------------------------------------------------------------------------------------

- This is a Timing class that keeps track of all time passed. It records elapsed time which 
  is great for frame independent games, where physics or graphics updates rely on time instead
  of frame rate. The class also keeps track of total time passed since the game first started.
  The class is a Singleton because it is a Manager class and will be accessed from anywhere in 
  the code. The important thing to note is that while the timer can be manually turned on and
  off, the actual SDL time that it relies on will continue to tick. 
  
- The Start() function will start off the timer from scratch, and the Stop() routine will reset
  the timer back to 0 altogether. The Pause() routine will reset the elapsed time only, keeping
  the total time calculating. This is because when pausing a game, the elapsed time may not be 
  needed because updating is paused. However the total time may still be needed. The Resume()
  function will restart the elapsed timing and the total time continues as normal.

- All the main elapsed and total timing calculations happen inside the Update() function. This 
  routine needs to be called from inside the main game's Update() routine. 

- The Output() function is for debug purposes and displays all the time data on the console window.

*/

#ifndef TIME_CONTROLLER_H
#define TIME_CONTROLLER_H

#include "Singleton.h"

class TimeManager
{

public:

	friend class Singleton<TimeManager>;

public:

	double GetElapsedTimeMilliseconds()  const;
	double GetElapsedTimeSeconds()       const;
	double GetElapsedTimeMinutes()       const;
	double GetElapsedTimeHours()         const;

	double GetTotalTimeMilliseconds()    const;
	double GetTotalTimeSeconds()         const;
	double GetTotalTimeMinutes()         const;
	double GetTotalTimeHours()           const;

public:

	void Start();
	void Pause();
	void Resume();
	void Stop();
	void Update();
	void Output();

private:

	void Reset();

private:

	TimeManager();
	TimeManager(const TimeManager&);
	TimeManager& operator=(const TimeManager&);

private:

	bool m_isTimerRunning;
	bool m_isTimerPaused;

	double m_startTime;
	double m_lastTime;

	double m_elapsedTimeMilliseconds;
	double m_elapsedTimeSeconds;
	double m_elapsedTimeMinutes;
	double m_elapsedTimeHours;

	double m_totalTimeMilliseconds;
	double m_totalTimeSeconds;
	double m_totalTimeMinutes;
	double m_totalTimeHours;

};

typedef Singleton<TimeManager> TheTime;

#endif