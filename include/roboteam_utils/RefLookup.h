#include <iostream>
#include <map>

const std::map <std::string,int> refstagelookup = {
	{"NORMAL_FIRST_HALF_PRE", 0},
	{"NORMAL_FIRST_HALF", 1},
	{"NORMAL_HALF_TIME", 2},
	{"NORMAL_SECOND_HALF_PRE", 3},
	{"NORMAL_SECOND_HALF", 4},
	{"EXTRA_TIME_BREAK", 5},
	{"EXTRA_FIRST_HALF_PRE", 6},
	{"EXTRA_FIRST_HALF", 7},
	{"EXTRA_HALF_TIME", 8},
	{"EXTRA_SECOND_HALF_PRE", 9},
	{"EXTRA_SECOND_HALF", 10},
	{"PENALTY_SHOOTOUT_BREAK", 11},
	{"PENALTY_SHOOTOUT", 12},
	{"POST_GAME", 13}
};

const std::map <std::string,int> refcommandlookup = {
	{"HALT",0},
	{"STOP",1},
	{"NORMAL_START",2},
	{"FORCE_START",3},
	{"PREPARE_KICKOFF_US",4},
	{"PREPARE_KICKOFF_THEM",5},
	{"PREPARE_PENALTY_US",6},
	{"PREPARE_PENALTY_THEM",7},
	{"DIRECT_FREE_US",8},
	{"DIRECT_FREE_THEM",9},
	{"INDIRECT_FREE_US",10},
	{"INDIRECT_FREE_THEM",11},
	{"TIMEOUT_US",12},
	{"TIMEOUT_THEM",13},
	{"GOAL_US",14},
	{"GOAL_THEM",15},
	{"BALL_PLACEMENT_US",16},
	{"BALL_PLACEMENT_THEM",17}	
	
};