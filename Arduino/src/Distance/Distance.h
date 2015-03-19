/**
*	@author Jacob Chesley
*	@date 3/19/2015
*/

#ifndef Distance_h
#define Distance_h

class Distance{
	Distance(float circumferenceOfWheel, float numBlackWhiteMarkings);
	Distance(float distanceBetweenMarkings);
	~Distance();

	float HitWhite();
	float HitBlack();

private:
	currentDistance;

};
#endif