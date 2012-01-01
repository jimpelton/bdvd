/*
 * ViewerOptions.h
 *
 *  Created on: Dec 20, 2011
 *      Author: jim
 */

#ifndef VIEWEROPTIONS_H_
#define VIEWEROPTIONS_H_

namespace OpMode {
	enum e {
		EXTRACT_AND_VIEW_SURFACE,
		EXTRACT_BATCH,
		VIEW_POLYDATA,
		VIEW_VOLUME,
		PLOT_VIEW_TRIANGLE_AVERAGES,
		PLOT_VIEW_SURFACE_AREAS,
		PLOTS_TRIANGLE_AVERAGES,
		PLOTS_BATCH_TRIANGLE_AVERAGES,
		PLOTS_BATCH_SURFACE_AREAS
	};


}
struct ViewerOptions
{
	int mode;
	char *outDir;
};


#endif /* VIEWEROPTIONS_H_ */
