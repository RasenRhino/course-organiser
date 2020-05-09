#include "menu.h"

#include <stdio.h>

#include "course_index.h"
#include "course_operation.h"
#include "exam_index.h"
#include "exam_operation.h"
#include "util.h"

struct course_index *course_index;

void main_menu() {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - MAIN MENU");
        nl();
        print_datetime(get_time());
        nl();
        nl();
        printf("1. Courses\n");
        printf("2. Exams\n");
        printf("3. Info\n");
        printf("4. Exit\n");
        nl();
        printf("Your Choice : ");
        scanf("%d", &control);
        flush_stdin_buffer();
        switch (control) {
            case 1:
                course_menu();
                break;
            case 2:
                exam_menu();
                break;
            case 3:
                // info_menu();
                break;
            case 4:
                return;
            default:
                printf("Invalid option. Press enter to continue.");
                getchar();
        }
    }
}

void course_menu() {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - COURSE MENU");
        nl();
        print_datetime(get_time());
        nl();
        nl();
        printf("1. Course(Display, Edit, Delete)\n");
        printf("2. Add Course\n");
        printf("3. Sort Courses\n");
        printf("4. Return\n");
        nl();
        printf("Your Choice : ");
        scanf("%d", &control);
        flush_stdin_buffer();
        switch (control) {
            case 1:
                display_all_courses_menu();
                break;
            case 2:
                insert_course_operation();
                break;
            case 3:
                sort_course_menu();
                break;
            case 4:
                return;
            default:
                printf("Invalid option. Press enter to continue.");
                getchar();
        }
    }
}

void display_all_courses_menu() {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - COURSE");
        nl();
        print_datetime(get_time());
        nl();
        printf("\nLIST OF ALL COURSES\n\n");
        if (!(course_index->size)) {
            printf("No Courses to display.\n");
            printf("\nPress enter to continue...");
            getchar();
            return;
        } else {
            display_code_name_course_operation();
            printf("\nSelect a course or press '0' to continue : ");
            scanf("%d", &control);
            flush_stdin_buffer();
            if (control == 0) {
                break;
            } else if (control > 0 && control <= course_index->size) {
                display_course_menu(control - 1);
            } else {
                continue;
            }
        }
    }
}

void display_course_menu(int index) {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - COURSE");
        nl();
        print_datetime(get_time());
        nl();
        nl();
        print_course(course_index->c[index]);
        if (exam_index->size) {
            printf("\nExams:\n");
            print_exams_for_course(course_index->c[index]);
        }
        nl();
        printf("1. Add Exam\n");
        printf("2. Edit Course\n");
        printf("3. Delete Course\n");
        printf("4. Return\n");
        nl();
        printf("Your Choice : ");
        scanf("%d", &control);
        flush_stdin_buffer();
        switch (control) {
            case 1:
                insert_exam_operation(course_index->c[index]);
                return;
            case 2:
                edit_course_operation(course_index->c[index]);
                return;
            case 3:
                printf("Are you sure you want to delete this course(y/n)? ");
                control = getchar();
                if (control == (int)'y' || control == (int)'Y') {
                    delete_course_operation(course_index->c[index]);
                }
                printf("\nPress enter to continue...");
                getchar();
                return;
            case 4:
                return;
            default:
                printf("Invalid option. Press enter to continue.");
                getchar();
        }
    }
}

void sort_course_menu() {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - SORT COURSE MENU");
        nl();
        print_datetime(get_time());
        nl();
        nl();
        printf("1. Sort by Course Code\n");
        printf("2. Sort by Course Name\n");
        printf("3. Sort by Course Credit\n");
        printf("4. Display All Courses\n");
        printf("5. Return\n");
        nl();
        printf("Your Choice : ");
        scanf("%d", &control);
        flush_stdin_buffer();
        switch (control) {
            case 1:
                sort_course_index(COURSE_CODE);
                break;
            case 2:
                sort_course_index(COURSE_NAME);
                break;
            case 3:
                sort_course_index(COURSE_CREDIT);
                break;
            case 4:
                display_all_courses_menu();
            case 5:
                sort_course_index(COURSE_CODE);
                return;
            default:
                printf("Invalid option. Press enter to continue.");
                getchar();
        }
    }
}

void exam_menu() {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - EXAM MENU");
        nl();
        print_datetime(get_time());
        nl();
        nl();
        printf("1. Display Exams\n");
        printf("2. Add Exams\n");
        printf("3. Sort Exams\n");
        printf("4. Return\n");
        nl();
        printf("Your Choice : ");
        scanf("%d", &control);
        flush_stdin_buffer();
        switch (control) {
            case 1:

                getchar();
                break;
            case 2:
                // sort_course_index(COURSE_NAME);
                break;
            case 3:
                // sort_course_index(COURSE_CREDIT);
                break;
            case 4:
                // display_all_courses_menu();
                return;
            default:
                printf("Invalid option. Press enter to continue.");
                getchar();
        }
    }
}

void display_all_exams_menu() {
    int control;
    while (1) {
        clear_screen();
        nl();
        printf("COURSE ORGANISER - EXAM");
        nl();
        print_datetime(get_time());
        nl();
        printf("\nLIST OF ALL EXAMS\n\n");
        if (!(exam_index->size)) {
            printf("No Exams to display.\n");
            printf("\nPress enter to continue...");
            getchar();
            return;
        } else {
            display_code_name_date_exam_operation();
            printf("\nSelect an exam or press '0' to continue : ");
            scanf("%d", &control);
            flush_stdin_buffer();
            if (control == 0) {
                break;
            } else if (control > 0 && control <= exam_index->size) {
                // display_exam_menu(control - 1);
            } else {
                continue;
            }
        }
    }
}

void info_menu() {}
