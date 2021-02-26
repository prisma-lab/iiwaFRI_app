// version: 1.5
/**

DISCLAIMER OF WARRANTY

This material targets the purpose of evaluation only, and is not developed
for productive use.
The Software is provided "AS IS" and "WITH ALL FAULTS,"
without warranty of any kind, including without limitation the warranties
of merchantability, fitness for a particular purpose and non-infringement.
KUKA makes no warranty that the Software is free of defects or is suitable
for any particular purpose. In no event shall KUKA be responsible for loss
or damages arising from the installation or use of the Software,
including but not limited to any indirect, punitive, special, incidental
or consequential damages of any character including, without limitation,
damages for loss of goodwill, work stoppage, computer failure or malfunction,
or any and all other commercial damages or losses.
The entire risk to the quality and performance of the Software is not borne by KUKA.
Should the Software prove defective, KUKA is not liable for the entire cost
of any service and repair.


COPYRIGHT

All Rights Reserved
Copyright (C)  2014
KUKA Laboratories GmbH
Augsburg, Germany

This material is the exclusive property of KUKA Laboratories GmbH and must be returned
to KUKA Laboratories GmbH immediately upon request.
This material and the information illustrated or contained herein may not be used,
reproduced, stored in a retrieval system, or transmitted in whole
or in part in any way - electronic, mechanical, photocopying, recording,
or otherwise, without the prior written consent of KUKA Laboratories GmbH.



*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "appClient.h"

#define CTRL_ACTIVE 1
#ifndef M_PI
#define M_PI 3.14159265358979
#endif

//******************************************************************************
appClient::appClient() {
   printf("appClient initialized");
   _current_state = IDLE;
}

//******************************************************************************
appClient::~appClient()
{

}

//******************************************************************************
void appClient::onStateChange(ESessionState oldState, ESessionState newState)
{
   LBRClient::onStateChange(oldState, newState);
   // (re)initialize sine parameters when entering Monitoring
   switch (newState)
   {
      case MONITORING_READY:
      {
        printf("State changed! Now we are in MONITORING_READY\n");
         /*
         _offset = 0.0;
         _t = 0.0;
         _stepWidth = 2 * M_PI * _freqHz * robotState().getSampleTime();
         */
         printf("Sample Time: %f\n", robotState().getSampleTime());
         _current_state = MONITORING_READY;
         break;
      }
      case MONITORING_WAIT:
      {
        printf("State changed! Now we are in MONITORING_WAIT\n");
        _current_state = MONITORING_WAIT;
        break;
      }
      case COMMANDING_WAIT:
      {
        printf("State changed! Now we are in COMMANDING_WAIT\n");
        _current_state = COMMANDING_WAIT;
        break;
      }
      case COMMANDING_ACTIVE:
      {
        _current_state = COMMANDING_ACTIVE;

        printf("State changed! Now we are in COMMANDING_ACTIVE\n");
        break;
      }
      case IDLE:
      {
        _current_state = IDLE;
        printf("State changed! Now we are in ACTIVE\n");
        break;
      }
      default:
      {
         break;
      }
   }
}


void appClient::get_js(ROBOT_STATE & state) {
   memcpy(_rs.jstate, robotState().getMeasuredJointPosition(), 7 * sizeof(double));
   state = _rs;
}



//******************************************************************************
void appClient::command()
{

   // calculate new offset
   /*
   double newOffset = _amplRad * sin(_t);
   _offset = _offset * _filterCoeff + newOffset * (1.0 - _filterCoeff);
   _t += _stepWidth;
   if (_t >= 2 * M_PI) _t -= 2 * M_PI;
   */
   // add offset to ipo joint position for all masked joints
   //memcpy(_rs.jstate, robotState().getMeasuredJointPosition(), 7 * sizeof(double));


   //jointPos[0]+=step;
   //printf("Robot joints states: ");
   //for (int i=0; i<7; i++)
   //  printf("%f ",jointPos[i]);
   //printf("\n");
   /*
   for (int i=0; i<7; i++)
   {
      if (_jointMask & (1<<i))
      {
         jointPos[i] += _offset;
      }
   }
   */

  if( CTRL_ACTIVE )
   robotCommand().setJointPosition(_rc.jcmd);
  else 
   robotCommand().setJointPosition(_rs.jstate);
  
   //printf("Commanding joint[0]: %f\n",jointPos[0]);

}
