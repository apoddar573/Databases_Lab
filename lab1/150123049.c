#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
	char roll_no[20];
	int no_classes_present;
	float percentage;
	int total_classes;
};


int main() {
	struct student info[1000];
	FILE *fp = fopen("database_lab1.csv", "r");
	int index = 0, i;

	char curr_roll[20], curr_held_on[30], curr_attd[20];

	fscanf(fp, "%s %s %s", curr_roll, curr_held_on, curr_attd);

	strcpy(info[0].roll_no, curr_roll);
	info[0].no_classes_present = 0;
	info[0].total_classes = 0;

	while(!feof(fp)){
	fscanf(fp, "%s %s %s", curr_roll, curr_held_on, curr_attd);
		if (strcmp(info[index].roll_no, curr_roll) == 0) {
			printf("%d\n", info[index].no_classes_present);
			info[index].total_classes++;
			if(curr_attd[0] == 'P') {
				info[index].no_classes_present++; }
		} else {
			index++;
			strcpy(info[index].roll_no, curr_roll);
			info[index].total_classes = 1;
			if(strcmp(curr_attd, "Present") == 0){
				info[index].no_classes_present = 1;}
			else{
				info[index].no_classes_present = 0;}
		}
	}
	FILE *fp1 = fopen("G75.csv", "w");
	FILE *fp2 = fopen("L75.csv", "w");
	for(i = 0; i<=index; i++) {
		info[i].percentage = (info[i].no_classes_present*100)/info[i].total_classes;
		printf("%s %d %d %.2f%%\n", info[i].roll_no, info[i].no_classes_present, info[i].total_classes, info[i].percentage );
		if(info[i].percentage >= 75.00) {
			fprintf(fp1, "%s %d, %.2f%%\n", info[i].roll_no, info[i].no_classes_present, info[i].percentage );
		} else {
			fprintf(fp2, "%s %d, %.2f%%\n", info[i].roll_no, info[i].no_classes_present, info[i].percentage );
		}
	}
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
}
