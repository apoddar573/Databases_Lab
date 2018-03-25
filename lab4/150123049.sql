create database 09feb2018;

use 09feb2018;

-- the department_id is the key and thus cannot not be the NULL, we have specified the
-- name as NOT NULL as it is not possible to have no name for a department
CREATE TABLE department( 
department_id CHAR(20),
name CHAR(80) NOT NULL, 
PRIMARY KEY(department_id)
);


-- the course_id and division are both NULL here since both comprise the primary key.
-- For courses that do not have a 
-- division, we specify NA as the division.
CREATE TABLE course( 
course_id CHAR(20), 
division ENUM('I', 'II', 'III', 'IV', 'NA') DEFAULT 'NA', 
PRIMARY KEY(course_id, division)
);


-- the room_number cannot be NULL here so it is specified as not null and the location has
-- specific values that it can 
-- take
CREATE TABLE room( 
room_number CHAR(40) NOT NULL, 
location ENUM('Core-I', 'Core-II', 'Core-III', 'Core-IV', 'LH', 'Local'),
PRIMARY KEY(room_number)
);


-- the letter and day are primary keys 
-- the start_time nd the end_time cannot be NULL since there may not be classes on a particular day
CREATE TABLE slot( 
letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1'),
day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'), 
start_time TIME NOT NULL, 
end_time TIME NOT NULL,
PRIMARY KEY(letter, day)
);


-- for scheduledin, we need to know the course id and division, the room number, and also the letter and day for every class
-- the department is needed to specify which department is offering the course
-- the course_id, division, letter and day are taken as primary key. The letter and day are both needed since the same course
-- may have classes at different rooms and different slots on different days of the week 
CREATE TABLE ScheduledIn (
course_id CHAR(20), 
division ENUM('I', 'II', 'III', 'IV', 'NA') DEFAULT 'NA', 
department_id CHAR(20),
letter ENUM('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'A1', 'B1', 'C1', 'D1', 'E1'),
day ENUM('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday'), 
room_number CHAR(40) NOT NULL, 
PRIMARY KEY(course_id, division, letter, day),

FOREIGN KEY (course_id, division) REFERENCES course(course_id, division),
FOREIGN KEY (department_id) REFERENCES department(department_id),
FOREIGN KEY (letter, day) REFERENCES slot(letter, day),
FOREIGN KEY (room_number) REFERENCES room(room_number)
);

-- source 150123049_rooms.sql;
-- source 150123049_courses.sql;
-- source 150123049_departments.sql;
-- source 150123049_slots.sql;
-- source 150123049_ScheduledIn.sql;







