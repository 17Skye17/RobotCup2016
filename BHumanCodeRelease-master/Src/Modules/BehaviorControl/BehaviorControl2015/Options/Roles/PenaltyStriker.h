option(PenaltyStriker)
{
  //int numOfObstacles = theObstacleModel.obstacles.size();
  initial_state(start)
  {
    transition
    {
      if(state_time > 1000)
        goto turnToBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      Stand();
    }
  }
  
    state(turnToBall)
  {
    transition
    {
      if(std::abs(theBallModel.estimate.position.angle()) < 5_deg)
        goto walkToBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(50.f, 50.f, 50.f), Pose2f(theBallModel.estimate.position.angle(), 0.f, 0.f));
    }
  }
  
  state(walkToBall)
  {
    transition
    {
      if(theBallModel.estimate.position.norm() < 500.f)
        goto alignToGoal;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(50.f, 50.f, 50.f), theBallModel.estimate.position);
    }
  }
  
  state(alignToGoal)
  {
    transition
    {
    
      if(std::abs(libCodeRelease.angleToGoalForStriker) < 10_deg && std::abs(theBallModel.estimate.position.y()) < 100.f)
        goto alignBehindBall;
    }
    action
    {
      theHeadControlMode = HeadControl::lookForward;
      WalkToTarget(Pose2f(100.f, 100.f, 100.f), Pose2f(libCodeRelease.angleToGoalForStriker, theBallModel.estimate.position.x() - 400.f, theBallModel.estimate.position.y()));
    }
  }
  
  state(alignBehindBall)
  {
    transition
    {
      if(libCodeRelease.between(theBallModel.estimate.position.y(), -50.f, -30.f)
          && libCodeRelease.between(theBallModel.estimate.position.x(), 140.f, 170.f)
          && std::abs(libCodeRelease.angleToGoalForStriker) < 2_deg)
        goto shoot;
    }
    action
    {
      theHeadControlMode = HeadControl::focusBall;
      WalkToTarget(Pose2f(80.f, 80.f, 80.f), Pose2f(libCodeRelease.angleToGoalForStriker, theBallModel.estimate.position.x() - 150.f, theBallModel.estimate.position.y() + 30.f));
    }
  }
  
  //**Kick with right leg straight**//
    state(shoot)
    {
        transition
        {
            if( (state_time > 10 && action_done))
                    goto turnToBall;
        }
        action
        {
            theHeadControlMode = HeadControl::focusBall;
            ShootKick();//shoot type
        }
    }
      
}