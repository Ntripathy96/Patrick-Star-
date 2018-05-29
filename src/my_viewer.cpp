
# include "my_viewer.h"
# include <sigogl/ui_dialogs.h>
# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>
# include <cmath>
# include <sigogl/ws_run.h>
const float pi = 3.14159265359f;
//FLOAT VARS
float upperarmrotation = 0; float lowerarmrotation = 0; float wristrotation = 0; float rotaterightfin = 0; float rightlegmove = 0;
float leftlegmove = 0;
bool addsecondarm = false;
float leftfinmove = 0;
float iterator = 0;
float torsoit = 0;
float fullbodyit = 0;
//BOOL VARS
bool fullarmmove = false;
bool elbowmove = false;
bool wristmove = false;
bool FINMOVETORIGHT = false;
bool rotpat = false;
bool linearly = false;
bool LEGTOMOVERIGHT = false; 
bool LEGTOMOVELEFT = false; 
bool FINTOMOVELEFT = false; 
bool TORSOMOVE = false; 
bool TURNAROUND = false; 

// Global Patrick Positioning System (GPPS)
double patrickX = 0.0;
double patrickY = 65.0;
double patrickZ = 0.0;
float eye = 0.0;
float v = 0.0;

MyViewer::MyViewer(int x, int y, int w, int h, const char* l) : WsViewer(x, y, w, h, l)
{
	_nbut = 0;
	_animating = false;
	build_ui();
	build_scene();
}

void MyViewer::build_ui()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel("", UiPanel::HorizLeft);
	p->add(new UiButton("View", sp = new UiPanel()));
	{	UiPanel* p = sp;
	p->add(_nbut = new UiCheckButton("Normals", EvNormals));
	}
	p->add(new UiButton("Animate", EvAnimate));
	p->add(new UiButton("Exit", EvExit)); p->top()->separate();
}

