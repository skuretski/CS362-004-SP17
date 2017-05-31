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
	   
	   System.out.println("\nShould be false\n");
	   printManualTest("http:/www.amazon.com", urlVal);
	   printManualTest("https:/www.amazon.com", urlVal);
	   printManualTest("https://///www.google.com", urlVal);
	   printManualTest("http:www.amazon.com", urlVal);
	   printManualTest("ssh:/something.com", urlVal);
	   printManualTest("http//www.amazon.com", urlVal);
	   printManualTest("www.amazon.com", urlVal);
	   printManualTest("amazon", urlVal);
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
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
   

}
