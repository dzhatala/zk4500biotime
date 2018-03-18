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

/* desc fpinfo;*/
 
 /*
 select fpinfo.* ,mdl_user.username ,mdl_user.firstname,mdl_user.middlename,mdl_user.lastname 
from fpinfo,mdl_user where fpinfo.person_id=mdl_user.id ;



*/

/**
select fpinfo.* ,mdl_user.username ,mdl_user.firstname,mdl_user.middlename,mdl_user.lastname ,mdl_user.id
from fpinfo right join mdl_user on fpinfo.person_id=mdl_user.id
**/
 
 