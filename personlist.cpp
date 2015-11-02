//Los Angeles Valley College
//CSIT 839
//Spring 2014
//Steve Mario Correa
//Assignment 4
//This program displays a menu which permits the user three choices: (1) add a student to the waiting list (by name and amount of the "contribution"; (2) view a list of the students, by name and amount of contribution, in the order stated above; or (3) exit the program.
#include "personlist.h"
#include <iostream>
PersonRec::PersonRec() {
	sName = "";
	nBribe = 0;
	personrecNext = NULL;
}
PersonRec::~PersonRec() {
	if(personrecNext != NULL)
		personrecNext = NULL;
}
PersonList::PersonList() {
	head = NULL;
}
PersonList::~PersonList() {
	if(head != NULL) {
		PersonRec** personrecToDelete = &head;
		bool bHaveDeletedHead = false;
		do {
			if((*personrecToDelete)->personrecNext == NULL) {
				delete (*personrecToDelete);
				(*personrecToDelete) = NULL;
				if(personrecToDelete == &head)
					bHaveDeletedHead = true;
				else
					personrecToDelete = &head; //Start over
			} else {
				personrecToDelete = &(*personrecToDelete)->personrecNext;
			}
		} while(bHaveDeletedHead == false);
	}
}
void PersonList::ViewList() {
	if(head == NULL) {
		std::cout << "\nList is empty\n";
	} else {
		PersonRec* personrecToShow = head;
		int nPlaceInLine = 1;
		std::cout << "\n# Name Contribution\n";
		std::cout << "=======================================\n\n";
		do {
			std::cout << nPlaceInLine << " ";
			std::cout << personrecToShow->sName << " $";
			std::cout << personrecToShow->nBribe << "\n";
			personrecToShow = personrecToShow->personrecNext;
			nPlaceInLine++;
		} while(personrecToShow != NULL);
	}
}
void PersonList::AddToList() {
	PersonRec* personrecAddition = new PersonRec;
	std::cout << "Enter the person's name: ";
	getline(std::cin, personrecAddition->sName);
	std::cout << "Enter the person's contribution: ";
	std::cin >> personrecAddition->nBribe;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	bool bPlacedAdditionInList = false;
	PersonRec** personrecAdditionMightPlaceInFrontOf = &head;
	do {
		if((*personrecAdditionMightPlaceInFrontOf) == NULL) {
			(*personrecAdditionMightPlaceInFrontOf) = personrecAddition;
			bPlacedAdditionInList = true;
		} else {
			bool bFoundAdditionsPlace = false;
			if((*personrecAdditionMightPlaceInFrontOf)->nBribe < personrecAddition->nBribe) {
				bFoundAdditionsPlace = true;
			} else {
				if((*personrecAdditionMightPlaceInFrontOf)->nBribe == personrecAddition->nBribe)
					if((*personrecAdditionMightPlaceInFrontOf)->sName.compare(personrecAddition->sName) > 0)
						bFoundAdditionsPlace = true;
			}
			if(bFoundAdditionsPlace) {
				personrecAddition->personrecNext = (*personrecAdditionMightPlaceInFrontOf);
				(*personrecAdditionMightPlaceInFrontOf) = personrecAddition;
				bPlacedAdditionInList = true;
			} else {
				personrecAdditionMightPlaceInFrontOf = &(*personrecAdditionMightPlaceInFrontOf)->personrecNext;
			}
		}
	} while(bPlacedAdditionInList == false);
}