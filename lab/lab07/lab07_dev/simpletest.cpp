//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-25.
//

#include <iostream>

#include "course.h"

int main() {

    Course *ve281 = create("Technical", "VE281", false, 0);
    Course *ve370 = create("Technical", "VE370", false, 0);
    Course *ve482 = create("Upper Level Technical", "VE482", true, 6);

    try{
        ve482->updateTask("Homework", 1, 9, 18);
        ve482->updateTask("Lab", 1, 9, 16);
        ve482->updateTask("Team Project", 1, 10, 6);
        ve482->print();
        ve482->updateTask("Homework", 1, 7, 16);
        ve482->print();
        ve482->updateTask("Lab", 1, 9, 13);
        ve482->updateTask("Homework", 1, 7, 16); // do nothing
        ve482->print();
        ve482->finishTask("Homework", 1, 9, 20);
        ve482->print();
        ve482->updateTask("Team Project", 2, 10, 5);
        ve482->updateTask("Team Project", 3, 10, 6);
        ve482->updateTask("Team Project", 4, 10, 6);
        ve482->updateTask("Team Project", 5, 10, 7);
        ve482->print();       
        ve482->updateTask("Team Project", 5, 10, 6);
        ve482->updateTask("Team Project", 2, 10, 6);
        ve482->updateTask("Team Project", 4, 10, 6);
        ve482->print();       
        ve482->finishTask("Team Project", 2, 10, 6);
        ve482->finishTask("Team Project", 4, 10, 6);
        ve482->print();       
        ve482->updateTask("Team Project", 3, 11, 6);
        ve482->print();     
        ve482->finishTask("Team Project", 3, 1, 1);  
        ve482->print();     
        ve482->finishTask("Team Project", 1, 1, 1);  
        ve482->finishTask("Team Project", 5, 11, 29);  
        ve482->finishTask("Lab", 1, 11, 29);  
        ve482->print();     
        ve482->updateTask("Lab", 0, 8, 19);
        ve482->updateTask("Lab", 3, 9, 20);
        ve482->print();     
        ve482->updateTask("Lab", 0, 9, 20);
        ve482->print();     
    }
    catch(tooManyTasks){
        std::cout << "Too many tasks\n";
    }

    delete ve281;
    delete ve370;
    delete ve482;

    return 0;
}

