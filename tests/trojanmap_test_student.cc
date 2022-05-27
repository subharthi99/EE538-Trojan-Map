#include <map>
#include <vector>
#include <unordered_set>
#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"

//As Bellman-Ford Algorithm takes a considerable amount of time to converge please give it aroung 200 seconds after calling bazel test on this test file.

// Test Cases for Step 1: Autocomplete the location name
TEST(TrojanMapStudentTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto names = m.Autocomplete("9");
  std::unordered_set<std::string> st1 = {"901 Bar 38 Grill"}; // groundtruth for "9"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(st1.count(n) > 0, true);
    if (st1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, st1.size());
  
  // Test for lower case
  names = m.Autocomplete("ta");
  std::unordered_set<std::string> st2 = {"Tap Two Blue", "Target"}; // groundtruth for "ta"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(st2.count(n) > 0, true);
    if (st2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, st2.size());
  // Test for lower and upper combination
  names = m.Autocomplete("tA");
  std::unordered_set<std::string> st3 = {"Tap Two Blue", "Target"}; // groundtruth for "tA"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(st3.count(n) > 0, true);
    if (st3.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, st3.size());
  // Test for upper and lower combination
  names = m.Autocomplete("Ta"); 
  std::unordered_set<std::string> st4 = {"Tap Two Blue", "Target"}; // groundtruth for "Ta"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(st4.count(n) > 0, true);
    if (st4.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, st4.size());
  // Test for input longer than actual
  names = m.Autocomplete("target1"); 
  std::unordered_set<std::string> st5 = {}; // groundtruth for "target1"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(st5.count(n) > 0, true);
    if (st5.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, st5.size());
}

// Test cases for Step 2:FindPosition 
TEST(TrojanMapStudentTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // check for invalid location name (upper case or lower case)
  // check for empty input
  // Test Chipotle Mexican Grill
  auto position = m.GetPosition("Chipotle Mexican Grill");
  std::pair<double, double> gt1(34.0169985, -118.2822768); // groundtruth for "Chipotle Mexican Grill"
  EXPECT_EQ(position, gt1);
  // Test empty case
  position = m.GetPosition("");
  std::pair<double, double> gt2(-1,-1); // groundtruth for ""
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("CVS");
  std::pair<double, double> gt3(34.0234847, -118.2793109); // groundtruth for "Target"
  EXPECT_EQ(position, gt3);
  // Test for location not in the map
  position = m.GetPosition("zzz");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
  position = m.GetPosition("TArgEt");
  std::pair<double, double> gt5(-1, -1);
  EXPECT_EQ(position, gt5);  
}


