#include "rorschach.h"

/**
 * Given an appropriate event type, determine what action to take from the rules.
 * 
 * @param file_info     Struct containing file metadata
 * @param event_type    Type of event, ie. MODIFY, CREATE or DELETE
 * @return              Whether or not the function was successful.
 */
int match_patterns(file &file_info, event event_type) {

	if(event_type == MODIFY) {
		print_detection("MODIFY", file_info.basepath);
		for(auto it: modify_rules) {
			if(check_match(it.pattern, file_info.basepath, file_info.fullpath)) {
				print_match(it.pattern, file_info.basepath);
				execute(file_info, it.action, "MODIFY");
			}
		}
	}
	else if(event_type == CREATE) {
		print_detection("CREATE", file_info.basepath);
		for(auto it: create_rules) {
			if(check_match(it.pattern, file_info.basepath, file_info.fullpath)) {
				print_match(it.pattern, file_info.basepath);
				execute(file_info, it.action, "CREATE");
			}
		}
	}
	else if(event_type == DELETE) {
		print_detection("DELETE", file_info.basepath);
		for(auto it: delete_rules) {
			if(check_match(it.pattern, file_info.basepath, file_info.fullpath)) {
				print_match(it.pattern, file_info.basepath);
				execute(file_info, it.action, "DELETE");
			}
		}
	}
	return EXIT_SUCCESS;
}
