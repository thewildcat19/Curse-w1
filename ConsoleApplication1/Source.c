#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#pragma warning(disable:4996)

typedef struct {
    int number;
    char name[50];
    int stages[5];
    int penalty;
    int total;
    float place;
} cyclist;

int check_size(char[30]);
int file_write(cyclist*, int, char[30]);
int file_read(cyclist*, char[30], int);
void arr_print_data(cyclist*, int);
void arr_print_results(cyclist*, int);
cyclist* arr_sorted(cyclist*, int);
cyclist* arr_calc_res(cyclist*, int);
int arr_change(cyclist*, int,int,int,int);
cyclist* arr_search(cyclist*, int, int, int);


 int main() {
 
    setlocale(LC_ALL, "Russian");
    int size;
    char  extension[6] = { ".txt" };
    char file_name[30];
    puts("Введите название файла в пределах 30 символов (без указания расширения файла)");
    scanf("%s", file_name);

    strcat(file_name, extension);
    printf("Имя файла: %s\n", file_name);
    size=check_size(file_name);
    cyclist* array= (cyclist*)malloc(size * sizeof(cyclist));
    file_read(array, file_name,size);
    char inp;
    int  choice=1;
    
    while (choice != 7) {
        printf("Программа оценки соревнований по велоспорту\n"
            "Для вывода исходной таблицы нажмите - 1\n"
            "Для вывода отсортированного по среднему значению списка нажмите - 2\n"
            "Для вывода результирующей таблицы, содержащей очки и места нажмите - 3\n"
            "Для поиска спортсмена по штрафным очкам в диапазоне нажмите - 4\n"
            "Для изменения значений этапа игрока нажмите - 5\n"
            "Для записи значений в файл нажмите - 6\n"
            "Для выхода из программы нажмите - 7\n"
        );
        scanf_s("\n%c", &inp);
        //choice = (int)inp - 48;
        choice = atoi(&inp);
       // scanf_s("%d", &choice);
        if (choice > 0 && choice <= 7) {
            switch (choice) {
            case 1:
                system("cls");
                arr_print_data(array, size, 0);
                break;
            case 2:
                system("cls");
                arr_print_data(arr_sorted(array, size), size, 1);
                break;
            case 3:
                system("cls");
                arr_calc_res(array, size);
                arr_print_results(array, size, 0);
                break;
            case 4:
                system("cls");
                printf("Введите значения нижнего и верхнего пределов диапазона:");
                int ub = 0, lb = 0;
                int sz = 0;
                scanf("%d", &lb);
                scanf("%d", &ub);
                arr_print_results(arr_search(array, size, lb, ub, &sz), sz, 1);
                printf("Показано %d записей\n", sz);
                break;
            case 5:
                system("cls");
                printf("Напишите номер игрока , этапа(для штрафных очков введите - 6) и новое значение:");
                int pl_numb, pl_st, pl_val, result;
                scanf("%d %d %d", &pl_numb, &pl_st, &pl_val);
                arr_change(array, size, pl_numb, pl_st, pl_val, result) == 1 ? printf("Изменение выполнено успешно!\n") : printf("Значение не найдено!\n");
                break;
            case 6:
                if (file_write(array, size, file_name) == 0)printf("Сохранено успешно!\n");
                break;


            }
        }
        else {
            system("cls"); printf("Ошибка! Повторите ввод!\n");
    }
      
        
    };
    
    exit(0);
}

 int check_size(char fname[30]) {
     FILE* S2 = fopen(fname, "rt");
     if (S2 == NULL) {
         puts("Не удалось открыть файл");
         exit(0);
     }
     int size;
     int k = 0;
     while (!feof(S2)) {
         if (fgetc(S2) == '\n'){k++; }

     }
     size = k;
     return size;
     fclose(S2);
 }

 int file_read(cyclist* array, char fname[30], int size) {
     system("cls");
     FILE* S2 = fopen(fname, "rt");
     if (S2 == NULL) {
         puts("Не удалось открыть файл");
         exit(0);
     }
     int i = 0;
     int k = 0;
     fseek(S2, 0, SEEK_SET);
     while (!feof(S2))
     {

         fscanf(S2, "|%5d|", &array[i].number);
         char c[21];
         fgets(c, 21, S2);
         strcpy(&array[i].name, c);
         fscanf(S2, "|%5d|%5d|%5d|%5d|%5d|%13d|\n", &array[i].stages[0], &array[i].stages[1], &array[i].stages[2], &array[i].stages[3], &array[i].stages[4], &array[i].penalty);
         i++;

     }
     fclose(S2);
     printf("Успешно импортировано %d записей!\n", i);
     return i;
 }

 int file_write(cyclist* array, int size, char fname[30]) {
     //запись в файл
     system("cls");
     FILE* S1 = fopen(fname, "w");
     for (int i = 0; i < size; i++) {
         fprintf(S1, "|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%13d|\n", array[i].number, array[i].name, array[i].stages[0], array[i].stages[1], array[i].stages[2], array[i].stages[3], array[i].stages[4], array[i].penalty);
     };
     if (fclose(S1)) {
         return 0;
     }
 }

