#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int read_cc(char path[100]) {
	FILE *fp = fopen(path, "r");
	FILE *fp1 = fopen("150123049_cc.sql", "w");
	int num_courses = 0;
	char cid[10];
	int credits;
	while(!feof(fp)) {
		int ret = fscanf(fp, "%[^,],%d\n", cid, &credits);
		if(ret != 2) break;
		fprintf(fp1, "INSERT INTO cc_temp Values('%s', '%d');\n", cid, credits);
		fprintf(fp1, "INSERT INTO cc_clone Values('%s', '%d');\n", cid, credits);
		fprintf(fp1, "INSERT INTO cc Values('%s', '%d');\n", cid, credits);
	}
	fclose(fp);
	fclose(fp1);
	return num_courses;
}

void read_ett(char path[1000]) {
	FILE *fp = fopen(path, "r");
	FILE *fp1 = fopen("150123049_ett.sql", "w");
	char cid[10];
	char date[20];
	char estime[10], eetime[10];
	while(!feof(fp)) {
		int ret = fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", cid, date, estime, eetime);
		if(ret != 4) break;
		fprintf(fp1, "INSERT INTO ett_temp Values('%s', '%s', '%s', '%s');\n", cid, date, estime, eetime);
		fprintf(fp1, "INSERT INTO ett_clone Values('%s', '%s', '%s', '%s');\n", cid, date, estime, eetime);
		fprintf(fp1, "INSERT INTO ett Values('%s', '%s', '%s', '%s');\n", cid, date, estime, eetime);

	}
}

void read_students_file(char path[50], char filename[20]) {
	char filePath[100] = "database-19-jan-2018/course-wise-students-list/";
	strcat(filePath, path);
	strcat(filePath, "/");
	strcat(filePath, filename);
	char cid[10];
	strcpy(cid, filename);
	cid[strlen(cid) - 4] = '\0';

	int sr, roll;
	char name[50], email[50];
	FILE *fp = NULL;
	FILE *fp1 = fopen("150123049_cwsl.sql", "a");
	fp = fopen(filePath, "r");
	while(!feof(fp)) {
		int ret = fscanf(fp,"%d,%d,%[^,],%[^\n]\n",&sr, &roll, name, email);
		if(ret != 4) break;
		fprintf(fp1, "INSERT INTO cwsl_temp Values ('%d', '%s', '%s', '%s', '%d');\n",roll, cid, name, email, sr);
		fprintf(fp1, "INSERT INTO cwsl_clone Values ('%d', '%s', '%s', '%s', '%d');\n",roll, cid, name, email, sr);
		fprintf(fp1, "INSERT INTO cwsl Values ('%d', '%s', '%s', '%s', '%d');\n",roll, cid, name, email, sr);
	}
	fclose(fp);
	fclose(fp1);
}

void read_students_dir(char path[50]) {
	struct dirent *de;  // Pointer for directory entry
 
    // opendir() returns a pointer of DIR type. 

	char dirPath[100] = "database-19-jan-2018/course-wise-students-list/";
	strcat(dirPath, path);
	// printf("%s\n", dirPath);
    DIR *dr = opendir(dirPath);
 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return ;
    }
 
    // for readdir()
    while ((de = readdir(dr)) != NULL) {
		if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
			printf("%s\n", de->d_name);
			read_students_file(path, de->d_name);
		}
	}
    

    closedir(dr);    

}


void read_students() {
	struct dirent *de;  // Pointer for directory entry
 
    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir("database-19-jan-2018/course-wise-students-list");
 
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return ;
    }
 
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL) {
		 if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
			printf("%s\n", de->d_name);
			read_students_dir(de->d_name);
    	}
    }

    closedir(dr);    
    return ;
}


int main() {


	char cc_path[50] = "database-19-jan-2018/course-credits.csv";
	char ett_path[50] = "database-19-jan-2018/exam-time-table.csv";
	int i, numOfStud, total_courses, j, k;

	FILE *fp = fopen("150123049_cwsl.sql", "w");
	fclose(fp);
	total_courses = read_cc(cc_path);
	read_ett(ett_path);
	read_students();
	// update_list(regStudents, availableCourses, numOfStud, total_courses);
	// check_timetable("illegalRecordsExamClash.csv", regStudents, numOfStud);
	// make_file("illegalRecordsExceedingCredits.csv", regStudents, numOfStud);

	return 0;
}






