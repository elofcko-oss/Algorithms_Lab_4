#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Добавление элемента в дерево
struct Node *CreateTree(struct Node *root, int data) {
    if (root == NULL) {
        struct Node *newNode = malloc(sizeof(struct Node));

        if (newNode == NULL) {
            printf("Ошибка выделения памяти.\n");
            exit(EXIT_FAILURE);
        }

        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if (data < root->data) {
        root->left = CreateTree(root->left, data);
    }
    else if (data > root->data) {
        root->right = CreateTree(root->right, data);
    }
    else {
        printf("Число уже есть в дереве!\n");
    }

    return root;
}

// Поиск элемента
struct Node *Search(struct Node *root, int value) {
    if (root == NULL || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return Search(root->left, value);
    }

    return Search(root->right, value);
}

// Подсчёт количества вхождений
int CountOccurrences(struct Node *root, int value) {
    if (root == NULL) {
        return 0;
    }

    if (root->data == value) {
        return 1;
    }

    if (value < root->data) {
        return CountOccurrences(root->left, value);
    }

    return CountOccurrences(root->right, value);
}

// Вывод дерева
void print_tree(struct Node *root, int level) {
    if (root == NULL) {
        return;
    }

    print_tree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("    ");
    }

    printf("%d\n", root->data);

    print_tree(root->left, level + 1);
}

// Освобождение памяти
void FreeTree(struct Node *root) {
    if (root == NULL) {
        return;
    }

    FreeTree(root->left);
    FreeTree(root->right);
    free(root);
}

int main() {
    struct Node *root = NULL;
    int D, value;

    printf("Построение бинарного дерева поиска.\n");
    printf("-1 - окончание построения дерева\n");

    while (1) {
        printf("Введите число: ");

        if (scanf("%d", &D) != 1) {
            printf("Ошибка ввода!\n");
            FreeTree(root);
            return 1;
        }

        if (D == -1) {
            break;
        }

        root = CreateTree(root, D);
    }

    printf("\nПостроение дерева окончено.\n");

    printf("\nБинарное дерево:\n");
    print_tree(root, 0);

    printf("\nВведите число для поиска: ");
    scanf("%d", &value);

    if (Search(root, value) != NULL) {
        printf("Элемент найден!\n");
    }
    else {
        printf("Элемент не найден!\n");
    }

    printf("Количество вхождений элемента %d: %d\n",
           value, CountOccurrences(root, value));

    FreeTree(root);

    return 0;
}
