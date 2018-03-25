use 150123049_23feb2018;

CREATE TABLE exam_clash(
	roll_number CHAR(30),
	name CHAR(50),
	course_id1 CHAR(20),
	course_id2 CHAR(20),
	PRIMARY KEY(roll_number, course_id1, course_id2)
);


DELIMITER $$


CREATE PROCEDURE tt_violation() 

BEGIN

	DECLARE done INT DEFAULT 0;
	DECLARE roll_number CHAR(30);
	DECLARE name CHAR(50);
	DECLARE course_id1 CHAR(20);
	DECLARE course_id2 CHAR(20);


	DECLARE cur1 CURSOR FOR select distinct cwsl1.roll_number, cwsl1.name, cwsl1.course_id, cwsl2.course_id 
							from cwsl AS cwsl1 join cwsl AS cwsl2 
							where cwsl1.roll_number = cwsl2.roll_number and cwsl1.course_id>cwsl2.course_id;

	DECLARE CONTINUE HANDLER FOR NOT FOUND set done = 1;
	OPEN cur1;
	studloop: LOOP

	FETCH FROM cur1 INTO roll_number, name, course_id1, course_id2;
	if done then
		leave studloop;
	end if;
	if exists(select *
		  from ett as ett1 join ett as ett2
		  where ett1.exam_date=ett2.exam_date and ett1.start_time=ett2.start_time and ett1.course_id=course_id1 and ett2.course_id=course_id2) then
		insert into exam_clash values(roll_number, name,course_id1,course_id2); /*insert the required tuples which follow the above condition into the table*/
	end if;

	select * from exam_clash;

	END LOOP;

END$$

DELIMITER ;

call tt_violation();
select * from exam_clash;