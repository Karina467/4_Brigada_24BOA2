#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int getnumber() { // ввод размера
    int num;
    printf("Введите размер массива: ");
    scanf("%d", &num);
    return num;
}

void rand_file(const char* fname, int num_count) { // заполление случайными числами
    FILE* file = fopen(fname, "wb");
    if (!file) {
        printf("Не удалось создать файл\n");
        return;
    }
    
    srand(time(NULL)); 
    for (int i = 0; i < num_count; i++) {
        int r_value = rand() % 201 - 100; // от -100 до 100
        fwrite(&r_value, sizeof(int), 1, file);
    }
    fclose(file);
}

void manual_file(const char* fname, int num_count) { // Функция ручного ввода чисел
    FILE* file = fopen(fname, "wb");
    if (!file) {
        printf("Не удалось создать файл\n");
        return;
    }
    
    printf("Введите %d чисел в диапазоне от -100 до 100:\n", num_count);
    for (int i = 0; i < num_count; i++) {
        int num;
        do {
            printf("Число %d: ", i+1);
            scanf("%d", &num);
            if (num < -100 || num > 100) {
                printf("Число должно быть от -100 до 100\n");
            }
        } while (num < -100 || num > 100);
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);
}

void sort(int arr[], int n) { // сортировка вставками
    for (int i = 1; i < n; i++) {
        int f = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > f) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = f;
    }
}

void save_f(int arr[], int n) {
    FILE* file = fopen("sort_array.txt", "w");
    if (!file) {
        printf("Не удалось создать файл\n");
        return;
    }    
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

void print_time_stats(int num_count, double time_taken) {
    printf("Количество элементов: %d\n", num_count);
    printf("Время сортировки: %.6f секунд\n", time_taken);
}

int main() {
    const char* name = "array.bin";
    int choice;
    
 
    
    int num_count = getnumber();
      
    
    int* arr = malloc(num_count * sizeof(int));// Чтение из файла 
    FILE* file = fopen(name, "rb");
    if (!file) {
        printf("Не удалось открыть файл\n");
        free(arr);
        return 1;
    }
    fread(arr, sizeof(int), num_count, file);
    fclose(file);
  
    
    clock_t start = clock();
    sort(arr, num_count);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    

    
    save_f(arr, num_count);
    print_time_stats(num_count, time_taken);
    
    free(arr);
    return 0;
}