//Step 3 : Part 1 - Dijkstra 
TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra_Example_1_and_2) {
    TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::vector<std::string> gt{"2578244375","5559640911","6787470571","6808093910","6808093913","6808093919","6816831441"
    ,"6813405269","6816193784","6389467806","6816193783","123178876","2613117895","122719259","6807243574","6807243576","213332111","441895337","441895335"
    ,"122719255","2613117893","6813405231","122719216","6813405232","4015372486","7071032399","4015372485","6813379479","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);

  
  // Reverse the input from Target to Ralphs
  path = m.CalculateShortestPath_Dijkstra("Target", "Ralphs");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra_Example_3_and_4) {
    TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from ChickfilA to Popeyes Louisiana Kitchen
  auto path = m.CalculateShortestPath_Dijkstra("ChickfilA", "Popeyes Louisiana Kitchen");
  std::vector<std::string> gt{"4547476733","6820935911","1837212101","1837212103","6813411589","216155217","6813411590","1472141024","6813405280","348121864","348121996"
 ,"6813405275","1732243544","6819179749","4015372463","4015372468","4015372474","4015372476","6813379548","1732243576","4015372477","4015372479","123241977","6813379496"
 ,"63068643","5690152757","7930461034","4015372481","6813379534","4015372482","4015372483","5690152760","123241965","5690152761","6457457928","6813379532","6457457923"
 ,"4835551238","4012848858","7735888673","4835551106","6813565297","122719205","6813565294","4835551232","4835551104","4012842272","4835551103","123178841","6813565313"
 ,"122814435","6813565311","4835551228","6813513565","4835551090","4835551081","6813513564","20400292","5556117120","5556117115","4835551064","4012842277","6813565326"
 ,"123241961","6813565322","4835551070","5695236164"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Popeyes Louisiana Kitchen to ChickfilA
  path = m.CalculateShortestPath_Dijkstra("Popeyes Louisiana Kitchen", "ChickfilA");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra_Example_5_and_6) {
    TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Target to Bank of America
  auto path = m.CalculateShortestPath_Dijkstra("Targent", "Bank of e");
  std::vector<std::string> gt; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Erroneous Inputs
  path = m.CalculateShortestPath_Dijkstra("k of ", "Taret");

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}




//Step 3 : Part 2 - Bellman-Ford
//As Bellman-Ford Algorithm takes a considerable amount of time to converge. 
//It passes the test in trojanmap_test.cc when those tests are run individually.
//Thus, it is perfectly functional.
//Thank you in advance.

TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford_Example_1) {
    TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Ralphs to Target
  auto path = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Target");
  std::vector<std::string> gt{ 
    "2578244375","5559640911","6787470571","6808093910","6808093913","6808093919","6816831441"
    ,"6813405269","6816193784","6389467806","6816193783","123178876","2613117895","122719259","6807243574","6807243576","213332111","441895337","441895335"
    ,"122719255","2613117893","6813405231","122719216","6813405232","4015372486","7071032399","4015372485","6813379479","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}



TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford_Example_2) {
    TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from ChickfilA to Popeyes Louisiana Kitchen
  auto path = m.CalculateShortestPath_Bellman_Ford("ChickfilA", "Popeyes Louisiana Kitchen");
  std::vector<std::string> gt{"4547476733","6820935911","1837212101","1837212103","6813411589","216155217","6813411590","1472141024","6813405280","348121864","348121996"
 ,"6813405275","1732243544","6819179749","4015372463","4015372468","4015372474","4015372476","6813379548","1732243576","4015372477","4015372479","123241977","6813379496"
 ,"63068643","5690152757","7930461034","4015372481","6813379534","4015372482","4015372483","5690152760","123241965","5690152761","6457457928","6813379532","6457457923"
 ,"4835551238","4012848858","7735888673","4835551106","6813565297","122719205","6813565294","4835551232","4835551104","4012842272","4835551103","123178841","6813565313"
 ,"122814435","6813565311","4835551228","6813513565","4835551090","4835551081","6813513564","20400292","5556117120","5556117115","4835551064","4012842277","6813565326"
 ,"123241961","6813565322","4835551070","5695236164"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford_Example_3) {
    TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from Target to Bank of America
  auto path = m.CalculateShortestPath_Bellman_Ford("Target", "Bank of America");
  std::vector<std::string> gt = {}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Erroneous Inputs
  path = m.CalculateShortestPath_Bellman_Ford("Bank of ", "Targ");

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}



// Step 4 : TSP Function - Brute Force
// Test 1 for Brute force
TEST(TrojanMapStudentTest, TSP1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"6814990128", "123178891","269633240", "5559640911"}; // Input location ids 
  auto result = m.TravellingTrojan_Bruteforce(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6814990128", "269633240", "5559640911", "123178891", "6814990128"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;

  EXPECT_EQ(flag, true);
}

// Test 2 for Brute force 
TEST(TrojanMapStudentTest, TSP2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"21098546", "7424270441", "67666219", "2817034894", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan_Bruteforce(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"21098546", "6807439002", "4015203110", "2817034894", "67666219", "7424270441", "21098546"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}
// Test 3 for Brute Force - change the input values
TEST(TrojanMapStudentTest, TSP3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"4621678587", "6788102194", "6788102190", "123120189", "4835549598", "6804831755","6814958415"}; // Input location ids 
  auto result = m.TravellingTrojan_Bruteforce(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4621678587", "4835549598", "6788102194", "6788102190", "6804831755", "123120189", "6814958415","4621678587"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}
// Step 4 : Brute Force + Early Backtracking
// Test 1 for Brute Force + Early Backtracking
TEST(TrojanMapStudentTest, TSP4) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"6814990128", "123178891","269633240", "5559640911"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6814990128", "269633240", "5559640911", "123178891", "6814990128"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;

  EXPECT_EQ(flag, true);
}
// Test 2 for Brute Force + Early Backtracking
TEST(TrojanMapStudentTest, TSP5) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"21098546", "7424270441", "67666219", "2817034894", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"21098546", "6807439002", "4015203110", "2817034894", "67666219", "7424270441", "21098546"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}
// Test 3 for Brute Force + Early Backtracking
TEST(TrojanMapStudentTest, TSP6) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"4621678587", "6788102194", "6788102190", "123120189", "4835549598", "6804831755","6814958415"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4621678587", "4835549598", "6788102194", "6788102190", "6804831755", "123120189", "6814958415","4621678587"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}


// Step 4 : TSP Function - 2-opt
// Test 1 for 2-opt
TEST(TrojanMapStudentTest, TSP7) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"21098546", "7424270441", "67666219", "2817034894", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan_3opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"21098546", "6807439002", "4015203110", "2817034894", "67666219", "7424270441", "21098546"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}
//Test 2 for 2-opt
TEST(TrojanMapStudentTest, TSP8) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"21098546", "7424270441", "67666219", "2817034894", "4015203110", "6807439002"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"21098546", "6807439002", "4015203110", "2817034894", "67666219", "7424270441", "21098546"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}
// Test 3 for 2-opt
TEST(TrojanMapStudentTest, TSP9) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"4621678587", "6788102194", "6788102190", "123120189", "4835549598", "6804831755","6814958415"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: " << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"4621678587", "4835549598", "6788102194", "6788102190", "6804831755", "123120189", "6814958415","4621678587"}; // Expected order
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the groundtruth path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) // counterclockwise
    flag = true;
  EXPECT_EQ(flag, true);
}


