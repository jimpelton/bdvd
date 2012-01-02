/********************************************************************
	filename: 	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer\UIMain.h
	file path:	C:\Users\jim\Documents\programming\VTK\vs\VolumeViewer\VolumeViewer
	file base:	UIMain
	file ext:	h
	author:		jim
	
	purpose:	Text UI for VolumeViewer class. Specifically for volume renderings.
*********************************************************************/
#ifndef UIMAIN_H_
#define UIMAIN_H_

#include "VolumeViewer.h"


#include <vector>
#include <string>
#include <queue>
//#include <list>

class VolumeViewer;

class UIMain
{

private:
	enum COMMAND { QUIT, SET, CLEAR, VSET, PRINT };
	std::vector<std::string> *cmdStrs;

	enum TARGET  { LIGHTING, TRANSFER };
	std::vector<std::string> *targStrs;

	enum LT_TARG_TYPE { AMBIENT, DIFFUSE, SPECULAR };
	std::vector<std::string> *lt_TargStrs;

	enum TR_TARG_TYPE { SCALAR, GRADIENT, COLOR };
	std::vector<std::string> *tr_TargStrs;

	VolumeViewer *myVolume;
	
	std::queue<int>   *cmdQueue;
	std::queue<float> *floatQueue;

	bool running;

	void waitForCmd();
	int matchCmd(std::string cmd);
	
	/**
	 * Parse the queue and set the lighting values specified.
	 * Private helper for matchCmd(), probably not any reason for
	 * the user to call this function.
	 */
	void setLighting(std::queue<std::string> *, std::string *);
	/**
	 *	set the ambient lighting for the volumeviewer.
	 */
	void setAmbient( float val );
	/**
	 *	set the diffuse lighting for the volumeviewer.
	 */
	void setDiffuse( float val );
	/**
	 *	set the specular lighting for the volumeviewer.
	 */
	void setSpecular(float val );


	void setTransfer(std::queue<std::string> *, std::string *);
	void clearTransfer(std::queue<std::string> *, std::string *);

	/**
	 *	add/replace a point (x, val) to the scalar opacity transfer function
	 */
	void setTransScalar(float x, float val);
	void clearTransScalar(float x);
	/**
	 *	add/replace a point (x, val) to the gradient opacity transfer function
	 */
	void setTransGrad(float x, float val);
	void clearTransGrad(float x);
	/**
	 *	add/replace a point (x, r, g, b) to the RGB transfer function
	 */
	void setTransColor(float x, float r, float g, float b);
	void clearTransColor(float x);

	void printLighting();
	void printLighting(std::string *);

	/**
	 * print all transform functions.
	 * Currently not implemented...will it ever be? We may never know!
	 */
	void printTransform();	
	/**
	 *	parse the queue and print the spec'd transfer function.
	 *	Private helper method for matchCmd(), probably not any reason for
	 *	the user to call this function.
	 */
	void printTransform(std::queue<std::string> * strqueue, std::string * tok);
	/**
	 *	print the scalar opacity value for this scalar value (x).
	 */
	void printScalarTransform(float x);
	/**
	 *	print the color RGB values for the given scalar value (x).
	 */
	void printColorTransform(float x);
	/**
	 *	print the gradient opacity value for the given scalar value (x).
	 */
	void printGradientTransform(float);

	/**
	 *	helpers for advancing parsing
	 */
	float getNextf(std::queue<std::string> * strqueue, std::string * tok);
	void  getNextToken(std::queue<std::string> * strqueue, std::string * tok);
public:
	UIMain(void);
	~UIMain(void);

	/**
	 *	Start listening for a command. This blocks VTK operations (except for
	 *	render updates) until 'quit' command is given. Then returns to VTK.
	 */
	int Start();

	/**
	 *	Set the volumeviewer that this UIMain with interface with.
	 */
	void SetVolumeViewer(VolumeViewer *);
	
};

#endif