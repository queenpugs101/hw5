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
bool schedBuilder(  const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, vector<int>& shiftsWorked, 
    size_t currentDay, size_t currentWorker);


// Add your implementation of schedule() and other helper functions here
/**
 * @brief Produces a work schedule given worker availability,
 *        the number of needed workers per day, and the maximum 
 *        shifts any single worker is allowed. Returns true if
 *        and the valid schedule if a solution exists, and false
 *        otherwise. 
 * 
 * @param [in]  avail n x k vector of vectors (i.e. matrix) of the availability
 *                    of the k workers for each of the n days
 * @param [in]  dailyNeed Number of workers needed per day (aka d)
 * @param [in]  maxShifts Maximum shifts any worker is allowed over 
 *                        the n day period (aka m)
 * @param [out] sched n x d vector of vectors indicating the d workers
 *                    who are scheduled to work on each of the n days
 * @return true if a solution exists; sched contains the solution
 * @return false if no solution exists; sched is undefined (can be anything)
 */
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    // is matirx filled if yes return true
    size_t n = avail.size(); //days
    size_t k = avail[0].size(); //total workers
    vector<int> shiftsWorked(k,0);
    sched.assign(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    return schedBuilder(avail, dailyNeed, maxShifts, sched, shiftsWorked, 0, 0);
    




}
bool schedBuilder(  const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, vector<int>& shiftsWorked, 
    size_t currentDay, size_t currentWorker){
    size_t n = avail.size(); // total days
    size_t k = avail[0].size(); //total workers
    if(n == currentDay){
        return true;
    }
    if(currentWorker== dailyNeed){
        return schedBuilder(  avail, dailyNeed, maxShifts, sched,  shiftsWorked, currentDay+1, 0);
    }
    //add workers 
    for(size_t i = 0; i < k; i++){
        if(avail[currentDay][i] == 1){
        if(shiftsWorked[i] < maxShifts){
            bool usedAlready = false;
            for (size_t x = 0; x < currentWorker; x++) {
                if (sched[currentDay][x] == i) {
                    usedAlready = true;
                    break;
                }
            }
            if(!usedAlready){
                    sched[currentDay][currentWorker] = i;
                    shiftsWorked[i]++;
                    if( schedBuilder(  avail, dailyNeed, maxShifts, sched,  shiftsWorked, currentDay, currentWorker+1)){
                        return true;
                    }
                    shiftsWorked[i]--;
                    sched[currentDay][currentWorker] = INVALID_ID;
            }
            }
            }
        }
        
    
    return false; 

}


