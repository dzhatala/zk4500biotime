use moodle;
drop table if exists FPINFO;
create table FPINFO
(
   FPINFO_ID            int not null,
   PERSON_ID            bigint(10) not null,
   LEFT_THUMB           int,
   LEFT_INDEX           int,
   LEFT_MIDDLE          int,
   LEFT_RING            int,
   LEFT_PINKY           int,
   RIGHT_THUMB          int,
   RIGHT_INDEX          int,
   RIGHT_MIDDLE         int,
   RIGHT_RING           int,
   RIGHT_PINKY          int,
   primary key (FPINFO_ID),
   unique index  (PERSON_ID) ,
   FOREIGN KEY (PERSON_ID)
      REFERENCES mdl_user(id)
      ON UPDATE restrict ON DELETE RESTRICT
      
) engine =innodb;
alter table FPINFO CHANGE FPINFO_ID FPINFO_ID int AUTO_increment;


use moodle;

drop table if exists IDENTIFIED1N;
create table IDENTIFIED1N
(
   IDENTIFIED1N_ID            int not null,
   TRIALDATE             datetime default current_timestamp,
   FPID					int default -1,
   SCORE					int default -1,
   PFN					int default -1,
   primary key (IDENTIFIED1N_ID)
      
) engine =innodb;
alter table IDENTIFIED1N CHANGE IDENTIFIED1N_ID IDENTIFIED1N_ID int AUTO_increment;

select * from IDENTIFIED1N;


/* desc fpinfo;*/
 
 /*
 select fpinfo.* ,mdl_user.username ,mdl_user.firstname,mdl_user.middlename,mdl_user.lastname 
from fpinfo,mdl_user where fpinfo.person_id=mdl_user.id ;



*/

/**
select fpinfo.* ,mdl_user.username ,mdl_user.firstname,mdl_user.middlename,mdl_user.lastname ,mdl_user.id
from fpinfo right join mdl_user on fpinfo.person_id=mdl_user.id
**/
 
 
/***IDENTIFIED PERSON ***/
 
select IDENTIFIED1N.*,fpinfo.person_id,mdl_user.username,mdl_user.username,mdl_user.firstname,mdl_user.lastname from IDENTIFIED1N, fpinfo,mdl_user where ((IDENTIFIED1N.fpid=fpinfo.RIGHT_INDEX) OR 
(IDENTIFIED1N.fpid=fpinfo.RIGHT_THUMB)OR
(IDENTIFIED1N.fpid=fpinfo.RIGHT_INDEX)OR
(IDENTIFIED1N.fpid=fpinfo.RIGHT_MIDDLE)OR
(IDENTIFIED1N.fpid=fpinfo.RIGHT_RING)OR
(IDENTIFIED1N.fpid=fpinfo.RIGHT_PINKY)OR
(IDENTIFIED1N.fpid=fpinfo.LEFT_THUMB)OR
(IDENTIFIED1N.fpid=fpinfo.LEFT_INDEX)OR
(IDENTIFIED1N.fpid=fpinfo.LEFT_MIDDLE)OR
(IDENTIFIED1N.fpid=fpinfo.LEFT_RING)OR
(IDENTIFIED1N.fpid=fpinfo.LEFT_PINKY)OR
0) AND person_id=mdl_user.id order by trialdate;

 
 /*****/