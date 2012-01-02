#include "UIMain.h"
#include <string>
#include <iostream>
#include <sstream>

using std::string;
using std::queue;


UIMain::UIMain(void)
{
	cmdQueue = new queue<int>();
	floatQueue = new queue<float>();

	cmdStrs = new vector<string>();
	cmdStrs->push_back("quit");
	cmdStrs->push_back("set");
	cmdStrs->push_back("clear");
	cmdStrs->push_back("vset");
	cmdStrs->push_back("print");

	targStrs = new vector<string>();
	targStrs->push_back("lighting");
	targStrs->push_back("transfer");
	
	lt_TargStrs = new vector<string>();
	lt_TargStrs->push_back( "ambient" );
	lt_TargStrs->push_back( "diffuse" );
	lt_TargStrs->push_back( "specular");
			  	 
	tr_TargStrs = new vector<string>();
	tr_TargStrs->push_back( "scalar"  );
	tr_TargStrs->push_back( "gradient");
	tr_TargStrs->push_back( "color"   );

}


UIMain::~UIMain(void)
{
	delete cmdQueue;
	delete floatQueue;
	delete cmdStrs;
	delete targStrs;
	delete lt_TargStrs;
	delete tr_TargStrs;
}

int UIMain::Start()
{
	running = true;
	waitForCmd();
	running = false;
	return 0;
}

void UIMain::waitForCmd()
{
	string cmd;
	int res = 1;
	while (res != -1) {
		fprintf(stdout, "\nVV ? ");
		getline(cin, cmd);
		fprintf(stdout, "cmd is: %s\n", cmd.c_str());
		res = matchCmd(cmd);
		//if (res == -1){ break; }
	}
}

int UIMain::matchCmd(string cmd)
{
	queue<string> strqueue;

	std::istringstream ss(cmd);
	while ( ss ){
		string yup;
		ss >> yup;
		strqueue.push(yup);
	}	
		
	string tok = strqueue.front();
	
	if (tok.compare( cmdStrs->at(QUIT) ) == 0 ||
		tok.compare("q") == 0 ){
		fprintf(stdout, "Returning to VTK.\n");
		return -1;
	}

	if (tok.compare( cmdStrs->at(SET) ) == 0){                          //set branch
		getNextToken(&strqueue, &tok);
		if (tok.compare( targStrs->at(LIGHTING) ) == 0){     
			getNextToken(&strqueue, &tok);
			setLighting(&strqueue, &tok);
		}else
		if (tok.compare( targStrs->at(TRANSFER) ) == 0){     
			getNextToken(&strqueue, &tok);                     
			setTransfer(&strqueue, &tok);
		}
	}else               	
	if (tok.compare( cmdStrs->at(CLEAR) ) == 0){                          //clear branch
		getNextToken(&strqueue, &tok);
		if (tok.compare( targStrs->at(TRANSFER) ) == 0){
			getNextToken(&strqueue, &tok);
			clearTransfer(&strqueue, &tok);
		}
	}else
	if (tok.compare( cmdStrs->at(PRINT) ) ==0){                          //print branch
		getNextToken(&strqueue, &tok);
		if (tok.compare( targStrs->at(LIGHTING)) == 0){
			getNextToken(&strqueue, &tok);
			if (tok.empty()){ printLighting(); }   
			else { printLighting( &tok ); }
		}
		if (tok.compare( targStrs->at(TRANSFER) ) == 0){
			getNextToken(&strqueue, &tok);
			if (tok.empty()) { printTransform(); }
			else { printTransform( &strqueue, &tok ); }
		}
	}
	return 0;
}

float UIMain::getNextf(queue<string> * strqueue, string * tok)
{
	getNextToken(strqueue, tok);
	if (tok->empty()) return -1.f;
	float f = atof(tok->c_str());
	return f;
}

void UIMain::getNextToken(queue<string> * strqueue, string * tok)
{
	strqueue->pop();
	*tok = strqueue->front();
}



/************************************************************************
 * PRINT methods                                                                   
************************************************************************/

void UIMain::printLighting()
{
	fprintf(stdout, "Ambient: %.2f\nDiffuse: %.2f\nSpecular: %.2f\n", 
		myVolume->Ambient(), myVolume->Diffuse(), myVolume->Specular());
}

void UIMain::printLighting(string *tok)
{
	if (tok->compare( lt_TargStrs->at(AMBIENT) ) == 0){
		fprintf(stdout, "Ambient: %.2f\n", myVolume->Ambient());
	}else if (tok->compare( lt_TargStrs->at(DIFFUSE) ) == 0){
		fprintf(stdout, "Diffuse: %.2f\n", myVolume->Diffuse());
	}else if (tok->compare( lt_TargStrs->at(SPECULAR) ) == 0){
		fprintf(stdout, "Specular: %.2f\n", myVolume->Specular());
	}
}



