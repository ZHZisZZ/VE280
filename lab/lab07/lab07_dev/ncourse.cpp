//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#include <iostream>
#include <algorithm>
#include "course.h"

typedef struct task{
    std::string type;
    int index; 
    int due_month;
    int due_day;
} Task;

const int MAXTASKS = 4; 

bool less(const Task& task1, const Task& task2) 
{
    return (task1.due_month < task2.due_month || (task1.due_month == task2.due_month && task1.due_day < task2.due_day));
}

bool lessE(const Task& task1, const Task& task2) 
{
    return (task1.due_month < task2.due_month || (task1.due_month == task2.due_month && task1.due_day <= task2.due_day));
}


class TechnicalCourse : public Course 
{
protected:
    Task *tasks;
    int numTasks;
    int sizeTasks;
    std::string course_code;

    enum State {NOTHING, UPDATED, ADD};
    struct returnType {
        int index; // the index in the array referring to the changed task;
        State state;
    };

    // REQUIRES: due_month and due_day are in normal range.
    // MODIFIES: this
    // EFFECTS: if Task index of type already exists in tasks, 
    //          return -1 if due_month and due_day does not change,
    //          return 0 if due_month and due_day are updated;
    //          else if tasks is not full, add Task i at the end and return 1,
    //          else throw exception;
    returnType updateBase(const std::string &type, int index, int due_month, int due_day);

public:
    // TODO: implement the constructor
    TechnicalCourse(const std::string &code, int size = MAXTASKS)
        : numTasks(0), sizeTasks(size), course_code(code) 
    {
        tasks = new Task[sizeTasks];
    };

    // TODO: declare and implement the destructor
    virtual ~TechnicalCourse()
    {
        delete [] tasks;
    }

    // EFFECTS: update task;
    virtual void updateTask(const std::string &type, int index, int due_month, int due_day);

    // EFFECTS: finish task;
    virtual void finishTask(const std::string &type, int index, int finish_month, int finish_day);

    // EFFECTS: print task;
    void print();

};

TechnicalCourse::returnType TechnicalCourse::updateBase(const std::string &type, int index, int due_month, int due_day)
{
    returnType re; re.state = NOTHING;
    int i = 0;
    for (; i != numTasks && (tasks[i].type != type || tasks[i].index != index); i++) continue;
    re.index = i;
    if (i == numTasks) { // not found
        if (numTasks == sizeTasks) throw tooManyTasks();
        tasks[i].type = type;
        tasks[i].index = index;
        numTasks++;
        re.state = ADD;
    }
    if (re.state != ADD && (tasks[i].due_month != due_month || tasks[i].due_day != due_day)) {
        re.state = UPDATED;
    }
    tasks[i].due_month = due_month;
    tasks[i].due_day = due_day;
    return re;
}

void TechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
{
    if (updateBase(type, index, due_month, due_day).state == ADD) {
        std::cout << course_code << " " << type << " " << index << " is released! "
                  << "Submit it via " << (type == "Lab" || type == "Project" ? "oj":"canvas") << "!\n";  
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finish_month, int finish_day)
{
    int i = 0;
    for (; i != numTasks && (tasks[i].type != type || tasks[i].index != index); i++) continue;
    if (i != numTasks) {
        std::cout << course_code << " " << type << " " << index << " is "  
                  << (finish_month > tasks[i].due_month || (finish_month == tasks[i].due_month && finish_day > tasks[i].due_day) ? "overdue" : "finished") <<"!\n";
        numTasks--;
        for (; i < numTasks; i++) {
            tasks[i] = tasks[i+1];
        }
    }
}

void TechnicalCourse::print()
{
    std::cout << course_code << std::endl;
    for(int i = 0; i < numTasks; ++i){
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].due_month << "/" << tasks[i].due_day << std::endl;
    }
}

class UpperlevelTechnicalCourse : public TechnicalCourse {
public:
    // TODO: implement the constructor
    UpperlevelTechnicalCourse(const std::string &course_code, int size = MAXTASKS)
        : TechnicalCourse(course_code, size) {};

    // TODO: declare and implement the destructor
    // no need to do so;
    // ~UpperlevelTechnicalCourse()
    // {
    //     delete [] tasks;
    // }

    // EFFECTS: update task;
    void updateTask(const std::string &type, int index, int due_month, int due_day);
};

void UpperlevelTechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & due_month & due_day if its due_month/due_day is changed,
//          do nothing if its due_month/due_day is unchanged.
{
    // TODO: implement this function
    returnType re;
    if ( (re = updateBase(type, index, due_month, due_day)).state == ADD) {
        std::cout << course_code << " " << type << " " << index << " is released! "
                  << "Submit it via " << (type == "Lab" || type == "Project" || type == "Team Project" ? type == "Team Project" ? "github":"oj":"canvas") << "!\n";  
    }

    if (re.state != NOTHING) {
        // 往前移动
        if (re.state == ADD || (re.state == UPDATED && ( re.index == numTasks-1 || less(tasks[re.index], tasks[re.index+1]) ) ) ) {
            auto tempTask = tasks[re.index];
            int i = re.index;
            for ( ;i && !lessE(tasks[i - 1], tempTask); i--) {
                tasks[i] = tasks[i - 1];
            }
            tasks[i] = tempTask;
        } 
        else {
            auto tempTask = tasks[re.index];
            int i = re.index;
            for (; i != numTasks - 1 && !less(tempTask, tasks[i + 1]); i++) {
                tasks[i] = tasks[i + 1];
            }
            tasks[i] = tempTask;
        }
    }
}

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size)
{
    if(class_type == "Technical"){
        if(assign_size){
            return new TechnicalCourse(course_code, tasks_size);
        }
        else{
            return new TechnicalCourse(course_code);
        }
    }
    else if(class_type == "Upper Level Technical"){
        if(assign_size){
            return new UpperlevelTechnicalCourse(course_code, tasks_size);
        }
        else{
            return new UpperlevelTechnicalCourse(course_code);
        }
    }
    else{
        return nullptr;
    }
}
