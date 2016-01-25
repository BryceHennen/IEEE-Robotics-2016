#include <BrainActions.h>

//Virtual class that is a functor (which stores a function [with arguments!] and can be called later).
Action::Action(Brain* brain)
{
	brain_ = brain;
};

ActionResult Action::Run() //Execute the parenthesis operator.
{
	return (*this)();
}

//Follow Wall //////////////////////////
FollowWallAction::FollowWallAction(Brain* brain, Direction dir, StopConditions success_flags, StopConditions error_flags)
	: Action(brain), dir_(dir), success_flags_(success_flags), error_flags_(error_flags)
{};

ActionResult FollowWallAction::operator()()
{
	StopConditions ret_flag = brain_->FollowWall(dir_, success_flags_ | error_flags_);
	if(ret_flag == StopConditions::NONE)
	{
		return ACT_GOING;
	}
	else if(any_flags<StopConditions, byte>(ret_flag & error_flags_))
	{
		return ActionResult(ret_flag);
	}
	else if(any_flags<StopConditions, byte>(ret_flag & success_flags_))
	{
		return ACT_SUCCESS;
	}
};

//Travel Past Wall //////////////////////////
TravelPastWallAction::TravelPastWallAction(Brain* brain, Direction dir) : Action(brain), dir_(dir)
{};

ActionResult TravelPastWallAction::operator()()
{
	if(brain_->TravelPastWall(dir_))
	{
		return ACT_SUCCESS;
	}
	else
	{
		return ACT_GOING;
	}
};

//Go To Victim //////////////////////////
GoToVictimAction::GoToVictimAction(Brain* brain) : Action(brain)
{};

ActionResult GoToVictimAction::operator()()
{
	if(brain_->GoToVictim())
	{
		return ACT_SUCCESS;
	}
	else
	{
		return ACT_GOING;
	}
};

//Rotate 90 //////////////////////////
Rotate90Action::Rotate90Action(Brain* brain, Direction dir) : Action(brain), dir_(dir)
{};

ActionResult Rotate90Action::operator()()
{
	if(brain_->Rotate90(dir_))
	{
		return ACT_SUCCESS;
	}
	else
	{
		return ACT_GOING;
	}
};