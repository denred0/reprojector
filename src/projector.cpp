#include <iostream>
using namespace std;

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <Eigen/Core>
#include <Eigen/Dense>

class Projector {
    public:
        int width, height;
        float fx1, fy1, cx1, cy1, lambda1, fx2, fy2, cx2, cy2, lambda2;

        void set_parameters (int, int, float, float, float, float, float, float, float, float, float, float);
        std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf> get3DCoordsfrom2D(int, int, float, float, float, float, float);
        std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf> get2DCoordsfrom3D(Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf, int, int, float, float, float, float, float);

};

void Projector::set_parameters (int width, int height, float fx1, float fy1, float cx1, float cy1, float lambda1, float fx2, float fy2, float cx2, float cy2, float lambda2) {
    width = width;
    height = height;

    fx1 = fx1;
    fy1 = fy1;
    cx1 = cx1;
    cy1 = cy1;
    lambda1 = lambda1;

    fx2 = fx2;
    fy2 = fy2;
    cx2 = cx2;
    cy2 = cy2;
    lambda2 = lambda2;
}


std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf, Eigen::ArrayXXf> Projector::get3DCoordsfrom2D(int width, int height, float fx, float fy, float cx, float cy, float lambda) {
    Eigen::ArrayXXf fx_mat = Eigen::MatrixXf::Constant(width, height, fx);
    Eigen::ArrayXXf fy_mat = Eigen::MatrixXf::Constant(width, height, fy);
    Eigen::ArrayXXf cx_mat = Eigen::MatrixXf::Constant(width, height, cx);
    Eigen::ArrayXXf cy_mat = Eigen::MatrixXf::Constant(width, height, cy);
    Eigen::ArrayXXf lambda_mat = Eigen::MatrixXf::Constant(width, height, lambda);

    Eigen::ArrayXXf X(width, height);
    Eigen::ArrayXXf Y(width, height);
    Eigen::ArrayXXf Z(width, height);

    for (int i = 0; i < width; i++) {
	    for (int j = 0; j < height; j++) {
            X(i, j) = i;
        }
    }

    for (int i = 0; i < width; i++) {
	    for (int j = 0; j < height; j++) {
            Y(i, j) = j;
        }
    }

    X = (X - cx_mat) / fx_mat;
    Y = (Y - cy_mat) / fy_mat;
    Z = 1 + lambda_mat * (((X - cx_mat) / fx_mat) * ((X - cx_mat) / fx_mat) + ((Y - cy_mat) / fy_mat) * ((Y - cy_mat) / fy_mat));


    return  std::make_tuple(X, Y, Z);
}


std::tuple<Eigen::ArrayXXf, Eigen::ArrayXXf> Projector::get2DCoordsfrom3D(Eigen::ArrayXXf X, Eigen::ArrayXXf Y, Eigen::ArrayXXf Z, int width, int height, float fx, float fy, float cx, float cy, float lambda) {
    Eigen::ArrayXXf fx_mat = Eigen::MatrixXf::Constant(width, height, fx);
    Eigen::ArrayXXf fy_mat = Eigen::MatrixXf::Constant(width, height, fy);
    Eigen::ArrayXXf cx_mat = Eigen::MatrixXf::Constant(width, height, cx);
    Eigen::ArrayXXf cy_mat = Eigen::MatrixXf::Constant(width, height, cy);
    Eigen::ArrayXXf lambda_mat = Eigen::MatrixXf::Constant(width, height, lambda);

    Eigen::ArrayXXf u(width, height);
    Eigen::ArrayXXf v(width, height);

    Eigen::ArrayXXf max_X_mat = Eigen::MatrixXf::Constant(width, height, X.maxCoeff());
    Eigen::ArrayXXf max_Y_mat = Eigen::MatrixXf::Constant(width, height, Y.maxCoeff());

    u = X / Z * fx_mat * (1 + lambda_mat * ((X / max_X_mat) * (X / max_X_mat) + (Y / max_Y_mat) * (Y / max_Y_mat))) + cx_mat;
    v = Y / Z * fy_mat * (1 + lambda_mat * ((X / max_X_mat) * (X / max_X_mat) + (Y / max_Y_mat) * (Y / max_Y_mat))) + cy_mat;

    return  std::make_tuple(u, v);
}



