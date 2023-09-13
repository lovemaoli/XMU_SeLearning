0)
su - omm
gs_om -t start
gsql -d postgres -p 26000 -r
\c sales

1)
CREATE TABLE dept(deptno char(2), deptname VARCHAR(20) NOT NULL, PRIMARY KEY(deptno));

2)
CREATE TABLE Teacher(
    ID char(5), 
    JOB VARCHAR(20) NOT NULL, 
    SAL NUMERIC(7,2), 
    deptno char(2), 
    PRIMARY KEY(ID), 
    FOREIGN KEY(deptno) REFERENCES dept(deptno)
);

3)
INSERT INTO dept VALUES ('01','CS'), ('02','SW'), ('03','MA');
INSERT INTO Teacher VALUES 
    ('10001','教授',3800,'01'), 
    ('10002','教授',4100,'02'), 
    ('10003','副教授',3500,'01'), 
    ('10004','助理教授',3000,'03');

4)
CREATE FUNCTION RECORD_INSERT_OR_UPDATE_SAL()
RETURNS TRIGGER AS $INSERT_OR_UPDATE_SAL$ DECLARE
BEGIN
    IF(new.JOB='教授' AND new.sal<4000) THEN new.sal=4000;
    END IF;
RETURN NEW;
END
$INSERT_OR_UPDATE_SAL$ LANGUAGE PLPGSQL;

CREATE TRIGGER INSERT_OR_UPDATE_SAL
BEFORE INSERT OR UPDATE ON Teacher
FOR EACH ROW
EXECUTE PROCEDURE RECORD_INSERT_OR_UPDATE_SAL();

5)
INSERT INTO Teacher VALUES ('10005','教授',3999,'02'), ('10006','教授',4000,'03');
UPDATE Teacher SET Sal=3900 WHERE ID='10002';

6)
SELECT tgname, tgtype, tgenabled, tgconstrrelid FROM PG_TRIGGER WHERE tgname='insert_or_update_sal';

7)
CREATE FUNCTION RECORD_DELETE_DEPT_TEACHER()
RETURNS TRIGGER AS $DELETE_DEPT_TEACHER$ DECLARE
BEGIN
    IF(old.deptno='03') THEN DELETE FROM Teacher WHERE deptno='03';
    END IF;
RETURN OLD;
END
$DELETE_DEPT_TEACHER$ LANGUAGE PLPGSQL;

CREATE TRIGGER DELETE_DEPT_TEACHER
BEFORE DELETE ON dept
FOR EACH ROW
EXECUTE PROCEDURE RECORD_DELETE_DEPT_TEACHER();

SELECT * FROM dept;
SELECT * FROM Teacher;
DELETE FROM dept WHERE deptno='03';
SELECT * FROM dept;
SELECT * FROM Teacher;

8)
前情提要
CREATE TABLE Student(
    Sno CHAR(9) PRIMARY KEY, 
    Sname CHAR(20) UNIQUE, 
    Ssex CHAR(2), 
    Sage SMALLINT, 
    Sdept CHAR(20)
);
CREATE TABLE Course(
    Cno CHAR(4) PRIMARY KEY, 
    Cname CHAR(40) NOT NULL, 
    Cpno CHAR(4), 
    Ccredit SMALLINT, 
    FOREIGN KEY(Cpno) REFERENCES Course(Cno)
);
CREATE TABLE SC(
    Sno CHAR(9), 
    Cno CHAR(4), 
    Grade SMALLINT, 
    PRIMARY KEY(Sno,Cno), 
    FOREIGN KEY(Sno) REFERENCES Student(Sno), 
    FOREIGN KEY(Cno) REFERENCES Course(Cno)
);
INSERT INTO Student(Sno, Sname, Sage, Sdept) VALUES
    ('201215121', '李勇',  20, 'CS'), 
    ('201215122', '刘晨', 19, 'CS'), 
    ('201215123', '王敏', 18, 'MA'), 
    ('201215125', '张立', 19, 'IS');
INSERT INTO Course(Cno, Cname, Cpno, Ccredit) VALUES
    ('1', '数据库', '5', 4), 
    ('2', '数学', NULL, 2), 
    ('3', '信息系统', '1', 4), 
    ('4', '操作系统', '6', 3), 
    ('5', '数据结构', '7', 4), 
    ('6', '数据处理', NULL, 2), 
    ('7', 'PASCAL语言', '6', 4);
INSERT INTO SC(Sno, Cno, Grade) VALUES
    ('201215121', '1', 92), 
    ('201215121', '2', 85), 
    ('201215121', '3', 88), 
    ('201215122', '2', 90), 
    ('201215122', '3', 80);
①
CREATE TABLE SC_U(
    Sno CHAR(9), 
    Cno CHAR(4), 
    Oldgrade SMALLINT, 
    Newgrade SMALLINT, 
    FOREIGN KEY(Sno) REFERENCES Student(Sno), 
    FOREIGN KEY(Cno) REFERENCES Course(Cno)
);
②
CREATE FUNCTION RECORD_tri_update_sc()
RETURNS TRIGGER AS $tri_update_sc$ DECLARE
BEGIN
    IF(new.Grade>=1.1*old.Grade)
    THEN INSERT INTO SC_U(Sno, Cno, Oldgrade, Newgrade) VALUES(old.Sno, old.Cno, old.Grade, new.Grade);
    END IF;
RETURN NEW;
END
$tri_update_sc$ LANGUAGE PLPGSQL;

CREATE TRIGGER tri_update_sc
AFTER UPDATE OF Grade ON SC
FOR EACH ROW
EXECUTE PROCEDURE RECORD_tri_update_sc();

③
UPDATE SC SET Grade=100 WHERE Sno='201215122' AND Cno='2';
UPDATE SC SET Grade=90 WHERE Sno='201215121' AND Cno='2';
SELECT * FROM SC_U;

9)
ALTER TRIGGER tri_update_sc ON SC RENAME TO update_sc_tri;

10)
①
UPDATE SC SET Grade=90 WHERE Sno='201215122' AND Cno='2';
UPDATE SC SET Grade=85 WHERE Sno='201215121' AND Cno='2';
DELETE FROM SC_U;

②
ALTER TABLE SC DISABLE TRIGGER update_sc_tri;

③
UPDATE SC SET Grade=100 WHERE Sno='201215122' AND Cno='2';
UPDATE SC SET Grade=90 WHERE Sno='201215121' AND Cno='2';

11)
DROP TRIGGER INSERT_OR_UPDATE_SAL ON Teacher;
DROP FUNCTION RECORD_INSERT_OR_UPDATE_SAL();
DROP TRIGGER DELETE_DEPT_TEACHER ON dept;
DROP FUNCTION RECORD_DELETE_DEPT_TEACHER();
DROP TRIGGER update_sc_tri ON SC;
DROP FUNCTION RECORD_tri_update_sc();
