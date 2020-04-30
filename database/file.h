#ifndef _FILE_H_
#define _FILE_H_

#include "../course/course.h"
#include "../exam/exam.h"
//#include "../info/info.h"
#include "../list/list.h"

#include <stdio.h>

// course related

enum modes {
    READ,
    WRITE,
};

FILE* open_course_db(int mode);
int insert_course_record(FILE *db, struct course *record);
struct list* load_course_db();


void close_db(FILE *db);

#endif
