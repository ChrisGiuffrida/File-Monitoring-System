#include "rorschach.h"

/**
 * Print the statement for a detection
 *
 * @param event_name    The name of the found event.
 * @param basepath      The basepath of the detected file.
 * 
 * @return              Whether or not the function was successful.
 */
void print_detection(string event_name, string basepath) {
	printf("Detected \"%s\" event on \"%s/%s\"\n", event_name.c_str(), ROOT, basepath.c_str());
}


/**
 * Print the statement for a match.
 * 
 * @param pattern       The pattern that matched.
 * @param basepath      The basepath of the matched file.
 *
 * @return              Whether or not the function was successful.
 */
void print_match(string pattern, string basepath) {
	printf("Matched \"%s\" pattern on \"%s\"\n", pattern.c_str(), basepath.c_str());
}


/**
 * Determines whether a file in the system was CREATED, MODIFIED, or DELETED.
 *
 * @return              Whether or not the function was successful.
 */
 string get_real_path(const char * path) {		
	char *real_path_char = realpath(path, NULL);
	string real_path(real_path_char);
	return real_path;
}


/**
 * Checks if there was a glob match for a file. 
 *
 * @param pattern       The pattern to match.
 * @param basepath      The basepath of the file.
 * @param fullpath      The fullpath of the file.
 *
 * @return              True of false if there was a match.
 */
int check_match(string pattern, string basepath, string fullpath) {
	return fnmatch(pattern.c_str(), basepath.c_str(), 0) == 0 || 
		fnmatch(pattern.c_str(), fullpath.c_str(), 0) == 0;
}


/**
 * Strips whitespace from a string. 
 *
 * @param                The string to strip.
             
*/
// Taken from http://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void strip(string& s)
{
  size_t p = s.find_first_not_of(" \t");
  s.erase(0, p);
  p = s.find_last_not_of(" \t");
  if (string::npos != p)
    s.erase(p+1);
}

