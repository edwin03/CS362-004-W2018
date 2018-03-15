
import junit.framework.TestCase;


public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
       super(testName);
   }

   public void testManualTest()
   {
       //You can use this function to implement your manual testing

   }


   public void testYourFirstPartition()
   {
       //You can use this function to implement your First Partition testing

   }

   public void testYourSecondPartition()
   {
       //You can use this function to implement your Second Partition testing

   }
   //You need to create more test cases for your Partitions if you need to

   public void testIsValid()
   {
       UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       int count = 0;
       String url;
       boolean expected, result;

       for (ResultPair scheme: testUrlParts[0]) {
           for (ResultPair authority: testUrlParts[1]) {
               for (ResultPair port: testUrlParts[2]) {
                   for (ResultPair path: testUrlParts[3]) {
                       for (ResultPair query: testUrlParts[4]) {
                           count++;

                           url = String.join("", scheme.item, authority.item, port.item, path.item, query.item);
                           result = validator.isValid(url);
                           expected = scheme.valid & authority.valid & port.valid & path.valid & query.valid;

                           System.out.println(url);
                           // System.out.println(count);

                           assertEquals(url, expected, result);
                       }
                   }
               }
           }
       }

   }

   //-------------------- Test data for creating a composite URL
   ResultPair[] testUrlScheme = { new ResultPair("http://", true),
                                  new ResultPair("ftp://", true),
                                  new ResultPair("h3t://", true),
                                  new ResultPair("3ht://", false),
                                  new ResultPair("http:/", false),
                                  new ResultPair("http:", false),
                                  new ResultPair("http/", false),
                                  new ResultPair("://", false) };

   ResultPair[] testUrlAuthority = { new ResultPair("www.google.com", true),
                                     new ResultPair("go.com", true),
                                     new ResultPair("go.au", true),
                                     new ResultPair("0.0.0.0", true),
                                     new ResultPair("255.255.255.255", true),
                                     new ResultPair("256.256.256.256", false),
                                     new ResultPair("255.com", true),
                                     new ResultPair("1.2.3.4.5", false),
                                     new ResultPair("1.2.3.4.", false),
                                     new ResultPair("1.2.3", false),
                                     new ResultPair(".1.2.3.4", false),
                                     new ResultPair("go.a", false),
                                     new ResultPair("go.a1a", false),
                                     new ResultPair("go.1aa", false),
                                     new ResultPair("aaa.", false),
                                     new ResultPair(".aaa", false),
                                     new ResultPair("aaa", false),
                                     new ResultPair("", false) };

   ResultPair[] testUrlPort = { new ResultPair(":80", true),
                                new ResultPair(":65535", true),
                                new ResultPair(":0", true),
                                new ResultPair("", true),
                                new ResultPair(":-1", false),
                                new ResultPair(":65636",false),
                                new ResultPair(":65a", false) };

   ResultPair[] testPath = { new ResultPair("/test1", true),
                             new ResultPair("/t123", true),
                             new ResultPair("/$23", true),
                             new ResultPair("/..", false),
                             new ResultPair("/../", false),
                             new ResultPair("/test1/", true),
                             new ResultPair("", true),
                             new ResultPair("/test1/file", true),
                             new ResultPair("/..//file", false),
                             new ResultPair("/test1//file", false) };

   ResultPair[] testUrlQuery = { new ResultPair("?action=view", true),
                                 new ResultPair("?action=edit&mode=up", true),
                                 new ResultPair("", true) };

   ResultPair[][] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};

}
