class RandomPattern: public LightPattern {
public:
	RandomPattern(PixelGroup* target, bool localPattern, int width, int size, int waitMillis,
			long duration) :
			LightPattern(target, duration, 0), localPattern(localPattern), width(width), size(
					size), waitMillis(waitMillis) {
		eraseWhenDone = true;
	}

	bool run(Adafruit_NeoPixel* strip) {
		uint32_t color;
		if (millis() < (patternStart + duration)) {
			for (int idx = 0; idx < width; idx++) {
				if (idx % size == 0) {
					color = LightUtil::randomDistinctiveColor(strip);
				} else if (idx % size == (size - 1)) {
					color = black; // one black stripe between blocks
				}

				if (!localPattern) {
					if (LightAddress::appliesHere(idx)) {
						LightUtil::setColumnColor(strip,
								LightAddress::fieldToController(idx), color);
					}
				} else {
					LightUtil::setColumnColor(strip, idx, color);
				} // field vs individual
			}
			strip->show();
			calculateTimingDelay(waitMillis);
		}

		checkErase(strip);
		return isDone();
	}
private:
	bool localPattern;
	int width;
	int size;
	int waitMillis;
};

