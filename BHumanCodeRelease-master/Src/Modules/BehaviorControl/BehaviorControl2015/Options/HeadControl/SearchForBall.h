option(SearchForBall)
{

    initial_state(LeftAndRight) {
        transition {
            if(action_done)
                goto lookRight;
        }
        action {
            SetHeadPanTilt(-0.8f, 0.f, 50_deg);
        }
    }
    state(lookRight) {
        transition {
            if(action_done)
                goto lookLeft;
        }
        action {
            SetHeadPanTilt(0.8f, 0.f, 50_deg);
        }
    }
    state(lookLeft) {
        transition {
            if(action_done)
                goto lookRight1;
        }
        action {
            SetHeadPanTilt(-0.8f, 0.f, 50_deg);
        }
    }

    state(lookRight1) {
        transition {
            if(action_done)
                goto lookLeft1;
        }
        action {
            SetHeadPanTilt(0.8f, 0.f, 50_deg);
        }
    }


    state(lookLeft1) {
        transition
        {
            if (action_done)
                goto LeftAndRight;
        }
        action {
            SetHeadPanTilt(-0.8f, 0.f, 50_deg);
        }
    }
}
