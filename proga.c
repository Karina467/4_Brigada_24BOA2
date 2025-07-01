#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int* arr = NULL;
int num_count = 0;  
const char* sluch_filename = "sluch_array.txt";//Файл для случайных чисел
const char* output_filename = "sorted_array.txt";//Файл для отсортированного массива

void sort(int arr[], int n) { //Сортировка вставками
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void save_to_file(const char* filename, int arr[], int n) { //Сохранение массива в файл
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int load_from_file(const char* filename, int** arr) {//Загрузка массива из файла
    
    FILE* file = fopen(filename, "r");
    int count = 0;
    int temp;
    while (fscanf(file, "%d", &temp) == 1) {
        count++;
    }
    fclose(file);

    *arr = malloc(count * sizeof(int));
    rewind(file);
    for (int i = 0; i < count; i++) {
        free(*arr);
        fclose(file);
        return 0;
    }
    
    fclose(file);
    return count;
}

void create_sluch_array() { //Заполнение случайными значениями
    printf("Введите количество элементов: ");
    scanf("%d", &num_count);
    if (arr != NULL) {
        free(arr);
    }
    arr = malloc(num_count * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < num_count; i++) {
        arr[i] = rand() % 201 - 100; // числа от -100 до 100
    }
    printf("Случайный массив создан и сохранен в файл %s\n", sluch_filename);

    save_to_file(sluch_filename, arr, num_count);    //случайный массив в файл
}

void show_menu() {
    printf("МЕНЮ ПРОГРАММЫ\n");
    printf("1. Загрузить массив из файла\n");
    printf("2. Создать случайный массив\n");
    printf("3. Отсортировать текущий массив\n");
    printf("4. Выйти из программы\n");
    printf("Выберите действие: ");
}

int main() {
    int choice;
    char filename[20];
    
    do {
        show_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Введите имя файла: ");
                scanf("%20s", filename);
                
                if (arr != NULL) {
                    free(arr);
                    arr = NULL;
                }
                
                num_count = load_from_file(filename, &arr);
                if (num_count > 0) {
                    printf("Массив загружен (%d элементов)\n", num_count);
                }
                break;
                
            case 2:
                create_sluch_array();
                break;
                
            case 3:        
                sort(arr, num_count);
                save_to_file(output_filename, arr, num_count);
                printf("Массив отсортирован и сохранен в файл %s\n", output_filename);
                break;
                
            case 4:
                printf("Завершение программы...\n");
                break;
                
            default:
                printf("Выберете меню.\n");
        }
        
        while (getchar() != '\n'); // Очистка ввода
        
    } while (choice != 4);
    
    if (arr != NULL) {
        free(arr);
    }
    
    return 0;
}
