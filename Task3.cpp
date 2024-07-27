#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

struct Task {
    string title;
    int priority;
    string description;
    tm dueDateTime;

    Task(string t, int p, string d, tm dt)
        : title(t), priority(p), description(d), dueDateTime(dt) {}
};

// Функция для добавления нового дела
void addTask(vector<Task>& tasks) {
    string title, description;
    int priority;
    tm dueDateTime = {};

    cout << "Введите название дела на английском: ";
    cin.ignore(); // Добавлено для корректного считывания после предыдущего ввода
    getline(cin, title);
    cout << "Введите приоритет (целое число): ";
    cin >> priority;
    cout << "Введите описание дела: ";
    cin.ignore();
    getline(cin, description);
    cout << "Введите дату исполнения (ГГГГ ММ ДД ЧЧ ММ СС): ";
    cin >> dueDateTime.tm_year >> dueDateTime.tm_mon >> dueDateTime.tm_mday >> dueDateTime.tm_hour >> dueDateTime.tm_min >> dueDateTime.tm_sec;

    dueDateTime.tm_year -= 1900; // Корректировка года
    dueDateTime.tm_mon -= 1;      // Корректировка месяца

    tasks.emplace_back(title, priority, description, dueDateTime);
}

// Функция для удаления дела
void removeTask(vector<Task>& tasks) {
    string title;
    cout << "Введите название дела для удаления: ";
    cin.ignore(); // Нужно здесь, чтобы избежать проблем с getline
    getline(cin, title);

    auto it = remove_if(tasks.begin(), tasks.end(),
        [&title](const Task& task) { return task.title == title; }); // Исправлено использование lambda-функции

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        cout << "Дело '" << title << "' было удалено." << endl;
    }
    else {
        cout << "Дело с названием '" << title << "' не найдено." << endl;
    }
}

// Функция для редактирования дела
void editTask(vector<Task>& tasks) {
    string title;
    cout << "Введите название дела для редактирования: ";
    cin.ignore(); // Нужно здесь, чтобы избежать проблем с getline
    getline(cin, title);

    for (auto& task : tasks) {
        if (task.title == title) {
            cout << "Введите новое название: ";
            getline(cin, task.title);
            cout << "Введите новый приоритет: ";
            cin >> task.priority;
            cout << "Введите новое описание: ";
            cin.ignore(); // Нужно здесь для правильного считывания
            getline(cin, task.description);
            cout << "Введите новую дату исполнения (ГГГГ ММ ДД ЧЧ ММ СС): ";
            cin >> task.dueDateTime.tm_year >> task.dueDateTime.tm_mon >> task.dueDateTime.tm_mday >> task.dueDateTime.tm_hour >> task.dueDateTime.tm_min >> task.dueDateTime.tm_sec;
            task.dueDateTime.tm_year -= 1900;
            task.dueDateTime.tm_mon -= 1;
            cout << "Дело успешно изменено." << endl;
            return;
        }
    }
    cout << "Дело с названием '" << title << "' не найдено." << endl;
}

// Функция для поиска дел
void searchTask(const vector<Task>& tasks) {
    int choice;
    cout << "Выберите критерий поиска:\n";
    cout << "1. По названию\n";
    cout << "2. По приоритету\n";
    cout << "3. По описанию\n";
    cout << "4. По дате исполнения\n";
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        string title;
        cout << "Введите название для поиска: ";
        cin.ignore(); // Нужно здесь, чтобы избежать проблем с getline
        getline(cin, title);
        for (const auto& task : tasks) {
            if (task.title == title) {
                cout << "Найдено дело: " << task.title << endl;
                return;
            }
        }
        cout << "Дело с названием '" << title << "' не найдено." << endl;
        break;
    }
    case 2: {
        int priority;
        cout << "Введите приоритет для поиска: ";
        cin >> priority;
        for (const auto& task : tasks) {
            if (task.priority == priority) {
                cout << "Найдено дело: " << task.title << endl;
            }
        }
        break;
    }
    case 3: {
        string description;
        cout << "Введите часть описания для поиска: ";
        cin.ignore(); // Нужно здесь для правильного считывания
        getline(cin, description);
        for (const auto& task : tasks) {
            if (task.description.find(description) != string::npos) { // Поиск по подстроке
                cout << "Найдено дело: " << task.title << endl;
            }
        }
        break;
    }
    case 4: {
        tm dueDateTime = {};
        cout << "Введите дату исполнения для поиска (ГГГГ ММ ДД ЧЧ ММ СС): ";
        cin >> dueDateTime.tm_year >> dueDateTime.tm_mon >> dueDateTime.tm_mday >> dueDateTime.tm_hour >> dueDateTime.tm_min >> dueDateTime.tm_sec;
        dueDateTime.tm_year -= 1900;
        dueDateTime.tm_mon -= 1;

        for (const auto& task : tasks) {
            if (difftime(mktime(const_cast<tm*>(&task.dueDateTime)), mktime(&dueDateTime)) == 0) {
                cout << "Найдено дело: " << task.title << endl;
            }
        }
        break;
    }
    default:
        cout << "Неверный выбор." << endl;
        break;
    }
}

// Основная функция
int main() {
    setlocale(LC_ALL, "RU");
    vector<Task> tasks;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить дело\n";
        cout << "2. Удалить дело\n";
        cout << "3. Редактировать дело\n";
        cout << "4. Поиск дела\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTask(tasks);
            break;
        case 2:
            removeTask(tasks);
            break;
        case 3:
            editTask(tasks);
            break;
        case 4:
            searchTask(tasks);
            break;
        case 5:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}