void UIMain::printTransform()
{
	fprintf(stdout, "You must spec. a transfer function type, eg., color, gradient or scalar.\nAlso, an optional scalar level can be given.");
}

void UIMain::printTransform(queue<string> *strqueue, string *tok)
{
	if (tok->compare( tr_TargStrs->at(COLOR) ) == 0){    //3a.
		float id = getNextf(strqueue, tok);
		printColorTransform(id); 
	}else
	if (tok->compare( tr_TargStrs->at(SCALAR) ) == 0){    //3b.
		float id = getNextf(strqueue, tok);
		printScalarTransform(id); 
	}else
	if (tok->compare( tr_TargStrs->at(GRADIENT) ) == 0){   //3c.
		float id = getNextf(strqueue, tok);
		printGradientTransform(id); 
	}			
}



void UIMain::printColorTransform(float id)
{
	vtkColorTransferFunction *pf = myVolume->VolumeProperty()->GetRGBTransferFunction();

	if (id == -1){
		//fprintf(stdout, "Print all color transfer nodes functionality not implemented.\n");
		pf->Print(cout);
	}else{
		
		double col[3];
		pf->GetColor(id, col);
		fprintf(stdout, "S: %.2f R: %.2f G: %.2f B: %.2f\n", id, col[0], col[1], col[2]);
	}
}

void UIMain::printScalarTransform(float id)
{
	vtkPiecewiseFunction *pf = myVolume->VolumeProperty()->GetScalarOpacity();
	if (id == -1){
		//fprintf(stdout, "Print all scalar transfer nodes functionality not implemented.\n");
		pf->Print(cout);
	}else{
		
		double v = pf->GetValue(id);
		fprintf(stdout, "S: %.2f V: %.2f\n", id, v);
	}
}

void UIMain::printGradientTransform(float id)
{
	vtkPiecewiseFunction *pf = myVolume->VolumeProperty()->GetGradientOpacity();
	if (id == -1){
	//	fprintf(stdout, "Print all gradient transfer nodes functionality not implemented.\n");
		pf->Print(cout);
	}else{
		
		double v = pf->GetValue(id);
		fprintf(stdout, "S: %.2f V: %.2f\n", id, v);
	}
}



/************************************************************************
 * SET/CLEAR methods                                                                 
************************************************************************/

void UIMain::setLighting(queue<string> * strqueue, string * tok)
{
	if (tok->compare( lt_TargStrs->at(AMBIENT) ) == 0){    //3a.
		strqueue->pop();
		*tok = strqueue->front();
		setAmbient(atof(tok->c_str()));
	}else
	if (tok->compare( lt_TargStrs->at(DIFFUSE) ) == 0){    //3b.
		strqueue->pop();
		*tok = strqueue->front();
		setDiffuse(atof(tok->c_str()));
	}else
	if (tok->compare( lt_TargStrs->at(SPECULAR) ) == 0){   //3c.
		strqueue->pop();
		*tok = strqueue->front();
		setSpecular(atof(tok->c_str()));
	}			
}

void UIMain::setAmbient(  float val )
{
	//fprintf(stdout, "%s, %f\n", __FUNCTION__ , val);
	myVolume->Ambient(val);
}

void UIMain::setDiffuse( float val )
{
	//fprintf(stdout, "%s, %f\n", __FUNCTION__ , val);
	myVolume->Diffuse(val);
}

void UIMain::setSpecular(float val )
{
	//fprintf(stdout, "%s, %f\n", __FUNCTION__ , val);
	myVolume->Specular(val);
}


void UIMain::setTransfer(queue<string> * strqueue, string * tok)
{
	if (tok->compare( tr_TargStrs->at(SCALAR) ) == 0){          
		float x   = getNextf(strqueue, tok);
		float val = getNextf(strqueue, tok);
		setTransScalar(x,val);
	}else
	if (tok->compare( tr_TargStrs->at(GRADIENT) ) == 0){  
		float x   = getNextf(strqueue, tok);
		float val = getNextf(strqueue, tok);
		setTransGrad(x, val);
	}else
	if (tok->compare( tr_TargStrs->at(COLOR) ) == 0){    
		float x = getNextf(strqueue, tok);
		float r = getNextf(strqueue, tok);
		float g = getNextf(strqueue, tok);
		float b = getNextf(strqueue, tok);
		setTransColor(x,r,g,b);
	} 
}

