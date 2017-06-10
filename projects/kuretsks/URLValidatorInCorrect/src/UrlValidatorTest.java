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
 * 
 */

/*	CS362-400, Spring 2017
 * 	Susan Kuretski, Yu Ju Chang, Soo-min Yoo
 * 	Final Project Part B
 */


import junit.framework.TestCase;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = true;		//To print statuses of partition tests and num failed & total for isValid()
   private boolean printIsValid = false;	//To print all the failures for isValid() test

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
			   "https://99.99.99.99:3000", "http://www.amazon.com.org","http://www.amazon.com/link?query=false"};
	   String [] manualUrlFalse = {"http:/www.amazon.com", "https:/www.amazon.com", "https://///www.google.com",
			   "http:www.amazon.com", "ssh:/something.com", "http//amazon.com", "www.amazon.com", "amazon", "11.11.11.11",
			   "http://www.amazon.com?query=true","http://72.21.215.90:65535",
			   "http://amazon", "http://www.amazo n.com", "http://www.amazon.com/l i n k", "http www.amazon.com",
			   "http", "http://", "http://localhost"};
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
	   if(printStatus){
		   for(int i = 0; i < trueSchemes.length; i++){
			   boolean success = true;
			   try{
				   assertTrue(urlVal.isValidScheme(trueSchemes[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", trueSchemes[i], "\tCaught exception: assertion fail.");
				   success = false;
			   } finally{
				   if(success){
					   System.out.printf(formatSuccess, "\tPASS: ", trueSchemes[i]);
				   }
			   }	   
		   }
		   for(int i = 0; i < falseSchemes.length; i++){
			   boolean success = true;
			   try{
				   assertFalse(urlVal.isValidScheme(falseSchemes[i]));
				   success = true;
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", falseSchemes[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally {
				   if(success)
					   System.out.printf(formatSuccess, "\tPASS: ", falseSchemes[i]);
			   }
		   }
	   }
	   for(int i = 0; i < trueSchemes.length; i++){
		   assertTrue(urlVal.isValidScheme(trueSchemes[i]));
	   }
	   for(int i = 0; i < trueSchemes.length; i++){
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
	   if(printStatus){
		   for(int i = 0; i < trueAuthor.length; i++){
			   boolean success = true;
			   try{
				   assertTrue(urlVal.isValidAuthority(trueAuthor[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", trueAuthor[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally{
				   if(success){
					   System.out.printf(formatSuccess, "\tPASS: ", trueAuthor[i]);
				   }
			   }	   
		   }
		   for(int i = 0; i < falseAuthor.length; i++){
			   boolean success = true;
			   try{
				   assertFalse(urlVal.isValidAuthority(falseAuthor[i]));
				   success = true;
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", falseAuthor[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally {
				   if(success)
					   System.out.printf(formatSuccess,"\tPASS: ", falseAuthor[i]);
			   }
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
	   if(printStatus){
		   for(int i = 0; i < truePorts.length; i++){
			   boolean success = true;
			   try{
				   assertTrue(urlVal.isValid(truePorts[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", truePorts[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally{
				   if(success){
					   System.out.printf(formatSuccess, "\tPASS: ", truePorts[i]);
				   }
			   }	   
		   }
		   for(int i = 0; i < falsePorts.length; i++){
			   boolean success = true;
			   try{
				   assertFalse(urlVal.isValid(falsePorts[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", falsePorts[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally {
				   if(success)
					   System.out.printf(formatSuccess,"\tPASS: ", falsePorts[i]);
			   }
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
	   if(printStatus)System.out.println("\n--------------------------- Testing Fourth Partition of PATH ----------------------------\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] truePaths = {"/folder1", "/_32", "/()", "/folder1/folder2/folder3/folder4/folder5"};
	   String[] falsePaths = {"//path", "/../", null, " ", "/path///", "path"};
	   String formatError = "%-20s%s%s%n";
	   String formatSuccess = "%-20s%s%n";
	   if(printStatus){
		   for(int i = 0; i < truePaths.length; i++){
			   boolean success = true;
			   try{
				   assertTrue(urlVal.isValidPath(truePaths[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", truePaths[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally{
				   if(success){
					   System.out.printf(formatSuccess, "\tPASS: ", truePaths[i]);
				   }
			   }	   
		   }
		   for(int i = 0; i < falsePaths.length; i++){
			   boolean success = true;
			   try{
				   assertFalse(urlVal.isValidPath(falsePaths[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", falsePaths[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally {
				   if(success)
					   System.out.printf(formatSuccess,"\tPASS: ", falsePaths[i]);
			   }
		   }
	   }
	   // ** These must run again to trigger pass/fail in JUnit since the errors are caught and handled above.
	   for(int i = 0; i < truePaths.length; i++){
		   assertTrue(urlVal.isValidAuthority(truePaths[i]));
	   }
	   for(int i = 0; i < falsePaths.length; i++){
		   assertFalse(urlVal.isValidAuthority(falsePaths[i]));
	   }
   }
   
   //Fifth Partition Test: tests query parameters i.e. ?key=value
   public void testYourFifthPartition(){
	   if(printStatus)System.out.println("\n--------------------------- Testing Fifth Partition of QUERY ----------------------------\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String[] trueQuery = {"?color=blue", "?color=blue&size=small", "?color=blue&size=sm&material=cotton"};
	   String[] falseQuery = {"color=blue", "??", "??mode=1", "color", "#value"};
	   String formatError = "%-20s%s%s%n";
	   String formatSuccess = "%-20s%s%n";
	   if(printStatus){
		   for(int i = 0; i < trueQuery.length; i++){
			   boolean success = true;
			   try{
				   assertTrue(urlVal.isValidQuery(trueQuery[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", trueQuery[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally{
				   if(success){
					   System.out.printf(formatSuccess, "\tPASS: ", trueQuery[i]);
				   }
			   }	   
		   }
		   for(int i = 0; i < falseQuery.length; i++){
			   boolean success = true;
			   try{
				   assertFalse(urlVal.isValidQuery(falseQuery[i]));
			   } catch(AssertionError e){
				   System.out.printf(formatError, "\tFAIL:", falseQuery[i], "\tERROR: Caught exception - assertion fail");
				   success = false;
			   } finally {
				   if(success)
					   System.out.printf(formatSuccess,"\tPASS: ", falseQuery[i]);
			   }
		   } 
	   }
	   // ** These must run again to trigger pass/fail in JUnit since the errors are caught and handled above.
	   for(int i = 0; i < trueQuery.length; i++){
		   assertTrue(urlVal.isValidAuthority(trueQuery[i]));
	   }
	   for(int i = 0; i < falseQuery.length; i++){
		   assertFalse(urlVal.isValidAuthority(falseQuery[i]));
	   }
   }
   
   public void testIsValid()
   {
	   if(printStatus)System.out.println("\n--------------------------- Testing isValid Combinations --------------------------------\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   int totalTest = 0;
	   int totalFailed = 0;
	   
	   String formatError = "%-10s%-80s%s%s%s%s%n";
	   for(int i = 0; i < testScheme.length; i++)
	   {   
		   // Scheme
		   for(int j = 0; j < testAuthority.length; j++)
		   {
			   // Scheme + Authority	   
			   for(int k = 0; k < testPort.length; k++)
			   {
				   // Scheme + Authority + Port
				   for(int l = 0; l < testPath.length; l++)
				   {
					   // Scheme + Authority + Port + Path 
					   for(int m = 0; m < testQuery.length; m++)
					   {
						   // Scheme + Authority + Port + Path + Query
						   StringBuffer testUrl = new StringBuffer();		// This will clear the StringBuffer on each pass
						   boolean expected = true;
						   testUrl.append(testScheme[i].item)
						   		.append(testAuthority[j].item)
						   		.append(testPort[k].item)
						   		.append(testPath[l].item)
						   		.append(testQuery[m].item);
						   expected = testScheme[i].valid && testAuthority[j].valid && testPort[k].valid && testPath[l].valid && testQuery[m].valid; 						
						   String url = testUrl.toString();
						   boolean result = true;
						   try{
							   result = urlVal.isValid(url);
							   assertEquals(expected, result);
						   } catch(AssertionError e){
							   if(printStatus && printIsValid){
								   System.out.printf(formatError, "FAIL:", testUrl.toString(), "Expected: ", expected, "\tResult: ", result);
							   }
							   totalFailed++;
						   } finally{
							   totalTest ++;
						   }	 
					   } // Query for-loop
				   } // Path for-loop
			   } // Port for-loop
		   } // Authority for-loop
	   } // Scheme for-loop
	   if(printStatus)System.out.println(String.format("\nTotal URLs Tested: %d", totalTest));
 	   if(printStatus)System.out.println(String.format("Total Failed URLs: %d", totalFailed));
 	   
 	   // This will flag JUnit Failure
 	   if(totalFailed > 0)
 		   fail("Assertion fail");
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
       new ResultPair("http", false)
   };
   
   ResultPair [] testAuthority = {
	   new ResultPair("1.1.1.1", true),
	   new ResultPair("256.256.256.256", false),
	   new ResultPair("www.google.com", true),
	   new ResultPair("ww.google.com", false),
	   new ResultPair("oregonstate.edu", true),
	   new ResultPair("google.c", false),
	   new ResultPair("0.0.0.0", true),
	   new ResultPair("255.255.255.255", true),
	   new ResultPair("go.com", true),
	   new ResultPair("google.comm", false)
   };
   
   ResultPair [] testPort = {
	   new ResultPair("", true),
	   new ResultPair("80", false),
	   new ResultPair(":1", true),
	   new ResultPair(":80", true),
	   new ResultPair(":3000", true),
	   new ResultPair(":0", true),
	   new ResultPair(":49f", false),
	   new ResultPair("-1", false),
	   new ResultPair(":65537", false)
   };
   
   ResultPair [] testPath = {
       new ResultPair("", true),
	   new ResultPair("/folder1", true),
	   new ResultPair("/folder1/folder2/folder3/folder4", true),
	   new ResultPair("//folder1", false),
	   new ResultPair("folder", false),
	   new ResultPair("/something$", true),
	   new ResultPair("/..", false),
	   new ResultPair("/2334", true),
	   new ResultPair("/folder1//folder2", false)
   };
   
   ResultPair [] testQuery = {
	   new ResultPair("?color=red", true),
	   new ResultPair("", true),
	   new ResultPair("?color=red&size=small", true),
	   new ResultPair("color=red", false),
	   new ResultPair("?size=1", true)
   };
}
