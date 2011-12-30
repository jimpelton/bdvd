/*
 * ViewerOptions.h
 *
 *  Created on: Dec 20, 2011
 *      Author: jim
 */

#ifndef VIEWEROPTIONS_H_
#define VIEWEROPTIONS_H_

enum OpMode { OPMODE_EXTRACT_AND_VIEW_SURFACE, OPMODE_VIEW_POLYDATA, OPMODE_BATCH_EXTRACT, OPMODE_VIEW_PLOTS, OPMODE_VIEW_VOLUME };

struct ViewerOptions
{
	OpMode mode;
};


#endif /* VIEWEROPTIONS_H_ */
