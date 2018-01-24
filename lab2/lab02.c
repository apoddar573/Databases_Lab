#include "readfile.h"


int main() {

	system("sed 's/,/ ,/g' database-19-jan-2018/exam-time-table.csv > database-19-jan-2018/exam-time-table1.csv");

	struct courses availableCourses[500];
	struct student regStudents[10000];
	char course_path[50] = "database-19-jan-2018/course-credits.csv";
	char course_credits_path[50] = "database-19-jan-2018/exam-time-table1.csv";
	int i, numOfStud, total_courses, j, k;

	total_courses = read_courses(course_path, availableCourses);
	read_courses_exam(course_credits_path, availableCourses, total_courses);
	read_students(regStudents, &numOfStud);
	update_list(regStudents, availableCourses, numOfStud, total_courses);
	check_timetable("illegalRecordsExamClash.csv", regStudents, numOfStud);
	make_file("illegalRecordsExceedingCredits.csv", regStudents, numOfStud);
	return 0;
}