int main(int argc, char **argv) {

    cv::Mat img;
    int width;
    int height;
    std::string image_path;

    if(argc < 2){
        printf("Please add path to source image as parameter\n");
        return 1;
    }
    else {
        image_path = cv::samples::findFile(argv[1]);

        img = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
        if(img.empty()) {
            std::cout << "Could not read the image: " << image_path << std::endl;
            return 1;
        }
        // cv::imshow("Display window", img);
        // int k = cv::waitKey(0);

        width = img.cols;
        height = img.rows;
    }


    float fx1 = 10.0;
    float fy1 = 10.0;
    float cx1 = width / 2.0;
    float cy1 = height / 2.0;
    float lambda1 = 0.0;

    float fx2 = 5.0;
    float fy2 = 5.0;
    float cx2 = width / 2.0;
    float cy2 = height / 2.0;
    float lambda2 = 0.0;


    for(int counter = 0; counter < argc; ++counter){

        if (counter == 2) {
            fx1 = atof(argv[counter]);
        }

        if (counter == 3) {
            fy1 = atof(argv[counter]);
        }

        if (counter == 4) {
            if (atof(argv[counter]) != -1) {
                cx1 = atof(argv[counter]);
            }
        }

        if (counter == 5) {
            if (atof(argv[counter]) != -1) {
                cy1 = atof(argv[counter]);
            }
        }

        if (counter == 6) {
            lambda1 = atof(argv[counter]);
        }

        if (counter == 7) {
            fx2 = atof(argv[counter]);
        }

        if (counter == 8) {
            fy2 = atof(argv[counter]);
        }

        if (counter == 9) {
            if (atof(argv[counter]) != -1) {
                cx2 = atof(argv[counter]);
            }
        }

        if (counter == 10) {
            if (atof(argv[counter]) != -1) {
                cy2 = atof(argv[counter]);
            }
        }

        if (counter == 11) {
            lambda2 = atof(argv[counter]);
        }
    }

    Projector projector;
    projector.set_parameters (width, height, fx1, fy1, cx1, cy1, lambda1, fx2, fy2, cx2, cy2, lambda2);

    Eigen::ArrayXXf X(width, height);
    Eigen::ArrayXXf Y(width, height);
    Eigen::ArrayXXf Z(width, height);
    tie(X, Y, Z) = projector.get3DCoordsfrom2D(width, height, fx1, fy1, cx1, cy1, lambda1);

    Eigen::ArrayXXf u(width, height);
    Eigen::ArrayXXf v(width, height);
    tie(u, v) = projector.get2DCoordsfrom3D(X, Y, Z, width, height, fx2, fy2, cx2, cy2, lambda2);

    cv::Mat img_convert = cv::Mat::zeros(cv::Size(width, height), CV_8UC1);

    for (int i = 0; i < width; i++) {
	    for (int j = 0; j < height; j++) {
            img_convert.at<uchar>((int)v(i, j), (int)u(i, j)) = img.at<uchar>(j, i);
        }
    }

    std::string::size_type const p0(image_path.find_last_of('.'));
    std::string ext = image_path.substr(p0 + 1, image_path.length());
    std::string result_path = image_path.substr(0, p0) + "_result." + ext;
    cv::imwrite(result_path, img_convert);

    printf("\nSource image path: %s", image_path.c_str());
    printf("\nSource focal distance X: %.1f", fx1);
    printf("\nSource focal distance Y: %.1f", fy1);
    printf("\nSource optical center X: %.1f", cx1);
    printf("\nSource optical center Y: %.1f", cy1);
    printf("\nSource lambda: %.1f", lambda1);
    printf("\n\nTarget image path: %s", result_path.c_str());
    printf("\nTarget focal distance X: %.1f", fx2);
    printf("\nTarget focal distance Y: %.1f", fy2);
    printf("\nTarget optical center X: %.1f", cx2);
    printf("\nTarget optical center Y: %.1f", cy2);
    printf("\nTarget lambda: %.1f\n", lambda2);

    // cv::imshow("Result", img_convert);
    // int kk = cv::waitKey(0);

	return 0;
}