void UIMain::clearTransfer(queue<string> * strqueue, string * tok)
{
	if (tok->compare( tr_TargStrs->at(SCALAR) ) == 0){
		float x = getNextf(strqueue, tok);
		clearTransScalar(x);
	}else
	if (tok->compare( tr_TargStrs->at(GRADIENT) ) == 0){
		float x = getNextf(strqueue, tok);
		clearTransGrad(x);
	}else
	if (tok->compare( tr_TargStrs->at(COLOR) ) == 0){
		float x = getNextf(strqueue, tok);
		clearTransColor(x);
	}
}

void UIMain::setTransColor(float x, float r, float g, float b)
{
	//fprintf(stdout, "%s, %f %f %f %f\n", __FUNCTION__ , x,r,g,b);
	myVolume->SetColorTransFunc(x, r, g, b);
}

void UIMain::clearTransColor(float x)
{
	myVolume->ClearColorTransFunc(x);
}




void UIMain::setTransGrad(float x, float val)
{
	//fprintf(stdout, "%s, %f %f\n", __FUNCTION__ , x, val);
	myVolume->SetGradientTransFunc(x, val);
}

void UIMain::clearTransGrad(float x)
{
	myVolume->ClearGradientTransFunc(x);
}




void UIMain::setTransScalar(float x, float val)
{
	//fprintf(stdout, "%s, %f %f\n", __FUNCTION__ , x, val);
	myVolume->SetScalarTransFunc(x, val);
}

void UIMain::clearTransScalar(float x)
{
	myVolume->ClearScalarTransFunc(x);
}

void UIMain::SetVolumeViewer(VolumeViewer *viewer)
{
	myVolume = viewer;
}

//void UIMain::matchCmd( string cmd )
	//{
	//	fprintf(stdout, "matchCmd: %s\n", cmd.c_str());
	//	if      (cmd.compare( cmdStrs->at(SET)  )   == 0) cmdQueue->push(SET);
	//	else if (cmd.compare( cmdStrs->at(CLEAR)) == 0)   cmdQueue->push(CLEAR);
	//	else if (cmd.compare( cmdStrs->at(VSET) )  == 0)  cmdQueue->push(VSET);
	//}
	//
	//void UIMain::matchTgt( string cmd )
	//{
	//	fprintf(stdout, "matchTgt: %s\n", cmd.c_str());
	//	if      (cmd.compare( targStrs->at(LIGHTING) ) == 0) cmdQueue->push(LIGHTING);
	//	else if (cmd.compare( targStrs->at(TRANSFER) ) == 0) cmdQueue->push(TRANSFER);
	//	
	//}
	//
	//void UIMain::matchLT( string cmd )
	//{
	//	fprintf(stdout, "matchLt: %s\n", cmd.c_str());
	//	if      (cmd.compare( lt_TargStrs->at(AMBIENT) ) == 0) cmdQueue->push(AMBIENT);
	//	else if (cmd.compare( lt_TargStrs->at(DIFFUSE) ) == 0) cmdQueue->push(DIFFUSE);
	//	else if (cmd.compare( lt_TargStrs->at(SPECULAR) )== 0) cmdQueue->push(SPECULAR);
	//}
	//
	//void UIMain::matchTR( string cmd )
	//{
	//	fprintf(stdout, "matchTr: %s\n", cmd.c_str());
	//	if      (cmd.compare( tr_TargStrs->at(SCALAR) )   == 0) cmdQueue->push(SCALAR);
	//	else if (cmd.compare( tr_TargStrs->at(GRADIENT) ) == 0) cmdQueue->push(GRADIENT);
	//	else if (cmd.compare( tr_TargStrs->at(COLOR) )  == 0)   cmdQueue->push(COLOR);
	//}
	//
	//void UIMain::matchArgs( string cmd )
	//{
	//	fprintf(stdout, "matchArgs: %s\n", cmd.c_str());
	//	istringstream ss(cmd);
	//	int i = 0;
	//	while ( ss ){
	//		string yup;
	//		ss >> yup;
	//		if (! yup.empty()){
	//			float f = stof(yup);
	//			floatQueue->push(f);
	//		}
	//	}	
	//}
	//} 
//void  UIMain::match(string cmd, int found)
//{
//
//	switch (found)
//	{
//	case 0:
//		matchCmd(cmd);
//		break;
//	case 1:
//		matchTgt(cmd);
//		break;
//	case 2:
//		matchLT(cmd);
//		break;
//	case 3:
//		matchTR(cmd);
//		break;
//	default:
//		matchArgs(cmd);
//		break;
//	}
//	
//
//}

