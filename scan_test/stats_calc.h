////  print inpud file and generated byte sizes
//    Serial.println("\n");  Serial.print(inCount);  Serial.print(" Bytes in / ");
//    Serial.print(outCount);  Serial.print("Bytes out, in ");
//    //  print total execution time in microseconds 0.000_001s
//    Serial.print(time_us);  Serial.println(" us.");
//
//    //  calculate and print SCANNER average speed
//    float f;
//    
//    //  of input stream
//    f = (float)(inCount * 8L);  f /= (float)time_us;  Serial.print(f);  Serial.print(" Mib/s  /  ");
//    f = (float)inCount;  f *= 1000.0;  f /= (float)time_us;  Serial.print(f);  Serial.println(" KByte/s  in");
//    
//    //  of output stream
//    f = (float)(outCount * 8L); f /= (float)time_us;  Serial.print(f);  Serial.print(" Mib/s  /  ");
//    f = (float)outCount;  f *= 1000.0;  f /= (float)time_us;  Serial.print(f);  Serial.println(" KByte/s  out\n");
//
//    //  reset buffer index,  
//    indx = 0;  inCount = 0; outCount = 0;  time_us = 0;


//inline void lx_print_code( char code ) {
//  switch (code) {
//    case _sID_:  Serial.print("i");  break;
//    case _sLC_:  Serial.print("l");  break;
//    case _sUC_:  Serial.print("u");  break;
//    case _sWS_:  Serial.print("");  break;
//    case _sNL_:  Serial.println("");  break;
//    case _sSE_:  Serial.print("");  break;
//    case _sNUM_:  Serial.print("n");  break;
//
//    case _sEQ_:  Serial.print("=");  break;
//    case _sDOT_:  Serial.print(".");  break;
//    case _sCM_:  Serial.print(",");  break;
//    
//    case _sSTR_:  break;
//    case _sSTT_:  break;
//    case _sSTR_END_:  Serial.print("STR");  break;
//    case _sBSL_:  Serial.print("BSL");  break;
//
//    case _sBWO_:  Serial.print("");  break;
//    case _sMTH_:  Serial.print("");  break;
//    case _sCMP_:  Serial.print("");  break;
//    case _sQST_:  Serial.print("?");  break;
//    case _sCOL_:  Serial.print(":");  break;
//    case _sSYM_:  Serial.print("s");  break;
//    case _sEXT_:  Serial.print("EXT ");  break;
//    
//      
//    
//    case _sSTART_:  Serial.print("\n__START__\n");  break;
//    case _sSTOP_:  Serial.print("\n__STOP__\n");  break;
//    case _sCMN_:  Serial.print("CMN");  break;
//    case _sDE_:  Serial.print("d");  break;
//    default :  Serial.print("UK:");  Serial.print((byte)code);  Serial.print(" ");  break;
//  }
//  
//  return;
//}


//  SCAN function code to string (for testing and debuggin purposes)
// inline void lx_print_code( char c );