void MyViewer::add_model(SnShape* s, GsVec p)
{
	SnManipulator* manip = new SnManipulator;
	GsMat m;
	GsMat r;
	m.translation(p);
	manip->initial_mat(m);
	SnManipulator* shadow = new SnManipulator;
	GsMat shad;

	shad.setl1(1, -8 / 5, 0, 0);
	shad.setl2(0, 0, 0, 0);
	shad.setl3(0, -20 / 5, 1, 0);
	shad.setl4(0, 0, 0, 1);
	shad.rcombtrans(p);

	shadow->initial_mat(shad);

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);
	shadow->child(g);
	rootg()->add(manip);
	rootg()->add(shadow);

}
void MyViewer::build_scene()
{
	// Re-initialize the scene before drawing.
	rootg()->remove_all();




	SnModel *grass = new SnModel;//grass
	grass->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\grass.obj");
	grass->color(GsColor::green);
	rootg()->add(grass); 



	SnModel *patricktorso = new SnModel;
	patricktorso->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\torso.obj");
	GsModel* PatModel = patricktorso->model();
	PatModel->scale(35);
	add_model(patricktorso, GsVec(patrickX, patrickY, patrickZ));  


	SnModel *patrickrightfin = new SnModel;
	patrickrightfin->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\patrickrightfin.obj");
	GsModel* PatModel2 = patrickrightfin->model();
	PatModel2->scale(35);
	add_model(patrickrightfin, GsVec(patrickX, patrickY, patrickZ));

	SnModel *patrickleftfin = new SnModel;//grass
	patrickleftfin->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\patrickleftfin.obj");
	GsModel* PatModel3 = patrickleftfin->model();
	PatModel3->scale(35);
	add_model(patrickleftfin, GsVec(patrickX, patrickY, patrickZ)); 

	SnModel *patrickleftleg = new SnModel;
	patrickleftleg->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\patrickleftleg.obj");
	GsModel* PatModel4 = patrickleftleg->model();
	PatModel4->scale(35);
	add_model(patrickleftleg, GsVec(patrickX, patrickY, patrickZ));

	SnModel *patrickrightleg = new SnModel;
	patrickrightleg->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\patrickrightleg.obj");
	GsModel* PatModel5 = patrickrightleg->model();
	PatModel5->scale(35);
	add_model(patrickrightleg, GsVec(patrickX, patrickY, patrickZ));

	SnModel *tree = new SnModel;
	tree->model()->load_obj("C:\\Users\\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\rose.obj");
	GsModel* TreeModel = tree->model();
	TreeModel->scale(2.1f);
	add_model(tree, GsVec(125.0f, 0.0f, -95.0f));








															 /*SnModel *sword = new SnModel;
															 sword->model()->load_obj("C:\\Users\ntripathy\\Documents\\CSE170Project1\\sigapp\\arm\\Sting-Sword-lowpoly.obj");
															 add_model(sword, GsVec(1, 1, 0));*/


}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation()
{
	/*addsecondarm = true;
	if (addsecondarm)
	{
	//iterator = 0.5f;
	//build_scene();
	}*/
	/*while (upperarmrotation < 1.57f) {
		GsEvent goarmup; goarmup.key = 'q';
		handle_keyboard(goarmup);


	}//starts by moving entire arm upwards by calling "q" (iterates by pi/64 upwards)

	while (lowerarmrotation < 2.0f) {
		GsEvent goarmup; goarmup.key = 'w';
		handle_keyboard(goarmup);

	}//calls to move elbow upwards 

	while (lowerarmrotation > 0.39f) {
		GsEvent goarmdown; goarmdown.key = 's';
		handle_keyboard(goarmdown);

	}//calls to move elbow back down 

	while (lowerarmrotation > 0.39f) {
		GsEvent goarmdown;	goarmdown.key = 's';
		handle_keyboard(goarmdown);

	}//repeat to move waving motion 

	while (lowerarmrotation < 2.0f) {
		GsEvent goarmup; goarmup.key = 'w';
		handle_keyboard(goarmup);

	}
	while (lowerarmrotation > 0.39f) {
		GsEvent goarmdown; goarmdown.key = 's';
		handle_keyboard(goarmdown);

	}//repeat to make waving motion 


	while (upperarmrotation> 0.0f) {
		GsEvent goarmdown; goarmdown.key = 'a';
		handle_keyboard(goarmdown);

	}//move back to origin 


	*/
}

