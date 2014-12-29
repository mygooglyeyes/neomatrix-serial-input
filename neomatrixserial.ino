// Adafruit_NeoMatrix example for single NeoPixel Shield.
// scrolls data read from serial to matrix

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define PIN 6
String readString;



adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] =
{
	matrix.Color(0, 0, 255), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255)
};

void setup()
{
	Serial.begin(9600);
	matrix.begin();
	matrix.setTextWrap(false);
	matrix.setBrightness(40);
	matrix.setTextColor(colors[0]);
}

int x    = matrix.width();
int pass = 0;

void loop ()
{
	matrix.fillScreen(0);
	matrix.setCursor(x, 0);
	while (Serial.available())
	{
		delay(10);
		if (Serial.available() > 0)
		{
			char c = Serial.read();
			readString += c;
		}
		
	}

	if (readString.length() > 0)
	{
		matrix.println(readString);
		pass = -abs(readString.length());

		if(--x < pass * 6)
		{
			x = matrix.width();
			readString = "";
		}

		matrix.show();
		delay(70);
	}

}
