#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* arr = NULL;  // глобальный массив
int num_count = 0; // количество элементов
const char* sluch_filename = "sluch_array.txt";
const char* output_filename = "sorted_array.txt";

// функция сортировки (вставками) с подсчетом перестановок
int sort(int arr[], int n) {
    int i, j, key;
    int swaps = 0; // счетчик перестановок
    
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            swaps++; // увеличиваем счетчик при каждой перестановке
        }
        arr[j + 1] = key;
    }
    return swaps;
}

// сохранение в файл
void save_to_file(const char* filename, int arr[], int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    
    fclose(file);
}
// загрузка из файла
int load_from_file(const char* filename, int** arr) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл не найден!\n");
        return 0;
    }

    // сначала считаем количество чисел
    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }
    
    // выделяем память
    *arr = (int*)malloc(count * sizeof(int));
    if (*arr == NULL) {
        printf("Память не выделилась!\n");
        fclose(file);
        return 0;
    }
    
    // читаем данные
    rewind(file);
    for (int i = 0; i < count; i++) {
        if (fscanf(file, "%d", &(*arr)[i]) != 1) {
            printf("Ошибка чтения!\n");
            free(*arr);
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return count;
}

// создание случайного массива
void create_sluch_array() {
    printf("Введите количество элементов: ");
    scanf("%d", &num_count);
    if (arr != NULL) {
        free(arr);
        arr = NULL;
    }
    arr = (int*)malloc(num_count * sizeof(int));
    if (arr == NULL) {
        printf("Память не выделилась\n");
        return;
    }
    srand(time(0)); // генератор случайных чисел
    for (int i = 0; i < num_count; i++) {
        arr[i] = rand() % 201 - 100; // числа от -100 до 100
    }
    save_to_file(sluch_filename, arr, num_count);
    printf("Случайный массив сохранен в файл %s\n", sluch_filename);
}

// показ меню
void show_menu() {
    printf(" МЕНЮ \n");
    printf("1. Загрузить массив из файла\n");
    printf("2. Создать случайный массив\n");
    printf("3. Отсортировать текущий массив\n");
    printf("4. Выйти\n");
    printf("Выберите: ");
}

int main() {
    int choice;
    char filename[50];
    
    do {
        show_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Введите имя файла: ");
                scanf("%s", filename);
                
                num_count = load_from_file(filename, &arr);
                break;
                
            case 2:
                create_sluch_array();
                break;
                
            case 3:
                if (arr == NULL || num_count == 0) {
                    printf("Массив пуст!\n");
                } else {
                    clock_t start = clock(); // начальное время
                    int swaps = sort(arr, num_count); // сортировка с подсчетом перестановок
                    clock_t end = clock(); // конечное время
                    
                    double time_spent = (double)(end - start) / CLOCKS_PER_SEC; // время выполнения
                    
                    save_to_file(output_filename, arr, num_count);
                    printf("Массив отсортирован и сохранен в %s\n", output_filename);
                    printf("Количество перестановок: %d\n", swaps);
                    printf("Время выполнения сортировки: %.6f секунд\n", time_spent);
                }
                break;
                
            case 4:
                printf("Выход...\n");
                break;
                
            default:
                printf("Неверный выбор!\n");
        } 
        // очистка ввода
        while (getchar() != '\n');
    } while (choice != 4);
    
    // освобождение памяти 
    if (arr != NULL) {
        free(arr);
    }
    
    return 0;
}