void MyViewer::show_normals(bool b)
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for (int k = 0; k<r->size(); k++)
	{
		SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if (!b) { l->visible(false); continue; }
		l->visible(true);
		if (!l->empty()) continue; // build only once
		l->init();
		if (s->instance_name() == SnPrimitive::class_name)
		{
			GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face(fn);
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for (int i = 0; i<m.F.size(); i++)
			{
				const GsVec& a = m.V[m.F[i].a]; l->push(a, a + (*n++)*f);
				const GsVec& b = m.V[m.F[i].b]; l->push(b, b + (*n++)*f);
				const GsVec& c = m.V[m.F[i].c]; l->push(c, c + (*n++)*f);
			}
		}
	}
}
void MyViewer::ARM_MOVEMENT(float incrementer)
{
	//ALL MANIPULATORS FOR ROTATION/TRANSLATION/MATRIX MANIPULATION ARE DECLARED HERE
      SnManipulator* upmanip = rootg()->get<SnManipulator>(0); // access manipulator for each segment of the arm (upper, lower, and hand) 
	GsMat upperarmmove = upmanip->mat();
	SnManipulator* lowmanip = rootg()->get<SnManipulator>(1);
	GsMat lowerarmmove = lowmanip->mat();
	SnManipulator* handmanip = rootg()->get<SnManipulator>(2);
	GsMat handmove = handmanip->mat();
	GsMat tr;//translation
	GsMat rot;
	if (fullarmmove)
	{

		//for the upperarm to move 
		upperarmrotation += incrementer; //increment by pi/64 around the axis when passed into function
		tr.translation(GsVec(0, 0, 0));
		upperarmmove.rotz(upperarmrotation);
		upperarmmove.mult(tr, upperarmmove);
		upmanip->initial_mat(upperarmmove);
		render();
		ws_check();


		//lower arm to move 			
		lowerarmmove.rotz(upperarmrotation);
		lowerarmmove.rcombtrans(GsVec(60, -12, 0));
		lowmanip->initial_mat(lowerarmmove);
		render();
		ws_check();

		//hand to move 
		handmove.rotz(upperarmrotation);
		handmove.rcombtrans(GsVec(110, 4, 0));
		handmanip->initial_mat(handmove);
		render();
		ws_check();
	}

	if (elbowmove)
	{
		//for forearm
		lowerarmrotation += incrementer;
		lowerarmmove.rotz(lowerarmrotation);
		tr.translation(GsVec(0, 0, 0));//create translation for lower arm to stay in place 
		lowerarmmove.mult(tr, lowerarmmove);
		rot.rotz(upperarmrotation);
		rot.rcombtrans(GsVec(60, -12, 0));
		lowerarmmove.mult(rot, lowerarmmove);
		lowmanip->initial_mat(lowerarmmove);
		render();
		ws_check();

		//for hand 
		handmove.rotz(lowerarmrotation / 64);
		handmove.rcombtrans(GsVec(57, 12, 0));
		handmove.mult(lowerarmmove, handmove);
		handmanip->initial_mat(handmove);
		render();
		ws_check();
	}
	if (wristmove)
	{
		//just accounts for hand 
		GsMat tr;
		wristrotation += incrementer;
		tr.translation(GsVec(57, 14, 0));
		handmove.rotz(wristrotation);
		handmove.mult(tr, handmove);
		handmove.mult(lowerarmmove, handmove);
		handmanip->initial_mat(handmove);
		render();
		ws_check();
	}
}


