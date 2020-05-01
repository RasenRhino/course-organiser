#include "file.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#include "../course/course.h"

FILE* open_course_db(int mode) {
    FILE* db = (FILE*)malloc(sizeof(FILE));
    if (db) {
        switch (mode) {
            case READ:
                db = fopen("database/course.db", "rb");
                break;
            case WRITE:
                db = fopen("database/course.db", "ab");
                break;
            default:
                db = NULL;
                break;
        }
        return db;
    }
    return NULL;
}

void close_db(FILE* db) {
    if (db)
        fclose(db);
}

int insert_course_db(struct course* record) {
    FILE* db = open_course_db(WRITE);
    if (db) {
        if (fwrite(record, sizeof(struct course), 1, db)) {
            close_db(db);
            return 1;
        }
        close_db(db);
        return 0;
    }
    return -1;
}

struct list* load_course_db() {
    struct list* courses = init_list();
    FILE* db = open_course_db(READ);
    if (db) {
        struct course* temp = init_course();
        while (fread(temp, sizeof(struct course), 1, db)) {
            insert_list(courses, temp, sizeof(struct course));
            memset(temp, 0, sizeof(struct course));
        }
        close_db(db);
        return courses;
    }
    return NULL;
}

