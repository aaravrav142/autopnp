#include <functional>

#include <ipa_room_segmentation/voronoi_random_field_segmentation.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>


int main()
{
	cv::Mat map = cv::imread("/home/rmb-fj/git/care-o-bot-indigo/src/autopnp/ipa_room_segmentation/common/files/test_maps/office_e_furnitures.png", 0); // office_b.png  /home/rmb-fj/Pictures/map.png

	for(unsigned int u = 0; u < map.rows; ++u)
	{
		for(unsigned int v = 0; v < map.cols; ++v)
		{
			if(map.at<unsigned char>(u,v) < 250)
			{
				map.at<unsigned char>(u,v) = 0;
			}
			else
			{
				map.at<unsigned char>(u,v) = 255;
			}
		}
	}

//	uchar t = 127;
//	uint g = 127;

	std::vector<uint> possible_labels(3); // vector that stores the possible labels that are drawn in the training maps. Order: room - hallway - doorway
	possible_labels[0] = 77;
	possible_labels[1] = 115;
	possible_labels[2] = 179;

	// string that stores the path to the saving files
	std::string conditional_weights_path = "/home/rmb-fj/git/care-o-bot-indigo/src/autopnp/ipa_room_segmentation/common/files/training_results/conditional_field_weights.txt";
	std::string boost_file_path = "/home/rmb-fj/git/care-o-bot-indigo/src/autopnp/ipa_room_segmentation/common/files/training_results/";

	// load the training maps
	cv::Mat training_map;
	std::vector<cv::Mat> training_maps;
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_Fr52.png", 0);
	training_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_Fr101.png", 0);
	training_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_intel.png", 0);
	training_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_lab_d_furniture.png", 0);
	training_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_lab_ipa.png", 0);
	training_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_NLB_furniture.png", 0);
	training_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/training_maps/training_office_e.png", 0);
	training_maps.push_back(training_map);
	// load the voronoi maps
	std::vector<cv::Mat> voronoi_maps;
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/Fr52_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/Fr101_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/lab_intel_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/lab_d_furnitures_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/lab_ipa_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	training_map = cv::imread("//home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/NLB_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_maps/office_e_voronoi.png", 0);
	voronoi_maps.push_back(training_map);
	// load the voronoi-nodes maps
	std::vector<cv::Mat> voronoi_node_maps;
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/Fr52_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/Fr101_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/lab_intel_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/lab_d_furnitures_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	training_map = cv::imread("//home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/lab_ipa_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/NLB_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/voronoi_node_maps/office_e_voronoi_nodes.png", 0);
	voronoi_node_maps.push_back(training_map);
	// load the original maps
	std::vector<cv::Mat> original_maps;
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/Fr52_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/Fr101_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/lab_intel_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/lab_d_furnitures_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/lab_ipa_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/NLB_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);
	training_map = cv::imread("/home/rmb-fj/Pictures/voronoi_random_fields/voronoi_training/original_maps/office_e_voronoi_nodes.png", 0);
	original_maps.push_back(training_map);

	std::cout << training_maps.size() << " " << voronoi_maps.size() << " " << voronoi_node_maps.size() << " " << original_maps.size() << std::endl;
//	for(size_t i = 0; i < training_maps.size(); ++i)
//	{
//		cv::imshow("training_map", training_maps[i]);
//		cv::imshow("voronoi_map", voronoi_maps[i]);
//		cv::imshow("nodes", voronoi_node_maps[i]);
//		cv::imshow("original_maps", original_maps[i]);
//		cv::waitKey();
//	}


	VoronoiRandomFieldSegmentation segmenter(true, true);

//	segmenter.segmentMap(map, 7, 50, 5, 7, true, "aa", "bb"); // 7, 50, 4, 5

	segmenter.trainAlgorithms(training_maps, voronoi_maps, voronoi_node_maps, original_maps, possible_labels, conditional_weights_path, boost_file_path);

//	segmenter.testFunc(map);

//	std::vector<std::vector<double> > d(4);
//	std::vector<double> a (4, 100);
//	std::vector<double> b (4, 200);
//
//	std::vector<double> c = a + b; // operator overload in voronoi_random_field_segmentation.h
//	d[0] = d[0] + a;
//	d[0] = d[0] + b;
////	d[1] = d[0];
//	d[3] += b;
//	d.back() += a;
//
//	for(size_t i = 0; i < d.size(); ++i)
//		for(size_t j = 0; j < d[i].size(); ++j)
//			std::cout << d[i][j] << std::endl;
//
//	column_vector test(4);
//
//	test = 1, 2, 3, 4;
//
//	std::cout << std::endl << test << std::endl;
//
//	std::ofstream output_file("/home/rmb-fj/Dokumente/test.txt", std::ios::out);
//	if (output_file.is_open()==true)
//		output_file << test;
//	output_file.close();
//
//	std::vector<double> weight_vector;
//
//	for(size_t weight = 0; weight < 4; ++weight)
//		weight_vector.push_back(test(0, weight));
//
//	std::cout << std::endl << "resaved vector: " << std::endl;
//
//	for(size_t i = 0; i < weight_vector.size(); ++i)
//		std::cout << weight_vector[i] << std::endl;
//
//	std::cout << "read in weights" << std::endl;
//
//	std::ifstream input_file("/home/rmb-fj/Dokumente/test.txt");
//	std::string line;
//	double value;
//	std::vector<double> read_weights;
//	if (input_file.is_open())
//	{
//		while (getline(input_file, line))
//		{
//			std::istringstream iss(line);
//			while (iss >> value)
//			{
//				std::cout << value << std::endl;
//				read_weights.push_back(value);
//			}
//		}
//		input_file.close();
//	}
//
//	std::cout << std::endl << "read vector: " << std::endl;
//
//	for(size_t i = 0; i < read_weights.size(); ++i)
//	{
//		std::cout << read_weights[i] << std::endl;
//	}

