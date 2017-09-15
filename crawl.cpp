#include "rorschach.h"

/**
 * Crawl through a given root directory to save file metadata for files in directory. 
 * 
 * @param root          Root directory path
 * @return              Whether or not the function was successful.
 */
int crawl(const char *root) {
	DIR *dirp = opendir(root);

	if(dirp == NULL) {
		fprintf(stderr, "crawl.cpp:  opendir %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

  // Loop through directory
	for(struct dirent *entry = readdir(dirp); entry != 0; entry = readdir(dirp)) {
		if((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)) {
			continue;
		}
		
		struct stat s;
		char path[BUFSIZ];
		sprintf(path, "%s/%s", root, entry->d_name);
		if(stat(path, &s) < 0) {
			fprintf(stderr, "crawl.cpp:  stat %s\n", strerror(errno));
			return EXIT_FAILURE;
		}

		file new_file = {
			.basepath = basename(path), 
			.fullpath = path,
			.time = {s.st_mtime}
		};

    // Updates file map if its regular file
		if((s.st_mode & S_IFMT) == S_IFREG) {
			current_data[new_file.fullpath] = new_file;
		}

    // Recursively crawl through subdirectory
		if((entry->d_type & DT_DIR) == DT_DIR) {
			crawl(path);
		}
	}

	closedir(dirp);
	return EXIT_SUCCESS;
}

