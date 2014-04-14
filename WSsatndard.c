#include &lt;Client.h&gt;
#include &lt;Ethernet.h&gt;
#include &lt;Server.h&gt;
#include &lt;Udp.h&gt;
#include &lt;SPI.h&gt;
/*
 * Web Server
  *
   * A simple web server: Displays a button to open/close
    * a Store and Store status
     */
      //-----------------------BEGIN Variable setup -------------------------------
       
       String readString = String(30); //string for fetching data from address
       boolean LEDON = false; //LED status flag
        
	int state;
	int val=0;
	 
	 byte mac[] = {
	   0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
	   byte ip[] =  {
	     192, 168, 1, 19 }; //Change your IP Address here
	     Server server(80); //Standard HTTP server port
	      
	      //-----------------------END Variable setup-------------------------------
	       
	       void setup()
	       {
	         pinMode(4, OUTPUT);    
		  
		    Ethernet.begin(mac, ip);
		      server.begin();
		        delay(100);
			  Serial.begin(57600);  //XBee module Baud rate
			    delay(100);
			      }
			      void loop()
			      {
			      //---------------Web Server initialization------------------------------
			        Client client = server.available();
				  if (client) {
				   
				       boolean current_line_is_blank = true;
				           while (client.connected()) {
					         if (client.available()) {
						         char c = client.read();
							         if (readString.length() &lt; 100)
								       {
								        
									        readString += c;
										      }
										      ///////////Check button status to determine actions to take for submit button///////////////
										             if(readString.indexOf("IO=1") &gt;0){ // If Store open request sent;
											                                               // send instruction to remote arduino
																                    if (LEDON== false){          //Ensure it only send the info once
																		                 //led has to be turned ON
																				              LEDON = true;                //Change LED state to print on the page
																					                   Serial.print('G');           //Send command to remote Arduino
																							               }
																								                  }
																										             if(readString.indexOf("IO=0") &gt;0){//Same as above but not used in
																											                                                  //this application
																																	             if (LEDON== true){
																																		                  //led has to be turned OFF
																																				               LEDON = false;
																																					                    Serial.print('K');
																																							               }
																																								                  }
																																										  ///////////////Finish checking and actions for submit button//////////////////
																																										   
																																										   //------------------Standard web Server -------------------------------
																																										           if (c == 'n' &amp;&amp; current_line_is_blank) {
																																											             // send a standard http response header
																																												               client.println("HTTP/1.1 200 OK");
																																													                 client.println("Content-Type: html");
																																															           client.println();
																																																             client.println("&lt;html&gt;");
																																																	               client.println("&lt;head&gt;");
																																																		                 client.println("&lt;title&gt;Xboard interface--Store control&lt;/title&gt;");
																																																				           client.println("&lt;/head&gt;");
																																																					             client.println("&lt;body&gt;");
																																																						               client.print("Welcome Home Automation Config");
																																																							                 client.println("&lt;br /&gt;");
																																																									           client.print("//*************************************");
																																																										             client.println("&lt;br /&gt;");
																																																											               client.println("&lt;br /&gt;");
																																																												                 client.print("//*************************************");
																																																														           client.println("&lt;br /&gt;");
																																																															             client.println("&lt;br /&gt;");
																																																																               client.print("&lt;form&gt;");
																																																																	                 client.print("&lt;input type=radio name=IO value=1 /&gt; Open&lt;br /&gt;");
																																																																			           client.print("&lt;input type=submit value=Submit &lt;/form&gt;&lt;br /&gt;");
																																																																				             client.println("&lt;/body&gt;");
																																																																					                 break;
																																																																							             }
																																																																								      
																																																																								              if (c == 'n') {
																																																																									                // we're starting a new line
																																																																											          current_line_is_blank = true;
																																																																												          }
																																																																													          else if (c != 'r') {
																																																																														            // we've gotten a character on the current line
																																																																															              current_line_is_blank = false;
																																																																																              }
																																																																																	            }
																																																																																		        }
																																																																																			//------------------END Standard web Server Jargon-------------------------------
																																																																																			 
																																																																																			 //-----------------Print Store status on web page and auto refresh----------------
																																																																																			      if (LEDON){
																																																																																			                //printing LED status
																																																																																					         client.print("&lt;font size='5'&gt;STORE status: ");
																																																																																						          client.println("&lt;font color='green' size='5'&gt;OPEN");
																																																																																							           client.println("&lt;META HTTP-EQUIV=REFRESH CONTENT=2;url=http://192.168.0.177/&gt;"); //Autorefresh
																																																																																								                           //Auto-refresh the site after 2 seconds to reset the Store status to closed
																																																																																											        }
																																																																																												     else{
																																																																																												               client.print("&lt;font size='5'&gt;STORE status: ");
																																																																																													                 client.println("&lt;font color='grey' size='5'&gt;CLOSED");
																																																																																															      }
																																																																																															                client.println("&lt;hr /&gt;");
																																																																																																	          client.println("&lt;hr /&gt;");
																																																																																																		            client.println("&lt;/body&gt;&lt;/html&gt;");
																																																																																																			              //clearing string for next read
																																																																																																				                readString="";
																																																																																																						//-----------------END Print Store status on web page and auto refresh----------------
																																																																																																						    client.stop();
																																																																																																						      }
																																																																																																						       
																																																																																																						       /*Routine to read response from remote Arduino
																																																																																																						        *and light local LED on PIN4
																																																																																																							 */
																																																																																																							    if (Serial.available() &gt; 0) {
																																																																																																							        val = Serial.read();
																																																																																																								    if (val == 'H') { //These values ('H')can be changed to what ever you want
																																																																																																								                          //just make sure you change them in both the server
																																																																																																											                        //program and the client program
																																																																																																														      digitalWrite(4, HIGH);
																																																																																																														            delay (20);
																																																																																																															         }
																																																																																																																     if (val == 'L') {
																																																																																																																           digitalWrite(4, LOW);
																																																																																																																	          delay (20);
																																																																																																																		      }
																																																																																																																		         }
																																																																																																																			 }
