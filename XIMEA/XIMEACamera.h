/**
@brief Generic Camera Driver Class
Implementation of XIMEA camera
@author Shane Yuan
@date Dec 29, 2017
*/

#ifndef __GENERAL_CAMERA_DRIVER_XIMEA_HPP__
#define __GENERAL_CAMERA_DRIVER__XIMEA_HPP__

#include "GenCameraDriver.h"

#ifdef WIN32
#include <windows.h>
#include "xiApi.h"       // Windows
#else
#include <m3api/xiApi.h> // Linux, OSX
#endif
#include <memory.h>

namespace cam {

	// function to check XIMEA function error
	void checkXIMEAInternal(XI_RETURN result, char const *const func,
		const char *const file, int const line);

	// XIMEA function safe call
	#define checkXIMEAErrors(val)  checkXIMEAInternal ( (val), #val, __FILE__, __LINE__ )

	class GenCameraXIMEA : public GenCamera {
	private:
		std::vector<HANDLE> hcams;
		std::vector<XI_IMG> xiImages;
	public:

	private:
		

	public:
		GenCameraXIMEA();
		~GenCameraXIMEA();

		/***********************************************************/
		/*                   basic camera functions                */
		/***********************************************************/
		/**
		@brief init camera
		@return int
		*/
		int init() override;

		/**
		@brief get camera information
		@param std::vector<GenCamInfo> & camInfos: output camera infos
		@return int
		*/
		int getCamInfos(std::vector<GenCamInfo> & camInfos) override;

		/**
		@brief start capture images
		@return int
		*/
		int startCapture() override;

		/**
		@brief stop capture images
		@return int
		*/
		int stopCapture() override;

		/**
		@brief release camera
		@return int
		*/
		int release() override;

		/***********************************************************/
		/*                  camera setting functions               */
		/***********************************************************/
		/**
		@brief set frame rate
		@param float fps: input fps
		@return int
		*/
		int setFPS(int camInd, float fps) override;

		/**
		@brief set auto white balance
		@param int ind: index of camera (-1 means all the cameras)
		@return int
		*/
		int setAutoWhiteBalance(int camInd) override;

		/**
		@brief set auto white balance
		@param int ind: index of camera (-1 means all the cameras)
		@param float redGain: red gain of the white balance
		@param float greenGain: green gain of the white balance
		@param float blueGain: blue gain of the white balance
		@return int
		*/
		int setWhiteBalance(int camInd, float redGain,
			float greenGain, float blueGain) override;

		/**
		@brief set auto exposure
		@param int ind: index of camera (-1 means all the cameras)
		@param Status autoExposure: if use auto exposure 
		@return int
		*/
		int setAutoExposure(int camInd, Status autoExposure) override;

		/**
		@brief set auto exposure level
		@param int ind: index of camera (-1 means all the cameras)
		@param float level: auto exposure level, average intensity of output
		signal AEAG should achieve
		@return int
		*/
		int setAutoExposureLevel(int camInd, float level) override;

		/**
		@brief set auto exposure compensation (only support PointGrey cameras)
		@param int ind: index of camera (-1 means all the cameras)
		@param Status status: if use auto EV value
		@param float relativeEV: only valid when the second argument is off.
		The reason why use relative EV value here is to directly set a absolute
		value is difficult
		@return int
		*/
		int setAutoExposureCompensation(int camInd,
			Status status, float relativeEV) override;

		/**
		@brief set exposure time
		@param int ind: index of camera (-1 means all the cameras)
		@param int time: exposure time (in microseconds)
		@return int
		*/
		int setExposure(int camInd, int time) override;

		/**
		@brief set/get bayer pattern
		@param int camInd: input camera index
		@param GenCamBayerPattern & bayerPattern: output bayer pattern
		@return int
		*/
		int getBayerPattern(int camInd, GenCamBayerPattern & bayerPattern) override;

		/**
		@brief make setting effective
		by capturing some frames
		@param int k: capture image frames (default is 10)
		@return int
		*/
		int makeSetEffective(int k = 10) override;

		/*************************************************************/
		/*                     capturing function                    */
		/*************************************************************/
		/**
		@brief capture single image of single camera in camera array
		@param int camInd: input index of camera
		@param cv::Mat & img: output captured images (pre-allocated memory)
		@return int
		*/
		int captureFrame(int camInd, cv::Mat & img) override;


	};

};

#endif