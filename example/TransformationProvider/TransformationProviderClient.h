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
#ifndef _KUKA_FRI_TRANSFORMATION_PROVIDER_CLIENT_H
#define _KUKA_FRI_TRANSFORMATION_PROVIDER_CLIENT_H

#include "friTransformationClient.h"

using namespace KUKA::FRI;

/**
 * \brief Example client for changing the transformation matrix of a robot frame.
 */
class TransformationProviderClient : public TransformationClient
{
private:
double _transformationMatrix[3][4];

public:
      
   /**
    * \brief Constructor.
    * 
    */
   TransformationProviderClient();
   
   /** 
    * \brief Destructor.
    */
   ~TransformationProviderClient();
   
   /**
    * \brief Callback in which the new transformation matrix is calculated.
    */
   virtual void provide();
};

#endif // _KUKA_FRI_TRANSFORMATION_PROVIDER_CLIENT_H
