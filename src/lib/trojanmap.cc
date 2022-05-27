#include "trojanmap.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

#include <algorithm>
#include <fstream>
#include <locale>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
//#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <cctype>
#include <unordered_set>
#include <stack>
#include <chrono>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

//-----------------------------------------------------
// TODO (Students): You do not and should not change the following functions:
//-----------------------------------------------------

/**
 * PrintMenu: Create the menu
 * 
 */
void TrojanMap::PrintMenu() {

  std::string menu =
      "**************************************************************\n"
      "* Select the function you want to execute.                    \n"
      "* 1. Autocomplete                                             \n"
      "* 2. Find the position                                        \n"
      "* 3. CalculateShortestPath                                    \n"
      "* 4. Travelling salesman problem                              \n"
      "* 5. Cycle Detection                                          \n"
      "* 6. Topological Sort                                         \n"
      "* 7. Find K Closest Points                                    \n"
      "* 8. Exit                                                     \n"
      "**************************************************************\n";
  std::cout << menu << std::endl;
  std::string input;
  getline(std::cin, input);
  char number = input[0];
  switch (number)
  {
  case '1':
  {
    menu =
        "**************************************************************\n"
        "* 1. Autocomplete                                             \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a partial location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = Autocomplete(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '2':
  {
    menu =
        "**************************************************************\n"
        "* 2. Find the position                                        \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input a location:";
    std::cout << menu;
    getline(std::cin, input);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = GetPosition(input);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.first != -1) {
      std::cout << "Latitude: " << results.first
                << " Longitude: " << results.second << std::endl;
      PlotPoint(results.first, results.second);
    } else {
      std::cout << "No matched locations." << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '3':
  {
    menu =
        "**************************************************************\n"
        "* 3. CalculateShortestPath                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the start location:";
    std::cout << menu;
    std::string input1;
    getline(std::cin, input1);
    menu = "Please input the destination:";
    std::cout << menu;
    std::string input2;
    getline(std::cin, input2);
    auto start = std::chrono::high_resolution_clock::now();
    auto results = CalculateShortestPath_Dijkstra(input1, input2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.size() != 0) {
      for (auto x : results) std::cout << x << std::endl;
      std::cout << "The distance of the path is:" << CalculatePathLength(results) << " miles" << std::endl;
      PlotPath(results);
    } else {
      std::cout << "No route from the start point to the destination."
                << std::endl;
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '4':
  {
    menu =
        "**************************************************************\n"
        "* 4. Traveling salesman problem                              \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "In this task, we will select N random points on the map and you need to find the path to travel these points and back to the start point.";
    std::cout << menu << std::endl << std::endl;
    menu = "Please input the number of the places:";
    std::cout << menu;
    getline(std::cin, input);
    int num = std::stoi(input);
    std::vector<std::string> keys;
    for (auto x : data) {
      keys.push_back(x.first);
    }
    std::vector<std::string> locations;
    srand(time(NULL));
    for (int i = 0; i < num; i++)
      locations.push_back(keys[rand() % keys.size()]);
    PlotPoints(locations);
    std::cout << "Calculating ..." << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    auto results = TravellingTrojan(locations);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    CreateAnimation(results.second);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results.second.size() != 0) {
      for (auto x : results.second[results.second.size()-1]) std::cout << x << std::endl;
      menu = "**************************************************************\n";
      std::cout << menu;
      std::cout << "The distance of the path is:" << results.first << " miles" << std::endl;
      PlotPath(results.second[results.second.size()-1]);
    } else {
      std::cout << "The size of the path is 0" << std::endl;
    }
    menu = "**************************************************************\n"
           "You could find your animation at src/lib/output.avi.          \n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '5':
  {
    menu =
        "**************************************************************\n"
        "* 5. Cycle Detection                                          \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the left bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    std::vector<double> square;
    square.push_back(atof(input.c_str()));

    menu = "Please input the right bound longitude(between -118.299 and -118.264):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the upper bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    menu = "Please input the lower bound latitude(between 34.011 and 34.032):";
    std::cout << menu;
    getline(std::cin, input);
    square.push_back(atof(input.c_str()));

    auto start = std::chrono::high_resolution_clock::now();
    auto results = CycleDetection(square);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************\n";
    std::cout << menu;
    if (results == true)
      std::cout << "there exists cycle in the subgraph " << std::endl;
    else
      std::cout << "there exist no cycle in the subgraph " << std::endl;
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '6':
  {
    menu =
        "**************************************************************\n"
        "* 6. Topological Sort                                         \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    menu = "Please input the locations filename:";
    std::cout << menu;
    std::string locations_filename;
    getline(std::cin, locations_filename);
    menu = "Please input the dependencies filename:";
    std::cout << menu;
    std::string dependencies_filename;
    getline(std::cin, dependencies_filename);
    
    // Read location names from CSV file
    std::vector<std::string> location_names;
    if (locations_filename == "") {
      //location_names = {"Ralphs", "Target", "Chipotle Mexican Grill", "CVS", "ChickfilA"};
      location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    }
    else{
      location_names = ReadLocationsFromCSVFile(locations_filename);
    }
    // Read dependencies from CSV file
    std::vector<std::vector<std::string>> dependencies;
    if (dependencies_filename == ""){
      //dependencies = {{"Target","Chipotle Mexican Grill"}, {"Target","CVS"}, {"Ralphs","CVS"}, {"Ralphs","ChickfilA"}};
      //dependencies = {{"Cardinal Gardens","Coffee Bean1"}, {"Cardinal Gardens","CVS"}, {"Coffee Bean1","CVS"}};
      dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};
    }
      
    else{
      dependencies = ReadDependenciesFromCSVFile(dependencies_filename);
    }
    
    // std::vector<std::string> location_names = {"Cardinal Gardens", "Coffee Bean1","CVS"};
    // std::vector<std::vector<std::string>> dependencies = {{"Coffee Bean1","Cardinal Gardens"}, {"CVS","Cardinal Gardens"}, {"CVS","Coffee Bean1"}};

    auto start = std::chrono::high_resolution_clock::now();
    auto result = DeliveringTrojan(location_names, dependencies);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Topological Sorting Results:" << std::endl;
    if(result.empty()){
      std::cout<<"No feasible route exists"<<std::endl;
    }
    else{
    for (auto x : result) std::cout << x << std::endl;
    std::vector<std::string> node_ids;
    for (auto x: result) {
      std::string id = GetID(x);
      node_ids.push_back(id);
    }
    PlotPointsOrder(node_ids);
    }
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
    case '7':
  {
    menu =
        "**************************************************************\n"
        "* 7. Find K Closest Points                                    \n"
        "**************************************************************\n";
    std::cout << menu << std::endl;
    
    menu = "Please input the locations:";
    std::cout << menu;
    std::string origin;
    getline(std::cin, origin);
    menu = "Please input k:";
    std::cout << menu;
    getline(std::cin, input);
    int k = std::stoi(input);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result = FindKClosestPoints(origin, k);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    menu = "*************************Results******************************";
    std::cout << menu << std::endl;
    std::cout << "Find K Closest Points Results:" << std::endl;
    int cnt = 1;
    for (auto x : result) { 
      std::cout << cnt << " " << data[x].name << std::endl;
      cnt++;
    }
    PlotPointsLabel(result, GetID(origin));
    menu = "**************************************************************\n";
    std::cout << menu;
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl << std::endl;
    PrintMenu();
    break;
  }
  case '8':
    break;
  default:
  {
    std::cout << "Please select 1 - 8." << std::endl;
    PrintMenu();
    break;
  }
  }
}


/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  std::fstream fin;
  fin.open("src/lib/map.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '['), word.end());
      word.erase(std::remove(word.begin(), word.end(), ']'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}

/**
 * PlotPoint: Given a location id, plot the point on the map
 * 
 * @param  {std::string} id : location id
 */
void TrojanMap::PlotPoint(std::string id) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(data[id].lat, data[id].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}
/**
 * PlotPoint: Given a lat and a lon, plot the point on the map
 * 
 * @param  {double} lat : latitude
 * @param  {double} lon : longitude
 */
void TrojanMap::PlotPoint(double lat, double lon) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto result = GetPlotLocation(lat, lon);
  cv::circle(img, cv::Point(int(result.first), int(result.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPath: Given a vector of location ids draws the path (connects the points)
 * 
 * @param  {std::vector<std::string>} location_ids : path
 */
void TrojanMap::PlotPath(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::line(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::startWindowThread();
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPoints(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points inside square
 * @param  {std::vector<double>} square : boundary
 */
void TrojanMap::PlotPointsandEdges(std::vector<std::string> &location_ids, std::vector<double> &square) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  auto upperleft = GetPlotLocation(square[2], square[0]);
  auto lowerright = GetPlotLocation(square[3], square[1]);
  cv::Point pt1(int(upperleft.first), int(upperleft.second));
  cv::Point pt2(int(lowerright.first), int(lowerright.second));
  cv::rectangle(img, pt2, pt1, cv::Scalar(0, 0, 255));
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    for(auto y : data[x].neighbors) {
      auto start = GetPlotLocation(data[x].lat, data[x].lon);
      auto end = GetPlotLocation(data[y].lat, data[y].lon);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPointsOrder: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsOrder(std::vector<std::string> &location_ids) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::putText(img, data[x].name, cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
  }
  // Plot dots and lines
  auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
  cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
             cv::Scalar(0, 0, 255), cv::FILLED);
  for (auto i = 1; i < location_ids.size(); i++) {
    auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
    auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
    cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::arrowedLine(img, cv::Point(int(start.first), int(start.second)),
             cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
             LINE_WIDTH);
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * PlotPoints: Given a vector of location ids draws the points on the map (no path).
 * 
 * @param  {std::vector<std::string>} location_ids : points
 */
void TrojanMap::PlotPointsLabel(std::vector<std::string> &location_ids, std::string origin) {
  std::string image_path = cv::samples::findFile("src/lib/input.jpg");
  cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
  int cnt = 1;
  auto result = GetPlotLocation(data[origin].lat, data[origin].lon);
  cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 255, 0), cv::FILLED);
  for (auto x : location_ids) {
    auto result = GetPlotLocation(data[x].lat, data[x].lon);
    cv::circle(img, cv::Point(result.first, result.second), DOT_SIZE,
               cv::Scalar(0, 0, 255), cv::FILLED);
    cv::putText(img, std::to_string(cnt), cv::Point(result.first, result.second), cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(255, 0, 0), 2);
    cnt++;
  }
  cv::imshow("TrojanMap", img);
  cv::waitKey(1);
}

/**
 * CreateAnimation: Create the videos of the progress to get the path
 * 
 * @param  {std::vector<std::vector<std::string>>} path_progress : the progress to get the path
 */
void TrojanMap::CreateAnimation(std::vector<std::vector<std::string>> path_progress){
  cv::VideoWriter video("src/lib/output.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(1248,992));
  for(auto location_ids: path_progress) {
    std::string image_path = cv::samples::findFile("src/lib/input.jpg");
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    auto start = GetPlotLocation(data[location_ids[0]].lat, data[location_ids[0]].lon);
    cv::circle(img, cv::Point(int(start.first), int(start.second)), DOT_SIZE,
              cv::Scalar(0, 0, 255), cv::FILLED);
    for (auto i = 1; i < location_ids.size(); i++) {
      auto start = GetPlotLocation(data[location_ids[i - 1]].lat, data[location_ids[i - 1]].lon);
      auto end = GetPlotLocation(data[location_ids[i]].lat, data[location_ids[i]].lon);
      cv::circle(img, cv::Point(int(end.first), int(end.second)), DOT_SIZE,
                cv::Scalar(0, 0, 255), cv::FILLED);
      cv::line(img, cv::Point(int(start.first), int(start.second)),
              cv::Point(int(end.first), int(end.second)), cv::Scalar(0, 255, 0),
              LINE_WIDTH);
    }
    video.write(img);
    cv::imshow("TrojanMap", img);
    cv::waitKey(1);
  }
	video.release();
}
/**
 * GetPlotLocation: Transform the location to the position on the map
 * 
 * @param  {double} lat         : latitude 
 * @param  {double} lon         : longitude
 * @return {std::pair<double, double>}  : position on the map
 */
std::pair<double, double> TrojanMap::GetPlotLocation(double lat, double lon) {
  std::pair<double, double> bottomLeft(34.01001, -118.30000);
  std::pair<double, double> upperRight(34.03302, -118.26502);
  double h = upperRight.first - bottomLeft.first;
  double w = upperRight.second - bottomLeft.second;
  std::pair<double, double> result((lon - bottomLeft.second) / w * 1248,
                                   (1 - (lat - bottomLeft.first) / h) * 992);
  return result;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(std::string id) {
  double a = 0.0;
    for (auto i = data.begin(); i != data.end(); i++){
    std::string b = data[i->first].id;
    if(b == id ){
      a = data[i->first].lat;
    }
  }
    return a;
}


/**
 * GetLon: Get the longitude of a Node given its id. 
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(std::string id) { 
    double a =0.0;
    for (auto i = data.begin(); i != data.end(); i++){
    std::string b = data[i->first].id;
    if(b == id ){
      a = data[i->first].lon;
    }
  }
    return a;
}

/**
 * GetName: Get the name of a Node given its id.
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(std::string id) { 
  std::string name ="";
  for (auto i = data.begin(); i != data.end(); i++){
    std::string a = data[i->first].id;
    if(a == id ){
      name = data[i->first].name;
    }
  }
    return name;
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(std::string id) {
    std::vector<std::string> v;
    for (auto i = data.begin(); i != data.end(); i++){
    std::string a = data[i->first].id;
    if(a == id ){
      v =data[i->first].neighbors;
    }
  }
    return v;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  // TODO: Use Haversine Formula:
  // dlon = lon2 - lon1;
  // dlat = lat2 - lat1;
  // a = (sin(dlat / 2)) ^ 2 + cos(lat1) * cos(lat2) * (sin(dlon / 2)) ^ 2;
  // c = 2 * arcsin(min(1, sqrt(a)));
  // distances = 3961 * c;

  // where 3961 is the approximate radius of the earth at the latitude of
  // Washington, D.C., in miles
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  if(path.empty()){
    return sum;
  }
  else{
    for (int i = 0;i < path.size()-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  }
  return sum;
}

/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  if (name.empty()){
    return results;
  }
  std::transform(name.begin(),name.end(),name.begin(),::tolower);
  for (auto i = data.begin(); i != data.end(); i++){
    std::string a = data[i->first].name;
    std::transform(a.begin(),a.end(),a.begin(),::tolower);
    auto res = std::mismatch(name.begin(), name.end(), a.begin());
    if(res.first == name.end()){
      results.push_back(data[i->first].name);
    }
  }
  return results;
}

/**
 * GetPosition: Given a location name, return the position.
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  if(name.empty()){
    return results;
  }
  for (auto i = data.begin(); i != data.end(); i++){
    std::string a = data[i->first].name;
    if(a == name){
      results.first = data[i->first].lat;
      results.second =  data[i->first].lon;
    }
  }
  return results;
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(std::string name) {
  std::string res;
  for (auto i = data.begin(); i != data.end(); i++){
    std::string a = data[i->first].name;
    if(a == name){
      res = data[i->first].id;
    }
  }
  return res;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */

std::unordered_map<std::string, int> TrojanMap::keys_ID(){
  std::unordered_map<std::string, int> temp_map;
  int counter = 0;
  for(auto i = data.begin(); i != data.end(); i++){
    temp_map.insert(std::pair<std::string,int>((i->second).id, counter));
    counter = counter + 1;
  }
  return temp_map;
} 
std::unordered_map<int, std::string> TrojanMap::keys_Index(){
  std::unordered_map<int, std::string> temp_map;
  std::unordered_map<std::string, int> temp_map_2 = keys_ID();
  for(auto i = data.begin(); i != data.end(); i++){
    temp_map.insert(std::pair<int,std::string>(temp_map_2[(i->second).id],(i->second).id));
  }
  return temp_map;
}

int TrojanMap::convert_to_Index(const std::string a){
  int counter = 0;
  for(auto i = data.begin(); i != data.end(); i++){
    if((i->second).id == a){
      break;
     }
    counter = counter + 1;
  }
  return counter;
}

std::string TrojanMap::convert_to_ID(int a){
  auto it = std::next(data.begin(),a);
  return (it->second).id;
}

std::vector<std::vector<double>> TrojanMap::construct_2D_Weights_Matrix(){
  std::vector<std::string> neighbours;
  std::vector<std::vector<double>> weights_2D(int(data.size()), std::vector<double>(int(data.size()),INT_MAX));
  std::unordered_map<std::string, int> keys_ID_map = keys_ID();
  std::unordered_map<int, std::string> keys_Index_Map = keys_Index();
  for(int i = 0; i < int(data.size()); i++){
      weights_2D[i][i] = 0;
      neighbours = GetNeighborIDs(keys_Index_Map[i]);
      for(int j = 0; j < int(neighbours.size()); j++){
        weights_2D[i][keys_ID_map[(neighbours[j])]] = CalculateDistance(keys_Index_Map[i], neighbours[j]);
      }
  }
  return weights_2D;
}

std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> empty_path = {};
  std::vector<std::string> path;
  
  if(location1_name.empty() || location2_name.empty() || GetID(location1_name).empty() || GetID(location2_name).empty()){
    return empty_path;
  }
  std::vector<std::string> reverse_path;
  
  std::vector<std::vector<double>> weights_2D = construct_2D_Weights_Matrix();
  std::unordered_set<std::string> visited;
  std::vector<std::pair<double,int>> distances_and_pre_1D(int(weights_2D.size()), std::make_pair(0,-1));

  

  std::unordered_map<std::string, int> keys_ID_map = keys_ID();
  std::unordered_map<int, std::string> keys_Index_Map = keys_Index();

  bool path_nonexistence = false;
  int source_index = keys_ID_map[(GetID(location1_name))];
  double min;
  int index_of_min;

  for(int j = 0; j < int(data.size()); j++){
    distances_and_pre_1D[j].first = weights_2D[source_index][j];
  }
  distances_and_pre_1D[source_index].first = 0;

  visited.insert(GetID(location1_name));

  std::vector<std::string> temp_neighbours;

  while(path_nonexistence == false && std::count(visited.begin(), visited.end(), GetID(location2_name)) == 0 && int(visited.size()) < int(weights_2D.size())){
    min = INT_MAX;
    path_nonexistence = true;
    for (int i = 0; i < int(distances_and_pre_1D.size()); i++) {
      if (visited.count(keys_Index_Map[i]) > 0) {
        continue;
      }
      double e = distances_and_pre_1D[i].first;
      if (min > e) {
        min = e;
        index_of_min = i;
        path_nonexistence = false;
      }
    }
    std::string a = keys_Index_Map[(index_of_min)];
    visited.insert(a);

    temp_neighbours = GetNeighborIDs(a);

    if(path_nonexistence == true){
      continue;
    }
    std::string b;
    int counter_temporary = 0;
    for(int i = 0; i < int(temp_neighbours.size()); i++){
      counter_temporary = keys_ID_map[temp_neighbours[i]];
      b = keys_Index_Map[counter_temporary];
      if(visited.count(b) == 0 && std::count(temp_neighbours.begin(),temp_neighbours.end(),b) > 0){
        distances_and_pre_1D[counter_temporary].first = std::min(distances_and_pre_1D[counter_temporary].first, distances_and_pre_1D[index_of_min].first + weights_2D[index_of_min][counter_temporary]);
        if(std::min(distances_and_pre_1D[counter_temporary].first, distances_and_pre_1D[index_of_min].first + weights_2D[index_of_min][counter_temporary]) == distances_and_pre_1D[index_of_min].first + weights_2D[index_of_min][counter_temporary]){
          distances_and_pre_1D[counter_temporary].second = index_of_min;
        }
      }
    }
  }

  if(visited.count(GetID(location2_name)) <= 0){
    return empty_path;
  }

  reverse_path.push_back(GetID(location2_name));
  std::string temp = GetID(location2_name);


  while(distances_and_pre_1D[keys_ID_map[temp]].second != -1){
    temp = keys_Index_Map[(distances_and_pre_1D[convert_to_Index(temp)].second)];
    reverse_path.push_back(temp);
  }
  reverse_path.push_back(GetID(location1_name));
  
  for(int i = int(reverse_path.size()) - 1; i >= 0; i--){
    path.push_back(reverse_path[i]);
  }
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  std::vector<std::string> path;
  if(location1_name.empty() || location2_name.empty() || GetID(location1_name) == "" || GetID(location2_name) == ""){
    return path;
  }
  std::vector<std::string> reverse_path;
  std::vector<std::string> empty_path = {};
  std::vector<std::vector<double>> weights_2D = construct_2D_Weights_Matrix();
  std::vector<double> source_distances;
  std::vector<std::string> predecessors(int(data.size()), "NONE");
  int counter_predecessors = 0;

  std::unordered_map<std::string, int> keys_ID_map = keys_ID();
  std::unordered_map<int, std::string> keys_Index_Map = keys_Index();

  if(GetID(location1_name) == "" || GetID(location2_name) == ""){
    std::cout<< "Please enter valid location names residing throughout the map!"<<std::endl;
    return empty_path;
  }

  int source_index_temp = keys_ID_map[(GetID(location1_name))];

  for(int i = 0; i <= int(weights_2D.size()); i++){
    source_distances.push_back(weights_2D[source_index_temp][i]);
  } 

  source_distances[keys_ID_map[(GetID(location1_name))]] = 0;

  std::vector<std::string> temp_neighbours;
  int temp_int = 0;

  int counter_temp_1 = 0;

  for(int i = 0; i < int(weights_2D.size()) - 1; i++){
    counter_temp_1 = counter_temp_1 + 1;
    for(int edge_u = 0; edge_u < int(weights_2D.size()); edge_u++){
      for(int edge_v = 0; edge_v < int(weights_2D.size()); edge_v++){
        temp_int = edge_v;
        if(source_distances[temp_int] > (source_distances[edge_u] + weights_2D[edge_u][temp_int]) ){
          source_distances[temp_int] = source_distances[edge_u] + weights_2D[edge_u][temp_int];
          predecessors[temp_int] = keys_Index_Map[edge_u];
        }
      }
    }
  }

  if(source_distances[keys_ID_map[(GetID(location2_name))]] == INT_MAX){
    return empty_path;
  }

  std::string temp_predecessor = GetID(location2_name);
  reverse_path.push_back(temp_predecessor);

  while(predecessors[keys_ID_map[(temp_predecessor)]] != "NONE"){
    temp_predecessor = predecessors[keys_ID_map[(temp_predecessor)]];
    reverse_path.push_back(temp_predecessor);
    counter_predecessors = counter_predecessors + 1;
  }
  reverse_path.push_back(GetID(location1_name));

  for(int i = int(reverse_path.size()) - 1; i >= 0; i--){
    path.push_back(reverse_path[i]);
  }
  return path;
}
/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
// 
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  
  int start = 0;
  std::vector<int> cur_path = {start};
  std::vector<int> min_path;
  double min_cost = DBL_MAX;
  results.first= min_cost;
  TSP_aux_BackTracking(start,location_ids,start, 0.0, cur_path,min_cost,min_path,results);
  return results;
}
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Bruteforce(
                                    std::vector<std::string> &location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> results;
  
  int start = 0;
  std::vector<int> cur_path = {start};
  std::vector<int> min_path;
  double min_cost = DBL_MAX;
  results.first= min_cost;
  TSP_aux(start,location_ids,start, 0.0, cur_path,min_cost,min_path,results);
  return results;
}
std::vector<std::string> TrojanMap::indextoString(std::vector<std::string> &location_ids,std::vector<int> cur_path){
  std::vector<std::string> fin_path(location_ids.size());
  int j = 0;
  for(int i = 0; i<cur_path.size(); i++){
    j = cur_path[i];
    fin_path[i]= location_ids[j];
  }
  fin_path.push_back(location_ids[0]);
  return fin_path;
}

void TrojanMap::TSP_aux(int start,std::vector<std::string> &location_ids,int cur_node, double cur_cost,std::vector<int> &cur_path, double &min_cost, std::vector<int> &min_path, std::pair<double, std::vector<std::vector<std::string>>> &results){
  std::vector<std::string> cur_pathStr(location_ids.size());
  if(cur_path.size()==location_ids.size()){
    
    double final_cost= cur_cost + CalculateDistance(location_ids[cur_node],location_ids[start]);
    if(final_cost < min_cost){
      results.first = final_cost;
      min_cost = final_cost;
      min_path = cur_path;
      cur_pathStr = indextoString(location_ids,cur_path);
      results.first = min_cost;
      results.second.push_back(cur_pathStr);
    } 
    return;
  }

  for(int i = 0; i < location_ids.size(); i++){
    auto it = std::find(cur_path.begin(), cur_path.end(), i);
    if(it == cur_path.end()){
      cur_path.push_back(i);
      TSP_aux(start, location_ids, i, cur_cost + CalculateDistance(location_ids[cur_node],location_ids[i]), cur_path, min_cost, min_path,results);
      cur_path.pop_back();
      }
  }
}

void TrojanMap::TSP_aux_BackTracking(int start,std::vector<std::string> &location_ids,int cur_node, double cur_cost,std::vector<int> &cur_path, double &min_cost, std::vector<int> &min_path, std::pair<double, std::vector<std::vector<std::string>>> &results){
  std::vector<std::string> cur_pathStr(location_ids.size());
  if(cur_path.size()==location_ids.size()){
    
    double final_cost= cur_cost + CalculateDistance(location_ids[cur_node],location_ids[start]);
    if(final_cost < min_cost){
      results.first = final_cost;
      min_cost = final_cost;
      min_path = cur_path;
      cur_pathStr = indextoString(location_ids,cur_path);
      results.first = min_cost;
      results.second.push_back(cur_pathStr);
    } 
    return;
  }
  if(cur_cost>results.first){
    return;
  }
  for(int i = 0; i < location_ids.size(); i++){
    auto it = std::find(cur_path.begin(), cur_path.end(), i);
    if(it == cur_path.end()){
      cur_path.push_back(i);
      TSP_aux_BackTracking(start, location_ids, i, cur_cost + CalculateDistance(location_ids[cur_node],location_ids[i]), cur_path, min_cost, min_path,results);
      cur_path.pop_back();
      }
  }
}


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::string> clocation_ids;
  for(auto i: location_ids){
    clocation_ids.push_back(i);
  }
  clocation_ids.push_back(location_ids[0]);
  

  double new_distance;
  std::vector<std::string> existing_route = clocation_ids;
  double best_distance;
  std::vector<std::string> new_route;

    int n = 0;
    while(n < 1000) {
    best_distance = CalculatePathLength(existing_route);
    for (int i = 1; i <= clocation_ids.size() - 1; i++) {
        for (int k = i + 1; k <= location_ids.size()-1; k++) {
            new_route = TSP_2optSwap(existing_route, i, k);
            new_distance = CalculatePathLength(new_route);
            if (new_distance < best_distance) {
                existing_route = new_route;
                best_distance = new_distance;
                results.second.push_back(new_route);
                results.first = new_distance;
            }
        }
    }
    n++;
}

  return results;
}
std::vector<std::string> TrojanMap::TSP_2optSwap(std::vector<std::string> &location_ids, int i, int k){
  std::vector<std::string> new_route(location_ids.begin(),location_ids.begin()+i);
  std::vector<std::string> rv(location_ids.begin()+i,location_ids.begin()+k+1);
  std::reverse(rv.begin(),rv.end());
  new_route.insert(new_route.end(),rv.begin(),rv.end());
  new_route.insert(new_route.end(),location_ids.begin()+k+1,location_ids.end());
  return new_route; 
}


std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_3opt(std::vector<std::string> &location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> results;
  std::vector<std::string> clocation_ids;
  
  for(auto i: location_ids){
    clocation_ids.push_back(i);
  }
  clocation_ids.push_back(location_ids[0]);
  
  double new_distance;
  std::vector<std::string> existing_route = clocation_ids;
  double best_distance;
  std::vector<std::string> new_route;

    int n = 0;
    while(n < 1000) {
    best_distance = CalculatePathLength(existing_route);
    for (int i = 1; i <= location_ids.size() ; i++) {
        for (int j = i + 2 ; j <= location_ids.size() ; j++) {
            for (int k = j + 2; j <= location_ids.size() + (i>0); k++){
              //std::cout<<"before entering swap"<<std::endl;
              new_route = TSP_3optSwap(existing_route, i, k, j);
              for(auto it : new_route){
                std::cout<<it<<std::endl;
              }
              new_distance = CalculatePathLength(new_route);
              if (new_distance < best_distance) {
                existing_route = new_route;
                best_distance = new_distance;
                results.second.push_back(new_route);
                results.first = new_distance;
            }
            }
        }
    }
    n++;
}
  return results;
}
std::vector<std::string> TrojanMap::TSP_3optSwap(std::vector<std::string> &loc, int i, int k, int j){
  std::vector<std::string> empty_path;
  std::string a = loc[i-1];
  std::string b = loc[i];

  std::string c = loc[j-1];
  std::string d = loc[j];
  
  std::string e = loc[k-1];
  std::string f = loc[k%loc.size()];

  double d0 = CalculateDistance(a,b) + CalculateDistance(c,d) + CalculateDistance(e,f); 
  double d1 = CalculateDistance(a,c) + CalculateDistance(b,d) + CalculateDistance(e,f); 
  double d2 = CalculateDistance(a,b) + CalculateDistance(c,e) + CalculateDistance(d,f); 
  double d3 = CalculateDistance(a,d) + CalculateDistance(e,b) + CalculateDistance(c,f); 
  double d4 = CalculateDistance(f,b) + CalculateDistance(c,d) + CalculateDistance(e,a); 
  
  if(d0>d1){
    std::reverse(loc.begin()+ i, loc.begin()+j);
  }
  else if(d0>d2){
    std::reverse(loc.begin() + j, loc.begin()+k);
  }
  else if(d0>d4){
    std::reverse(loc.begin()+i,loc.begin()+k);
  }
  else if(d0>d3){
    int count = 0;
    std::vector<std::string> path1(loc.begin()+j,loc.begin()+k);
    std::vector<std::string> path2(loc.begin()+i, loc.begin()+j);
    path1.insert(path1.end(),path2.begin(),path2.end());
    for(auto it : path1){
      loc[i + count] = it;
    }
  }
  return loc;
}
/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  std::fstream fin;
  fin.open(locations_filename, std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    while (getline(s, word, ',')) {
      location_names_from_csv.push_back(word);
    }
  }
  fin.close();

  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  std::fstream fin;
  fin.open(dependencies_filename, std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);
    std::string parent;
    std::string child;
    std::vector<std::string> temp;
    int count = 0;
    while (getline(s, word, ',')) {
      
      if (count == 0){
        parent = word;
        temp.push_back(parent);
      }
      else if(count == 1){
        child = word;
        temp.push_back(child);
      }
      count++;

    }
    dependencies_from_csv.push_back(temp);
  }
  fin.close();
  
  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations, std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;
  
  std::unordered_map<std::string, std::vector<std::string>> adj;
  for(auto location:locations){
    std::vector<std::string> temp;
    adj[location]= temp;
  }
  for(auto dependency:dependencies){
    adj[dependency[0]].push_back(dependency[1]);
  }

  std::string curnode;
  std::map<std::string,int> indegree;
  
  for (int i =0 ; i<locations.size();i++){
    curnode = locations[i];
    indegree[curnode]=0;
  }
  for(int i=0;i<locations.size();i++){
    curnode = locations[i];
    for(auto child : adj[curnode]){
      indegree[child]++;
    }
  }
  std::string root = getMin(indegree);
  
  std::map<std::string, int> marks;
  for (auto& id: locations){
    if(marks.count(id) == 0) {
      DFS_helper_TopoSort(id,marks,adj,result);
    }
  }
  std::reverse(result.begin(),result.end());
  std::vector<std::string> result_copy;
  result_copy=result;
  
  for (auto loc : locations){
    for (auto it : adj[loc]){
      if (indexFinder(result_copy,loc)>indexFinder(result_copy,it)){
        result.clear();
        break;
      }
    }
  }
  return result;   
}

int TrojanMap::indexFinder(std::vector<std::string> locations, std::string specific_location){
  int index =0;
  auto it = find(locations.begin(),locations.end(),specific_location);
  index = it - locations.begin();
  return index;
}

void TrojanMap::DFS_helper_TopoSort(std::string root, std::map<std::string, int> &marks,std::unordered_map<std::string, std::vector<std::string>> adj, std::vector<std::string> &result){
       
  marks[root] = 1;
  
  for (auto child: adj[root]){
    if(marks[child] != 1){
      DFS_helper_TopoSort(child, marks, adj, result);
    }
  }
  result.push_back(root);
}
bool TrojanMap::compare(std::pair<std::string, int> i, std::pair<std::string, int> j) 
{ 
  return i.second < j.second; 
}

std::string TrojanMap::getMin(std::map<std::string, int> mymap) 
{
  std::pair<std::string, int> min = *min_element(mymap.begin(), mymap.end(), &TrojanMap::compare);
  return min.first; 
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */

bool TrojanMap::CycleDetection_Helper(std::string current_ID, std::map<std::string, bool> &visited, std::string parent_ID, std::map<std::string, std::vector<std::string>> &predecessors, double &left, double &right, double &top, double &bottom, std::vector<std::string> &cycle_path){
  visited[current_ID] = true;
  std::vector<std::string> neighbours = GetNeighborIDs(current_ID);
  predecessors.insert(std::pair<std::string,std::vector<std::string>>(parent_ID,neighbours));

  for(int i = 0; i < int(neighbours.size()); i++){
    if((data[neighbours[i]].lat <= top && data[neighbours[i]].lat >= bottom) && (data[neighbours[i]].lon <= right && data[neighbours[i]].lon >= left)){
      if(visited[neighbours[i]] == false){
        cycle_path.push_back(neighbours[i]);
        bool test = CycleDetection_Helper(neighbours[i], visited, current_ID, predecessors, left, right, top, bottom, cycle_path);
        if(test){
          return true;
        }
        cycle_path.pop_back();
        continue;
      }
      if(visited[neighbours[i]] == true){
        if(neighbours[i] != parent_ID){
          cycle_path.push_back(neighbours[i]);
          return true;
        }
      }
    }
  }

  return false;
}

bool TrojanMap::CycleDetection(std::vector<double> &square) {
  if(square[0] < -118.299 || square[1] > -118.264 || square[2] > 34.032 || square[3] < 34.011 || square[1] < square[0] || square[2] < square[3]){
    std::cout << "Please enter the longitude and latitude credentials within the offered boundaries!" << std::endl;  
  }
  std::vector<std::string> present_nodes;
  std::vector<std::string> cycle_path;
  std::map<std::string,bool> visited;
  std::map<std::string,std::vector<std::string>> predecessors;
  std::string a;
  for(int i = 0; i < int(data.size()); i++){
    a = convert_to_ID(i);
    if((data[a].lat <= square[2] && data[a].lat >= square[3]) && (data[a].lon <= square[1] && data[a].lon >= square[0])){
      visited.insert(std::pair<std::string,bool>(a, false));
      present_nodes.push_back(a);
    }
  }
  for(auto i: visited){
    if(i.second == false){
      cycle_path = {};
      cycle_path.push_back(i.first);
      if(CycleDetection_Helper(i.first, visited, i.first, predecessors, square[0], square[1], square[2], square[3],cycle_path)){
        PlotPointsandEdges(cycle_path,square);
        return true;
      }
    }
  }
  return false;
}

/**
 * FindKClosetPoints: Given a location id and k, find the k closest points on the map
 * 
 * @param {std::string} name: the name of the location
 * @param {int} k: number of closest points
 * @return {std::vector<std::string>}: k closest points
 */
std::vector<std::string> TrojanMap::FindKClosestPoints(std::string name, int k) {
  std::vector<std::string> res;

  std::vector<std::string> reversed_closest;

  std::priority_queue<std::pair<double,std::string>> max_heap;

  std::string source_ID = GetID(name);
  if(source_ID == ""|| name.empty()){
    std::cout<< "Please enter a valid location name!" << std::endl;
    return res;
  }
  if(k <= 0){
    std::cout<< "Please enter a positive number for k" << std::endl;
    return res;
  }

  int counter_max_heap = 0;
  std::string a;
  for(int i = 0; i < int(data.size()); i++){
    a = convert_to_ID(i);
    if(GetName(a) == ""){
      continue;
    }
    if(a != source_ID){
      if(counter_max_heap < k){
        max_heap.push(std::make_pair(CalculateDistance(source_ID, a), a));
        counter_max_heap = counter_max_heap + 1;
      }
      else{
        if(CalculateDistance(source_ID, a) < (max_heap.top()).first){
          max_heap.pop();
          max_heap.push(std::make_pair(CalculateDistance(source_ID, a), a));
        }
      }
    }
  }
  int temp_size = int(max_heap.size());
  for(int i = 0; i < temp_size; i++){
    reversed_closest.push_back((max_heap.top()).second);
    max_heap.pop();
  }

  for(int i = int(reversed_closest.size()) - 1; i >= 0; i--){
    res.push_back(reversed_closest[i]);
  }

  return res;
}