#ifndef Z_FINAL_PROJ_OUTPUT_H
#define Z_FINAL_PROJ_OUTPUT_H
/*
***** ALL RESULTS ARE VERIFIED ******
//--------------------------------------------------------------------
// Normal:
//--------------------------------------------------------------------

[exit] ?: create table emp fields name, lname
Created table: emp

[exit] ?: insert into emp values sepehr, heravi
Inserted: sepehr heravi into emp

[exit] ?: select * from emp


Table name: emp1 - Records: 1

rec                name               lname

[0]              sepehr              heravi

[exit] ?: batch sample

//****************************************************************************

//		CREATE AND INSERT

//****************************************************************************

//---- employee table ----------


[0] make table employee fields  last, 		first, 			dep

Created table: employee


[1] insert into employee values Blow, 		Joe, 			CS

Inserted: Blow Joe CS into employee


[2] insert into employee values Johnson, 	"Jimmy", 		Chemistry

Inserted: Johnson Jimmy Chemistry into employee


[3] insert into employee values Yang, 		Bo, 			CS

Inserted: Yang Bo CS into employee


[4] insert into employee values "Jackson",	Billy, 			Math

Inserted: Jackson Billy Math into employee


[5] insert into employee values Johnson,	Billy, 			"Phys Ed"

Inserted: Johnson Billy Phys Ed into employee


[6] insert into employee values "Van Gogh",	"Jim Bob", 		"Phys Ed"

Inserted: Van Gogh Jim Bob Phys Ed into employee


[7] select * from employee



Table name: employee3 - Records: 6

rec                last               first                 dep

[0]                Blow                 Joe                  CS
[1]             Johnson               Jimmy           Chemistry
[2]                Yang                  Bo                  CS
[3]             Jackson               Billy                Math
[4]             Johnson               Billy             Phys Ed
[5]            Van Gogh             Jim Bob             Phys Ed

//----- student table ----------


[8] make table student fields 	fname, 			lname, 		major, age

Created table: student


[9] insert into student values 	Flo, 			Yao, 		CS, 	20

Inserted: Flo Yao CS 20 into student


[10] insert into student values 	"Flo", 			"Jackson", 	Math,	 			21

Inserted: Flo Jackson Math 21 into student


[11] insert into student values 	Calvin, 		Woo, 		Physics,			22

Inserted: Calvin Woo Physics 22 into student


[12] insert into student values 	"Anna Grace", 	"Del Rio", 	CS,	22

Inserted: Anna Grace Del Rio CS 22 into student


[13] select * from student



Table name: student5 - Records: 4

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20
[1]                 Flo             Jackson                Math                  21
[2]              Calvin                 Woo             Physics                  22
[3]          Anna Grace             Del Rio                  CS                  22

//****************************************************************************

//		SIMPLE SELECT

//****************************************************************************


[14] select * from student



Table name: student6 - Records: 4

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20
[1]                 Flo             Jackson                Math                  21
[2]              Calvin                 Woo             Physics                  22
[3]          Anna Grace             Del Rio                  CS                  22

//------- simple strings -------------------


[15] select * from student where lname = Jackson



Table name: student7 - Records: 1

rec               fname               lname               major                 age

[0]                 Flo             Jackson                Math                  21

//----- quoted strings ---------------------


[16] select * from student where lname = "Del Rio"



Table name: student8 - Records: 1

rec               fname               lname               major                 age

[0]          Anna Grace             Del Rio                  CS                  22

//-------- non-existing string ------------------


[17] select * from student where lname = "Does Not Exist"



Table name: student9 - Records: 0

rec               fname               lname               major                 age


//****************************************************************************

//		RELATIONAL OPERATORS:

//****************************************************************************

//.................

//:Greater Than   :

//.................


[18] select * from student where lname > Yang



Table name: student10 - Records: 1

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20

//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .


[19] select * from student where age > 50



Table name: student11 - Records: 0

rec               fname               lname               major                 age


//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .


[20] select * from student where age  > 53



Table name: student12 - Records: 0

rec               fname               lname               major                 age


//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .


[21] select * from student where age > 54



Table name: student13 - Records: 0

rec               fname               lname               major                 age


//.................

//:Greater Equal  :

//.................


[22] select * from student where lname >= Yang



Table name: student14 - Records: 1

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20

//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .


[23] select * from employee where last >= Jack



Table name: employee15 - Records: 5

rec                last               first                 dep

[0]             Johnson               Jimmy           Chemistry
[1]                Yang                  Bo                  CS
[2]             Jackson               Billy                Math
[3]             Johnson               Billy             Phys Ed
[4]            Van Gogh             Jim Bob             Phys Ed

//.................

//:Less Than      :

//.................

//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .


[24] select * from student where lname < Jackson



Table name: student16 - Records: 1

rec               fname               lname               major                 age

[0]          Anna Grace             Del Rio                  CS                  22

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .


[25] select * from student where age  < 20



Table name: student17 - Records: 0

rec               fname               lname               major                 age


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .


[26] select * from student where age  < 19



Table name: student18 - Records: 0

rec               fname               lname               major                 age


//.................

//:Less Equal     :

//.................


[27] select * from student where lname <= Smith



Table name: student19 - Records: 2

rec               fname               lname               major                 age

[0]                 Flo             Jackson                Math                  21
[1]          Anna Grace             Del Rio                  CS                  22

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .


[28] select * from employee where last <= Peach



Table name: employee20 - Records: 4

rec                last               first                 dep

[0]                Blow                 Joe                  CS
[1]             Johnson               Jimmy           Chemistry
[2]             Jackson               Billy                Math
[3]             Johnson               Billy             Phys Ed

//****************************************************************************

//		LOGICAL OPERATORS

//****************************************************************************

//.................

//:AND            :

//.................


[29] select * from student where fname = "Flo"  and lname = "Yao"



Table name: student21 - Records: 1

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20

//.................

//:OR            :

//.................


[30] select * from student where fname = Flo or lname = Jackson



Table name: student22 - Records: 2

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20
[1]                 Flo             Jackson                Math                  21

//.................

//:OR AND         :

//.................


[31] select * from student where fname = Flo or major = CS and age <= 23



Table name: student23 - Records: 3

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20
[1]                 Flo             Jackson                Math                  21
[2]          Anna Grace             Del Rio                  CS                  22

//.................

//:AND OR AND     :

//.................


[32] select * from student where age <30 and major=CS or major = Physics and lname = Jackson



Table name: student24 - Records: 2

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20
[1]          Anna Grace             Del Rio                  CS                  22

//.................

//:OR AND OR      :

//.................


[33] select * from student where lname = Yang or major = CS and age < 23 or lname = Jackson



Table name: student25 - Records: 3

rec               fname               lname               major                 age

[0]                 Flo                 Yao                  CS                  20
[1]                 Flo             Jackson                Math                  21
[2]          Anna Grace             Del Rio                  CS                  22

[exit] ?: batch test

//****************************************************************************

//		CREATE TABLES AND INSERT RECORDS

//****************************************************************************


[0] make table employee fields  last, 		first, 			dep,  	salary, 	year

Created table: employee


[1] insert into employee values Blow, 		Joe, 			CS,	100000, 	2018

Inserted: Blow Joe CS 100000 2018 into employee


[2] insert into employee values Blow, 		JoAnn,			Physics, 	200000, 	2016

Inserted: Blow JoAnn Physics 200000 2016 into employee


[3] insert into employee values Johnson, 	Jack, 			HR, 	150000, 	2014

Inserted: Johnson Jack HR 150000 2014 into employee


[4] insert into employee values Johnson, 	"Jimmy", 		Chemistry,	140000, 	2018

Inserted: Johnson Jimmy Chemistry 140000 2018 into employee


[5] insert into employee values Yao,	 	Jimmy, 			Math,	145000, 	2014

Inserted: Yao Jimmy Math 145000 2014 into employee


[6] insert into employee values "Yao", 		Flo, 			CS,	147000, 	2012

Inserted: Yao Flo CS 147000 2012 into employee


[7] insert into employee values Yang, 		Bo, 			CS,	160000, 	2013

Inserted: Yang Bo CS 160000 2013 into employee


[8] insert into employee values Jackson,	"Flo", 			Math,	165000, 	2017

Inserted: Jackson Flo Math 165000 2017 into employee


[9] insert into employee values Jackson,	Bo,	 			Chemistry,	130000, 	2011

Inserted: Jackson Bo Chemistry 130000 2011 into employee


[10] insert into employee values "Jackson",	Billy, 			Math,	170000, 	2017

Inserted: Jackson Billy Math 170000 2017 into employee


[11] insert into employee values Johnson,	"Mary Ann", 	Math,		165000, 	2014

Inserted: Johnson Mary Ann Math 165000 2014 into employee


[12] insert into employee values Johnson,	"Billy Bob", 	Physics,	142000, 	2014

Inserted: Johnson Billy Bob Physics 142000 2014 into employee


[13] insert into employee values Johnson,	Billy, 			"Phys Ed",	102000, 	2014

Inserted: Johnson Billy Phys Ed 102000 2014 into employee


[14] insert into employee values "Van Gogh",	Vincent, 		Art,	240000, 	2015

Inserted: Van Gogh Vincent Art 240000 2015 into employee


[15] insert into employee values "Van Gogh",	Vincent, 		CS,	245000, 	2015

Inserted: Van Gogh Vincent CS 245000 2015 into employee


[16] insert into employee values "Van Gogh",	"Jim Bob", 		"Phys Ed",	230000, 	2010

Inserted: Van Gogh Jim Bob Phys Ed 230000 2010 into employee


[17] select * from employee



Table name: employee27 - Records: 16

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]                 Yao               Jimmy                Math              145000                2014
[5]                 Yao                 Flo                  CS              147000                2012
[6]                Yang                  Bo                  CS              160000                2013
[7]             Jackson                 Flo                Math              165000                2017
[8]             Jackson                  Bo           Chemistry              130000                2011
[9]             Jackson               Billy                Math              170000                2017
[10]             Johnson            Mary Ann                Math              165000                2014
[11]             Johnson           Billy Bob             Physics              142000                2014
[12]             Johnson               Billy             Phys Ed              102000                2014
[13]            Van Gogh             Vincent                 Art              240000                2015
[14]            Van Gogh             Vincent                  CS              245000                2015
[15]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[18] make table student fields fname, lname, major, age, company

Created table: student


[19] insert into student values Flo, 			Yao, 		CS, 	20, 	Google

Inserted: Flo Yao CS 20 Google into student


[20] insert into student values Bo, 				Yang, 		CS, 				28,		Microsoft

Inserted: Bo Yang CS 28 Microsoft into student


[21] insert into student values "Flo", 			"Jackson", 	Math,	21,		Google

Inserted: Flo Jackson Math 21 Google into student


[22] insert into student values "Greg", 			"Pearson", 	Physics,			20,		Amazon

Inserted: Greg Pearson Physics 20 Amazon into student


[23] insert into student values "Jim Bob", 		Smith, 		Math,	23,		Verizon

Inserted: Jim Bob Smith Math 23 Verizon into student


[24] insert into student values Calvin, 			Woo, 		Physics,			22,		Uber

Inserted: Calvin Woo Physics 22 Uber into student


[25] insert into student values "Anna Grace", 	"Del Rio", 	CS,	 	22,		USAF

Inserted: Anna Grace Del Rio CS 22 USAF into student


[26] insert into student values "Teresa Mae", 	Gowers, 	Chemistry,	22,		Verizon

Inserted: Teresa Mae Gowers Chemistry 22 Verizon into student


[27] insert into student values Alex,			Smith,		"Gender Studies", 	53,		Amazon

Inserted: Alex Smith Gender Studies 53 Amazon into student


[28] select * from student



Table name: student29 - Records: 9

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                 Flo             Jackson                Math                  21              Google
[3]                Greg             Pearson             Physics                  20              Amazon
[4]             Jim Bob               Smith                Math                  23             Verizon
[5]              Calvin                 Woo             Physics                  22                Uber
[6]          Anna Grace             Del Rio                  CS                  22                USAF
[7]          Teresa Mae              Gowers           Chemistry                  22             Verizon
[8]                Alex               Smith      Gender Studies                  53              Amazon

//****************************************************************************

//		SIMPLE SELECT:

//****************************************************************************


[29] select * from student



Table name: student30 - Records: 9

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                 Flo             Jackson                Math                  21              Google
[3]                Greg             Pearson             Physics                  20              Amazon
[4]             Jim Bob               Smith                Math                  23             Verizon
[5]              Calvin                 Woo             Physics                  22                Uber
[6]          Anna Grace             Del Rio                  CS                  22                USAF
[7]          Teresa Mae              Gowers           Chemistry                  22             Verizon
[8]                Alex               Smith      Gender Studies                  53              Amazon

//------- simple strings -------------------


[30] select * from student where lname = Jackson



Table name: student31 - Records: 1

rec               fname               lname               major                 age             company

[0]                 Flo             Jackson                Math                  21              Google


[31] select * from student where major = CS



Table name: student32 - Records: 3

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]          Anna Grace             Del Rio                  CS                  22                USAF


[32] select * from student where company = Uber



Table name: student33 - Records: 1

rec               fname               lname               major                 age             company

[0]              Calvin                 Woo             Physics                  22                Uber

//----- quoted strings ---------------------


[33] select * from student where lname = "Del Rio"



Table name: student34 - Records: 1

rec               fname               lname               major                 age             company

[0]          Anna Grace             Del Rio                  CS                  22                USAF


[34] select * from student where fname = "Jim Bob"



Table name: student35 - Records: 1

rec               fname               lname               major                 age             company

[0]             Jim Bob               Smith                Math                  23             Verizon


[35] select * from student where fname = "Anna Grace"



Table name: student36 - Records: 1

rec               fname               lname               major                 age             company

[0]          Anna Grace             Del Rio                  CS                  22                USAF


[36] select * from student where fname = "Teresa Mae"



Table name: student37 - Records: 1

rec               fname               lname               major                 age             company

[0]          Teresa Mae              Gowers           Chemistry                  22             Verizon

//-------- non-existing string ------------------


[37] select * from student where lname = "Does Not Exist"



Table name: student38 - Records: 0

rec               fname               lname               major                 age             company


//****************************************************************************

//		RELATIONAL OPERATORS:

//****************************************************************************

//.................

//:Greater Than   :

//.................


[38] select * from student where lname > Yang



Table name: student39 - Records: 1

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google


[39] select * from student where major > Math



Table name: student40 - Records: 2

rec               fname               lname               major                 age             company

[0]                Greg             Pearson             Physics                  20              Amazon
[1]              Calvin                 Woo             Physics                  22                Uber


[40] select * from employee where salary > 200000



Table name: employee41 - Records: 3

rec                last               first                 dep              salary                year

[0]            Van Gogh             Vincent                 Art              240000                2015
[1]            Van Gogh             Vincent                  CS              245000                2015
[2]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[41] select * from employee where dep > Chemistry



Table name: employee42 - Records: 9

rec                last               first                 dep              salary                year

[0]                Blow               JoAnn             Physics              200000                2016
[1]             Johnson                Jack                  HR              150000                2014
[2]                 Yao               Jimmy                Math              145000                2014
[3]             Jackson                 Flo                Math              165000                2017
[4]             Jackson               Billy                Math              170000                2017
[5]             Johnson            Mary Ann                Math              165000                2014
[6]             Johnson           Billy Bob             Physics              142000                2014
[7]             Johnson               Billy             Phys Ed              102000                2014
[8]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[42] select * from employee where last > Jackson



Table name: employee43 - Records: 11

rec                last               first                 dep              salary                year

[0]             Johnson                Jack                  HR              150000                2014
[1]             Johnson               Jimmy           Chemistry              140000                2018
[2]                 Yao               Jimmy                Math              145000                2014
[3]                 Yao                 Flo                  CS              147000                2012
[4]                Yang                  Bo                  CS              160000                2013
[5]             Johnson            Mary Ann                Math              165000                2014
[6]             Johnson           Billy Bob             Physics              142000                2014
[7]             Johnson               Billy             Phys Ed              102000                2014
[8]            Van Gogh             Vincent                 Art              240000                2015
[9]            Van Gogh             Vincent                  CS              245000                2015
[10]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[43] select * from employee where first > "Billy Bob"



Table name: employee44 - Records: 13

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]                 Yao               Jimmy                Math              145000                2014
[5]                 Yao                 Flo                  CS              147000                2012
[6]                Yang                  Bo                  CS              160000                2013
[7]             Jackson                 Flo                Math              165000                2017
[8]             Jackson                  Bo           Chemistry              130000                2011
[9]             Johnson            Mary Ann                Math              165000                2014
[10]            Van Gogh             Vincent                 Art              240000                2015
[11]            Van Gogh             Vincent                  CS              245000                2015
[12]            Van Gogh             Jim Bob             Phys Ed              230000                2010

//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .


[44] select * from student where age > 50



Table name: student45 - Records: 1

rec               fname               lname               major                 age             company

[0]                Alex               Smith      Gender Studies                  53              Amazon


[45] select * from student where age > 35



Table name: student46 - Records: 1

rec               fname               lname               major                 age             company

[0]                Alex               Smith      Gender Studies                  53              Amazon


[46] select * from student where fname > T



Table name: student47 - Records: 1

rec               fname               lname               major                 age             company

[0]          Teresa Mae              Gowers           Chemistry                  22             Verizon


[47] select * from employee where salary > 130000



Table name: employee48 - Records: 13

rec                last               first                 dep              salary                year

[0]                Blow               JoAnn             Physics              200000                2016
[1]             Johnson                Jack                  HR              150000                2014
[2]             Johnson               Jimmy           Chemistry              140000                2018
[3]                 Yao               Jimmy                Math              145000                2014
[4]                 Yao                 Flo                  CS              147000                2012
[5]                Yang                  Bo                  CS              160000                2013
[6]             Jackson                 Flo                Math              165000                2017
[7]             Jackson               Billy                Math              170000                2017
[8]             Johnson            Mary Ann                Math              165000                2014
[9]             Johnson           Billy Bob             Physics              142000                2014
[10]            Van Gogh             Vincent                 Art              240000                2015
[11]            Van Gogh             Vincent                  CS              245000                2015
[12]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[48] select * from employee where  year > 2009



Table name: employee49 - Records: 16

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]                 Yao               Jimmy                Math              145000                2014
[5]                 Yao                 Flo                  CS              147000                2012
[6]                Yang                  Bo                  CS              160000                2013
[7]             Jackson                 Flo                Math              165000                2017
[8]             Jackson                  Bo           Chemistry              130000                2011
[9]             Jackson               Billy                Math              170000                2017
[10]             Johnson            Mary Ann                Math              165000                2014
[11]             Johnson           Billy Bob             Physics              142000                2014
[12]             Johnson               Billy             Phys Ed              102000                2014
[13]            Van Gogh             Vincent                 Art              240000                2015
[14]            Van Gogh             Vincent                  CS              245000                2015
[15]            Van Gogh             Jim Bob             Phys Ed              230000                2010

//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .


[49] select * from student where age  > 53



Table name: student50 - Records: 0

rec               fname               lname               major                 age             company



[50] select * from student where lname > Yao



Table name: student51 - Records: 0

rec               fname               lname               major                 age             company



[51] select * from student where fname > "Teresa Mae"



Table name: student52 - Records: 0

rec               fname               lname               major                 age             company



[52] select * from employee where last > "Van Gogh"



Table name: employee53 - Records: 3

rec                last               first                 dep              salary                year

[0]                 Yao               Jimmy                Math              145000                2014
[1]                 Yao                 Flo                  CS              147000                2012
[2]                Yang                  Bo                  CS              160000                2013


[53] select * from employee where first > Vincent



Table name: employee54 - Records: 0

rec                last               first                 dep              salary                year



[54] select * from employee where salary > 260000



Table name: employee55 - Records: 0

rec                last               first                 dep              salary                year


//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .


[55] select * from student where age > 54



Table name: student56 - Records: 0

rec               fname               lname               major                 age             company



[56] select * from student where lname > Zoolander



Table name: student57 - Records: 0

rec               fname               lname               major                 age             company



[57] select * from employee where last > Zoolaner



Table name: employee58 - Records: 0

rec                last               first                 dep              salary                year



[58] select * from employee where first > Xu



Table name: employee59 - Records: 0

rec                last               first                 dep              salary                year


//.................

//:Greater Equal  :

//.................


[59] select * from student where lname >= Yang



Table name: student60 - Records: 2

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft


[60] select * from student where age >= 40



Table name: student61 - Records: 1

rec               fname               lname               major                 age             company

[0]                Alex               Smith      Gender Studies                  53              Amazon

//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .


[61] select * from employee where last >= Jack



Table name: employee62 - Records: 14

rec                last               first                 dep              salary                year

[0]             Johnson                Jack                  HR              150000                2014
[1]             Johnson               Jimmy           Chemistry              140000                2018
[2]                 Yao               Jimmy                Math              145000                2014
[3]                 Yao                 Flo                  CS              147000                2012
[4]                Yang                  Bo                  CS              160000                2013
[5]             Jackson                 Flo                Math              165000                2017
[6]             Jackson                  Bo           Chemistry              130000                2011
[7]             Jackson               Billy                Math              170000                2017
[8]             Johnson            Mary Ann                Math              165000                2014
[9]             Johnson           Billy Bob             Physics              142000                2014
[10]             Johnson               Billy             Phys Ed              102000                2014
[11]            Van Gogh             Vincent                 Art              240000                2015
[12]            Van Gogh             Vincent                  CS              245000                2015
[13]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[62] select * from employee where first >= Bill



Table name: employee63 - Records: 16

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]                 Yao               Jimmy                Math              145000                2014
[5]                 Yao                 Flo                  CS              147000                2012
[6]                Yang                  Bo                  CS              160000                2013
[7]             Jackson                 Flo                Math              165000                2017
[8]             Jackson                  Bo           Chemistry              130000                2011
[9]             Jackson               Billy                Math              170000                2017
[10]             Johnson            Mary Ann                Math              165000                2014
[11]             Johnson           Billy Bob             Physics              142000                2014
[12]             Johnson               Billy             Phys Ed              102000                2014
[13]            Van Gogh             Vincent                 Art              240000                2015
[14]            Van Gogh             Vincent                  CS              245000                2015
[15]            Van Gogh             Jim Bob             Phys Ed              230000                2010


[63] select * from employee where salary >= 235000



Table name: employee64 - Records: 2

rec                last               first                 dep              salary                year

[0]            Van Gogh             Vincent                 Art              240000                2015
[1]            Van Gogh             Vincent                  CS              245000                2015

//.................

//:Less Than      :

//.................

//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .


[64] select * from student where lname < Jackson



Table name: student65 - Records: 2

rec               fname               lname               major                 age             company

[0]          Anna Grace             Del Rio                  CS                  22                USAF
[1]          Teresa Mae              Gowers           Chemistry                  22             Verizon


[65] select * from student where major < Math



Table name: student66 - Records: 5

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]          Anna Grace             Del Rio                  CS                  22                USAF
[3]          Teresa Mae              Gowers           Chemistry                  22             Verizon
[4]                Alex               Smith      Gender Studies                  53              Amazon


[66] select * from student where fname < "Jim Bob"



Table name: student67 - Records: 7

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                 Flo             Jackson                Math                  21              Google
[3]                Greg             Pearson             Physics                  20              Amazon
[4]              Calvin                 Woo             Physics                  22                Uber
[5]          Anna Grace             Del Rio                  CS                  22                USAF
[6]                Alex               Smith      Gender Studies                  53              Amazon


[67] select * from employee where salary < 200000



Table name: employee68 - Records: 12

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]             Johnson                Jack                  HR              150000                2014
[2]             Johnson               Jimmy           Chemistry              140000                2018
[3]                 Yao               Jimmy                Math              145000                2014
[4]                 Yao                 Flo                  CS              147000                2012
[5]                Yang                  Bo                  CS              160000                2013
[6]             Jackson                 Flo                Math              165000                2017
[7]             Jackson                  Bo           Chemistry              130000                2011
[8]             Jackson               Billy                Math              170000                2017
[9]             Johnson            Mary Ann                Math              165000                2014
[10]             Johnson           Billy Bob             Physics              142000                2014
[11]             Johnson               Billy             Phys Ed              102000                2014


[68] select * from employee where dep < CS



Table name: employee69 - Records: 1

rec                last               first                 dep              salary                year

[0]            Van Gogh             Vincent                 Art              240000                2015


[69] select * from employee where last < Jackson



Table name: employee70 - Records: 2

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016


[70] select * from employee where first < "Billy Bob"



Table name: employee71 - Records: 2

rec                last               first                 dep              salary                year

[0]             Jackson               Billy                Math              170000                2017
[1]             Johnson               Billy             Phys Ed              102000                2014

//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .


[71] select * from student where age  < 20



Table name: student72 - Records: 0

rec               fname               lname               major                 age             company



[72] select * from student where lname < "Del Rio"



Table name: student73 - Records: 0

rec               fname               lname               major                 age             company



[73] select * from student where fname < Alex



Table name: student74 - Records: 0

rec               fname               lname               major                 age             company



[74] select * from employee where last < Blow



Table name: employee75 - Records: 0

rec                last               first                 dep              salary                year



[75] select * from employee where first < Billy



Table name: employee76 - Records: 0

rec                last               first                 dep              salary                year



[76] select * from employee where salary < 100000



Table name: employee77 - Records: 0

rec                last               first                 dep              salary                year


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .


[77] select * from student where age  < 19



Table name: student78 - Records: 0

rec               fname               lname               major                 age             company



[78] select * from student where lname < Adams



Table name: student79 - Records: 0

rec               fname               lname               major                 age             company



[79] select * from student where fname < Adam



Table name: student80 - Records: 0

rec               fname               lname               major                 age             company



[80] select * from employee where last < Alex



Table name: employee81 - Records: 0

rec                last               first                 dep              salary                year



[81] select * from employee where first < Avory



Table name: employee82 - Records: 0

rec                last               first                 dep              salary                year



[82] select * from employee where dep < Alchemy



Table name: employee83 - Records: 0

rec                last               first                 dep              salary                year


//.................

//:Less Equal     :

//.................


[83] select * from student where lname <= Smith



Table name: student84 - Records: 6

rec               fname               lname               major                 age             company

[0]                 Flo             Jackson                Math                  21              Google
[1]                Greg             Pearson             Physics                  20              Amazon
[2]             Jim Bob               Smith                Math                  23             Verizon
[3]          Anna Grace             Del Rio                  CS                  22                USAF
[4]          Teresa Mae              Gowers           Chemistry                  22             Verizon
[5]                Alex               Smith      Gender Studies                  53              Amazon


[84] select * from student where fname <= Greg



Table name: student85 - Records: 7

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                 Flo             Jackson                Math                  21              Google
[3]                Greg             Pearson             Physics                  20              Amazon
[4]              Calvin                 Woo             Physics                  22                Uber
[5]          Anna Grace             Del Rio                  CS                  22                USAF
[6]                Alex               Smith      Gender Studies                  53              Amazon


[85] select * from student where age <= 40



Table name: student86 - Records: 8

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                 Flo             Jackson                Math                  21              Google
[3]                Greg             Pearson             Physics                  20              Amazon
[4]             Jim Bob               Smith                Math                  23             Verizon
[5]              Calvin                 Woo             Physics                  22                Uber
[6]          Anna Grace             Del Rio                  CS                  22                USAF
[7]          Teresa Mae              Gowers           Chemistry                  22             Verizon

//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .


[86] select * from employee where last <= Peach



Table name: employee87 - Records: 10

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]             Jackson                 Flo                Math              165000                2017
[5]             Jackson                  Bo           Chemistry              130000                2011
[6]             Jackson               Billy                Math              170000                2017
[7]             Johnson            Mary Ann                Math              165000                2014
[8]             Johnson           Billy Bob             Physics              142000                2014
[9]             Johnson               Billy             Phys Ed              102000                2014


[87] select * from employee where first <= Gary



Table name: employee88 - Records: 7

rec                last               first                 dep              salary                year

[0]                 Yao                 Flo                  CS              147000                2012
[1]                Yang                  Bo                  CS              160000                2013
[2]             Jackson                 Flo                Math              165000                2017
[3]             Jackson                  Bo           Chemistry              130000                2011
[4]             Jackson               Billy                Math              170000                2017
[5]             Johnson           Billy Bob             Physics              142000                2014
[6]             Johnson               Billy             Phys Ed              102000                2014


[88] select * from employee where salary <= 23500



Table name: employee89 - Records: 14

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]                 Yao               Jimmy                Math              145000                2014
[5]                 Yao                 Flo                  CS              147000                2012
[6]                Yang                  Bo                  CS              160000                2013
[7]             Jackson                 Flo                Math              165000                2017
[8]             Jackson                  Bo           Chemistry              130000                2011
[9]             Jackson               Billy                Math              170000                2017
[10]             Johnson            Mary Ann                Math              165000                2014
[11]             Johnson           Billy Bob             Physics              142000                2014
[12]             Johnson               Billy             Phys Ed              102000                2014
[13]            Van Gogh             Jim Bob             Phys Ed              230000                2010

//****************************************************************************

//		LOGICAL OPERATORS

//****************************************************************************

//.................

//:AND            :

//.................


[89] select * from student where fname = "Flo" and lname = "Yao"



Table name: student90 - Records: 1

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google


[90] select * from student where major = "CS" and age < 25



Table name: student91 - Records: 2

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]          Anna Grace             Del Rio                  CS                  22                USAF


[91] select * from student where major < Math and age > 25



Table name: student92 - Records: 2

rec               fname               lname               major                 age             company

[0]                  Bo                Yang                  CS                  28           Microsoft
[1]                Alex               Smith      Gender Studies                  53              Amazon


[92] select * from employee where dep = CS and salary > 150000



Table name: employee93 - Records: 2

rec                last               first                 dep              salary                year

[0]                Yang                  Bo                  CS              160000                2013
[1]            Van Gogh             Vincent                  CS              245000                2015


[93] select * from employee where last = Jackson and year < 2015



Table name: employee94 - Records: 1

rec                last               first                 dep              salary                year

[0]             Jackson                  Bo           Chemistry              130000                2011


[94] select * from employee where last = Johnson and year >=2014



Table name: employee95 - Records: 5

rec                last               first                 dep              salary                year

[0]             Johnson                Jack                  HR              150000                2014
[1]             Johnson               Jimmy           Chemistry              140000                2018
[2]             Johnson            Mary Ann                Math              165000                2014
[3]             Johnson           Billy Bob             Physics              142000                2014
[4]             Johnson               Billy             Phys Ed              102000                2014

//.................

//:OR            :

//.................


[95] select * from student where fname = Flo or lname = Jackson



Table name: student96 - Records: 2

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                 Flo             Jackson                Math                  21              Google


[96] select * from student where age >=40  or company = Verizon



Table name: student97 - Records: 3

rec               fname               lname               major                 age             company

[0]             Jim Bob               Smith                Math                  23             Verizon
[1]          Teresa Mae              Gowers           Chemistry                  22             Verizon
[2]                Alex               Smith      Gender Studies                  53              Amazon


[97] select * from employee where first = Bo or last = Johnson



Table name: employee98 - Records: 7

rec                last               first                 dep              salary                year

[0]             Johnson                Jack                  HR              150000                2014
[1]             Johnson               Jimmy           Chemistry              140000                2018
[2]                Yang                  Bo                  CS              160000                2013
[3]             Jackson                  Bo           Chemistry              130000                2011
[4]             Johnson            Mary Ann                Math              165000                2014
[5]             Johnson           Billy Bob             Physics              142000                2014
[6]             Johnson               Billy             Phys Ed              102000                2014


[98] select * from employee where year >= 2015 or dep = CS



Table name: employee99 - Records: 9

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson               Jimmy           Chemistry              140000                2018
[3]                 Yao                 Flo                  CS              147000                2012
[4]                Yang                  Bo                  CS              160000                2013
[5]             Jackson                 Flo                Math              165000                2017
[6]             Jackson               Billy                Math              170000                2017
[7]            Van Gogh             Vincent                 Art              240000                2015
[8]            Van Gogh             Vincent                  CS              245000                2015

//.................

//:OR AND         :

//.................


[99] select * from student where fname = Flo or major = CS and age <= 23



Table name: student100 - Records: 3

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                 Flo             Jackson                Math                  21              Google
[2]          Anna Grace             Del Rio                  CS                  22                USAF


[100] select * from student where lname = Jackson or age < 23 and company > Uber



Table name: student101 - Records: 2

rec               fname               lname               major                 age             company

[0]                 Flo             Jackson                Math                  21              Google
[1]          Teresa Mae              Gowers           Chemistry                  22             Verizon


[101] select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000



Table name: employee102 - Records: 5

rec                last               first                 dep              salary                year

[0]             Jackson                 Flo                Math              165000                2017
[1]             Jackson               Billy                Math              170000                2017
[2]            Van Gogh             Vincent                 Art              240000                2015
[3]            Van Gogh             Vincent                  CS              245000                2015
[4]            Van Gogh             Jim Bob             Phys Ed              230000                2010

//.................

//:AND OR AND     :

//.................


[102] select * from student where age <30 and major=CS or major = Physics and company = Amazon



Table name: student103 - Records: 4

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                Greg             Pearson             Physics                  20              Amazon
[3]          Anna Grace             Del Rio                  CS                  22                USAF


[103] select * from student where age <=40 and company=Uber or major = CS and company = Google



Table name: student104 - Records: 2

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]              Calvin                 Woo             Physics                  22                Uber


[104] select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"



Table name: employee105 - Records: 3

rec                last               first                 dep              salary                year

[0]                Yang                  Bo                  CS              160000                2013
[1]            Van Gogh             Vincent                 Art              240000                2015
[2]            Van Gogh             Vincent                  CS              245000                2015

//.................

//:OR AND OR      :

//.................


[105] select * from student where lname = Yang or major = CS and age < 23 or company = Google



Table name: student106 - Records: 4

rec               fname               lname               major                 age             company

[0]                 Flo                 Yao                  CS                  20              Google
[1]                  Bo                Yang                  CS                  28           Microsoft
[2]                 Flo             Jackson                Math                  21              Google
[3]          Anna Grace             Del Rio                  CS                  22                USAF


[106] select * from student where major = Physics or major = Math and company = Google or lname = Jackson



Table name: student107 - Records: 3

rec               fname               lname               major                 age             company

[0]                 Flo             Jackson                Math                  21              Google
[1]                Greg             Pearson             Physics                  20              Amazon
[2]              Calvin                 Woo             Physics                  22                Uber


[107] select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 265000



Table name: employee108 - Records: 8

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]                 Yao                 Flo                  CS              147000                2012
[3]                Yang                  Bo                  CS              160000                2013
[4]             Jackson                 Flo                Math              165000                2017
[5]             Jackson               Billy                Math              170000                2017
[6]            Van Gogh             Vincent                 Art              240000                2015
[7]            Van Gogh             Vincent                  CS              245000                2015

[exit] ?: select * from employee


Table name: employee109 - Records: 16

rec                last               first                 dep              salary                year

[0]                Blow                 Joe                  CS              100000                2018
[1]                Blow               JoAnn             Physics              200000                2016
[2]             Johnson                Jack                  HR              150000                2014
[3]             Johnson               Jimmy           Chemistry              140000                2018
[4]                 Yao               Jimmy                Math              145000                2014
[5]                 Yao                 Flo                  CS              147000                2012
[6]                Yang                  Bo                  CS              160000                2013
[7]             Jackson                 Flo                Math              165000                2017
[8]             Jackson                  Bo           Chemistry              130000                2011
[9]             Jackson               Billy                Math              170000                2017
[10]             Johnson            Mary Ann                Math              165000                2014
[11]             Johnson           Billy Bob             Physics              142000                2014
[12]             Johnson               Billy             Phys Ed              102000                2014
[13]            Van Gogh             Vincent                 Art              240000                2015
[14]            Van Gogh             Vincent                  CS              245000                2015
[15]            Van Gogh             Jim Bob             Phys Ed              230000                2010

[exit] ?: select * from employee where last = "Van gogh" or salary > 150000


Table name: employee110 - Records: 8

rec                last               first                 dep              salary                year

[0]                Blow               JoAnn             Physics              200000                2016
[1]                Yang                  Bo                  CS              160000                2013
[2]             Jackson                 Flo                Math              165000                2017
[3]             Jackson               Billy                Math              170000                2017
[4]             Johnson            Mary Ann                Math              165000                2014
[5]            Van Gogh             Vincent                 Art              240000                2015
[6]            Van Gogh             Vincent                  CS              245000                2015
[7]            Van Gogh             Jim Bob             Phys Ed              230000                2010

[exit] ?: exit
Tables Used: emp employee student



================================



==============END=================
Press <RETURN> to close this window...


[Process completed]




================================



==============END=================


*/
#endif // Z_FINAL_PROJ_OUTPUT_H
