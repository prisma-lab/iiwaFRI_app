/**

DISCLAIMER OF WARRANTY

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
Copyright (C)  2014-2015 
KUKA Roboter GmbH
Augsburg, Germany

This material is the exclusive property of KUKA Roboter GmbH and must be returned 
to KUKA Roboter GmbH immediately upon request.  
This material and the information illustrated or contained herein may not be used, 
reproduced, stored in a retrieval system, or transmitted in whole 
or in part in any way - electronic, mechanical, photocopying, recording, 
or otherwise, without the prior written consent of KUKA Roboter GmbH.  






1.9
*/
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "TransformationProviderClient.h"

//******************************************************************************
TransformationProviderClient::TransformationProviderClient()
{
   printf("TransformationProviderClient initialized:\n");

   // create a transformation matrix which keeps the orientation of the frame but 
   // results in a translational movement
   for (int row = 0; row < 3; row++)
   {
      for (int column = 0; column < 4; column++)
      {
         if (row == column)
         {
            _transformationMatrix[row][column] = 1;
         }
         else if (column == 3)
         {
            _transformationMatrix[row][column] = 10;
         }
         else
         {
            _transformationMatrix[row][column] = 0;
         }
      }
   }
   // _transformationMatrix is now:
   // {  1, 0, 0, 10},
   // {  0, 1, 0, 10},
   // {  0, 0, 1, 10}

}

//******************************************************************************
TransformationProviderClient::~TransformationProviderClient()
{
}

//******************************************************************************
void TransformationProviderClient::provide()
{
   // Change the translational vector of the transformation matrix (all values in mm)
   double x = _transformationMatrix[0][3];
   if (x < 100)
   {
      x++;
   }
   else
   {
      x = 0;
   }
   _transformationMatrix[0][3] = x;

   double y = _transformationMatrix[1][3];
   if (y < 200)
   {
      y += 5;
   }
   else
   {
      y = 0;
   }
   _transformationMatrix[1][3] = y;

   double z = _transformationMatrix[2][3];
   if (z < 300)
   {
      z += 10;
   }
   else
   {
      z = 0;
   }
   _transformationMatrix[2][3] = z;

   //printf("X:%f, Y:%f, Z:%f\n", _transformationMatrix[0][3], _transformationMatrix[1][3], _transformationMatrix[2][3]);

   // Set new transformation matrix for frame with identifier"PBase"
   setTransformation("PBase", _transformationMatrix, getTimestampSec(),
         getTimestampNanoSec());
}
