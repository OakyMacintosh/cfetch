#define _GNU_SOURCE

#include <stdio.h>
#define CFETCH_VERSION "0.1.0"
#define CFETCH_LICENSE "BSD License"
#define CFETCH_AUTHOR "OakyMacintosh"
#define CFETCH_GITHUB "https://github.com/OakyMacintosh/cfetch"
#define CFETCH_ISSUES "https://github.com/OakyMacintosh/cfetch/issues"

#define COLOR_RESET   "\033[0m"
#define COLOR_TITLE   "\033[1;36m"
#define COLOR_LABEL   "\033[1;33m"
#define COLOR_VALUE   "\033[1;32m"

void print_version() {
	printf(COLOR_TITLE "cfetch v%s\n" COLOR_RESET, CFETCH_VERSION);
	printf(COLOR_LABEL "License: " COLOR_VALUE "%s\n" COLOR_RESET, CFETCH_LICENSE);
	printf(COLOR_LABEL "Author: " COLOR_VALUE "%s\n" COLOR_RESET, CFETCH_AUTHOR);
	printf(COLOR_LABEL "GitHub: " COLOR_VALUE "%s\n" COLOR_RESET, CFETCH_GITHUB);
	printf(COLOR_LABEL "Issues: " COLOR_VALUE "%s\n" COLOR_RESET, CFETCH_ISSUES);
}

void print_help() {
	printf(COLOR_TITLE "cfetch usage:\n" COLOR_RESET);
	printf("  --help      Show this help message\n");
	printf("  --version   About this program\n");
	printf("  --minimal   Show minimal info\n");
	printf("  --all       Show all info (default)\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>

// Print OS and kernel info
void print_os_kernel() {
	struct utsname uname_data;
	if (uname(&uname_data) == 0) {
		printf(COLOR_LABEL "OS: " COLOR_VALUE "%s\n" COLOR_RESET, uname_data.sysname);
		printf(COLOR_LABEL "Kernel: " COLOR_VALUE "%s %s\n" COLOR_RESET, uname_data.release, uname_data.version);
	}
}

// Print hostname
void print_hostname() {
	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) == 0) {
		printf(COLOR_LABEL "Hostname: " COLOR_VALUE "%s\n" COLOR_RESET, hostname);
	}
}

// Print username
void print_username() {
	struct passwd *pw = getpwuid(getuid());
	if (pw) {
		printf(COLOR_LABEL "User: " COLOR_VALUE "%s\n" COLOR_RESET, pw->pw_name);
	}
}

// Print uptime
void print_uptime() {
	FILE *fp = fopen("/proc/uptime", "r");
	if (fp) {
		double uptime;
		if (fscanf(fp, "%lf", &uptime) == 1) {
			int days = (int)(uptime / 86400);
			int hours = ((int)uptime % 86400) / 3600;
			int mins = ((int)uptime % 3600) / 60;
			printf(COLOR_LABEL "Uptime: " COLOR_VALUE "%d days, %d hours, %d mins\n" COLOR_RESET, days, hours, mins);
		}
		fclose(fp);
	} else {
		// macOS fallback: use sysctl kern.boottime
		#ifdef __APPLE__
		#include <sys/types.h>
		#include <sys/sysctl.h>
		#include <sys/time.h>
		struct timeval boottime;
		size_t size = sizeof(boottime);
		int mib[2] = {CTL_KERN, KERN_BOOTTIME};
		time_t now = time(NULL);
		if (sysctl(mib, 2, &boottime, &size, NULL, 0) == 0 && boottime.tv_sec != 0) {
			time_t uptime = now - boottime.tv_sec;
			int days = uptime / 86400;
			int hours = (uptime % 86400) / 3600;
			int mins = (uptime % 3600) / 60;
			printf(COLOR_LABEL "Uptime: " COLOR_VALUE "%d days, %d hours, %d mins\n" COLOR_RESET, days, hours, mins);
		}
		#endif
	}
}

// Print shell
void print_shell() {
	char *shell = getenv("SHELL");
	if (shell) {
		printf(COLOR_LABEL "Shell: " COLOR_VALUE "%s\n" COLOR_RESET, shell);
	}
}

// Print current time
void print_time() {
	time_t now = time(NULL);
	struct tm *tm_now = localtime(&now);
	char buf[64];
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_now);
	printf(COLOR_LABEL "Time: " COLOR_VALUE "%s\n" COLOR_RESET, buf);
}

int main(int argc, char *argv[]) {
	int show_all = 1, show_minimal = 0;
	if (argc > 1) {
		if (strcmp(argv[1], "--help") == 0) {
			print_help();
			return 0;
		} else if (strcmp(argv[1], "--version") == 0) {
			print_version();
			return 0;
		} else if (strcmp(argv[1], "--minimal") == 0) {
			show_minimal = 1;
			show_all = 0;
		} else if (strcmp(argv[1], "--all") == 0) {
			show_all = 1;
		} else {
			printf("Unknown argument: %s\n", argv[1]);
			print_help();
			return 1;
		}
	}
	if (show_minimal) {
		print_os_kernel();
		print_username();
		print_time();
	} else if (show_all) {
		print_os_kernel();
		print_hostname();
		print_username();
		print_uptime();
		print_shell();
		print_time();
	}
	return 0;
}
