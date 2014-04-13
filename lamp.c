#include <RCSwitch.h>
#include <LiquidCrystal.h>

RCSwitch mySwitch = RCSwitch(); 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // déclare une variable LiquidCrystal appelée lcd 
int i=0;
int j=0;
int s=0;
int inter;

const int LAMP_TEST = 13; 
const int SOUND_SENSOR = A0; //pin du capteur de son
const int THRESHOLD = 350; //niveau sonore du clap
const int SOUND_SAMPLE_LENGTH = 100; //temps avant on/off
const int CLAP_DURATION_WINDOW = 1500; //temps entre chaque clap
const int CLAPS_FOR_TRIGGER = 2; // nombre de clap avant enclenchement

unsigned long lastLampRelayLoop = 0;
int soundSensorReading = 0;
int soundLength = 0;
int previousSoundLength = 0;
int soundSampleLength = SOUND_SAMPLE_LENGTH;
int clapDurationWindow = CLAP_DURATION_WINDOW;
int currentClaps = 0;
int relayState = LOW;
 
 //////// initialisation
 void setup() 
 {
   mySwitch.enableTransmit(10);    //transmetteur RF sur la pin 10
     pinMode(10, OUTPUT);
       pinMode(9, INPUT);
         digitalWrite(9 ,LOW);
	   
	     Serial.begin(9600);
	       pinMode(LAMP_TEST, OUTPUT);    // LED son
	         lcd.begin(8, 2);               //LCD 

		   ////nom
		      lcd.clear();
		         lcd.setCursor(0, 0);
			    lcd.print("  DOMO");
			       delay(1000);
			          lcd.setCursor(0, 1);
				     lcd.print(" MAISON");

				     }

				      
				      void loop() {
				       inter = digitalRead(9); 
				        soundSensorReading = analogRead(SOUND_SENSOR);
					   
					     if (Serial.available())
					       {
					           byte inBT = Serial.read();     //lecture du code envoyé

						   ///////power      
						       if (inBT == 'C')
						           {
							   	  i++;
								  	  if ( (i % 2) == 0)
									  	  {
										        		mySwitch.switchOff(4, 1);
															mySwitch.switchOff(4, 2);
															      		mySwitch.switchOff(4, 3);
																			mySwitch.switchOff(4, 4); 
																			   
																			      		//affichage   
																					    		lcd.clear();
																							    		lcd.setCursor(0, 0);
																									    		lcd.print("1,2,3et4");
																											    		lcd.setCursor(0, 1);
																															lcd.print("eteintes");
																															    		Serial.println("prises 1, 2, 3 et 4 eteintes");
																																	    	   }
																																		      	 else
																																			 	   {   
																																				       		mySwitch.switchOn(4, 1);
																																						    		mySwitch.switchOn(4, 2);
																																								    		mySwitch.switchOn(4, 3);
																																										    		mySwitch.switchOn(4, 4);
																																												    
																																												           		//affichage   
																																															    		lcd.clear();
																																																	    		lcd.setCursor(0, 0);
																																																			    		lcd.print("1,2,3et4");
																																																					    		lcd.setCursor(0, 1);
																																																							    		lcd.print("allumees");;
																																																									   	  }
																																																										      }

																																																										      ///////ON    
																																																										          if (inBT == 'a') 
																																																											      {
																																																											          mySwitch.switchOn(4, 1);
																																																												      
																																																												          //affichage 
																																																													     Serial.println("prise 1 allumee");  
																																																													         lcd.clear();
																																																														     lcd.setCursor(0, 0);
																																																														         lcd.print("prise 1");
																																																															     lcd.setCursor(0, 1);
																																																															         lcd.print("allumee");
																																																																     }
																																																																         
																																																																	     if (inBT == 'c') 
																																																																	         {
																																																																		     mySwitch.switchOn(4, 2);
																																																																		         //affichage 
																																																																			    Serial.println("prise 2 allumee");  
																																																																			        lcd.clear();
																																																																				    lcd.setCursor(0, 0);
																																																																				        lcd.print("prise 2");
																																																																					    lcd.setCursor(0, 1);
																																																																					        lcd.print("allumee");
																																																																						    }
																																																																						        
																																																																							    if (inBT == 'b') 
																																																																							        {
																																																																								    mySwitch.switchOn(4, 3);
																																																																								        //affichage   
																																																																									   Serial.println("prise 3 allumee");
																																																																									       lcd.clear();
																																																																									           lcd.setCursor(0, 0);
																																																																										       lcd.print("prise 3");
																																																																										           lcd.setCursor(0, 1);
																																																																											       lcd.print("allumee");
																																																																											           }
																																																																												       if (inBT == 'd') 
																																																																												           {
																																																																													       mySwitch.switchOn(4, 4);
																																																																													           //affichage 
																																																																														      Serial.println("prise 4 allumee");  
																																																																														          lcd.clear();
																																																																															      lcd.setCursor(0, 0);
																																																																															          lcd.print("prise 4");
																																																																																      lcd.setCursor(0, 1);
																																																																																          lcd.print("allumee");
																																																																																	      }
																																																																																	          
																																																																																		      if (inBT == 'U') 
																																																																																		          {   
																																																																																			      mySwitch.switchOn(4, 1);
																																																																																			          mySwitch.switchOn(4, 2);
																																																																																				      mySwitch.switchOn(4, 3);
																																																																																				          mySwitch.switchOn(4, 4);
																																																																																					      
																																																																																					          //affichage   
																																																																																						     Serial.println("prises 1, 2, 3 et 4 allumees");
																																																																																						         lcd.clear();
																																																																																							     lcd.setCursor(0, 0);
																																																																																							         lcd.print("1,2,3et4");
																																																																																								     lcd.setCursor(0, 1);
																																																																																								         lcd.print("allumees");
																																																																																									     i++;
																																																																																									        }

																																																																																										///////OFF  
																																																																																										    if (inBT == 'e') 
																																																																																										        {
																																																																																											      mySwitch.switchOff(4, 1);
																																																																																											          //affichage 
																																																																																												     Serial.println("prise 1 eteinte");  
																																																																																												         lcd.clear();
																																																																																													     lcd.setCursor(0, 0);
																																																																																													         lcd.print("prise 1");
																																																																																														     lcd.setCursor(0, 1);
																																																																																														         lcd.print("eteinte");
																																																																																															     }
																																																																																															         
																																																																																																     if (inBT == 'f') 
																																																																																																         {
																																																																																																	       mySwitch.switchOff(4, 2);
																																																																																																	           //affichage   
																																																																																																		      Serial.println("prise 2 eteinte");
																																																																																																		          lcd.clear();
																																																																																																			      lcd.setCursor(0, 0);
																																																																																																			          lcd.print("prise 2");
																																																																																																				      lcd.setCursor(0, 1);
																																																																																																				          lcd.print("eteinte");
																																																																																																					      }
																																																																																																					          
																																																																																																						      if (inBT == 'g') 
																																																																																																						          {
																																																																																																							        mySwitch.switchOff(4, 3);
																																																																																																								    //affichage 
																																																																																																								       Serial.println("prise 3 eteinte");  
																																																																																																								           lcd.clear();
																																																																																																									       lcd.setCursor(0, 0);
																																																																																																									           lcd.print("prise 3");
																																																																																																										       lcd.setCursor(0, 1);
																																																																																																										           lcd.print("eteinte");
																																																																																																											       }
																																																																																																											           
																																																																																																												       if (inBT == 'h') 
																																																																																																												           {
																																																																																																													         mySwitch.switchOff(4, 4);
																																																																																																														     //affichage
																																																																																																														        Serial.println("prise 4 eteinte");   
																																																																																																															    lcd.clear();
																																																																																																															        lcd.setCursor(0, 0);
																																																																																																																    lcd.print("prise 4");
																																																																																																																        lcd.setCursor(0, 1);
																																																																																																																	    lcd.print("eteinte");
																																																																																																																	        } 
																																																																																																																		    
																																																																																																																		        if (inBT == 'D') 
																																																																																																																			    {
																																																																																																																			          mySwitch.switchOff(4, 1);
																																																																																																																				        mySwitch.switchOff(4, 2);
																																																																																																																					      mySwitch.switchOff(4, 3);
																																																																																																																					            mySwitch.switchOff(4, 4);  
																																																																																																																						          
																																																																																																																							      //affichage  
																																																																																																																							         Serial.println("prises 1, 2, 3 et 4 eteintes"); 
																																																																																																																								     lcd.clear();
																																																																																																																								         lcd.setCursor(0, 0);
																																																																																																																									     lcd.print("1,2,3et4");
																																																																																																																									         lcd.setCursor(0, 1);
																																																																																																																										     lcd.print("eteintes");
																																																																																																																										           i++;
																																																																																																																											       }
																																																																																																																											        
																																																																																																																												 ///// test
																																																																																																																												  if (inter == HIGH)
																																																																																																																												   {digitalWrite(LAMP_TEST, HIGH);}
																																																																																																																												    
																																																																																																																												     
																																																																																																																												      if (inBT == 'R') 
																																																																																																																												       {
																																																																																																																												          j=1;
																																																																																																																													      digitalWrite(LAMP_TEST, HIGH);
																																																																																																																													          //affichage 
																																																																																																																														      lcd.clear();
																																																																																																																														          lcd.setCursor(0, 0);
																																																																																																																															      lcd.print("  SON  ");
																																																																																																																															          lcd.setCursor(0, 1);
																																																																																																																																      lcd.print("  ON   ");
																																																																																																																																       }
																																																																																																																																        
																																																																																																																																	  if (inBT == 'L') 
																																																																																																																																	   {
																																																																																																																																	      j=0;
																																																																																																																																	          digitalWrite(LAMP_TEST, LOW);
																																																																																																																																		      //affichage   
																																																																																																																																		          lcd.clear();
																																																																																																																																			      lcd.setCursor(0, 0);
																																																																																																																																			          lcd.print("  SON   ");
																																																																																																																																				      lcd.setCursor(0, 1);
																																																																																																																																				          lcd.print("  OFF   ");
																																																																																																																																					   }
																																																																																																																																					     }
																																																																																																																																					       
																																																																																																																																					         ////////////clapclap  
																																																																																																																																						 if (j == 1)  
																																																																																																																																						   {
																																																																																																																																						       digitalWrite(LAMP_TEST, HIGH);
																																																																																																																																						         if (soundSensorReading >= THRESHOLD) { 
																																																																																																																																							     soundLength++;
																																																																																																																																							       } else {
																																																																																																																																							           if (soundLength > 1) {
																																																																																																																																								         previousSoundLength = soundLength;
																																																																																																																																									     }
																																																																																																																																									      
																																																																																																																																									          soundLength = 0;
																																																																																																																																										    }
																																																																																																																																										     
																																																																																																																																										       if (soundSampleLength == SOUND_SAMPLE_LENGTH) {
																																																																																																																																										           soundSampleLength = 0;
																																																																																																																																											    
																																																																																																																																											        if (previousSoundLength > 1) { 
																																																																																																																																												      clapDurationWindow = 0;
																																																																																																																																												            currentClaps++;
																																																																																																																																													     
																																																																																																																																													           if (currentClaps == CLAPS_FOR_TRIGGER) {
																																																																																																																																														           relayState = !relayState;
																																																																																																																																															    
																																																																																																																																															            if (millis()-lastLampRelayLoop >= 1000) 
																																																																																																																																																    {
																																																																																																																																																    { 
																																																																																																																																																    s++;
																																																																																																																																																     if ( (s % 2) == 0)            
																																																																																																																																																       { mySwitch.switchOff(4, 1);
																																																																																																																																																           mySwitch.switchOff(4, 2);
																																																																																																																																																	       mySwitch.switchOff(4, 3);
																																																																																																																																																	           mySwitch.switchOff(4, 4);
																																																																																																																																																		           //affichage   
																																																																																																																																																			       Serial.println("prises 1, 2, 3 et 4 eteintes");
																																																																																																																																																			           lcd.clear();
																																																																																																																																																				       lcd.setCursor(0, 0);
																																																																																																																																																				           lcd.print("1,2,3et4");
																																																																																																																																																					       lcd.setCursor(0, 1);
																																																																																																																																																					           lcd.print("eteintes");
																																																																																																																																																						       i++;
																																																																																																																																																						         }
																																																																																																																																																							    else           
																																																																																																																																																							      { mySwitch.switchOn(4, 1);
																																																																																																																																																							          mySwitch.switchOn(4, 2);
																																																																																																																																																								      mySwitch.switchOn(4, 3);
																																																																																																																																																								          mySwitch.switchOn(4, 4);
																																																																																																																																																									          //affichage   
																																																																																																																																																										      Serial.println("prises 1, 2, 3 et 4 allumees");
																																																																																																																																																										          lcd.clear();
																																																																																																																																																											      lcd.setCursor(0, 0);
																																																																																																																																																											          lcd.print("1,2,3et4");
																																																																																																																																																												      lcd.setCursor(0, 1);
																																																																																																																																																												          lcd.print("allumees");
																																																																																																																																																													      i++;
																																																																																																																																																													        }
																																																																																																																																																														}    

																																																																																																																																																														   
																																																																																																																																																														             lastLampRelayLoop = millis();
																																																																																																																																																															             }
																																																																																																																																																																           }
																																																																																																																																																																	    
																																																																																																																																																																	          previousSoundLength = 0;
																																																																																																																																																																		      }
																																																																																																																																																																		        }
																																																																																																																																																																			 
																																																																																																																																																																			   if (clapDurationWindow >= CLAP_DURATION_WINDOW) {
																																																																																																																																																																			       currentClaps = 0; 
																																																																																																																																																																			         }
																																																																																																																																																																				  
																																																																																																																																																																				    if (clapDurationWindow <= CLAP_DURATION_WINDOW) {
																																																																																																																																																																				        clapDurationWindow++;
																																																																																																																																																																					  }
																																																																																																																																																																					   
																																																																																																																																																																					     if (soundSampleLength < SOUND_SAMPLE_LENGTH) {
																																																																																																																																																																					         soundSampleLength++; 
																																																																																																																																																																						   }
																																																																																																																																																																						     }

																																																																																																																																																																						     }
