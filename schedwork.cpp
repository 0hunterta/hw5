#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helperSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftCount, size_t day, size_t slot);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
	size_t nDays = avail.size();
	if(nDays == 0) return false;
	size_t nWorkers = avail[0].size();
	sched.assign(nDays, vector<Worker_T>(dailyNeed, INVALID_ID));
	vector<size_t> shiftCount(nWorkers, 0);
	return helperSchedule(avail,dailyNeed,maxShifts,sched,shiftCount,0,0);
}
bool helperSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<size_t>& shiftCount, size_t day, size_t slot)
{
	size_t nDays = avail.size();
	if(day == nDays) return true;
	if(slot == dailyNeed) return helperSchedule(avail, dailyNeed, maxShifts, sched, shiftCount, day+1, 0);
	size_t nWorkers = avail[day].size();
	for(Worker_T w=0; w<nWorkers; ++w) {
		if(!avail[day][w] || shiftCount[w] >= maxShifts) continue;
		bool already = false;
		for(size_t i=0; i<slot; ++i) {
			if(sched[day][i] == w) {
				already = true;
				break;
			}
		}
		if(already) continue;
		sched[day][slot] = w;
		shiftCount[w]++;
		if(helperSchedule(avail, dailyNeed, maxShifts, sched, shiftCount, day, slot+1)) return true;
		shiftCount[w]--;
		sched[day][slot] = INVALID_ID;
	}
	return false;
}
