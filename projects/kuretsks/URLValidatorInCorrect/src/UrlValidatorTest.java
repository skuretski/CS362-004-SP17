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

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void printManualTest(String url, UrlValidator urlVal){
	   String format = "%-60s%s%n";
	   System.out.printf(format, url, urlVal.isValid(url));
   }
   
   public void testManualTest()
   {
	   System.out.println("--------------------------- Manual Tests --------------------------");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("Should be true\n");
	   printManualTest("http://www.amazon.com", urlVal);
	   printManualTest("https://www.amazon.com", urlVal);
	   printManualTest("http://www.amazon.com/folder1", urlVal);
	   printManualTest("https:///www.amazon.com/folder2", urlVal);
	   printManualTest("http://www.amazon.com:80", urlVal);
	   printManualTest("https://www.amazon.com:80", urlVal);
	   printManualTest("http://www.amazon.en.com", urlVal);
	   printManualTest("http://www.amazon.com/action=something", urlVal);
	   printManualTest("ssh://something.com", urlVal);
	   printManualTest("ftp://something.edu", urlVal);
	   printManualTest("http://something.org", urlVal);
	   printManualTest("http://www.amazon.com/value?color=blue", urlVal);
	   printManualTest("http://something.com:1000", urlVal);
	   printManualTest("http://11.11.11.11", urlVal);
	   printManualTest("http://11.11.11.11:80", urlVal);
	   
	   
	   
	   System.out.println("\nShould be false\n");
	   printManualTest("http:/www.amazon.com", urlVal);
	   printManualTest("https:/www.amazon.com", urlVal);
	   printManualTest("https://///www.google.com", urlVal);
	   printManualTest("http:www.amazon.com", urlVal);
	   printManualTest("ssh:/something.com", urlVal);
	   printManualTest("http//www.amazon.com", urlVal);
	   printManualTest("www.amazon.com", urlVal);
	   printManualTest("amazon", urlVal);
	   printManualTest("11.11.11.11", urlVal);
	   
   }
   
   //First Partition Test: tests scheme i.e. http, https, etc.
   public void testYourFirstPartition()
   {
	   System.out.println("--------------------------- Testing First Partition of Scheme --------------------------------");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("http://www.yahoo.com"));
	   assertTrue(urlVal.isValid("https://www.yahoo.com"));
	   assertTrue(urlVal.isValid("http://255.255.255.255"));
	   assertTrue(urlVal.isValid("ftp://11.11.11.11"));
	   assertTrue(urlVal.isValid("sftp://11.11.11.11"));
   }
   
   //Second Partition Test: tests authority i.e. google.com, www.something.com, 12.12.12.12
   public void testYourSecondPartition(){
	   
   }
   
   //Third Partition Test: tests port number i.e. :80, :3000
   public void testYourThirdPartition(){
	   
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
       new ResultPair("http", false)

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