void MyViewer::movePatrick(double x, double y, double z)
{
	// Get the manipulator and matrix.
	SnManipulator* patrickManip = rootg()->get<SnManipulator>(3); // right arm
	GsMat patrickMatrix = patrickManip->mat();

	SnManipulator* patrickManip2 = rootg()->get<SnManipulator>(1); //torso
	GsMat patrickMatrix2 = patrickManip2->mat();

	SnManipulator* patrickManip3 = rootg()->get<SnManipulator>(5); //left arm
	GsMat patrickMatrix3 = patrickManip3->mat();

	SnManipulator* patrickManip4 = rootg()->get<SnManipulator>(7);//left leg
	GsMat patrickMatrix4 = patrickManip4->mat();

	SnManipulator* patrickManip5 = rootg()->get<SnManipulator>(9);//right leg
	GsMat patrickMatrix5 = patrickManip5->mat();

	// Get Patrick's current coordinates, and adjust them.
	camera().center.x += float (x);
	camera().center.y += float(y);
	camera().center.z += float(z);
	patrickX += x;
	patrickY += y;
	patrickZ += z;

	if (FINMOVETORIGHT)
	{
		//just accounts for hand 
		GsMat rightfinyy;
		//while (rotaterightfin < (2 * (gspi / 360)))
		//{
			rightfinyy.translation(GsVec(patrickX, patrickY, patrickZ));
			patrickMatrix3.rotz(rotaterightfin);
			patrickMatrix3.mult(rightfinyy, patrickMatrix3);
			//handmove.mult(lowerarmmove, patrickMatrix3);
			patrickManip3->initial_mat(patrickMatrix3);
			render();
			ws_check();
		//}
	}

	if (LEGTOMOVERIGHT)
	{
		GsMat rightleg;
		//while (rotaterightfin < (2 * (gspi / 360)))
		//{
		rightleg.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix5.rotz(rightlegmove);
		patrickMatrix5.mult(rightleg, patrickMatrix5);
		//handmove.mult(lowerarmmove, patrickMatrix3);
		patrickManip5->initial_mat(patrickMatrix5);
		render();
		ws_check();
	}

	if (LEGTOMOVELEFT)
	{
		GsMat leftleg ;
		//while (rotaterightfin < (2 * (gspi / 360)))
		//{
		leftleg.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix4.rotz(leftlegmove);
		patrickMatrix4.mult(leftleg, patrickMatrix4);
		//handmove.mult(lowerarmmove, patrickMatrix3);
		patrickManip4->initial_mat(patrickMatrix4);
		render();
		ws_check();
	}

	if (FINTOMOVELEFT)
	{ 
		GsMat leftfinyy;
		//while (rotaterightfin < (2 * (gspi / 360)))
		//{
		leftfinyy.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix.rotz(leftfinmove);
		patrickMatrix.mult(leftfinyy, patrickMatrix);
		//handmove.mult(lowerarmmove, patrickMatrix3);
		patrickManip->initial_mat(patrickMatrix);
		render();
		ws_check();
	}

	if (TORSOMOVE)
	{
		GsMat movetorso; 
		movetorso.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix2.roty(torsoit);
		patrickMatrix2.mult(movetorso, patrickMatrix2);
		patrickManip2->initial_mat(patrickMatrix2);
		render(); 
		ws_check();
	}

	if (TURNAROUND)
	{
		GsMat newbody;
		newbody.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix.roty(fullbodyit);
		patrickMatrix.mult(newbody, patrickMatrix);
		patrickManip->initial_mat(patrickMatrix);

		GsMat newbody2;
		newbody2.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix2.roty(fullbodyit);
		patrickMatrix2.mult(newbody2, patrickMatrix2);
		patrickManip->initial_mat(patrickMatrix2);

		GsMat newbody3;
		newbody3.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix3.roty(fullbodyit);
		patrickMatrix3.mult(newbody3, patrickMatrix3);
		patrickManip->initial_mat(patrickMatrix3);

		GsMat newbody4;
		newbody4.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix4.roty(fullbodyit);
		patrickMatrix4.mult(newbody4, patrickMatrix4);
		patrickManip->initial_mat(patrickMatrix4);

		GsMat newbody5;
		newbody5.translation(GsVec(patrickX, patrickY, patrickZ));
		patrickMatrix5.roty(fullbodyit);
		patrickMatrix5.mult(newbody5, patrickMatrix5);
		patrickManip->initial_mat(patrickMatrix5);

		render();
		ws_check();

	}
	if (linearly == true)
	{
		// Translate.
		patrickMatrix.translation(GsVec(patrickX, patrickY, patrickZ));

		// Set the matrix.
		//patrickManip->initial_mat(patrickMatrix);


		patrickMatrix2.translation(GsVec(patrickX, patrickY, patrickZ));
		//patrickManip2->initial_mat(patrickMatrix2);

		patrickMatrix3.translation(GsVec(patrickX, patrickY, patrickZ));
		//patrickManip3->initial_mat(patrickMatrix3);

		patrickMatrix4.translation(GsVec(patrickX, patrickY, patrickZ));
	//	patrickManip4->initial_mat(patrickMatrix4);

		patrickMatrix5.translation(GsVec(patrickX, patrickY, patrickZ));
		//patrickManip5->initial_mat(patrickMatrix5);

		
	}
	patrickManip->initial_mat(patrickMatrix);
	patrickManip2->initial_mat(patrickMatrix2);
	patrickManip3->initial_mat(patrickMatrix3);
	patrickManip4->initial_mat(patrickMatrix4);
	patrickManip5->initial_mat(patrickMatrix5);

	render();
	ws_check();
}

