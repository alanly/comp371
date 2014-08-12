/**
 * @author Alan Ly
 */

#include "Light.h"


using namespace std;


Light::Light(void)
{
	lColor = glm::vec3(1.f, 1.f, 1.f);
	lCoefficients = glm::vec3(0.f, 0.f, 0.02f);
}


Light::~Light(void)
{
}

void Light::Load(ci_istringstream& iss)
{
	ci_string line;

	// Parse model line by line
	while(std::getline(iss, line))
	{
		// Splitting line into tokens
		ci_istringstream strstr(line);
		istream_iterator<ci_string, char, ci_char_traits> it(strstr);
		istream_iterator<ci_string, char, ci_char_traits> end;
		vector<ci_string> token(it, end);

		if (ParseLine(token) == false)
		{
			fprintf(stderr, "Error loading scene file... token:  %s!", token[0]);
			getchar();
			exit(-1);
		}
	}
}

bool Light::ParseLine(const std::vector<ci_string> &token)
{
	if (token.empty() == false)
	{
		if (token[0].empty() == false && token[0][0] == '#')
		{
			return true;
		}

		if (token[0] == "name")
		{
			assert(token.size() > 2);
			assert(token[1] == "=");

			lName = token[2];
		}
		else if (token[0] == "position")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			SetLightPosition(
				static_cast<float>(atof(token[2].c_str())),
				static_cast<float>(atof(token[3].c_str())),
				static_cast<float>(atof(token[4].c_str()))
				);
		}
		else if (token[0] == "color")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			lColor.x = static_cast<float>(atof(token[2].c_str()));
			lColor.y = static_cast<float>(atof(token[3].c_str()));
			lColor.z = static_cast<float>(atof(token[4].c_str()));
		}
		else if (token[0] == "coefficients")
		{
			assert(token.size() > 4);
			assert(token[1] == "=");

			lCoefficients.x = static_cast<float>(atof(token[2].c_str()));
			lCoefficients.y = static_cast<float>(atof(token[3].c_str()));
			lCoefficients.z = static_cast<float>(atof(token[4].c_str()));
		}
		else
		{
			return false;
		}
	}

	return true;
}


void Light::Enlighten(unsigned int lightCount)
{
	// Determine our light ID.
	unsigned int LIGHT_ID = GL_LIGHT0 + lightCount;

	// Enable the light.
	glEnable(GL_LIGHTING);
	glEnable(LIGHT_ID);
	glEnable(GL_NORMALIZE);

	// What is this light model magic?
	GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// But we don't want any spotlight stuff...
	GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
	GLint spot_exponent = 30;
	GLint spot_cutoff = 180;
	glLightfv(LIGHT_ID, GL_SPOT_DIRECTION, spot_direction);
	glLighti(LIGHT_ID, GL_SPOT_EXPONENT, spot_exponent);
	glLighti(LIGHT_ID, GL_SPOT_CUTOFF, spot_cutoff);

	// Set our light attenuation co-efficients.
	glLightf(LIGHT_ID, GL_CONSTANT_ATTENUATION, lCoefficients.x);
	glLightf(LIGHT_ID, GL_LINEAR_ATTENUATION, lCoefficients.y);
	glLightf(LIGHT_ID, GL_QUADRATIC_ATTENUATION, lCoefficients.z);

	// Set the light position.
	glLightfv(LIGHT_ID, GL_POSITION, &lPosition[0]);

	// Set the light colour for ambient, diffuse, and specular.
	glLightfv(LIGHT_ID, GL_AMBIENT, &lColor[0]);
	glLightfv(LIGHT_ID, GL_DIFFUSE, &lColor[0]);
	glLightfv(LIGHT_ID, GL_SPECULAR, &lColor[0]);
}