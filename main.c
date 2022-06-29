#include "LinkedList.h"
#include "BenchMark.h"
#include "Table.h"
#include "Menu.h"

unsigned int* size;

__attribute__((flatten)) struct BenchMarkTask* get_default_task() {
    struct LinkedList* seeds = ll_new();
    ll_append(seeds, SEED(ordered));
    ll_append(seeds, SEED(randomized));
    ll_append(seeds, SEED(backordered));

    struct BenchMarkTask* task = malloc(sizeof(struct BenchMarkTask));
    task->seeders    = seeds;
    task->describe   = false;
    task->multiplier = 1;
    task->iterations = 12;

    return task;
}

__attribute__((flatten)) struct BenchMarkTask* get_full_task() {
    struct LinkedList* algos = ll_new();
    ll_append(algos, ALGO(Select6));
    ll_append(algos, ALGO(Select8));
    ll_append(algos, ALGO(Select3Exchange));

    struct BenchMarkTask* task = get_default_task();
    task->algos      = algos;
    task->iterations = 28;

    return task;
}

MENU_HANDLER(testSelect6) {
    struct LinkedList* algos = ll_new();
    ll_append(algos, ALGO(Select6));

    SETSIZE(size, 1, 0, 0);
    printf("P = const = 1\nM = ");
    fflush(stdout);
    scanf("%d", &size[1]);
    printf("N = ");
    fflush(stdout);
    scanf("%d", &size[2]);

    struct BenchMarkTask* task = get_default_task();
    task->algos    = algos;
    task->describe = true;
    task->size     = size;

    struct Table* results = measure(task);
    tbl_print(results);
    tbl_destroy(results);
    ll_destroy(algos);
    ll_destroy(task->seeders);
    free(task);

    printf("\a\n");
    system("pause");

    return true;
}

MENU_HANDLER(testSelect8) {
    struct LinkedList* algos = ll_new();
    ll_append(algos, ALGO(Select8));

    SETSIZE(size, 1, 0, 0);
    printf("P = const = 1\nM = ");
    fflush(stdout);
    scanf("%d", &size[1]);
    printf("N = ");
    fflush(stdout);
    scanf("%d", &size[2]);

    struct BenchMarkTask* task = get_default_task();
    task->algos    = algos;
    task->describe = true;
    task->size     = size;

    struct Table* results = measure(task);
    tbl_print(results);
    tbl_destroy(results);
    ll_destroy(algos);
    ll_destroy(task->seeders);
    free(task);

    printf("\a\n");
    system("pause");

    return true;
}

MENU_HANDLER(testSelect3Exchange) {
    struct LinkedList* algos = ll_new();
    ll_append(algos, ALGO(Select3Exchange));

    SETSIZE(size, 1, 0, 0);
    printf("P = const = 1\nM = ");
    fflush(stdout);
    scanf("%d", &size[1]);
    printf("N = ");
    fflush(stdout);
    scanf("%d", &size[2]);

    struct BenchMarkTask* task = get_default_task();
    task->algos    = algos;
    task->describe = true;
    task->size     = size;

    struct Table* results = measure(task);
    tbl_print(results);
    tbl_destroy(results);
    ll_destroy(algos);
    ll_destroy(task->seeders);
    free(task);

    printf("\a\n");
    system("pause");

    return true;
}

MENU_HANDLER(testAlgos) {
    struct MenuEntry** entries = calloc(4, sizeof(struct MenuEntry*));
    entries[0] = menu_entry_new("Test Select №6", &testSelect6);
    entries[1] = menu_entry_new("Test Select №8", &testSelect8);
    entries[2] = menu_entry_new("Test Select+Exchange №3", &testSelect3Exchange);
    entries[3] = menu_entry_new("OK", &menu_handler_exit);

    struct TextMenu* menu = menu_new(entries, 4);
    menu_start(menu);

    return true;
}

__attribute__((flatten)) void measureDefault() {
    struct BenchMarkTask* task = get_full_task();
    task->size = size;

    struct Table* results = measure(task);
    tbl_print(results);
    tbl_destroy(results);
    ll_destroy(task->algos);
    ll_destroy(task->seeders);
    free(task);

    printf("\n\n\n");
}

void measureCase1() {
    unsigned int N = 15500;

    struct BenchMarkTask* task = get_full_task();
    task->multiplier = 3;
    for(unsigned int i = 2500; i <= 12500; i += 2500) {
        printf("## For vector arr[%d]:\n", i);
        SETSIZE(size, 1, 1, i);
        
        task->size = size;
        
        struct Table* results = measure(task);
        tbl_print(results);
        tbl_destroy(results);
        printf("\n\n\n");
    }
    
    ll_destroy(task->algos);
    ll_destroy(task->seeders);
    free(task);

    unsigned int P = 3;
    for(int M = 1; M <= 1024; M *= 2) {
        printf("## For arr[%d][%d][%d]:\n", P, M, N);
        SETSIZE(size, P, M, N);

        measureDefault();
    }
}

void measureCase2() {
    unsigned int P = 3;
    for(int M = 10; M <= 10000; M *= 10) {
        int N = 10000 / (M / 10);
        printf("## For arr[%d][%d][%d]:\n", P, M, N);
        SETSIZE(size, P, M, N);

        measureDefault();
    }
}

void measureCase3() {
    unsigned int M = 100;
    for(int P = 20; P <= 2000; P *= 10) {
        unsigned int N = 2000 / ((P / 2) / 10);
        printf("## For arr[%d][%d][%d]:\n", P, M, N);
        SETSIZE(size, P, M, N);

        measureDefault();
    }
}

MENU_HANDLER(measureEverything) {
    printf("# Study case №1: Impact of column length on execution time of different sorting algorithms:\n\n");
    measureCase1();

    printf("# Study case №2: Impact of incision shape on execution time of different sorting algorithms:\n\n");
    measureCase2();

    printf("# Study case №3: Impact of keys quantity on execution time of different sorting algorithms:\n\n");
    measureCase3();

    printf("\a\a\a");
    system("pause");

    return true;
}

MENU_HANDLER(help) {
    printf("# SDA Coursework\n\n");
    printf("This program demonstrates the behaviour of 3 sorting algorithms:\n");
    printf("• Selection sort No. 6\n");
    printf("• Selection sort No. 8\n");
    printf("• Selection/Exchange sort No. 3\n\n");

    printf("To test if the implementation of algorithm is correct, pick 'Test...' in main menu and select the algo you'd like to test. ");
    printf("You will be prompted to enter values of M and N (arr[1][M][N]).\n");
    printf("To measure all algorithms at once, pick 'Measure everything' option in menu and wait for 3 bells.\n\n");

    printf("Coursework done by: KV-14 Oleksandr Briukhanov\n\n");
    system("pause");

    return true;
}

int main() {
    srand(time(NULL));

    struct MenuEntry** entries = calloc(4, sizeof(struct MenuEntry*));
    entries[0] = menu_entry_new("Measure everything", &measureEverything);
    entries[1] = menu_entry_new("Test...", &testAlgos);
    entries[2] = menu_entry_new("Help", &help);
    entries[3] = menu_entry_new("Quit", &menu_handler_exit);

    struct TextMenu* menu = menu_new(entries, 4);
    menu_start(menu);

    return 0;
}