int MyViewer::handle_keyboard(const GsEvent &e)
{
	switch (e.key)
	{
	case GsEvent::KeyEsc: gs_exit(); return 1;
		//case 'n': { bool b = !_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		//q moves whole arm up
	case 'q': {
		/*fullarmmove = true;
		elbowmove = false;
		wristmove = false;
		ARM_MOVEMENT(0.04906f);
		return 1;*/

	//	rotaterightfin += 0.05f;
		rotaterightfin += (gspi / 720);
		rotpat = false;
		FINMOVETORIGHT = true;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = false;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;
		
		return 1;

	}
	case 'a': {//a moves whole arm down


		/*fullarmmove = true;
		elbowmove = false;
		wristmove = false;
		ARM_MOVEMENT(-0.04906f);
		return 1;*/

		rotaterightfin -= (gspi / 720);
		rotpat = false;
		FINMOVETORIGHT = true;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = false;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;
	}
	case 'w': {//w moves elbow up

		/*fullarmmove = false;
		elbowmove = true;
		wristmove = false;
		ARM_MOVEMENT(0.04906f);

		return 1;*/
		rightlegmove += (gspi / 180);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = true;
		LEGTOMOVELEFT = false;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;
	}
	case 's': {//s moves elbow down
			   //upperarmrotation = 0.0f;
		/*wristrotation = 0.0f;
		fullarmmove = false;
		elbowmove = true;
		wristmove = false;
		ARM_MOVEMENT(-0.04906f);
		return 1;
		*/
		rightlegmove -= (gspi / 180);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = true;
		LEGTOMOVELEFT = false;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;

	}
	case 'e': { //moves wrist up
		leftlegmove += (gspi / 180);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = true;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;
	}
	case 'd': { //moves wrist down 
		leftlegmove -= (gspi / 180);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = true;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;
	}
	case 'r': {
		leftfinmove -= (gspi / 720);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = false;
		FINTOMOVELEFT = true;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;

	}

	case 'f': {
		leftfinmove += (gspi / 720);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = false;
		FINTOMOVELEFT = true;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;

	}
	
	case 't': {
		torsoit += (gspi / 360);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = false;
		FINTOMOVELEFT = false;
		TORSOMOVE = true;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;
	}

	case 'g': {
		torsoit -= (gspi / 360);
		rotpat = false;
		FINMOVETORIGHT = false;
		linearly = false;
		LEGTOMOVERIGHT = false;
		LEGTOMOVELEFT = false;
		FINTOMOVELEFT = false;
		TORSOMOVE = true;
		movePatrick(0.0, 0.0, 0.0);
		//rotpat = false;

		return 1;
	}

	case GsEvent::KeyRight:
	{
		//rotaterightfin += -0.05f;
		//rotpat = true;
		linearly = true;
	//	FINMOVETORIGHT = false;
		movePatrick(1.0, 0.0, 0.0);
		//rotpat = false;
		//rotpat = false;
		linearly = false;
		return 1;
		
	}
	case GsEvent::KeyLeft:
	{
		//rotaterightfin += -0.05f;
		//rotpat = true;
		linearly = true;
		//leftfinmove = false;
		movePatrick(-1.0, 0.0, 0.0);
		//rotpat = false;
		//rotpat = false;
		linearly = false;
		return 1;
	}
	case GsEvent::KeyUp:
	{
		rotpat = false;
		linearly = true;
		movePatrick(0.0, 0.0, 1.0);
		linearly = false;
		return 1;
		
	}
	case GsEvent::KeyDown:
	{
		rotpat = false;
		linearly = true;
		movePatrick(0.0, 0.0, -1.0);
		linearly = false;
		return 1;
		
	}
	case GsEvent::KeySpace:
	{
		double lt, t0 = gs_time();
		do
		{
			lt = gs_time() - t0;
			
			//camera().eye.x += 0.001f;
			camera().center.y += 1.0f;
			//camera() += 0.001f;
			render();
			ws_check();
			//message().setf(“local time = %f”, lt);
		} while (lt<3.0f);
	}
	default: gsout << "Key pressed: " << e.key << gsnl;
	}

	return 0;
}


int MyViewer::uievent(int e)
{
	switch (e)
	{
	case EvNormals: show_normals(_nbut->value()); return 1;
	case EvAnimate: run_animation(); return 1;
	case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
