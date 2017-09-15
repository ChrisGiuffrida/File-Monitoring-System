#include "rorschach.h"

/**
 * Determines whether a file in the system was CREATED, MODIFIED, or DELETED.
 *
 * @return              Whether or not the function was successful.
 */
int compare() {

    // Check for deletion
		for(auto it : previous_data) {
			if(current_data.count(it.first) == 0) {
				if(match_patterns(it.second, DELETE) != 0) {
					fprintf(stderr, "compare.cpp:  executing %s\n", strerror(errno));
					return EXIT_FAILURE;
				}
			}
      // Check for modification
			else {
				if((it.second.time.tv_sec - current_data[it.first].time.tv_sec) != 0) {
					if(match_patterns(it.second, MODIFY) != 0) {
						fprintf(stderr, "compare.cpp:  executing %s\n", strerror(errno));
						return EXIT_FAILURE;
					}
				}
			}
		}

    // Check for creation
		for(auto it : current_data) {
			if(previous_data.count(it.first) == 0) {
				if(match_patterns(it.second, CREATE) != 0) {
					fprintf(stderr, "compare.cpp:  executing %s\n", strerror(errno));
					return EXIT_FAILURE;
				}
			}
		}


	previous_data = current_data;
	return EXIT_SUCCESS;
}
