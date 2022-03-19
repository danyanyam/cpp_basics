#include <iostream>
#include <map>
#include <string>
#include <tuple>
using namespace std;
//
// person: {new: 2, in_progress: 3, }
//
//
//
// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
   private:
    map<string, TasksInfo> data;

   public:
    TeamTasks(){};
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& get_person_tasks_info(const string person) {
        return data[person];
    };

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void add_task(const string& person) {
        TasksInfo task;  // {NEW: 1, INP: 2, DONE: 3, TESTING: 4}
        int counter;

        if (data.count(person) > 0) {
            task = data[person];
            if (task.count(TaskStatus::NEW) > 0) {
                data[person][TaskStatus::NEW] += 1;
            } else {
                task[TaskStatus::NEW] = 1;
            };
        } else {
            task.insert(make_pair(TaskStatus::NEW, 1));
            data.insert(make_pair(person, task));
        };
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> perform_person_task(const string& person,
                                                    int task_count)
    {
        /**

          Метод PerformPersonTasks должен реализовывать следующий алгоритм:
          Рассмотрим все невыполненные задачи разработчика person.
          Упорядочим их по статусам: сначала все задачи в статусе NEW, затем
          все задачи в статусе IN_PROGRESS и, наконец, задачи в статусе
          TESTING. Рассмотрим первые task_count задач и переведём каждую из
          них в следующий статус в соответствии с естественным порядком: NEW
          → IN_PROGRESS → TESTING → DONE. Вернём кортеж из двух элементов:
          информацию о статусах обновившихся задач (включая те, которые
          оказались в статусе DONE) и информацию о статусах остальных не
          выполненных задач.

            В случае отсутствия разработчика с именем person метод
          PerformPersonTasks должен вернуть кортеж из двух пустых TasksInfo
            Гарантируется, что task_count является положительным числом. Если
          task_count превышает текущее количество невыполненных задач
          разработчика, достаточно считать, что task_count равен количеству
          невыполненных задач: дважды обновлять статус какой - либо задачи в
          этом случае не нужно.

            Кроме того, гарантируется, что метод GetPersonTasksInfo не будет
          вызван для разработчика, не имеющего задач.
         */
    };
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void print_tasks_info(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"
         << ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"
         << ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested"
         << ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main(int argc, char const* argv[]) {
    TeamTasks tasks;
    tasks.add_task("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.add_task("Ivan");
    };

    cout << "Ilia's tasks: ";
    print_tasks_info(tasks.get_person_tasks_info("Ilia"));
    cout << "Ivan's tasks: ";
    print_tasks_info(tasks.get_person_tasks_info("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    // cout << "Updated Ivan's tasks: ";
    // print_tasks_info(updated_tasks);
    // cout << "Untouched Ivan's tasks: ";
    // print_tasks_info(untouched_tasks);

    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan",
    // 2); cout << "Updated Ivan's tasks: "; print_tasks_info(updated_tasks);
    // cout << "Untouched Ivan's tasks: ";
    // print_tasks_info(untouched_tasks);

    return 0;
}
