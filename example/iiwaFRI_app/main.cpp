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
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strstr
#include "appClient.h"
#include "friUdpConnection.h"
#include "friClientApplication.h"
#include <unistd.h>
#include <boost/thread/thread.hpp>
#include <mutex>


#define CLIENT "172.31.1.145"
#define SERVER "172.31.1.147"

using namespace KUKA::FRI;

#define DEFAULT_PORTID 30200
#define DEFAULT_JOINTMASK 0x8
#define DEFAULT_FREQUENCY 0.25
#define DEFAULT_AMPLITUDE 0.04
#define DEFAULT_FILTER_COEFFICIENT 0.99

using namespace std;

ROBOT_CMD rc;
std::mutex rc_mtx;

void get_command() {
   int input_socket;
   listener_socket(9031, &input_socket);

   int slen, rlen;
	sockaddr_in si_other;
	ROBOT_CMD rc_in;
	while( true ) {
		rlen = recvfrom( input_socket, &rc_in, sizeof(rc_in),0,(struct sockaddr*)&si_other, (socklen_t*)&slen);
      if (rlen>0) {
         rc_mtx.lock();
         for(int i=0; i<7; i++ )
            rc.jcmd[i] = rc_in.jcmd[i];
         rc_mtx.unlock();

         //cout << "Jcommand: ";
         //for(int i=0; i<7; i++ ) cout << rc.jcmd[i] << " ";
         //cout << endl;
      }
	}
}

int main (int argc, char** argv)
{
   

  //Input/output via socket
  ROBOT_STATE rs;
  int out_socket;

  boost::thread func( &get_command );

  create_socket( CLIENT, 9030, &out_socket);

   /***************************************************************************/
   /*                                                                         */
   /*   Place user Client Code here                                           */
   /*                                                                         */
   /**************************************************************************/

   // create new sine overlay client
   appClient client;

   /***************************************************************************/
   /*                                                                         */
   /*   Standard application structure                                        */
   /*   Configuration                                                         */
   /*                                                                         */
   /***************************************************************************/

   // create new udp connection
   UdpConnection connection;

   // pass connection and client to a new FRI client application
   ClientApplication app(connection, client);


   bool success = true;
   // connect client application to KUKA Sunrise controller
   success=app.connect(30200, SERVER);
   printf("Success?: %d\n", success);
   //int i=0;

   while (client.getCurrentState() != MONITORING_WAIT ) {
      app.step();
      usleep(0.002*1e6);
   } // Robot is ready to read the joint pos

   //---Set robot command first time, equal to read joint positions
   client.get_js( rs );
   for(int i=0; i<7; i++ )
      rc.jcmd[i] = rs.jstate[i];
   client.set_rc( rc );
   //---

   while( true ) {
      client.get_js( rs );
      write( out_socket, &rs, sizeof(rs) );
      
      //Apply command ( read from socket ) 
      rc_mtx.lock();
      client.set_rc( rc );
      rc_mtx.unlock();
/*

      cout << "Letto: " << endl;
      for(int i=0; i<7; i++ )
            cout << rs.jstate[i] << " ";
      cout << endl;

      cout << "Comandato: " << endl;
      for(int i=0; i<7; i++ )
            cout << rc.jcmd[i] << " ";
      cout << endl;
*/
      app.step();
   }
/*
   //Solo quando sono in stato operativo
   while (i++ < 300 )
   {
      client.get_js( rs );
      //client.set_rc( )
      cout << "Jstate: ";
      
      cout << endl;

      int scritto = write( out_socket, &rs, sizeof(rs) );
      cout << "SCritto: " << scritto << endl;
      printf("iter %d: ", i);
      success = app.step();
      //printf("Success?: %d\n", success);

      //get js

      //write js
   }
*/
   /***************************************************************************/
   /*                                                                         */
   /*   Standard application structure                                        */
   /*   Dispose                                                               */
   /*                                                                         */
   /***************************************************************************/

   // disconnect from controller
   app.disconnect();

   return 1;
}
