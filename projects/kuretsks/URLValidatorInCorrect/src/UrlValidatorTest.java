/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = true;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   // Helper functions
   public void printManualTest(String url, UrlValidator urlVal, int assertValue){
	   String format = "%-60s%s%n";
	   if(assertValue == 1){
		   System.out.printf(format, url, urlVal.isValid(url));
	   } else if(assertValue == 0){
		   System.out.printf(format, url, urlVal.isValid(url));
	   }
   }
   
   // Testing Functions
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] manualUrlTrue = {"http://www.amazon.com", "http://www.amazon.com", "http://www.amazon.com/folder1",
			   "https://www.amazon.com/folder2", "http://www.amazcon.en.com", "http://www.amazon.com/action=something",
			   "ssh://something.com", "ftp://something.edu", "http://something.org", "http://www.amazon.com/value?color=blue",
			   "http://something.com:1000", "http://11.11.11.11", "http://11.11.11.11:80", "https://255.255.255.255", 
			   "https://99.99.99.99:3000"};
	   String [] manualUrlFalse = {"http:/www.amazon.com", "https:/www.amazon.com", "https://///www.google.com",
			   "http:www.amazon.com", "ssh:/something.com", "http//amazon.com", "www.amazon.com", "amazon", "11.11.11.11"};
	   if(printStatus){
		   System.out.println("--------------------------- Manual Tests --------------------------");   
		   System.out.println("SHOULD BE TRUE\n");
		   for(int i = 0; i < manualUrlTrue.length; i++){
			   printManualTest(manualUrlTrue[i], urlVal, 1);
		   }
		   
		   System.out.println("\nSHOULD BE FALSE\n");
		   for(int i = 0; i < manualUrlFalse.length; i++){
			   printManualTest(manualUrlFalse[i], urlVal, 0);
		   }
	   }
	   // ** These must run again to trigger pass/fail in JUnit since assertions are not made in print functions.
	   for(int i = 0; i < manualUrlTrue.length; i++){
		   assertTrue(urlVal.isValid(manualUrlTrue[i]));
	   }
	   for(int i = 0; i < manualUrlFalse.length; i++){
		   assertFalse(urlVal.isValid(manualUrlFalse[i]));  
	   }	   
   }
   
   //First Partition Test: tests scheme i.e. http, https, etc.
   public void testYourFirstPartition()
   {
	   String formatError = "%-20s%s%s%n";
	   String formatSuccess = "%-20s%s%n";
	   if(printStatus)System.out.println("\n--------------------------- Testing First Partition of SCHEME --------------------------------\n");
	   UrlValidator urlVal = new UrlValidator(null);
	   String[] trueSchemes = {"http", "https", "ftp"};
	   String[] falseSchemes = {"http:", "https:", "http://", "ftp:/", "pop", "sftp:", "nfs", "sftp", null};
	   for(int i = 0; i < trueSchemes.length; i++){
		   boolean success = false;
		   try{
			   assertTrue(urlVal.isValidScheme(trueSchemes[i]));
			   success = true;
		   } catch(AssertionError e){
			   if(printStatus){
				   System.out.printf(formatError, "\tFAIL:", trueSchemes[i], "\tCaught exception: assertion fail.");
			   }	   
		   } finally{
			   if(success && printStatus){
				   System.out.printf(formatSuccess, "\tPASS: ", trueSchemes[i]);
			   }
		   }	   
	   }
	   for(int i = 0; i < falseSchemes.length; i++){
		   boolean success = false;
		   try{
			   assertFalse(urlVal.isValidScheme(falseSchemes[i]));
			   success = true;
		   } catch(AssertionError e){
			   if(printStatus){
				   System.out.printf(formatError, "\tFAIL:", falseSchemes[i], "\tERROR: Caught exception - assertion fail");
			   }	   
		   } finally {
			   if(success && printStatus)
				   System.out.printf(formatSuccess, "\tPASS: ", falseSchemes[i]);
		   }
	   }
	   // ** These must run again to trigger pass/fail in JUnit since the errors are caught and handled above.
	   for(int i = 0; i < trueSchemes.length; i++){
		   assertTrue(urlVal.isValidScheme(trueSchemes[i]));
	   }
	   for(int i = 0; i < falseSchemes.length; i++){
		   assertFalse(urlVal.isValidScheme(falseSchemes[i]));
	   }
   }
   
   //Second Partition Test: tests authority i.e. google.com, www.something.com, 12.12.12.12
   public void testYourSecondPartition(){
	   if(printStatus)System.out.println("\n--------------------------- Testing Second Partition of AUTHORITY ----------------------------\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] trueAuthor = {"www.google.com", "www.google.com", "www.oregonstate.edu", "1.1.1.1", "99.99.99.99", "255.255.255.255"};
	   String[] falseAuthor = {"google.c", "www.google.c", "1.1.1", ".com", "256.256.256.256"};
	   String formatError = "%-20s%s%s%n";
	   String formatSuccess = "%-20s%s%n";
	   for(int i = 0; i < trueAuthor.length; i++){
		   boolean success = false;
		   try{
			   assertTrue(urlVal.isValidAuthority(trueAuthor[i]));
			   success = true;
		   } catch(AssertionError e){
			   if(printStatus){
				   System.out.printf(formatError, "\tFAIL:", trueAuthor[i], "\tERROR: Caught exception - assertion fail");
			   }
			   
		   } finally{
			   if(success && printStatus){
				   System.out.printf(formatSuccess, "\tPASS: ", trueAuthor[i]);
			   }
		   }	   
	   }
	   for(int i = 0; i < falseAuthor.length; i++){
		   boolean success = false;
		   try{
			   assertFalse(urlVal.isValidAuthority(falseAuthor[i]));
			   success = true;
		   } catch(AssertionError e){
			   if(printStatus){
				   System.out.printf(formatError, "\tFAIL:", falseAuthor[i], "\tERROR: Caught exception - assertion fail");
			   }		   
		   } finally {
			   if(success && printStatus)
				   System.out.printf(formatSuccess,"\tPASS: ", falseAuthor[i]);
		   }
	   }
	   // ** These must run again to trigger pass/fail in JUnit since the errors are caught and handled above.
	   for(int i = 0; i < trueAuthor.length; i++){
		   assertTrue(urlVal.isValidAuthority(trueAuthor[i]));
	   }
	   for(int i = 0; i < falseAuthor.length; i++){
		   assertFalse(urlVal.isValidAuthority(falseAuthor[i]));
	   }
   }
   
   //Third Partition Test: tests port number i.e. :80, :3000
   public void testYourThirdPartition(){
	   if(printStatus)System.out.println("\n--------------------------- Testing Third Partition of PORT ----------------------------\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] truePorts = {"http://1.1.1.1:80", "http://1.1.1.1:1", "http://1.1.1.1:3000", "http://155.155.155.155:4000", "http://www.google.com:80"};
	   String[] falsePorts = {"http://1.1.1.1:20000", "http://99.99.99.99:-1", "http://255.255.255.255:null"};
	   String formatError = "%-20s%s%s%n";
	   String formatSuccess = "%-20s%s%n";
	   for(int i = 0; i < truePorts.length; i++){
		   boolean success = false;
		   try{
			   assertTrue(urlVal.isValid(truePorts[i]));
			   success = true;
		   } catch(AssertionError e){
			   if(printStatus){
				   System.out.printf(formatError, "\tFAIL:", truePorts[i], "\tERROR: Caught exception - assertion fail");
			   }
			   
		   } finally{
			   if(success && printStatus){
				   System.out.printf(formatSuccess, "\tPASS: ", truePorts[i]);
			   }
		   }	   
	   }
	   for(int i = 0; i < falsePorts.length; i++){
		   boolean success = false;
		   try{
			   assertFalse(urlVal.isValid(falsePorts[i]));
			   success = true;
		   } catch(AssertionError e){
			   if(printStatus){
				   System.out.printf(formatError, "\tFAIL:", falsePorts[i], "\tERROR: Caught exception - assertion fail");
			   }		   
		   } finally {
			   if(success && printStatus)
				   System.out.printf(formatSuccess,"\tPASS: ", falsePorts[i]);
		   }
	   }
	   // ** These must run again to trigger pass/fail in JUnit since the errors are caught and handled above.
	   for(int i = 0; i < truePorts.length; i++){
		   assertTrue(urlVal.isValidAuthority(truePorts[i]));
	   }
	   for(int i = 0; i < falsePorts.length; i++){
		   assertFalse(urlVal.isValidAuthority(falsePorts[i]));
	   }
   }
   
   //Fourth Partition Test: tests path i.e. /path1, /somepath/somemorepath
   public void testYourFourthPartition(){
	   
	   
   }
   
   //Fifth Partition Test: tests query parameters i.e. ?key=value
   public void testYourFifthPartition(){
	   
	   
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   ResultPair [] testScheme = {
       new ResultPair("http://", true),
       new ResultPair("https://", true),
       new ResultPair("ftp://", true),
       new ResultPair("//", false),
       new ResultPair(":/", false),
       new ResultPair("", true),
       new ResultPair("http", false),
       new ResultPair("sftp://", true)
   };
   
   ResultPair [] testAuthority = {
		 
   };
   
   ResultPair [] testPort = {
		   
   };
   
   ResultPair [] testPath = {
		   
   };
   
   ResultPair [] testQuery = {
		   
   };

}
