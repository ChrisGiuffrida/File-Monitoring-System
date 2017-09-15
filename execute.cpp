#include "rorschach.h"

/**
 * Execute a given command in the bash shell after setting environmet variables. 
 * 
 * @param file_info          Root directory path
 * @param action             The action to run for the event.
 * @param event              Type of event that occurred
 * @return                   Whether or not the function was successful.
 */
int execute(file &file_info, string action, string event) {
	vector<string> env_vars;
	pid_t pid = fork();
	switch (pid) {
		case -1:
			fprintf(stderr, "execute.cpp:  fork %s\n", strerror(errno));
			return EXIT_FAILURE;
			break;
		case 0:
			printf("Executing action \"%s\"\n", action.c_str());  
			setenv("BASEPATH", file_info.basepath.c_str(), 1);
			setenv("FULLPATH", file_info.fullpath.c_str(), 1);
			setenv("EVENT", event.c_str(), 1);
      char time[BUFSIZ];
      sprintf(time, "%ld", (long int)file_info.time.tv_sec);
      setenv("TIMESTAMP", time, 1);
      
      execlp("/bin/sh", "/bin/sh", "-c", action.c_str(), NULL);

			_exit(0);
			break;
		default:
			int status;
			while((pid = wait(&status)) < 0);
			break;
	}

	return EXIT_SUCCESS;
}
