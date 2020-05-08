#include "exam_index.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "exam.h"
#include "exam_list.h"
#include "util.h"

struct exam_list *exam_list;
struct exam_index *exam_index;
int sorted_by_exam_index;

void init_exam_index() {
    if (exam_list) {
        exam_index = malloc(sizeof(struct exam_index));
        exam_index->c = malloc(sizeof(struct exam *) * (exam_list->size));
        exam_index->size = exam_list->size;
    }
}

void load_exam_index() {
    int i = 0;
    printf("Indexing exams....\n");
    struct exam_list_node *trav = exam_list->head;
    while (trav && i < exam_index->size) {
        exam_index->c[i++] = trav->data;
        trav = trav->next;
    }
}

void sort_exam_index(enum exam_field_name sort_by) {
    if (exam_index) {
        int (*comparator)(const void *, const void *) =
            get_comparator_exam(sort_by);
        if (comparator) {
            qsort(exam_index->c, exam_index->size, sizeof(struct exam *),
                  comparator);
            sorted_by_exam_index = sort_by;
        }
    }
}

void free_exam_index() {
    free(exam_index->c);
    free(exam_index);
}

int search_exam_index(struct exam *key, enum exam_field_name sorted_by, int low,
                      int high) {
    if (sorted_by_exam_index != sorted_by) {
        sort_exam_index(sorted_by);
    }
    int (*comparator)(const void *, const void *) =
        get_comparator_exam(sorted_by);
    if (low > high || exam_index->size == 0) {
        return -1;
    } else {
        int mid = low + (high - low) / 2;
        // int mid = ((unsigned int)low + (unsigned int)high) >> 1;
        if (comparator(&(key), &(exam_index->c[mid])) == 0) {
            return mid;
        } else if (comparator(&(key), &(exam_index->c[mid])) < 0) {
            return search_exam_index(key, sorted_by, low, mid - 1);
        } else {
            return search_exam_index(key, sorted_by, mid + 1, high);
        }
    }
}

void make_exam_index(enum exam_field_name sort_by) {
    if (exam_index) {
        free(exam_index);
    }
    init_exam_index();
    load_exam_index();
    sort_exam_index(sort_by);
    printf("Indexed %d exams....\n", exam_index->size);
}

struct exam *get_by_id_exam_index(long id_key) {
    struct exam *search = init_exam(NULL);
    search->id = id_key;
    int index = search_exam_index(search, EXAM_ID, 0, exam_index->size);
    return index == -1 ? NULL : exam_index->c[index];
}