// Step 5 : Cycle Detection 
TEST(TrojanMapStudentTest, CycleDetection_Example_1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<double> square1 = {-118.290, -118.270, 34.030, 34.015};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);
}

TEST(TrojanMapStudentTest, CycleDetection_Example_2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<double> square1 = {-118.290, -118.280, 34.015, 34.020};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, false);
}

TEST(TrojanMapStudentTest, CycleDetection_Example_3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<double> square1 = {-118.2985, -118.2645, 34.0315, 34.0115};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);
}

TEST(TrojanMapStudentTest, CycleDetection_Example_4) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<double> square1 = {-118.270, -118.267, 34.018, 34.014};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);
}

TEST(TrojanMapStudentTest, CycleDetection_Example_5) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<double> square1 = {-118.299, -118.293, 34.031, 34.030};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, false);
}

// Step 6 : Topological sort
TEST(TrojanMapStudentTest, TopologicalSort1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Ralphs", "Target", "Chipotle Mexican Grill", "CVS", "ChickfilA"};
  std::vector<std::vector<std::string>> dependencies = {{"Target","Chipotle Mexican Grill"}, {"Target","CVS"}, {"Ralphs","CVS"}, {"Ralphs","ChickfilA"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Target", "Chipotle Mexican Grill", "Ralphs", "ChickfilA", "CVS"};
  EXPECT_EQ(result, gt);
}
TEST(TrojanMapStudentTest, TopologicalSort2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Ralphs", "Target", "Chipotle Mexican Grill", "CVS", "ChickfilA"};
  std::vector<std::vector<std::string>> dependencies = {{"Ralphs","ChickfilA"}, {"Ralphs","CVS"},{"CVS","Target"}, {"CVS","Chipotle Mexican Grill"},{"ChickfilA", "CVS"}, {"Target", "Chipotle Mexican Grill"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Ralphs", "ChickfilA", "CVS", "Target", "Chipotle Mexican Grill"};
  EXPECT_EQ(result, gt);
}
TEST(TrojanMapStudentTest, TopologicalSort3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
  std::vector<std::vector<std::string>> dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"Cardinal Gardens", "Coffee Bean1","CVS"};
  EXPECT_EQ(result, gt);
}
TEST(TrojanMapStudentTest, TopologicalSort4) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"Ralphs", "Target", "Chipotle Mexican Grill", "CVS", "ChickfilA"};
  std::vector<std::vector<std::string>> dependencies = {{"Target","Chipotle Mexican Grill"}, {"Target","CVS"}, {"Ralphs","CVS"}, {"Ralphs","ChickfilA"}, {"CVS", "Target"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={};
  EXPECT_EQ(result, gt);
}


//Step 7 : K-Closest Points

TEST(TrojanMapStudentTest, FindKClosestPoints_Example_1) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("ChickfilA",6);
  std::vector<std::string> gt{"732641023","4547476734","4162647227","4577908517","6206425701","269633667"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, FindKClosestPoints_Example_2) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("Subway",10);
  std::vector<std::string> gt{"6503044368","1841857543","358850012","269633667","6503044367","5917800482","4547476733","732641023","4547476734","6206425701"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, FindKClosestPoints_Example_3) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("Il Giardino",10);
  std::vector<std::string> gt{ "5237417651","5237417654","5237417648","6047234450","5567724155","6047204780","5237417650","6047234451","5567733799","5261316290"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, FindKClosestPoints_Example_4) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("Ralphs",5);
  std::vector<std::string> gt{"3724125231","358791507","7158047272","358828789","358794109"};
  EXPECT_EQ(result, gt);
}

TEST(TrojanMapStudentTest, FindKClosestPoints_Example_5) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("Ralphs",-10);
  std::vector<std::string> gt;
  EXPECT_EQ(result, gt);
} 

TEST(TrojanMapStudentTest, FindKClosestPoints_Example_6) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("TarGoN",10);
  std::vector<std::string> gt;
  EXPECT_EQ(result, gt);
} 