void arr_print_data(cyclist* a, int size,int mode) {
    if (mode == 0) {
        printf("\nТаблица данных\n");
        printf("|%2s|%20s|%5s|%5s|%5s|%5s|%5s|%5s|\n", "Номер", "Имя Фамилия", "Этап1", "Этап2", "Этап3", "Этап4", "Этап5", "Штрафные очки");
        for (int i = 0; i < size; i++) {
            printf("|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%13d|\n", a[i].number, a[i].name, a[i].stages[0], a[i].stages[1], a[i].stages[2], a[i].stages[3], a[i].stages[4], a[i].penalty);
        };
    }

    else if (mode == 1) {
        printf("\nТаблица данных\n");
        printf("|%2s|%20s|%5s|%5s|%5s|%5s|%5s|%7s|%5s|\n", "Номер", "Имя Фамилия", "Этап1", "Этап2", "Этап3", "Этап4", "Этап5", "Среднее", "Штрафные очки");
        for (int i = 0; i < size; i++) {
            printf("|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%7.1f|%13d|\n", a[i].number, a[i].name, a[i].stages[0], a[i].stages[1], a[i].stages[2], a[i].stages[3], a[i].stages[4], ((a[i].stages[0] + a[i].stages[1] + a[i].stages[2] + a[i].stages[3] + a[i].stages[4]) / 5.), a[i].penalty);
        };
    }
}

void arr_print_results(cyclist* a, int size,int mode) {
    if (mode == 0) {
        printf("\nТаблица результатов\n");
        printf("|%20s|%5s|%5s|\n", "Имя Фамилия", "Общие очки", "Место");
        for (int i = 0; i < size; i++) {
            printf("|%20s|%10d|%5.1f|\n", a[i].name, a[i].total, a[i].place);
        };
    }
    else if (mode == 1) {
        printf("\nТаблица данных\n");
        printf("|%2s|%20s|%5s|\n", "Номер", "Имя Фамилия", "Штрафные очки"); for (int i = 0; i < size; i++)
        {
            printf("|%5d|%20s|%13d|\n", a[i].number, a[i].name, a[i].penalty);
        }
    }
}

cyclist* arr_sorted(cyclist* a, int size) {
    cyclist t;
    cyclist* b = (cyclist*)malloc(size * sizeof(cyclist));
    for (int i = 0; i < size; i++) b[i] = a[i];
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (((b[i].stages[0] + b[i].stages[1] + b[i].stages[2] + b[i].stages[3] + b[i].stages[4]) / 5.) < ((b[j].stages[0] + b[j].stages[1] + b[j].stages[2] + b[j].stages[3] + b[j].stages[4]) / 5.)) {

                t = b[i];
                b[i] = b[j];
                b[j] = t;
            }
        }
    }
    return b;
    free(b);
}




cyclist* arr_calc_res(cyclist* a, int size) {
    for (int i = 0; i < size; i++)a[i].total = (a[i].stages[0]+ a[i].stages[1]+ a[i].stages[2]+ a[i].stages[3]+ a[i].stages[4]) - a[i].penalty;
    for (int i = 0; i < size; i++) {
        int r = 1;
        for (int j = 0; j < size; j++) {
            if (i != j && a[i].total < a[j].total)
                r += 1;
        }
        a[i].place = r;
    }
    return a;
}

cyclist* arr_search(cyclist* a, int size, int lowerbound, int upperbound,int* sz) {
    int k = 0;
    cyclist* b = (cyclist*)malloc(size * sizeof(cyclist));
    for (int i = 0; i < size; i++)
    {
        if (a[i].penalty >= lowerbound && a[i].penalty <= upperbound) {
            
            b[k].number = a[i].number;
            strcpy(b[k].name, a[i].name);
            b[k].penalty = a[i].penalty;
            k++;
            //printf("|%5d|%20s|%13d|\n", a[i].number, a[i].name, a[i].penalty);
        }
    }
    *sz = k;
    b = (cyclist*)realloc(b, *sz*sizeof(cyclist));
    return b;

}

int arr_change(cyclist* a, int size, int pl_numb,int pl_st, int pl_val) {
    int result;
    for (int i = 0; i < size; i++) {
        if (a[i].number == pl_numb) {
            pl_st > 0 && pl_st < 6 ? a[i].stages[pl_st - 1] = pl_val : false;
            pl_st == 6 ? a[i].penalty = pl_val : false;
            result = 1;
            break;
        }
        else { result = 0; }
        }
    return result;
    }
