#include "PriorityDecoder.h"

void PriorityDecoder::unwrapPhase() {
	int start = getStart();
	toProcess.push(UnwrapPath(0, start, phase[start]));

	while(!toProcess.empty()) {
		const UnwrapPath& cur = toProcess.top();
		int i = cur.target;
		if(ready[i]) {
			phase[i] = cur.resultPhase;
			ready[i] = false;
			float sourcePhase = phase[i];
			toProcess.pop();

	    int x = i % width;
			int y = i / width;

			if (y > 0) // up
				unwrapPhase(i - width, sourcePhase);
			if (y < height - 1) // down
				unwrapPhase(i + width, sourcePhase);
			if (x > 0) // left
				unwrapPhase(i - 1, sourcePhase);
			if (x < width - 1) // right
				unwrapPhase(i + 1, sourcePhase);
		} else {
			toProcess.pop();
		}
	}
}

void PriorityDecoder::unwrapPhase(int target, float sourcePhase) {
	if(ready[target]) {
		float diff = phase[target] - (sourcePhase - (int) sourcePhase);
		if(diff > .5)
			diff--;
		else if(diff < -.5)
			diff++;
		float resultPhase = sourcePhase + diff;
		toProcess.push(UnwrapPath(diff, target, resultPhase));
	}
}
