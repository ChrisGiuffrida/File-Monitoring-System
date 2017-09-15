#ifndef RORSCHACH_H
#define RORSCHACH_H

#include <map>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>
#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <vector>
#include <fnmatch.h>

using namespace std;

typedef enum {
	CREATE,
	MODIFY,
	DELETE,
	UNDETERMINED
} event;


struct file {
	string basepath;
	string fullpath;
	timespec time;
};

struct rule {
	string pattern;
	string action;
};

extern char const *ROOT;
extern map<string, file> previous_data;
extern map<string, file> current_data;
extern vector<rule> modify_rules;
extern vector<rule> create_rules;
extern vector<rule> delete_rules;


int crawl(const char *);
int compare();
int match_patterns(file &, event);
int parse_rules(const char *);
int execute(file &, string, string);

void print_detection(string, string);
string get_real_path(const char *);
void strip(string &);
void print_match(string, string);
int check_match(string, string, string);


#endif
