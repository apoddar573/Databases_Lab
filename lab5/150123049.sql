
/*Part (a)
*/
select distinct(course_id) 
from ScheduledIn 
where room_number = '2001';

/*Part (b)
*/
select distinct(course_id) 
from ScheduledIn 
where letter = 'C';

/*Part (c)
*/
select distinct(division) 
from course 
natural join ScheduledIn 
where room_number in ('L2', 'L3');

/* Part (d)
*/
select course_id, count(course_id) as cnt 
from (select distinct course_id, room_number 
	from ScheduledIn 
	GROUP BY course_id, room_number) courseRooms 
GROUP BY course_id 
HAVING cnt>1;


/*Part (e)
*/
select distinct(name) 
from department 
natural join ScheduledIn 
where room_number in('L1', 'L2', 'L3', 'L4');


/*Part (f)
*/
select name 
from department 
where name not in (select distinct name 
	from department 
	natural join ScheduledIn 
	where room_number in ('L1', 'L2'));

/*Part (g)
*/
create table deptSlot as 
	select department_id, count(department_id) as cnt 
	from (select department_id, letter 
		from ScheduledIn 
		GROUP BY department_id, letter) departmentSlot 
	group by department_id;

select * 
from deptSlot 
where cnt = 17;

/*Part (h)
*/
select letter, count(letter) AS cnt 
	from (select * from ScheduledIn 
	GROUP BY letter, course_id) slotcourse
Group By letter 
Order By cnt;

/*Part (i)
*/
select room_number, count(room_number) AS cnt 
from (select * from ScheduledIn 
	GROUP BY room_number, course_id) slotcourse 
Group By room_number 
Order By cnt DESC;

/*Part (j)
*/
create table cttable as
 select letter, count(letter) AS cnt  
 from (select * 
 	from ScheduledIn  
 	GROUP BY letter, course_id) slotCourse
 Group By letter  
 Order By cnt;

select * from cttable  where cnt = (select min(cnt) from cttable) ;

/*Part (k)
*/
select distinct letter 
from (select * 
	from ScheduledIn 
	where course_id like '%M') letterCourse;

/*Part (l)
*/
select * 
from (select department_id 
	from department) as dept_id 
join (select distinct letter 
	from slot) as slt 
where (department_id, letter) 
not in (select distinct department_id, letter 
	from ScheduledIn) 
ORDER BY department_id, letter;






