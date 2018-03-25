use 150123049_23feb2018;
CREATE TABLE exceeding_credits(
	roll_number CHAR(30) NOT NULL,
	name CHAR(50),
	total_credits INT,
	PRIMARY KEY(roll_number)
);

DELIMITER $$
CREATE PROCEDURE count_credits()
BEGIN 
	DECLARE done INT DEFAULT false;
	DECLARE prev_credits, curr_credits INT DEFAULT 0;
	DECLARE curr_roll, prev_roll CHAR(30);
	DECLARE prev_name, curr_name CHAR(50);
	DECLARE cid CHAR(20);

	DECLARE cur1 cursor for select course_id, roll_number, name, number_of_credits from cwsl natural join cc ORDER BY roll_number;

	DECLARE CONTINUE HANDLER FOR NOT FOUND set done = TRUE;

	OPEN cur1;

	FETCH next from cur1 INTO cid, prev_roll, prev_name, prev_credits;
    
	studentloop: LOOP
		set curr_roll = prev_roll;
		set curr_credits = 0;
		set curr_name = prev_name;

		while (curr_roll = prev_roll) do 
			set curr_credits = curr_credits + prev_credits;
			FETCH next from cur1 INTO cid, prev_roll, prev_name, prev_credits;
			if done THEN
				leave studentloop;
			END IF;
		end while;

	if (curr_credits>40) then 
		insert into exceeding_credits values (curr_roll, curr_name, curr_credits);
	end if;
	
	select * from exceeding_credits;
	
	END LOOP studentloop;
	CLOSE cur1;

END$$

DELIMITER ;

call count_credits();
select * from exceeding_credits;