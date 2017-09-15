#include "rorschach.h"

/* Globals */
char *PROGRAM_NAME = NULL;
char const *ROOT   = ".";
char const *RULES  = "rules";
int  SECONDS       = 5;
map<string, file> previous_data;
map<string, file> current_data;
vector<rule> modify_rules;
vector<rule> create_rules;
vector<rule> delete_rules;

/* Functions */
void usage(int status) {
	fprintf(stdout, "Usage: rorschach [options] ROOT\n");
	fprintf(stdout, "\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "\t-h\t\tPrint this help message\n");
	fprintf(stdout, "\t-f RULES\tLoad rules from this file (default is rules)\n");
	fprintf(stdout, "\t-t SECONDS\tTime between scans (default is 5 seconds)\n");
	exit(status);
}

// Cleanup after recieving sigint
void cleanup_handler(int signum) {
	printf("\nCleaning up\n");
	printf("Bye\n");
	exit(EXIT_SUCCESS);
}

/* Main Execution */
int main(int argc, char *argv[]) {
	int argind = 1;
	PROGRAM_NAME = argv[0];

	if(argc < 2) { 
		usage(1);
	}

  // Parse command line arguments
	while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
		char *arg = argv[argind++];

		if(arg[1] == 'h') {
			usage(0);
		}
		else if(arg[1] == 'f') {
			if(argind < argc) {
				RULES = argv[argind++];
			}
			else {
				usage(1);
			}
		}
		else if(arg[1] == 't') {
			if(argind < argc) {
				SECONDS = atoi(argv[argind++]);
			}
			else {
				usage(1);
			}
		}
		else {
			usage(1);
		}
	}

	if(argind < argc) {
		ROOT = argv[argind++];
	}

	signal(SIGINT, cleanup_handler);  

	if(parse_rules(RULES) != 0) {
		fprintf(stderr, "main.cpp:  parse_rules() failed\n");
		return EXIT_FAILURE;
	}

  // Loop forever and crawl through the directory
	printf("Monitoring %s\n", ROOT);
	while(1) {
		//printf("Starting a crawl...\n");
		current_data.clear();
		if(crawl(ROOT) != 0) {
			fprintf(stderr, "main.cpp:  crawling %s\n", strerror(errno));
			return EXIT_FAILURE;
		}

		if(compare() != 0) {
			fprintf(stderr, "main.cpp:  comparing %s\n", strerror(errno));
			return EXIT_FAILURE;
		}

		sleep(SECONDS);
	}
}
