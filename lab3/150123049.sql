
create database 25jan2018;

use database 25ja2018;

create table cc( cid CHAR(10) UNIQUE NOT NULL, credits int, PRIMARY KEY(cid));
--primary key should be cid since we cannot have multiple courses

CREATE TABLE ett( cid CHAR(10) UNIQUE NOT NULL, edate DATE, estime TIME, eetime TIME, PRIMARY KEY(cid, edate, estime) );
-- one exam can have multiple records, so we make cid, date and start time as primar key together

create table cwsl( roll INT UNIQUE,  cid CHAR(10) NOT NULL, name CHAR(50) NOT NULL, email CHAR(50) UNIQUE, sr INT, PRIMARY KEY(roll, cid) );
--a student will have multiple courses, so cid ans roll is our primary key

create temporary table cc_temp( cid CHAR(10) UNIQUE, credits int, PRIMARY KEY(cid));

CREATE TEMPORARY TABLE ett_temp( cid CHAR(10) UNIQUE, edate DATE, estime TIME, eetime TIME, PRIMARY KEY(cid, edate, estime) );

create temporary table cwsl_temp( roll INT UNIQUE,  cid CHAR(10) NOT NULL, name CHAR(50), email CHAR(50) UNIQUE, sr INT, PRIMARY KEY(roll, cid) );

create table cc_clone LIKE cc;

create table ett_clone LIKE ett;

create table cwsl_clone LIKE cwsl;

source 150123049_ett.sql;
source 150123049_cc.sql;
source 150123049_cwsl.sql;