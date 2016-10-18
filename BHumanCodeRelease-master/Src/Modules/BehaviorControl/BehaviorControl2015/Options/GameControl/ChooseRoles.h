option(ChooseRoles)
{
	char KEEPER_NUM =1;
	char DEFENDER_LEFT = 4;
	char STRIKER_NUM = 2;
	char SUPPORTER_NUM = 3;
    char DEFENDER_RIGHT = 5;
  /** Stand still and wait. */
  initial_state(initial)
  {
	  transition{
		  if ( theRobotInfo.number == KEEPER_NUM )
			goto Keeper;
		else if  ( theRobotInfo.number == DEFENDER_LEFT)
			goto DefenderLeft;
        else if ( theRobotInfo.number == DEFENDER_RIGHT)
            goto DefenderRight;
		else if (theRobotInfo.number == STRIKER_NUM)
			goto Striker;
		else if (theRobotInfo.number == SUPPORTER_NUM)
			goto Supporter;
	}
    action
    {
     theHeadControlMode = HeadControl::none;
      SetHeadPanTilt(0.f, 0.f, 150_deg);
    }
  }
  state(Keeper)
  {
	  action
	  {
		  Keeper();
          theBehaviorStatus.role = Role::keeper;
		}
	}
	state(DefenderLeft)
  {
	  
	  action
	  {
			//ShowTeammateData(otherTeammate.number,otherTeammate.ball);
           // for(Obstacle o:theObstacleModel.obstacles)
             //   ShowObstacles(o.center);
			DefenderLeft();
            theBehaviorStatus.role = Role::defender;
		}
	}
    
    state(DefenderRight)
    {
        action
        {
            DefenderRight();
            theBehaviorStatus.role = Role::defender;

        }
    }
    
state(Striker)
  {
	  transition{
		  if ( theTeammateData.numberOfActiveTeammates !=0 ){//判断是否有发送消息的队友，没有的情况默认为Striker
				for (Teammate tempTeammate:theTeammateData.teammates)
				{		//找到Supporter的信息
						if (tempTeammate.number != KEEPER_NUM &&
							tempTeammate.number != DEFENDER_LEFT && 
                            tempTeammate.number != DEFENDER_RIGHT &&
							tempTeammate.number != 5&& 
							tempTeammate.number != theRobotInfo.number )
							{otherTeammate=tempTeammate;}
				}
				if (theFrameInfo.getTimeSince(otherTeammate.ball.timeWhenLastSeen) < 600 &&
						//libCodeRelease.timeSinceBallWasSeen()<300 &&
						(otherTeammate.ball.estimate.position.norm() < theBallModel.estimate.position.norm()) )
					goto Supporter;
		  }
	  }
	  action
	  {
          if(theGameInfo.kickOffTeam != theOwnTeamInfo.teamNumber)
            {
                if(theBallModel.estimate.velocity.x() > 0.0 || theBallModel.estimate.velocity.y() > 0.0 || state_time  > 10000)
                {
                    ShowTeammateData(otherTeammate.number,otherTeammate.ball);
                    StrikerDong1();
                    theBehaviorStatus.role = Role::striker;
                }
            }
            
            else 
            {
                ShowTeammateData(otherTeammate.number,otherTeammate.ball);
                StrikerDong1();
                theBehaviorStatus.role = Role::striker;
            }
		  
		}
	}
	state(Supporter)
  {
	  transition{
		  if ( theTeammateData.numberOfActiveTeammates !=0 ){//判断是否有发送消息的队友，没有的情况默认为Striker
				for (Teammate tempTeammate:theTeammateData.teammates)
				{		//找到Striker的信息
						if (tempTeammate.number != KEEPER_NUM &&
							tempTeammate.number != DEFENDER_LEFT && 
                            tempTeammate.number != DEFENDER_RIGHT &&
							tempTeammate.number != 5&& 
							tempTeammate.number != theRobotInfo.number )
							{otherTeammate=tempTeammate;}
				}
				if (otherTeammate.number ==-1 || otherTeammate.status != Teammate::Status::FULLY_ACTIVE )//为空或者没有在踢球
					goto Striker;
				if (theFrameInfo.getTimeSince(otherTeammate.ball.timeWhenLastSeen) < 600 &&
							//libCodeRelease.timeSinceBallWasSeen()<300 &&
							(otherTeammate.ball.estimate.position.norm() > theBallModel.estimate.position.norm()) )
					goto Striker;
				//else if (theFrameInfo.getTimeSince(otherTeammate.ball.timeWhenLastSeen) > 7000 &&
							//libCodeRelease.timeSinceBallWasSeen()<300)
					//goto Striker;
		  }
		  else {goto Striker;}
	  }
	  action
	  {
          
          if(theGameInfo.kickOffTeam != theOwnTeamInfo.teamNumber)
            {
                if(theBallModel.estimate.velocity.x() > 0.0 || theBallModel.estimate.velocity.y() > 0.0 || state_time  > 10000)
                {
                    ShowTeammateData(otherTeammate.number,otherTeammate.ball);
                    theBehaviorStatus.role = Role::supporter;
                    Supporter();
                }
            }
            
            else 
            {
                ShowTeammateData(otherTeammate.number,otherTeammate.ball);
                theBehaviorStatus.role = Role::supporter;
                Supporter();
            }
		}
	}
/*	state(defaultRole)
  {
	  
	  action
	  {
            if (theRobotInfo.number == SUPPORTER_NUM){
                theBehaviorStatus.role = Role::supporter;
                Supporter();
                }
            else if (theRobotInfo.number == STRIKER_NUM){
                theBehaviorStatus.role = Role::striker;
                StrikerDong1();
                }
			//ShowTeammateData(otherTeammate.number,otherTeammate.ball);
			 
		}
	}*/
}
Teammate otherTeammate;