#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

IplImage *src, *templ,*frame;
        char* filename0 = "finger.jpg";

        CvCapture *capture = cvCreateCameraCapture(0);


        if((templ=cvLoadImage(filename0, 1))== 0) {
                printf("Error on reading template %s\n",filename0);
                return(-1);
        }
         src = cvQueryFrame(capture);
		int patchx = templ->width;
        int patchy = templ->height;
        int iwidth = src->width - patchx + 1;
        int iheight = src->height - patchy + 1;
        frame = cvCreateImage( cvSize(iwidth,iheight),32,1);
         double    minval, maxval;
        CvPoint    minloc, maxloc;


		cvNamedWindow( "frame",CV_WINDOW_AUTOSIZE);
		while(1){
		src = cvQueryFrame(capture);

		cvMatchTemplate( src, templ, frame, 1);
		cvMinMaxLoc(frame, &minval, &maxval, &minloc, &maxloc, 0);
        //cvNormalize(frame,frame,1,0,CV_MINMAX,0);

        cvRectangle(src, cvPoint(minloc.x, minloc.y), cvPoint(minloc.x+templ->width-1, minloc.y+templ->height-1), CV_RGB(255, 0, 0), 1, 8,0);



        cvShowImage(   "frame", src );
        char c = cvWaitKey(100);
        if(c == 27)break;
	}
