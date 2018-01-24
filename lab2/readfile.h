#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>


struct courses 
{
	char name[10];
	int credits,date, year, month, start, end, exam;
};

struct student
{
	char roll_no[20];
	char name[100];
	int num_courses, exam_clash;
	int total_credits;
	char courses[10][10];
	struct courses my_courses[10];
};


int read_courses(char path[100], struct courses *c) {
	FILE *fp = fopen(path, "r");
	int num_courses = 0;
	struct courses *ptr = c;
	while(!feof(fp)) {
		int curr_credits;
		fscanf(fp, "%[^,] ,%d\n", ptr->name, &curr_credits);
		ptr->credits = curr_credits;
		ptr->exam = 0;
		num_courses++;
		ptr = ptr+1;
	}
	return num_courses;
}

void read_courses_exam(char path[1000], struct courses *c, int num_courses) {
	FILE *fp = fopen(path, "r");
	char curr_course[10];
	int year, date, month, start, end, i;
	while(!feof(fp)) {
		fscanf(fp, "%s ,%d-%d-%d ,%d:00 ,%d:00", curr_course, &year, &month, &date, &start, &end);
		for(i = 0; i<num_courses; i++) {
			if((c+i)->exam == 1) {
				continue;
			}
			(c+i)->exam = 0;
			if(strcmp((c+i)->name,curr_course) == 0) {
				(c+i)->year = year;
				(c+i)->month = month;
				(c+i)->date = date;
				(c+i)->start = start;
				(c+i)->end = end;
				(c+i)->exam = 1;
			}
		}
	}
}

void read_students_file(char path[50], char filename[20], struct student *s, int *numOfStud) {
	char filePath[100] = "database-19-jan-2018/course-wise-students-list/";
	strcat(filePath, path);
	strcat(filePath, "/");
	strcat(filePath, filename);
	char course_name[10];
	strcpy(course_name, filename);
	course_name[strlen(course_name) - 4] = '\0';
	// printf("%s\n", course_name);

	int i, sn, flag;
	char name[100], roll[20];
	FILE *fp = NULL;
	fp = fopen(filePath, "r");
	while(!feof(fp)) {
		int ret = fscanf(fp,"%d,%[^,],%[^\n]",&sn, roll, name);
		// printf("%s %s\n",roll, name);
		if(ret != 3) {
			continue;
		}
		flag = 0;
		for (i = 0; i < *numOfStud; ++i)
		{
			if( strcmp((s+i)->roll_no, roll) == 0) {
				strcpy((s+i)->courses[(s+i)->num_courses], course_name); 
				(s+i)->num_courses = (s+i)->num_courses + 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			strcpy((s+*numOfStud)->name, name);
			strcpy((s+*numOfStud)->roll_no, roll);
			(s+*numOfStud)->num_courses = 1;
			strcpy((s+*numOfStud)->courses[0], course_name);
			// printf("%s %s\n",(s + *numOfStud)->roll_no, (s+*numOfStud)->name);
			*numOfStud = *numOfStud + 1;
		}
	}
}

void read_students_dir(char path[50], struct student *s, int *numOfStud) {
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
			// printf("%s\n", de->d_name);
			read_students_file(path, de->d_name, s, numOfStud);
		}
	}
    

    closedir(dr);    

}


void read_students(struct student *s, int *numOfStud) {
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
			// printf("%s\n", de->d_name);
			read_students_dir(de->d_name, s, numOfStud);
    	}
    }

    closedir(dr);    
    return ;
}

void update_list(struct student *regStudents, struct courses *availableCourses, int numOfStud, int num_courses) {
	int i, j, k;
	for(i = 0; i<numOfStud; i++) {
	int total_credits = 0;
	for(j = 0; j<regStudents[i].num_courses; j++) {
		for(k = 0; k<num_courses; k++) {
			if(strcmp(availableCourses[k].name, regStudents[i].courses[j]) == 0) {
				total_credits = total_credits + availableCourses[k].credits;
				regStudents[i].my_courses[j] = availableCourses[k];
				}
			}
		}
	regStudents[i].total_credits = total_credits;
	} 

}

int check_exam_dates(struct courses cs1, struct courses cs2) {
	if(cs1.date == cs2.date) {
		if(cs1.month == cs2.month) {
			if(cs1.year == cs2.year) {
				if(cs1.start == cs2.start) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void check_timetable(char filename[50], struct student *regStudents, int numOfStud) {
	FILE *fp = fopen(filename, "w");
	int i, j, k;
	int flag;
	for(i = 0; i<numOfStud; i++) {
		regStudents[i].exam_clash = 0;
		for(j = 0; j<regStudents[i].num_courses; j++) {
			if (regStudents[i].my_courses[j].exam == 0) {
				continue;
			}
			for(k = j+1; k<regStudents[i].num_courses; k++) {
				if(regStudents[i].my_courses[k].exam == 0) {
					continue;
				}
				if(check_exam_dates(regStudents[i].my_courses[j], regStudents[i].my_courses[k]) == 1) {
					regStudents[i].exam_clash = 1;
					if(strcmp(regStudents[i].my_courses[j].name, regStudents[i].my_courses[k].name))
					fprintf(fp, "%s, %s, %s, %s\n", regStudents[i].roll_no, regStudents[i].name, regStudents[i].my_courses[j].name, regStudents[i].my_courses[k].name);
					break;
				}
			}
		}
	}
	fclose(fp);
}

void make_file(char filename[50], struct student *regStudents, int numOfStud) {
	FILE *fp = fopen(filename, "w");
	int i;
	for(i = 0; i<numOfStud; i++) {
		if((regStudents[i].total_credits>40)) {
			fprintf(fp, "%s, %s, %d\n", regStudents[i].roll_no, regStudents[i].name, regStudents[i].total_credits);
		}
	}
	fclose(fp);
}
