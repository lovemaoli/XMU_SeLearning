DROP PROCEDURE IF EXISTS InsertTeachers;
DROP PROCEDURE IF EXISTS InsertRooms;
DROP PROCEDURE IF EXISTS InsertExamRooms;

DELIMITER $$
CREATE PROCEDURE InsertTeachers()
BEGIN
    DECLARE i INT DEFAULT 5001;
    WHILE i <= 15000 DO
        INSERT INTO `teacher` (`id`, `deptID`, `gender`, `ExamCampus`, `participatedLastYear`, `ExamId`) 
        VALUES (i, FLOOR(1 + RAND() * 200), FLOOR(RAND() * 2), FLOOR(RAND() * 3), FLOOR(RAND() * 2), 1);
        SET i = i + 1;
    END WHILE;
END$$
DELIMITER ;

CALL InsertTeachers();

DELIMITER $$
CREATE PROCEDURE InsertRooms()
BEGIN
  DECLARE i INT DEFAULT 254;
  WHILE i <= 500 DO
    INSERT INTO `room` (`id`, `name`, `campus`, `buildingNo`, `roomNo`) 
    VALUES (i, CONCAT('room', i), FLOOR(RAND() * 3), FLOOR(1 + RAND() * 5), i);
    SET i = i + 1;
  END WHILE;
END$$
DELIMITER ;

CALL InsertRooms();

DELIMITER $$
CREATE PROCEDURE InsertExamRooms()
BEGIN
  DECLARE i INT DEFAULT 260;
  WHILE i <= 600 DO
    INSERT INTO `exam_room` (`id`, `examId`, `roomId`) 
    VALUES (i, 1, FLOOR(1 + RAND() * 500));
    SET i = i + 1;
  END WHILE;
END$$
DELIMITER ;

CALL InsertExamRooms();