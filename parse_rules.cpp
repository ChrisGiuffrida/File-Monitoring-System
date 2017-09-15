#include "rorschach.h"

/**
 * Parse the given rules file. 
 * 
 * @param rules         The path to the rules file.
 * @return              Whether or not the function was successful.
 */
int parse_rules(const char * rules) {

	FILE *file;
	if((file = fopen(rules, "r")) == NULL) {
		fprintf(stderr, "parse_rules.cpp:  open %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	char line[BUFSIZ];
	char * event_type;
	char * pattern; 
	char * action;
	rule new_rule;
	while(fgets(line, BUFSIZ, file)) {
		event_type = strtok(line, " \t\n");
		pattern = strtok(NULL, " \t\n");
		action = strtok(NULL, "\n");

		if(event_type != NULL) {
			string event_type_string(event_type);
			if (event_type_string[0] == '#') {
				continue;
			}
			else if(pattern != NULL && action != NULL) {
				string pattern_string(pattern);
				string action_string(action);
				strip(pattern_string);
				strip(action_string);
				new_rule.pattern = pattern_string;
				new_rule.action  = action_string;

				if(event_type_string == "MODIFY") {
					modify_rules.push_back(new_rule);
				}
				else if(event_type_string == "DELETE") {
					delete_rules.push_back(new_rule);
				}
				else if(event_type_string == "CREATE") {
					create_rules.push_back(new_rule);
				}
				else {
					printf("Invalid rule: %s\n", line);
					return EXIT_FAILURE;
				}
			}
			else {
				printf("Invalid rule: %s\n", line);
				return EXIT_FAILURE;
			}
		}	
		else {
			continue;
		}
	}
	return EXIT_SUCCESS;
}
