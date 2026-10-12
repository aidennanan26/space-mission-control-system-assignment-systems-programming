/* 
   ####################################################
   IMPLEMENT FUNCTIONS 4 & 5:
    - load_missions_from_file() (15 points)
    - save_mission_report() (10 points)
   ################################################### 
*/


#include "space_mission.h"

/**
 * FUNCTION 4: load_missions_from_file()
 * 
 * PURPOSE: Load mission data from a text file using fscanf()
 * 
 * File format:
 * Line 1: number_of_missions
 * Following lines: mission_id mission_name launch_date
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   filename - Path to input file
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Use fscanf() for file input parsing
 *  - Validate file operations and parsed data before creating missions
 *  - Create missions using existing create_mission_with_crew() function in mission_control.c
 *  - Handle file errors and invalid data gracefully
 *  - Support loading 0 missions (empty file case)
 */
int load_missions_from_file(MissionControl* system, const char* filename) {
    
    // TODO: Implement load_missions_from_file() with file I/O
    //
    // 1. INPUT VALIDATION:
    //    - Check system and filename for NULL
    //    - Return -1 if invalid
    //
    // 2. OPEN FILE:
    //    - Use fopen() to open file for reading ("r" mode)
    //    - Return -1 if file cannot be opened
    //
    // 3. READ MISSION COUNT:
    //    - Use fscanf() to read number of missions from first line
    //    - Validate mission count is non-negative
    //    - Handle case where mission count is 0 (empty file)
    //
    // 4. READ MISSION DATA:
    //    - Loop through each mission entry
    //    - Use fscanf() to read: mission_id, mission_name, launch_date
    //    - Validate each field (mission_id > 0, valid date format)
    //    - Call create_mission_with_crew() function in mission_control.cfor each valid mission
    //    - Return -1 if any mission creation fails
    //
    // 5. CLEANUP:
    //    - Close file using fclose()
    //    - Return 0 for success
    
    // Your implementation here:

        if (system == NULL || filename == NULL) {
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    int mission_count = 0;

    if (fscanf(file, "%d", &mission_count) != 1) {
        fclose(file);
        return -1;
    }

    if (mission_count < 0) {
        fclose(file);
        return -1;
    }

    for (int i = 0; i < mission_count; i++) {
        int id;
        char name[MAX_NAME_LENGTH];
        char date[MAX_DATE_LENGTH];

        if (fscanf(file, "%d %49s %11s", &id, name, date) != 3) {
            fclose(file);
            return -1;
        }

        if (id <= 0 || !is_valid_date_format(date)) {
            fclose(file);
            return -1;
        }

        if (create_mission_with_crew(system, id, name, date) != 0) {
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return 0;
}

/*
 * FUNCTION 5: save_mission_report()
 * 
 * PURPOSE: Generate a comprehensive mission status report using fprintf()
 * 
 * PARAMETERS:
 *   system - Pointer to mission control system
 *   filename - Path to output file
 * 
 * RETURNS:
 *   0 on success, -1 on failure
 * 
 * REQUIREMENTS:
 *  - Use fprintf() for formatted output
 *  - Write professional report header with system statistics - refer to the 'SAMPLE_report.txt' file provided
 *  - For each mission: display mission details, communication counts by priority
 *  - Calculate and display system totals (total missions, total communications)
 *  - Handle file operations with proper error checking
 */
int save_mission_report(const MissionControl* system, const char* filename) {
    
    // TODO: Implement save_mission_report with formatted output
    //
    // 1. INPUT VALIDATION:
    //    - Check system and filename for NULL
    //    - Return -1 if invalid
    //
    // 2. OPEN FILE:
    //    - Use fopen() to open file for writing ("w" mode)
    //    - Return -1 if file cannot be opened
    //
    // 3. WRITE REPORT HEADER: - refer to the 'SAMPLE_report.txt' file provided:
    //    - Use fprintf() to write professional header
    //    - Include total missions count
    //    - Add appropriate formatting and separators
    //
    // 4. WRITE MISSION DETAILS:
    //    - Loop through all missions in system
    //    - For each mission, write:
    //      * Mission ID, name, launch date, status
    //      * Communication count
    //      * Communication summary by priority (routine/urgent/emergency counts)
    //
    // 5. WRITE SYSTEM TOTALS: - refer to the 'SAMPLE_report.txt' file provided:
    //    - Calculate and write total communications across all missions
    //    - Add footer formatting
    //
    // 6. CLEANUP:
    //    - Close file using fclose()
    //    - Return 0 for success
    
    // Your implementation here:
    
        if (system == NULL || filename == NULL) {
        return -1;
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        return -1;
    }

    int total_comm = 0;

    fprintf(file, "=====================================\n");
    fprintf(file, "       MISSION CONTROL REPORT        \n");
    fprintf(file, "=====================================\n\n");

    fprintf(file, "Total Missions: %d\n\n", system->mission_count);

    for (int i = 0; i < system->mission_count; i++) {
        Mission* m = &system->missions[i];

        int routine = 0, urgent = 0, emergency = 0;

        for (int j = 0; j < m->comm_count; j++) {
            CommLog* c = &m->communications[j];

            if (c->priority == ROUTINE) routine++;
            else if (c->priority == URGENT) urgent++;
            else if (c->priority == EMERGENCY) emergency++;
        }

        int mission_total = routine + urgent + emergency;
        total_comm += mission_total;

        fprintf(file, "-------------------------------------\n");
        fprintf(file, "Mission ID: %d\n", m->mission_id);
        fprintf(file, "Name: %s\n", m->mission_name);
        fprintf(file, "Launch Date: %s\n", m->launch_date);
        fprintf(file, "Status: %s\n", status_to_string(m->status));

        fprintf(file, "Communications:\n");
        fprintf(file, "  Routine: %d\n", routine);
        fprintf(file, "  Urgent: %d\n", urgent);
        fprintf(file, "  Emergency: %d\n", emergency);
        fprintf(file, "  Total: %d\n\n", mission_total);
    }

    fprintf(file, "=====================================\n");
    fprintf(file, "TOTAL COMMUNICATIONS: %d\n", total_comm);
    fprintf(file, "=====================================\n");

    fclose(file);
    return 0;
}