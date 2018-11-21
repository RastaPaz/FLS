//cpp includes
#include <stdio.h>
#include <string.h>
//sdk includes
#include <bvt_sdk.h>
//opencv2 includes
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;


int main( int argc, char *argv[] )
{

	/*
	int ret;
	// Create a new BVTSonar Object
	BVTSonar son = BVTSonar_Create();
	if( son == NULL )
	{
		printf("BVTSonar_Create: failed\n");
		return 1;
	}


	ret = BVTSonar_Open(son, "FILE", argv[1]);
	if( ret != 0 )
	{
		printf("BVTSonar_Open: ret=%d\n", ret);
		return 1;
	}

	// Make sure we have the right number of heads
	int heads = -1;
	BVTSonar_GetHeadCount(son, &heads);
	printf("BVTSonar_GetHeadCount: %d\n", heads);


	// Get the first head
	BVTHead head = NULL;
	ret = BVTSonar_GetHead(son, 0, &head);
	if( ret != 0 )
	{
		printf("BVTSonar_GetHead: ret=%d\n", ret);
		return 1;
	}

	// Check the ping count
	int pings = -1;
	BVTHead_GetPingCount(head, &pings);
	printf("BVTHead_GetPingCount: %d\n", pings);

   namedWindow( "Display window", WINDOW_AUTOSIZE); //create a window for display

    //Declaration of variables
    int height;
    int width;
    unsigned short* bitBuffer;

    for (int ping_num=1;ping_num<pings;ping_num++) {

    // Now, get a ping! (takes the num ping from the file)

    	BVTPing ping = NULL;
    	ret = BVTHead_GetPing(head, ping_num, &ping);
    	if( ret != 0 )
    	{
    		printf("BVTHead_GetPing: ret=%d\n", ret);
    		return 1;
    	}


    	// Generate an image from the ping
    	BVTImageGenerator ig = BVTImageGenerator_Create();
    	BVTImageGenerator_SetHead(ig, head);
    	BVTMagImage img;


    	ret = BVTImageGenerator_GetImageXY(ig, ping, &img);
    	if( ret != 0 )
    	{
    		printf("BVTImageGenerator_GetImageXY: ret=%d\n", ret);
    		return 1;
    	}

    	printf("\n");




    	// Check the image height and width out

    	BVTMagImage_GetHeight(img, &height);
    	printf("BVTMagImage_GetHeight: %d\n", height);

    	BVTMagImage_GetWidth(img, &width);
    	printf("BVTMagImage_GetWidth: %d\n", width);



    	BVTMagImage_GetBits(img, &bitBuffer);


    	Mat L (height,width,CV_16UC1, (void*)bitBuffer);

    	//////////////////////////////////////////////////////////////////////
    	///////////////////Conversation from num to string/////////////////////
    	//////////////////////////////////////////////////////////////////////

    	//Declaring output string stream
    	ostringstream str1;
    	//Sending number as stream into output string
    	str1 << ping_num;
    	//The str() converts number into string
    	string ping_str = str1.str();

    	/////Write Image to file
    	string filename = "a/Try" + ping_str + ".jpg";
    	imwrite (filename,L);


		//display image

    	imshow( "Display window", L ); //show the image

    	waitKey(1); //Display the image until user press a key

		// Clean up
	    //BVTColorImage_Destroy(cimg);
	    BVTMagImage_Destroy(img);
	    //BVTColorMapper_Destroy(mapper);
	    BVTPing_Destroy(ping);


    }
    BVTSonar_Destroy(son);
    return 0;
    */
	int ret;
	// Create a new BVTSonar Object
	BVTSonar son = BVTSonar_Create();

	if( son == NULL )
	{
		printf("BVTSonar_Create: failed\n");
		return 1;
	}

	ret = BVTSonar_Open(son, "FILE", argv[1]);
	if( ret != 0 )
	{
		printf("BVTSonar_Open: ret=%d\n", ret);
		return 1;
	}

	// Make sure we have the right number of heads
	int heads = -1;
	BVTSonar_GetHeadCount(son, &heads);
	printf("BVTSonar_GetHeadCount: %d\n", heads);


	// Get the first head
	BVTHead head = NULL;
	ret = BVTSonar_GetHead(son, 0, &head);
	if( ret != 0 )
	{
		printf("BVTSonar_GetHead: ret=%d\n", ret);
		return 1;
	}

	// Check the ping count
	int pings = -1;
	BVTHead_GetPingCount(head, &pings);
	printf("BVTHead_GetPingCount: %d\n", pings);

	//Open new window to display image
	namedWindow( "Display window", WINDOW_AUTOSIZE); //create a window for display

	//Declaration of variables
	int height;
	int width;
	unsigned int* bitBuffer;
	/////////////////////////////////////////////////////////

	// Build a color mapper
	BVTColorMapper mapper;
	mapper = BVTColorMapper_Create();
	if( mapper == NULL )
	{
		printf("BVTColorMapper_Create: failed\n");
	    return 1;
	}

	  // Load the bone colormap
	 ret = BVTColorMapper_Load(mapper, "colormaps/jet.cmap");
	 if( ret != 0 )
	    {
	    	printf("BVTColorMapper_Load: ret=%d\n", ret);
	    	return 1;
	   	}

	    for (int ping_num=1;ping_num<pings;ping_num++)
	    {

	    	// Now, get a ping! (takes the num ping from the file)

	    	BVTPing ping = NULL;
	    	ret = BVTHead_GetPing(head, ping_num, &ping);
	    	if( ret != 0 )
	    	{
	    		printf("BVTHead_GetPing: ret=%d\n", ret);
	    		return 1;
	    	}


	    // Generate an image from the ping
	    BVTImageGenerator ig = BVTImageGenerator_Create();
	    BVTImageGenerator_SetHead(ig, head);
	    BVTMagImage img;

	    ret = BVTImageGenerator_GetImageXY(ig, ping, &img);
	    if( ret != 0 )
	   	{
	    	printf("BVTImageGenerator_GetImageXY: ret=%d\n", ret);
	    	return 1;
	    }

	    printf("\n");

	  	// Perform the colormapping
	    BVTColorImage cimg;
	   	ret = BVTColorMapper_MapImage(mapper, img, &cimg);
	    if( ret != 0 )
	    {
	     	printf("BVTColorMapper_MapImage: ret=%d\n", ret);
	     	return 1;
	    }
	    printf("\n");

	    /////////////////////////////////////////////////////////
	    // Check the image height and width out
	    BVTColorImage_GetHeight(cimg, &height);
	    printf("BVTColorImage_GetHeight: %d\n", height);
	    BVTColorImage_GetWidth(cimg, &width);
	    printf("BVTColorImage_GetWidth: %d\n", width);

	    //Get a pointer to the entire image
	    BVTColorImage_GetBits(cimg, &bitBuffer);

	    //Load the image into opencv matrix
	    Mat L (height,width,CV_8UC4, (void*)bitBuffer);


	    //////////////////////////////////////////////////////////////////////
		///////////////////Conversation from num to string/////////////////////
		//////////////////////////////////////////////////////////////////////

		//Declaring output string stream
		ostringstream str1;
		//Sending number as stream into output string
		str1 << ping_num;
		//The str() converts number into string
		string ping_str = str1.str();

		/////Write Image to file
		string filename = "Test2_ColorPics/Try" + ping_str + ".ppm";
		imwrite (filename,L);


		//display image

		imshow( "Display window", L ); //show the image

		waitKey(1); //Display the image until user press a key


		//Clean up
	    BVTColorImage_Destroy(cimg);
	   	BVTPing_Destroy(ping);


		}
	    BVTColorMapper_Destroy(mapper);
	    BVTSonar_Destroy(son);
	    return 0;
}
