#include "Scheduler.h"

// Each bit represents a single event that is presently scheduled. A '1' indicates
// that the event is presently scheduled and needs to be excecuted. Since this is a
// 32 bit variable, a total of 32 distinctive events can be scheduled with this scheduler
static uint32_t scheduledEvents;

/**
 * @brief Add event to scheduled events
 * 
 * @param event - which event to add
*/
void SCHEDULAR_addSchedulerEvent(uint32_t event) 
{   
    scheduledEvents |= event; // 'event' is a bit mask which represents a 32 bit value containing
                               // a single '1' and all 0's. 
}
/**
 * @brief Removes scheduled event by resetting specified bit
 * 
 * @param event - which event to remove
*/
void SCHEDULAR_removeSchedularEvent(uint32_t event)
{
    scheduledEvents &= ~event; // Reset specific event value
}

/**
 * @brief Returns scheduled events
*/
uint32_t SCHEDULAR_getScheduledEvents()
{
    return scheduledEvents;
}