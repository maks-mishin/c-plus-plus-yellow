#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <string>

/*
	@brief - Status of task
*/
enum class TaskStatus
{
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

// Amount of tasks for each status
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks
{
public:
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const;

	void AddNewTask(const std::string& person);

	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count
	);
private:
	/*
		@brief - Container for keeping data of developers team
		First param - name of deleloper
		Second param - statistics for this developer
	*/
	std::map<std::string, TasksInfo> dev_team;
};

/*
	@brief - remove items of TasksInfo, when TasksInfo[TaskStatus] == 0
	@param - object TasksInfo
*/
void RemoveZeroItems(TasksInfo& tasks)
{
	std::vector<TaskStatus> stats_remove;
	for (const auto& task : tasks)
	{
		if (task.second == 0)
			stats_remove.push_back(task.first);
	}
	for (const auto status : stats_remove)
	{
		tasks.erase(status);
	}
}

/*
	@brief - Get information about specific developer
	@return - object TasksInfo
	@param - name of developer
*/
const TasksInfo& TeamTasks::GetPersonTasksInfo(const std::string& person) const
{
	return dev_team.at(person);
}

/*
	@brief - Function for make new task for specific developer
	@param - name of developer
*/
void TeamTasks::AddNewTask(const std::string & person)
{
	++dev_team[person][TaskStatus::NEW];
}

/*
	@brief - Function for changing status of task
	@return - new status (next)
	@param - current status
*/
TaskStatus ChangeTaskStatus(TaskStatus src_status)
{
	return static_cast<TaskStatus>(static_cast<int>(src_status) + 1);
}

/*
	@brief - Function for removing items of TasksInfo, within amount of tasks for
	specific status equals 0
	@param - obj TasksInfo
*/
void RemoveZeros(TasksInfo& tasks_info) 
{
	std::vector<TaskStatus> statuses_to_remove;
	for (const auto& task_item : tasks_info) 
	{
		if (task_item.second == 0) 
		{
			statuses_to_remove.push_back(task_item.first);
		}
	}
	for (const TaskStatus status : statuses_to_remove) 
	{
		tasks_info.erase(status);
	}
}

/*
	@brief - Function for refreshing the status part of tasks for developers team
	@return - tuple (updated_tasks, untouched_tasks)
	@param1 - name of developer
	@param2 - amount of tasks which are need to refresh
*/
std::tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const std::string & person, int task_count)
{
	TasksInfo updated_tasks, untouched_tasks;

	TasksInfo& tasks = dev_team[person];

	for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = ChangeTaskStatus(status)) 
	{
		TaskStatus new_status = ChangeTaskStatus(status);

		updated_tasks[new_status] = std::min(task_count, tasks[status]);
		task_count -= updated_tasks[new_status];
	}

	for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = ChangeTaskStatus(status)) 
	{
		TaskStatus new_status = ChangeTaskStatus(status);

		untouched_tasks[status] = tasks[status] - updated_tasks[new_status];
		tasks[status] += updated_tasks[status] - updated_tasks[new_status];
	}
	
	tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

	RemoveZeros(updated_tasks);
	RemoveZeros(untouched_tasks);
	RemoveZeros(dev_team.at(person));

	return std::make_tuple(updated_tasks, untouched_tasks);
}

/*
	@brief - Function for print info for team
*/
void PrintTasksInfo(TasksInfo tasks_info) {
	std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}