#include "CaptionImageSet.h"


CaptionImageSet::CaptionImageSet(Image* subject, Image* caption)
	: subject(subject), caption(caption)
{
}


CaptionImageSet::~CaptionImageSet(void)
{
	delete caption;
	delete subject;
}
