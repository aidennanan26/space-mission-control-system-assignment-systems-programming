
/* 
   ####################################################
   IMPLEMENT FUNCTIONS 1 & 2:
    - create_mission_control() (10 points)
    - create_mission_with_crew() (25 points)
   ################################################### 
*/

#include "space_mission.h"
/*
 * FUNCTION 1: create_mission_control()
 * 
 * PURPOSE: Create and initialize a new mission control system
 * 
 * PARAMETERS:
 *   initial_capacity - Initial size for missions array (must be > 0)
 * 
 * RETURNS:
 *   Pointer to newly created MissionControl system, NULL on failure
 * 
 * REQUIREMENTS:
 *  - Validate `initial_capacity > 0`, return NULL if invalid
 *  - Allocate memory for main MissionControl structure using malloc()
 *  - Allocate missions array for specified capacity
 *  - Initialize all structure members (mission_count = 0, capacity = initial_capacity)
 *  - Return NULL on any allocation failure with proper cleanup
 */
MissionControl* create_mission_control(int initial_capacity) {
    // TODO: Implement create_mission_control with proper memory allocation
    //
    // 1. INPUT VALIDATION:
    //    - Verify initial_capacity is greater than 0
    //    - Return NULL if invalid
    //
    // 2. ALLOCATE MAIN STRUCTURE:
    //    - Use malloc() to allocate MissionControl structure
    //    - Check allocation success
    //
    // 3. ALLOCATE MISSIONS ARRAY:
    //    - Allocate missions array for initial_capacity missions
    //    - If allocation fails, cleanup main structure and return NULL
    //
    // 4. INITIALIZE STRUCTURE MEMBERS:
    //    - Set mission_count to 0
    //    - Set capacity to initial_capacity
    //    - Set missions pointer
    //    - Return initialized system
    
    // Your implementation here:

    // 1. INPUT VALIDATION:
    if (initial_capacity <= 0) {
        return NULL;
    }

    // 2. ALLOCATE MAIN STRUCTURE:
    MissionControl* system = (MissionControl*)malloc(sizeof(MissionControl));
    if (system == NULL) {
        return NULL; // Allocation failed
    }

    // 3. ALLOCATE MISSIONS ARRAY:
    system->missions = (Mission*)malloc(initial_capacity * sizeof(Mission));
    if (system->missions == NULL) {
        free(system); // Cleanup main structure
        return NULL; // Allocation failed
    }

    //4. INITIALIZE STRUCTURE MEMBERS:
    system->mission_count = 0;
    system->capacity = initial_capacity;
    return system; // Return initialized system
    
}

/*
 * FUNCTION 2: create_mission_with_crew()
 * 
 * PURPOSE: Create a new mission and add it to the system
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   mission_id - Unique mission identifier (must be > 0)
 *   name - Mission name/designation (cannot be NULL or empty)
 *   launch_date - Launch date in YYYY-MM-DD format
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Validate all inputs: NULL pointers, mission_id > 0, valid date format using `is_valid_date_format()`
 *  - Check for duplicate mission IDs in existing missions
 *  - Expand missions array using realloc() when capacity reached (double the size)
 *  - Allocate communications array for new mission using calloc()
 *  - Initialize mission structure with PLANNED status and proper defaults
 */
int create_mission_with_crew(MissionControl* system, int mission_id, const char* name, 
                            const char* launch_date) {
    
    // TODO: Implement create_mission_with_crew with comprehensive validation
    //
    // 1. INPUT VALIDATION:
    //    - Check all pointer parameters for NULL
    //    - Validate mission_id > 0
    //    - Verify name is not NULL or empty
    //    - Use is_valid_date_format() in driver.c to validate launch_date
    //    - Return -1 if any validation fails
    //
    // 2. DUPLICATE ID CHECK:
    //    - Search existing missions for duplicate mission_id
    //    - Return -1 if duplicate found
    //
    // 3. ARRAY EXPANSION:
    //    - Check if missions array needs expansion (count >= capacity)
    //    - Use realloc() to double capacity if needed
    //    - Update system->capacity after successful realloc
    //
    // 4. INITIALIZE NEW MISSION:
    //    - Set mission_id, mission_name, launch_date
    //    - Set status to PLANNED enum value
    //    - Use calloc() to allocate communications array (INITIAL_COMM_CAPACITY * sizeof(CommLog))
    //    - Initialize comm_count to 0, comm_capacity to INITIAL_COMM_CAPACITY
    //    - Increment system->mission_count
    //    - Return 0 for success
    
    // Your implementation here:
    
    (void)system;
    (void)mission_id;
    (void)name;
    (void)launch_date;

    // 1. INPUT VALIDATION:
    if (system == NULL || name == NULL || launch_date == NULL ||
        mission_id <= 0 || strlen(name) == 0 ||
        !is_valid_date_format(launch_date)) {
        return -1;
    }

    // 2. DUPLICATE ID CHECK:
    for (int i = 0; i < system->mission_count; i++) {
        if (system->missions[i].mission_id == mission_id) {
            return -1;
        }
    }

    // 3. ARRAY EXPANSION:
    if (system->mission_count >= system->capacity) {
        int new_capacity = system->capacity * 2;

        Mission* new_missions =
            (Mission*)realloc(system->missions, new_capacity * sizeof(Mission));

        if (new_missions == NULL) {
            return -1;
        }

        system->missions = new_missions;
        system->capacity = new_capacity;
    }

    // 4. INITIALIZE NEW MISSION:
    Mission* new_mission = &system->missions[system->mission_count];

    new_mission->mission_id = mission_id;

    strncpy(new_mission->mission_name, name, MAX_NAME_LENGTH - 1);
    new_mission->mission_name[MAX_NAME_LENGTH - 1] = '\0';

    strncpy(new_mission->launch_date, launch_date, MAX_DATE_LENGTH - 1);
    new_mission->launch_date[MAX_DATE_LENGTH - 1] = '\0';

    new_mission->status = PLANNED;

    new_mission->communications =
        (CommLog*)calloc(INITIAL_COMM_CAPACITY, sizeof(CommLog));

    if (new_mission->communications == NULL) {
        return -1;
    }

    new_mission->comm_count = 0;
    new_mission->comm_capacity = INITIAL_COMM_CAPACITY;

    system->mission_count++;

    return 0; // Success

}