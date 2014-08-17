#pragma once

#include "Image.h"


class CaptionImageSet
{
public:
	CaptionImageSet(Image* subject, Image* caption = nullptr);
	~CaptionImageSet(void);

	Image* GetSubject(void) { return subject; }
	Image* GetCaption(void) { return caption; }

	bool HasCaption(void) { return caption != nullptr; }

private:
	Image* subject;
	Image* caption;
};