//	CvBoost boost;
//	boost.load("/home/rmb-fj/git/care-o-bot-indigo/src/autopnp/ipa_room_segmentation/common/files/training_results/trained_room_boost.xml");
//
//	std::vector<double> angles_for_simulation_;
//	for (double angle = 0; angle < 360; angle++)
//	{
//		angles_for_simulation_.push_back(angle);
//	}
//
//	std::vector<cv::Point> clique_members;
//
//	std::vector<double> temporary_beams = raycasting(map, cv::Point(350,350));
//
//	std::cout << "map value: " << (double) map.at<unsigned char>(350,350) << std::endl;
//
//	cv::Mat featuresMat(1, getFeatureCount()-1, CV_32FC1); //OpenCV expects a 32-floating-point Matrix as feature input
//	for (int f = 1; f <= getFeatureCount()-1; ++f)
//	{
//		//get the features for each room and put it in the featuresMat
//		featuresMat.at<float>(0, f - 1) = (float) getFeature(temporary_beams, angles_for_simulation_, clique_members, cv::Point(350,350), f);
//	}
//
//	CvMat features = featuresMat;									// Wanted from OpenCV to get the weak hypothesis from the
//	CvMat weak_hypothesis = cv::Mat(1, boost.get_weak_predictors()->total, CV_32F);	// separate weak classifiers.
//
//	std::cout << "weak: " << weak_hypothesis.cols << " features: " << features.cols << std::endl;
//
//	float sum = boost.predict(&features, 0, &weak_hypothesis, CV_WHOLE_SEQ, false, true);
//
//	float test_sum = 0;
//
//	for(size_t f = 0; f < weak_hypothesis.cols; ++f)
//	{
//		std::cout << CV_MAT_ELEM(weak_hypothesis, float, 0, f) << " " << f << std::endl;
//		test_sum += CV_MAT_ELEM(weak_hypothesis, float, 0, f);
//	}
//
//	std::cout << "complete sum: " << test_sum << " real sum: " << sum << std::endl;


//	cv::Mat ger(1,2,CV_32F);
//
//	ger.at<float>(0,0) = 2.3;
//	ger.at<float>(0,1) = 3.5;
//
//	CvMat test = ger;
//
//	float pixval = CV_MAT_ELEM(test, float, 0, 1);
//
//	std::cout << "normal Mat: " << (double) ger.at<float>(0, 1) << " new Mat: " << (double) pixval << std::endl;

//	std::vector<cv::Point> testpoints;
//	testpoints.push_back(cv::Point(200, 205));
//	testpoints.push_back(cv::Point(210, 205));
//	testpoints.push_back(cv::Point(200, 300));
//
//	cv::Point2f center;
//	float radius;
//
//	cv::minEnclosingCircle(testpoints, center, radius);
//
//    cv::circle(map, center, radius, cv::Scalar(127), CV_FILLED);
//    cv::circle(map, testpoints[0], 1, cv::Scalar(100), CV_FILLED);
//    cv::circle(map, testpoints[1], 1, cv::Scalar(100), CV_FILLED);
//    cv::circle(map, testpoints[2], 1, cv::Scalar(100), CV_FILLED);
//    cv::imshow("ellipse", map);
//    cv::imwrite("/home/rmb-fj/Pictures/ellipse.png", map);
//    cv::waitKey();




//	for(unsigned int i = 1; i < 4; ++i)
//	{
//		std::cout << i << " ";
//		if((i+1)%4 == 0)
//		{
//			std::cout << 1 << std::endl;
//		}
//		else
//		{
//			std::cout << i+1 << std::endl;
//		}
//	}

	std::map<unsigned int, double> label_mapping;

	// create each possible key and data (done by hand because in this case all possible configurations are known before --> room,hallway,doorway)
	label_mapping[possible_labels[0] + possible_labels[0]] = 10; // room-room
	label_mapping[possible_labels[0] + possible_labels[1]] = -10; // room-hallway
	label_mapping[possible_labels[0] + possible_labels[2]] = 5; // room-doorway
	label_mapping[possible_labels[1] + possible_labels[1]] = 10; // hallway-hallway
	label_mapping[possible_labels[1] + possible_labels[2]] = 5; // hallway-doorway
	label_mapping[possible_labels[2] + possible_labels[2]] = 10; // doorway-doorway

	std::cout << (float) label_mapping[possible_labels[0] + possible_labels[0]] << std::endl;

	return 0;
}